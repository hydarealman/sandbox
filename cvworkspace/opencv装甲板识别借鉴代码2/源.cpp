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

int main()
{
    //VideoCapture video; //VC类对象化
    //video.open("D:/opencv资料库/opencv操作视频保存/机器人旋转视频.avi");
    //VideoCapture video("D:/opencv资料库/opencv操作视频保存/机器人旋转视频.avi");
    VideoCapture video("D:/opencv资料库/opencv操作视频保存/机器人上下左右晃动视频.avi");

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