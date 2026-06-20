import pandas as pd
import numpy as np
import math, os
import matplotlib.pyplot as plt
from pathlib import Path
import warnings
warnings.filterwarnings('ignore')

#  设置中文字体
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False
# 基本参数
BW_RB = 360e3
NOISE_DBM_HZ = -174
NF_DB = 7
RB_MBS, RB_SBS = 100, 50
SLA_RATE = {'U':10e6, 'E':50e6, 'M':1e6}          # bit/s
DELAY_SLA_MS = {'U':5, 'E':100, 'M':500}
DT_MS = 1
N_SLOT = 50

# 速度/精度
POWERS_MBS = [15, 25, 35]
POWERS_SBS = [14, 22, 30]
RB_STEP = 10
BEST_RESPONSE_ITERS = 2

# 数据路径
DATA_DIR = r"C:\\Users\\dong\\Desktop\\数学建模培训第三轮题目\\B题\\附件\\附件4"
SAVE_DIR = Path('./问题4结果')
SAVE_DIR.mkdir(exist_ok=True)

mbs = pd.read_excel(os.path.join(DATA_DIR, 'MBS_1.xlsx'))
sbs = {i: pd.read_excel(os.path.join(DATA_DIR, f'SBS_{i}.xlsx')) for i in (1,2,3)}
task = pd.read_excel(os.path.join(DATA_DIR, 'taskflow.xlsx'))

# 用户集合
URLLC = [f'U{i}' for i in range(1,11)]
eMBB  = [f'e{i}' for i in range(1,21)]
mMTC  = [f'm{i}' for i in range(1,41)]
USERS = URLLC + eMBB + mMTC
UCLS  = {u:'U' for u in URLLC} | {u:'E' for u in eMBB} | {u:'M' for u in mMTC}

# 工具
def dbm2mw(dbm): return 10**((dbm-30)/10)
def noise_mw(rb): return dbm2mw(NOISE_DBM_HZ+NF_DB) * BW_RB * rb

def rate_bits_per_s(rb, prx_mw_sig, interf_mw):
    gamma = prx_mw_sig / (interf_mw + noise_mw(rb))
    return rb * BW_RB * math.log2(1 + gamma)

def assoc_by_best_sbs(idx):
    own = {'MBS':[], 1:[], 2:[], 3:[]}
    for u in USERS:
        losses = {i: sbs[i].iloc[idx][u] for i in (1,2,3)}
        best = min(losses, key=losses.get)
        own[best].append(u)
    return own

def spill_to_mbs(assoc, idx):
    for i in (1,2,3):
        ordered = sorted(assoc[i], key=lambda u: (['U','E','M'].index(UCLS[u]), sbs[i].iloc[idx][u]))
        kept, rb_used = [], 0
        for u in ordered:
            need = 10 if UCLS[u]=='U' else 5 if UCLS[u]=='E' else 2
            if rb_used + need <= RB_SBS:
                kept.append(u); rb_used += need
        assoc['MBS'] += [u for u in assoc[i] if u not in kept]
        assoc[i] = kept
    return assoc

def per_bs_best_response(bid, idx, assoc, K, P, q_bits, delay_ms):
    if bid == 'MBS':
        rb_total = RB_MBS
        losses = {u: mbs.iloc[idx][u] for u in assoc['MBS']}
        power_grid = POWERS_MBS
    else:
        rb_total = RB_SBS
        losses = {u: sbs[bid].iloc[idx][u] for u in assoc[bid]}
        power_grid = POWERS_SBS

    if len(losses) == 0:
        return {'U':0,'E':0,'M':0}, (power_grid[0] if bid!='MBS' else POWERS_MBS[0]), 0.0

    prx_self = {u: {p: dbm2mw(p - losses[u]) for p in power_grid} for u in losses}
    interf_map = {u: 0.0 for u in losses}
    if bid != 'MBS':
        other = [b for b in (1,2,3) if b != bid]
        for u in losses:
            interf = 0.0
            for b2 in other:
                loss_b2 = sbs[b2].iloc[idx][u]
                interf += dbm2mw(P[b2] - loss_b2)
            interf_map[u] = interf

    bestU, bestK, bestP = -1e18, None, None
    for KL in range(0, rb_total+1, RB_STEP):
        for KB in range(0, rb_total-KL+1, RB_STEP):
            KM = rb_total - KL - KB
            Kcand = {'U': KL, 'E': KB, 'M': KM}
            for p in power_grid:
                U_sum = 0.0
                for cls, Kcls in Kcand.items():
                    if Kcls == 0:
                        continue
                    users = [u for u in losses if UCLS[u]==cls]
                    if not users:
                        continue
                    rb_u = Kcls / max(1,len(users))
                    for u in users:
                        prx = prx_self[u][p]
                        interf = 0.0 if bid=='MBS' else interf_map[u]
                        R = rate_bits_per_s(rb_u, prx, interf)
                        if cls=='U':
                            ok = (R >= SLA_RATE['U']) and (delay_ms[u] + DT_MS <= DELAY_SLA_MS['U'])
                            U_sum += 0.95 if ok else 0.0
                        elif cls=='E':
                            U_sum += 1.0 if R >= SLA_RATE['E'] else (R / SLA_RATE['E'])
                        else:
                            U_sum += 1.0 if R >= SLA_RATE['M'] else 0.0
                if U_sum > bestU:
                    bestU, bestK, bestP = U_sum, Kcand, p
    return bestK, bestP, bestU

def main():
    q_bits = {u: 0.0 for u in USERS}
    delay_ms = {u: 0 for u in USERS}
    rows, sla_series, rb_series, power_series, back_delay_series = [], [], [], [], []

    K = {'MBS': {'U':30,'E':50,'M':20}, 1:{'U':10,'E':30,'M':10}, 2:{'U':10,'E':30,'M':10}, 3:{'U':10,'E':30,'M':10}}
    P = {'MBS': 25, 1: 22, 2: 22, 3: 22}

    for slot in range(N_SLOT):
        idx = slot
        arrivals = task.iloc[idx] if idx < len(task) else pd.Series({u:0 for u in USERS})
        for u in USERS:
            q_bits[u] += float(arrivals.get(u,0))

        assoc = spill_to_mbs(assoc_by_best_sbs(idx), idx)

        for _ in range(BEST_RESPONSE_ITERS):
            for bid in ['MBS',1,2,3]:
                Kb, Pb, Ub = per_bs_best_response(bid, idx, assoc, K, P, q_bits, delay_ms)
                K[bid] = Kb; P[bid] = Pb

        total_util = 0.0
        met_count = {'U':0,'E':0,'M':0}
        tot_count = {'U':0,'E':0,'M':0}

        for bid in ['MBS',1,2,3]:
            losses = {u: (mbs.iloc[idx][u] if bid=='MBS' else sbs[bid].iloc[idx][u]) for u in assoc['MBS' if bid=='MBS' else bid]}
            users = list(losses.keys())
            for cls in ['U','E','M']:
                us = [u for u in users if UCLS[u]==cls]
                Kcls = K[bid][cls]
                if not us or Kcls==0:
                    continue
                rb_u = Kcls / len(us)
                for u in us:
                    prx = dbm2mw(P[bid] - losses[u])
                    interf = 0.0
                    if bid!='MBS':
                        for b2 in [1,2,3]:
                            if b2==bid: continue
                            loss_b2 = sbs[b2].iloc[idx][u]
                            interf += dbm2mw(P[b2] - loss_b2)
                    R = rate_bits_per_s(rb_u, prx, interf)
                    sent = min(q_bits[u], R * (DT_MS/1000))
                    q_bits[u] -= sent

                    ok = False
                    if cls=='U':
                        ok = (R >= SLA_RATE['U']) and (delay_ms[u] + DT_MS <= DELAY_SLA_MS['U'])
                        total_util += 0.95 if ok else 0.0
                    elif cls=='E':
                        ok = R >= SLA_RATE['E']
                        total_util += 1.0 if ok else (R / SLA_RATE['E'])
                    else:
                        ok = R >= SLA_RATE['M']
                        total_util += 1.0 if ok else 0.0

                    met_count[cls] += 1 if ok else 0
                    tot_count[cls] += 1
                    delay_ms[u] = 0 if q_bits[u]<=1e-9 else delay_ms[u] + DT_MS

        rb_tot_slice = {
            'RB_U_total': K['MBS']['U'] + K[1]['U'] + K[2]['U'] + K[3]['U'],
            'RB_E_total': K['MBS']['E'] + K[1]['E'] + K[2]['E'] + K[3]['E'],
            'RB_M_total': K['MBS']['M'] + K[1]['M'] + K[2]['M'] + K[3]['M'],
        }

        sla_rate = {f'SLA_{k}': (met_count[k]/tot_count[k]*100 if tot_count[k]>0 else 0.0) for k in ['U','E','M']}
        backlog_mbit = sum(q_bits.values())/1e6
        avg_delay = {
            'AvgDelay_U': np.mean([delay_ms[u] for u in URLLC if q_bits[u]>0]) if any(q_bits[u]>0 for u in URLLC) else 0.0,
            'AvgDelay_E': np.mean([delay_ms[u] for u in eMBB  if q_bits[u]>0]) if any(q_bits[u]>0 for u in eMBB)  else 0.0,
            'AvgDelay_M': np.mean([delay_ms[u] for u in mMTC  if q_bits[u]>0]) if any(q_bits[u]>0 for u in mMTC)  else 0.0,
        }

        rows.append({
            'slot': slot,
            'Utility': total_util,
            'P_MBS': P['MBS'], 'P_B1': P[1], 'P_B2': P[2], 'P_B3': P[3],
            **rb_tot_slice, **sla_rate,
            'Backlog(Mbit)': backlog_mbit,
            **avg_delay
        })

        sla_series.append({'slot':slot, **sla_rate})
        rb_series.append({'slot':slot, **rb_tot_slice})
        power_series.append({'slot':slot, 'P_MBS':P['MBS'],'P_B1':P[1],'P_B2':P[2],'P_B3':P[3]})
        back_delay_series.append({'slot':slot, 'Backlog(Mbit)':backlog_mbit, **avg_delay})

    df_sum = pd.DataFrame(rows)
    df_pow = pd.DataFrame(power_series)
    df_rb = pd.DataFrame(rb_series)
    df_sla = pd.DataFrame(sla_series)
    df_bd  = pd.DataFrame(back_delay_series)

    # 控制台漂亮输出
    head_cols = ['slot','Utility','P_MBS','P_B1','P_B2','P_B3','RB_U_total','RB_E_total','RB_M_total','SLA_U','SLA_E','SLA_M','Backlog(Mbit)']
    fmt = {c:'{:.2f}'.format for c in ['Utility','SLA_U','SLA_E','SLA_M','Backlog(Mbit)']}
    print("\n【每时隙摘要】")
    print(df_sum[head_cols].to_string(index=False, formatters=fmt, max_colwidth=20))

    final_line = {
        'Utility(合计)': f"{df_sum['Utility'].sum():.2f}",
        'SLA_U(平均%)': f"{df_sum['SLA_U'].mean():.2f}",
        'SLA_E(平均%)': f"{df_sum['SLA_E'].mean():.2f}",
        'SLA_M(平均%)': f"{df_sum['SLA_M'].mean():.2f}",
        'Backlog(末尾Mbit)': f"{df_sum.iloc[-1]['Backlog(Mbit)']:.2f}"
    }
    print("\n【汇总】")
    print(pd.DataFrame([final_line]).to_string(index=False))

    # 可视化：效用趋势
    plt.figure()
    plt.plot(df_sum['slot'], df_sum['Utility'], marker='o')
    plt.xlabel('时隙'); plt.ylabel('效用'); plt.title('总效用趋势')
    plt.tight_layout(); plt.savefig(SAVE_DIR/'utility_trend.png', dpi=150)

    # 可视化：功率趋势
    plt.figure()
    for c,label in [('P_MBS','MBS'),('P_B1','B1'),('P_B2','B2'),('P_B3','B3')]:
        plt.plot(df_pow['slot'], df_pow[c], marker='.', label=label)
    plt.xlabel('时隙'); plt.ylabel('功率(dBm)'); plt.legend(); plt.title('功率选择趋势')
    plt.tight_layout(); plt.savefig(SAVE_DIR/'power_trend.png', dpi=150)

    # 可视化：SLA达标率
    plt.figure()
    plt.plot(df_sla['slot'], df_sla['SLA_U'], label='URLLC')
    plt.plot(df_sla['slot'], df_sla['SLA_E'], label='eMBB')
    plt.plot(df_sla['slot'], df_sla['SLA_M'], label='mMTC')
    plt.xlabel('时隙'); plt.ylabel('SLA达标率(%)'); plt.legend(); plt.title('各切片SLA达标率')
    plt.tight_layout(); plt.savefig(SAVE_DIR/'sla_trend.png', dpi=150)

    # 可视化：全网切片RB堆叠
    plt.figure()
    plt.stackplot(df_rb['slot'], df_rb['RB_U_total'], df_rb['RB_E_total'], df_rb['RB_M_total'], labels=['URLLC','eMBB','mMTC'])
    plt.xlabel('时隙'); plt.ylabel('RB(总)'); plt.legend(); plt.title('全网切片RB投入（MBS+SBS合计）')
    plt.tight_layout(); plt.savefig(SAVE_DIR/'rb_stack.png', dpi=150)
    plt.show()

    # 导出 Excel
    with pd.ExcelWriter(SAVE_DIR/'problem4_report.xlsx', engine='openpyxl') as w:
        df_sum.to_excel(w, index=False, sheet_name='per_slot_summary')
        df_pow.to_excel(w, index=False, sheet_name='power_trend')
        df_rb.to_excel(w,  index=False, sheet_name='rb_allocation')
        df_sla.to_excel(w, index=False, sheet_name='sla_series')
        df_bd.to_excel(w,  index=False, sheet_name='backlog_delay')
    print(f"\n已导出：{SAVE_DIR/'problem4_report.xlsx'}")
    print(f"已保存图：{SAVE_DIR/'utility_trend.png'}, {SAVE_DIR/'power_trend.png'}, {SAVE_DIR/'sla_trend.png'}, {SAVE_DIR/'rb_stack.png'}")

if __name__ == '__main__':
    main()
