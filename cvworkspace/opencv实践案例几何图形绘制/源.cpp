#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main() {
	//创建空白图像
	Mat result(Size(400, 400), CV_8UC3);
	result.setTo(Scalar(255, 255, 255));
	

	//绘制直线
	Point point1(200, 200);
	Point point2(400, 400);
	line(result, point1, point2, Scalar(255, 0, 0), 5);
	//绘制圆形
	circle(result, point1, 200, Scalar(0, 0, 255), 5);
	//绘制矩形
	rectangle(result, point1, point2, Scalar(0, 255, 0), 5);
	//绘制椭圆
	ellipse(result,point1,Size(50,20),0,0,360,Scalar(255,255,0));
	//绘制多边形
	vector<Point> pts;
	pts.push_back(Point(25,25));
	pts.push_back(Point(25,0));
	pts.push_back(Point(0,25));
	polylines(result,pts,true,Scalar(0,0,255),5,LINE_4);
	//绘制文本函数
	putText(result,"hello world!",Point(200,200),FONT_HERSHEY_SIMPLEX,1,Scalar(255,0,0),1);

	//演示结果
	imshow("图像绘制演示", result);
	waitKey(0);
}