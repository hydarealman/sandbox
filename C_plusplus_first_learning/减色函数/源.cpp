#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
using namespace cv;

void colorReduce(Mat image, int div = 64) {
	int n1 = image.rows;//行数
	int nc = image.cols * image.channels();//每行元素数量
	for (int j = 0; j < n1; j++) {
		//取得行j的地址
		uchar* data = image.ptr<uchar>(j);

		for (int i = 0; i < nc; i++) {
			//处理每个像素
			data[i] = data[i] / div * div + div / 2;
			//像素处理结束
		}//一行结束
	}
}
int main() {
	//读取图像
	Mat image = imread("D:/opencv资料库/opencv处理图像/809-23021G105091Y.png");
	//处理图像
	colorReduce(image, 64);
	//显示图像
	namedWindow("Image",WINDOW_FREERATIO);
	imshow("Image", image);
	waitKey(0);

}