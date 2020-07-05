#pragma once
#include <opencv2/core/mat.hpp>
#include <memory>

struct CVParamsBase {};

struct BlurParams : CVParamsBase
{
	cv::Mat img;
	cv::Size size;
	double sigmaX;
	double sigmaY;
};

struct ErodeParams : CVParamsBase
{
	cv::Mat img;
	cv::Mat kernel;
	cv::Point anchor;
	int iterations;
};