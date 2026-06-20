#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>
using namespace cv;
using namespace std;

void wave(Mat& image, Mat& result) {
	//映射参数
	Mat srcX(image.rows, image.cols, CV_32F);
	Mat srcY(image.rows, image.cols, CV_32F);

	//创建映射参数
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {

			//(i,j)像素的位置
			srcX.at<float>(i, j) = j;//保持在同一列
			srcY.at<float>(i, j) = i+5*sin(j/10.0);//原来在第i行的像素,现在根据一个正弦曲线移动
		}
	}
	remap(image, result, srcX, srcY, INTER_LINEAR);
}
int main() {
	Mat image1 = imread("D:/opencv资料库/opencv处理图像/屏幕截图 2025-02-13 092024.png");
	Mat result;
	wave(image1, result);
	imshow("图像相加", result);
	waitKey(0);
}