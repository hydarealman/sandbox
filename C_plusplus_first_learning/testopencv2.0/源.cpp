
#include<opencv2/opencv.hpp>
using namespace cv;

int main() {
	Mat awaw;
	awaw = imread("www.jpg");
	imshow("ºÚºï",awaw);
	waitKey();
	return 0;
}