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
# 常量
BW_RB = 360e3
NOISE_DBM_HZ = -174
NF_DB = 7
RB_MBS, RB_SBS = 100, 50
SLA_RATE = {'U':10e6, 'E':50e6, 'M':1e6}         # bit/s
DELAY_SLA_MS = {'U':5, 'E':100, 'M':500}
DT_MS = 1
N_SLOT = 50

# 能耗模型
FIX_EN = 28.0
ETA_RB = 0.75
ETA_PA = 0.35
def dbm2w(p_dbm): return 10**((p_dbm-30)/10)
def energy_w(power_dbm, rb_used):
    return FIX_EN + ETA_RB*rb_used + dbm2w(power_dbm)/ETA_PA

# 加速/精度
POWERS_MBS = [20, 30, 40]            # 可细化为 range(10,41,5)
POWERS_SBS = [18, 24, 30]            # 可细化为 range(10,31,2)
RB_STEP_QOS = 10                     # 第一步求QoS*时切片RB步长
RB_STEP_E   = 2                      # 第二步节能时切片RB步长
BEST_RESPONSE_ITERS = 2

# 数据
DATA_DIR = r"C:\\Users\\dong\\Desktop\\数学建模培训第三轮题目\\B题\\附件\\附件4"
SAVE_DIR = Path('./问题5结果')
SAVE_DIR.mkdir(exist_ok=True)
mbs = pd.read_excel(os.path.join(DATA_DIR, 'MBS_1.xlsx'))
sbs = {i: pd.read_excel(os.path.join(DATA_DIR, f'SBS_{i}.xlsx')) for i in (1,2,3)}
task = pd.read_excel(os.path.join(DATA_DIR, 'taskflow.xlsx'))

# 用户集
URLLC = [f'U{i}' for i in range(1,11)]
eMBB  = [f'e{i}' for i in range(1,21)]
mMTC  = [f'm{i}' for i in range(1,41)]
USERS = URLLC + eMBB + mMTC
UCLS  = {u:'U' for u in URLLC} | {u:'E' for u in eMBB} | {u:'M' for u in mMTC}

# 工具
def dbm2mw(dbm): return 10**((dbm-30)/10)
def noise_mw(rb): return dbm2mw(NOISE_DBM_HZ+NF_DB) * BW_RB * rb

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
        need = {'U':10,'E':5,'M':2}
        for u in ordered:
            n = need[UCLS[u]]
            if rb_used + n <= RB_SBS:
                kept.append(u); rb_used += n
        assoc['MBS'] += [u for u in assoc[i] if u not in kept]
        assoc[i] = kept
    return assoc

def rate_bits_per_s(rb, prx_mw_sig, interf_mw):
    gamma = prx_mw_sig / (interf_mw + noise_mw(rb))
    return rb * BW_RB * math.log2(1 + gamma)

def compute_qos_and_serve(idx, assoc, K, P, q_bits, delay_ms):
    total_util = 0.0
    sla_met = {'U':0,'E':0,'M':0}
    sla_cnt = {'U':0,'E':0,'M':0}
    rb_used = {'MBS':0, 1:0, 2:0, 3:0}

    for bid in ['MBS',1,2,3]:
        if bid=='MBS':
            losses = {u: mbs.iloc[idx][u] for u in assoc['MBS']}
        else:
            losses = {u: sbs[bid].iloc[idx][u] for u in assoc[bid]}
        users = list(losses.keys())
        for cls in ['U','E','M']:
            us = [u for u in users if UCLS[u]==cls]
            Kcls = K[bid][cls]
            if not us or Kcls==0:
                continue
            rb_u = Kcls / len(us)
            rb_used[bid] += Kcls
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

                sla_met[cls] += 1 if ok else 0
                sla_cnt[cls] += 1
                delay_ms[u] = 0 if q_bits[u]<=1e-9 else delay_ms[u] + DT_MS

    sla_rate = {k: (sla_met[k]/sla_cnt[k]*100 if sla_cnt[k]>0 else 0.0) for k in sla_met}
    return total_util, rb_used, sla_rate

def per_bs_best_response_qos(bid, idx, assoc, K, P, q_bits, delay_ms, rb_step):
    if bid == 'MBS':
        rb_total = RB_MBS
        losses = {u: mbs.iloc[idx][u] for u in assoc['MBS']}
        power_grid = POWERS_MBS
    else:
        rb_total = RB_SBS
        losses = {u: sbs[bid].iloc[idx][u] for u in assoc[bid]}
        power_grid = POWERS_SBS
    if len(losses)==0:
        return {'U':0,'E':0,'M':0}, (power_grid[0] if bid!='MBS' else POWERS_MBS[0]), 0.0

    prx_self = {u: {p: dbm2mw(p - losses[u]) for p in power_grid} for u in losses}
    interf_map = {u: 0.0 for u in losses}
    if bid!='MBS':
        other = [b for b in (1,2,3) if b!=bid]
        for u in losses:
            interf = 0.0
            for b2 in other:
                loss_b2 = sbs[b2].iloc[idx][u]
                interf += dbm2mw(P[b2] - loss_b2)
            interf_map[u] = interf

    bestU, bestK, bestP = -1e18, None, None
    for KL in range(0, rb_total+1, rb_step):
        for KB in range(0, rb_total-KL+1, rb_step):
            KM = rb_total - KL - KB
            Kcand = {'U':KL,'E':KB,'M':KM}
            for p in power_grid:
                U_sum = 0.0
                for cls,Kcls in Kcand.items():
                    if Kcls==0: continue
                    us = [u for u in losses if UCLS[u]==cls]
                    if not us: continue
                    rb_u = Kcls/len(us)
                    for u in us:
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

def total_energy(P, rb_used):
    return sum(energy_w(P[b], rb_used[b]) for b in ['MBS',1,2,3])

def greedy_power_down(idx, assoc, K, P, q_bits0, delay0, QoS_star):
    improved = True
    q_bits = q_bits0.copy()
    delay  = delay0.copy()
    # 先“恢复”到当前 K,P 下的状态
    _ = compute_qos_and_serve(idx, assoc, K, P, q_bits, delay)
    while improved:
        improved = False
        for bid in ['MBS',1,2,3]:
            candidates = (POWERS_MBS if bid=='MBS' else POWERS_SBS)
            cur_idx = candidates.index(P[bid])
            if cur_idx == 0:
                continue
            next_p = candidates[cur_idx-1]
            P_try = P.copy(); P_try[bid] = next_p
            qtmp = q_bits.copy(); dtmp = delay.copy()
            QoS, rb_used, _ = compute_qos_and_serve(idx, assoc, K, P_try, qtmp, dtmp)
            if QoS + 1e-9 >= QoS_star:
                P = P_try; q_bits = qtmp; delay = dtmp
                improved = True
    return K, P

def greedy_rb_trim(idx, assoc, K0, P, q_bits0, delay0, QoS_star, step=RB_STEP_E):
    """
    在 QoS 不低于 QoS_star 的前提下，贪心减少切片 RB 来降能耗。
    做法：每轮尝试减小任一 (bs, slice) 的 RB_step，计算新的 QoS 与能耗；
         若 QoS 仍达标且节能最多，则接受该变更，继续下一轮；直到再也减不了。
    """
    # 当前解
    K = {b: K0[b].copy() for b in ['MBS', 1, 2, 3]}

    # 先算一次当前能耗作为 baseline（要拿到四个基站的 rb_used）
    qb = q_bits0.copy(); db = delay0.copy()
    QoS_now, rb_used_now, _ = compute_qos_and_serve(idx, assoc, K, P, qb, db)
    energy_now = total_energy(P, rb_used_now)

    improved = True
    while improved:
        improved = False
        best_save = 0.0
        best_move = None

        # 枚举一次“减 step 个 RB”的候选
        for bid in ['MBS', 1, 2, 3]:
            for cls in ['U', 'E', 'M']:
                if K[bid][cls] < step:
                    continue
                # 尝试减
                K_try = {b: K[b].copy() for b in K}
                K_try[bid][cls] -= step

                # 评估 QoS 与能耗（注意传入 copy，compute 会更新队列与时延）
                qtmp = q_bits0.copy(); dtmp = delay0.copy()
                QoS_try, rb_used_try, _ = compute_qos_and_serve(idx, assoc, K_try, P, qtmp, dtmp)

                if QoS_try + 1e-9 >= QoS_star:
                    energy_try = total_energy(P, rb_used_try)
                    save = energy_now - energy_try
                    if save > best_save + 1e-9:
                        best_save = save
                        best_move = (bid, cls, K_try, energy_try)

        # 若本轮有节能收益，则接受最优的那一步
        if best_move:
            bid, cls, K, energy_now = best_move
            improved = True

    return K


def main():
    rows = []
    q_bits = {u: 0.0 for u in USERS}
    delay_ms = {u: 0 for u in USERS}

    # 初始
    K = {'MBS': {'U':30,'E':50,'M':20}, 1:{'U':10,'E':30,'M':10}, 2:{'U':10,'E':30,'M':10}, 3:{'U':10,'E':30,'M':10}}
    P = {'MBS': 30, 1: 24, 2: 24, 3: 24}

    for slot in range(N_SLOT):
        idx = slot
        arrivals = task.iloc[idx] if idx < len(task) else pd.Series({u:0 for u in USERS})
        for u in USERS: q_bits[u] += float(arrivals.get(u,0))

        assoc = spill_to_mbs(assoc_by_best_sbs(idx), idx)

        # 第一步：最大化QoS
        for _ in range(BEST_RESPONSE_ITERS):
            for bid in ['MBS',1,2,3]:
                Kb, Pb, Ub = per_bs_best_response_qos(bid, idx, assoc, K, P, q_bits, delay_ms, RB_STEP_QOS)
                K[bid] = Kb; P[bid] = Pb

        q_copy = q_bits.copy(); d_copy = delay_ms.copy()
        QoS_star, rb_used_star, sla_star = compute_qos_and_serve(idx, assoc, K, P, q_copy, d_copy)

        # 第二步：先降功率，再裁剪RB
        K2, P2 = greedy_power_down(idx, assoc, K, P, q_bits.copy(), delay_ms.copy(), QoS_star)
        K3     = greedy_rb_trim(idx, assoc, K2, P2, q_bits.copy(), delay_ms.copy(), QoS_star, step=RB_STEP_E)

        # 以节能后的 (K3,P2) 重新计算实际 QoS/Energy
        q_tmp = q_bits.copy(); d_tmp = delay_ms.copy()
        QoS, rb_used, sla = compute_qos_and_serve(idx, assoc, K3, P2, q_tmp, d_tmp)
        E_total = total_energy(P2, rb_used)
        E_break = {
            'E_MBS': energy_w(P2['MBS'], rb_used['MBS']),
            'E_B1':  energy_w(P2[1], rb_used[1]),
            'E_B2':  energy_w(P2[2], rb_used[2]),
            'E_B3':  energy_w(P2[3], rb_used[3]),
        }
        q_bits, delay_ms = q_tmp, d_tmp

        rows.append({
            'slot':slot,
            'QoS*':QoS_star, 'QoS':QoS,
            'E_total(W)':E_total,
            'P_MBS':P2['MBS'], 'P_B1':P2[1], 'P_B2':P2[2], 'P_B3':P2[3],
            'RB_MBS':rb_used['MBS'],'RB_B1':rb_used[1],'RB_B2':rb_used[2],'RB_B3':rb_used[3],
            'SLA_U(%)':sla['U'],'SLA_E(%)':sla['E'],'SLA_M(%)':sla['M'],
            'Backlog(Mbit)': sum(q_bits.values())/1e6,
            **E_break
        })

    df = pd.DataFrame(rows)
    head_cols = ['slot','QoS*','QoS','E_total(W)','P_MBS','P_B1','P_B2','P_B3','RB_MBS','RB_B1','RB_B2','RB_B3','SLA_U(%)','SLA_E(%)','SLA_M(%)','Backlog(Mbit)']
    fmts = {c:'{:.2f}'.format for c in ['QoS*','QoS','E_total(W)','SLA_U(%)','SLA_E(%)','SLA_M(%)','Backlog(Mbit)']}
    print("\n【每时隙摘要】")
    print(df[head_cols].to_string(index=False, formatters=fmts))

    tail = {
        'QoS*(合计)': f"{df['QoS*'].sum():.2f}",
        'QoS(合计)':  f"{df['QoS'].sum():.2f}",
        'E_total(平均W)': f"{df['E_total(W)'].mean():.2f}",
        'SLA_U(平均%)': f"{df['SLA_U(%)'].mean():.2f}",
        'SLA_E(平均%)': f"{df['SLA_E(%)'].mean():.2f}",
        'SLA_M(平均%)': f"{df['SLA_M(%)'].mean():.2f}",
        'Backlog(末尾Mbit)': f"{df.iloc[-1]['Backlog(Mbit)']:.2f}"
    }
    print("\n【汇总】")
    print(pd.DataFrame([tail]).to_string(index=False))

    SAVE_DIR.mkdir(exist_ok=True)
    df.to_excel(SAVE_DIR/'problem5_energy_report.xlsx', index=False)

    plt.figure()
    plt.plot(df['slot'], df['E_total(W)'], marker='o')
    plt.xlabel('时隙'); plt.ylabel('总能耗(W)'); plt.title('能耗趋势'); plt.tight_layout()
    plt.savefig(SAVE_DIR/'energy_trend.png', dpi=150)

    plt.figure()
    for c,label in [('P_MBS','MBS'),('P_B1','B1'),('P_B2','B2'),('P_B3','B3')]:
        plt.plot(df['slot'], df[c], marker='.', label=label)
    plt.xlabel('时隙'); plt.ylabel('功率(dBm)'); plt.legend(); plt.title('功率趋势'); plt.tight_layout()
    plt.savefig(SAVE_DIR/'power_trend.png', dpi=150)

    plt.figure()
    plt.stackplot(df['slot'], df['RB_MBS'], df['RB_B1'], df['RB_B2'], df['RB_B3'], labels=['MBS','B1','B2','B3'])
    plt.xlabel('时隙'); plt.ylabel('RB(总)'); plt.legend(); plt.title('各站RB投入'); plt.tight_layout()
    plt.savefig(SAVE_DIR/'rb_stack.png', dpi=150)

    plt.figure()
    plt.plot(df['slot'], df['SLA_U(%)'], label='URLLC')
    plt.plot(df['slot'], df['SLA_E(%)'], label='eMBB')
    plt.plot(df['slot'], df['SLA_M(%)'], label='mMTC')
    plt.xlabel('时隙'); plt.ylabel('SLA达标率(%)'); plt.legend(); plt.title('SLA达标率'); plt.tight_layout()
    plt.savefig(SAVE_DIR/'sla_trend.png', dpi=150)

    print(f"\n已导出：{SAVE_DIR/'problem5_energy_report.xlsx'}")
    print(f"已保存图：{SAVE_DIR/'energy_trend.png'}, {SAVE_DIR/'power_trend.png'}, {SAVE_DIR/'rb_stack.png'}, {SAVE_DIR/'sla_trend.png'}")

if __name__ == '__main__':
    main()
