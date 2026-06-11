#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

int main() {
//定义一个带边框的矩形
//矩形外部的像素会被标记为背景
Rect rectangle(5, 5, 1, 1);
Mat result;					//分割结果
Mat bgModel, fgModel;		//模型内部使用
Mat image = imread("D:/opencv资料库/opencv处理图像/屏幕截图 2025-02-13 092024.png");
	//GrabCut分割算法
grabCut(image, result, rectangle,bgModel,fgModel,5,GC_INIT_WITH_RECT);
imshow("result", result);
waitKey(0);
}