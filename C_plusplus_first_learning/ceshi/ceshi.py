import cv2
import numpy as np

#创建窗口
cv2.namedWindow("trackbar",cv2.WINDOW_NORMAL)
cv2.resizeWindow("trackbar",840,880)
#cv2.namedWindow("trackbar")
#定义回调函数
def callback(value):
    #print(value)
    pass

#创建6个trackbar
#cv2.createTrackbar(别名,显示窗口,默认值,最大值,回调)
cv2.createTrackbar('lR','trackbar',0,255,callback)
cv2.createTrackbar('lG','trackbar',0,255,callback)
cv2.createTrackbar('lB','trackbar',0,255,callback)
cv2.createTrackbar('uR','trackbar',255,255,callback)
cv2.createTrackbar('uG','trackbar',255,255,callback)
cv2.createTrackbar('uB','trackbar',255,255,callback)

#创建一个背景图
img = cv2.imread(r"E:\picture\img4\test1\img475.jpg ")
hsv = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)

while True:

        #获取当前trackbar的值
    b_u = cv2.getTrackbarPos('lB','trackbar')   
    g_u = cv2.getTrackbarPos('lG','trackbar')
    r_u = cv2.getTrackbarPos('lR','trackbar')
    b_d = cv2.getTrackbarPos('uB','trackbar')    
    g_d = cv2.getTrackbarPos('uG','trackbar')
    r_d = cv2.getTrackbarPos('uR','trackbar')

    #用获取到的三个值修改背景图片颜色
    l_u = np.array([b_u,g_u,r_u])
    l_d = np.array([b_d,g_d,r_d])
    #img[:] = [b_u,g_u,r_u]
    #img[:] = [b_d,g_d,r_d]

    mask = cv2.inRange(hsv, l_u, l_d)
    res = cv2.bitwise_and(img, img, mask=mask)
    #显示窗口
    cv2.imshow("trackbar",res)
    key = cv2.waitKey(1)
    if key == 'q':
        break
cv2.destroyAllWindows()


