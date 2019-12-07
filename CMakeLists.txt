cmake_minimum_required(VERSION 2.8)

project(worldIMaker)

set(EXECUTABLE_NAME worldIMaker)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

# For UPEM compilation
if(UPEMLV)
    set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)
endif(UPEMLV)

## INCLUDE LIB ##

#OpenGL
message("Looking for OpenGL...")
find_package(OpenGL REQUIRED)
if(${OpenGL_FOUND})
    message(STATUS "lib OpenGL found")
    message(STATUS "  version " ${OpenGL_VERSION_STRING})
    message(STATUS "  include " ${OpenGL_INCLUDE_DIR})
endif()

#GLEW
message("Looking for GLEW...")
find_package(GLEW REQUIRED)
if(${GLEW_FOUND})
    message(STATUS "lib GLEW found")
    message(STATUS "  version " ${OpenGL_VERSION_STRING})
    message(STATUS "  include " ${OpenGL_INCLUDE_DIR})
endif()

#SDL2

message("Looking for SDL2...")
# On windows
if (WIN32) 
    set(SDL2_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.10/include)
    set(SDL2_LIBRARIES ${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.10/lib/x64/SDL2.lib;
                       ${CMAKE_SOURCE_DIR}/lib/SDL2-2.0.10/lib/x64/SDL2main.lib)
# On linux
else()
find_package(SDL2 REQUIRED)
if(${SDL2_FOUND})
    message(STATUS "lib SDL2 found")
    message(STATUS "  version " ${SDL2_VERSION_STRING})
    message(STATUS "  include " ${SDL2_INCLUDE_DIR})
endif()
endif()

# include eigen
message("Looking for Eigen...")
find_package(Eigen3 REQUIRED)
if(${EIGEN3_FOUND})
    message(STATUS "lib EIGEN3 found")
    message(STATUS "  version " ${EIGEN3_VERSION_STRING})
    message(STATUS "  include " ${EIGEN3_INCLUDE_DIR})
else()
    include_directories("/usr/include/eigen3") # manually specify the include location
endif()

#GLAD
add_library(GLAD STATIC "lib/glad/src/glad.c")

# compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -lSDL2 -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")

include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} lib/glimac/include lib/imgui/include lib/glad/include third-party/include)

set(ALL_LIBRARIES ${SDL2_LIBRARIES} glimac imgui GLAD ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

# Add the glimac library
add_subdirectory(lib/glimac)
# Add the imgui library
add_subdirectory(lib/imgui)

file(GLOB_RECURSE HEADER_FILES src/include/*) # get all headers
file(GLOB_RECURSE SRC_FILES src/*.cpp) # get all sources files
file(GLOB_RECURSE SHADERS_FILES shaders/*.glsl) # get all shaders
file(GLOB_RECURSE ASSETS_FILES assets/*) # get all the assets

add_executable(${EXECUTABLE_NAME} ${SHADERS_FILES} ${ASSETS_FILES} ${SRC_FILES} ${HEADER_FILES}) # add the executable

target_link_libraries(${EXECUTABLE_NAME} ${ALL_LIBRARIES})
file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY lib/debug_break DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/lib)
file(COPY lib/spdlog DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/lib)

if (WIN32) # Copy .dll to build folder
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/lib/SDL2-2.0.10/lib/x64/SDL2.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()