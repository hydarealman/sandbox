#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	string pb_file_path = "D:/cvworkspace/opencv_tutorial_data-master/models/face_detector/opencv_face_detector_uint8.pb";
	string pbtxt_file_path = "D:/cvworkspace/opencv_tutorial_data-master/models/face_detector/opencv_face_detector.pbtxt";
	cv::dnn::Net net = cv::dnn::readNetFromTensorflow(pb_file_path, pbtxt_file_path);
	VideoCapture cap(0);
	Mat frame;
	while (true) {
		cap.read(frame);
		flip(frame, frame, 1);
		if (frame.empty()) {
			break;
		}
		Mat blob = cv::dnn::blobFromImage(frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false);
		net.setInput(blob);
		Mat probs = net.forward();
		Mat detectMat(probs.size[2], probs.size[3], CV_32F, probs.ptr<float>());
		for (int row = 0; row < detectMat.rows; row++) {
			float conf = detectMat.at<float>(row, 2);
			if (conf > 0.5) {
				float x1 = detectMat.at<float>(row, 3) * frame.cols;
				float y1 = detectMat.at<float>(row, 4) * frame.rows;
				float x2 = detectMat.at<float>(row, 5) * frame.cols;
				float y2 = detectMat.at<float>(row, 6) * frame.rows;
				cv::Rect box(x1, y1, x2 - x1, y2 - y1);
				cv::rectangle(frame, box, Scalar(0, 0, 255), 2, 8);
			}
		}
		cv::imshow("Opencv4.8 DNN »À¡≥ºÏ≤‚—› æ", frame);
		char c = waitKey(1);
		if (c == 27) {
			break;
		}
	}
	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}