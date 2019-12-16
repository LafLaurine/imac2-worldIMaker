find_package (Doxygen)

message("worldIMaker_SOURCE_DIR     " ${worldIMaker_SOURCE_DIR})
message("worldIMaker_BINARY_DIR     " ${worldIMaker_BINARY_DIR})
message("DOXYGEN_EXECUTABLE     " ${worldIMaker_EXECUTABLE})

if(DOXYGEN_FOUND)
  configure_file (${worldIMaker_SOURCE_DIR}/doc/Doxyfile-html.cmake ${worldIMaker_BINARY_DIR}/doc/Doxyfile-html)
  add_custom_target (html ${DOXYGEN_EXECUTABLE} ${worldIMaker_BINARY_DIR}/doc/Doxyfile-html)
endif (DOXYGEN_FOUND)
