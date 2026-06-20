#include <iostream> 
#include <opencv2/opencv.hpp>
#include <vector>

// 数据结构，用于存储检测结果
struct FaceDetectionResult {
    std::vector<cv::Rect> faces;
    int centroidX;
    int centroidY;
};

// 人脸检测函数
FaceDetectionResult detectFaces(const cv::Mat& gray, cv::CascadeClassifier& face_cascade, const cv::Mat& frame) {
    // 人脸检测
    std::vector<cv::Rect> faces;
    face_cascade.detectMultiScale(gray, faces, 1.3, 5);

    // 使用图像中心作为默认形心位置
    int centroid_X = frame.cols / 2;
    int centroid_Y = frame.rows / 2;

    if (!faces.empty()) {
        // 计算所有人脸的形心
        float sumX = 0, sumY = 0;
        for (size_t i = 0; i < faces.size(); i++) {
            sumX += faces[i].x + faces[i].width / 2.0f;
            sumY += faces[i].y + faces[i].height / 2.0f;
        }
        //static_cast<int>显式类型转换操作符
        centroid_X = static_cast<int>(sumX / faces.size());
        centroid_Y = static_cast<int>(sumY / faces.size());
    }

    return { faces, centroid_X, centroid_Y };
}

// 绘制结果函数
void drawResults(cv::Mat& frame, const FaceDetectionResult& result) {
    if (!result.faces.empty()) {
        // 绘制检测到的人脸
        for (size_t i = 0; i < result.faces.size(); i++) {
            cv::Rect face = result.faces[i];

            // 使用绿色矩形框住人脸
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);

            // 计算单个人脸中心（红点）
            int X = face.x + face.width / 2;
            int Y = face.y + face.height / 2;
            cv::circle(frame, cv::Point(X, Y), 8, cv::Scalar(0, 0, 255), -1);
        }

        // 绘制形心（蓝色点）
        cv::circle(frame, cv::Point(result.centroidX, result.centroidY), 8, cv::Scalar(255, 0, 0), -1);

        // 在形心位置添加标签
        std::string text = "Center: (" + std::to_string(result.centroidX) + ", " +
            std::to_string(result.centroidY) + ")";
        cv::putText(frame, text, cv::Point(result.centroidX, result.centroidY - 20),
            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 2);
    }

    // 在屏幕上显示检测到的面部数量
    std::string faceCount = "Faces: " + std::to_string(result.faces.size());
    cv::putText(frame, faceCount, cv::Point(10, 30),
        cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 0), 2);

    // 绘制参考矩形
    std::vector<cv::Point> rectangle_pts = {
        cv::Point(0, 0),
        cv::Point(320, 0),
        cv::Point(320, 240),
        cv::Point(0, 240)
    };
    cv::polylines(frame, rectangle_pts, true, cv::Scalar(0, 255, 0), 2);

    std::vector<cv::Point> rectangle_pts2 = {
        cv::Point(320, 240),
        cv::Point(640, 240),
        cv::Point(640, 480),
        cv::Point(320, 480)
    };
    cv::polylines(frame, rectangle_pts2, true, cv::Scalar(0, 255, 0), 2);
}

int main() {
    // 加载人脸检测分类器
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load("D:/opencv/opencv/build/etc/haarcascades/haarcascade_frontalface_default.xml")) {
        std::cerr << "Error loading face cascade" << std::endl;
        std::cerr << "请检查路径是否正确或从以下地址下载文件:" << std::endl;
        std::cerr << "https://github.com/opencv/opencv/blob/master/data/haarcascades/haarcascade_frontalface_default.xml" << std::endl;
        return -1;
    }

    // 打开摄像头
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error opening camera" << std::endl;
        return -1;
    }

    // 设置摄像头分辨率
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) break;

        cv::flip(frame, frame, 1);

        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);  // 灰度转换

        // 检测人脸
        FaceDetectionResult result = detectFaces(gray, face_cascade, frame);

        // 绘制结果
        drawResults(frame, result);

        // 显示结果
        cv::imshow("Face Detection", frame);

        // 打印形心坐标
        std::cout << "X = " << result.centroidX << "\tY = " << result.centroidY << std::endl;

        // 按ESC退出
        if (cv::waitKey(5) == 27) {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}