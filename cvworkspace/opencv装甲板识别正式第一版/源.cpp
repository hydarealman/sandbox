#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;

int main() {

	//视频处理
	VideoCapture video;
	video.open("D:/opencv操作视频保存/视频1.avi");

	//各种参数


	//图像预处理
	//HSV颜色过滤
	//定义敌方颜色
	Scalar lower_red1(0, 50, 50), upper_red1(10, 255, 255);//HSV红色区间1
	Scalar lower_red2(160, 50, 50), upper_red2(180, 255, 255);//Hsv区间2

	Mat hsv, mask_red1, mask_red2, mask_combined;

	//双区间合并处理红色
	inRange(hsv, lower_red1, upper_red1, mask_red1);
	inRange(hsv, lower_red2, upper_red2, mask_red2);
	bitwise_or(mask_red1, mask_red2, mask_combined);
	
	//形态学开运算去噪声
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	morphologyEx(mask_combined, mask_combined, MORPH_OPEN, kernel);

	imshow("test",mask_combined);
	waitKey(0);



	//形态学操作


	//轮廓筛选条件



	//提取旋转矩形顶点



	//灯条配对(核心)




	//角度/距离/比例满足



	//计算装甲板区域


	//绘制四边形围框
}
