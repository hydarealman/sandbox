#include<opencv2/opencv.hpp>
#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
using namespace cv;
using namespace std;

int main() {
	Mat srcImage = imread("D:/opencv资料库/opencv处理图像/opencv资料库.jpg");
	if (!srcImage.data)
		return 1;
	imshow("srcImage", srcImage);

	int xRoi = 0;
	int yRoi = 0;
	int widthRoi = 20;
	int heightRoi = 10;

	Mat ROI_img(srcImage, Rect(xRoi, yRoi, widthRoi, heightRoi));
	namedWindow("ROI_img", WINDOW_FREERATIO);
	imshow("ROI_img", ROI_img);
	waitKey(0);

	return 0;
}