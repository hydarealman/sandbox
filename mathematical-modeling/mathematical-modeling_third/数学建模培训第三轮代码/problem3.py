import pandas as pd
import numpy as np
import os
import matplotlib.pyplot as plt
from pathlib import Path
import warnings
warnings.filterwarnings('ignore')

#  设置中文字体
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False
# 参数设置
RB_TOTAL = 50                               # 系统总RB
RB_PER_SLICE = {'URLLC': 10, 'eMBB': 5, 'mMTC': 2}  # 每类用户的最小分配RB
SLA_RATE = {'URLLC': 10e6, 'eMBB': 50e6, 'mMTC': 1e6}  # 各类SLA速率 (bps)
ALPHA = 0.95                                # URLLC 满速权重
BANDWIDTH_RB = 360e3                        # RB带宽 Hz
THERMAL_DBM = -174                          # 热噪声密度 dBm/Hz
NOISE_FIG_DB = 7                            # 噪声系数
DT = 0.001                                  # 时隙长度 1ms
POWER_RANGE = range(10, 31, 2)              # 功率搜索范围 10-30dBm
SAVE_DIR = Path("./问题3结果")
SAVE_DIR.mkdir(exist_ok=True)

# 数据读取
DATA_DIR = r"C:\\Users\\dong\\Desktop\\数学建模培训第三轮题目\\B题\\附件\\附件3"
df_bs = {i: pd.read_excel(os.path.join(DATA_DIR, f'BS{i}.xlsx')) for i in (1, 2, 3)}

# 用户分类
URLLC = [f'U{i}' for i in range(1, 7)]
eMBB = [f'e{i}' for i in range(1, 13)]
mMTC = [f'm{i}' for i in range(1, 31)]
USER_CLASS = {**{u: 'URLLC' for u in URLLC},
              **{u: 'eMBB' for u in eMBB},
              **{u: 'mMTC' for u in mMTC}}

# 工具函数
def dbm2mw(p_dbm):
    return 10 ** ((p_dbm - 30) / 10)

def sinr(loss_db, p_dbm):
    n0_mw = dbm2mw(THERMAL_DBM + NOISE_FIG_DB) * BANDWIDTH_RB
    sig_mw = dbm2mw(p_dbm - loss_db)
    return sig_mw / n0_mw

def rate(rb, sinr_val):
    return rb * BANDWIDTH_RB * np.log2(1 + sinr_val)

# 贪心RB分配
def greedy_rb(users, gain_db, p_dbm, rb_total=RB_TOTAL):
    alloc = {u: 0 for u in users}
    rest = rb_total
    # URLLC优先
    for u in users:
        if USER_CLASS[u] == 'URLLC' and rest >= RB_PER_SLICE['URLLC']:
            alloc[u] = RB_PER_SLICE['URLLC']
            rest -= RB_PER_SLICE['URLLC']
    # eMBB按信道好坏
    embb_users = [u for u in users if USER_CLASS[u] == 'eMBB']
    for u in sorted(embb_users, key=lambda x: -gain_db[x]):
        if rest >= RB_PER_SLICE['eMBB']:
            alloc[u] = RB_PER_SLICE['eMBB']
            rest -= RB_PER_SLICE['eMBB']
    # mMTC轮询
    for u in [u for u in users if USER_CLASS[u] == 'mMTC']:
        if rest >= RB_PER_SLICE['mMTC']:
            alloc[u] = RB_PER_SLICE['mMTC']
            rest -= RB_PER_SLICE['mMTC']
        else:
            break
    return alloc

# QoS计算
def qos(alloc, gain_db, p_dbm):
    total = 0.0
    for u, rb in alloc.items():
        if rb == 0:
            continue
        gamma = sinr(gain_db[u], p_dbm)
        cls = USER_CLASS[u]
        R = rate(rb, gamma)
        if cls == 'eMBB':
            total += 1 if R >= SLA_RATE['eMBB'] else R / SLA_RATE['eMBB']
        elif cls == 'URLLC':
            total += ALPHA if R >= SLA_RATE['URLLC'] else 0
        else:  # mMTC
            total += 1 if R >= SLA_RATE['mMTC'] else 0
    return total

# 功率搜索
def best_power(users, gain_db):
    best_q, best_p, best_alloc = -1, None, {}
    for p in POWER_RANGE:
        alloc = greedy_rb(users, gain_db, p)
        q = qos(alloc, gain_db, p)
        if q > best_q:
            best_q, best_p, best_alloc = q, p, alloc
    return best_p, best_alloc, best_q

# 主程序
def main():
    results = []
    N_SLOT = 10  # 10个时隙
    for k in range(N_SLOT):
        idx = int(k * DT * 1000)  # 对应行号（1ms间隔）
        assoc = {1: [], 2: [], 3: []}
        # 用户关联
        for u in USER_CLASS:
            losses = {b: df_bs[b].iloc[idx][u] for b in (1, 2, 3)}
            best_b = min(losses, key=losses.get)
            assoc[best_b].append(u)
        # 各BS优化
        slot_info = {'Slot': k}
        for b in (1, 2, 3):
            if not assoc[b]:
                slot_info.update({f'BS{b}_Power(dBm)': 0,
                                  f'BS{b}_QoS': 0,
                                  f'BS{b}_RB_alloc': {}})
                continue
            row = df_bs[b].iloc[idx]
            gain_db = {u: row[u] for u in assoc[b]}
            p_opt, alloc_opt, q_opt = best_power(assoc[b], gain_db)
            slot_info.update({f'BS{b}_Power(dBm)': p_opt,
                              f'BS{b}_QoS': q_opt,
                              f'BS{b}_RB_alloc': alloc_opt})
        results.append(slot_info)

    df_res = pd.DataFrame(results)
    print("\n【每时隙分配结果】")
    print(df_res.to_string(index=False))

    # 汇总统计
    avg_power = {f'BS{b}': df_res[f'BS{b}_Power(dBm)'].mean() for b in (1, 2, 3)}
    avg_qos = {f'BS{b}': df_res[f'BS{b}_QoS'].mean() for b in (1, 2, 3)}
    df_summary = pd.DataFrame([{
        **{f'AvgPower_{bs}': avg_power[bs] for bs in avg_power},
        **{f'AvgQoS_{bs}': avg_qos[bs] for bs in avg_qos}
    }])
    print("\n【汇总统计】")
    print(df_summary.to_string(index=False, float_format="%.2f"))

    # 可视化
    plt.figure()
    for b in (1, 2, 3):
        plt.plot(df_res['Slot'], df_res[f'BS{b}_Power(dBm)'], marker='o', label=f'BS{b} Power')
    plt.xlabel('Slot')
    plt.ylabel('Power (dBm)')
    plt.title('基站功率变化')
    plt.legend()
    plt.savefig(SAVE_DIR / 'power_trend.png', dpi=150)

    plt.figure()
    for b in (1, 2, 3):
        plt.plot(df_res['Slot'], df_res[f'BS{b}_QoS'], marker='x', label=f'BS{b} QoS')
    plt.xlabel('Slot')
    plt.ylabel('QoS')
    plt.title('基站QoS变化')
    plt.legend()
    plt.savefig(SAVE_DIR / 'qos_trend.png', dpi=150)

    plt.show()

    df_res.to_excel(SAVE_DIR / 'slot_results.xlsx', index=False)
    df_summary.to_excel(SAVE_DIR / 'summary.xlsx', index=False)
    print(f"\n已保存结果到 {SAVE_DIR}")


# 保存Excel和图片
    slot_results_path = SAVE_DIR / 'slot_results.xlsx'
    summary_path = SAVE_DIR / 'summary.xlsx'
    power_trend_path = SAVE_DIR / 'power_trend.png'
    qos_trend_path = SAVE_DIR / 'qos_trend.png'

    df_res.to_excel(slot_results_path, index=False)
    df_summary.to_excel(summary_path, index=False)

    print("\n【保存的文件路径】")
    print(f"1. 时隙详细结果: {slot_results_path}")
    print(f"2. 汇总统计结果: {summary_path}")
    print(f"3. 功率变化趋势图: {power_trend_path}")
    print(f"4. QoS变化趋势图: {qos_trend_path}")
    print(f"\n所有结果已保存到目录: {SAVE_DIR}")

if __name__ == '__main__':
    main()




