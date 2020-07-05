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
		lib = std::make_shared<CVWrapper>( "BlurAsyncLib.dll" );
	}
	catch ( const boost::exception& ex )
	{
		std::cerr << boost::diagnostic_information( ex );
	}
	if ( !lib ) return 0; // library wasn't uploaded

	auto image = cv::imread( "images/img.jpg" );
	BlurParams params;
	image.copyTo( params.img );
	params.sigmaX = params.sigmaY = 10.;
	params.size = cv::Size( 5, 5 );

	auto handle = lib->processAsync( params );

	std::this_thread::sleep_for( std::chrono::milliseconds( 10 ) );

	auto resultImg = lib->waitForResult( handle );
	cv::imshow( "window1", image );
	cv::imshow( "window2", resultImg );
	cv::waitKey();
	return 0;
}