import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from tqdm import tqdm
import os
import psutil

# 设置中文字体支持
plt.rcParams['font.sans-serif'] = ['SimHei']  # 使用黑体
plt.rcParams['axes.unicode_minus'] = False    # 解决负号显示问题

def main():
    print("加载数据...")
    # 只加载必要列减少内存占用
    cols_to_use = ['时间', '车牌号', '交叉口']
    dtype = {
        '车牌号': 'category',
        '交叉口': 'category'
    }
    
    # 分块读取CSV文件
    chunks = []
    for chunk in tqdm(pd.read_csv(
        'C:\\Users\\dong\\Desktop\\数学建模真题2019-2024\\数学建模2024真题\\CUMCM2024Problems\\E题\\附件2.csv', 
        encoding='gbk',
        usecols=cols_to_use,
        dtype=dtype,
        chunksize=100000
    ), desc="读取数据块"):
        chunks.append(chunk)
    
    data = pd.concat(chunks, ignore_index=True)
    
    print("数据预处理...")
    # 转换时间格式
    data['时间'] = pd.to_datetime(data['时间'], format='%Y-%m-%dT%H:%M:%S.%f')
    data['日期'] = data['时间'].dt.date
    
    # 只保留五一黄金周数据 (4月29日-5月5日)
    start_date = pd.to_datetime('2024-04-29').date()
    end_date = pd.to_datetime('2024-05-05').date()
    holiday_data = data[(data['日期'] >= start_date) & (data['日期'] <= end_date)].copy()
    del data  # 释放原始数据内存
    
    print("轨迹分析...")
    # 轨迹分析
    holiday_data.sort_values(by=['车牌号', '时间'], inplace=True)
    
    # 计算时间差和速度
    holiday_data['时间差'] = holiday_data.groupby('车牌号')['时间'].diff().dt.total_seconds()
    holiday_data['速度'] = 300 / holiday_data['时间差']  # 假设交叉口间距300米
    
    print("识别寻找停车位行为...")
    # 定义寻找停车位条件
    v_threshold = 10  # 速度阈值 (km/h)
    time_threshold = 5 * 60  # 时间阈值 (5分钟)
    
    # 将速度转换为km/h
    holiday_data['速度_km/h'] = holiday_data['速度'] * 3.6
    
    # 识别寻找停车位行为
    holiday_data['寻找停车位'] = (
        (holiday_data['速度_km/h'] < v_threshold) &
        (holiday_data['时间差'] < time_threshold)
    )
    
    print("统计巡游车辆数量...")
    # 按小时统计巡游车辆数量
    holiday_data['小时'] = holiday_data['时间'].dt.hour
    hourly_cruise = holiday_data[holiday_data['寻找停车位']].groupby('小时')['车牌号'].nunique()
    
    # 计算总巡游车辆数量
    total_cruise = holiday_data['寻找停车位'].sum()
    print(f"五一黄金周期间巡游车辆总数量: {total_cruise}")
    
    print("计算停车位需求...")
    # 参数设置
    T_park = 0.5  # 平均停车时间 (小时)
    T_total = 7 * 24  # 总时间 (小时)
    rho = 0.8  # 停车位利用率
    
    # 计算停车位需求
    P_required = (total_cruise * T_park) / (T_total * rho)
    print(f"估算的临时停车位需求: {P_required:.1f}个")
    
    # 按小时计算需求
    hourly_demand = (hourly_cruise * T_park) / rho
    
    print("结果可视化...")
    plt.figure(figsize=(12, 8))
    
    # 巡游车辆时间分布
    plt.subplot(2, 1, 1)
    hourly_cruise.plot(kind='bar')
    plt.title('巡游车辆时间分布')
    plt.xlabel('小时')
    plt.ylabel('车辆数')
    plt.grid(True)
    plt.savefig('巡游车辆时间分布.png')
    plt.show()
    
    # 停车位需求时间分布
    plt.subplot(2, 1, 2)
    hourly_demand.plot(kind='bar', color='orange')
    plt.title('停车位需求时间分布')
    plt.xlabel('小时')
    plt.ylabel('停车位需求')
    plt.grid(True)
    plt.tight_layout()
    plt.savefig('停车位需求分析.png')
    plt.show()
    
    print("\n" + "="*50)
    print(f"五一黄金周景区需要临时征用停车位数量: {round(P_required)}个")
    print("="*50)

if __name__ == "__main__":
    # 设置显示选项
    pd.set_option('display.max_columns', None)
    pd.set_option('display.width', 1000)
    
    main()