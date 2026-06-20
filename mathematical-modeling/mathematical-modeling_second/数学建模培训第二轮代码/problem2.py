import numpy as np
import pandas as pd
from scipy.optimize import linprog

# 读取CSV文件并打印列名，确认实际列名
data = pd.read_csv('C:\\Users\\dong\\Desktop\\数学建模真题2019-2024\\数学建模2024真题\\CUMCM2024Problems\\E题\\附件2.csv', 
                   encoding='gbk')
print("实际数据列名:", data.columns.tolist())  # 这里会输出实际列名用于确认
pattern = r'^(经中路|纬中路).*'
data = data[data['交叉口'].str.contains(pattern, regex=True)]

# 根据实际列名设置变量
crossing_column = "交叉口"  # 实际的交叉口列名是"交叉口"
direction_column = "方向"    # 方向列名
flow_column = None          # 您数据中没有车流量列，需要用计数代替

# 定义方向映射
direction_mapping = {
    1: {"中文": "东向西", "英文": "east-west"},
    2: {"中文": "西向东", "英文": "west-east"},
    3: {"中文": "南向北", "英文": "south-north"},
    4: {"中文": "北向南", "英文": "north-south"}
}

# 添加方向名称列
data["方向名称"] = data[direction_column].map(lambda x: direction_mapping.get(x, {}).get("中文", "未知"))
data["英文方向"] = data[direction_column].map(lambda x: direction_mapping.get(x, {}).get("英文", "unknown"))

# 时间处理
data['时间'] = pd.to_datetime(data['时间'], format='%Y-%m-%dT%H:%M:%S.%f')
data['日期'] = data['时间'].dt.date
data['星期'] = data['时间'].dt.dayofweek  # 0=周一, 6=周日
data['小时'] = data['时间'].dt.hour
data['时间段'] = pd.cut(data['小时'], 
                     bins=[0, 6, 9, 12, 17, 20, 24],
                     labels=['深夜(0-6)', '早高峰(6-9)', '上午(9-12)', 
                             '下午(12-17)', '晚高峰(17-20)', '夜间(20-24)'],
                     right=False)

# 关键修改：由于没有车流量列，我们使用车辆计数代替车流量
def calculate_direction_flows(group):
    # 统计南北方向（方向3和4）的车辆数
    ns_flow = group[group[direction_column].isin([3, 4])].shape[0]
    
    # 统计东西方向（方向1和2）的车辆数
    ew_flow = group[group[direction_column].isin([1, 2])].shape[0]
    
    return pd.Series({"north_south_flow": ns_flow, "east_west_flow": ew_flow})

# 使用正确的交叉口列名进行分组
flows_df = data.groupby([crossing_column, "时间段"]).apply(calculate_direction_flows).reset_index()

# 打印前几行确认数据处理正确
print("\n流量计算结果预览:")
print(flows_df.head())

# 定义优化函数
def optimize_signal_timing(df_flows, crossing_col):
    # 确定唯一交叉口
    intersections = df_flows[crossing_col].unique()
    n = len(intersections)
    
    # 提取流量数据
    ns_flows = []
    ew_flows = []
    
    for inter in intersections:
        # 对于每个交叉口，我们取它在时间段内的平均值
        inter_data = df_flows[df_flows[crossing_col] == inter]
        ns_flows.append(inter_data["north_south_flow"].mean())
        ew_flows.append(inter_data["east_west_flow"].mean())
    
    # 每个交叉口有两个绿灯时间变量：南北和东西方向
    objective_coefficients = []
    for i in range(n):
        objective_coefficients.append(-ns_flows[i])
        objective_coefficients.append(-ew_flows[i])
    objective_coefficients = np.array(objective_coefficients)
    
    # 约束条件参数
    signal_max_time = 60
    min_green_time = 10
    
    # 约束1：每个交叉口的绿灯时间之和不超过总周期
    A_ineq = np.zeros((n, 2 * n))
    for i in range(n):
        A_ineq[i, 2 * i] = 1
        A_ineq[i, 2 * i + 1] = 1
    b_ineq = np.ones(n) * signal_max_time
    
    # 约束2：最小绿灯时间约束
    A_min = np.zeros((2 * n, 2 * n))
    for i in range(2 * n):
        A_min[i, i] = -1
    b_min = np.ones(2 * n) * -min_green_time
    
    # 合并所有不等式约束
    A_ub = np.vstack([A_ineq, A_min])
    b_ub = np.hstack([b_ineq, b_min])
    
    # 线性规划求解
    result = linprog(
        c=objective_coefficients,
        A_ub=A_ub,
        b_ub=b_ub,
        bounds=(0, None),
    )
    
    return result, ns_flows, ew_flows, intersections

# 4. 执行优化并存储结果
all_results = [] # 存储所有时间段的结果

for period in ['早高峰(6-9)', '晚高峰(17-20)']:
    period_flows = flows_df[flows_df["时间段"] == period]
    
    if not period_flows.empty:
        result, ns_flows, ew_flows, intersections = optimize_signal_timing(period_flows,crossing_column)
        
        if result.success:
            # 创建当前时间段的DataFrame
            period_results = []
            for i, inter in enumerate(intersections):
                ns_green = result.x[2 * i]
                ew_green = result.x[2 * i + 1]
                cycle_time = ns_green + ew_green
                
                period_results.append({
                    "时间段": period,
                    "交叉口": inter,
                    "南北流量": ns_flows[i],
                    "东西流量": ew_flows[i],
                    "南北绿灯时长(s)": ns_green,
                    "东西绿灯时长(s)": ew_green,
                    "信号周期时长(s)": cycle_time
                })
            
            # 添加到总结果列表
            all_results.extend(period_results)

# 5. 导出到Excel
if all_results:
    # 创建结果DataFrame
    results_df = pd.DataFrame(all_results)
    
    # 按时间段和交叉口排序
    results_df = results_df.sort_values(["时间段", "交叉口"])
    
    # 导出到Excel
    output_path = "C:\\Users\\dong\\Desktop\\信号配时优化结果.xlsx"
    results_df.to_excel(output_path, index=False)
    print(f"优化结果已保存至: {output_path}")
else:
    print("未生成有效优化结果")