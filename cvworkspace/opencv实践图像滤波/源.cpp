#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

//计算拉普拉斯算子
//关于拉普拉斯算子简单的类
class LaplacianZC {
private:
	//拉普拉斯算子
	Mat laplace;
	//拉普拉斯内核的孔径大小
	int aperture;
public:
	LaplacianZC() : aperture(3) {}

	//设置内核的孔径大小
	void setAperture(int a) {
		aperture = a;
	}
	//计算浮点数类型的拉普拉斯算子
	Mat computeLaplacian(const Mat& image) {
		//计算拉普拉斯算子
		Laplacian(image, laplace, CV_32F, aperture);
		return laplace;
	}

//获得拉普拉斯结果,存在8位图像中
//0表示灰度级128
//如果不指定缩放比例,那么最大值会放大到255
//在调用这个函数之前,必须先调用computeLaplacian
	Mat getLaplacianImage(double scale = -1.0) {
		if (scale < 0) {
			double lapmin, lapmax;
			//取得最小和最大拉普拉斯值
			minMaxLoc(laplace, &lapmin, &lapmax);
			//缩放拉普拉斯算子到127
			scale = 127 / max(-lapmin, lapmax);
		}
		//生成灰度图像
		Mat laplaceImage;
		laplace.convertTo(laplaceImage, CV_8U, scale, 128);
		return laplaceImage;
}
	//获得过零点的二值图像
//获得拉普拉斯图像的类型必须时CV_32F
	Mat getZeroCrossings(Mat laplace) {
		//阈值为零
		//负数用黑色
		//正数用白色
		Mat signImage;
		threshold(laplace, signImage, 0, 255, THRESH_BINARY);

		//把+/-图像转换成CV_8U
		Mat binary;
		signImage.convertTo(binary, CV_8U);
		//膨胀+/-区域的二值图像
		Mat dilated;
		dilate(binary, dilated, Mat());

		//返回过零点的轮廓
		return dilated - binary;
	}
};




int main() {
	////低通滤波器
	//Mat image = imread("D:/opencv资料库/opencv处理图像/th.jpg");
	//Mat result;
	//blur(image, result, Size(5, 5));
	//imshow("原图像", image);
	//imshow("低通滤波器演示图像", result);
	//waitKey(0);

	////高斯模糊
	///*有时需要让邻域内较近的像素具有更高的重要度。因此可计算加权平均值，即较近的像素比较远的像素具有更大的权重*/
	//Mat image = imread("D:/opencv资料库/opencv处理图像/th.jpg");
	//Mat result;
	//GaussianBlur(image, result, Size(5, 5), 1.5);
	//imshow("原图像", image);
	//imshow("高斯模糊演示图像", result);
	//waitKey(0);

	//实现缩小图像
	//首先去除高频成分
	/*为避免混叠现象的发生，在缩减图像之前必须进行低通滤波。前面说过，低通滤波的作用是
	消除在缩减后的图像中无法表示的高频部分。这一现象称为Nyquist - Shannon定理，它表明如果
	把图像缩小一半，那么其可见的频率带宽也将减少一半*/
	//Mat image = imread("D:/opencv资料库/opencv处理图像/th.jpg");
	//GaussianBlur(image, image, Size(11, 11), 2.0);
	////只保留每四个像素中的1个
	//Mat reduced(image.rows / 4, image.cols / 4, CV_8U);
	//for (int i = 0; i < reduced.rows; i++) {
	//	for (int j = 0; j < reduced.cols; j++) {
	//		reduced.at<uchar>(i, j) = image.at<uchar>(i * 4, j * 4);
	//	}
	//}
	////图像插值 最邻近策略
	////按比例缩放图像后，必须进行像素插值，以便在原像素之间的位置插入新的像素值
	//Mat newImage;
	//resize(reduced, newImage, Size(), 3, 3, INTER_NEAREST);
	//imshow("缩小后的图像", reduced);
	//waitKey(0);

	//还有其他插值算法  例如   双三次插值算法......


	////OpenCV中有一个专用函数，利用这个原理实现了图像缩减，即cv::pyrDown函数：
	//Mat image = imread("D:/opencv资料库/opencv处理图像/th.jpg");
	//Mat reducedImage;
	//pyrDown(image, reducedImage);
	//imshow("缩小后的图像", reducedImage);
	//waitKey(0);

	////指定缩放后图像的尺寸
	//Mat image = imread("D:/opencv资料库/opencv处理图像/th.jpg");
	//Mat resizedImage;			//用于存储缩放后的图像
	//resize(image,resizedImage,Size(image.cols/4,image.rows/4));//行和列均缩小为原来的1/4
	//imshow("缩小后的图像", resizedImage);
	//waitKey(0);



	////中值滤波器
	//Mat image = imread("D:/opencv资料库/opencv处理图像/th.jpg");
	//Mat result;			
	//medianBlur(image, result, 5);
	//imshow("缩小后的图像", result);
	//waitKey(0);



	////用定向滤波器检测边缘
	////Sobel滤波器,只对垂直或水平方向的图像频率起作用(具体方向取决于滤波器选用的内核)
	//Mat image = imread("D:/opencv资料库/opencv处理图像/th.jpg");
	//Mat sobelX;			
	//Sobel(image, sobelX, CV_8U, 1, 0, 3, 0.4, 128);
	//Mat sobelY;
	//Sobel(image, sobelY, CV_8U, 0, 1, 3, 0.4, 128);
	//imshow("水平方向滤波图像", sobelX);
	//imshow("垂直方向滤波图像", sobelY);
	//waitKey(0);
	
	 
	
	
	////计算Sobel滤波器的范数
	//Mat image = imread("D:/opencv资料库/opencv处理图像/th.jpg");
	//
	//Mat sobelX;
	//Mat sobelY;
	//Sobel(image, sobelX, CV_16S, 1, 0);
	//Sobel(image, sobelY, CV_16S, 0, 1);
	//Mat sobel;
	////计算L1范数
	//sobel = abs(sobelX) + abs(sobelY);
	////找到Sobel最大值
	//double sobmin, sobmax;
	//minMaxLoc(sobel, &sobmin, &sobmax);
	////转换成8位图像
	//Mat sobelImage;
	//sobel.convertTo(sobelImage, CV_8U, -255./sobmax, 255);
	////imshow("8位图像", sobelImage);
	//cvtColor(sobelImage, sobelImage, COLOR_BGR2GRAY);
	//Mat sobelThresholded;
	//threshold(sobelImage, sobelThresholded, 208, 250, THRESH_BINARY);
	//imshow("二值化图像",sobelThresholded);
	//waitKey(0);



////计算Sobel算子,必须用浮点数
//Mat image = imread("D:/opencv资料库/opencv处理图像/th.jpg");
//Mat sobelX;
//Mat sobelY;
//// 计算Sobel 算子，必须用浮点数类型  
//cv::Sobel(image, sobelX, CV_32F, 1, 0);
//cv::Sobel(image, sobelY, CV_32F, 0, 1);
//// 计算梯度的L2范数和方向 
//cv::Mat norm, dir;
//// 将笛卡儿坐标换算成极坐标，得到幅值和角度 
//cv::cartToPolar(sobelX, sobelY, norm, dir);
//cout << norm << endl;
//cout << dir << endl;
//waitKey(0);



////使用类,从7x7内核计算拉普拉斯图像的方法为:
////用LaplacianZC类计算拉普拉斯算子
//Mat image = imread("D:/opencv资料库/opencv处理图像/th.jpg");
//Mat laplace;
//LaplacianZC laplacian;
//laplacian.setAperture(7);    //7x7的拉普拉斯算子
//Mat flap = laplacian.computeLaplacian(image);
//laplace = laplacian.getLaplacianImage();
//imshow("拉普拉斯算子图像滤波", laplace);
//waitKey(0);



////在拉普拉斯图像上追踪过零点曲线
////这种算法首先对拉普拉斯图像阈值化（采用的阈值为 0），得到正数和负数之间
////的分割区域，这两个区域之间的边界就是过零点。所以，我们可以用形态学运算来提取这些轮廓，
////也就是用拉普拉斯图像减去膨胀后的图像（这是5.4节中介绍的Beucher梯度）。下面的方法实现
////了这个算法，生成了一个过零点的二值图像：
//Mat image = imread("D:/opencv资料库/opencv处理图像/th.jpg");
//Mat laplace;
//LaplacianZC laplacian;
//laplacian.setAperture(7);    //7x7的拉普拉斯算子
//Mat flap = laplacian.computeLaplacian(image);
//laplace = laplacian.getLaplacianImage();
//Mat result = getZeroCrossings(laplace);
//imshow("拉普拉斯图像上追踪过零点", result);
//waitKey(0);



//高斯差分
Mat image = imread("D:/opencv资料库/opencv处理图像/th.jpg");
Mat gauss20, gauss22;
GaussianBlur(image, gauss20, Size(), 2.0);
GaussianBlur(image, gauss22, Size(), 2.2);
LaplacianZC laplacian;

//计算高斯差分
Mat dog;
subtract(gauss22, gauss20, dog, Mat(), CV_32F);

//计算DOG的过零点
Mat zeros;
zeros = laplacian.getZeroCrossings(dog);
imshow("高斯差分演示", zeros);
waitKey(0);
}