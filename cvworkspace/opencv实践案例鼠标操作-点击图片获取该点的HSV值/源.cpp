#include<opencv2/opencv.hpp>
#include<vector>

using namespace cv;
using namespace std;

vector<Point> selectedRegion;
bool selectingRegion = false;
int h_lower = 0, h_upper = 179;
int s_lower = 0, s_upper = 255;
int v_lower = 0, v_upper = 255;

void on_Mouse(int event, int x, int y, int flage, void* userdata) {
	Mat* frame = (Mat*)userdata;
	if (event == EVENT_LBUTTONDOWN) {
		selectingRegion = true;
		selectedRegion.clear();
		selectedRegion.push_back(Point(x, y));
	}
	else if (event == EVENT_MOUSEMOVE && selectingRegion) {
		selectedRegion.push_back(Point(x,y));
	}
	else if (event == EVENT_LBUTTONUP) {
		selectingRegion = false;
		selectedRegion.push_back(Point(x, y));

		//创建一个掩膜,初始值为零
		Mat mask = Mat::zeros(frame->size(), CV_8UC1);

		vector<vector<Point>> poly;
		poly.push_back(selectedRegion);
		fillPoly(mask, poly, Scalar(255));

		//计算所选区域的HSV范围
		Mat hsv, roi;
		cvtColor(*frame, hsv, COLOR_BGR2HSV);
		hsv.copyTo(roi, mask);  // 只保留选定区域的HSV值
		Scalar meanScalar = mean(roi, mask);
		//计算hsv范围
		h_lower = max(0, static_cast<int>(meanScalar[0]) - 10);
		h_upper = min(179, static_cast<int>(meanScalar[0]) + 10);
		s_lower = max(0, static_cast<int>(meanScalar[1]) - 50);
		s_upper = min(255, static_cast<int>(meanScalar[1]) + 50);
		v_lower = max(0, static_cast<int>(meanScalar[2]) - 50);
		v_upper = min(255, static_cast<int>(meanScalar[2]) + 50);
		//更新滑动条
		setTrackbarPos("Hue Lower", "Trackbars", h_lower);
		setTrackbarPos("Hue Upper", "Trackbars", h_upper);
		setTrackbarPos("Sat Lower", "Trackbars", s_lower);
		setTrackbarPos("Sat Upper", "Trackbars", s_upper);
		setTrackbarPos("Val Lower", "Trackbars", v_lower);
		setTrackbarPos("Val Upper", "Trackbars", v_upper);
	}
}

void on_trackbar(int, void*) {
	//在这里处理滑动条数值改变时的逻辑
}

int main() {
	VideoCapture cap(0);
	if (!cap.isOpened()) {
		return -1;
	}
	//WINDOW_NORMAL是namedWindow函数中的一个标志，表示窗口可以被用户调整大小。它允许用户通过拖动窗口边缘来改变窗口的尺寸
	namedWindow("Original", WINDOW_NORMAL);
	namedWindow("Trackbars", WINDOW_NORMAL);

	createTrackbar("Hue Lower", "Trackbars", &h_lower, 179, on_trackbar);
	createTrackbar("Hue Upper", "Trackbars", &h_upper, 179, on_trackbar);
	createTrackbar("Sat Lower", "Trackbars", &s_lower, 255, on_trackbar);
	createTrackbar("Sat Upper", "Trackbars", &s_upper, 255, on_trackbar);
	createTrackbar("Val Lower", "Trackbars", &v_lower, 255, on_trackbar);
	createTrackbar("Val Upper", "Trackbars", &v_upper, 255, on_trackbar);
	
	Mat frame, hsv, mask, result;
	while (true) {
		cap.read(frame);
		if (frame.empty()) {
			break;
		}

		setMouseCallback("Original", on_Mouse, &frame);
		cvtColor(frame, hsv, COLOR_BGR2HSV);
		inRange(hsv, Scalar(h_lower, s_lower, v_lower), Scalar(h_upper, s_upper, v_upper), mask);

		bitwise_and(frame, frame, result, mask);//使用掩码来获取结果
		imshow("Original", frame);
		resizeWindow("Original", 640, 480);

		imshow("Result", result);//显示处理结果
		imshow("mask", mask);

		if (waitKey(1) == 27) {
			break;
		}

	}
	cap.release();
	destroyAllWindows();

	return 0;
}
