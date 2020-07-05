template<typename Params, typename>
int CVWrapper::processAsync( const Params& params )
{
	using ProcessAsyncFuncType = int( const Params& params );
	auto func = lib_.get_alias<ProcessAsyncFuncType>( "processAsyncName" );
	return func( params );
}

// deprecated variant --------------------------------------------------
template<typename ...Args>
int CVWrapper::processAsync( const cv::Mat& img, const Args&... args )
{
	using ProcessAsyncFuncType = int( const cv::Mat&, const Args&... );
	auto func = lib_.get_alias<ProcessAsyncFuncType>( "processAsyncName" );
	return func(img, args... );
}
//----------------------------------------------------------------------
