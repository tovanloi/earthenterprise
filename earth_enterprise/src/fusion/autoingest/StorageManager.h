/*
 * Copyright 2019 The Open GEE Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <map>
#include <mutex>
#include <string>
#include <time.h>
#include <vector>
#include <memory>

#include "common/khCache.h"
#include "common/khFileUtils.h"
#include "common/notify.h"
#include "common/SharedString.h"
#include "StorageManagerAssetHandle.h"
#include "AssetSerializer.h"

// Items stored in the storage manager must inherit from the StorageManaged class
class StorageManaged {
  public:
    time_t timestamp;
    uint64 filesize;
    StorageManaged() : timestamp(0), filesize(0) {}
};

// Handles to items stored in the storage manager must implement the asset
// handle interface. This is only used for the legacy Get function.
template<class AssetType>
class AssetHandleInterface {
  public:
    virtual bool Valid(const AssetPointerType<AssetType> &) const = 0;
};

template<class AssetType>
class StorageManagerInterface {
  public:
    using PointerType = AssetPointerType<AssetType>;
    virtual AssetHandle<const AssetType> Get(const AssetKey &) = 0;
    virtual AssetHandle<AssetType> GetMutable(const AssetKey &) = 0;
    virtual ~StorageManagerInterface() {}
};

template<class AssetType>
class StorageManager : public StorageManagerInterface<AssetType> {
  public:
    using Base = StorageManagerInterface<AssetType>;
    using PointerType = typename Base::PointerType;
    using SerializerPtr = std::unique_ptr<AssetSerializerInterface<AssetType>>;

    StorageManager(uint cacheSize,
                   bool limitByMemory,
                   uint64 maxMemory,
                   const std::string & type,
                   SerializerPtr serializer) :
        assetType(type),
        serializer(std::move(serializer)),
        cache(cacheSize, type)
    {
      SetCacheMemoryLimit(limitByMemory, maxMemory);
    }
    StorageManager(uint cacheSize,
                   bool limitByMemory,
                   uint64 maxMemory,
                   const std::string & type) :
        StorageManager(cacheSize, limitByMemory, maxMemory, type,
                       SerializerPtr(new AssetSerializerLocalXML<AssetType>())) {}
    ~StorageManager() = default;

    inline uint32 CacheSize() const;
    inline uint32 CacheCapacity() const;
    inline uint32 DirtySize() const;
    inline uint64 CacheMemoryUse() const;
    inline void SetCacheMemoryLimit(const bool & limitByMemory, const uint64 & maxMemory);
    inline void UpdateCacheItemSize(const AssetKey & key);
    inline uint64 GetCacheItemSize(const AssetKey & key);
    inline void AddNew(const AssetKey &, const PointerType &);
    inline void AddExisting(const AssetKey &, const PointerType &);
    inline void NoLongerNeeded(const AssetKey &, bool = true);
    void Abort();
    bool SaveDirtyToDotNew(khFilesTransaction &, std::vector<AssetKey> *);
    PointerType Get(const AssetHandleInterface<AssetType> *, const AssetKey &, bool, bool, bool);
    
    // Pass a handle to a const to prevent callers from modifying it.
    AssetHandle<const AssetType> Get(const AssetKey &);
    
    // Pass a handle to a non-const so callers can modify it.
    AssetHandle<AssetType> GetMutable(const AssetKey &);
  private:
    using CacheType = khCache<AssetKey, PointerType>;

    static const bool check_timestamps;

    mutable std::recursive_mutex storageMutex;
    const std::string assetType;
    const SerializerPtr serializer;
    CacheType cache;
    std::map<AssetKey, PointerType> dirtyMap;

    StorageManager(const StorageManager &) = delete;
    StorageManager& operator=(const StorageManager &) = delete;
    
    PointerType GetEntryFromCacheOrDisk(const AssetKey &);
};

template<class AssetType>
inline uint32 StorageManager<AssetType>::CacheSize() const {
  std::lock_guard<std::recursive_mutex> lock(storageMutex);
  return cache.size();
}

template<class AssetType>
inline uint32 StorageManager<AssetType>::CacheCapacity() const {
  std::lock_guard<std::recursive_mutex> lock(storageMutex);
  return cache.capacity();
}

template<class AssetType>
inline uint32 StorageManager<AssetType>::DirtySize() const {
  std::lock_guard<std::recursive_mutex> lock(storageMutex);
  return dirtyMap.size();
}

template<class AssetType>
inline uint64 StorageManager<AssetType>::CacheMemoryUse() const {
  std::lock_guard<std::recursive_mutex> lock(storageMutex);
  return cache.getMemoryUse();
}

template<class AssetType>
inline void StorageManager<AssetType>::SetCacheMemoryLimit(const bool & limitByMemory, const uint64 & maxMemory) {
  std::lock_guard<std::recursive_mutex> lock(storageMutex);
  cache.setCacheMemoryLimit(limitByMemory, maxMemory);
}

template<class AssetType>
inline void StorageManager<AssetType>::UpdateCacheItemSize(const AssetKey & key) {
  std::lock_guard<std::recursive_mutex> lock(storageMutex);
  cache.updateCacheItemSize(key);
}

template<class AssetType>
inline uint64 StorageManager<AssetType>::GetCacheItemSize(const AssetKey & key) {
  std::lock_guard<std::recursive_mutex> lock(storageMutex);
  return cache.getCacheItemSize(key);
}

template<class AssetType>
inline void
StorageManager<AssetType>::AddNew(const AssetKey & key, const PointerType & value) {
  std::lock_guard<std::recursive_mutex> lock(storageMutex);
  cache.Add(key, value);
  // New assets are automatically dirty
  dirtyMap.emplace(key, value);
}

template<class AssetType>
inline void
StorageManager<AssetType>::AddExisting(const AssetKey & key, const PointerType & value) {
  std::lock_guard<std::recursive_mutex> lock(storageMutex);
  cache.Add(key, value);
}

template<class AssetType>
inline void
StorageManager<AssetType>::NoLongerNeeded(const AssetKey & key, bool prune) {
  std::lock_guard<std::recursive_mutex> lock(storageMutex);
  cache.Remove(key, prune);
}

// This is the "legacy" Get function used by the AssetHandle_ class (see
// AssetHandle.h). New code should use the other Get function or the
// GetMutable function as appropriate, which return AssetHandle objects,
// which are defined in StorageManagerAssetHandle.h. Evetually this function
// should go away.
template<class AssetType>
typename StorageManager<AssetType>::PointerType
StorageManager<AssetType>::Get(
    const AssetHandleInterface<AssetType> * handle,
    const AssetKey & ref,
    bool checkFileExistenceFirst,
    bool addToCache,
    bool makeMutable) {
  const AssetKey key = AssetType::Key(ref);
  const std::string filename = AssetType::Filename(key);

  std::lock_guard<std::recursive_mutex> lock(storageMutex);

  // Check in cache.
  PointerType entry;
  cache.Find(key, entry);
  if (entry && !handle->Valid(entry)) entry = PointerType();
  bool updated = false;

  // Try to load from XML.
  if (!entry) {
    if (checkFileExistenceFirst) {
      if (!khExists(filename)) {
        // In this case DoBind is allowed not to throw even if
        // we configured to normally throw.
        return PointerType();
      }
    }

    // Will succeed, generate stub, or throw exception.
    entry = serializer->Load(key);
    updated = true;
  } else if (check_timestamps) {
    uint64 filesize = 0;
    time_t timestamp = 0;
    if (khGetFileInfo(filename, filesize, timestamp) &&
        ((timestamp != entry->timestamp) ||
         (filesize != entry->filesize))) {
      // The file has changed on disk.

      // Drop the current entry from the cache.
      cache.Remove(key, false);  // Don't prune, the Add() will.

      // Will succeed, generate stub, or throw exception.
      entry = serializer->Load(key);
      updated = true;
    }
  }

  if (entry) {
    // Add it to the cache.
    if (addToCache && updated)
      cache.Add(key, entry);

    // Add it to the dirty map. If it's already in the dirty map the existing
    // one will win; that's OK.
    if (makeMutable)
      dirtyMap.emplace(key, entry);
  }

  return entry;
}

template<class AssetType>
typename StorageManager<AssetType>::PointerType
StorageManager<AssetType>::GetEntryFromCacheOrDisk(const AssetKey & ref) {
  AssetKey key = AssetType::Key(ref);

  // Deal quickly with an invalid key
  if (!AssetType::ValidRef(key)) return PointerType();

  const std::string filename = AssetType::Filename(key);

  // Check in cache.
  PointerType entry;
  cache.Find(key, entry);
  bool updated = false;

  // Try to load from XML.
  if (!entry) {
    // Avoid throwing exceptions when the file doesn't exist
    if (!khExists(filename)) return PointerType();
    // Will succeed, generate stub, or throw exception.
    entry = serializer->Load(key);
    updated = true;
  } else if (check_timestamps) {
    uint64 filesize = 0;
    time_t timestamp = 0;
    if (khGetFileInfo(filename, filesize, timestamp) &&
        ((timestamp != entry->timestamp) ||
         (filesize != entry->filesize))) {
      // The file has changed on disk.

      // Drop the current entry from the cache.
      cache.Remove(key, false);  // Don't prune, the Add() will.

      // Will succeed, generate stub, or throw exception.
      entry = serializer->Load(key);
      updated = true;
    }
  }

  if (entry && updated) {
    // Add it to the cache.
    cache.Add(key, entry);
  }

  return entry;
}

template<class AssetType>
AssetHandle<const AssetType> StorageManager<AssetType>::Get(const AssetKey & ref) {
  std::lock_guard<std::recursive_mutex> lock(storageMutex);
  PointerType entry = GetEntryFromCacheOrDisk(ref);
  return AssetHandle<const AssetType>(std::shared_ptr<const AssetType>(entry), nullptr);
}

template<class AssetType>
AssetHandle<AssetType> StorageManager<AssetType>::GetMutable(const AssetKey & ref) {
  std::lock_guard<std::recursive_mutex> lock(storageMutex);
  PointerType entry = GetEntryFromCacheOrDisk(ref);
  // Add it to the dirty map. If it's already in the dirty map the existing
  // one will win; that's OK.
  dirtyMap.emplace(ref, entry);
  return AssetHandle<AssetType>(entry, [=]() {
    UpdateCacheItemSize(AssetType::Key(ref));
  });
}

template<class AssetType>
void StorageManager<AssetType>::Abort() {
  std::lock_guard<std::recursive_mutex> lock(storageMutex);
  // remove all the dirty Impls from the cache
  for (const std::pair<AssetKey, PointerType> & entry : dirtyMap) {
    cache.Remove(entry.first, false); // false -> don't prune
  }
  cache.Prune();  // prune at the end to avoid possible prune thrashing

  // now clear the dirtyMap itself
  dirtyMap.clear();
}

template<class AssetType>
bool StorageManager<AssetType>::SaveDirtyToDotNew(
    khFilesTransaction &savetrans,
    std::vector<AssetKey> *saved) {
  notify(NFY_INFO, "Writing %lu %s records", dirtyMap.size(), assetType.c_str());
  std::lock_guard<std::recursive_mutex> lock(storageMutex);
  typename std::map<AssetKey, PointerType>::iterator entry = dirtyMap.begin();
  while (entry != dirtyMap.end()) {
    std::string filename = entry->second->XMLFilename() + ".new";

    if (serializer->Save(entry->second, filename)) {
      savetrans.AddNewPath(filename);
      if (saved) {
        saved->push_back(entry->first);
      }
      // Remove the element and advance the pointer
      entry = dirtyMap.erase(entry);
    } else {
      return false;
    }
  }
  return true;
}

#endif // STORAGEMANAGER_H

