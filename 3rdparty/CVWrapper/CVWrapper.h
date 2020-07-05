#pragma once
#include <string>
#include <boost/dll.hpp>
#include <functional>
#include <opencv2/core/mat.hpp>

/*
*	lib interface
*/

class CVWrapper
{
public:
	CVWrapper( const std::string& libname );

	template<typename ...Args>
	int processAsync( const cv::Mat& img, const Args&... );

	cv::Mat waitForResult( int handle );

private:
	using WaitForResultFuncType = cv::Mat( int );

	boost::dll::shared_library lib_;
	std::function<WaitForResultFuncType> waitForResultFunc_;
};

#include "CVWrapper.hpp"