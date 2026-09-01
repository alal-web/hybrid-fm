#[=======================================================================[.rst:
FindWebEngineDictConverter
-------

Finds the qwebengine_convert_dict tool

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``WebEngineDictConverter_FOUND``
  True if the system has the qwebengine_convert_dict executable.
``WebEngineDictConverter_EXECUTABLE``
  The path to the qwebengine_convert_dict executable
#]=======================================================================]
include(ECMQueryQmake)
query_qmake(QT_BINARIES_DIR QT_INSTALL_BINS)
find_program(WebEngineDictConverter_EXECUTABLE qwebengine_convert_dict HINTS ${QT_BINARIES_DIR})
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(WebEngineDictConverter
  FOUND_VAR WebEngineDictConverter_FOUND
  REQUIRED_VARS WebEngineDictConverter_EXECUTABLE
)
