#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

int main() {
	//定义棋盘格参数
	const int board_w = 16, board_h = 16;//每行的角点个数，每列的角点个数
	const int board_n = board_w * board_h;//总角点个数
	Size board_size(16, 16);//棋盘格尺寸

	Mat gray_img, draw_img;
	vector<Point2f> point_pix_pos_buf;//单张图的像素角点
	vector<vector<Point2f>> point_pix_pos;//所有成功图像的像素角点

	int found, successes = 0;//是否找到角点//成功标定的图像数
	Size img_size;//图像尺寸

	//感觉这个cnt写的没有什么卵用
	int cnt = 0;
	int k = 0, n = 0;
	//for (int i = 0; i < 1; i++) {//20张图片
	Mat src0 = imread("D:/chessboard_image/5f19f8-main/标定图片/标定图片/chess_board.jpg");//读取图像0.jpg到19.jpg

	//if (!cnt) {//如果cnt等于0//也就是读取第一张图片的时候
		img_size.width = src0.cols;
		img_size.height = src0.rows;
	//}
	found = findChessboardCorners(src0, board_size, point_pix_pos_buf);//检测棋盘格角点的函数
	if (found && point_pix_pos_buf.size() == board_n) {//检测成功,并且所有角点都被检测到了
		successes++;//成功标定的图像加1
		cvtColor(src0, gray_img, COLOR_BGR2GRAY);
		find4QuadCornerSubpix(gray_img, point_pix_pos_buf, Size(5, 5));//初始的角点坐标作为 输入,优化后的 角点坐标作为输出
		point_pix_pos.push_back(point_pix_pos_buf);
		draw_img = src0.clone();
		drawChessboardCorners(draw_img, board_size, point_pix_pos_buf, found);//在图像上绘制检测到的角点函数
		imshow("corners", draw_img);
		waitKey(50);
	}
	else {
		cout << "\tbut failed to found all chess board corners in this image" << endl;
	}
	point_pix_pos_buf.clear();
	//cnt++;
//}
	std::cout << successes << " useful chess boards" << std::endl;

	Size squares_size(10, 10);//棋盘格每个方格的物理尺寸
	vector<vector<Point3f>> point_grid_pos;//单张图像对应的角点坐标缓存
	vector<Point3f> point_grid_pos_buf;//所有图像对应的角点坐标缓存
	vector<int> point_count;

	Mat camera_matrix(3, 3, CV_32FC1, Scalar::all(0));//存内参矩阵
	Mat dist_coeffs(1, 5, CV_32FC1, Scalar::all(0));//存畸变系数
	
	//外参
	vector<Mat> rvecs;//旋转向量
	vector<Mat> tvecs;//平移向量

	//通过多张不同视角的图像,计算相机如何将三维世界投影到二维图像的
	//生成标定用的棋盘的三维坐标
	for (int i = 0; i < successes; i++) {//遍历标记成功的图像
		for (int j = 0; j < board_h; j++) {
			for (int k = 0; k < board_w; k++) {
				Point3f pt;
				pt.x = k * squares_size.width;
				pt.y = j * squares_size.height;
				pt.z = 0;
				point_grid_pos_buf.push_back(pt);
			}
		}
		point_grid_pos.push_back(point_grid_pos_buf);
		point_grid_pos_buf.clear();
		point_count.push_back(board_h * board_w);
	}
	calibrateCamera(point_grid_pos, point_pix_pos,img_size, camera_matrix, dist_coeffs, rvecs,tvecs);
	cout << camera_matrix << dist_coeffs << endl;
	return 0;
}