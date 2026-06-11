#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main()
{
    // 1. 准备标定棋盘图像
    int boardWidth = 9;  // 棋盘格横向内角点数量
    int boardHeight = 6; // 棋盘格纵向内角点数量
    float squareSize = 1.f; // 棋盘格格子的大小，单位为米,随便设置，不影响相机内参计算
    Size boardSize(boardWidth, boardHeight);

    vector<vector<Point3f>> objectPoints;
    vector<vector<Point2f>> imagePoints;
    vector<Point2f> corners;

    // 2. 拍摄棋盘图像
    Mat image, gray;
    namedWindow("image", WINDOW_NORMAL);
    vector<String> fileNames;
    glob("D:/相机标定_棋盘格图片20张/camera_cal", fileNames);
    //检查图像路径和数量
    if (fileNames.empty()) {
        cerr << "Error: No images found in the directory." << endl;
        return -1;
    }
    cout << "Found " << fileNames.size() << " images." << endl;

    int successCount = 0;
    Size imageSize;
    Size targetSize(1280, 720); // 设置目标尺寸（根据实际情况调整）
    for (size_t i = 0; i < fileNames.size(); i++)
    {
        image = imread(fileNames[i], IMREAD_COLOR);
        if (image.empty()) {
            cerr << "警告：无法读取图像 " << fileNames[i] << "，跳过该文件。" << endl;
            continue; // 跳过后续处理
        }
        // 强制调整图像尺寸
        if (image.size() != targetSize) {
            resize(image, image, targetSize); // 缩放图像到目标尺寸
        }

        // 检查图像尺寸一致性
        if (i == 0) {
            imageSize = image.size();
        }
        else if (image.size() != imageSize) {
            cerr << "错误：图像尺寸不一致，请确保所有图像分辨率相同！" << endl;
            return -1;
        }
        cvtColor(image, gray, COLOR_BGR2GRAY);

        // 3. 读入图像数据，并提取角点
        bool found = findChessboardCorners(image, boardSize, corners, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);
        if (found)
        {
            successCount++;
            cout << "Corners found in image: " << fileNames[i] << endl;
            cornerSubPix(gray, corners, Size(11, 11), Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));
            drawChessboardCorners(image, boardSize, corners, found);
            imshow("image", image);
            waitKey(5);

            vector<Point3f> objectCorners;
            for (int j = 0; j < boardHeight; j++)
            {
                for (int k = 0; k < boardWidth; k++)
                {
                    objectCorners.push_back(Point3f(k * squareSize, j * squareSize, 0));
                }
            }
            objectPoints.push_back(objectCorners);
            imagePoints.push_back(corners);
        }
        else {
            cerr << "Warning: Corners not found in image: " << fileNames[i] << endl;
        }
    }
    cout << "Successfully processed " << successCount << " images." << endl;
    destroyWindow("image");

    if (successCount < 10) { // 至少需要10张图像
        cerr << "错误：成功标定的图像不足 (" << successCount << " 张)，请提供更多有效图像！" << endl;
        return -1;
    }

    // 在调用 calibrateCamera 前添加检查//这部分没有问题
    if (objectPoints.empty() || imagePoints.empty()) {
        cerr << "错误：objectPoints 或 imagePoints 为空，请确保成功提取了足够的角点！" << endl;
        return -1;
    }

    // 4. 标定相机
    // 显式初始化参数
    Mat cameraMatrix = Mat::eye(3, 3, CV_64F);
    Mat distCoeffs = Mat::zeros(8, 1, CV_64F);
    vector<Mat> rvecs, tvecs;
    cv::calibrateCamera(objectPoints, imagePoints, image.size(), cameraMatrix, distCoeffs, rvecs, tvecs);

    cout << "Camera matrix:" << endl << cameraMatrix << endl;
    cout << "Distortion coefficients:" << endl << distCoeffs << endl;

    return 0;
}