#include<opencv2/opencv.hpp>
#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
using namespace cv;
using namespace std;


int main() {
	Mat image = imread("D:/opencv资料库/opencv处理图像/opencv资料库.jpg");
	Mat hsv;
	vector<Mat> channels;
	cvtColor(image, hsv,COLOR_BGR2HSV);
	split(hsv, channels);
	namedWindow("channels[0]", WINDOW_FREERATIO);
	namedWindow("channels[1]", WINDOW_FREERATIO);
	namedWindow("channels[2]", WINDOW_FREERATIO);
	namedWindow("hsv", WINDOW_FREERATIO);
	imshow("channels[0]", channels[0]);
	imshow("channels[1]", channels[0]);
	imshow("channels[2]", channels[0]);
	merge(channels, hsv);
	imshow("hsv", hsv);
	waitKey(0);
}