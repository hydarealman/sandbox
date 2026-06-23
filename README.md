# Sandbox — 本科学习代码合集

这是我在本科期间积累的个人代码仓库，涵盖课堂实验、网课练习、竞赛备赛、期末复习以及课外自学项目。不是单一工程，而是一个 **学习轨迹的归档**，按课程/方向分目录管理。

---

## 📁 目录总览

| 目录 | 技术栈 | 说明 | 规模 |
|---|---|---|---|
| [c_language_first_learning/](c_language_first_learning/) | C | 最初的 C 语言入门代码（大一上） | ~168 文件 |
| [C_plusplus_first_learning/](C_plusplus_first_learning/) | C++ | C++ 系统学习（基础→STL→算法→项目） | ~414 文件 |
| [C/](C/) | C | 协程库、时间转换、OS yield 测试 | ~11 文件 |
| [Programing_Coding/](Programing_Coding/) | C++ | 程序设计基础练习（problem1~18 + 补充题） | ~57 文件 |
| [Data_Structure/](Data_Structure/) | C++ | 数据结构与算法实现 | ~41 文件 |
| [JAVALAB/](JAVALAB/) | Java | 面向对象课程实验（lab1~lab5），含实验报告 | ~105 文件 |
| [JAVAPRATICE/](JAVAPRATICE/) | Java | 博客作业 + 期末复习（多线程、IO流、正则、接口） | ~42 文件 |
| [JAVAWEBPRATICE/](JAVAWEBPRATICE/) | Java, JSP, Servlet | Java Web 课程 10 次实验 + Tomcat | ~809 文件 |
| [java-web-internship/](java-web-internship/) | Java, MyBatis, MySQL | Java Web 实习（MyBatis 持久层框架） | ~20 文件 |
| [MYSQL_homework/](MYSQL_homework/) | SQL, Python | MySQL 数据库作业 + 实验报告 | ~77 文件 |
| [python_first_learning/](python_first_learning/) | Python | Python 初学（OOP、数据分析、数据库、图表） | ~36 文件 |
| [os_homework/](os_homework/) | C | 操作系统（IPC、信号量、生产者消费者、虚拟内存） | ~31 文件 |
| [mathematical-modeling/](mathematical-modeling/) | Python, ML | 数学建模备赛（LSTM、LightGBM、优化算法） | ~65 文件 |
| [stm32project/](stm32project/) | C (ARM) | STM32F103C8 嵌入式（39 个项目，15 单元） | ~7079 文件 |
| [cvworkspace/](cvworkspace/) | C++ (OpenCV) | 计算机视觉实践（标定、装甲板识别等 48 项） | ~50 文件 |
| [ros_pratice_ws/](ros_pratice_ws/) | C++, Python, ROS 2 | ROS 2 机器人仿真（WPR 系列） | ~753 文件 |

---

## 🗂️ 详细介绍

### C 语言入门 → 进阶

#### [c_language_first_learning/](c_language_first_learning/) — 最初的 C 语言代码（大一上）
真正开始学编程时写的第一批代码，内容包括：
- Hello World、变量、数据类型、运算符
- 分支与循环、数组、指针、结构体
- 冒泡排序、斐波那契数列、素数判断、阶乘
- 字符串处理、函数练习、调试实验
- Visual Studio 工程（.sln / .vcxproj）

#### [C_plusplus_first_learning/](C_plusplus_first_learning/) — C++ 系统学习（大一）
最庞大的学习集合，280+ 个小项目，覆盖：
- **基础** — 变量、函数、引用、指针、数组、结构体
- **面向对象** — 类、封装、继承、多态、运算符重载、友元、静态成员、常成员
- **STL** — vector、algorithm（排序、查找、拷贝、替换、算术、集合）、仿函数、谓词、Lambda 表达式
- **模板** — 函数模板、类模板、模板特化
- **文件 IO** — 文本文件读写、二进制文件读写
- **数据结构** — 链表（手写）、二叉树（递归遍历）、哈希表
- **算法** — KMP、二分查找、排序（冒泡/选择/插入/归并/快速/桶排序）、DFS（岛屿、最大面积、沉岛）、BFS（网格岛屿）、DP（01 背包、完全背包、爬楼梯、最小路径和）、回溯（八皇后、全排列、所有路径）
- **项目实战** — 职工管理系统、演讲比赛流程、坦克大战、飞机大战、通讯录管理系统
- **LeetCode 练习**
- **OpenCV 初探** — 图像加载、ROI、颜色缩减、图像重映射、摄像头捕获、人脸识别

#### [C/](C/) — C 语言小项目
- **coroutine-master** — 非对称协程库（ucontext 共享栈实现）
- **C_time_transform** — 时间格式转换工具
- **OS/** — yield 调度测试

---

### 数据结构

#### [Data_Structure/](Data_Structure/) — 数据结构与算法
手写实现全部经典结构：
- **树** — 二叉搜索树、AVL 树、B 树、B+ 树、红黑树、二叉树
- **链表** — 单向链表、双向循环链表、循环链表
- **栈 & 队列** — 顺序栈、链栈、顺序队列、链队列、循环队列
- **图** — Dijkstra（最短路径）、Floyd（多源最短路径）、Prim（最小生成树）、Kruskal（最小生成树）
- **排序** — 冒泡、插入、归并、选择排序
- **其他** — 并查集、进制转换（栈实现）

---

### Java 方向

#### [JAVALAB/](JAVALAB/) — 面向对象课程实验
- **lab1** — Java 入门：HelloWorld、猜数字、菜单打印、中文输入
- **lab2** — 面向对象核心：继承、多态、接口、状态模式（动物类、银行系统、天气状态等）
- **lab3** — 字符串处理：生日计算、手机号校验、红包生成、购物小票、字符串操作
- **lab4** — 综合项目：口算练习 GUI（Swing）+ 控制台扫雷，含[完整实验报告](JAVALAB/lab4/实验报告.md)
- **lab5** — 多线程：双线程猜数字、词汇统计、中文输入/输出线程，含截图

#### [JAVAPRATICE/](JAVAPRATICE/) — 博客作业 & 期末复习
- `code/` — 博客配套代码（blog_1 ~ blog_7）
- `review_pratice/` — 复习专题：
  - 封装·继承·多态
  - 接口
  - **多线程**（Thread、Runnable、生产者消费者）
  - **IO 流**（字节流、字符流、文件读写）
  - **正则表达式**（Pattern/Matcher 常用模式）

#### [JAVAWEBPRATICE/](JAVAWEBPRATICE/) — Java Web 课程
- **10 次实验**（experiment01~10），从 HTML 基础到 Servlet + JavaBean：
  - 实验 1-3：HTML 表单、页面布局、表单验证
  - 实验 4-7：JSP 基础、登录验证、访客计数器、购物车、点餐、三角形计算
  - 实验 8-10：Servlet、JavaBean、会话管理
- 内嵌 **Apache Tomcat 11** 完整服务器，开箱即用
- 含实验报告生成脚本（`extract_doc.py`、`generate_reports.py`）
- `reports/` — 10 份 .docx 实验报告 + HTML 版本

#### [java-web-internship/](java-web-internship/) — Java Web 实习（MyBatis）
- **Day01** — MyBatis 入门：ORM、SqlSession 生命周期、CRUD、@Param 参数、动态代理原理
- **Day02** — 代理方式 CRUD：typeAliases 别名配置、getMapper() 代理、三种映射文件指定方式
- 数据库：MySQL（`t_user` 表 + `user` 表）
- 构建工具：Maven（MyBatis 3.5.16 + MySQL Connector 8.0.33）
- `code/day01/` — 4 个可运行程序（HelloWorld / CURDDemo1 / ParamTest / ProxyTest）
- `code/day02/` — 2 个可运行程序（TypeAliase / CURDTest）

---

### 数据库

#### [MYSQL_homework/](MYSQL_homework/) — MySQL 数据库作业
- `sql/` — 12 个 SQL 脚本（实验 1~8，含事务隔离级别对比）
- `reports/` — 8 份独立实验报告（.docx）
- `outputs/` — 查询结果与演示输出
- `scripts/` — Python 报告生成脚本（`build_report.py`、`make_screenshots.py` 等）
- 涵盖：SQL 查询、索引、视图、存储过程、触发器、安全性、完整性、执行计划、事务隔离级别

---

### Python

#### [python_first_learning/](python_first_learning/) — Python 初学
- **面向对象** — 类、对象、继承、多态、封装、构造方法、魔术方法
- **类型注解** — Union 类型、函数签名注解
- **数据分析** — pandas 示例、JSON 处理、CSV 销售数据处理
- **数据库** — pymysql 连接 MySQL、数据插入与查询
- **可视化** — pyecharts 折线图
- **OpenCV** — `opencvtest01.py` 图像处理初探
- **自定义包** — `my_utils/`（文件工具、字符串工具）

---

### 数学建模

#### [mathematical-modeling/](mathematical-modeling/) — 数学建模备赛
三轮建模训练，完整代码 + 图表输出：

| 轮次 | 主题 | 方法与技术 |
|---|---|---|
| 第一轮 | 医疗健康预测 | LSTM 神经网络、LightGBM、逻辑回归；脑卒中、心脏病、肝硬化预测；混淆矩阵、ROC 曲线、特征重要性图 |
| 第二轮 | 交通流量分析 | 信号灯配时优化、停车需求分析；Excel 报告 + PNG 图 |
| 第三轮 | 资源调度优化 | QoS 优化、功耗分析、SLA 趋势分析；5 道题 + 结果图 |

**技术栈：** Python · scikit-learn · LightGBM · Keras/LSTM · pandas · matplotlib · openpyxl

---

### 嵌入式

#### [stm32project/](stm32project/) — STM32 单片机
基于 STM32F103C8（ARM Cortex-M3），Keil uVision + 标准外设库，39 个项目系统学习：

| 单元 | 内容 |
|---|---|
| 2-3 | 工程模板、GPIO（LED 闪烁/流水灯、蜂鸣器、按键、光敏传感器） |
| 4 | OLED 显示驱动 |
| 5 | 外部中断（对射式红外计次、旋转编码计次） |
| 6 | 定时器（中断、外部时钟、PWM 呼吸灯/舵机/直流电机、输入捕获、PWMI、编码器测速） |
| 7 | ADC（单通道、多通道） |
| 8 | DMA（数据转运 + ADC 多通道联动） |
| 9 | USART（串口收发、HEX 数据包协议、文本数据包协议） |
| 10 | I²C（软件/硬件读写 MPU6050 六轴传感器） |
| 11 | SPI（软件/硬件读写 W25Q64 Flash） |
| 12 | 备份寄存器、RTC 实时时钟 |
| 13 | 时钟配置、睡眠/停止/待机低功耗模式 |
| 14 | 独立看门狗、窗口看门狗 |
| 15 | 内部 FLASH 读写、芯片 ID 读取 |

---

### 机器视觉 & 机器人

#### [cvworkspace/](cvworkspace/) — OpenCV 计算机视觉
48 个项目，涵盖：
- **相机标定** — 张正友标定法，对比 CSDN / 知乎 / 上海交大多个来源实现
- **装甲板识别** — 单目识别 + 相机标定 + 距离测量，多个迭代版本（推测与 RoboMaster 相关）
- **图像处理** — 扫描、阈值、滤波、形态学、颜色空间、直方图、像素操作
- **特征检测** — MSER、GrabCut、分水岭分割
- **形状检测** — 几何形状、轮廓、四边形、旋转矩形
- **QR / 条码** — QR 码位姿估计、ZBar 条码识别
- **人脸检测**、**PnP 测距**、**颜色识别**、**红区检测**

#### [ros_pratice_ws/](ros_pratice_ws/) — ROS 2 机器人
跟随 B 站 / YouTube 教程「机器人操作系统 ROS 2 入门」，使用 WPR 系列仿真机器人：
- `demo_cpp/` — 25+ 演示程序（发布/订阅、LiDAR、IMU、SLAM、导航、CV、人脸检测、物体抓取）
- `exercises/` — 17+ 课后练习解答
- Gazebo 物理仿真世界 + Navigation2 自主导航 + SLAM 建图
- 人脸检测、物体跟踪、机械臂抓取

---

### 操作系统

#### [os_homework/](os_homework/) — 操作系统课程
- **进程间通信** — 命名管道（FIFO）、共享内存
- **信号量** — 生产者消费者（单/多生产者、多消费者变体）
- **经典同步问题** — 哲学家进餐（含死锁演示版本）
- **虚拟内存** — vmemory 实验

---

## 🛠️ 涉及技术全景

```
语言
├── C           (OS、嵌入式、协程)
├── C++         (数据结构、算法、OpenCV、ROS 2、STL)
├── Java        (OOP、多线程、Swing、JSP、Servlet、JavaBean)
├── Python      (数据分析、ML、ROS 2、脚本工具)
├── SQL         (MySQL：查询、索引、视图、存储过程、触发器、事务)
├── HTML / CSS / JavaScript  (Web 前端基础)
│
框架 / 库
├── OpenCV          (计算机视觉)
├── scikit-learn    (机器学习)
├── LightGBM        (梯度提升)
├── Keras/LSTM      (深度学习)
├── pyecharts       (数据可视化)
├── pymysql         (Python 数据库连接)
├── ROS 2 Humble    (机器人操作系统)
├── Gazebo          (机器人仿真)
├── Navigation2     (自主导航)
│
硬件 / 平台
├── STM32F103C8  (ARM Cortex-M3)
├── Keil uVision  (嵌入式 IDE)
│
工具链
├── Git
├── VS Code / Visual Studio / IntelliJ IDEA
├── Apache Tomcat 11
├── MySQL
└── CMake / colcon (ROS 2)
```

---

## 🗺️ 学习路线图

```
大一上学期                    大一下/大二                     大二/大三
┬ C 语言入门                   ┬ C++ 系统学习                  ┬ 数学建模备赛
│ c_language_first_learning    │ C_plusplus_first_learning    │ mathematical-modeling
│                              │ Programing_Coding            │
├──────────────────────────────┤                              ├──────────────────────────
│                              ├─ 数据结构                     │ ROS 2 机器人
│                              │  Data_Structure              │ ros_pratice_ws
│                              │                              │
│                              ├─ 操作系统                     │ STM32 嵌入式
│                              │  os_homework                 │ stm32project
│                              │  C/ (协程)                    │
│                                                             ├──────────────────────────
│                              ├─ Java OOP                    │ 计算机视觉
│                              │  JAVALAB                     │ cvworkspace
│                              │  JAVAPRATICE                 │
│                              │                              │
│                              ├─ Java Web                    │
│                              │  JAVAWEBPRATICE              │
│                              │                              │
│                              ├─ MySQL                       │
│                              │  MYSQL_homework              │
│                              │                              │
│                              └─ Python                      │
│                                 python_first_learning       │
```

---

## ⚠️ 说明

- 本仓库是 **个人学习归档**，非生产级项目。代码多为课程作业或练习性质，仅供参考。
- 多数代码注释、目录名、实验报告使用中文。
- `ros_pratice_ws/src/wpr_simulation2` 克隆自 [6-robot/wpr_simulation2](https://github.com/6-robot/wpr_simulation2)，配套 ROS 2 入门课程使用。
- `JAVAWEBPRATICE/JAVAWEBLAB/apache-tomcat/` 为完整 Tomcat 11 服务器，进入 `bin/` 执行 `catalina.bat run` 即可启动（端口 8088）。
- 目录规模差异大是因为：`stm32project/` 含 Keil 标准外设库，`C_plusplus_first_learning/` 有大量 VS Code 工程模板，`ros_pratice_ws/` 含编译产物。实际手写代码量以目录内 `.c`/`.cpp`/`.java`/`.py` 文件为准。

---

> 📅 记录时间：2025–2026（本科阶段）  
> 🔄 最近更新：2026-06-20
