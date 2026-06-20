#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;


int main() {
	Mat image1 = imread("D:/opencv资料库/opencv处理图像/屏幕截图 2025-02-13 092024.png");
	Mat image2 = imread("D:/opencv资料库/opencv处理图像/屏幕截图 2025-02-13 092042.png");
	Mat src;
	resize(image2, image2, image1.size());
	addWeighted(image1, 0.7, image2, 0.9, 1, src);
	imshow("图像相加", src);
	waitKey();
}