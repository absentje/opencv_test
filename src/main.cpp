#include <iostream>
#include <CVWrapper/CVWrapper.h>
#include <opencv2/opencv.hpp>
#include <boost/exception/diagnostic_information.hpp>
#include <memory>

int main(int argc, char *argv[])
{
	std::shared_ptr<CVWrapper> lib;
	try
	{
		lib = std::make_shared<CVWrapper>( "CVWrapperImpl.dll" );
	}
	catch ( const boost::exception& ex )
	{
		std::cerr << boost::diagnostic_information( ex );
	}
	if ( !lib ) return 0; // library wasn't uploaded

	auto image = cv::imread( "img.jpg" );
	auto handle = lib->processAsync( image, cv::Size( 15, 15 ), 4, 4 );

	std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );

	auto resultImg = lib->waitForResult( handle );
	cv::imshow( "window1", image );
	cv::imshow( "window2", resultImg );
	cv::waitKey();
	return 0;
}