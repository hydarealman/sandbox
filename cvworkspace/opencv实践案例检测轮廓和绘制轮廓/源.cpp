#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>
using namespace cv;
using namespace std;
#define PI 3.14

int main() {
	////Canny算法
	////它的核心理念是用两个不同的阈值来判断哪个点属于轮廓，一个是低阈值，一个是高阈值。
	//Mat image = imread("D:/opencv资料库/opencv处理图像/th.jpg");
	//Mat contours;
	//Canny(image, contours, 125, 350);//灰度图像//输出轮廓//低阈值//高阈值
	//imshow("Canny算法演示", contours);
	//waitKey(0);




	//霍夫变换没搞懂
	////检测直线的霍夫变换
	////应用Cannny算法
	//Mat image = imread("D:/opencv资料库/opencv处理图像/th (1).jpg");
	//Mat contours;
	//Canny(image,contours,125,350);
	////用霍夫变换检测直线
	//vector<Vec2f> lines;
	//Mat test;
	//Mat gray;
	//Mat result;
	//cvtColor(image, gray, COLOR_BGR2GRAY);
	//threshold(gray,result,70,255,THRESH_BINARY);
	////waitKey(0);
	//
	//
	//HoughLines(result, lines, 5, PI / 180*100, 90);
	////通过遍历直线向量划出所有直线
	//vector<Vec2f>::const_iterator it = lines.begin();
	////Mat result(image.size(), image.type(), Scalar(255));
	//while (it != lines.end()) {

	//	float rho = (*it)[0];		//第一个元素是距离tho
	//	float theta = (*it)[1];		//第二个元素是角度theta

	//	if (theta < PI / 4. || theta > 3. * PI / 4.) {//垂直线大致
	//		//直线与第一行的交叉点
	//		Point pt1(rho / cos(theta), 0);
	//		//直线与最后一行的交叉点
	//		Point pt2((rho - result.rows * sin(theta)) / cos(theta), result.rows);
	//		//画白色的线
	//		line(image, pt1, pt2, Scalar(255,255,255), 1);
	//		//imshow("image", image);
	//		//waitKey(0);
	//	}
	//	else {//水平线(大致)
	//		//直线与第一列的交叉点
	//		Point pt1(0, rho / sin(theta));
	//		//直线与最后一列的交叉点
	//		Point pt2(result.cols, rho - result.cols * cos(theta) / sin(theta));
	//		//画白色的线
	//		line(image,pt1,pt2,Scalar(255,255,255),1);
	//	}
	//	++it;
	//}
	//imshow("霍夫变换绘制结果",image);
	//cout << lines.size() << endl;
	//waitKey(0);


	////基本没看懂
	////创建霍夫累加器
	////这里的图像类型为uchar,实际使用时应该用int
	//Mat acc(200, 180, CV_8U, Scalar(0));

	////选取一个像素点
	//int x = 50, y = 30;
	////循环遍历所有角度
	//for (int i = 0; i < 180; i++) {
	//	double theta = i * PI / 180;

	//	//找到对应rho值
	//	double rho = x * cos(theta) + y * sin(theta);
	//	//j对应-100~100的rho值
	//	int j = static_cast<int>(rho + 100.5);
	//	cout << i << "," << j << endl;
	//	//增值累加器
	//	acc.at<uchar>(j, i)++;
	//}



	//拟合最适合指定点集的直线
	//略,搞不懂


	//在二维点集上拟合一个椭圆
	//RotatedRect rrect = fitEllipse(Mat(Points));
	//ellipse(image, rrect, Scalar(0));



	//提取连续区域
	//用于存储轮廓的向量
	vector<vector<Point>> contours;
	Mat image = imread("D:/opencv资料库/opencv处理图像/th.jpg");
	cvtColor(image, image, COLOR_BGR2GRAY);
	threshold(image, image, 185, 255, THRESH_BINARY);
	findContours(image, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);//存储轮廓的向量//检索外部轮廓//每个轮廓的全部像素
	//画出区域轮廓
	Mat result = Mat::zeros(image.size(), CV_8UC1);
	result.setTo(Scalar(255, 255, 255));
	drawContours(result,contours,-1,0,2);//画全部轮廓//用黑色画//宽度为2
	




//你也可以对识别出的连续区域进行独立的分析。例如，如果事先已经知道感兴趣物体的大小，
//就可以将部分区域删除。我们采用区域边界的最小值和最大值，具体做法是迭代遍历存放轮廓的
//向量，并且删除无效的轮廓：
//删除太短或太长的轮廓
int cmin = 50;		//最小轮廓长度
int cmax = 1000;	//最大轮廓长度
//vector<vector<Point>>::iterator itc = contours.begin();
////针对所有轮廓
//while (itc != contours.end()) {
//	//验证轮廓大小
//	if (itc->size() < cmin || itc->size() > cmax) {
//		itc = contours.erase(itc);
//	}
//	else {
//		++itc;
//	}
//}

imshow("轮廓绘制演示", result);
waitKey(0);



//findContours函数检测二值图像的所有闭合轮廓
//Mat image = imread("D:/opencv资料库/opencv处理图像/th (1).jpg");
//cvtColor(image, image, COLOR_BGR2GRAY);
//threshold(image,image,200,255,THRESH_BINARY);
//vector<vector<Point>> contours;
//findContours(image, contours,RETR_LIST,CHAIN_APPROX_NONE);
//Mat result = Mat::zeros(image.size(),CV_8UC1);
//result.setTo(Scalar(255, 255, 255));
//drawContours(result,contours,-1,0,2);
//cout << contours.size() << endl;

//计算区域的形状描述子
//测试边界框
Rect r0 = boundingRect(contours[0]);
//画矩形
rectangle(result, r0,0,2);

//测试覆盖圆
float radius;
Point2f center;
minEnclosingCircle(contours[1], center, radius);
//画圆形
circle(result,center,static_cast<int>(radius),Scalar(0),2);

//计算区域轮廓的多边形逼近
vector<Point> poly;
approxPolyDP(contours[2], poly, 5, true);
//画多边形
polylines(result, poly, true, 0, 2);
//测试凸包
vector<Point> hull;
convexHull(contours[3], hull);
//画多边形
polylines(result, hull, true, 0, 2);
//测试轮廓矩
//迭代遍历所有轮廓
vector<vector<Point>>::iterator itc = contours.begin();
while (itc != contours.end()) {

	//计算所有轮廓矩
	Moments mom = moments(Mat(*itc++));

	//画重心
	circle(result,
		//将重心位置转换成整数
		Point(mom.m10/mom.m00,mom.m01/mom.m00),2,Scalar(0),2);//画黑点
}

//识别凸包缺陷
vector<Vec4i> defects;
convexityDefects(contours,hull,defects);

imshow("检测二值图像的所有闭合轮廓", result);
waitKey(0);
}

