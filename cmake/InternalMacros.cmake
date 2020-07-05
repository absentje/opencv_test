################################################################################
# Macro to install a target
################################################################################
macro(INSTALL_TARGET targetName)
	install( TARGETS ${targetName}
		RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
		LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
		ARCHIVE DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
	)
endmacro(INSTALL_TARGET)

################################################################################
# Macro to copy Qt dlls
################################################################################
macro(COPY_QT_DLLS)
	set(QtDllNames Qt5Test Qt5Gui Qt5Core Qt5OpenGL Qt5Widgets)
	foreach(QT_DLL_NAME ${QtDllNames})
		if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
			set(QT_DLL_NAME "${QT_DLL_NAME}d")
		endif()
		set(QT_DLL_NAME "${QT5_DIR}/bin/${QT_DLL_NAME}.dll")
		file(COPY ${QT_DLL_NAME} DESTINATION ${INSTALL_FOLDER})
	endforeach()
endmacro(COPY_QT_DLLS)

################################################################################
# Macro to copy OpenCV dlls
################################################################################
#find_package( OpenCV REQUIRED )

macro(COPY_CV_DLLS)
	message("_OpenCV_LIB_PATH: ${_OpenCV_LIB_PATH}")

	if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
		file(GLOB CV_DLLS "${_OpenCV_LIB_PATH}/*d.dll")
	else(${CMAKE_BUILD_TYPE} STREQUAL "Release")
		file(GLOB CV_DLLS "${_OpenCV_LIB_PATH}/*[^d].dll")
	endif()
	foreach(CV_DLL_NAME ${CV_DLLS})
		file(COPY ${CV_DLL_NAME} DESTINATION ${INSTALL_FOLDER})
	endforeach()
endmacro(COPY_CV_DLLS)
################################################################################