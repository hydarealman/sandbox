//#include <iostream> 
//#include <opencv2/opencv.hpp>
//#include <vector>
//
//// 数据结构，用于存储检测结果
//struct FaceDetectionResult {
//    std::vector<cv::Rect> faces;
//    int centroidX;
//    int centroidY;
//};
//
////人脸检测函数第一版(无法识别近处人脸误识别,远处人脸识别不到)
////// 人脸检测函数
////FaceDetectionResult detectFaces(const cv::Mat& gray, cv::CascadeClassifier& face_cascade, const cv::Mat& frame) {
////    // 人脸检测
////    std::vector<cv::Rect> faces;
////    face_cascade.detectMultiScale(gray, faces, 1.05, 4.5,0,cv::Size(30,30));
////
////    // 使用图像中心作为默认形心位置
////    int centroid_X = frame.cols / 2;
////    int centroid_Y = frame.rows / 2;
////
////    if (!faces.empty()) {
////        // 计算所有人脸的形心
////        float sumX = 0, sumY = 0;
////        for (size_t i = 0; i < faces.size(); i++) {
////            sumX += faces[i].x + faces[i].width / 2.0f;
////            sumY += faces[i].y + faces[i].height / 2.0f;
////        }
////        //static_cast<int>显式类型转换操作符
////        centroid_X = static_cast<int>(sumX / faces.size());
////        centroid_Y = static_cast<int>(sumY / faces.size());
////    }
////
////    return { faces, centroid_X, centroid_Y };
////}
////
//// 绘制结果函数
//void drawResults(cv::Mat& frame, const FaceDetectionResult& result) {
//    if (!result.faces.empty()) {
//        // 绘制检测到的人脸
//        for (size_t i = 0; i < result.faces.size(); i++) {
//            cv::Rect face = result.faces[i];
//
//            // 使用绿色矩形框住人脸
//            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
//
//            // 计算单个人脸中心（红点）
//            int X = face.x + face.width / 2;
//            int Y = face.y + face.height / 2;
//            cv::circle(frame, cv::Point(X, Y), 8, cv::Scalar(0, 0, 255), -1);
//        }
//
//        // 绘制形心（蓝色点）
//        cv::circle(frame, cv::Point(result.centroidX, result.centroidY), 8, cv::Scalar(255, 0, 0), -1);
//
//        // 在形心位置添加标签
//        std::string text = "Center: (" + std::to_string(result.centroidX) + ", " +
//            std::to_string(result.centroidY) + ")";
//        cv::putText(frame, text, cv::Point(result.centroidX, result.centroidY - 20),
//            cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 2);
//    }
//
//    // 在屏幕上显示检测到的面部数量
//    std::string faceCount = "Faces: " + std::to_string(result.faces.size());
//    cv::putText(frame, faceCount, cv::Point(10, 30),
//        cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 0), 2);
//
//    // 绘制参考矩形
//    std::vector<cv::Point> rectangle_pts = {
//        cv::Point(0, 0),
//        cv::Point(160, 0),
//        cv::Point(160, 120),
//        cv::Point(0, 120)
//    };
//    cv::polylines(frame, rectangle_pts, true, cv::Scalar(0, 255, 0), 2);
//
//    std::vector<cv::Point> rectangle_pts2 = {
//        cv::Point(160, 120),
//        cv::Point(320, 120),
//        cv::Point(320, 240),
//        cv::Point(160, 240)
//    };
//    cv::polylines(frame, rectangle_pts2, true, cv::Scalar(0, 255, 0), 2);
//}
//
//FaceDetectionResult detectFaces(const cv::Mat& frame, cv::CascadeClassifier& face_cascade) {
//    // 预处理
//    cv::Mat gray;
//    cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
//
//    // 增强处理
//    cv::Mat enhanceImg;
//    cv::equalizeHist(gray, enhanceImg);
//    cv::GaussianBlur(enhanceImg, enhanceImg, cv::Size(3, 3), 0);
//
//    // 人脸检测
//    std::vector<cv::Rect> allFaces;
//    face_cascade.detectMultiScale(
//        enhanceImg,
//        allFaces,
//        1.1,
//        6,
//        0,
//        cv::Size(20, 20)
//    );
//
//    // 多级筛选
//    std::vector<cv::Rect> validFaces;
//    for (const auto& face : allFaces) {
//        // 宽高比筛选
//        float aspect_ratio = static_cast<float>(face.width) / face.height;
//        if (aspect_ratio < 0.8 || aspect_ratio > 1.8) continue;
//
//        // 面积占比筛选
//        float area_ratio = face.area() / static_cast<float>(frame.total());
//        if (area_ratio > 0.4) continue;
//
//        validFaces.push_back(face);
//    }
//
//    // 皮肤区域验证
//    std::vector<cv::Rect> filteredFaces;
//    for (const auto& face : validFaces) {
//        cv::Mat faceROI = frame(face);
//        cv::Mat hsv;
//        cv::cvtColor(faceROI, hsv, cv::COLOR_BGR2HSV);
//
//        cv::Mat skinMask;
//        cv::inRange(hsv, cv::Scalar(0, 48, 80), cv::Scalar(25, 255, 255), skinMask);
//
//        // 皮肤像素比例要求
//        double skinRatio = static_cast<double>(cv::countNonZero(skinMask)) / faceROI.total();
//        if (skinRatio < 0.4) continue;
//
//        filteredFaces.push_back(face);
//    }
//
//    // 形心计算（同原函数）
//    int centroid_X = frame.cols / 2;
//    int centroid_Y = frame.rows / 2;
//
//    if (!filteredFaces.empty()) {
//        float sumX = 0, sumY = 0;
//        for (size_t i = 0; i < filteredFaces.size(); i++) {
//            sumX += filteredFaces[i].x + filteredFaces[i].width / 2.0f;
//            sumY += filteredFaces[i].y + filteredFaces[i].height / 2.0f;
//        }
//        centroid_X = static_cast<int>(sumX / filteredFaces.size());
//        centroid_Y = static_cast<int>(sumY / filteredFaces.size());
//    }
//
//    return { filteredFaces, centroid_X, centroid_Y };
//}
//
//int main() {
//    // 加载人脸检测分类器
//    cv::CascadeClassifier face_cascade;
//    if (!face_cascade.load("D:/opencv/opencv/build/etc/haarcascades/haarcascade_frontalface_default.xml")) {
//        std::cerr << "Error loading face cascade" << std::endl;
//        std::cerr << "请检查路径是否正确或从以下地址下载文件:" << std::endl;
//        std::cerr << "https://github.com/opencv/opencv/blob/master/data/haarcascades/haarcascade_frontalface_default.xml" << std::endl;
//        return -1;
//    }
//
//    // 打开摄像头
//    cv::VideoCapture cap(1);
//    if (!cap.isOpened()) {
//        std::cerr << "Error opening camera" << std::endl;
//        return -1;
//    }
//
//    // 设置摄像头分辨率
//    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
//    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
//
//    while (true) {
//        cv::Mat frame;
//        cap >> frame;
//        if (frame.empty()) break;
//
//        FaceDetectionResult result = detectFaces(frame, face_cascade);
//
//        // 绘制结果
//        drawResults(frame, result);
//
//        cv::flip(frame, frame, 1);
//
//        // 显示结果
//        cv::imshow("Face Detection", frame);
//
//        // 打印形心坐标
//        std::cout << "X = " << result.centroidX << "\tY = " << result.centroidY << std::endl;
//
//        // 按ESC退出
//        if (cv::waitKey(5) == 27) {
//            break;
//        }
//    }
//
//    cap.release();
//    cv::destroyAllWindows();
//    return 0;
//}



//人脸识别第二版(解决快速移动人脸和侧边人脸无法识别到的问题)
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <chrono>

// 数据结构，用于存储检测结果
struct FaceDetectionResult {
    std::vector<cv::Rect> faces;
    int centroidX;
    int centroidY;
    double avgConfidence;
};

// 优化的人脸检测函数
FaceDetectionResult detectFaces(const cv::Mat& frame, cv::CascadeClassifier& face_cascade) {
    // 计时开始
    auto start = std::chrono::high_resolution_clock::now();

    // 预处理 - 使用金字塔降采样加速
    cv::Mat resizedFrame;
    cv::resize(frame, resizedFrame, cv::Size(), 0.5, 0.5); // 缩小一半处理
    cv::Mat gray;
    cv::cvtColor(resizedFrame, gray, cv::COLOR_BGR2GRAY);

    // 增强处理 - 自适应光照
    cv::Mat enhanceImg;
    cv::equalizeHist(gray, enhanceImg);
    cv::medianBlur(enhanceImg, enhanceImg, 3); // 中值滤波更好地保留边缘

    // 使用多角度检测器
    std::vector<cv::Rect> allFaces;

    // 检测正面和侧面人脸
    face_cascade.detectMultiScale(enhanceImg, allFaces,
        1.05,      // 更小的缩放因子
        3,         // 降低邻居数提高敏感度
        cv::CASCADE_FIND_BIGGEST_OBJECT, // 只检测最大物体
        cv::Size(20, 20)); // 最小人脸尺寸

    // 检测轮廓更清晰的侧面人脸
    cv::CascadeClassifier profile_cascade;
    if (profile_cascade.load("D:/opencv/opencv/build/etc/haarcascades/haarcascade_profileface.xml")) {
        std::vector<cv::Rect> profileFaces;
        profile_cascade.detectMultiScale(enhanceImg, profileFaces,
            1.05, 3, 0,
            cv::Size(20, 20));
        allFaces.insert(allFaces.end(), profileFaces.begin(), profileFaces.end());
    }

    // 时间测量
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    // std::cout << "Detection time: " << duration.count() << "ms" << std::endl;

    // 多级筛选
    std::vector<cv::Rect> validFaces;
    for (const auto& face : allFaces) {
        // 恢复原始坐标 (因为图像被缩小处理)
        cv::Rect origFace(face.x * 2, face.y * 2, face.width * 2, face.height * 2);

        // 宽高比筛选 - 更宽松的条件 (0.7到2.0)
        float aspect_ratio = static_cast<float>(origFace.width) / origFace.height;
        if (aspect_ratio < 0.7 || aspect_ratio > 2.0) continue;

        // 面积占比筛选 - 防止过大误检
        float area_ratio = origFace.area() / static_cast<float>(frame.total());
        if (area_ratio > 0.5) continue;

        validFaces.push_back(origFace);
    }

    // 形心计算
    int centroid_X = frame.cols / 2;
    int centroid_Y = frame.rows / 2;
    double avgConfidence = 0.0;

    if (!validFaces.empty()) {
        float sumX = 0, sumY = 0;
        for (size_t i = 0; i < validFaces.size(); i++) {
            sumX += validFaces[i].x + validFaces[i].width / 2.0f;
            sumY += validFaces[i].y + validFaces[i].height / 2.0f;
        }
        centroid_X = static_cast<int>(sumX / validFaces.size());
        centroid_Y = static_cast<int>(sumY / validFaces.size());

        // 计算平均置信度（简单用面积代替）
        for (const auto& face : validFaces) {
            avgConfidence += face.area() / static_cast<float>(frame.total());
        }
        avgConfidence /= validFaces.size();
    }

    return { validFaces, centroid_X, centroid_Y, avgConfidence };
}

// 绘制结果函数（增加置信度显示）
void drawResults(cv::Mat& frame, const FaceDetectionResult& result) {
    if (!result.faces.empty()) {
        // 绘制检测到的人脸
        for (size_t i = 0; i < result.faces.size(); i++) {
            cv::Rect face = result.faces[i];

            // 根据置信度确定颜色（绿色-黄色-红色）
            float confidence = face.area() / static_cast<float>(frame.total());
            cv::Scalar color;
            if (confidence > 0.1) color = cv::Scalar(0, 255, 0); // 高置信度 - 绿色
            else if (confidence > 0.05) color = cv::Scalar(0, 255, 255); // 中置信度 - 黄色
            else color = cv::Scalar(0, 0, 255); // 低置信度 - 红色

            cv::rectangle(frame, face, color, 2);

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

    // 显示平均置信度
    std::string confText = "Confidence: " + std::to_string(result.avgConfidence).substr(0, 4);
    cv::putText(frame, confText, cv::Point(10, 60),
        cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 255), 2);

    // 显示帧率
    static double fps = 0;
    static auto lastTime = std::chrono::high_resolution_clock::now();
    auto currentTime = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count() / 1000.0;
    fps = 0.9 * fps + 0.1 * (1.0 / elapsed);
    lastTime = currentTime;

    std::string fpsText = "FPS: " + std::to_string((int)fps);
    cv::putText(frame, fpsText, cv::Point(frame.cols - 100, 30),
        cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(0, 255, 255), 2);

    // 绘制运动轨迹（黄色虚线）
    static std::vector<cv::Point> centroidHistory;
    centroidHistory.push_back(cv::Point(result.centroidX, result.centroidY));
    if (centroidHistory.size() > 10) {
        centroidHistory.erase(centroidHistory.begin());
    }
    for (size_t i = 1; i < centroidHistory.size(); i++) {
        cv::line(frame, centroidHistory[i - 1], centroidHistory[i],
            cv::Scalar(0, 255, 255), 1, cv::LINE_AA);
    }
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
    cv::VideoCapture cap(1);
    if (!cap.isOpened()) {
        std::cerr << "Error opening camera" << std::endl;
        return -1;
    }

    // 设置摄像头分辨率
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    // 创建跟踪器对象
    double prevTime = 0;
    cv::Point2f prevPosition(0, 0);
    float smoothingFactor = 0.8; // 位置平滑系数

    while (true) {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty()) break;

        auto start = std::chrono::high_resolution_clock::now();

        // 优化：跳帧处理 - 当FPS低于10时跳过处理
        static double avgFps = 15.0;
        static int frameCounter = 0;
        frameCounter++;

        // 预测下一帧位置（卡尔曼滤波器简化版）
        cv::Point2f prediction = prevPosition + (prevPosition - prevPosition);

        FaceDetectionResult result;
        if (avgFps > 10 || frameCounter % 2 == 0) { // 每两帧处理一次
            result = detectFaces(frame, face_cascade);

            // 位置平滑处理
            if (!result.faces.empty()) {
                cv::Point currentPos(result.centroidX, result.centroidY);
                prevPosition.x = smoothingFactor * currentPos.x + (1 - smoothingFactor) * prevPosition.x;
                prevPosition.y = smoothingFactor * currentPos.y + (1 - smoothingFactor) * prevPosition.y;
                result.centroidX = static_cast<int>(prevPosition.x);
                result.centroidY = static_cast<int>(prevPosition.y);
            }
        }
        else {
            // 使用之前的结果
            result = { {}, static_cast<int>(prediction.x), static_cast<int>(prediction.y), 0.0 };
        }

        // 绘制结果
        drawResults(frame, result);

        auto end = std::chrono::high_resolution_clock::now();
        double fps = 1000.0 / std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        avgFps = avgFps * 0.95 + fps * 0.05;

        //cv::flip(frame, frame, 1);
        cv::imshow("Face Detection", frame);

        // 添加人脸识别引导功能
        if (result.faces.empty()) {
            cv::putText(frame, "Move closer to camera", cv::Point(50, 100),
                cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 2);
        }

        // 按ESC退出
        if (cv::waitKey(5) == 27) {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
