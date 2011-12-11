 
	   Package: SkyEdit v0.01alpha, 10 December 2011
	    Author: Dave Humphrey, dave@uesp.net
	   Website: www.uesp.net/wiki/Tes5Mod:SkyEdit


  Introduction
=======================================
SkyEdit is an alternate editor for The Elder Scrolls:Skyrim, similar to the official
"Creation Kit". This first release is mainly for testing and feedback and only a 
basic set of features is included. 


  Important Release Notes
=======================================

  - As a first release there may, or will, be bugs present that may affect any saved
    plugins. As with any third party utility, keep regular backups of plugins. SkyEdit
	automatically backs up plugins when saved (unless disabled).
  - One main purpose for this release is to receive feedback from the modding community.
    Feedback may be given at:
               http://www.uesp.net/wiki/Tes5Mod:SkyEdit/Feedback
               http://www.uesp.net/wiki/Tes5Mod:SkyEdit/Bugs
            or dave@uesp.net
    All comments, suggestions, and bug reports are welcome.
  - Another major purpose of this release is for more extensive testing. The more people
    use it and the more different systems it is used on the more bugs can be found and
	fixed.
  - A minimum of 512MB of RAM is recommended for decent performance. Loading of 
    Skyrim.esm uses around 500MB of memory. Plugins can also be edited without loading
	the master files to save time/memory but this limits what editing can be done.
  - Some help and documentation can be found at:
               http://www.uesp.net/wiki/Tes5Mod:SkyEdit


  Current Status
=======================================

  Fully Editable Records
	- Keywords
	- Globals
	- Game Settings
	- Recipes

  Partially Editable Records
	- Weapons
	- Magic Effects


  What it Can Do
=======================================
The basic capabilities of the editor in this release include:

  - Load plugins with multiple master files
  - Edit a few record types
  - Basic find text feature
  - Viewing/selection of resources in Data path and in BSA files
  - Import/export from/to CSV files
  - Simple undo system
  - Automatic backup when saving plugins


  What it Can't Do (Yet)
=======================================
Some notable lack of features in the current release are:

  - Cannot edit or view most record types yet
  - No script compiler or syntax highlighting
  - No cell view or preview windows
  - No use info display
  - Does not update dependancies when deleting records


  Installation
=======================================
  - Download the SkyEdit binary version
  - Unzip into a directory of your choice
  - Multiple installations of SkyEdit can be made in seperate directories
  - All program options are found in SKYEDIT.INI
  - There should be no specific requirements to run SkyEdit. It includes all 
    necessary external libraries so if it runs Skyrim it should run SkyEdit.
  - A minimum of 512MB of RAM is required and 1GB or more is suggested. 
  - Several 100MB of free disk space is recommended and more is better (for 
    backups and temporary resource files).


  Features
=======================================
Some more specific features of the editor are listed below. A more exhaustive list 
can be found at:
               http://www.uesp.net/wiki/Tes5Mod:SkyEdit/Features

      General
  ---------------------------
  - Automatic backup of files when saving
  - Undo most actions when editing records
  - More complete find text or binary data 
  - Batch edit multiple records with common fields
  - Easily open and edit multiple plugins at once 
  - Press F1 to access appropriate help on the UESP or CS wikis

      User Interface
  ---------------------------
  - Record counts shown in record tree
  - Record list shows active and deleted records in different colors
  - Custom dialog to make selection of scripts, enchantments, etc...
  - Record list shows almost all fields for a record
  - Record tree can be customized to show different grouping of records.
  - Update a record being edited without closing its dialog (Apply)
  - Drag-and-drop operations are supported in more locations
  - Tooltips for most controls

      Resource Viewer
  ---------------------------
  - Seperate window for viewing and selecting game resources (textures, meshes,
    sounds, icons, etc...)
  - View resources in DATA path as well as within known BSA files.
  
      Import/Export
  ---------------------------
  - Import/export most records from/to CSV (Comma Seperated Value) files
  - Most records fields supported
  - Existing records are automatically updated/overwritten when importing
  - Formids automatically assigned to new imported records

      Performance
  ---------------------------
  - Improved performance at the cost of requiring more memory
  - Skyrim.esm is only ever loaded once. This allows multiple plugins to 
    be loaded at once and decreases loading time of subsequent loads. 
  - Simple caching to defer loading of parts of master files to reduce
    memory requirements (currently only LAND and NAVM records).



  Credits
=======================================
SkyEdit uses several libraries which has sped up development considerably.

  - Devil (http://openil.sourceforge.net/) for loading images.
  - zLib (http://www.zlib.net/) for loading/saving compressed data.
  - Resizable Control Bars (http://www.datamekanix.com/) for the dockable error/undo 
    control bars in the main view.
  - Tes5Lib (http://github.com/uesp/tes5lib)


