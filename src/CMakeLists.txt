cmake_minimum_required (VERSION 3.8)
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("${3RDPARTY_DIR}")

find_library(CVWrapper REQUIRED)

# blurTest.exe
add_executable (blurTest "blurTest.cpp")
target_link_libraries(blurTest opencv_highgui CVWrapper)
INSTALL_TARGET(blurTest)

# erodeTest.exe
add_executable (erodeTest "erodeTest.cpp")
target_link_libraries(erodeTest opencv_highgui CVWrapper)
INSTALL_TARGET(erodeTest)

# copy after create install_dir
COPY_QT_DLLS()
COPY_CV_DLLS()