|Google logo|

===================
Create custom masks
===================

.. container::

   .. container:: content

      .. rubric:: Table of Contents

      -  :ref:`Getting started <Getting_Started>`
      -  :ref:`How to use this guide <How_Use_Guide>`
      -  :ref:`What is gepolymaskgen? <What_gepolymaskgen>`
      -  :ref:`What is gemaskgen? <What_gemaskgen>`
      -  :ref:`Useful information about gepolymaskgen <Useful_Info_gepolymaskgen>`
      -  :ref:`Useful information about gemaskgen <Useful_info_gemaskgen>`
      -  :ref:`When to use gepolymaskgen <When_Use_gepolymaskgen>`
      -  :ref:`When to use gemaskgen <When_Use_gemaskgen>`
      -  :ref:`Recommended tools for creating custom mask
         files <Recommended_Tools_Mask_Filters>`
      -  :ref:`gepolymaskgen command usage <gepolymaskgen_Command_Usage>`
      -  :ref:`Example use cases and commands to build custom
         masks <Example_Use_Cases_Commands>`

         -  :ref:`Case 1: Create custom masks for imagery which has no fill
            pixels (usable imagery goes to the
            edges) <Imagery_No_Fill_Pixels>`

            -  :ref:`Example A: Creating an edge-matched mask with no
               feather <Edge_Match_No_Feather>`
            -  :ref:`Example B: Creating an edge-matched mask with a fixed
               value feather <Edge_Mask_Fixed_Feather>`

         -  :ref:`Case 2: Create custom masks for
            islands <Custom_Mask_Islands>`

            -  :ref:`Example A: Create a custom edge-matched mask for an
               island that masks into the land <Island_Masks_Into_Land>`
            -  :ref:`Example B: Create a custom edge-matched mask for an
               island that masks into the water <Island_Masks_Into_Water>`

         -  :ref:`Case 3: Create custom masks with coastlines and shared
            edges with other imagery resources <Masks_Coastline_Shared_Edges>`

            -  :ref:`Example A: Create an edge-matched custom mask that
               feathers coastlines and external edges with the same
               feather value <Coastline_External_Edges_Same_Values>`
            -  :ref:`Example B: Create an edge-matched custom mask with
               feathered coastlines and feathered external
               edges <Feathered_Coastlines_External_Edges>`
            -  :ref:`Example C: Feathered internal coastline and no-feather
               external edge <Feathered_Internal_Coastline_No_Edge>`

         -  :ref:`Case 4: Masking out sections within an image
            resource <Masking_Out_Sections_Large_Image>`

            -  :ref:`Example A: Creating an edge-matched mask with a
               feathered edge and masking missing internal imagery in
               one step <Feathered_Edge_Masking_Missing_Internal_Imagery_One_Step>`
            -  :ref:`Example B: Creating an edge-matched mask with a
               feathered edge and masking missing internal imagery in
               two steps <Feathered_Edge_Masking_Missing_Internal_Imagery_Two_Step>`

         -  :ref:`Case 5: Building custom masks with both gemaskgen and
            gepolymaskgen <Custom_Masks_gemaskgen_gepolymaskgen>`

      -  :ref:`Appendix A: Importing custom masks with imagery and terrain
         resources in Google Earth Enterprise Fusion
         Pro <Importing_Custom_Masks_Imagery_Terrain_GEE_Fusion>`

         -  :ref:`Example 1: Enable havemask mode in the Fusion GUI for a new
            image resource <Enable_havemask_New_Image_Resource>`
         -  :ref:`Example 2: Enable havemask mode by command line for a new
            image resource <Enable_havemask_Command_Line_New_Image_Resource>`
         -  :ref:`Example 3: Enable havemask mode in the Fusion GUI for an
            existing image resource <Enable_havemask_Existing_Image_Resource>`
         -  :ref:`Example 4: Enable havemask mode by command line for an
            existing image resource <Enable_havemask_Command_Line_Existing_Image_Resource>`

      -  :ref:`Appendix B: Locating mask files and Fusion format data in an
         Asset Root <Locating_Mask_Files_Format_Data_Asset_Root>`

         -  :ref:`Example 1: Locate the Fusion format imagery (.kip) and mask
            (.kmp) files of an image resource <Locate_Fusion_Format_Imagery_Mask_Files_Image_Resource>`
         -  :ref:`Example 2: Locate a mask.tif file automatically built by
            the automask feature of a Fusion resource
            build <Locate_Mask_File_Built_Automask_Fusion_Build>`
         -  :ref:`Example 3: Locate the mask.tif file and Fusion format .kip
            file utilized for building the Fusion format .kmp (mask
            product) <Locate_Mask_File_Fusion_Format_File_Building_Mask_Product>`

      -  :ref:`Appendix C: Determining source file raster size with
         geinfo <Determining_Source_File_Raster_Size_geinfo>`

         -  :ref:`Maximum suggested raster dimensions for source files used
            as gepolymaskgen --base_image files <Maximum_Suggested_Raster_Dimensions_Source_Files_gepolymaskgen>`
         -  :ref:`Square-shaped rasters <Square_Shaped_Rasters>`
         -  :ref:`Rectangular-shaped rasters <Rectangular_Sharped_Rasters>`

      -  :ref:`Appendix D: Building high resolution mask files with
         gemaskgen <Building_High_Resolution_Mask_Files_gemaskgen>`
      -  :ref:`Appendix E: Using a Photo Editing application to augment a
         custom mask <Using_Photo_Editing_App_Augment_Custom_App>`
      -  :ref:`Appendix F: Building custom masks for large source
         imagery <Building_Custom_Masks_Large_Source_Imagery>`
      -  :ref:`Appendix G: Gepolymaskgen help menu <gepolymaskgen_Help_Menu>`

      .. _Getting_Started:
      .. rubric:: Getting started

      A new masking tool is now available with Google Earth Enterprise
      (GEE) Fusion Pro version 4.0 which is able to create very high
      quality, custom masks for imagery resources. This tool,
      ``gepolymaskgen``, supports clipping coastlines from imagery
      resources or arbitrary polygonal shapes from imagery resources,
      and can be integrated into source file preparation or creating
      updated masks for existing imagery resources.

      .. _How_Use_Guide:
      .. rubric:: How to use this guide

      This guide is intended to provide in-depth information about
      creating custom masks, the new ``gepolymaskgen`` tool, and the
      existing ``gemaskgen`` tool, as well as example cases with command
      sequences to build your own custom masks. You may jump directly to
      the cases section to build your custom masks and then read the
      informational sections later, or read the entire guide from start
      to finish.

      .. _What_gepolymaskgen:
      .. rubric:: What is gepolymaskgen?

      ``gepolymaskgen`` is a new low-level GEE Fusion Pro tool capable
      of creating a mask file for a single source image, mosaicked
      source imagery set, or a GEE Fusion Pro imagery resource based on
      user-specified masking options. With this tool, users can
      programmatically create masks for imagery that follows a shoreline,
      create masks at a fixed feather value, or augment mask files with
      KML polygons from Google Earth to show or hide imagery through a
      mask. The ``gepolymaskgen`` tool has two key differences from the
      existing automask tool ``gemaskgen``: 1) ``gepolymaskgen`` only
      fulfills operations specified by users and does not operate
      automatically in the same manner as ``gemaskgen``; 2)
      ``gepolymaskgen`` may only be invoked by the command line,
      separately from the normal automated GEE resource import
      sequences.

      .. _What_gemaskgen:
      .. rubric:: What is gemaskgen?

      ``gemaskgen`` is an existing low-level masking tool bundled with
      GEE Fusion Pro that is invoked by Fusion when building an imagery
      or terrain resource. The ``gemaskgen`` tool was designed to
      automatically build mask files for imported source imagery and
      terrain data to hide external, or internal, fill data from view on
      the globe. In order to build the mask, users must specify within
      the Resource Editing tool which band (Red, Green, or Blue) should
      be used to create the mask; the amount of feathering that should
      be applied between the fill data (masked) and the usable imagery;
      a tolerance value (buffer) that may be applied by the tool when
      checking if a pixel is fill value or not; if the entire image
      should be checked for fill data (holes); and if both white and
      black fill data should be included in the mask (0 is assumed
      default, 255 to be included).

      The ``gemaskgen`` tool will be invoked by GEE Fusion Pro after the
      source imagery is converted into Fusion format (``kip``).
      ``gemaskgen`` collects the value for each corner pixel on band 1
      of the image resource - which is assumed to be the fill data pixel
      value (0 is the typical value) - and then systematically moves
      through the ``kip`` adding all fill data into the mask until
      non-fill data is found. The edge between the fill data and usable
      imagery is feathered based on the user-specified feather value (in
      pixels). The new GEE Fusion Pro imagery or terrain resource is
      comprised of both the imported source data and the computed mask
      file as demonstrated in the graphic below.

      |Masked imagery diagram|

      .. _Useful_Info_gepolymaskgen:
      .. rubric:: Useful information about gepolymaskgen

      -  ``gepolymaskgen`` is a single-threaded low-level GEE Fusion
         command-line tool that may be manually invoked for building
         custom mask files for imagery or terrain data sets
      -  Operationally, ``gepolymaskgen`` is CPU-intensive and *very*
         RAM-intensive.

         -  At least 16GB free RAM must be available on the machine to
            safely build custom masks with ``gepolymaskgen``.

      -  All mask files built by ``gepolymaskgen`` will be written out
         in ``GeoTIFF`` format.
      -  Mask files will be written with complementary geographic
         coordinates and projection to the source data.

         -  All mask files, KML polygons, vector source files, and
            source imagery should be in the same projection for building
            custom masks.
         -  Masks may be built for resources in Plate-Carre projection
            (EPSG:4326) or Mercator projection (EPSG:3857).

      -  ``gepolymaskgen`` can build a mask for one source file or many
         source files that are described with a ``khvr`` virtual raster
         text file.
      -  Mask files built by ``gepolymaskgen`` will use 255 to show
         imagery and 0 to hide imagery.

         -  All new masks start as an image file with all pixels of
            value 0 - all imagery will be masked.
         -  Areas to hide (to be masked) will be set to pixel value 0.
         -  The ``--or_mask`` masking operator will, typically, show
            more imagery for an area in the final mask.
         -  The ``--and_neg_mask`` masking operator will, typically,
            hide more imagery for an area in the final mask.

      -  The final mask is built by subtracting and adding desired areas
         to hide or view by a sequence of operators.

      .. note::

         **Note:** It is easy to create very high resolution masks with
         ``gepolymaskgen``, to the point of pixel-by-pixel matching for
         the source imagery. Please check the overall raster size of
         your source imagery before creating a custom mask with
         ``gepolymaskgen`` as it is easy to create a custom mask that
         will be larger than the 2GB ``GeoTIFF`` file size limit. Please
         see :ref:`Appendix C <Determining_Source_File_Raster_Size_geinfo>` for further information
         on calculating the overall size of a mask file.

      .. _Useful_info_gemaskgen:
      .. rubric:: Useful information about gemaskgen

      -  ``gemaskgen`` is a single-threaded low-level Fusion tool which
         is automatically called during image and terrain resource
         builds after the source imagery or terrain is imported.
      -  All mask files computed by ``gemaskgen`` will be written out in
         ``GeoTIFF`` format.
      -  ``gemaskgen`` scans through an imported imagery or terrain
         resource to:

         -  identify the pixel value of each corner pixel, and
         -  erode inward into the image to mask out all pixels that have
            the same pixel value as the corner pixels.

      -  ``gemaskgen`` will, by default, create an output mask file
         which is no more than 16,000 pixels on any one side.

         -  This can lead to low-resolution masks for high resolution
            data.

      -  Masks may be manually created by invoking ``gemaskgen``
         directly!

         -  Masks larger than 16,000 pixels may be created for large
            imagery resources with the ``--maxsize``\ option.
         -  Please see :ref:`Appendix D <Building_High_Resolution_Mask_Files_gemaskgen>` for additional
            details.

      .. rubric:: Comparison of the gemaskgen and gepolymaskgen
         :name: comparison-of-the-gemaskgen-and-gepolymaskgen

      ============================================================================================================= ============================================================= =======================================================
      Capability                                                                                                    ``gemaskgen``                                                 ``gepolymaskgen``
      ============================================================================================================= ============================================================= =======================================================
      Reads Fusion format imagery (.kip) and terrain (.ktp)                                                         Yes                                                           No
      Part of image resource import process                                                                         Yes, for automask mode                                        No
      Can read source file images including: ``khvrs;         GeoTIFFs;         JPEG2000``                          No, can only read Fusion imagery and terrain resource formats Yes
      Can automatically identify and mask Fill Data automatically within imagery resource (holes)                   Yes                                                           No, but may be manually removed with KML polygons
      Can feather a specified amount of pixels from the edge of the image, irrespective of the imagery pixel values No                                                            Yes
      Capable of creating high-resolution mask files                                                                Yes, manually possible                                        Yes - depends on raster dimensions of input source file
      Can automatically distinguish Fill Data from usable imagery by pixel values                                   Yes                                                           No
      Can mask out arbitrary polygonal shapes within the image resource                                             No                                                            Yes
      ============================================================================================================= ============================================================= =======================================================

      .. _When_Use_gepolymaskgen:
      .. rubric:: When to use gepolymaskgen

      The ``gepolymaskgen`` tool is best suited for when imagery is to
      be masked along specific, designated borders - such as coastlines,
      boundaries, or a building - or to mask image at a fixed feathering
      from the image edge regardless of whether usable imagery or fill data
      are at the edge.

      .. _When_Use_gemaskgen:
      .. rubric:: When to use gemaskgen

      Fusion's automask (``gemaskgen``) function is best suited for
      automatically creating mask files that detect and hide fill data
      while displaying usable (non-fill) imagery. ``gemaskgen`` is also
      very useful when working with large image resources to create a
      base mask that will be less than 2GB in file size but still
      facilitate a high fidelity mask.

      Please see :ref:`Appendix F <Building_Custom_Masks_Large_Source_Imagery>` for further
      instructions on how ``gemaskgen`` may be utilized with creating
      masks for large image resources.

      .. _Recommended_Tools_Mask_Filters:
      .. rubric:: Recommended tools for creating custom mask files

      -  A server or workstation with minimum 16GB RAM to build the
         custom masks. More RAM is better!
      -  Global coastlines as polygons for coastline masking. *Make
         certain these are polygons and not lines*.
      -  A GIS application, such as QGIS, to view source imagery
         datasets. This is helpful in determining if usable imagery is
         surrounded by fill data, reprojecting the source imagery, or
         combining multiple source files into one image.
      -  A copy of Google Earth EC to connect to and view 3D databases
         built with the custom masks for QA testing. Google Earth can
         also be used in the masking process by creating KML polygons
         for additional areas that are to be masked from view.
      -  A photo editing application such as Adobe Photoshop, GIMP, or
         similar, to view the custom mask files after ``gepolymaskgen``
         builds, or to make modifications to the mask file such as
         unmasking water bodies or exposing more visible water from a
         coastline.

      .. _gepolymaskgen_Command_Usage:
      .. rubric:: gepolymaskgen command usage

      ``gepolymaskgen`` has a few command line parameters to specify the
      workflow for creating a mask. The main workflow is directing
      ``gepolymaskgen`` to create or load an image as a reference for
      masking, generating a mask based on desired regions, feathering
      the mask edges as needed, and then writing out the resulting mask.
      Here are the main ``gepolymaskgen`` options:

      ``gepolymaskgen``

      #. **Specify which file to reference for creating the mask, or
         which existing mask file to load:**

         -  **``--base_image``**: specifies a source file that will be
            used for overall raster dimensions, geographic coordinates,
            and projection information. May be a ``GeoTIFF``,
            ``JPEG2000``, or ``KHVR`` file. Each ``gepolymaskgen``
            invocation may only include either one ``--base_image`` or
            one ``--base_mask`` for masking operations.
         -  **``--base_mask``**: specifies a mask file to read in for
            further mask processing. The specified file may be a
            ``GeoTIFF``. Each ``gepolymaskgeninvocation`` may only
            include either one ``--base_image`` or one
            ``--base_mask``\ for masking operations.

      #. **Modify the mask file by changing what is masked and
         feathering:**

         -  **``--feather``**: directs ``gepolymaskgen`` to create a
            feather along a masked edge by the specified number of
            pixels. Either positive or negative values may be specified
            with ``--feather`` to expand or contract the feathered edge
            around the masked line. Positive feather settings typically
            erode into the usable imagery from the mask line
            (contracting) while negative feather settings typically
            erode away from the usable imagery from the mask line
            (expanding). Using the ``--invert`` setting with a masking
            operation will reverse the effect a ``--feather`` operation
            has on the mask. The ``--feather`` option may be used with
            the ``--base_image``, ``--base_mask``, ``--and_neg_mask``,
            and ``--or_mask`` mask options; however, only one
            ``--feather`` option may be specified for each operator. The
            default feather value for ``--feather`` is set to 0 pixels.

         -  **``--feather_border``**: used in conjunction only with
            ``--feather``. Directs ``gepolymaskgen`` to apply a
            feather to the extent of the mask file with the same
            feathering values specified with the ``--feather`` option.
            The ``--feather_border`` option is off by default.

         -  **``--invert``:** directs ``gepolymaskgen`` to invert a
            specified mask from its original values to the opposite. In
            almost all cases, this involves swapping pixel values from 0
            to 255 or 255 to 0, depending on whether the
            ``--base_image`` or ``--base_mask`` are inverted, or an
            ``--and_neg_mask`` or\ ``--or_mask`` are inverted. Inverting
            a mask affects the ``--feather`` operations as well for
            expanding or contracting mask feathering at the specified mask
            edges. The ``--invert`` option may be combined with
            ``--base_image``, ``--base_mask``, ``--and_neg_mask``,
            ``--or_mask``, or ``--output_mask``.

         -  **``--and_neg_mask``**: directs ``gepolymaskgen`` to remove
            a specified area from view (i.e. subtracting, or masking).
            May be combined with the\ ``--feather`` and
            ``--feather_border`` options to build a feathered edge along
            masked areas. Multiple ``--and_neg_mask``\ operations may be
            combined in one ``gepolymaskgen`` sequence as necessary for
            complex mask builds. It is also possible for a
            ``gepolymaskgen``\ sequence to include
            both\ ``--and_neg_mask`` and ``--or_mask`` operations.
         -  **``--or_mask``**: directs ``gepolymaskgen`` to add a
            specified area into view (i.e. adding, or "unmasking"). May
            be combined with the ``--feather`` and ``--feather_border``
            options to build a feathered edge along masked areas.
            Multiple\ ``--or_mask`` operations may be combined in one
            ``gepolymaskgen`` sequence, as necessary, for complex mask
            builds. It is also possible for a ``gepolymaskgen`` sequence
            to include both ``--and_neg_mask`` and
            ``--or_mask``\ operations.

      #. **Specify the output mask**

         -  **``--output_mask``**: the folder path location and file name
            ``gepolymaskgen`` is to write the finished mask file. The
            completed mask file to import with GEE Fusion Pro must have
            the same file name as the source file with a ``-mask.tif``
            extension. For example, if the source file is
            ``brazil-squareimage-nofill.tif`` the mask file must be
            named ``brazil-squareimage-nofill-mask.tif``. Only one
            ``--output_mask`` may be specified per
            ``gepolymaskgen``\ operation.

         As an example, this ``gepolymaskgen`` invocation will create a
         zero-feather mask file that edge-matches source data:

         ``gepolymaskgen --feather 0 --feather_border 0 --base_image brazil-squareimage-nofill.khvr --invert --output_mask brazil-squareimage-nofill-mask.tif``

         Let's step through the sequence of events that occur when
         ``gepolymaskgen`` is invoked as noted above.
         A new mask file will be created with the same raster dimensions, projection,
         and geographic coordinates as the
         ``brazil-squareimage-nofill.khvr`` mosaic file specified with
         ``--base_image``.
         ``gepolymaskgen`` will not feather the edge
         of the new mask file (``--feather 0``) for which all pixel
         values in the mask will be 0.
         The ``--invert`` option directs ``gepolymaskgen`` to change the
         mask pixel values from 0 to 255 before writing out the finished
         mask file ``brazil-squareimage-nofill-mask.tif``.
         The resulting mask file will look like the image below as viewed in the GIMP
         photo editing tool. The resulting image resource, when imported
         into GEE Fusion Pro will display all pixels since the mask file
         includes edge-to-edge 255 pixels, to display the imagery.
         Conversely, if all pixels were value 0 (black), the image would
         be fully hidden from view.

         .. rubric:: An edge-matched, zero-feather mask file built by
            gepolymaskgen as viewed in the GIMP photo editing tool:
            :name: an-edge-matched-zero-feather-mask-file-built-by-gepolymaskgen-as-viewed-in-the-gimp-photo-editing-tool

         |Hidden masked diagram|

         All custom mask files can be built with the different
         ``gepolymaskgen`` masking operators in various combinations to
         add or subtract shapes from a mask so only the desired imagery
         is visible. Some masking situations may be very complex and
         require building multiple mask files with ``gepolymaskgen`` to
         achieve the desired effect. The next section includes some
         common use cases for building custom masks as a quick reference
         guide so you may see the steps involved and copy and adapt the
         commands to suit your own masking needs. These example cases
         include creating an edge-matched imagery mask with no
         feathering; creating a mask that clips imagery to the coastline
         on one side and creates an edge feather on the other side;
         masking islands to only show land imagery; and masking sections
         within an image.

      .. _Example_Use_Cases_Commands:
      .. rubric:: Example use cases and commands to build custom masks

      Five example cases are available below to reference for building
      custom masks for imagery resources within Google Earth Enterprise
      Fusion Pro. Each case or scenario is intended to address common
      masking challenges that may be encountered when working with
      various source imagery data sets. Each case will include
      contextual information for the scenario, workflow description, an
      example build with screenshots, and a set of command templates
      that may be copied and pasted to the command line of your system
      to assist in building a custom mask.

      The example cases include:

      **Case 1**: Creating masks for imagery that has edge-to-edge
      usable imagery pixels with a fixed-width feather;

      **Case 2:** Creating custom masks for islands with coastlines;

      **Case 3**: Creating a custom mask with coastlines on one side and
      a fixed-width feather on other sides;

      **Case 4**: Custom masks that mask out areas within the image
      utilizing a ``KML`` file;

      **Case 5**: Creating a custom mask utilizing ``gemaskgen`` for
      automatic fill detection and ``gepolymaskgen`` for coastline
      masking

      .. _Imagery_No_Fill_Pixels:
      .. rubric:: Case 1: Create custom masks for imagery which has no
         fill pixels (usable imagery goes to the edges)

      Working with source imagery which includes usable imagery to
      the image edges can cause problems for the ``gemaskgen`` tool
      since usable imagery pixels (ex: 132, 56, 200), and not fill
      pixels (ex: 0, 0, 0), will occupy the image corners that
      ``gemaskgen`` references for fill pixel values. The
      ``gepolymaskgen`` tool is well-suited to meet this masking
      challenge since a mask can be created to the exact raster dimensions
      of the image resource, the exact feathering value (0) can be
      specified, and ``gepolymaskgen`` will not attempt to read pixel
      values. Consider the imagery mosaic below in the middle of Brazil
      that includes several source images which include all usable
      imagery and no fill.

      .. rubric:: Location of image mosaic as seen with virtual raster
         file:

      |Brazil Imagery mosaic diagram|

      .. rubric:: Close up of imagery resource imported into Fusion:
         :name: close-up-of-imagery-resource-imported-into-fusion

      |Brazil Imagery Fusion import|

      Since we know the source imagery does not contain fill data, we can
      create a custom mask based on the ``khvr`` virtual mosaic
      description file, then include this for import into Fusion. For
      this process, ``gepolymaskgen`` will need to know:

      #. The base image to create the mask file from (including location
         and raster dimensions)
      #. What feather to apply to the image
      #. If the image border is to be feathered (yes)
      #. What to name the output image

      Due to how ``gepolymaskgen`` works, we will have to invert the
      output mask so the image edge is masked out instead of masking out
      the usable imagery. A ``khvr`` mosaic description file was created
      for the collection of ``JPEG2000`` imagery files with the
      ``gevirtualraster`` command, and this will be used as our base
      image since it represents the overall size of the mosaic. The
      output mask will be named the same filename as the ``khvr`` file
      but with a ``-mask.tif`` extension so it may be read into Fusion
      Pro. Two masks will be built for this case which are identical
      except for the applied feathering value. Part 1 will build an
      edge-matched mask with a zero-edge feather to show all pixels of
      the source imagery while Part 2 will build an edge-matched mask
      with a 100-pixel feather.

      .. _Edge_Match_No_Feather:
      .. rubric:: Example A: Creating an edge-matched mask with no
         feather

      The **command template** to build a zero-feather, edge-matched
      mask file with ``gepolymaskgen`` is:

      ``gepolymaskgen --feather 0 --feather_border 0 --base_image imagery.tif --invert --output_mask imagery-mask.tif``

      Here is output from the console building a working mask file for
      the example imagery:

      ``jcain@machine123:/gevol-local/src/$ time /opt/google/bin/gepolymaskgen --feather 0 --feather_border 0 --base_image brazil-squareimage-nofill.khvr --invert --output_mask brazil-squareimage-nofill-mask.tif``

      ``Fusion Notice: Feather 0``

      ``Fusion Notice: Feather border 0``

      ``Fusion Notice: Base image: brazil-squareimage-nofill.khvr``

      ``Fusion Notice: brazil-squareimage-nofill.khvr width: 20480 height: 20480``

      ``Fusion Notice: north: -7.646484e+00 south: -9.404297e+00 east: -5.387695e+01 west: -5.563477e+01``

      ``Fusion Notice: File type: KHM/Keyhole Mosaic``

      ``Fusion Notice: Projection : 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]'``

      ``Fusion Notice: Invert``

      ``Fusion Notice: Output mask: brazil-squareimage-nofill-mask.tif``

      ``Fusion Notice: Setting feather 0.``

      ``Fusion Notice: Feather border is off.``

      ``Fusion Notice: Setting base image brazil-squareimage-nofill.khvr.``

      ``Fusion Notice: Inverting current mask.``

      ``Fusion Notice: Saving mask to brazil-squareimage-nofill-mask.tif.``

      ``Fusion Notice: Writing alpha file brazil-squareimage-nofill-mask.tif``

      ``real 0m5.350s``

      ``user 0m2.670s``

      ``sys 0m2.260s``

      The resulting mask will be approximately 100MB in file size and
      will display all usable imagery in the areas of white pixels.

      .. rubric:: View of the built mask file within the GIMP photo
         editing tool with edge-to-edge display of all imagery pixels
         for the source file:

      |hidden masked diagram|

      .. rubric:: View of the image resource after import into Fusion
         Pro with the custom mask:

      |Fusion Pro with custom mask|

      Once the mask file is built by ``gepolymaskgen``, the source
      imagery may be imported into Fusion Pro by enabling the
      ``havemask`` masking mode in the Fusion GUI or specifying the
      ``--havemask`` option with the ``genewimageryresource`` or
      ``gemodifyimageryresource`` commands.

      Please see :ref:`Appendix A <Importing_Custom_Masks_Imagery_Terrain_GEE_Fusion>` for further
      information about enabling the ``havemask`` mask mode for an image
      resource.

      .. _Edge_Mask_Fixed_Feather:
      .. rubric:: Example B: Creating an edge-matched mask with a fixed
         value feather

      The same technique described in Part 1 may also be used for
      creating a mask that masks the imagery edge by a specified number
      of pixels regardless of the imagery along the edges of the image.
      In this case, suppose we have the same 15-meter resolution imagery
      for Brazil from Part 1, where each source image includes usable
      imagery in each pixel and does not include any fill data borders,
      and we wish to create a mask for the entire mosaic that feathers
      100 pixels into the image.

      The **command template** to build a 100-pixel feathered edge mask
      is:

      ``gepolymaskgen --feather -100 --feather_border 1 --base_image source-image.tif --invert --output_mask source-image-mask.tif``

      The pixel value may be larger than 100 pixels or smaller than 100
      pixels to expand the mask into the imagery or toward the imagery
      edge as desired for each image and terrain resource.

      Here is an example output from g\ ``epolymaskgen`` building the
      100-pixel feather edge-matched mask for the Brazil imagery:

      ``jcain@machine123:/gevol-local/src/$ time /opt/google/bin/gepolymaskgen --feather -100 --feather_border 1 --base_image brazil-squareimage-nofill.khvr --invert --output_mask brazil-squareimage-nofill-mask.tif``

      ``Fusion Notice: Feather -100``

      ``Fusion Notice: Feather border 1``

      ``Fusion Notice: Base image: brazil-squareimage-nofill.khvr``

      ``Fusion Notice: brazil-squareimage-nofill.khvr width: 20480 height: 20480``

      ``Fusion Notice: north: -7.646484e+00 south: -9.404297e+00 east: -5.387695e+01 west: -5.563477e+01``

      ``Fusion Notice: File type: KHM/Keyhole Mosaic``

      ``Fusion Notice: Projection : 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]'``

      ``Fusion Notice: Invert``

      ``Fusion Notice: Output mask: brazil-squareimage-nofill-mask-100feather.tif``

      ``Fusion Notice: Setting feather -100.``

      ``Fusion Notice: Feather border is on.``

      ``Fusion Notice: Setting base image brazil-squareimage-nofill.khvr.``

      ``Total tiles to process: 1``

      ``Completed 100% (1/1) - tiles/sec: 0.10 - time left: 00:00:00 [CPU: 99 Mem: 975 MB PF: 0]``

      ``Processed 1 tiles``

      ``Total time to process: 00:00:10``

      ``Average tiles per second: 0.10``

      ``Fusion Notice: Inverting current mask.``

      ``Fusion Notice: Saving mask to brazil-squareimage-nofill-mask.tif.``

      ``Fusion Notice: Writing alpha file brazil-squareimage-nofill-mask.tif``

      ``real 0m16.985s``

      ``user 0m14.450s``

      ``sys 0m2.200s``

      The resulting mask file will be approximately 100MB in file size
      with a feathered edge 100 pixels from the edge inwards into the
      image resource.

      .. rubric:: Resulting mask file from gepolymaskgen seen in the
         GIMP photo editing tool:

      |gepolymaskgen in gimp photo editor|

      .. rubric:: The image resource now has a 100-pixel feather after
         Fusion import:

      |image with 100-pixel feather in Fusion|

      Once the mask file is built by ``gepolymaskgen``, the source
      imagery may be imported into Fusion Pro by enabling the
      ``havemask`` masking mode in the Fusion GUI or specifying the
      ``--havemask`` option with the ``genewimageryresource`` or
      ``gemodifyimageryresource`` commands.

      Please see :ref:`Appendix A <Importing_Custom_Masks_Imagery_Terrain_GEE_Fusion>` for further
      information about enabling the ``havemask`` mask mode for an image
      resource.

      .. _Custom_Mask_Islands:
      .. rubric:: Case 2: Create custom masks for islands

      Masking imagery around islands is another good use case for
      ``gepolymaskgen`` since it is often desirable to only show usable
      imagery for the island above sea level and to mask imagery at the
      coastlines. In this example, we have imagery for the island of
      Oahu for Hawaii, USA, where all imagery for the island is to be
      seen in the imagery project but all imagery from the coastline
      away from the island to the edge of the imagery is to be masked
      from view.

      .. rubric:: Fusion Preview window:
         :name: fusion-preview-window

      |Fusion preview window|

      The Fusion Preview window above displays the overall dimensions
      and source file extents for four images creating an imagery mosaic
      for the island of Oahu, Hawaii, USA. A virtual raster description
      file (``KHVR``) was created for the four source files and loaded
      into the Fusion Preview window.

      .. rubric:: Importing the source imagery into Fusion Pro creates
         an image resource with imagery for the island and water
         (automask used):

      |Island and water automask in Fusion|

      Four ``JPEG2000`` images were grouped into one virtual mosaic for
      the image resource and a ``khvr`` mosaic description file was
      built with ``gevirtualraster``. To create the custom mask we need
      to:

      #. Direct ``gepolymaskgen`` to use the source ``khvr`` file as the
         base image to set the custom mask the same raster size and
         fully masks all imagery from view;
      #. Clip out the island of Oahu with a set of vector polygons so
         the island imagery will be visible;
      #. Feather along the specified polygon coastlines to facilitate
         smooth blending with other image resources (feather = 100);
      #. Write out the custom mask file.

      Two examples will be included for this case demonstrating the
      effect of positive and negative feather values for feathering
      along the shoreline. Generally speaking, a positive feather value
      will erode from the mask line inward to show less visible imagery
      while a negative feather value will draw away from the mask line
      to show more visible imagery.

      .. _Island_Masks_Into_Land:
      .. rubric:: Example A: Create a custom edge-matched mask for an
         island that masks into the land

      The **command template** for creating a custom mask for an island
      with a positive value feather is:

      ``gepolymaskgen --base_image imagery.tif --feather 100 --or_mask world_coastlines_4326.shp --output_mask imagery-mask.tif``

      The larger or smaller pixel value may be specified to expand the
      mask further from the coastline into the visible imagery (larger
      number), or to stay closer to the coastline.

      Example console output is included below:

      ``jcain@machine123:/gevol-local/src/gepolymaskgen-howto$ time gepolymaskgen --base_image glandsat_15m_oahu.khvr --feather 100 --or_mask world_coastlines_4326.shp --output_mask glandsat_15m_oahu-100mask.tif``

      ``Fusion Notice: Base image: glandsat_15m_oahu.khvr``

      ``Fusion Notice: glandsat_15m_oahu.khvr width: 10240 height: 10240``

      ``Fusion Notice: north: 2.179688e+01 south: 2.091797e+01 east: -1.575879e+02 west: -1.584668e+02``

      ``Fusion Notice: File type: KHM/Keyhole Mosaic``

      ``Fusion Notice: Projection : 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]'``

      ``Fusion Notice: Feather 100``

      ``Fusion Notice: OR mask: world_coastlines_4326.shp``

      ``Fusion Notice: Output mask: glandsat_15m_oahu-100mask.tif``

      ``Fusion Notice: Setting base image glandsat_15m_oahu.khvr.``

      ``Fusion Notice: Setting feather 100.``

      ``Fusion Notice: Writing alpha file glandsat_15m_oahu-100mask.tif``

      ``Fusion Notice: Executing: gdal_rasterize -b 1 -burn 255 -l world_coastlines_4326 world_coastlines_4326.shp glandsat_15m_oahu-100mask.tif``

      ``0...10...20...30...40...50...60...70...80...90...100 - done.``

      ``Total tiles to process: 1``

      ``Completed 100% (1/1) - tiles/sec: 0.38 - time left: 00:00:00 [CPU: 15 Mem: 554 MB PF: 0]``

      ``Processed 1 tiles``

      ``Total time to process: 00:00:03``

      ``Average tiles per second: 0.38``

      ``Fusion Notice: OR-ing mask with new mask.``

      ``Fusion Notice: Saving mask to glandsat_15m_oahu-100mask.tif.``

      ``Fusion Notice: Writing alpha file glandsat_15m_oahu-100mask.tif``

      ``real 0m31.757s``

      ``user 0m28.390s``

      ``sys 0m3.020s``

      The resulting mask file is approximately 400MB in filesize.
      Screenshots of the output mask and resulting Fusion image resource
      may be seen below.

      .. rubric:: View of the mask with a 100 pixel feather as seen in
         the GIMP photo editor:

      |Mask with 100 pixel feather in GIMP|

      .. rubric:: View of the Oahu, Hawaii, USA imagery in Fusion
         Preview after importing the custom mask with the image
         resource:

      |Custom|

      The custom mask file may now be imported into Fusion Pro with the
      source imagery by enabling the ``havemask`` masking mode in the
      Fusion Pro Resource Editor or by specifying the
      ``gemodifyimageryresource --havemask`` option on the command line.

      Please see :ref:`Appendix A <Importing_Custom_Masks_Imagery_Terrain_GEE_Fusion>` for further
      information about enabling the ``havemask`` mask mode for an image
      resource.

      .. _Island_Masks_Into_Water:
      .. rubric:: Example B: Create a custom edge-matched mask for an
         island that masks into the water

      This example uses the same source imagery as :ref:`Example
      A <Island_Masks_Into_Land>` but a negative pixel value is provided for
      the feather value to expand the mask feather away from the
      shoreline outward into the water.

      The **command template** for this example is:

      ``gepolymaskgen --base_image imagery.khvr --feather -100 --or_mask world_coastlines_4326.shp --output_mask imagery-mask.tif``

      Larger or smaller negative feather values may be specified with
      the ``gepolymaskgen``\ command to expand farther away from the
      coastline mask or closer to the coastline mask as desired.

      Example output for creating the mask and screenshots are included
      below:

      ``jcain@machine123:/gevol-local/src/gepolymaskgen-howto$ time gepolymaskgen --base_image glandsat_15m_oahu.khvr --feather -100 --or_mask world_coastlines_4326.shp --output_mask glandsat_15m_oahu-minus100mask.tif``

      ``Fusion Notice: Base image: glandsat_15m_oahu.khvr``

      ``Fusion Notice: glandsat_15m_oahu.khvr width: 10240 height: 10240``

      ``Fusion Notice: north: 2.179688e+01 south: 2.091797e+01 east: -1.575879e+02 west: -1.584668e+02``

      ``Fusion Notice: File type: KHM/Keyhole Mosaic``

      ``Fusion Notice: Projection : 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]'``

      ``Fusion Notice: Feather -100``

      ``Fusion Notice: OR mask: world_coastlines_4326.shp``

      ``Fusion Notice: Output mask: glandsat_15m_oahu-minus100mask.tif``

      ``Fusion Notice: Setting base image glandsat_15m_oahu.khvr.``

      ``Fusion Notice: Setting feather -100.``

      ``Fusion Notice: Writing alpha file glandsat_15m_oahu-minus100mask.tif``

      ``Fusion Notice: Executing: gdal_rasterize -b 1 -burn 255 -l world_coastlines_4326 world_coastlines_4326.shp glandsat_15m_oahu-minus100mask.tif``

      ``0...10...20...30...40...50...60...70...80...90...100 - done.``

      ``Total tiles to process: 1``

      ``Completed 100% (1/1) - tiles/sec: 0.38 - time left: 00:00:00 [CPU: 16 Mem: 554 MB PF: 0]``

      ``Processed 1 tiles``

      ``Total time to process: 00:00:03``

      ``Average tiles per second: 0.38``

      ``Fusion Notice: OR-ing mask with new mask.``

      ``Fusion Notice: Saving mask to glandsat_15m_oahu-minus100mask.tif.``

      ``Fusion Notice: Writing alpha file glandsat_15m_oahu-minus100mask.tif``

      ``real 0m31.621s``

      ``user 0m28.510s``

      ``sys 0m3.100s``

      The resulting mask file is approximately 400MB in filesize.
      Screenshots of the output mask and resulting Fusion image resource
      may be seen below.

      .. rubric:: View of the mask file with a -100 pixel feather as
         seen in the GIMP photo editor:

      |Mask file of Oahu Hawaii in GIMP|

      .. rubric:: View of the Oahu, Hawaii, USA imagery in Fusion
         Preview after importing the custom mask with the image
         resource:

      |Oahu Hawaii in Fusion Preview|

      The custom mask file may now be imported into Fusion Pro with the
      source imagery by enabling the ``havemask`` masking mode in the
      Fusion Pro Resource Editor or by specifying the
      ``gemodifyimageryresource --havemask`` option on the command line.

      Please see :ref:`Appendix A <Importing_Custom_Masks_Imagery_Terrain_GEE_Fusion>` for further
      information about enabling the ``havemask`` mask mode for an image
      resource.

      .. _Masks_Coastline_Shared_Edges:
      .. rubric:: Case 3: Create custom masks with coastlines and shared
         edges with other imagery resources

      Creating custom masks for imagery resources bordering coastlines
      is a little more challenging since a set of vector polygons are
      needed to mask the desired imagery to the coastline, and it is
      necessary to determine what feather values to apply to the
      coastline and the external edges of the mask. We will first see the
      imagery we will be working with in this example.

      .. rubric:: View from the Fusion Preview GUI with imagery for
         California, USA along the coastline:

      |Fusiin Preview GUI in California|

      Forty-two source files of 15-meter imagery have been grouped into
      one virtual raster to build a new imagery resource. The source
      images along the interior of California fully contain usable
      imagery and do not include fill data; however, imagery along the
      Pacific Ocean includes water. The goal will be to mask the water
      from view while displaying imagery for the land. The workflow will
      be as follows:

      #. Create the overall mask for the image
      #. Apply a set of coastal polygons to demarcate the coastline
      #. Feather the coastline and apply the feather to the mask border
         as well
      #. Write out the mask file

      In this case, we will create three different types of masks with
      coastline data - one where the coastlines and edges have the same
      feathering, one where the coastlines and edges have different
      feathering values, and one where the coastline is feathered but
      the edges are not feathered.

      .. _Coastline_External_Edges_Same_Values:
      .. rubric:: Example A: Create an edge-matched custom mask that
         feathers coastlines and external edges with the same feather
         value

      This example will build a mask file that masks visible imagery to
      a specified coastline polygon - described by a source vector file
      in ``ESRI Shapefile format`` - and hides all ocean imagery from
      view. The source data are comprised of 42 images in a rectangle
      with the northernmost and easternmost edges being a border for
      another image resource. A consistent feather value (300 pixels)
      will be applied to both the coastlines and the external edges of
      the imagery with ``gepolymaskgen``.

      The **command template** to build this type of mask is:

      ``gepolymaskgen --base_image imagery.khvr --invert --feather -300 --feather_border 1 --and_neg_mask world_coastlines_4326.shp --invert --output_mask imagery-mask.tif``

      Here is an example output to build this type of mask for the
      15-meter resolution California imagery:

      ``jcain@machine123:/gevol-local/src/gepolymaskgen-howto$ time /opt/google/bin/gepolymaskgen --base_image glandsat_15m_california_bay_area.khvr --invert --feather -300 --feather_border 1 --and_neg_mask world_coastlines_4326.shp --invert --output_mask glandsat_15m_california_bay_area-coastline-exampleA.tif``

      ``Fusion Notice: Base image: glandsat_15m_california_bay_area.khvr``

      ``Fusion Notice: glandsat_15m_california_bay_area.khvr width: 35840 height: 30720``

      ``Fusion Notice: north: 3.849609e+01 south: 3.585938e+01 east: -1.211133e+02 west: -1.241895e+02``

      ``Fusion Notice: File type: KHM/Keyhole Mosaic``

      ``Fusion Notice: Projection : 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]'``

      ``Fusion Notice: Invert``

      ``Fusion Notice: Feather -300``

      ``Fusion Notice: Feather border 1``

      ``Fusion Notice: AND mask: world_coastlines_4326.shp``

      ``Fusion Notice: Invert``

      ``Fusion Notice: Output mask: glandsat_15m_california_bay_area-coastline-exampleA.tif``

      ``Fusion Notice: Setting base image glandsat_15m_california_bay_area.khvr.``

      ``Fusion Notice: Inverting current mask.``

      ``Fusion Notice: Setting feather -300.``

      ``Fusion Notice: Feather border is on.``

      ``Fusion Notice: Writing alpha file glandsat_15m_california_bay_area-coastline-exampleA.tif``

      ``Fusion Notice: Executing: gdal_rasterize -b 1 -burn 255 -l world_coastlines_4326 world_coastlines_4326.shp glandsat_15m_california_bay_area-coastline-exampleA.tif``

      ``0...10...20...30...40...50...60...70...80...90...100 - done.``

      ``Total tiles to process: 1``

      ``Completed 100% (1/1) - tiles/sec: 0.04 - time left: 00:00:00 [CPU: 19 Mem: 3844 MB PF: 0]``

      ``Processed 1 tiles``

      ``Total time to process: 00:00:28``

      ``Average tiles per second: 0.04``

      ``Fusion Notice: AND-ing mask with new mask.``

      ``Fusion Notice: Inverting current mask.``

      ``Fusion Notice: Saving mask to glandsat_15m_california_bay_area-coastline-exampleA.tif.``

      ``Fusion Notice: Writing alpha file glandsat_15m_california_bay_area-coastline-exampleA.tif``

      ``real 3m55.820s``

      ``user 3m39.810s``

      ``sys 0m15.650s``

      The resulting mask file is approximately 1GB in filesize.
      Screenshot of the mask from the GIMP photo editing tool and the
      resulting image resource after the mask is applied are available
      below.

      .. rubric:: View of the mask file built in Example A as seen in
         the GIMP photo editing tool:

      |Example A mask file in GIMP|

      .. rubric:: View of the imagery resource within the Fusion Preview
         window after the custom mask is imported:

      |Finished image after custom mask import|

      The custom mask file may now be imported into Fusion Pro with the
      source imagery by enabling the ``havemask`` masking mode in the
      Fusion Pro Resource Editor or by specifying the
      ``gemodifyimageryresource --havemask`` option on the command line.

      Please see :ref:`Appendix A <Importing_Custom_Masks_Imagery_Terrain_GEE_Fusion>` for further
      information about enabling the havemask mask mode for an image
      resource.

      .. _Feathered_Coastlines_External_Edges:
      .. rubric:: Example B: Create an edge-matched custom mask with
         feathered coastlines and feathered external edges

      This example will build a mask file that masks visible imagery to
      a specified coastline polygon - described by a source vector file
      in ``ESRI Shapefile`` format - and hides all ocean imagery from
      view. The source data are comprised of 42 images in a rectangle
      with the northernmost and easternmost edges being a border for
      another image resource. A feather value of -300 pixels will be
      applied to the coastlines while a -100 pixel feather will be
      applied to the external imagery edges with ``gepolymaskgen``. This
      use case is more complex in that three separate steps are needed
      to create twp separate masks - one which includes the feather
      border for the overall image, one for the coastlines - and then
      one operation to merge the mask files together.

      The **command templates** are as follows:

      #. **Create a 'picture frame' mask for the overall image:**

         ``gepolymaskgen --feather -100 --feather_border 1 --base_image source_image.tif --output_mask borderfeather-mask.tif``

      #. **Create a coastline mask:**

         ``gepolymaskgen --base_image source_image.tif --feather -300 --or_mask world_coastlines_4326.shp --output coastline-mask.tif``

      #. **Merge the two masks together into the final mask:**

         ``gepolymaskgen --base_mask coastline-mask.tif --and_neg_mask borderfeather-mask.tif --output_mask source_image-mask.tif``

      Screen shots of each mask file generated by the three steps are
      included below as a reference.

      .. rubric:: Picture frame border mask:

      |picture frame border mask|

      .. rubric:: Coastline mask:

      |Example A mask file in GIMP|

      .. rubric:: Finished, merged mask of coastline and border feather:

      |finished mask of coastline and border feather|

      Console output for building these masks are included below for
      reference along with the time to build and output file sizes for
      each of the three masks.

      #. **Create a 'picture frame' mask for the overall image:**

         ``jcain@machine123:/gevol-local/src/gepolymaskgen-howto$ time gepolymaskgen --feather -100 --feather_border 1 --base_image glandsat_15m_california_bay_area.khvr --output_mask california_borderfeather-mask.tif``

         ``Fusion Notice: Feather -100``

         ``Fusion Notice: Feather border 1``

         ``Fusion Notice: Base image: glandsat_15m_california_bay_area.khvr``

         ``Fusion Notice: glandsat_15m_california_bay_area.khvr width: 35840 height: 30720``

         ``Fusion Notice: north: 3.849609e+01 south: 3.585938e+01 east: -1.211133e+02 west: -1.241895e+02``

         ``Fusion Notice: File type: KHM/Keyhole Mosaic``

         ``Fusion Notice: Projection : 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]'``

         ``Fusion Notice: Output mask: california_borderfeather-mask.tif``

         ``Fusion Notice: Setting feather -100.``

         ``Fusion Notice: Feather border is on.``

         ``Fusion Notice: Setting base image glandsat_15m_california_bay_area.khvr.``

         ``Total tiles to process: 1``

         ``Completed 100% (1/1) - tiles/sec: 0.04 - time left: 00:00:00 [CPU: 98 Mem: 2294 MB PF: 0]``

         ``Processed 1 tiles``

         ``Total time to process: 00:00:27``

         ``Average tiles per second: 0.04``

         ``Fusion Notice: Saving mask to california_borderfeather-mask.tif.``

         ``Fusion Notice: Writing alpha file california_borderfeather-mask.tif``

         ``real 0m40.672s``

         ``user 0m36.000s``

         ``sys 0m4.300s``

         The resulting mask file is approximately 1 GB in file size.

      #. **Create a coastline mask:**

         ``jcain@machine123:/gevol-local/src/gepolymaskgen-howto$ time gepolymaskgen --base_image glandsat_15m_california_bay_area.khvr --feather -300 --or_mask world_coastlines_4326.shp --output california_coastline-mask.tif``

         ``Fusion Notice: Base image: glandsat_15m_california_bay_area.khvr``

         ``Fusion Notice: glandsat_15m_california_bay_area.khvr width: 35840 height: 30720``

         ``Fusion Notice: north: 3.849609e+01 south: 3.585938e+01 east: -1.211133e+02 west: -1.241895e+02``

         ``Fusion Notice: File type: KHM/Keyhole Mosaic``

         ``Fusion Notice: Projection : 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]'``

         ``Fusion Notice: Feather -300``

         ``Fusion Notice: OR mask: world_coastlines_4326.shp``

         ``Fusion Notice: Output mask: california_coastline-mask.tif``

         ``Fusion Notice: Setting base image glandsat_15m_california_bay_area.khvr.``

         ``Fusion Notice: Setting feather -300.``

         ``Fusion Notice: Writing alpha file california_coastline-mask.tif``

         ``Fusion Notice: Executing: gdal_rasterize -b 1 -burn 255 -l world_coastlines_4326 world_coastlines_4326.shp california_coastline-mask.tif``

         ``0...10...20...30...40...50...60...70...80...90...100 - done.``

         ``Total tiles to process: 1``

         ``Completed 100% (1/1) - tiles/sec: 0.04 - time left: 00:00:00 [CPU: 19 Mem: 3844 MB PF: 0]``

         ``Processed 1 tiles``

         ``Total time to process: 00:00:28``

         ``Average tiles per second: 0.04``

         ``Fusion Notice: OR-ing mask with new mask.``

         ``Fusion Notice: Saving mask to california_coastline-mask.tif.``

         ``Fusion Notice: Writing alpha file california_coastline-mask.tif``

         ``real 3m56.730s``

         ``user 3m41.010s``

         ``sys 0m15.340s``

         The resulting mask file is approximately 1 GB in file size.

      #. **Merge the two masks together into the final mask:**

         ``jcain@machine123:/gevol-local/src/gepolymaskgen-howto$ time gepolymaskgen --base_mask california_coastline-mask.tif --and_neg_mask california_borderfeather-mask.tif --output_mask glandsat_15m_california_bay_area-mask.tif``

         ``Fusion Notice: Base mask: california_coastline-mask.tif``

         ``Fusion Notice: california_coastline-mask.tif width: 35840 height: 30720``

         ``Fusion Notice: north: 3.849609e+01 south: 3.585938e+01 east: -1.211133e+02 west: -1.241895e+02``

         ``Fusion Notice: File type: GTiff/GeoTIFF``

         ``Fusion Notice: Projection : 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]'``

         ``Fusion Notice: AND mask: california_borderfeather-mask.tif``

         ``Fusion Notice: Output mask: glandsat_15m_california_bay_area-mask.tif``

         ``Fusion Notice: Setting base mask california_coastline-mask.tif.``

         ``Fusion Notice: Writing alpha file glandsat_15m_california_bay_area-mask.tif``

         ``Fusion Notice: AND-ing mask with new mask.``

         ``Fusion Notice: Saving mask to glandsat_15m_california_bay_area-mask.tif.``

         ``Fusion Notice: Writing alpha file glandsat_15m_california_bay_area-mask.tif``

         ``real 0m23.029s``

         ``user 0m15.690s``

         ``sys 0m7.300s``

         The resulting mask file is approximately 1 GB in file size.

         .. rubric:: View of finished mask file feathering the
            coastlines and external edges of the image resource:

         |finished mask of coastline and border feather|

         .. rubric:: View of finished image resource after importing
            custom mask:

         |Finished image after custom mask import|

         The custom mask file may now be imported into Fusion Pro with
         the source imagery by enabling the ``havemask`` masking mode in
         the Fusion Pro Resource Editor or by specifying the
         ``gemodifyimageryresource --havemask`` option on the command
         line.

         Please see :ref:`Appendix A <Importing_Custom_Masks_Imagery_Terrain_GEE_Fusion>` for further
         information about enabling the ``havemask`` mask mode for an
         image resource.

      .. _Feathered_Internal_Coastline_No_Edge:
      .. rubric:: Example C: Feathered internal coastline and no-feather
         external edge

      This example will build a mask file that masks visible imagery to
      a specified coastline polygon - described by a source vector file
      in ``ESRI Shapefile`` format - and hides all ocean imagery from
      view. The source data are comprised of 42 images in a rectangle
      with the northernmost and easternmost edges being a border for
      another image resource. A feather value (300 pixels) will be
      applied to the coastlines while the external imagery edges will
      have a zero-feather edge.

      The **command template** for this mask is:

      ``gepolymaskgen --base_image source_imagery.tif --invert --feather -300 --feather_border 0 --and_neg_mask world_coastlines_4326.shp --invert --output_mask source_imagery-mask.tif``

      Console output for building this mask is included below for
      reference:

      ``jcain@machine123:/gevol-local/src/gepolymaskgen-howto$ time gepolymaskgen --base_image glandsat_15m_california_bay_area.khvr --invert --feather -300 --feather_border 0 --and_neg_mask world_coastlines_4326.shp --invert --output_mask glandsat_15m_california_bay_area-mask.tif``

      ``Fusion Notice: Base image: glandsat_15m_california_bay_area.khvr``

      ``Fusion Notice: glandsat_15m_california_bay_area.khvr width: 35840 height: 30720``

      ``Fusion Notice: north: 3.849609e+01 south: 3.585938e+01 east: -1.211133e+02 west: -1.241895e+02``

      ``Fusion Notice: File type: KHM/Keyhole Mosaic``

      ``Fusion Notice: Projection : 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]'``

      ``Fusion Notice: Invert``

      ``Fusion Notice: Feather -300``

      ``Fusion Notice: Feather border 0``

      ``Fusion Notice: AND mask: world_coastlines_4326.shp``

      ``Fusion Notice: Invert``

      ``Fusion Notice: Output mask: glandsat_15m_california_bay_area-mask.tif``

      ``Fusion Notice: Setting base image glandsat_15m_california_bay_area.khvr.``

      ``Fusion Notice: Inverting current mask.``

      ``Fusion Notice: Setting feather -300.``

      ``Fusion Notice: Feather border is off.``

      ``Fusion Notice: Writing alpha file glandsat_15m_california_bay_area-mask.tif``

      ``Fusion Notice: Executing: gdal_rasterize -b 1 -burn 255 -l world_coastlines_4326 world_coastlines_4326.shp glandsat_15m_california_bay_area-mask.tif``

      ``0...10...20...30...40...50...60...70...80...90...100 - done.``

      ``Total tiles to process: 1``

      ``Completed 100% (1/1) - tiles/sec: 0.04 - time left: 00:00:00 [CPU: 19 Mem: 3844 MB PF: 0]``

      ``Processed 1 tiles``

      ``Total time to process: 00:00:28``

      ``Average tiles per second: 0.04``

      ``Fusion Notice: AND-ing mask with new mask.``

      ``Fusion Notice: Inverting current mask.``

      ``Fusion Notice: Saving mask to glandsat_15m_california_bay_area-mask.tif.``

      ``Fusion Notice: Writing alpha file glandsat_15m_california_bay_area-mask.tif``

      ``real 3m55.201s``

      ``user 3m40.410s``

      ``sys 0m14.540s``

      The resulting mask will be approximately 1 GB in file size.

      .. rubric:: View of the finished mask within the GIMP photo
         editing tool:

      |finished mask in GIMP|

      .. rubric:: View of the imagery resource within the Fusion Preview
         window after importing the custom mask:

      |Fusion preview window with custom mark import|

      The custom mask file may now be imported into Fusion Pro with the
      source imagery by enabling the ``havemask`` masking mode in the
      Fusion Pro Resource Editor or by specifying the
      ``gemodifyimageryresource --havemask`` option on the command line.

      Please see :ref:`Appendix A <Importing_Custom_Masks_Imagery_Terrain_GEE_Fusion>` for further
      information about enabling the ``havemask`` mask mode for an image
      resource.

      .. _Masking_Out_Sections_Large_Image:
      .. rubric:: Case 4: Masking out sections within an image resource

      ``gepolymaskgen`` is capable of masking out sections within a
      source image in addition to masking external edges of the imagery.
      This is similar to the hole checking option with the ``gemaskgen``
      tool which can automatically scan an image resource to seek fill
      data within the image resource. The main difference is
      ``gepolymaskgen`` will only mask out user-specified sections of
      the imagery. This example case will build on the principles
      discussed in :ref:`Case 1 <Imagery_No_Fill_Pixels>` where a fixed feather
      value edge mask will be made for a mosaic with imagery to the
      edges, and additionally demonstrate removing (masking) internal
      portions of an image resource from view with a ``KML`` file
      created in Google Earth. Let's first see a screenshot of imagery
      used for this example.

      .. rubric:: View of image resource in Fusion Preview after import
         with the automask tool:
         :name: view-of-image-resource-in-fusion-preview-after-import-with-the-automask-tool

      |image in Fusion with automask|

      Boundaries for the imported source files (``khvr``) are overlaid
      on the image for reference.

      The workflow for this example is different from the others since
      we need a ``KML`` file to specify which area in the image to
      remove from view. The general workflow will be:

      #. Import the imagery into GEE Fusion Pro and build into an
         imagery project.
      #. Build and publish the imagery into a flyable 3D database.
      #. View the 3D database with Google Earth EC to QA the data.
      #. Draw an enclosed polygon in Google Earth EC that would mask the
         missing area of imagery from view.
      #. Build the custom mask with ``gepolymaskgen`` to correctly
         feather the imagery edges and mask the missing imagery.
      #. Import the custom mask with the image resource.

      Examples of what the imagery resource looks like as viewed in
      Google Earth EC are included below.

      .. rubric:: This image demonstrates how the image resource appears
         with the area of missing imagery:

      |Missing imagery in GEEC|

      .. rubric:: This image is a screenshot after a polygon was drawn
         over the entire area of missing imagery:

      |Polygon on mising imagery|

      The polygon area was set to 50% opacity in order to show the
      polygon fully covers the area of missing imagery with a little
      overlap into the usable imagery. This polygon will be stored in
      the **Places** panel of Google Earth EC and must be saved out from
      Google Earth as an independent ``KML`` file that can then be
      utilized with ``gepolymaskgen``.

      .. note::

         **Note:** Additional information about creating polygons within
         Google Earth is also freely available with the Google Earth
         Outreach tutorials, directly accessible at
         `http://earth.google.com/outreach/tutorial_annotate.html#addpolygons <http://earth.google.com/outreach/tutorial_annotate.html#addpolygons>`_.

         **Tip:** Each polygon correction should be saved out as a
         ``KML`` file directly (four polygons saved to four separate
         ``KML`` files) as these will be separate mask operations within
         ``gepolymaskgen``.

      .. _Feathered_Edge_Masking_Missing_Internal_Imagery_One_Step:
      .. rubric:: Example A: Creating an edge-matched mask with a
         feathered edge and masking missing internal imagery in one step

      This example will create the custom mask in one command sequence
      by first creating a feathered edge mask based on the source image
      (``--base_image``) and then applying a ``KML`` file to mask out
      the area of missing imagery.

      The **command template** to create the mask, in one step, is:

      ``gepolymaskgen --feather -100 --feather_border 1 --base_image source_imagery.khvr --invert --feather 50 --and_neg_mask missing-imagery-area.kml --output_mask source_imagery-mask.tif``

      Console output for creating the mask file in one step is as
      follows:

      ``jcain@machine123:/gevol-local/src/gepolymaskgen-howto$ time gepolymaskgen --feather -100 --feather_border 1 --base_image glandsat_15m_bhutan_missing_imagery.khvr --invert --feather 50 --and_neg_mask bhutan.kml --output_mask glandsat_15m_bhutan_missing_imagery-mask.tif``

      ``Fusion Notice: Feather -100``

      ``Fusion Notice: Feather border 1``

      ``Fusion Notice: Base image: glandsat_15m_bhutan_missing_imagery.khvr``

      ``Fusion Notice: glandsat_15m_bhutan_missing_imagery.khvr width: 30720 height: 30720``

      ``Fusion Notice: north: 2.882812e+01 south: 2.619141e+01 east: 9.114258e+01 west: 8.850586e+01``

      ``Fusion Notice: File type: KHM/Keyhole Mosaic``

      ``Fusion Notice: Projection : 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]'``

      ``Fusion Notice: Invert``

      ``Fusion Notice: Feather 50``

      ``Fusion Notice: AND mask: bhutan.kml``

      ``Fusion Notice: Output mask: glandsat_15m_bhutan_missing_imagery-mask.tif``

      ``Fusion Notice: Setting feather -100.``

      ``Fusion Notice: Feather border is on.``

      ``Fusion Notice: Setting base image glandsat_15m_bhutan_missing_imagery.khvr.``

      ``Total tiles to process: 1``

      ``Completed 100% (1/1) - tiles/sec: 0.04 - time left: 00:00:00 [CPU: 99 Mem: 1990 MB PF: 0]``

      ``Processed 1 tiles``

      ``Total time to process: 00:00:23``

      ``Average tiles per second: 0.04``

      ``Fusion Notice: Inverting current mask.``

      ``Fusion Notice: Setting feather 50.``

      ``Fusion Notice: Writing alpha file glandsat_15m_bhutan_missing_imagery-mask.tif``

      ``Fusion Notice: Executing: ogr2ogr -t_srs 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]' /tmp/p14999QFR8Mx/tmp.shp bhutan.kml``

      ``Warning 6: Normalized/laundered field name: 'Description' to 'Descriptio'``

      ``Fusion Notice: Executing: gdal_rasterize -b 1 -burn 255 -l tmp /tmp/p14999QFR8Mx/tmp.shp glandsat_15m_bhutan_missing_imagery-mask.tif``

      ``0...10...20...30...40...50...60...70...80...90...100 - done.``

      ``Total tiles to process: 1``

      ``Completed 100% (1/1) - tiles/sec: 0.04 - time left: 00:00:00 [CPU: 93 Mem: 3262 MB PF: 0]``

      ``Processed 1 tiles``

      ``Total time to process: 00:00:23``

      ``Average tiles per second: 0.04``

      ``Fusion Notice: AND-ing mask with new mask.``

      ``Fusion Notice: Saving mask to glandsat_15m_bhutan_missing_imagery-mask.tif.``

      ``Fusion Notice: Writing alpha file glandsat_15m_bhutan_missing_imagery-mask.tif``

      ``real 1m24.041s``

      ``user 1m11.650s``

      ``sys 0m11.990s``

      The resulting mask file will be approximately 900 MB in file size.
      Screenshots of the finished mask and the resulting image resource
      are included below.

      .. rubric:: Custom mask which masks missing interior imagery with
         feathered edge as viewed in the GIMP photo editing tool:

      |Custom mask with missing imagery in GIMP|

      .. rubric:: Resulting image resource built by Fusion after the
         custom mask is imported. Lower resolution imagery from the
         resource under the 15-meter imagery will be visible from the
         internal area masked from view:

      |Image in Fusion after custom mask import|

      The custom mask file may now be imported into Fusion Pro with the
      source imagery by enabling the ``havemask`` masking mode in the
      Fusion Pro Resource Editor or by specifying the
      ``gemodifyimageryresource --havemask`` option on the command line.

      Please see :ref:`Appendix A <Importing_Custom_Masks_Imagery_Terrain_GEE_Fusion>` for further
      information about enabling the ``havemask`` mask mode for an image
      resource.

      .. note::

         **Note:** This mask file could also be created in two steps as
         well - the first step to create the base mask file (**picture
         frame**) that provides a feathered edge for the overall image,
         and the second step to apply the internal mask with the
         specified ``KML`` file. Multiple areas may be removed from the
         internal portion of the image mask as separate operations.

      .. _Feathered_Edge_Masking_Missing_Internal_Imagery_Two_Step:
      .. rubric:: Example B: Creating an edge-matched mask with a
         feathered edge and masking missing internal imagery in two
         steps

      This example will create the custom mask in two command sequences:
      in the first step a feathered edge mask based on the source
      image (``--base_image``) is built; and in the second step, a
      ``KML`` file to mask out the area of missing imagery is applied to
      the mask built in the first step.

      The **command templates** to create the mask are:

      #. **Create the edge mask (picture frame):**

         ``gepolymaskgen --feather -100 --feather_border 1 --base_image source_imagery.khvr --invert --output_mask source_imagery-basemask.tif``

      #. **Mask the area of missing imagery from the mask built in the
         previous step:**

         ``gepolymaskgen --base_mask source_imagery-basemask.tif --feather 50 --and_neg_mask missing-imagery-area.kml --output_mask source_imagery-mask.tif``

      Console output for creating the mask file in one step is as
      follows:

      #. **Create the edge mask (picture frame):**

         ``jcain@machine123:/gevol-local/src/gepolymaskgen-howto$ time gepolymaskgen --feather -100 --feather_border 1 --base_image glandsat_15m_bhutan_missing_imagery.khvr --invert --output_mask glandsat_15m_bhutan_missing_imagery-basemask.tif``

         ``Fusion Notice: Feather -100``

         ``Fusion Notice: Feather border 1``

         ``Fusion Notice: Base image: glandsat_15m_bhutan_missing_imagery.khvr``

         ``Fusion Notice: glandsat_15m_bhutan_missing_imagery.khvr width: 30720 height: 30720``

         ``Fusion Notice: north: 2.882812e+01 south: 2.619141e+01 east: 9.114258e+01 west: 8.850586e+01``

         ``Fusion Notice: File type: KHM/Keyhole Mosaic``

         ``Fusion Notice: Projection : 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]'``

         ``Fusion Notice: Invert``

         ``Fusion Notice: Output mask: glandsat_15m_bhutan_missing_imagery-basemask.tif``

         ``Fusion Notice: Setting feather -100.``

         ``Fusion Notice: Feather border is on.``

         ``Fusion Notice: Setting base image glandsat_15m_bhutan_missing_imagery.khvr.``

         ``Total tiles to process: 1``

         ``Completed 100% (1/1) - tiles/sec: 0.04 - time left: 00:00:00 [CPU: 97 Mem: 1990 MB PF: 0]``

         ``Processed 1 tiles``

         ``Total time to process: 00:00:23``

         ``Average tiles per second: 0.04``

         ``Fusion Notice: Inverting current mask.``

         ``Fusion Notice: Saving mask to glandsat_15m_bhutan_missing_imagery-basemask.tif.``

         ``Fusion Notice: Writing alpha file glandsat_15m_bhutan_missing_imagery-basemask.tif``

         ``real 0m36.297s``

         ``user 0m32.370s``

         ``sys 0m3.620s``

         The resulting mask will be approximately 900 MB in filesize.

         .. _gepolymaskgen_Viewed_GIMP:
         .. rubric:: Edge mask created with gepolymaskgen as viewed in
            the GIMP photo editing tool:

         |gepolymaskgen Edge mask in GIMP|

      #. **Mask the area of missing imagery from the mask built in the
         previous step:**

         ``jcain@machine123:/gevol-local/src/gepolymaskgen-howto$ time gepolymaskgen --base_mask glandsat_15m_bhutan_missing_imagery-basemask.tif --feather 50 --and_neg_mask bhutan.kml --output_mask glandsat_15m_bhutan_missing_imagery-mask.tif``

         ``Fusion Notice: Base mask: glandsat_15m_bhutan_missing_imagery-basemask.tif``

         ``Fusion Notice: glandsat_15m_bhutan_missing_imagery-basemask.tif width: 30720 height: 30720``

         ``Fusion Notice: north: 2.882812e+01 south: 2.619141e+01 east: 9.114258e+01 west: 8.850586e+01``

         ``Fusion Notice: File type: GTiff/GeoTIFF``

         ``Fusion Notice: Projection : 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]'``

         ``Fusion Notice: Feather 50``

         ``Fusion Notice: AND mask: bhutan.kml``

         ``Fusion Notice: Output mask: glandsat_15m_bhutan_missing_imagery-mask.tif``

         ``Fusion Notice: Setting base mask glandsat_15m_bhutan_missing_imagery-basemask.tif.``

         ``Fusion Notice: Setting feather 50.``

         ``Fusion Notice: Writing alpha file glandsat_15m_bhutan_missing_imagery-mask.tif``

         ``Fusion Notice: Executing: ogr2ogr -t_srs 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]' /tmp/p15693nKOdrD/tmp.shp bhutan.kml``

         ``Warning 6: Normalized/laundered field name: 'Description' to 'Descriptio'``

         ``Fusion Notice: Executing: gdal_rasterize -b 1 -burn 255 -l tmp /tmp/p15693nKOdrD/tmp.shp glandsat_15m_bhutan_missing_imagery-mask.tif``

         ``0...10...20...30...40...50...60...70...80...90...100 - done.``

         ``Total tiles to process: 1``

         ``Completed 100% (1/1) - tiles/sec: 0.04 - time left: 00:00:00 [CPU: 90 Mem: 3228 MB PF: 0]``

         ``Processed 1 tiles``

         ``Total time to process: 00:00:23``

         ``Average tiles per second: 0.04``

         ``Fusion Notice: AND-ing mask with new mask.``

         ``Fusion Notice: Saving mask to glandsat_15m_bhutan_missing_imagery-mask.tif.``

         ``Fusion Notice: Writing alpha file glandsat_15m_bhutan_missing_imagery-mask.tif``

         ``real 0m56.214s``

         ``user 0m44.330s``

         ``sys 0m11.890s``

         The resulting mask file will be approximately 900 MB in
         filesize.

         .. rubric:: Merged mask built with gepolymaskgen with feathered
            edge and internal image masking for area of missing imagery
            as viewed in the GIMP photo editing tool:

         |gepolymaskgen merged mask in GIMP|

         The custom mask file may now be imported into Fusion Pro with
         the source imagery by enabling the ``havemask`` masking mode in
         the Fusion Pro Resource Editor or by specifying the
         ``gemodifyimageryresource --havemask`` option on the command
         line.

         Please see :ref:`Appendix A <Importing_Custom_Masks_Imagery_Terrain_GEE_Fusion>` for further
         information about enabling the ``havemask`` mask mode for an
         image resource.

      .. _Custom_Masks_gemaskgen_gepolymaskgen:
      .. rubric:: Case 5: Building custom masks with both gemaskgen and
         gepolymaskgen

      There are special cases where the capabilities of both
      ``gemaskgen`` and ``gepolymaskgen`` are needed to build a custom
      mask file for an image resource. The SFBayAreaLansat imagery from
      the Google Earth Enterprise Fusion Pro Tutorial is a good example
      (screenshot below).

      .. rubric:: Screenshot of the usgsLanSat.tif source file imported
         into Fusion Pro viewed with no mask. Note the areas of fill
         data surrounding the imagery:

      |usgsLanSat.tif in Fusion pro with no mask|

      .. rubric:: Screenshot of the usgsLanSat.tif imagery after being
         imported into Fusion Pro with a mask automatically computed:

      |usgsLanSat.tif in Fusion pro with a mask|

      .. rubric:: Screenshot of the imported SFBayAreaLanSat image
         resource in Fusion after the custom mask is created:

      |SFBayAreaLanSat image in fusion with custom mask|

      Here, the Fusion Pro automask function is needed to build a mask
      for the source imagery to mask all Fill Data; however, the imagery
      also includes imagery for the water which should be, ideally,
      masked to the coastline. Both ``gemaskgen`` and ``gepolymaskgen``
      will be needed to accomplish this type of masking to
      build a mask hiding fill data within the image and then creating a
      coastline mask. This example is a special case since the source
      imagery must be imported into Fusion format first, then the custom
      mask will be generated from the output of the imagery resource
      build process. This example will also utilize information found in
      Appendixes :ref:`B <Locating_Mask_Files_Format_Data_Asset_Root>`, :ref:`C <Determining_Source_File_Raster_Size_geinfo>` and
      :ref:`D <Building_High_Resolution_Mask_Files_gemaskgen>` for locating masks built with
      ``gemaskgen``.

      The workflow to accomplish this custom mask will be:

      #. Import the source imagery as a Fusion Pro image resource
      #. Use the mask file built during the image resource import as the
         base mask for ``gepolymaskgen``
      #. Mask the imagery to the coastline and write out the new mask
      #. Enable the ``havemask`` mask mode for the image resource to
         import the custom mask

      The **command templates** for building this custom mask will be:

      #. **Locate the mask computed during the image resource build:**

         | ``gequery --outfiles Resources/Imagery/YourImageResource.kiasset/maskgen.kia``
         | ``/gevol/assets/Resources/Imagery/YourImageResource.kiasset/maskgen.kia/ver001/mask.tif``

      #. **Create an inverted version of the mask:**

         ``/gevol/assets/Resources/Imagery/YourImageResource.kiasset/maskgen.kia/ver001/mask.tif --invert --output_mask /gevol/src/path/to/source/imagery-basemaskinverted.tif``

      #. **Create a coastline mask using the mask as a base image:**

         ``gepolymaskgen --base_image``

         ``/gevol/src/path/to/source/imagery-basemaskinverted.tif --invert --feather 100 --and_neg_mask /gevol/src/coastlines.shp --output_mask /gevol/src/path/to/source/imagery-coastlinesinverted.tif``

      #. **Merge the two mask files to the final custom mask:**

         ``gepolymaskgen --base_mask /gevol/src/path/to/source/imagery-basemaskinverted.tif --invert --and_neg_mask /gevol/src/path/to/source/imagery-coastlinesinverted.tif --output_mask /gevol/src/path/to/source/imagery-mask.tif``

         The resulting ``imagery-mask.tif`` custom mask may then be
         imported with the source imagery and applied to the image
         resource in Google Earth Enterprise Fusion Pro.

      An example workflow is included below which constructs a custom
      mask - masking both fill data automatically with ``gemaskgen`` and
      the coastlines with ``gepolymaskgen`` - for the SFBayAreaLanSat
      imagery resource built during the Google Earth Enterprise Fusion
      Tutorial.

      #. **Locate the computed mask file built when SFBayAreaLanSat
         built by gemaskgen**

         ``jcain@machine123:/gevol-local/gepolymaskgen$ gequery --infiles Resources/Imagery/SFBayAreaLanSat.kiasset/maskproduct.kia``

         ``/gevol-local/gepolymaskgen/Resources/Imagery/SFBayAreaLanSat.kiasset/product.kia/ver001/raster.kip``

         ``/gevol-local/gepolymaskgen/Resources/Imagery/SFBayAreaLanSat.kiasset/maskgen.kia/ver002/mask.tif``

      #. **Create a custom mask with gepolymaskgen using the gemaskgen base
      mask and mask to the coastlines (three steps)**
         a. Invert the mask file built during the Fusion Pro import:

         ``jcain@machine123:/gevol-local/gepolymaskgen$ sudo``\ **``/opt/google/bin/gepolymaskgen --base_mask /gevol-local/gepolymaskgen/Resources/Imagery/SFBayAreaLanSat.kiasset/maskgen.kia/ver002/mask.tif --invert --output_mask /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-invertbasemask.tif``**

         ``Fusion Notice: Base mask: /gevol-local/gepolymaskgen/Resources/Imagery/SFBayAreaLanSat.kiasset/maskgen.kia/ver002/mask.tif``

         ``Fusion Notice: /gevol-local/gepolymaskgen/Resources/Imagery/SFBayAreaLanSat.kiasset/maskgen.kia/ver002/mask.tif width: 8206 height: 5856``

         ``Fusion Notice: north: 3.846468e+01 south: 3.645418e+01 east: -1.207133e+02 west: -1.235306e+02``

         ``Fusion Notice: File type: GTiff/GeoTIFF``

         ``Fusion Notice: Projection : 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]'``

         ``Fusion Notice: Invert``

         ``Fusion Notice: Output mask: /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-invertbasemask.tif``

         ``Fusion Notice: Setting base mask /gevol-local/gepolymaskgen/Resources/Imagery/SFBayAreaLanSat.kiasset/maskgen.kia/ver002/mask.tif.``

         ``Fusion Notice: Inverting current mask.``

         ``Fusion Notice: Saving mask to /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-invertbasemask.tif.``

         ``Fusion Notice: Writing alpha file /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-invertbasemask.tif``

         b. Create a second mask file with the coastlines, inverted:

         ``jcain@machine123:/gevol-local/gepolymaskgen$ sudo``\ **``/opt/google/bin/gepolymaskgen --base_image /gevol-local/gepolymaskgen/Resources/Imagery/SFBayAreaLanSat.kiasset/maskgen.kia/ver002/mask.tif --invert --feather 50 --and_neg_mask /gevol-local/src/gepolymaskgen-howto/world_coastlines_4326.shp --output_mask /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-invertcoastmask.tif``**

         ``Fusion Notice: Base image: /gevol-local/gepolymaskgen/Resources/Imagery/SFBayAreaLanSat.kiasset/maskgen.kia/ver002/mask.tif``

         ``Fusion Notice: /gevol-local/gepolymaskgen/Resources/Imagery/SFBayAreaLanSat.kiasset/maskgen.kia/ver002/mask.tif width: 8206 height: 5856``

         ``Fusion Notice: north: 3.846468e+01 south: 3.645418e+01 east: -1.207133e+02 west: -1.235306e+02``

         ``Fusion Notice: File type: GTiff/GeoTIFF``

         ``Fusion Notice: Projection : 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]'``

         ``Fusion Notice: Invert``

         ``Fusion Notice: Feather -50``

         ``Fusion Notice: AND mask: /gevol-local/src/gepolymaskgen-howto/world_coastlines_4326.shp``

         ``Fusion Notice: Output mask: /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-invertcoastmask.tif``

         ``Fusion Notice: Setting base image /gevol-local/gepolymaskgen/Resources/Imagery/SFBayAreaLanSat.kiasset/maskgen.kia/ver002/mask.tif.``

         ``Fusion Notice: Inverting current mask.``

         ``Fusion Notice: Setting feather -50.``

         ``Fusion Notice: Writing alpha file /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-invertcoastmask.tif``

         ``Fusion Notice: Executing: gdal_rasterize -b 1 -burn 255 -l world_coastlines_4326 /gevol-local/src/gepolymaskgen-howto/world_coastlines_4326.shp /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-invertcoastmask.tif``

         ``0...10...20...30...40...50...60...70...80...90...100 - done.``

         ``Total tiles to process: 1``

         ``Completed 100% (1/1) - tiles/sec: 0.83 - time left: 00:00:00 [CPU: 7 Mem: 292 MB PF: 0]``

         ``Processed 1 tiles``

         ``Total time to process: 00:00:01``

         ``Average tiles per second: 0.83``

         ``Fusion Notice: AND-ing mask with new mask.``

         ``Fusion Notice: Saving mask to /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-invertcoastmask.tif.``

         ``Fusion Notice: Writing alpha file /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-invertcoastmask.tif``

         c. Construct the final mask by merging the two mask files:

         ``jcain@machine123:/gevol-local/gepolymaskgen$ sudo``\ **``/opt/google/bin/gepolymaskgen --base_mask /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-invertbasemask.tif --invert --and_neg_mask /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-invertcoastmask.tif --output_mask /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-mask.tif``**

         ``Fusion Notice: Base mask: /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-invertbasemask.tif``

         ``Fusion Notice: /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-invertbasemask.tif width: 8206 height: 5856``

         ``Fusion Notice: north: 3.846468e+01 south: 3.645418e+01 east: -1.207133e+02 west: -1.235306e+02``

         ``Fusion Notice: File type: GTiff/GeoTIFF``

         ``Fusion Notice: Projection : 'GEOGCS["WGS 84",DATUM["WGS_1984",SPHEROID["WGS 84",6378137,298.257223563,AUTHORITY["EPSG","7030"]],AUTHORITY["EPSG","6326"]],PRIMEM["Greenwich",0],UNIT["degree",0.0174532925199433],AUTHORITY["EPSG","4326"]]'``

         ``Fusion Notice: Invert``

         ``Fusion Notice: AND mask: /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-invertcoastmask.tif``

         ``Fusion Notice: Output mask: /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-mask.tif``

         ``Fusion Notice: Setting base mask /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-invertbasemask.tif.``

         ``Fusion Notice: Inverting current mask.``

         ``Fusion Notice: Writing alpha file /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-mask.tif``

         ``Fusion Notice: AND-ing mask with new mask.``

         ``Fusion Notice: Saving mask to /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-mask.tif.``

         ``Fusion Notice: Writing alpha file /opt/google/share/tutorials/fusion/Imagery/usgsLanSat-mask.tif``

      Screenshots of the mask files during the build process are
      included below for reference. Each mask file is approximately 50 MB
      in file size.

      .. rubric:: Mask computed by gemaskgen during SFBayAreaLanSat
         image resource import:

      |mask by gemaskgen during SFBayAreaLanSat import|

      .. rubric:: Step A: Inverted base mask:

      |Inverted base mask|

      .. rubric:: Step B: Inverted coastlines mask:

      |Inverted coastlines mask|

      .. rubric:: Step C: Merged, finished custom mask:

      |merged custom mask|

      The custom mask may now be imported into Google Earth Enterprise
      Fusion Pro with the image resource by enabling the ``havemask``
      mask mode.

      Please see :ref:`Appendix A <Importing_Custom_Masks_Imagery_Terrain_GEE_Fusion>` for further details
      about importing the new custom mask with an image resource.

      .. rubric:: A screenshot of the SFBayAreaLanSat image resource
         with the custom mask is viewable below:

      |SFBayAreaLanSat image with custom mask|

      This example workflow utilized the mask file automatically
      computed by Fusion Pro during the image resource import. By
      default, the mask files created by ``gemaskgen`` will typically be
      low resolution with a maximum of 16,000 pixels on any one side. It
      is possible to create a higher resolution mask file by manually
      operating the ``gemaskgen`` command on the command line.

      Please see :ref:`Appendix D <Building_High_Resolution_Mask_Files_gemaskgen>` for further details.

      .. _Importing_Custom_Masks_Imagery_Terrain_GEE_Fusion:
      .. rubric:: Appendix A: Importing custom masks with imagery and
         terrain resources in Google Earth Enterprise Fusion Pro

      Custom imagery mask files built by either ``gemaskgen``,
      ``gepolymaskgen``, or another third-party application will only be
      imported automatically if the ``havemask`` mask option is selected
      for an image or terrain resource. Custom masks may be created
      before an image is imported into Fusion Pro or built after the
      image has already been imported as a resource. For either case,
      the ``havemask`` masking mode may be enabled either from the
      Fusion GUI Resource Editor or from the command line with the
      ``--havemask``\ option.

      Example procedures for enabling the ``havemask`` option by command
      line and the Fusion GUI are available below as reference. Further
      details about the Fusion GUI Resource Editor and the command line
      tools ``genewimageryresource`` and ``gemodifyimageryresource`` may
      be found in the "Google Earth Enterprise Fusion Reference Guide"
      **Defining Resources** section and the **Command Line Reference**
      section.

      Four examples cases are included below as a reference - two for
      enabling ``havemask`` mode within the Fusion GUI for new or
      existing image resources, and two for enabling ``havemask`` mode
      on the command line.

      .. _Enable_havemask_New_Image_Resource:
      .. rubric:: Example 1: Enable havemask mode in the Fusion GUI for
         a new image resource

      #. Move the custom mask file to the same folder as the source file
         for the image.
      #. | Rename the custom mask file to be the same file name as the
           source image file with a ``-mask.tif`` extension.

         For example: If the ``/gevol/src/imagery/example.tif`` is the
         source file, then the custom mask must be

         ``/gevol/src/imagery/example-mask.tif``

      #. Load the Fusion GUI Asset Manager:

         |Fusion GUI Asset Manager|

      #. Start a new image resource and specify the source file,
         provider, and acquisition date.
      #. Set the **Mask Type** to Have Mask from the **Mask Options** drop-down
         menu.

         |Mask Options drop down menu|

      #. Save the image resource, specifying the location and name for
         the new image resource.
      #. Build the image resource.
      #. Once complete, load the newly built Fusion image resource into
         the Preview window to view the results. Proceed building the
         image resource into an imagery project if the custom mask is
         satisfactory, or continue working on the custom mask and repeat
         the import process until satisfied with the custom mask.

      .. _Enable_havemask_Command_Line_New_Image_Resource:
      .. rubric:: Example 2: Enable havemask mode by command line for a
         new image resource

      #. Move the custom mask file to the same folder as the source file
         for the image.
      #. Rename the custom mask file to be the same file name as the
         source image file with a ``-mask.tif`` extension.

         For example if the:

         ``/gevol/src/imagery/example.tif`` is the source file, then the
         custom mask must be:

         ``/gevol/src/imagery/example-mask.tif``

      #. On the command line, enter:

         ``genewimageryresource --havemask --sourcedate '0000-00-00' --provider 'USGS' -o Resources/Imagery/Example-Imagery /gevol/src/imagery/example.tif``

         replacing the provider, sourcedate and resource name to suit
         the imagery being imported.

      #. Build the image resource by entering:

         ``gebuild Resources/Imagery/Example-Imagery``\ on the command
         line.

      #. Once the image resource build is complete, load the newly built
         Fusion image resource into the Preview window to view the
         results. Proceed building the image resource into an imagery
         project if the custom mask is satisfactory, or continue working
         on the custom mask and repeat the import process until
         satisfied with the custom mask.

      .. _Enable_havemask_Existing_Image_Resource:
      .. rubric:: Example 3: Enable havemask mode in the Fusion GUI for
         an existing image resource

      #. Move the custom mask file to the same folder as the source file
         for the image.
      #. Rename the custom mask file to be the same file name as the
         source image file with a ``-mask.tif`` extension.

         For example if the:

         ``/gevol/src/imagery/example.tif`` is the source file, then the
         custom mask must be:

         ``/gevol/src/imagery/example-mask.tif``

      #. Load the Fusion GUI Asset Manager:

         |Fusion GUI Asset Manager|

      #. Double-click the image resource to which the
         custom mask will be applied, or right-click the image.
         resource and select **Modify**
      #. When the Resource Editor loads, change the **Mask Type** to Have
         Mask from the **Mask Options** drop-down menu.

         |Mask Options drop down menu|

      #. Save the image resource.
      #. Build the image resource.
      #. Once the image resource build is complete, load the newly built
         Fusion image resource into the Preview window to view the
         results. Proceed building the image resource into an imagery
         project if the custom mask is satisfactory, or continue working
         on the custom mask and repeat the import process until
         satisfied with the custom mask.

      .. _Enable_havemask_Command_Line_Existing_Image_Resource:
      .. rubric:: Example 4: Enable havemask mode by command line for an
         existing image resource

      #. Move the custom mask file to the same folder as the source file
         for the image.
      #. Rename the custom mask file to be the same file name as the
         source image file with a ``-mask.tif`` extension.

         For example if the:

         ``/gevol/src/imagery/example.tif`` is the source file, then the
         custom mask must be:

         ``/gevol/src/imagery/example-mask.tif``

      #. On the command line, enter:

         ``gemodifyimageryresource --havemask --sourcedate '0000-00-00' --provider 'USGS' -o Resources/Imagery/Example-Imagery /gevol/src/imagery/example.tif``

         replacing the provider, sourcedate and resource name to suit
         the imagery being imported.

      #. Build the image resource by entering
         ``gebuild Resources/Imagery/Example-Imagery``\ on the command
         line.
      #. Once the image resource build is complete, load the newly built
         Fusion image resource into the Preview window to view the
         results. Proceed building the image resource into an imagery
         project if the custom mask is satisfactory, or continue working
         on the custom mask and repeat the import process until
         satisfied with the custom mask.

      .. _Locating_Mask_Files_Format_Data_Asset_Root:
      .. rubric:: Appendix B: Locating mask files and Fusion format data
         in an Asset Root

      Several files are created by GEE Fusion Pro when building an
      imagery or terrain resource, including the Fusion-format version
      of the imagery (``.kip`` extension) or terrain (``.ktp``
      extension), a computed mask file built by ``gemaskgen``, and the
      Fusion-format version of the computed mask (``.kmp`` extension).
      These files and folders may be located within the Asset Root with
      the help of the ``gequery`` command and the ``--outfiles`` and
      ``--infiles`` options.

      These files may be desired for custom masking operations such as
      computing a new, higher-resolution mask with ``gemaskgen`` - which
      is computed from a ``.kip`` or ``.ktp`` folder - or locating the
      mask automatically built with ``gemaskgen`` to add coastlines,
      such as described in the :ref:`Case 5 Example <Custom_Masks_gemaskgen_gepolymaskgen>`
      section. This section of the How-To guide will provide command
      templates for locating the Fusion-format versions of imagery and
      terrain within the GEE Fusion Asset Root, and locating a mask file
      built by ``gemaskgen`` during resource import.

      .. _Locate_Fusion_Format_Imagery_Mask_Files_Image_Resource:
      .. rubric:: Example 1: Locate the Fusion format imagery (.kip) and
         mask (.kmp) files of an image resource

      The ``gequery --outfiles`` command can be used to locate the
      Fusion-format versions of imported imagery or terrain data, and
      the Fusion-format version of the mask file as these are the
      **output** of the Fusion resource. Here is an example command to
      find the Fusion format imagery (``.kip``) and mask (``.kmp``)
      files from the SFBayAreaLanSat image resource built during the
      Fusion Pro Tutorial:

      ``jcain@machine123:/gevol-local/gepolymaskgen$ gequery --outfiles Resources/Imagery/SFBayAreaLanSat.kiasset``

      ``/gevol-local/gepolymaskgen/Resources/Imagery/SFBayAreaLanSat.kiasset/product.kia/ver001/raster.kip``

      ``/gevol-local/gepolymaskgen/Resources/Imagery/SFBayAreaLanSat.kiasset/maskproduct.kia/ver002/mask.kmp``

      The response from ``gequery --outfiles`` provides the full folder
      path where the ``.kip`` and ``.kmp`` folders are located that
      comprise the SFBayAreaLanSat image resource imagery and mask in
      Fusion format. The location of the ``.kip`` folder will be vital
      information to regenerate a mask with ``gemaskgen`` as noted in
      :ref:`Appendix C <Determining_Source_File_Raster_Size_geinfo>`, or if working with an imagery
      dataset that is larger than 65,000 pixels on a side as noted in
      :ref:`Appendix D <Building_High_Resolution_Mask_Files_gemaskgen>`. The version of the imagery
      ``.kip`` folder and mask ``.kmp`` folders will change over time as
      newer source imagery is imported for the image resource or
      changes are made to the automask. The ``gequery --outfiles``
      command will report the full paths that relate to the most current
      version of the image resource. Further information about the
      gequery command may be found in the ``gequery --help`` menu.

      .. _Locate_Mask_File_Built_Automask_Fusion_Build:
      .. rubric:: Example 2: Locate a mask.tif file automatically built
         by the automask feature of a Fusion resource build

      Finding the mask file automatically computed by ``gemaskgen``
      during a resource import is slightly different since it is the
      output of a different phase of the image resource build, but is
      needed to build the ``.kmp`` folder. The ``gequery --outfiles``
      options can help locate the mask file built by the Fusion automask
      tool ``gemaskgen``. Here is an example command to locate the full
      path of the mask file computed by Fusion for the SFBayAreaLanSat
      image resource built during the Fusion Pro Tutorial:

      ``jcain@machine123:/gevol-local/gepolymaskgen$ gequery --outfiles Resources/Imagery/SFBayAreaLanSat.kiasset/maskgen.kia``

      ``/gevol-local/gepolymaskgen/Resources/Imagery/SFBayAreaLanSat.kiasset/maskgen.kia/ver002/mask.tif``

      The response from ``gequery --outfiles`` provides the full path
      location to the mask file built by the ``gemaskgen`` tool when the
      automask masking mode is selected for a resource. This computed
      mask file is used to build the Fusion-format mask (``.kmp``) for a
      resource. It is possible to build complex mask files for image
      resources by combining output from the ``gemaskgen`` automask tool
      and the ``gepolymaskgen`` tool, as described in the `Case 5
      Example <Custom_Masks_gemaskgen_gepolymaskgen>`__ where the automatic fill data
      detection of ``gemaskgen`` can be combined with coastline masking
      capabilities of ``gepolymaskgen``.

      Please see the :ref:`Case 5 Example <Custom_Masks_gemaskgen_gepolymaskgen>` for further
      details.

      .. _Locate_Mask_File_Fusion_Format_File_Building_Mask_Product:
      .. rubric:: Example 3: Locate the mask.tif file and Fusion-format
         .kip file utilized for building the Fusion format .kmp (mask
         product)

      Two inputs are required by Fusion to convert a mask file from
      ``GeoTIFF``\ format into Fusion format for use with an image or
      terrain resource: the location of the ``mask.tif`` file and the
      location of the correct ``.kip`` folder. Examples
      :ref:`1 <Locate_Fusion_Format_Imagery_Mask_Files_Image_Resource>` and :ref:`2 <Locate_Mask_File_Built_Automask_Fusion_Build>` demonstrated
      how ``gequery --outfiles`` may be utilzed to determine the folder
      paths of the Fusion-format ``.kip`` and ``.kmp`` data and the
      location of the mask file computed by ``gemaskgen`` during the
      resource build.

      The locations of the ``.kip`` and ``mask.tif`` files read in by
      Fusion for generating the Fusion-format ``.kmp`` mask may be found
      with the ``gequery --infiles`` option. This is useful in
      situations where a higher-fidelity base mask file is needed for
      building a custom mask file, as described in the :ref:`Case 5
      Example <Custom_Masks_gemaskgen_gepolymaskgen>`. Here is the command to locate the
      full paths to the computed mask file (``gemaskgen``) and
      Fusion-format ``.kip`` folder for the SFBayAreaLanSat image
      resource built during the Fusion Pro Tutorial:

      ``jcain@machine123:/gevol-local/gepolymaskgen$ gequery --infiles Resources/Imagery/SFBayAreaLanSat.kiasset/maskproduct.kia``

      ``/gevol-local/gepolymaskgen/Resources/Imagery/SFBayAreaLanSat.kiasset/product.kia/ver001/raster.kip``

      ``/opt/google/share/tutorials/fusion/Imagery/usgsLanSat-mask.tif``

      A new base mask file may be built with the ``gemaskgen`` command
      which permits a larger number of pixels to be used for developing
      the mask file - as described in :ref:`Appendix D <Building_High_Resolution_Mask_Files_gemaskgen>`
      - which could then be used in conjunction with There :ref:`Case 5
      Example <Custom_Masks_gemaskgen_gepolymaskgen>`, or as a base mask for very large
      image resources as described in :ref:`Appendix F <Building_Custom_Masks_Large_Source_Imagery>`.

      .. _Determining_Source_File_Raster_Size_geinfo:
      .. rubric:: Appendix C: Determining source file raster size with
         geinfo

      Google Earth Enterprise Fusion Pro includes a tool called
      ``geinfo`` capable of reporting metadata about source imagery and
      terrain files, including:

      -  Overall raster dimensions
      -  Pixel resolution
      -  Geographic location of the data
      -  Native projection or geographic coordinate system
      -  Number of bands in the file
      -  Band format (ex: 8-bit, 16-bit)

      ``geinfo`` is able to read the same raster source formats that can
      be imported as Fusion image resources, including ``khvr`` (virtual
      raster) files for the raster dimensions of a mosaic.

      Mask files computed with the ``gepolymaskgen`` tool will be
      written out in ``GeoTIFF`` format and must be less than 2 GB in
      total file size. The ``geinfo`` tool can be used to determine the
      overall raster size of the input source file by entering
      ``geinfo source_imagery.tif`` onto the command line, where GEE
      Fusion Pro is installed, and then mulitplying the source file
      raster width (pixels) and height (pixels) values. The product may
      be used to estimate the file size that would be created by
      ``gepolymaskgen``, if the source file was specified as the
      ``gepolymaskgen --base_image``. Example output from ``geinfo`` is
      included below for the California 15-meter Landsat imagery that
      was used with the :ref:`Case 3 Example <Masks_Coastline_Shared_Edges>`. The
      raster dimensions for the mosaic are highlighted for quick
      reference.

      ``jcain@machine123:/gevol-local/src/gepolymaskgen-howto$ geinfo glandsat_15m_california_bay_area.khvr``

      ``File Type:   KHM/Keyhole Mosaic``

      ``Raster Size: 35840,30720``

      ``Extents:     (ns) 38.496093750000,35.859375000000``

      ``(ew) -121.113281250000,-124.189453125000``

      ``Pixel Size:  (xy) 0.000085830688,-0.000085830688``

      ``Keyhole Normalized {``

      ``Raster Size: 35840,30720``

      ``Extents:     (ns) 38.496093750000,35.859375000000``

      ``(ew) -121.113281250000,-124.189453125000``

      ``Pixel Size:  (xy) 0.000085830688,-0.000085830688``

      ``Top level:   22``

      ``}``

      ``Spatial Reference System:``

      ``GEOGCS["WGS 84",``

      ``DATUM["WGS_1984",``

      ``SPHEROID["WGS 84",6378137,298.257223563,``

      ``AUTHORITY["EPSG","7030"]],``

      ``AUTHORITY["EPSG","6326"]],``

      ``PRIMEM["Greenwich",0],``

      ``UNIT["degree",0.0174532925199433],``

      ``AUTHORITY["EPSG","4326"]]``

      ``Corner Coordinates:``

      ``Upper Left  (-124.1894531,  38.4960938) (124d11'22.03"W, 38d29'45.94"N)``

      ``Lower Left  (-124.1894531,  35.8593750) (124d11'22.03"W, 35d51'33.75"N)``

      ``Upper Right (-121.1132812,  38.4960938) (121d 6'47.81"W, 38d29'45.94"N)``

      ``Lower Right (-121.1132812,  35.8593750) (121d 6'47.81"W, 35d51'33.75"N)``

      ``Center      (-122.6513672,  37.1777344) (122d39'4.92"W, 37d10'39.84"N)``

      ``Band 1 Block=2048x200 Type=Byte, ColorInterp=Red``

      ``NoData Value=0``

      ``Band 2 Block=2048x200 Type=Byte, ColorInterp=Green``

      ``NoData Value=0``

      ``Band 3 Block=2048x200 Type=Byte, ColorInterp=Blue``

      ``NoData Value=0``

      ``Band 4 Block=2048x200 Type=Byte, ColorInterp=Alpha``

      Multiplying the raster dimensions together (``35840 x 30720``)
      results in 1,101,004,800 which means a 1 GB (approximate) mask file
      would be created if the ``khvr`` was specified as a
      ``gepolymaskgen --base_image``.

      .. _Maximum_Suggested_Raster_Dimensions_Source_Files_gepolymaskgen:
      .. rubric:: Maximum suggested raster dimensions for source files
         used as gepolymaskgen --base_image files

      Some suggested maximum raster dimensions are included as a rough
      guideline to help size and scope source files when creating custom
      masks. The source file should not be used as a base image for
      ``gepolymaskgen`` if the total raster size is larger than
      2,000,000,000 pixels. For this case, a lower-resolution image
      should be created as described in :ref:`Appendix
      D <Building_High_Resolution_Mask_Files_gemaskgen>`.

      .. _Square_Shaped_Rasters:
      .. rubric:: Square-shaped rasters

      Perfectly square source raster files should be less than 44,000
      pixels by 44,000 pixels for use as a base image or base mask
      with ``gepolymaskgen``. A substitute base image or mask file
      should be created for square-shaped source images that are larger
      than 44,000 pixels on both sides, as described in :ref:`Appendix
      D <Building_High_Resolution_Mask_Files_gemaskgen>`.

      .. _Rectangular_Sharped_Rasters:
      .. rubric:: Rectangular-shaped rasters

      The maximum suggested raster dimensions for rectangular images
      varies by the amount of the longest side. Some suggested
      dimensions are included below for reference.

      -  55,000 x 30,000
      -  60,000 x 35,000
      -  65,000 x 30,000
      -  70,000 x 27,000

      A substitute base image or mask file should be created if the
      source imagery is larger than these recommended dimensions, or if
      the product of the raster width and height is more than
      2,000,000,000 pixels. Instructions for creating a substitute base
      image, with ``gemaskgen``, may be found in :ref:`Appendix
      D <Building_High_Resolution_Mask_Files_gemaskgen>`.

      .. _Building_High_Resolution_Mask_Files_gemaskgen:
      .. rubric:: Appendix D: Building high resolution mask files with
         ``gemaskgen``

      The ``gemaskgen`` automask utility has several options to
      automatically compute a mask file from an imported Fusion imagery
      resource (``.kip``); however, by default ``gemaskgen`` limits the
      computed mask to be a maximum of 16,000 pixels on any one
      side, which can result in low-resolution masks for high-resolution
      image resources. Higher resolution masks may be created by
      manually invoking the ``gemaskgen`` tool and specifying a higher pixel
      value for the ``--maxsize`` option.

      ``gemaskgen`` requires access to the Fusion format version of the
      imagery resource to compute the mask file, which may be located
      either in the Fusion Asset Root or in a separate folder, depending
      on whether the imagery was processed by another system and copied to the
      Fusion system for use, or if a ``KRP.taskrule`` taskrule file
      redirects output from Fusion resource imports to another volume.
      The location of both the ``.kip`` folder Fusion-format imagery and
      ``mask.tif`` file may be found with the ``gequery --infiles``
      command as described in :ref:`Appendix B <Locating_Mask_Files_Format_Data_Asset_Root>`,
      :ref:`Example 3 <Locate_Mask_File_Fusion_Format_File_Building_Mask_Product>`.

      The exact settings used by ``gemaskgen`` when building a mask file
      for an image resource may be found from the ``gemaskgen`` log
      file, available in the Google Earth Enterprise Fusion Pro Asset
      Manager. To access the log file, load the Asset Manager and
      right-click on the desired image resource. Select  **Current
      Version Properties**,  then expand the ``CHILD.KRMP`` item
      until the ``Maskgen.kia&`` entry is visible.

      |maskgen version properties|

      Click the logfile icon to the right of the
      ``Maskgen.kia`` entry to open the logfile.

      |Maskgen Logfile diagram|

      The ``gemaskgen`` command executed by Fusion Pro during the image
      resource build is visible at the top of the log file on the line
      starting with ``COMMAND``. This command may be utilized as a
      template for building a higher resolution mask by also including
      the ``--maxsize`` option.

      An example ``gemaskgen`` use will be included below that will
      build a mask for the ``example-imagery.kip`` image resource with a
      maximum size of 55,000 pixels, feathered 100 pixels into the
      imagery, with fill data set to pixel value 0:

      ``jcain@machine123:/gevol-local/src/gepolymaskgen-howto$ time gemaskgen --mask --maxsize 55000 --feather 100 /path/to/example-imagery.kip /path/to/example-imagery-mask.tif``

      ``gemaskgen``\ will read the ``example-imagery.kip`` folder and
      compute a mask file that masks Fill Data pixels and builds a
      feathered edge of 100 pixels into the usable imagery. The actual
      output dimensions of the computed mask varies from case to case;
      however, ``gemaskgen`` will restrict the maximum length of either
      the height or width to 55,000 pixels. Additional information about
      recommended mask dimensions may be found in :ref:`Appendix
      C <Determining_Source_File_Raster_Size_geinfo>`. Once complete, the mask file computed by
      ``gemaskgen`` may be used as a base image for building a custom
      mask with ``gepolymaskgen`` and then imported with the image
      resource as described in :ref:`Appendix A <Importing_Custom_Masks_Imagery_Terrain_GEE_Fusion>`.

      Further information about available ``gemaskgen`` options may be
      found in the ``gemaskgen --help`` menu.

      .. _Using_Photo_Editing_App_Augment_Custom_App:
      .. rubric:: Appendix E: Using a Photo Editing application to
         augment a custom mask

      This is a special section for manually modifying a custom mask for
      an imagery resource. Both the ``gepolymaskgen`` and ``gemaskgen``
      tools are able to build high-quality masks to accompany image
      resources; however, there are cases where neither tool may be able
      to provide the correct solution for a set of imagery. Consider the
      mask and imagery resource from the :ref:`Case 5
      Example <Custom_Masks_gemaskgen_gepolymaskgen>` based on the SFBayAreaLanSat image
      resource for California (below) where ``gemaskgen`` successfully
      masked Fill Data from view and ``gepolymaskgen`` successfully
      masked ocean imagery to the specified coastline. The resulting
      mask masks out the San Francisco Bay which makes the
      low-resolution BlueMarble imagery visible (green).

      .. rubric:: SFBayAreaLanSat image resource as completed in Example
         Case 5:

      |SFBayAreaLanSat image with custom mask|

      .. rubric:: SFBayAreaLanSat image resource with automasking only:

      |SFBayAreaLanSat image with automask|

      One solution for this case is to manually modify the finished
      custom mask with a photo editing tool such as GIMP or Adobe
      Photoshop to alter the mask to show more or less imagery
      based on the circumstance. In this example, the
      ``usgsLanSat-mask.tif`` custom mask will be modified such that
      imagery for the San Francisco Bay will be visible in the final
      image resource while still masking imagery to the California
      Coastline. Here is the workflow for manually modifying the mask
      file for the SFBayAreaLanSat image resource:

      #. Load the ``usgsLanSat-mask.tif`` mask file created from the :ref:`Case 5
         Example <Custom_Masks_gemaskgen_gepolymaskgen>` into the photo editing
         application.

         |merged custom mask|

      #. Select the paintbrush tool and set to paint with white
         fill(255). The pixel width, opacity, and feather value of the
         brush needed will vary for each mask.
      #. Brush out the entire San Francisco Bay to remove the bay
         coastline mask.

         |bay coastline mark removed|

      #. Save the updated mask file to the same folder location as the
         ``usgsLanSat.tif`` source image file for the SFBayAreaLanSat
         image
         resource\ ``- /opt/google/share/tutorials/fusion/Imagery``.
      #. Modify the SFBayAreaLanSat image resource to enable the
         ``HaveMask`` mask mode.

         Please see :ref:`Appendix A <Importing_Custom_Masks_Imagery_Terrain_GEE_Fusion>`, Examples
         :ref:`3 <Enable_havemask_Existing_Image_Resource>` and :ref:`4 <Enable_havemask_Command_Line_Existing_Image_Resource>` for
         further details.

      #. Build the image resource to import the updated mask file.
      #. Load the SFBayAreaLanSat image resource into the Fusion Pro
         Preview.

         .. rubric:: usgsLanSat mask after mask updates to show the
            imagery for the San Francisco Bay:

         |san francisco bay with usgsLanSat mask|

      .. rubric:: usgsLanSat mask before mask edits:

         |usgsLanSat before mask|

      .. _Building_Custom_Masks_Large_Source_Imagery:
      .. rubric:: Appendix F: Building custom masks for large source
         imagery

      This is a special section intended for use when working with
      source imagery datasets - such as an image resource of 0.5-meter
      per pixel resolution 3-band, color imagery for an entire state -
      where a high-fidelity mask could easily create a mask
      file larger than 2 GB in file size. The same tools described in this
      document and appendices can be used to construct a custom mask
      that provides high fidelity masking for the image resource while
      being less than 2GB in file size. The key difference in the
      workflow for building custom masks for large imagery resources -
      where the image resource will have more than 65,000 pixels on one
      side - is the source imagery are imported first, then
      ``gemaskgen`` is called manually to create a stand-in base mask
      file for use with ``gepolymaskgen``. This workflow is similar to
      the :ref:`Case 5 Example <Custom_Masks_gemaskgen_gepolymaskgen>` where the image resource
      was imported first into Fusion Pro and then a custom mask was
      generated and added after import.

      The general workflow for this use case will be:

      Assuming the source imagery is detected to be larger than 65,000
      pixels on one side or more than 2,000,000,000 total pixels with
      ``geinfo`` (See :ref:`Appendix C <Determining_Source_File_Raster_Size_geinfo>`);

      #. Import the image resource with Fusion Pro.
      #. View the finished image resource in the Fusion Pro window to
         determine what type of masking may be needed so an appropriate
         example case may be referenced.
      #. Find the full paths to the imported Fusion-format ``kip``
         folder for the imagery with the ``gequery --outfiles command``
         (See :ref:`Appendix B <Locating_Mask_Files_Format_Data_Asset_Root>`, :ref:`Example
         1 <Locate_Fusion_Format_Imagery_Mask_Files_Image_Resource>`).
      #. Generate a stand-in base mask file with ``gemaskgen`` that
         will construct an image less than 2,000,000,000 total pixels
         (See :ref:`Appendix D <Building_High_Resolution_Mask_Files_gemaskgen>` for creating the mask
         and :ref:`Appendix C <Determining_Source_File_Raster_Size_geinfo>` for recommended mask
         sizes).
      #. Construct a custom mask with ``gepolymaskgen`` referencing the
         **stand-in** image from the :ref:`Case 5 Example <Custom_Masks_gemaskgen_gepolymaskgen>`
         as the ``--base_image``. Reference one of the five example
         cases for additional steps in constructing the custom mask.
      #. Update the image resource configuration to enable ``havemask``
         mode so the custom mask will be imported and applied to the
         image resource (See :ref:`Appendix A <Importing_Custom_Masks_Imagery_Terrain_GEE_Fusion>`, Examples
         :ref:`3 <Enable_havemask_Existing_Image_Resource>` and :ref:`4 <Enable_havemask_Command_Line_Existing_Image_Resource>`).
      #. Build the image resource to commit the change and import the
         new custom mask, then view the image resource in the Fusion
         Preview window.

      .. _gepolymaskgen_Help_Menu:
      .. rubric:: Appendix G: gepolymaskgen help menu

      A full copy of the help contents for ``gepolymaskgen`` is
      available in this appendix for reference:

      ``usage: gepolymaskgen --help | -?``

      ``gepolymaskgen [--feather <int_feather>] --base_mask <geotiff_mask_file> [options] --output_mask <geotiff_mask_file>``

      ``gepolymaskgen [--feather <int_feather>] --base_image <geotiff_image_file> [options] --output_mask <geotiff_mask_file>``

      ``Options are applied in order given.``

      ``Valid options:``

      ``--feather <int_feather>:     Feather to apply to all``

      ``subsequent masks until a``

      ``different feather is given.``

      ``Feather can be 0, positive,``

      ``or negative. Default is 0.``

      ``--feather_border <int_flag>: If flag is non-zero, border``

      ``is feathered. Otherwise,``

      ``border is left in tact.``

      ``Flag remains in effect``

      ``until it is modified.``

      ``Default is border is``

      ``feathered.``

      ``--and_neg_mask <mask_file>:  Bitwise AND of negative image``

      ``of polygon or raster mask``

      ``with the current mask.``

      ``Polygons can be given in``

      ``.kml or .shp files and are``

      ``assumed to be filled with``

      ``0x00. Raster masks should be``

      ``.tif files with the same pixel``

      ``dimensions as the base mask.``

      ``Care should be taken not to``

      ``overlap feathered regions.``

      ``--or_mask <mask_file>:       Bitwise OR polygon or raster``

      ``mask to the current mask.``

      ``Polygons can be given in``

      ``.kml or .shp files and are``

      ``assumed to be filled with``

      ``0xff. Raster masks should be``

      ``.tif files with the same pixel``

      ``dimensions as the base mask.``

      ``Care should be taken not to``

      ``overlap feathered regions.``

      ``--threshold <thresh_byte>:   All pixels at or below the``

      ``threshold byte are set to``

      ``0x00; all other pixels are set``

      ``to 0xff.``

      ``Please note that ordering of arguments is important; they are applied in the order that they are given. The feather argument implies that you are setting the feather to be used for any subsequent masks. E.g. to feather the base mask, you must set the feather before the base mask is given. Positive feathers erode the mask (white area retracts); negative feathers expand the mask (white area grows).``

      ``Examples:``

      ``-- simple polygon mask with no feathering``

      ``gepolymaskgen --base_image /path/input_image.tif \``

      ``--or_mask /path/polygon.kml \``

      ``--output_mask /path/result_mask.tif``

      ``-- negative polygon mask with some feathering``

      ``gepolymaskgen --base_image /path/input_image.tif \``

      ``--feather 30 \``

      ``--feather_border 0 \``

      ``--and_neg_mask /path/polygon.kml \``

      ``--invert \``

      ``--output_mask /path/result_mask.tif``

      ``-- OR and AND polygon and tiff masks with different feathers \``

      ``gepolymaskgen --feather 30 \``

      ``--base_mask /path/base_mask.tif \``

      ``--feather 20 \``

      ``--feather_border 0 \``

      ``--or_mask /path/SF.kml \``

      ``--or_mask /path/daly_city.kml \``

      ``--feather 15 \``

      ``--feather_border 1 \``

      ``--or_mask /path/circle_mask.tif \``

      ``--feather 5 \``

      ``--and_neg_mask /path/gg_park.kml \``

      ``--and_neg_mask /path/northbeach.kml \``

      ``--feather 40 \``

      ``--and_neg_mask /path/circle_mask2.tif \``

      ``--output_mask /path/mask.tif``

.. |Google logo| image:: ../../art/common/googlelogo_color_260x88dp.png
   :width: 130px
   :height: 44px
.. |Masked imagery diagram| image:: ../../art/custom_masks/image10.jpg
.. |Hidden masked diagram| image:: ../../art/custom_masks/image24.jpg
.. |Brazil Imagery mosaic diagram| image:: ../../art/custom_masks/image29.jpg
.. |Brazil Imagery Fusion import| image:: ../../art/custom_masks/image40.jpg
.. |hidden masked diagram| image:: ../../art/custom_masks/image24.jpg
.. |Fusion Pro with custom mask| image:: ../../art/custom_masks/image00.jpg
.. |gepolymaskgen in gimp photo editor| image:: ../../art/custom_masks/image31.jpg
.. |image with 100-pixel feather in Fusion| image:: ../../art/custom_masks/image21.jpg
.. |Fusion preview window| image:: ../../art/custom_masks/image02.jpg
.. |Island and water automask in Fusion| image:: ../../art/custom_masks/image11.jpg
.. |Mask with 100 pixel feather in GIMP| image:: ../../art/custom_masks/image09.jpg
.. |Custom| image:: ../../art/custom_masks/image33.jpg
.. |Mask file of Oahu Hawaii in GIMP| image:: ../../art/custom_masks/image34.jpg
.. |Oahu Hawaii in Fusion Preview| image:: ../../art/custom_masks/image28.jpg
.. |Fusiin Preview GUI in California| image:: ../../art/custom_masks/image41.jpg
.. |Example A mask file in GIMP| image:: ../../art/custom_masks/image13.jpg
.. |Finished image after custom mask import| image:: ../../art/custom_masks/image05.jpg
.. |picture frame border mask| image:: ../../art/custom_masks/image30.jpg
.. |finished mask of coastline and border feather| image:: ../../art/custom_masks/image07.jpg
.. |Finished image after custom mask import| image:: ../../art/custom_masks/image42.jpg
.. |finished mask in GIMP| image:: ../../art/custom_masks/image32.jpg
.. |Fusion preview window with custom mark import| image:: ../../art/custom_masks/image43.jpg
.. |image in Fusion with automask| image:: ../../art/custom_masks/image16.jpg
.. |Missing imagery in GEEC| image:: ../../art/custom_masks/image23.jpg
.. |Polygon on mising imagery| image:: ../../art/custom_masks/image03.jpg
.. |Custom mask with missing imagery in GIMP| image:: ../../art/custom_masks/image08.jpg
.. |Image in Fusion after custom mask import| image:: ../../art/custom_masks/image22.jpg
.. |gepolymaskgen Edge mask in GIMP| image:: ../../art/custom_masks/image06.jpg
.. |gepolymaskgen merged mask in GIMP| image:: ../../art/custom_masks/image08.jpg
.. |usgsLanSat.tif in Fusion pro with no mask| image:: ../../art/custom_masks/image19.jpg
.. |usgsLanSat.tif in Fusion pro with a mask| image:: ../../art/custom_masks/image15.jpg
.. |SFBayAreaLanSat image in fusion with custom mask| image:: ../../art/custom_masks/image12.jpg
.. |mask by gemaskgen during SFBayAreaLanSat import| image:: ../../art/custom_masks/image18.jpg
.. |Inverted base mask| image:: ../../art/custom_masks/image25.jpg
.. |Inverted coastlines mask| image:: ../../art/custom_masks/image20.jpg
.. |merged custom mask| image:: ../../art/custom_masks/image01.jpg
.. |SFBayAreaLanSat image with custom mask| image:: ../../art/custom_masks/image12.jpg
.. |Fusion GUI Asset Manager| image:: ../../art/custom_masks/image14.jpg
.. |Mask Options drop down menu| image:: ../../art/custom_masks/image17.jpg
.. |maskgen version properties| image:: ../../art/custom_masks/image44.jpg
.. |Maskgen Logfile diagram| image:: ../../art/custom_masks/image26.jpg
.. |SFBayAreaLanSat image with automask| image:: ../../art/custom_masks/image27.jpg
.. |bay coastline mark removed| image:: ../../art/custom_masks/image04.jpg
.. |san francisco bay with usgsLanSat mask| image:: ../../art/custom_masks/image12.jpg
.. |usgsLanSat before mask| image:: ../../art/custom_masks/image27.jpg
