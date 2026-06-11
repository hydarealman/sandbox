#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main() {
//阈值二值化处理
Mat src = imread("D:/opencv资料库/opencv处理图像/opencv资料库.jpg");
cvtColor(src, src, COLOR_BGR2GRAY);
Mat fixedThresh, adaptiveThresh;

//固定阈值
double thresh_value = 128;
double max_value = 255;
threshold(src,fixedThresh,thresh_value,max_value,THRESH_BINARY);

//自动适应阈值
adaptiveThreshold(src, adaptiveThresh, max_value, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 2);

//显示结果
namedWindow("fixed threshold", WINDOW_FREERATIO);
namedWindow("adaptive threshold", WINDOW_FREERATIO);
imshow("fixed threshold", fixedThresh);
imshow("adaptive threshold", adaptiveThresh);
waitKey(0);

return 0;
}