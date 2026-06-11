#include<iostream> 
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<sstream>
#include<iomanip>
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


int main()
{



    //变量集中定义
    Mat frame, channels[3], binary, Gaussian, dilatee;
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    Rect boundRect;
    RotatedRect box;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<Point2f> boxPts(4);
    //相机内参和畸变系数
    Mat cameraMatrix = (cv::Mat_<double>(3, 3) << 1704.45313471055, 0, 0, 0.460601854648428, 1704.60254015387, 0, 665.913826347723, 487.291315275975, 1);
    Mat distCoeffs = (cv::Mat_<double>(1, 5) << -0.0817259940211909, 0.392083347020012, -0.000578920794543104, 0.00187156396493549, -0.140959043006811);


    //图像预处理

    frame = imread("D:/opencv资料库/opencv处理图像/Image_20250324214001264.bmp");
    split(frame, channels); //通道分离
    threshold(channels[0], binary, 220, 255, 0);//二值化
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

                yGap_ratio > 0.65 ||//  Y轴对齐约束   使装甲板水平对齐

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
                line(frame, vertices[i], vertices[(i + 1) % 4], Scalar(0, 255, 0), 4);
            }


            //获取装甲板的四个点的像素坐标
            vector<Point2f> armoured_plate_pixel_point;

            armoured_plate_pixel_point = {
                Point2f(center.x - dis / 2,center.y - meanLen / 2),
                Point2f(center.x + dis / 2,center.y - meanLen / 2),
                Point2f(center.x + dis / 2,center.y + meanLen / 2),
                Point2f(center.x - dis / 2,center.y + meanLen / 2)
            };



            //变量集中定义
            //旋转矩阵,平移矩阵
            Mat rotation_vector, translation_vector;
            //装甲板的物理尺寸
            const float armoured_plate_width = 0.235f;
            const float armoured_plate_height = 0.127f;
            //灯条长度
            const float light_len = 0.070f;
            //计算装甲板四个角点的世界坐标（以装甲板中心为原点，Z=0平面）
            vector<Point3f> armoured_plate_real_point = {
                Point3f(-armoured_plate_width / 2, light_len / 2, 0),  // 左上
                Point3f(armoured_plate_width / 2, light_len / 2, 0),   // 右上
                Point3f(armoured_plate_width / 2, -light_len / 2, 0),  // 右下
                Point3f(-armoured_plate_width / 2, -light_len / 2, 0)  // 左下
            };
            /*vector<Point3f> armoured_plate_real_point = {
                Point3f(-armoured_plate_width / 2,0,0),
                Point3f(armoured_plate_width / 2,0,0),
                Point3f(0,armoured_plate_height / 2,0),
                Point3f(0,-armoured_plate_height / 2,0)
            };*/

            //php方法测距
            cv::solvePnP(armoured_plate_real_point, armoured_plate_pixel_point, cameraMatrix, distCoeffs, rotation_vector, translation_vector);
            double depth = translation_vector.at<double>(2);
            cout << "depth:" << depth << endl;

            //绘制代码
            //ostringstream的主要功能是将不同类型的数据格式化为一个字符串
            std::ostringstream depthStr;
            //<<流式操作符将数据写入ostringstream中
            depthStr << std::fixed << std::setprecision(2) << "depth:" << depth << "m";//将深度值转换为字符串 //用于控制浮点数显示精度的格式化操作符
            cv::Point textPos(center.x - 40, center.y - 20);//确定文字显示位置-40和-10是经验偏移值,目的是让文字显示在装甲板中心的上方偏左的位置
            // 绘制半透明背景//防止文字与图像颜色混合导致看不清
            cv::Mat overlay = frame.clone();//复制当前帧到一个临时图层overlay
            cv::rectangle(overlay,//画在overlat图层上
                textPos - cv::Point(5, 20),
                textPos + cv::Point(70, 5),
                cv::Scalar(0, 0, 0),
                -1);
            cv::addWeighted(overlay, 0.5, frame, 0.5, 0, frame);//将overlay和原始frame以50%透明度混合,实现半透明效果frame = overlay*0.5 + frame*0.5 + 0

            // 绘制文字
            cv::putText(frame, //从 ostringstream 中获取格式化后的深度信息字符串。
                depthStr.str(),//调用str()方法获取最终格式化后的字符串
                textPos,//文字显示的位置
                FONT_HERSHEY_SIMPLEX,//字体类型
                0.6,//字体大小
                cv::Scalar(0, 255, 255),//字体颜色
                2);//文字粗细
            //绘制装甲板宽和高
            std::ostringstream widthStr;
            std::ostringstream heightStr;
            widthStr << std::fixed << std::setprecision(2) << "width:" << armoured_plate_height << "m";
            heightStr << std::fixed << std::setprecision(2) << "height:" << armoured_plate_width << "m";
            Point textPos1(center.x - 40, center.y + 10);
            Point textPos2(center.x - 40, center.y + 30);
            //绘制装甲版的宽
            cv::putText(frame,
                widthStr.str(),
                textPos1,
                FONT_HERSHEY_SIMPLEX,
                0.6,
                cv::Scalar(255, 0, 255),
                2);
            //绘制装甲版的高
            cv::putText(frame,
                heightStr.str(),
                textPos2,
                FONT_HERSHEY_SIMPLEX,
                0.6,
                cv::Scalar(255, 0, 255),
                2);

        }
    }
    //writer.write(frame);
    namedWindow("video", WINDOW_FREERATIO);
    cv::imshow("video", frame);
    cv::waitKey(0);

    //writer.release();
    cv::destroyAllWindows();
    return 0;
}