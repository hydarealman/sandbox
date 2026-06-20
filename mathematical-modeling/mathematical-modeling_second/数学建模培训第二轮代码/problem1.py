# import pandas as pd
# import numpy as np
# import matplotlib.pyplot as plt

# '''
# 数据读取与预处理模块：
# 1. 从CSV文件读取交通流量数据
# 2. 定义方向映射字典，将数字方向编码转换为可读的中英文描述
# 3. 添加方向名称列（中文）和英文方向列
# 4. 转换时间格式并提取日期、星期、小时等信息
# 5. 将一天划分为六个有意义的时间段（深夜、早高峰等）
# '''
# # 读取CSV文件，使用gbk编码解决中文问题
# data = pd.read_csv('C:\\Users\\dong\\Desktop\\数学建模真题2019-2024\\数学建模2024真题\\CUMCM2024Problems\\E题\\附件2.csv', 
#                    encoding='gbk')

# data = data[data['交叉口'] == '经中路-纬中路']


# # 定义方向映射字典，将数字方向编码转换为可读的中英文描述
# direction_mapping = {
#     1: {"中文": "东向西", "英文": "east-west"},
#     2: {"中文": "西向东", "英文": "west-east"},
#     3: {"中文": "南向北", "英文": "south-north"},
#     4: {"中文": "北向南", "英文": "north-south"}
# }

# # 添加方向名称列（中文）和英文方向列
# data["方向名称"] = data["方向"].map(lambda x: direction_mapping[x]["中文"] if x in direction_mapping else "未知")
# data["英文方向"] = data["方向"].map(lambda x: direction_mapping[x]["英文"] if x in direction_mapping else "unknown")

# # 转换时间格式并提取日期、星期、小时等信息
# data['时间'] = pd.to_datetime(data['时间'], format='%Y-%m-%dT%H:%M:%S.%f')
# data['日期'] = data['时间'].dt.date
# data['星期'] = data['时间'].dt.dayofweek  # 0=周一, 6=周日
# data['小时'] = data['时间'].dt.hour

# # 将一天划分为六个有意义的时间段（深夜、早高峰等）
# data['时间段'] = pd.cut(data['小时'], 
#                      bins=[0, 6, 9, 12, 17, 20, 24],  # 定义时间段的边界点
#                      labels=['深夜(0-6)', '早高峰(6-9)', '上午(9-12)', 
#                              '下午(12-17)', '晚高峰(17-20)', '夜间(20-24)'],
#                      right=False)  # 区间为左闭右开


# '''
# 数据分析模块：
# 1. 交叉口分析：统计每个交叉口不同方向的车流量
# 2. 小时级流量统计：按小时统计各方向的车流量
# '''
# # 交叉口分析：统计每个交叉口不同方向的车流量
# crossing_analysis = data.groupby(['交叉口', '方向名称']).size().unstack(fill_value=0)

# # 小时级流量统计：按小时统计各方向的车流量
# hourly_flow = data.groupby(['小时', '方向名称']).size().unstack(fill_value=0).reset_index()


# '''
# 数据可视化模块：
# 1. 设置中文字体支持
# 2. 绘制方向流量分布折线图:展示24小时内各方向车流量的变化趋势
# 3. 绘制时间带流量分布柱状图：展示不同时间段总体车流量的分布
# 4. 绘制交叉口方向分布堆叠柱状图：展示各交叉口不同方向车流量的分布
# '''

# # 设置中文字体支持
# plt.rcParams['font.sans-serif'] = ['SimHei']
# print("使用默认中文字体: SimHei")

# # 过滤数据 - 只保留经中路和维中路
# # data = data[data['交叉口'].isin(['经中路', '纬中路'])]



# hourly_flow_filtered = data.groupby(['小时', '方向名称']).size().unstack(fill_value=0).reset_index()

# plt.figure(figsize=(14, 8))
# for direction in direction_mapping.values():
#     dir_name = direction["中文"]
#     if dir_name in hourly_flow_filtered.columns:
#         plt.plot(hourly_flow_filtered['小时'], hourly_flow_filtered[dir_name], 
#                  label=dir_name, linewidth=2.5, marker='o')

# plt.title('经中路和纬中路-24小时各方向车流量变化', fontsize=16)  # 修改标题
# plt.xlabel('小时', fontsize=14)
# plt.ylabel('车流量', fontsize=14)
# plt.xticks(range(0, 25))
# plt.grid(True, linestyle='--', alpha=0.7)
# plt.legend()
# plt.tight_layout()
# plt.savefig('经中路和纬中路-各方向车流量变化.png', dpi=300)
# plt.show()

# # 修改2：时间带流量分布柱状图 - 使用过滤后的数据
# period_flow = data.groupby('时间段').size()  # 使用过滤后的数据
# plt.figure(figsize=(12, 7))
# period_flow.plot(kind='bar', color='skyblue', edgecolor='black')
# plt.title('经中路和纬中路-不同时间段总体车流量分布', fontsize=16)  # 修改标题
# plt.xlabel('时间段', fontsize=14)
# plt.ylabel('车流量', fontsize=14)
# plt.grid(axis='y', alpha=0.5)
# plt.tight_layout()
# plt.savefig('经中路和纬中路-时间段车流量分布.png', dpi=300)
# plt.show()

# # 修改3：交叉口方向分布堆叠柱状图 - 只显示经中路和纬中路
# # 由于数据已经过滤，所以crossing_analysis只包含这两个交叉口
# plt.figure(figsize=(14, 8))
# crossing_analysis.plot(kind='bar', stacked=True)
# plt.title('经中路和纬中路交叉口方向分布', fontsize=16)  # 修改标题
# plt.xlabel('交叉口', fontsize=14)
# plt.ylabel('车流量', fontsize=14)
# plt.legend(title='方向')
# plt.grid(axis='y', alpha=0.5)
# plt.tight_layout()
# plt.savefig('经中路和纬中路-交叉口方向分布.png', dpi=300)
# plt.show()

# '''
# 结果导出模块：
# 将分析结果保存到Excel文件,包含多个工作表：
# 1. 交叉口方向分布
# 2. 小时级流量统计
# 3. 时间段总体分布
# 4. 每个交叉口的详细流量统计
# '''
# # 使用ExcelWriter创建一个Excel文件
# with pd.ExcelWriter('交通流量分析结果.xlsx') as writer:
#     # 将交叉口分析结果写入名为'交叉口方向分布'的工作表
#     crossing_analysis.to_excel(writer, sheet_name='交叉口方向分布')
    
#     # 将小时级流量统计结果写入名为'小时级流量统计'的工作表
#     hourly_flow.to_excel(writer, sheet_name='小时级流量统计')
    
#     # 将时间段总体流量统计结果转换为DataFrame（列名为'总流量'）并写入工作表
#     period_flow.to_frame('总流量').to_excel(writer, sheet_name='时间段总体分布')
    
#     # 对每个交叉口，分别统计其小时级各方向流量，并写入单独的工作表
#     for cross in data['交叉口'].unique():
#         # 筛选当前交叉口的数据
#         cross_data = data[data['交叉口'] == cross]
#         # 按小时和方向名称分组统计流量，并展开为方向为列
#         cross_hourly = cross_data.groupby(['小时', '方向名称']).size().unstack(fill_value=0)
#         # 将结果写入以交叉口名称命名的工作表
#         cross_hourly.to_excel(writer, sheet_name=f'{cross}流量统计')

# print(crossing_analysis)

# print("----------------------------------")

# print(hourly_flow)



import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import matplotlib

# 确保使用兼容的中文字体
matplotlib.rcParams['font.sans-serif'] = ['SimHei']  # 使用黑体
matplotlib.rcParams['axes.unicode_minus'] = False    # 解决负号显示问题

'''
数据读取与预处理模块
'''
# 读取CSV文件
data = pd.read_csv('C:\\Users\\dong\\Desktop\\数学建模真题2019-2024\\数学建模2024真题\\CUMCM2024Problems\\E题\\附件2.csv', 
                   encoding='gbk')

# 只选择经中路-纬中路交叉口的数据
data = data[data['交叉口'] == '经中路-纬中路']

# 添加车辆计数列（每条记录代表一辆车）
data['车辆计数'] = 1

# 定义方向映射字典
direction_mapping = {
    1: {"中文": "东向西", "英文": "east-west"},
    2: {"中文": "西向东", "英文": "west-east"},
    3: {"中文": "南向北", "英文": "south-north"},
    4: {"中文": "北向南", "英文": "north-south"}
}

# 添加方向名称列
data["方向名称"] = data["方向"].map(lambda x: direction_mapping.get(x, {}).get("中文", "未知"))
data["英文方向"] = data["方向"].map(lambda x: direction_mapping.get(x, {}).get("英文", "unknown"))

# 转换时间格式
data['时间'] = pd.to_datetime(data['时间'], format='%Y-%m-%dT%H:%M:%S.%f', errors='coerce')
data['日期'] = data['时间'].dt.date
data['星期'] = data['时间'].dt.dayofweek  # 0=周一, 6=周日
data['小时'] = data['时间'].dt.hour

# 定义时间段函数
def get_time_period(hour):
    if 0 <= hour < 6:
        return "深夜(0-6)"
    elif 6 <= hour < 9:
        return "早高峰(6-9)"
    elif 9 <= hour < 12:
        return "上午(9-12)"
    elif 12 <= hour < 17:
        return "下午(12-17)"
    elif 17 <= hour < 20:
        return "晚高峰(17-20)"
    else:
        return "夜间(20-24)"

# 应用时间段划分
data['时间段'] = data['小时'].apply(get_time_period)

# 确保数据质量
if data.isnull().values.any():
    data = data.dropna()
    print("注意: 数据中存在空值，已删除空值行")

'''
车流量估计与分析模块
'''
# 创建车流量估算表格（按时间段和方向）
flow_estimation = pd.pivot_table(data, 
                                values='车辆计数',  # 使用车辆计数列
                                index='时间段',
                                columns='方向名称',
                                aggfunc='count',   # 使用计数方法
                                fill_value=0)

# 添加总流量列
flow_estimation['总流量'] = flow_estimation.sum(axis=1)

# 添加全时段行
full_time_period = flow_estimation.sum()
full_time_period.name = '全时段'

# 使用 pd.concat() 替代 append()
flow_estimation = pd.concat([flow_estimation, full_time_period.to_frame().T])

print("车流量估算结果:")
print(flow_estimation)

# 识别高峰低谷时段（排除全时段行）
flow_estimation_main = flow_estimation.iloc[:-1]
max_flow_period = flow_estimation_main['总流量'].idxmax()
min_flow_period = flow_estimation_main['总流量'].idxmin()

print(f"\n高峰时段: {max_flow_period}, 流量: {flow_estimation_main.loc[max_flow_period, '总流量']}")
print(f"低谷时段: {min_flow_period}, 流量: {flow_estimation_main.loc[min_flow_period, '总流量']}")

# 计算高峰流量占比
peak_flow = flow_estimation_main.loc[['早高峰(6-9)', '晚高峰(17-20)'], '总流量'].sum()
peak_flow_ratio = peak_flow / flow_estimation.loc['全时段', '总流量']
print(f"\n早晚高峰时段占总流量比例: {peak_flow_ratio:.2%}")

# 计算各方向流量比例（基于全时段总计）
direction_proportions = flow_estimation_main.drop('总流量', axis=1).sum() / flow_estimation_main.drop('总流量', axis=1).sum().sum()
direction_proportions.name = '比例'

print("\n方向流量比例:")
print(direction_proportions.to_string(float_format='{:.2%}'.format))

# 创建详细的交通流量分析报告
analysis_report = f"""
交通流量分析报告（经中路-纬中路交叉口）
{'='*60}

1. 时段流量分析:
   - 高峰时段: {max_flow_period} ({flow_estimation_main.loc[max_flow_period, '总流量']:,} 辆)
   - 低谷时段: {min_flow_period} ({flow_estimation_main.loc[min_flow_period, '总流量']:,} 辆)
   - 早晚高峰占比: {peak_flow_ratio:.2%}

2. 方向流量分布:
   - 东向西(D_EW): {direction_proportions['东向西']:.2%}
   - 西向东(D_WE): {direction_proportions['西向东']:.2%}
   - 南向北(D_NS): {direction_proportions['南向北']:.2%}
   - 北向南(D_SN): {direction_proportions['北向南']:.2%}

3. 总流量统计:
   全时段总流量: {flow_estimation.loc['全时段', '总流量']:,} 辆

4. 流量估计公式说明:
   - 南向北流量(D_NS) = ∑(各小时南向车流量)
   - 北向南流量(D_SN) = ∑(各小时北向车流量)
   - 东向西流量(D_EW) = ∑(各小时西向车流量)
   - 西向东流量(D_WE) = ∑(各小时东向车流量)
"""

print(analysis_report)


'''
数据可视化模块
'''
# 各方向车流量24小时变化趋势图
plt.figure(figsize=(14, 8))
# 按小时和方向名称分组，并包含英文方向
hourly_flow = data.groupby(['小时', '方向名称', '英文方向']).size().reset_index()
hourly_flow.rename(columns={0: '车流量'}, inplace=True)

# 创建一个方向映射（避免错误）
direction_labels = ['东向西', '西向东', '南向北', '北向南']

for direction in direction_labels:
    # 筛选特定方向的数据
    direction_data = hourly_flow[hourly_flow['方向名称'] == direction]
    if not direction_data.empty:
        # 直接使用数据中的英文方向（相同方向的所有行英文方向相同，取第一行即可）
        english_dir = direction_data['英文方向'].iloc[0]
        # 确保按小时排序
        direction_data = direction_data.sort_values('小时')
        plt.plot(direction_data['小时'], direction_data['车流量'], 
                 label=f"{direction}({english_dir})", 
                 linewidth=2.5, 
                 marker='o')

plt.title('经中路-纬中路交叉口 24小时各方向车流量变化', fontsize=16)
plt.xlabel('小时', fontsize=14)
plt.ylabel('车流量', fontsize=14)
plt.xticks(range(0, 25))
plt.grid(True, linestyle='--', alpha=0.7)
plt.legend(title='方向', title_fontsize=12)
plt.tight_layout()
plt.savefig('经中路-纬中路-各方向车流量变化.png', dpi=300)
plt.show()