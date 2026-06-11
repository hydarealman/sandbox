#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;


//实践案例
//int main() {
//	Mat test_image(200, 200, CV_8UC3, Scalar(0));
//	RotatedRect rRect = RotatedRect(Point2f(100, 100), Size2f(100, 50), 30);
//
//	//获得角度
//	cout << rRect.angle << endl;
//
//	//获得中心点
//	cout << rRect.center << endl;
//
//	//获得宽*高
//	cout << rRect.size << endl;
//
//	//获得高
//	cout << rRect.size.height << endl;
//
//	//获得宽
//	cout << rRect.size.width << endl;
//
//	//获得面积
//	cout << rRect.size.area() << endl;
//
//	//绘制旋转矩形
//	Point2f vertices[4];
//	rRect.points(vertices);//求矩形的四个点
//	for (int i = 0; i < 4; i++) {
//		line(test_image, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 2);
//	}
//
//	//圈中这个旋转矩形的外矩形
//	Rect brect = rRect.boundingRect();//求与坐标轴平行的最小外接矩形
//	rectangle(test_image, brect, Scalar(255, 0, 0), 2);
//
//	imshow("旋转矩形",test_image);
//	waitKey(0);
//}


////类成员变量探究
////矩形旋转
//int main() {
//	Mat src(400, 400, CV_8UC1, Scalar::all(0));
//	for (float angle = 0; angle <= 720; angle++) {
//		RotatedRect angle_rotatedRect(Point2f(200, 200), Size2f(50, 100), angle);
//		Point2f vertices[4];
//		angle_rotatedRect.points(vertices);
//		for (int i = 0; i < 4; i++) {
//			line(src, vertices[i], vertices[(i + 1) % 4], Scalar::all(255), 2);
//		}
//
//		RotatedRect points_RotatedRect(vertices[3], vertices[2], vertices[1]);
//		//用角度构造的旋转矩形和用点构造的旋转矩形
//		//角度
//		cout << "角度" << angle << " " << angle_rotatedRect.angle << " " << points_RotatedRect.angle << endl;
//		//宽
//		cout << "宽" << angle_rotatedRect.size.width << " " << points_RotatedRect.size.width << endl;
//		//高
//		cout << "高" << angle_rotatedRect.size.height << " " << points_RotatedRect.size.height << endl;
//		cout << endl;
//
//		
//
//		imshow("src", src);
//		if (waitKey(1) == 'q') return 0;
//		src = Scalar::all(0);
//	}
//	return 0;
//}







