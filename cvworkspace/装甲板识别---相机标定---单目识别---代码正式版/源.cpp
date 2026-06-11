#include<iostream> 
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
//由于在识别中的核心物体以及相关的物理特性是灯条，所以建一个灯条类
class LightDescriptor
{	    //在识别以及匹配到灯条的功能中需要用到旋转矩形的长宽偏转角面积中心点坐标等
public:float width, length, angle, area;
      cv::Point2f center;
public:
    LightDescriptor() {};
    //让得到的灯条套上一个旋转矩形，以方便之后对角度这个特殊因素作为匹配标准
    LightDescriptor(const cv::RotatedRect& light)
    {
        width = light.size.width;
        length = light.size.height;
        center = light.center;
        angle = light.angle;
        area = light.size.area();
    }
};
//相机标定---获取相机内参和畸变系数
//没有足够的图片无法成功跑出来
int camera_calibration(Mat cameraMatrix, Mat distCoeffs) {
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
    for (size_t i = 0; i < fileNames.size(); i++)
    {
        image = imread(fileNames[i], IMREAD_COLOR);
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

    // 4. 标定相机

    vector<Mat> rvecs, tvecs;
    cv::calibrateCamera(objectPoints, imagePoints, image.size(), cameraMatrix, distCoeffs, rvecs, tvecs);

    cout << "Camera matrix:" << endl << cameraMatrix << endl;
    cout << "Distortion coefficients:" << endl << distCoeffs << endl;

    return 0;
}

int main()
{
    //VideoCapture video; //VC类对象化
    //video.open("D:/opencv资料库/opencv操作视频保存/机器人旋转视频.avi");
    VideoCapture video("D:/opencv资料库/opencv操作视频保存/机器人旋转视频.avi");
    //VideoCapture video("D:/opencv资料库/opencv操作视频保存/机器人上下左右晃动视频.avi");

    //VideoCapture video("D:/opencv资料库/opencv操作视频保存/机器人左右平移视频.avi");
    //获取视频参数
    //int fourcc = VideoWriter::fourcc('M', 'J', 'P', 'G');
    //double fps = video.get(CAP_PROP_FPS);
    //Size frameSize(static_cast<int>(video.get(CAP_PROP_FRAME_WIDTH)), static_cast<int>(video.get(CAP_PROP_FRAME_HEIGHT)));
    //VideoWriter writer("D:/opencv资料库/opencv操作视频保存/rotate.avi", fourcc, fps, frameSize,true );//保存的视频打不开

    //变量集中定义
    Mat frame, channels[3], binary, Gaussian, dilatee;
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    Rect boundRect;
    RotatedRect box;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<Point2f> boxPts(4);
    //相机内参和畸变系数
    Mat cameraMatrix, distCoeffs;

    //图像预处理
    for (;;) {
        //Rect point_array[20];
        video.read(frame);  //读取每帧
        if (frame.empty()) {
            break;
        }
        split(frame, channels); //通道分离
        threshold(channels[2], binary, 220, 255, 0);//二值化
        GaussianBlur(binary, Gaussian, Size(5, 5), 0);//滤波
        dilate(Gaussian, dilatee, element);
        // dilate(Gaussian, dilate, element, Point(-1, -1));//膨胀，把滤波得到的细灯条变宽
        findContours(dilatee,
            contours, //输出轮廓图像,是一个向量,向量的每一个元素是一个轮廓
            hierarchy, //输出各个轮廓的继承关系
            RETR_TREE, //检测所有轮廓,并且建立所有的继承关系
            CHAIN_APPROX_NONE//把轮廓的所有点存储
        );//轮廓检测
        vector<LightDescriptor> lightInfos;//创建一个灯条类的动态数组
        //筛选灯条
        for (int i = 0; i < contours.size(); i++) {
            // 求轮廓面积
            double area = contourArea(contours[i]);
            // 去除较小轮廓&fitEllipse的限制条件
            if (area < 5 || contours[i].size() <= 1)
                continue;//相当于就是把这段轮廓去除掉
            // 用椭圆拟合区域得到外接矩形（特殊的处理方式：因为灯条是椭圆型的，所以用椭圆去拟合轮廓，再直接获取旋转外接矩形即可）
            RotatedRect Light_Rec = fitEllipse(contours[i]);

            // 长宽比和轮廓面积比限制（由于要考虑灯条的远近都被识别到，所以只需要看比例即可）
            if (Light_Rec.size.width / Light_Rec.size.height > 4)
                continue;
            lightInfos.push_back(LightDescriptor(Light_Rec));
        }
        //二重循环多条件匹配灯条
        for (size_t i = 0; i < lightInfos.size(); i++) {
            for (size_t j = i + 1; (j < lightInfos.size()); j++) {
                LightDescriptor& leftLight = lightInfos[i];
                LightDescriptor& rightLight = lightInfos[j];
                float angleGap_ = abs(leftLight.angle - rightLight.angle);
                //由于灯条长度会因为远近而受到影响，所以按照比值去匹配灯条



                //计算左右灯条的中心距离
                float dis = pow(pow((leftLight.center.x - rightLight.center.x), 2) + pow((leftLight.center.y - rightLight.center.y), 2), 0.5);
                //计算左右灯条长度的均值
                float meanLen = (leftLight.length + rightLight.length) / 2;



                //绝对长度差/较长灯条的长度     衡量长度差异相对于较大灯条的占比    检测单侧过长的不合理匹配
                float LenGap_ratio = abs(leftLight.length - rightLight.length) / max(leftLight.length, rightLight.length);
                //绝对长度差/两条灯条的平均长度       衡量长度差异相对于平均值的偏离程度   检测整体长度失衡的情况
                float lengap_ratio = abs(leftLight.length - rightLight.length) / meanLen;



                //计算灯条y的差
                float yGap = abs(leftLight.center.y - rightLight.center.y);
                //计算灯条x的差
                float xGap = abs(leftLight.center.x - rightLight.center.x);



                //计算y差值的比值
                float yGap_ratio = yGap / meanLen;
                //计算灯条x差值的比值
                float xGap_ratio = xGap / meanLen;



                //计算灯条的距离与长度的比值(也就是嫌疑装甲板长和宽的比值)
                float ratio = dis / meanLen;


                //对上面各量筛选,如果y差太大(y最好越相近越好),或者x差的太小,又或者装甲板长宽比不合适就排除掉



                //匹配不通过的条件
                if (angleGap_ > 15 ||//约束灯条左右角度差  保证俩个灯条灯条平行
                    LenGap_ratio > 1.0 ||   //长度差约束（1）检测单条过长的不合理匹配
                    lengap_ratio > 0.8 ||   //长度差约束（2）检测整体长度失衡的情况

                    yGap_ratio > 1.5 ||//  Y轴对齐约束   使装甲板水平对齐

                    xGap_ratio > 2.2 ||//  X轴对齐约束  使装甲板竖直对齐
                    xGap_ratio < 0.8 ||

                    ratio > 3 ||//计算灯条的距离与灯条平均长度的比值 控制装甲板长宽比
                    ratio < 0.8) {
                    continue;
                }
                //最后筛选出两个灯条计算中心 角度 长宽 绘制方框rect 
                //绘制矩形
                Point center = Point((leftLight.center.x + rightLight.center.x) / 2, (leftLight.center.y + rightLight.center.y) / 2);
                RotatedRect rect = RotatedRect(center, Size(dis, meanLen), (leftLight.angle + rightLight.angle) / 2);
                Point2f vertices[4];
                //获得四个端点
                rect.points(vertices);
                //利用取模的算法绘制矩形的四条边
                for (int i = 0; i < 4; i++) {
                    line(frame, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 4);
                }
                //旋转矩阵,平移矩阵
                Mat rotation_vector, translation_vector;
                //内参,畸变系数
                Mat camera_matrix = (Mat_<double>(3, 3) <<
                    832.5, 0, 320.1,
                    0, 832.8, 240.3,
                    0, 0, 1);
                Mat dist_coeffs = (Mat_<double>(5, 1) <<
                    0.12, -0.3, 0.001, -0.002, 0.15
                    );
                //获取装甲板的四个点的像素坐标
                vector<Point2f> armoured_plate_pixel_point;
                vector<vector<float>> dir = {
                    {0,meanLen / 2},
                    {dis / 2,0},
                    {0,-meanLen / 2},
                    {-dis / 2,0}
                };
                for (int i = 0; i < 4; i++) {
                    Point2f pt;
                    pt.x = center.x + dir[i][0];
                    pt.y = center.y + dir[i][1];
                    armoured_plate_pixel_point.push_back(pt);
                }
                //自己写写的老代码//写的不对//没有正确建立世界坐标系
                ////计算装甲板上四个点的世界坐标
                //vector<Point3f> armoured_plate_real_point;
                //for (int i = 0; i < 4; i++) {
                //    Point3f pt;
                //    pt.x = armoured_plate_pixel_point[i].x * armoured_plate_width;
                //    pt.y = 0;
                //    pt.z = armoured_plate_pixel_point[i].y * armoured_plate_height;
                //    armoured_plate_real_point.push_back(pt);
                //}
                // 定义装甲板四个角点的世界坐标（以装甲板中心为原点，Z=0平面）
                 //装甲板的物理尺寸
                const float armoured_plate_width = 0.14f;
                const float armoured_plate_height = 0.125f;
                vector<Point3f> armoured_plate_real_point = {
                    Point3f(-armoured_plate_width / 2, armoured_plate_height / 2, 0),  // 左上
                    Point3f(armoured_plate_width / 2, armoured_plate_height / 2, 0),   // 右上
                    Point3f(armoured_plate_width / 2, -armoured_plate_height / 2, 0),  // 右下
                    Point3f(-armoured_plate_width / 2, -armoured_plate_height / 2, 0)  // 左下
                };

                //php方法测距
                solvePnP(armoured_plate_real_point, armoured_plate_pixel_point, camera_matrix, dist_coeffs, rotation_vector, translation_vector);
                double depth = translation_vector.at<double>(2);
                std::cout << depth << endl;
                //cout <<  norm(translation_vector) << endl;
                 // //重新投影误差验证
                 //vector<Point2f> reprojected_points;
                 //projectPoints(armoured_plate_real_point,
                 //    rotation_vector,
                 //    translation_vector,
                 //    camera_matrix,
                 //    dist_coeffs,
                 //    reprojected_points);

                 //double total_error = 0;
                 //for (size_t i = 0; i < 4; ++i) {
                 //    double error = norm(armoured_plate_pixel_point[i] - reprojected_points[i]);
                 //    total_error += error;
                 //}
                 //cout << "平均重投影误差: " << total_error / 4 << " 像素" << endl;

                 //// 合理范围：误差应 < 1.5像素
                 //if (total_error / 4 > 1.5) {
                 //    cerr << "警告：解算结果精度不足！" << endl;
                 //}
            }
        }
        //writer.write(frame);
        namedWindow("video", WINDOW_FREERATIO);
        imshow("video", frame);
        waitKey(5);
    }
    video.release();
    //writer.release();
    cv::destroyAllWindows();
    return 0;
}