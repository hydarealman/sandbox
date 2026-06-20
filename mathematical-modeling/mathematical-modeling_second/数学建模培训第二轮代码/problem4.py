import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from scipy import stats
from matplotlib.patches import Patch
import re

# 设置中文字体支持
plt.rcParams['font.sans-serif'] = ['SimHei']  # 使用黑体
plt.rcParams['axes.unicode_minus'] = False    # 解决负号显示问题

def evaluate_traffic_control_measures(df):
    """
    评估景区周边道路临时交通管控措施效果
    """
    # 1. 数据预处理
    print("开始数据预处理...")
    
    # 检查并重命名列名
    if '时间' in df.columns and '通过时间' not in df.columns:
        df.rename(columns={'时间': '通过时间'}, inplace=True)
    
    # 确保有通过时间列
    if '通过时间' not in df.columns:
        print("错误: 数据中缺少时间列")
        return {}
    
    df['通过时间'] = pd.to_datetime(df['通过时间'])
    
    # 管控时间段 (5月1日-5月5日)
    control_period = ('2024-05-01', '2024-05-05')
    start_date, end_date = control_period
    
    # 2. 标注管控要素（根据图片信息）
    # 管控路段（红色） - 来自图片描述
    control_roads = [
        "环西路-纬中路", "经中路-纬中路", "环东路-纬中路",
        "环北路-经中路", "环南路-经中路"
    ]
    df['路段类型'] = np.where(df['交叉口'].isin(control_roads), '管控路段', '普通路段')
    
    # 进出路线定义（完全按照图片说明）
    # 驶出景区路线（绿色箭头）
    out_routes = [
        "经中路-纬中路", 
        "环西路-纬中路", 
        "环东路-纬中路",
        "环北路-经中路"
    ]
    
    # 进入景区路线（橙色箭头）
    in_routes = [
        "环南路-经中路",
        "环东路-经中路"
    ]
    
    # 3. 改进基准期选择（前两周同期）
    base_start = pd.Timestamp(start_date) - pd.Timedelta(weeks=2)
    base_end = pd.Timestamp(start_date) - pd.Timedelta(days=1)  # 管控前一天结束
    base_mask = (df['通过时间'] >= base_start) & (df['通过时间'] <= base_end)
    control_mask = (df['通过时间'] >= start_date) & (df['通过时间'] <= end_date)
    
    # 4. 关键指标计算
    print("计算关键指标...")
    
    # 筛选两条主路的数据
    main_roads = ['环西路', '经中路']
    pattern = '|'.join(main_roads)
    main_roads_df = df[df['交叉口'].str.contains(pattern)]
    
    # 按小时分组计算指标
    def calculate_hourly_metrics(df):
        # 添加车辆标识（使用车牌号）
        if '车辆标识' not in df.columns:
            if '车牌号' in df.columns:
                df['车辆标识'] = df['车牌号']
            else:
                # 创建唯一标识符
                df['车辆标识'] = range(1, len(df)+1)
        
        # 添加速度列 - 如果数据中有通行时间和距离，则计算真实速度
        if '速度' not in df.columns:
            if '通行时间' in df.columns and '距离' in df.columns:
                # 计算速度 = 距离 / (通行时间/3600) 得到km/h
                df['速度'] = df['距离'] / (df['通行时间'] / 3600)
                # 移除可能的无穷大或NaN
                df['速度'] = df['速度'].replace([np.inf, -np.inf], np.nan)
                df['速度'] = df['速度'].fillna(30)  # 用30填充缺失值
            else:
                # 使用分时段默认速度
                df['小时'] = df['通过时间'].dt.hour
                # 高峰时段：早晚高峰（7-9, 17-19）
                peak_hours = list(range(7, 10)) + list(range(17, 20))
                df['速度'] = np.where(df['小时'].isin(peak_hours), 25, 35)
        
        return df.groupby(['交叉口', pd.Grouper(key='通过时间', freq='h')]).agg(
            车流量=('车辆标识', 'count'),
            平均速度=('速度', 'mean')
        ).reset_index()
    
    base_metrics = calculate_hourly_metrics(main_roads_df.loc[base_mask])
    control_metrics = calculate_hourly_metrics(main_roads_df.loc[control_mask])
    
    # 5. 主干道效果分析
    results = {}
    
    for road in main_roads:
        print(f"分析{road}的管控效果...")
        # 获取与当前主干道相关的交叉口
        road_junctions = [j for j in control_roads if road in j]
        if not road_junctions: continue
        
        road_base = base_metrics[base_metrics['交叉口'].isin(road_junctions)]
        road_control = control_metrics[control_metrics['交叉口'].isin(road_junctions)]
        
        # 流量变化分析
        flow_base = road_base.groupby(pd.Grouper(key='通过时间', freq='D'))['车流量'].sum().mean()
        flow_control = road_control.groupby(pd.Grouper(key='通过时间', freq='D'))['车流量'].sum().mean()
        flow_change = (flow_control - flow_base) / flow_base * 100
        
        # 速度变化分析
        speed_base = road_base.groupby(pd.Grouper(key='通过时间', freq='D'))['平均速度'].mean().mean()
        speed_control = road_control.groupby(pd.Grouper(key='通过时间', freq='D'))['平均速度'].mean().mean()
        speed_change = (speed_control - speed_base) / speed_base * 100
        
        # 改进的显著性检验（对样本量较小的情况使用非参数检验）
        try:
            # 对样本量较小的情况使用Mann-Whitney U检验
            if len(road_control) < 30 or len(road_base) < 30:
                _, flow_p = stats.mannwhitneyu(road_control['车流量'], road_base['车流量'])
                _, speed_p = stats.mannwhitneyu(road_control['平均速度'], road_base['平均速度'])
            else:
                # 使用t检验，处理NaN值
                _, flow_p = stats.ttest_ind(
                    road_control['车流量'].dropna(), 
                    road_base['车流量'].dropna(),
                    equal_var=False  # 假设方差不相等
                )
                _, speed_p = stats.ttest_ind(
                    road_control['平均速度'].dropna(), 
                    road_base['平均速度'].dropna(),
                    equal_var=False  # 假设方差不相等
                )
        except Exception as e:
            print(f"显著性检验错误: {e}")
            flow_p = 1.0
            speed_p = 1.0
        
        # 存储每日流量和速度数据（用于后续可视化）
        daily_flow_base = road_base.groupby(pd.Grouper(key='通过时间', freq='D'))['车流量'].sum()
        daily_flow_control = road_control.groupby(pd.Grouper(key='通过时间', freq='D'))['车流量'].sum()
        daily_speed_base = road_base.groupby(pd.Grouper(key='通过时间', freq='D'))['平均速度'].mean()
        daily_speed_control = road_control.groupby(pd.Grouper(key='通过时间', freq='D'))['平均速度'].mean()
        
        results[road] = {
            '流量变化(%)': flow_change,
            '速度变化(%)': speed_change,
            '流量显著性': flow_p,
            '速度显著性': speed_p,
            '基准流量': daily_flow_base,
            '管控流量': daily_flow_control,
            '基准速度': daily_speed_base,
            '管控速度': daily_speed_control
        }
    
    # 6. 可视化结果
    print("生成可视化结果...")
    visualize_results(results, control_period, main_roads)
    
    return results

def visualize_results(results, control_period, main_roads):
    """生成管控效果可视化图表"""
    plt.figure(figsize=(15, 10))
    plt.suptitle(f'五一黄金周临时交通管控措施效果评估 ({control_period[0]}至{control_period[1]})', fontsize=16)
    
    # 颜色设置
    palette = {'环西路': '#1f77b4', '经中路': '#ff7f0e'}
    
    # 1. 车流量对比（分道路）
    plt.subplot(2, 2, 1)
    for road in main_roads:
        if road not in results: continue
        # 转换日期格式
        base_dates = [d.strftime('%m-%d') for d in results[road]['基准流量'].index]
        control_dates = [d.strftime('%m-%d') for d in results[road]['管控流量'].index]
        
        # 绘制基准期和管控期流量
        plt.plot(base_dates, results[road]['基准流量'], 
                 color=palette[road], linestyle='--', alpha=0.7, label=f'{road}基准期')
        plt.plot(control_dates, results[road]['管控流量'], 
                 color=palette[road], linewidth=2.5, label=f'{road}管控期')
    
    plt.title('主干道日均车流量对比')
    plt.ylabel('车辆数/日')
    plt.legend()
    plt.grid(True, linestyle=':', alpha=0.6)
    
    # 2. 车速变化
    plt.subplot(2, 2, 2)
    for road in main_roads:
        if road not in results: continue
        # 转换日期格式
        base_dates = [d.strftime('%m-%d') for d in results[road]['基准速度'].index]
        control_dates = [d.strftime('%m-%d') for d in results[road]['管控速度'].index]
        
        # 绘制基准期和管控期车速
        plt.plot(base_dates, results[road]['基准速度'], 
                 color=palette[road], linestyle='--', alpha=0.7)
        plt.plot(control_dates, results[road]['管控速度'], 
                 color=palette[road], linewidth=2.5, label=f'{road}')
    
    plt.title('主干道日均通行速度变化')
    plt.ylabel('平均速度 (km/h)')
    plt.legend()
    plt.grid(True, linestyle=':', alpha=0.6)
    
    # 3. 指标综合对比
    plt.subplot(2, 2, 3)
    # 准备柱状图数据
    metrics_data = []
    for road in main_roads:
        if road not in results: continue
        metrics_data.append({
            '道路': road,
            '指标': '流量变化(%)',
            '值': results[road]['流量变化(%)'],
            '显著': results[road]['流量显著性'] < 0.05
        })
        metrics_data.append({
            '道路': road,
            '指标': '速度变化(%)',
            '值': results[road]['速度变化(%)'],
            '显著': results[road]['速度显著性'] < 0.05
        })
    
    metrics_df = pd.DataFrame(metrics_data)
    
    # 绘制柱状图
    ax = sns.barplot(x='指标', y='值', hue='道路', data=metrics_df)
    
    # 添加显著性标记
    y_max = metrics_df['值'].max() * 1.1
    y_min = metrics_df['值'].min() * 1.1
    for i, bar in enumerate(ax.patches):
        if metrics_df.iloc[i//2]['显著']:
            x = bar.get_x() + bar.get_width() / 2
            y = bar.get_height() + (0.02 * (y_max-y_min) if bar.get_height() > 0 else -0.05 * (y_max-y_min))
            plt.text(x, y, '*', ha='center', fontsize=14, fontweight='bold')
    
    plt.title('管控措施效果综合对比')
    plt.ylabel('变化率(%)')
    plt.axhline(0, color='black', linewidth=0.8)
    plt.legend()
    plt.grid(axis='y', linestyle=':', alpha=0.6)
    
    # 添加图例说明
    legend_elements = [
        Patch(facecolor='gray', label='* 表示变化显著(p<0.05)'),
    ]
    plt.legend(handles=legend_elements, loc='upper left')
    
    # 4. 效果评价总结
    plt.subplot(2, 2, 4)
    plt.axis('off')
    
    summary_text = "临时交通管控措施效果评价总结:\n\n"
    for road in main_roads:
        if road not in results: continue
        
        metrics = results[road]
        flow_sign = "增加" if metrics['流量变化(%)'] > 0 else "减少"
        speed_sign = "提高" if metrics['速度变化(%)'] > 0 else "降低"
        
        flow_sig = "显著" if metrics['流量显著性'] < 0.05 else "不显著"
        speed_sig = "显著" if metrics['速度显著性'] < 0.05 else "不显著"
        
        road_summary = (
            f"{road}:\n"
            f"- 流量变化: {abs(metrics['流量变化(%)']):.1f}% {flow_sign} ({flow_sig})\n"
            f"- 速度变化: {abs(metrics['速度变化(%)']):.1f}% {speed_sign} ({speed_sig})\n"
        )
        
        # 改进的效果评级标准（考虑流量增加情况）
        if metrics['流量变化(%)'] < -5 and metrics['速度变化(%)'] > 5:
            road_summary += "- 效果评价: ★★★★★ (效果显著)\n"
        elif metrics['流量变化(%)'] < 0 and metrics['速度变化(%)'] > 0:
            road_summary += "- 效果评价: ★★★★ (效果良好)\n"
        elif metrics['流量变化(%)'] < 0 or metrics['速度变化(%)'] > 0:
            road_summary += "- 效果评价: ★★★ (效果一般)\n"
        else:  # 流量没有减少反而增加
            if metrics['流量变化(%)'] > 10:
                road_summary += "- 效果评价: ★ (效果差)\n"
            else:
                road_summary += "- 效果评价: ★★ (效果较差)\n"
        
        summary_text += road_summary + "\n"
    
    plt.text(0.05, 0.95, summary_text, fontsize=12, ha='left', va='top', transform=plt.gca().transAxes)
    
    plt.tight_layout()
    plt.savefig(f'traffic_control_results_{control_period[0]}_{control_period[1]}.png')
    plt.show()

# 主程序
if __name__ == "__main__":
    # 读取数据
    print("读取交通数据...")
    try:
        df = pd.read_csv('C:\\Users\\dong\\Desktop\\数学建模真题2019-2024\\数学建模2024真题\\CUMCM2024Problems\\E题\\附件2.csv', 
                   encoding='gbk')
        print("数据读取成功!")
        print("数据列名:", df.columns.tolist())  # 打印列名用于调试
    except Exception as e:
        print(f"读取数据失败: {e}")
        exit()
    
    # 检查必要列是否存在
    required_columns = ['交叉口']
    
    # 时间列处理
    if '通过时间' not in df.columns and '时间' in df.columns:
        df.rename(columns={'时间': '通过时间'}, inplace=True)
    
    if '通过时间' not in df.columns:
        print("错误: 数据中缺少时间列")
        exit()
    
    # 车辆标识列处理
    if '车辆标识' not in df.columns:
        if '车牌号' in df.columns:
            df['车辆标识'] = df['车牌号']
        else:
            # 创建唯一标识符
            df['车辆标识'] = range(1, len(df)+1)
    
    # 执行评估
    print("开始评估临时交通管控措施效果...")
    results = evaluate_traffic_control_measures(df)
    
    # 生成报告
    if results:
        print("\n" + "="*50)
        print("五一黄金周景区周边道路管控措施效果评估报告")
        print("="*50)
        
        for road, metrics in results.items():
            print(f"\n主路: {road}")
            print("-"*40)
            
            # 流量变化
            flow_sign = "+" if metrics['流量变化(%)'] > 0 else ""
            flow_sig = "**" if metrics['流量显著性'] < 0.05 else ""
            print(f"流量变化: {flow_sign}{metrics['流量变化(%)']:.1f}%{flow_sig}")
            
            # 速度变化
            speed_sign = "+" if metrics['速度变化(%)'] > 0 else ""
            speed_sig = "**" if metrics['速度显著性'] < 0.05 else ""
            print(f"速度变化: {speed_sign}{metrics['速度变化(%)']:.1f}%{speed_sig}")
            
            # 改进的效果评级
            if metrics['流量变化(%)'] < -5 and metrics['速度变化(%)'] > 5:
                print("评价: 措施效果优秀 ★★★★★")
            elif metrics['流量变化(%)'] < 0 and metrics['速度变化(%)'] > 0:
                print("评价: 措施效果良好 ★★★★")
            elif metrics['流量变化(%)'] < 0 or metrics['速度变化(%)'] > 0:
                print("评价: 效果一般 ★★★")
            else:
                if metrics['流量变化(%)'] > 10:
                    print("评价: 效果差 ★")
                else:
                    print("评价: 效果较差 ★★")
        
        print("\n注: **表示变化具有统计学显著性(p<0.05)")
        print("="*50)
    else:
        print("未生成有效结果")

