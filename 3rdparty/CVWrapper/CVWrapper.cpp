#include "CVWrapper.h"
#include <boost/dll.hpp>

CVWrapper::CVWrapper( const std::string& libname )
	: lib_( libname )
{
	bool isLoaded = lib_.is_loaded();

	blurAsyncFunc_ = lib_.get_alias<BlurAsyncFuncType>( "blurAsyncName" );
	blurResultFunc_ = lib_.get_alias<BlurResultFuncType>( "blurResultName" );
}

int CVWrapper::blurAsync( const cv::Mat& img, cv::Size size, double sigmaX, double sigmaY )
{
	return blurAsyncFunc_( img, size, sigmaX, sigmaY );
}

cv::Mat CVWrapper::blurResult( int handle )
{
	return blurResultFunc_( handle );
}