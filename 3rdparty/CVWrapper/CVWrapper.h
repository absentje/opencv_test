#pragma once
#include <string>
#include <boost/dll/shared_library.hpp>
#include <functional>
#include <opencv2/core/mat.hpp>
//#include <opencv2/opencv.hpp>

/*
*	lib interface
*/

class CVWrapper
{
public:
	CVWrapper( const std::string& libname );

	int blurAsync( const cv::Mat& img, cv::Size size, double sigmaX, double sigmaY );
	cv::Mat blurResult( int handle );

private:
	using BlurAsyncFuncType = int( const cv::Mat&, cv::Size, double, double );
	using BlurResultFuncType = cv::Mat( int );

	boost::dll::shared_library lib_;

	std::function<BlurAsyncFuncType> blurAsyncFunc_;
	std::function<BlurResultFuncType> blurResultFunc_;
};