find_package (Doxygen)

if(DOXYGEN_FOUND)
  configure_file (${worldIMaker_SOURCE_DIR}/doc/Doxyfile-html.cmake ${worldIMaker_BINARY_DIR}/doc/Doxyfile-html)
  add_custom_target (html ${DOXYGEN_EXECUTABLE} ${worldIMaker_BINARY_DIR}/doc/Doxyfile-html)
endif (DOXYGEN_FOUND)
