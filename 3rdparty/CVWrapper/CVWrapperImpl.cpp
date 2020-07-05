#include <boost/config.hpp>
#include <boost/dll/alias.hpp>
#include <future>
#include <unordered_map>
#include <opencv2/opencv.hpp>
#include <mutex>

namespace
{
int unique_handle = 0;
std::unordered_map<int, std::future<cv::Mat>> map_; // int - handle
std::mutex mapMutex;
}

int blurAsync( const cv::Mat& img, cv::Size size, double sigmaX, double sigmaY )
{
	std::lock_guard<std::mutex> lock( mapMutex );
	++unique_handle;
	map_.emplace( unique_handle, std::async( std::launch::async,
							  [&img, size, sigmaX, sigmaY] {
								  cv::Mat result( img.size(), img.type() );
								  cv::GaussianBlur( img, result, size, sigmaX, sigmaY );
								  return result;
							  }
							 ));
	return unique_handle;
}

cv::Mat blurResult( int handle )
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

BOOST_DLL_ALIAS( blurAsync, blurAsyncName )
BOOST_DLL_ALIAS( blurResult, blurResultName )