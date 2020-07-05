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
		lib = std::make_shared<CVWrapper>( "ErodeAsyncLib.dll" );
	}
	catch ( const boost::exception& ex )
	{
		std::cerr << boost::diagnostic_information( ex );
	}
	catch ( const std::exception& ex )
	{
		std::cerr << ex.what();
	}

	if ( !lib ) return 0; // library wasn't uploaded

	auto image = cv::imread( "images/img.jpeg" );

	ErodeParams params;
	image.copyTo( params.img );
	params.kernel = cv::getGaussianKernel( 7, 10 );
	params.anchor = cv::Point( 0, 0 );
	params.iterations = 1;

	auto handle = lib->processAsync( params );
	std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );

	auto resultImg = lib->waitForResult( handle );
	cv::imshow( "window1", image );
	cv::imshow( "window2", resultImg );
	cv::waitKey();
	return 0;
}