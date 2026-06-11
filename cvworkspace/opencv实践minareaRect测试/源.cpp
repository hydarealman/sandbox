#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

#define W_CONVEX "RESULT"


//随机数生成点集
//绘制计算给定点集或轮廓的最小外接矩形
int main() {
	Mat image = Mat::zeros(600, 600, CV_8UC3);
	
	RNG& rng = theRNG();//???
	

	while (1) {
		char key;

		int count = (unsigned)rng % 100 + 3;
		vector<Point>points;

		for (int i = 0; i < count; i++) {
			Point point;
			point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);
			circle(image, point, 2, Scalar::all(255), 2);
			points.push_back(point);
		}

		RotatedRect rotatedRect = minAreaRect(points);//用于计算给定集的最小外接矩形
		Point2f hull[4];
		rotatedRect.points(hull);
		for (int i = 0; i < 4; i++) {
			line(image, hull[i], hull[(i + 1) % 4], Scalar::all(255), 2);
		}
		cout << "RotatedRect's angle:" << rotatedRect.angle << endl;
		cout << "RotatedRect's width:" << rotatedRect.size.width << endl;
		cout << "RotatedRect's height:" << rotatedRect.size.height << endl;
		cout << endl;
		
		namedWindow(W_CONVEX, WINDOW_NORMAL);
		imshow(W_CONVEX, image);

		image = Scalar::all(0);

		if (waitKey() == 'q') return 0;
	}



	return 0;
}


//改变angle,采用角度规则