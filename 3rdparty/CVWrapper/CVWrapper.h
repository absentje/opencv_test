#pragma once
#include <string>
#include <boost/dll.hpp>
#include <functional>
#include <opencv2/core/mat.hpp>
#include "LibParams.h"
#include <type_traits>

/*
*	lib interface
*/

class CVWrapper
{
public:
	CVWrapper( const std::string& libname );

	template<typename Params,
		typename = std::enable_if_t<std::is_base_of<CVParamsBase, Params>::value>>
	int processAsync( const Params& params );
	cv::Mat waitForResult( int handle ); // output can be one of parameters
										 // or we can use template output param

private:
	using WaitForResultFuncType = cv::Mat( int );
	boost::dll::shared_library lib_;
	std::function<WaitForResultFuncType> waitForResultFunc_;

	// deprecated variant -----------------------------------------------
	 template<typename ...Args>
	 [[deprecated]] int processAsync( const cv::Mat& img, const Args&... );
	//-------------------------------------------------------------------
};

#include "CVWrapper.hpp"