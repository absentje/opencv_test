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

# BlurAsync (library implementation)
add_library (BlurAsyncLib SHARED "BlurAsyncLib.cpp")
target_link_libraries(BlurAsyncLib opencv_highgui ${Boost_LIBRARIES})
INSTALL_TARGET(BlurAsyncLib)

# ErodeAsync (library implementation)
add_library (ErodeAsyncLib SHARED "ErodeAsyncLib.cpp")
target_link_libraries(ErodeAsyncLib opencv_highgui ${Boost_LIBRARIES})
INSTALL_TARGET(ErodeAsyncLib)