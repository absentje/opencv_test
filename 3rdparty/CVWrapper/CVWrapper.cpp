#include "CVWrapper.h"
#include <boost/dll.hpp>

CVWrapper::CVWrapper( const std::string& libname )
	: lib_( libname )
{
	waitForResultFunc_ = lib_.get_alias<WaitForResultFuncType>( "waitForResultName" );
}

cv::Mat CVWrapper::waitForResult( int handle )
{
	return waitForResultFunc_( handle );
}