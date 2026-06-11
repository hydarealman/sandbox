#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;
int main() {
//绘制直方图
Mat gray;
Mat src = imread("D:/opencv资料库/opencv处理图像/opencv资料库.jpg");
if (!src.data) {
cout << "读取图片错误,请重新输入正确路径!\n";
system("pause");
return -1;
}
cvtColor(src, gray, COLOR_BGR2GRAY);
imshow("灰度图", gray);
//定义直方图参数并计算直方图
const int channels[] = { 0 };
Mat hist;//定义输出Mat类型
int dims = 1;//设置直方图维度
const int histSize[] = { 256 };//直方图每一个维度划分的柱条的数目
//每一个维度取值范围
float pranges[] = { 0,255 };//取值区间
const float* ranges[] = { pranges };

calcHist(&gray, 1, channels, Mat(), hist, dims, histSize, ranges, true, false);

//绘制直方图
int scale = 2;
int hist_height = 256;
Mat hist_img = Mat::zeros(hist_height, 256 * scale, CV_8UC3);//创建一个黑底的8位的三通道图像,高256，宽256*2
double max_val;
minMaxLoc(hist, 0, &max_val, 0, 0);

for (int i = 0; i < 256; i++) {
	float bin_val = hist.at<float>(i);//遍历hist元素
	int intensity = cvRound(bin_val * hist_height / max_val);//绘制高度
	rectangle(hist_img, Point(i * scale, hist_height - 1), Point((i + 1) * scale - 1, hist_height - intensity), Scalar(255, 255, 255));//绘制直方图
}

imshow("灰度直方图--方法一", hist_img);
waitKey(0);
}