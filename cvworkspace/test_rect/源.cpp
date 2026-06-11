#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
using namespace cv;
int main() {
	Mat image = imread("D:/opencv资料库/opencv处理图像/opencv资料库.jpg");
	Mat logo = imread("C:/Users/dong/Pictures/Screenshots/奶龙.jpg");
	Mat imageROI(image,Rect(image.cols-logo.cols,image.rows-logo.rows,logo.cols,logo.rows));

	//插入标志
	logo.copyTo(imageROI);
	imshow("插入图片", imageROI);
	waitKey(0);
}