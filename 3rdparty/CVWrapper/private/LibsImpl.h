#include <boost/config.hpp>
#include <boost/dll/alias.hpp>
#include <future>
#include <unordered_map>
#include <opencv2/opencv.hpp>
#include <mutex>
#include "../LibParams.h"

namespace
{
int unique_handle = 0;
std::unordered_map<int, std::future<cv::Mat>> map_; // int - handle
std::mutex mapMutex;
}

#ifdef BLUR_LIB
int processAsync( const BlurParams& blur_params )
{
	std::lock_guard<std::mutex> lock( mapMutex );
	++unique_handle;
	map_.emplace( unique_handle, 
				  std::async( std::launch::async,

						[params{ std::move( blur_params ) }]
						{
							cv::Mat result( params.img.size(), params.img.type() );
							cv::GaussianBlur( params.img, result, params.size, params.sigmaX, params.sigmaY );
							return result;
						}
						));
	return unique_handle;
}
BOOST_DLL_ALIAS( processAsync, processAsyncName )
#endif

#ifdef ERODE_LIB
int processAsync( const ErodeParams& erode_params )
{
	std::lock_guard<std::mutex> lock( mapMutex );
	++unique_handle;
	map_.emplace( unique_handle, 
				  std::async( std::launch::async,
					[params{ std::move( erode_params ) }]
					{
						cv::Mat result( params.img.size(), params.img.type() );
						cv::erode( params.img,
									result,
									params.kernel,
									params.anchor,
									params.iterations );
						return result;
					}
	) );
	return unique_handle;
}
BOOST_DLL_ALIAS( processAsync, processAsyncName )
#endif


cv::Mat waitForResult( int handle )
{
	std::future<cv::Mat> result;
	{
		std::lock_guard<std::mutex> lock( mapMutex );
		auto iter = map_.find( handle );
		if ( iter != map_.end() )
		{
			result = std::move( iter->second );
			map_.erase( iter );
		}
		else
		{
			return cv::Mat();
		}
	}
	return result.get();
}
BOOST_DLL_ALIAS( waitForResult, waitForResultName )




