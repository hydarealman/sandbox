#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;

//创建灯条类
class LightDescriptor {
	//在识别以及匹配到灯条的功能中需要用到旋转矩形的长，宽，偏转角，面积，中心点坐标等
public:
	float width, height, angle, area;
public:
	LightDescriptor() {};
	//让得到的灯条套上一个旋转矩形,以方便之后对角度这个特殊因素作为匹配标准
	LightDescriptor(const RotatedRect& light) {
		width = light.size.width;
		height = light.size.height;
		angle = light.angle;
		area = light.size.area();
	}
};

int main() {

	VideoCapture video;
	video.open("D:/opencv资料库/opencv操作视频保存/机器人旋转视频.avi");

	Mat frame,binary,gaussian,dilatee;
	//返回一个结构元素（卷积核）
	Mat element = getStructuringElement(MORPH_RECT,//返回矩形卷积核
		Size(5, 5));//卷积核大小
	vector<Mat> channels;
	vector<vector<Point>> contours;

	for (;;) {
		video >> frame;
		if (frame.empty()) {
			break;
		}
		//图像预处理
		//通道分离
		split(frame, channels);
		//二值化
		threshold(channels[0],binary,220,255,THRESH_BINARY);
		//滤波
		GaussianBlur(binary, gaussian, Size(5, 5), 0);
		//膨胀
		dilate(gaussian,dilatee,element);
		findContours(dilatee,contours,RETR_TREE,CHAIN_APPROX_NONE);
		vector<LightDescriptor> lightInfos;//创建一个灯条类的动态数组
		for (int i = 0; i < contours.size(); i++) {
			//求轮廓面积
			double area = contourArea(contours[i]);
			//去除较小轮廓&fitEllipse的限制条件
			if (area < 5 || contours[i].size() <= 1)//因为灯条有大小限制
				continue;
			//用椭圆拟合区域得到外接矩形
			RotatedRect Light_Rec = fitEllipse(contours[i]);
			//长宽比和轮廓面积比限制
			//要考虑到灯条的远近都被识别到,所以只需要看比例即可
			if (Light_Rec.size.width / Light_Rec.size.height > 4)
				continue;
			lightInfos.push_back(LightDescriptor(Light_Rec));
		}
		//二重循环匹配灯条
		for (size_t i = 0; i < lightInfos.size(); i++) {
			for (size_t j = i + 1; j < lightInfos.size(); j++) {
				LightDescriptor& leftLight = lightInfos[i];
				LightDescriptor& rightLight = lightInfos[j];
				float angleGap_ = abs(leftLight.angle - rightLight.angle);
				//由于灯条长度会因为远近而受到影响,所以按照比值去匹配灯条

			}
		}
		//绘制矩形



		namedWindow("video", WINDOW_FREERATIO);
		imshow("video",frame);
		waitKey(5);
	}
}