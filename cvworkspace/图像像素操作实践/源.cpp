#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
//#include<string_view>
//#include<iostream>
using namespace cv;
//void salt(cv::Mat image, int n) {
//    std::default_random_engine generator;
//    std::uniform_int_distribution<int>
//        randomRow(0, image.rows - 1);
//    std::uniform_int_distribution<int>
//        randomCol(0, image.cols - 1);
//    int i, j;
//    for (int k = 0; k < n; k++) {
//        // 随机生成图形位置
//            i = randomCol(generator);
//        j = randomRow(generator);
//        if (image.type() == CV_8UC1) { // 灰度图像 
//            // 单通道8位图像 
//            image.at<uchar>(j, i) = 255;
//        }
//        else if (image.type() == CV_8UC3) { // 彩色图像 
//            // 3 通道图像 
//            image.at<cv::Vec3b>(j, i)[0] = 255;
//            image.at<cv::Vec3b>(j, i)[1] = 255;
//            image.at<cv::Vec3b>(j, i)[2] = 255;
//        }
//    }
//}
int main() {
	Mat M;
	M.at<uchar>(512 - 1, 512 * 3 - 1);
	M.at<Vec3b>(512 - 1, 512 - 1)[2];
}