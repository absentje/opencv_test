
template<typename ...Args>
int CVWrapper::processAsync( const cv::Mat& img, const Args&... args )
{
	using ProcessAsyncFuncType = int( const cv::Mat&, const Args&... );
	auto func = lib_.get_alias<ProcessAsyncFuncType>( "processAsyncName" );
	return func(img, args... );
}