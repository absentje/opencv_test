project ("dyn_async_openCV")
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "lib")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" )
include( InternalMacros )

set(3RDPARTY_DIR "${CMAKE_SOURCE_DIR}/3rdparty")
set(CVWrapper_DIR "${3RDPARTY_DIR}/CVWrapper")

set(INSTALL_FOLDER "${CMAKE_INSTALL_PREFIX}/bin")

add_subdirectory ("src")
add_subdirectory (${CVWrapper_DIR})
