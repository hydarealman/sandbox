# Sandbox — 本科学习代码合集

这是我在本科期间积累的个人代码仓库，涵盖课堂实验、网课练习、期末复习以及课外自学项目。不是单一工程，而是一个 **学习轨迹的归档**，按课程/方向分目录管理。

---

## 📁 目录总览

| 目录 | 技术栈 | 说明 |
|---|---|---|
| [JAVALAB/](JAVALAB/) | Java | 面向对象课程实验（lab1~lab4），含实验报告 |
| [JAVAPRATICE/](JAVAPRATICE/) | Java | 博客作业 + 期末复习（多线程、IO流、正则、接口） |
| [JAVAWEBPRATICE/](JAVAWEBPRATICE/) | Java, JSP, Servlet, HTML/CSS/JS | Java Web 课程 7 次实验，含登录、购物车、Servlet 等 |
| [Data_Structure/](Data_Structure/) | C++ | 数据结构与算法实现（树、图、排序、栈队列等） |
| [Programing_Coding/](Programing_Coding/) | C++ | 程序设计基础练习（problem1~18 + 补充题） |
| [os_homework/](os_homework/) | C | 操作系统：进程通信、信号量、生产者消费者、哲学家进餐、虚拟内存 |
| [C/](C/) | C | 协程库实现、时间转换小工具、OS yield 测试 |
| [stm32project/](stm32project/) | C (STM32) | STM32F103C8 嵌入式（15 个单元，从 GPIO 到看门狗） |
| [cvworkspace/](cvworkspace/) | C++ (OpenCV) | 计算机视觉实践（相机标定、装甲板识别、形态学等 48 个项目） |
| [ros_pratice_ws/](ros_pratice_ws/) | C++, Python, ROS 2 | ROS 2 Humble 机器人仿真（WPR 系列），跟随 B 站教程 |
| [MYSQL_homework/](MYSQL_homework/) | — | MySQL 作业（占位，暂为空） |

---

## 🗂️ 详细介绍

### Java 方向

#### [JAVALAB/](JAVALAB/) — 面向对象课程实验
- **lab1** — Java 入门：HelloWorld、猜数字、菜单打印、中文输入
- **lab2** — 面向对象核心：继承、多态、接口、状态模式（动物、银行、天气状态等）
- **lab3** — 字符串处理：生日计算、手机号校验、红包生成、字符串操作
- **lab4** — 综合项目：口算练习 GUI（Swing） + 控制台扫雷游戏，含[完整实验报告](JAVALAB/lab4/实验报告.md)

#### [JAVAPRATICE/](JAVAPRATICE/) — 博客作业 & 期末复习
- `code/` — 博客配套代码（blog_1 ~ blog_7）
- `review_pratice/` — 复习专题：
  - 封装·继承·多态
  - 接口
  - **多线程**（Thread、Runnable、生产者消费者）
  - **IO 流**（字节流、字符流、文件读写）
  - **正则表达式**（Pattern/Matcher 常用模式）

#### [JAVAWEBPRATICE/](JAVAWEBPRATICE/) — Java Web 实验
7 次实验循序渐进，覆盖 JSP 基础 → Servlet → JavaBean → Session 管理：
- 实验一～二：HTML + JSP 基础页面
- 实验三～四：JSP 登录验证、访客计数器、购物车、点餐页面
- 实验五：JavaBean + JSP（三角形计算器）
- 实验六～七：Servlet + JavaBean（登录系统、计算器、会话管理）

### C/C++ 方向

#### [Data_Structure/](Data_Structure/) — 数据结构
二叉搜索树、AVL 树、B 树 / B+ 树、红黑树、链表（单/双/循环）、栈、队列、冒泡/插入/归并/选择排序、Dijkstra、Floyd、Prim、Kruskal、并查集等

#### [Programing_Coding/](Programing_Coding/) — 程序设计基础
C++ 基础编程题，共 18 道主习题 + 10 道补充题

#### [os_homework/](os_homework/) — 操作系统
- 进程间通信：命名管道（FIFO）、共享内存
- 信号量：生产者消费者（单/多生产者、多消费者变体）
- 哲学家进餐（含死锁演示版本）
- 虚拟内存实验

#### [C/](C/) — C 语言小项目
- **coroutine-master** — 非对称协程库（基于 ucontext 的共享栈实现）
- **C_time_transform** — 时间格式转换
- **OS/** — yield 测试

### 嵌入式方向

#### [stm32project/](stm32project/) — STM32 单片机
基于 STM32F103C8（ARM Cortex-M3），使用 Keil uVision + 标准外设库，共 39 个项目：

| 单元 | 内容 |
|---|---|
| 2-3 | 工程模板、GPIO（LED、蜂鸣器、按键、光敏传感器） |
| 4 | OLED 显示驱动 |
| 5 | 外部中断（红外计数、旋转编码器） |
| 6 | 定时器（中断、PWM 呼吸灯/舵机/直流电机、输入捕获、编码器接口） |
| 7 | ADC（单通道、多通道） |
| 8 | DMA（数据转运 + ADC 多通道联动） |
| 9 | USART（串口收发、HEX 包、文本包协议） |
| 10 | I²C（软件/硬件读写 MPU6050 六轴传感器） |
| 11 | SPI（软件/硬件读写 W25Q64 Flash） |
| 12 | 备份寄存器、RTC 实时时钟 |
| 13 | 时钟配置、睡眠/停止/待机低功耗模式 |
| 14 | 独立看门狗、窗口看门狗 |
| 15 | 内部 FLASH 读写、芯片 ID |

### 机器视觉 & 机器人方向

#### [cvworkspace/](cvworkspace/) — OpenCV 计算机视觉
48 个项目，涵盖：
- **相机标定** — 张正友标定法，来自 CSDN / 知乎 / 上海交大多个来源对比
- **装甲板识别** — 单目识别 + 相机标定 + 距离测量，多个迭代版本（推测与 RoboMaster 相关）
- **图像处理基础** — 扫描、阈值、滤波、形态学、颜色空间、直方图、像素操作
- **特征检测** — MSER、GrabCut、分水岭分割
- **形状检测** — 几何形状、轮廓、四边形、旋转矩形
- **其他** — 人脸检测、QR 码位姿、PnP 测距、ZBar 条码

#### [ros_pratice_ws/](ros_pratice_ws/) — ROS 2 机器人
跟随 B 站 / Youtube 教程「机器人操作系统 ROS 2 入门」，使用 WPR 系列仿真机器人：
- `demo_cpp/` — 25+ 演示程序（话题、服务、动作、参数、TF 坐标变换）
- `exercises/` — 17+ 课后练习解答
- Gazebo 仿真世界 + 自主导航（Navigation2） + SLAM 建图
- 人脸检测、物体跟踪、机械臂抓取

---

## 🛠️ 涉及技术全景

```
语言/平台
├── Java (SE, Web, Swing)
├── C (POSIX, IPC, 嵌入式)
├── C++ (数据结构, OpenCV, ROS 2)
├── Python (ROS 2 launch)
├── JSP / Servlet / HTML / CSS / JavaScript
├── STM32 (ARM Cortex-M3, Keil MDK)
│
工具链
├── Git
├── VS Code / IntelliJ (Java) / Keil uVision
├── Visual Studio (OpenCV)
├── ROS 2 Humble + Gazebo + RViz
└── MySQL (计划中)
```

---

## ⚠️ 说明

- 本仓库是 **个人学习归档**，非生产级项目。代码多为课程作业或练习性质，仅供参考。
- 多数代码注释、目录名、实验报告使用中文。
- `ros_pratice_ws/src/wpr_simulation2` 克隆自 [6-robot/wpr_simulation2](https://github.com/6-robot/wpr_simulation2)，配套 ROS 2 入门课程使用。
- `MYSQL_homework/` 为预留目录，当前为空。

---
