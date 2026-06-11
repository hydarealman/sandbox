#include<iostream>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/opencv.hpp>
using namespace cv;
using namespace std;

//用迭代器扫描图像
//实现减色函数
void colorReduce(Mat image, int div = 64) {
	//div必须是2的幂
	int n = static_cast<int>(log(static_cast<double>(div))/log(2.0) + 0.5);
	//用来截取像素值的掩码
	uchar mask = 0XFF << n;
	uchar div2 = div >> 1;
	//迭代器
	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = image.end<Vec3b>();

	for (; it != itend; ++it) {
		(*it)[0] &= mask;
		(*it)[0] += div2;
		(*it)[1] &= mask;
		(*it)[1] += div2;
		(*it)[2] &= mask;
		(*it)[2] += div2;
	}
}


int main() {

}