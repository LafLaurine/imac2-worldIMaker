cmake_minimum_required(VERSION 2.8)

project(worldIMaker)

set(EXECUTABLE_NAME worldIMaker)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/lib)

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
find_package(SDL2 REQUIRED)
if(${SDL2_FOUND})
    message(STATUS "lib SDL2 found")
    message(STATUS "  version " ${SDL2_VERSION_STRING})
    message(STATUS "  include " ${SDL2_INCLUDE_DIR})
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

# compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -lSDL2 -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")

include_directories(${SDL2_INCLUDE_DIRS} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} lib/glimac/include lib/imgui/include third-party/include)

set(ALL_LIBRARIES ${SDL2_LIBRARIES} glimac imgui ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

# Add the glimac library
add_subdirectory(lib/glimac)
add_subdirectory(lib/imgui)

file(GLOB_RECURSE HEADER_FILES src/include/*.hpp) # get all headers
file(GLOB_RECURSE SRC_FILES src/*.cpp) # get all sources files
file(GLOB_RECURSE SHADER_FILES shaders/*.glsl) # get all shaders
file(GLOB_RECURSE ASSET_FILES assets/*) # get all the assets

add_executable(${EXECUTABLE_NAME} ${SRC_FILES} ${HEADER_FILES} ${SHADER_FILES} ${ASSET_FILES}) # add the executable

target_link_libraries(${EXECUTABLE_NAME} ${ALL_LIBRARIES})