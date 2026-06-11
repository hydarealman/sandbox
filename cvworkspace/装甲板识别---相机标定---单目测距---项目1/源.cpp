#include<iostream> 
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;
class LightDescriptor
{	    
public:float width, length, angle, area;
      cv::Point2f center;
public:
    LightDescriptor() {};
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
    VideoCapture video("D:/opencv资料库/opencv操作视频保存/机器人上下左右晃动视频.avi");

    Mat frame, channels[3], binary, Gaussian, dilatee;
    Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
    Rect boundRect;
    RotatedRect box;
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    vector<Point2f> boxPts(4);
    for (;;) {
        video.read(frame);  
        if (frame.empty()) {
            break;
        }
        split(frame, channels); 
        threshold(channels[2], binary, 220, 255, 0);
        GaussianBlur(binary, Gaussian, Size(5, 5), 0);
        dilate(Gaussian, dilatee, element);
   
        findContours(dilatee,
            contours, 
            hierarchy,
            RETR_TREE, 
            CHAIN_APPROX_NONE
        );
        vector<LightDescriptor> lightInfos;
       
        for (int i = 0; i < contours.size(); i++) {
           
            double area = contourArea(contours[i]);
           
            if (area < 5 || contours[i].size() <= 1)
                continue;
          
            RotatedRect Light_Rec = fitEllipse(contours[i]);
           

         
            if (Light_Rec.size.width / Light_Rec.size.height > 4)
                continue;
            lightInfos.push_back(LightDescriptor(Light_Rec));
        }
       
        for (size_t i = 0; i < lightInfos.size(); i++) {
            for (size_t j = i + 1; (j < lightInfos.size()); j++) {
                LightDescriptor& leftLight = lightInfos[i];
                LightDescriptor& rightLight = lightInfos[j];
                float angleGap_ = abs(leftLight.angle - rightLight.angle);
              



               
                float dis = pow(pow((leftLight.center.x - rightLight.center.x), 2) + pow((leftLight.center.y - rightLight.center.y), 2), 0.5);
               
                float meanLen = (leftLight.length + rightLight.length) / 2;



             
                float LenGap_ratio = abs(leftLight.length - rightLight.length) / max(leftLight.length, rightLight.length);
               
                float lengap_ratio = abs(leftLight.length - rightLight.length) / meanLen;



               
                float yGap = abs(leftLight.center.y - rightLight.center.y);
               
                float xGap = abs(leftLight.center.x - rightLight.center.x);



                
                float yGap_ratio = yGap / meanLen;
               
                float xGap_ratio = xGap / meanLen;



               
                float ratio = dis / meanLen;


                
                if (angleGap_ > 15 ||
                    LenGap_ratio > 1.0 ||   
                    lengap_ratio > 0.8 || 

                    yGap_ratio > 1.5 ||

                    xGap_ratio > 2.2 ||
                    xGap_ratio < 0.8 ||

                    ratio > 3 ||
                    ratio < 0.8) {
                    continue;
                }
                
                Point center = Point((leftLight.center.x + rightLight.center.x) / 2, (leftLight.center.y + rightLight.center.y) / 2);
                RotatedRect rect = RotatedRect(center, Size(dis, meanLen), (leftLight.angle + rightLight.angle) / 2);
                Point2f vertices[4];
               
                rect.points(vertices);
               
                for (int i = 0; i < 4; i++) {
                    line(frame, vertices[i], vertices[(i + 1) % 4], Scalar(0, 0, 255), 4);
                }
            }
        }
       
        namedWindow("video", WINDOW_FREERATIO);
        imshow("video", frame);
        waitKey(5);
    }
    video.release();
    //writer.release();
    cv::destroyAllWindows();
    return 0;
}