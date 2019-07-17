#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main()
{
	cv::Mat image_in = cv::imread("D:/autocruis/Gamma/IMG_1.jpg");

	int r = image_in.rows;
	int c = image_in.cols;
	int d = image_in.dims;
	int i, j, k,ch1[] = {2,0}, ch2[] = {0,2};
	cv::Mat image_out = cv::Mat(r, c, CV_8UC3);
	cv::Mat image_hsv = cv::Mat(r,c,CV_8UC3);
	cv::Mat image_v = cv::Mat(r, c, CV_8UC1);
	cv::Mat image_3 = cv::Mat(r, c, CV_32FC1);
	cv::Mat mask = cv::Mat(r, c, CV_8UC1);
	cv::Mat mask1 = cv::Mat(r, c, CV_8UC1);
	cv::Mat image_temp = cv::Mat(r, c, CV_32FC1);
	cv::Mat gamma = cv::Mat( r, c, CV_32FC1);

	if (image_in.empty())	return -1;
	cv::namedWindow("image_input", 0);
	cv::imshow("image_input", image_in);

	cvtColor(image_in, image_hsv, CV_RGB2HSV);
	mixChannels(&image_hsv,1,&image_v,1,ch1,1);
	mask = 255 - image_v;
	cv::bilateralFilter( mask, mask1, 5, 3, 0.1);
	mask1.convertTo( gamma, CV_32FC1);
	image_v.convertTo(image_3, CV_32FC1);
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < c; j++)
		{
			gamma.at<float>(i, j) = pow(2, (128 - gamma.at<float>(i, j)) / 128.0);
			image_temp.at<float>(i, j) = pow( image_3.at<float>(i, j)/255.0, gamma.at<float>(i, j))*255;
		}
	}
	image_temp.convertTo( image_v, CV_8UC1);
	
	mixChannels(&image_v, 1, &image_hsv, 1, ch2, 1);
	cvtColor(image_hsv, image_out, CV_HSV2RGB);
	cv::namedWindow("image_output", 0);
	cv::imshow("image_output", image_out);
	cv::waitKey(0);
	cv::destroyWindow("image_input");
	cv::destroyWindow("image_output");
	return 0;
}