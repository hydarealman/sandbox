#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
int main() {
	Mat img = imread("www.jpg");
	namedwindow("ºÚºïÍ¼Æ¬");
	imshow("ºÚºïÍ¼Æ¬", img);
	waitkey(6000);
	return 0;
}