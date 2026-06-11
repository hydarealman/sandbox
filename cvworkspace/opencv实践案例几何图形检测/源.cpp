#include<iostream>
#include<opencv2/opencv.hpp>
//#include<opencv2/imgproc/imgproc.hpp>
//#include<opencv2/highgui/highgui.hpp>
#include<vector>
using namespace std;
using namespace cv;

//opencv轮廓拟合函数实践
int main() {
	//读取二进制图像
	Mat image = imread("D:/opencv资料库/opencv处理图像/th.jpg",0);
	threshold(image,image,180,255,THRESH_BINARY);
	if (!image.data) return 0;
	namedWindow("Binary Image");
	imshow("Binary Image",image);
	
	//获取轮廓和连接部分
	vector<vector<Point>> contours;
	findContours(image,
		contours,				//轮廓向量
		RETR_EXTERNAL,			//检索外部轮廓
		CHAIN_APPROX_NONE);		//检索每个轮廓的所有像素
	cout << "Contours: " << contours.size() << endl;
	vector<vector<Point>>::const_iterator itContours = contours.begin();
	for (; itContours != contours.end(); ++itContours) {
		cout << "Size: " << itContours->size() << endl;
	}
	
	//消除所有过长或过短轮廓
	int cmin = 50;
	int cmax = 500;
	vector<vector<Point>>::iterator itc = contours.begin();
	while (itc!=contours.end()) {
		if (itc != contours.end()) {
			if (itc->size() < cmin || itc->size() > cmax) {
				itc = contours.erase(itc);
			}
			else {
				itc++;
			}
		}
	}
	//绘制轮廓
	Mat result(image.size(), CV_8U, Scalar::all(255));
	drawContours(result, contours,
		-1,				//绘制所有轮廓
		Scalar::all(0),	//颜色
		2);				//线宽为2
	namedWindow("Contours");
	imshow("Contours", result);





	////绘制轮廓
	//Mat original(image.size(),CV_8U,Scalar::all(255));
	//drawContours(original,contours,-1,Scalar(0,0,255),2);
	//namedWindow("Contours on Amimal");
	//imshow("Contours on Amimal", original);
	//result.setTo(Scalar::all(255));
	//drawContours(result,contours,-1,0,1);
	//image = imread("D:/opencv资料库/opencv处理图像/th.jpg",0);
	////矩形
	//Rect r0 = boundingRect(contours[0]);
	//rectangle(result,r0,0,2);
	////圆形
	//float radius;
	//Point2f center;
 //	minEnclosingCircle(contours[1],center,radius);
	////近似多边形
	//vector<Point> poly;
	//approxPolyDP(contours[1],poly,5, radius);
	//polylines(result, poly, true, 0, 2);
	//cout << "Polygon size" << poly.size() << endl;
	////凸包
	//vector<Point> hull;
	//convexHull(contours[3], hull);
	//polylines(result, hull, true, 0, 2);
	////矩
	//itc = contours.begin();
	//while (itc != contours.end()) {
	//	
	//}






	waitKey(0);
}