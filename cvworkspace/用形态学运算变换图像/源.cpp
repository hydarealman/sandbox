#include<opencv2/opencv.hpp>
using namespace cv;


class WatershedSegmenter {
private:
	Mat markers;

public:
	void setMarkers(const Mat& markerImage) {
		//转换成整数型图像
		markerImage.convertTo(markers, CV_32S);
	}
	Mat process(const Mat& image) {
		//应用分水岭
		watershed(image, markers);
		return markers;
	}
};
int main() {
	////膨胀与腐蚀
	//Mat image = imread("D:/opencv资料库/opencv处理图像/opencv资料库.jpg");
	////腐蚀图像
	////采用默认的3x3结构元素
	//Mat element(7, 7, CV_8U, Scalar(1));
	//Mat eroded;//目标图像
	//erode(image, eroded, element);

	////膨胀图像
	//Mat dilated;//目标图像
	//dilate(image, dilated, element);

	//namedWindow("原图像", WINDOW_FREERATIO);
	//imshow("原图像", image);
	//namedWindow("腐蚀图像", WINDOW_FREERATIO);
	//imshow("腐蚀图像", eroded);
	//namedWindow("膨胀图像", WINDOW_FREERATIO);
	//imshow("膨胀图像", dilated);
	//waitKey(0);



	////开启与闭合滤波器
	//Mat image = imread("D:/opencv资料库/opencv处理图像/opencv资料库.jpg");
	//Mat element(7, 7, CV_8U, Scalar(1));
	//Mat result;
	////膨胀原图像
	//dilate(image, result, element);
	////就地腐蚀膨胀后的图像
	//erode(result, result, element);
	//namedWindow("闭合滤波器", WINDOW_FREERATIO);
	//imshow("闭合滤波器", result);
	//waitKey(0);


	////形态学梯度运算提取图像边缘
	//Mat image1 = imread("C:/Users/dong/Pictures/Screenshots/微信图片_20250215194419.jpg");
	//Mat result1;
	//morphologyEx(image1, result1, MORPH_GRADIENT, Mat());
	//namedWindow("提取图像边缘1", WINDOW_FREERATIO);
	//imshow("提取图像边缘1", result1);
	



	////顶帽变换突出报纸中的文字
	//Mat image2 = imread("C:/Users/dong/Pictures/Screenshots/微信图片_20250215194419.jpg");
	//Mat result2;
	//Mat element7(7, 7, CV_8U, Scalar(1));
	//morphologyEx(image2, result2, MORPH_GRADIENT, element7);
	//namedWindow("提取图像边缘2", WINDOW_FREERATIO);
	//imshow("提取图像边缘2", result2);
	//waitKey(0);




	//分水岭算法实现图像分割
	//封装的类在前面
	Mat image = imread("D:/opencv资料库/opencv处理图像/th.jpg");
	//将图像转化为灰度图像
	Mat binary;
	cvtColor(image, binary, COLOR_BGR2GRAY);
	//消除噪声和细小物体
	Mat fg;
	erode(binary, fg, Mat(), Point(-1, -1), 4);
	//标识不含物体的图像像素
	Mat bg;
	dilate(binary, bg, Mat(), Point(-1, -1), 4);
	threshold(bg, bg, 1, 128, THRESH_BINARY);
	//合并两张图像创建标记图像
	Mat markers(binary.size(), CV_8U, Scalar(0));
	markers = fg + bg;
	//创建分水岭分割类的对象
	WatershedSegmenter segmenter;
	//设置标记图像,然后执行分割过程
	segmenter.setMarkers(markers);
	namedWindow("分水岭算法实现图像分割", WINDOW_FREERATIO);
	imshow("分水岭算法实现图像分割",markers);
	waitKey(0);
}