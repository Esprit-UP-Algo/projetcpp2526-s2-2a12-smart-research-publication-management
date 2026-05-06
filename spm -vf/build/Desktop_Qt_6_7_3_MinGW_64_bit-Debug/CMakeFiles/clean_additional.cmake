# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SmartResearchPublicationManagement_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SmartResearchPublicationManagement_autogen.dir\\ParseCache.txt"
  "SmartResearchPublicationManagement_autogen"
  )
endif()
