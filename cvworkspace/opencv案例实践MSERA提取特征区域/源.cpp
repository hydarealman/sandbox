#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;

int main() {
	Mat image = imread("D:/opencv资料库/opencv处理图像/opencv资料库.jpg");
	//基本的MSER检测器
	Ptr<MSER> ptrMSER = MSER::create(5, 200, 2000);
	//点集的容器
	vector<vector<Point>> points;
	//矩形的容器
	vector<Rect> rects;
	//检测MSER特征
	ptrMSER->detectRegions(image, points, rects);
	/*检测结果放在两个容器中。第一个是区域的容器，每个区域用组成它的像素点表示；第二个
	是矩形的容器，每个矩形包围一个区域。为了呈现结果，创建一个空白图像，在图像上用不同的
	颜色显示检测到的区域（颜色是随机选择的）*/
	//创建白色图像
	Mat output(image.size(), CV_8UC3);
	output = Scalar(255, 255, 255);

	//opencv随机数生成器
	RNG rng;

	//针对每个检测到的特征区域,在彩色区域显示MSER
	//反向排序,显示较大的MSER
	for (vector<vector<Point>>::reverse_iterator it = points.rbegin(); it != points.rend(); ++it) {

		//生成随机颜色
		Vec3b c(rng.uniform(0, 254), rng.uniform(0, 254), rng.uniform(0, 254));

		//针对MSER集合中的每个点
		for (vector<Point>::iterator itPts = it->begin(); itPts != it->end(); ++itPts) {
			//不重写MSER像素
			if (output.at<Vec3b>(*itPts)[0] == 255) {
				output.at<Vec3b>(*itPts) = c;
			}
		}
		
		
		////方法一
		/*提取出所有包含垂直矩形的区域。实现方法是将每个矩形的面积与
			检测到的对应区域进行比较，如果两者一致（这里用的判断标准是两者比例超过0.6），那么它就
			是一个MSER*/
		////提取并显示矩形的MSER
		//vector<Rect>::iterator itr = rects.begin();
		//vector<vector<Point>>::iterator itp = points.begin();
		////检查两者比例
		//if (static_cast<double>(itp->size()) / itr->area() > 0.6)
		//	rectangle(image, *itr, Scalar(255), 2);


		//方法二
		/*检测到的
		区域不能太细长（将封闭的矩形旋转，计算其宽高比），然后用未旋转的封闭椭圆表示它们。*/
		//提取并显示椭圆形的MSER
		for (vector<vector<Point>>::iterator it = points.begin(); it != points.end(); ++it) {
			//遍历Mser集合中的每个点
			for (vector<Point>::iterator itPts = it->begin(); itPts != it->end(); ++itPts) {

				//提取封闭的矩形
				RotatedRect rr = minAreaRect(*it);
				//检查椭圆的长宽比
				if (rr.size.width / rr.size.height > 0.6 || rr.size.width / rr.size.height < 1.6)
					ellipse(image, rr, Scalar(255), 2);
			}
		 } 
		

		imshow("MSER特征提取", image);
		waitKey(0);
	}
}