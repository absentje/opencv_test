cmake_minimum_required (VERSION 3.8)

# boost
set(Boost_USE_STATIC_LIBS ON)
find_package( Boost 1.73.0 REQUIRED COMPONENTS filesystem )
include_directories(${Boost_INCLUDE_DIRS})

# opencv
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})

# CVWrapper (lib interface)
add_library (CVWrapper STATIC "CVWrapper.cpp")
target_link_libraries(CVWrapper ${Boost_LIBRARIES})
target_include_directories(CVWrapper PUBLIC ${OpenCV_INCLUDE_DIRS})
target_include_directories(CVWrapper PUBLIC ${Boost_INCLUDE_DIRS})
INSTALL_TARGET(CVWrapper)

# CVWrapperImpl (library implementation)
add_library (CVWrapperImpl SHARED "CVWrapperImpl.cpp")
target_link_libraries(CVWrapperImpl opencv_highgui ${Boost_LIBRARIES})
INSTALL_TARGET(CVWrapperImpl)