cmake_minimum_required (VERSION 3.8)
find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories("${3RDPARTY_DIR}")

find_library(CVWrapper REQUIRED)

add_executable (Main "main.cpp")
target_link_libraries(Main opencv_highgui CVWrapper)
INSTALL_TARGET(Main)

# copy after create install_dir
COPY_QT_DLLS()
COPY_CV_DLLS()