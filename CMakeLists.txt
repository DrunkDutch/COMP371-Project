cmake_minimum_required(VERSION 3.7)
project(COMP371-Project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY cmake-build-debug)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules)

# Find SOIL package
find_package(SOIL REQUIRED)
include_directories(${SOIL_INCLUDE_DIRS})
set(LIBS ${LIBS} ${SOIL_LIBRARIES})

# Find Assimp package
find_package(assimp REQUIRED)
include_directories(${ASSIMP_INCLUDE_DIRS})
set(LIBS ${LIBS} ${ASSIMP_LIBRARIES})


# Setup conan lib locations
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)  # Clion, with conanbuildinfo.cmake in build directory
    include(${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
    conan_basic_setup()
elseif(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)  # Not CLion
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
elseif(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)  # Look in .conan directory
    include(.conan/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()


# Setup conan autobuild missing
# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/memsharded/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif()


set(SOURCE_FILES src/main.cpp src/shader.hpp src/camera.hpp src/world.hpp src/window.hpp src/input.hpp src/geo_obj.hpp src/track.hpp src/track.cpp src/plane.cpp src/plane.hpp src/cube.hpp src/model.hpp src/mesh.hpp src/objloader.hpp src/objloader.cpp src/lamp.h)
add_executable(comp371-project ${SOURCE_FILES})
target_link_libraries(comp371-project ${CONAN_LIBS} ${LIBS})
