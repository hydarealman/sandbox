#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main() {
	//1.准备标定棋盘图像
	int boardWidth = 7;//棋盘格横向内角点数量
	int boardHeight = 7;//棋盘格纵向内角点数量
	float squareSize = 1.f;//棋盘格格子的大小,单位为米,随便设置不影响
	Size boardSize(boardWidth, boardHeight);

	vector<vector<Point3f>> objectPoints;
	vector<vector<Point2f>> imagePoints;
	vector<Point2f> corners;

	//2.拍摄棋盘图像
	Mat image, gray;
	namedWindow("image", WINDOW_NORMAL);
	vector<String> filenames;
	glob("D:/opencv资料库/opencv处理图像/OIP-C.jpg", filenames);//这里是读取文件夹里面的所有图片
	for (size_t i = 0; i < filenames.size(); i++) {
		image = imread(filenames[i], IMREAD_COLOR);
		cvtColor(image, gray, COLOR_BGR2BGRA);

		//读入图像数据,并提取角点
		bool found = findChessboardCorners(image, boardSize, corners);
		if (found) {
			bool found = findChessboardCorners(image, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);
			imshow("image", image);
			waitKey(0);

			vector<Point3f> objectCorners;
			for (int j = 0; j < boardHeight; j++) {
				for (int k = 0; k < boardWidth; k++) {
					objectCorners.push_back(Point3f(k * squareSize, j * squareSize, 0));
				}
			}
			objectPoints.push_back(objectCorners);
			imagePoints.push_back(corners);
		}
	}
	Mat cameraMatrix, distCoeffs;
	vector<Mat> rvecs, tvecs;
	calibrateCamera(objectPoints, imagePoints, image.size(), cameraMatrix, distCoeffs, rvecs, tvecs);

	cout << "Camera matrix:" << endl << cameraMatrix << endl;
	cout << "Distortion coefficients:" << endl << distCoeffs << endl;

	return 0;
}