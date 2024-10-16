# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\PBL2-LibraryManagement_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\PBL2-LibraryManagement_autogen.dir\\ParseCache.txt"
  "PBL2-LibraryManagement_autogen"
  )
endif()
