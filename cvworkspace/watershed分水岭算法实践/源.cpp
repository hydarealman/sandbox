#include<stdio.h>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
	char input_win[] = "input image";
	char watershed_win[] = "watershed segementation demo";
	Mat src  = imread("D:/opencv资料库/opencv处理图像/th.jpg",-1);
	resize(src, src,Size(), 1, 1, 1);

	if (src.empty()) {
		puts("could not load images");
		return -1;
	}

	namedWindow(input_win, WINDOW_AUTOSIZE);
	imshow(input_win, src);

	//1.将白色背景变成黑色背景 - 目的是为了后面的变换做准备
	for (int row = 0; row < src.rows; row++) {
		for (int col = 0; col < src.cols; col++) {
			if (src.at<Vec3b>(row, col) == Vec3b(255, 255, 255)) {
				src.at<Vec3b>(row, col)[0] = 0;
				src.at<Vec3b>(row, col)[1] = 0;
				src.at<Vec3b>(row, col)[2] = 0;
			}
		}
	}
	namedWindow("black background", WINDOW_AUTOSIZE);
	imshow("black background", src);
	

	//使用filter2D与拉普拉斯算子实现图像对比度的提高 - sharp
	Mat kernel1 = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
	Mat imgLaplance;
	Mat imgSharpen;
	filter2D(src, imgLaplance, CV_32F, kernel1, Point(-1, -1), 0, BORDER_DEFAULT);

	src.convertTo(imgSharpen, CV_32F);
	Mat imgResult = imgSharpen - imgLaplance;
	imgResult.convertTo(imgResult, CV_8UC3);
	imgLaplance.convertTo(imgLaplance, CV_8UC3);
	imshow("sharpen img", imgResult);

	//3.通过threshold转为二值图像
	Mat imgBinary;
	cvtColor(imgResult, imgResult, COLOR_BGR2GRAY);
	threshold(imgResult, imgBinary,40,255,THRESH_BINARY|THRESH_OTSU);

	Mat temp;
	imgBinary.copyTo(temp, Mat());
	Mat kernel2 = getStructuringElement(MORPH_RECT, Size(2, 2), Point(-1, -1));
	morphologyEx(temp, temp, MORPH_TOPHAT, kernel2, Point(-1, -1), 1);

	for (int row = 0; row < src.rows; row++) {
		for (int col = 0; col < src.cols; col++) {
			imgBinary.at<uchar>(row, col) = saturate_cast<uchar>(imgBinary.at<uchar>(row, col) - temp.at<uchar>(row, col));
		}
	}

	imshow("sharpen img", imgResult);
	imshow("binary img", imgBinary);

	//4.距离变换
	Mat imgDist;
	distanceTransform(imgBinary, imgDist, DIST_L1, 3);
	

	//5.对距离变换结果进行归一化[0-1]之间
	normalize(imgDist, imgDist, 0, 1, NORM_MINMAX);
	imshow("distance result normalize", imgDist);




	waitKey(0);
}