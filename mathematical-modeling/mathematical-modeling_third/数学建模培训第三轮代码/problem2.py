import pandas as pd
import numpy as np
import random
from itertools import product
from collections import defaultdict
import matplotlib
import matplotlib.pyplot as plt
 

# 设置中文字体
matplotlib.rcParams['font.sans-serif'] = ['SimHei']     # 使用黑体
matplotlib.rcParams['axes.unicode_minus'] = False       # 解决符号显示问题
"""
URLLC(超可靠低延迟)
eMBB(增强移动宽带)
mMTC(大规模物联网)
"""

"""
物理层约束：
    带宽约束
    噪声约束
    信号衰减约束
    SINO约束
"""

"""
动态规划约束:
    资源守恒约束: 分配的RB数超过物理限制将导致系统崩溃
    SLA服务质量约束: 运营商与切片租户之间的质量契约
    时态耦合约束: 当前决策影响未来状态
    状态转移约束: 残留数据会激烈到下一时刻
"""
class EnhancedDynamicScheduler:
    # 5G网络切片资源调度器类的初始化函数 
    def __init__(self,data_path,scenario_params=None):
        """增强版动态调度器"""
        self.time_steps = 10                    # 调度时间步数
        self.step_duration = 0.1                # 每步时长
        self.total_rb = 50                      # 总资源块数

        self.setp_default_params()              # 设置默认参数
        # 如果有场景参数设置场景参数
        if scenario_params:
            self.update_params(scenario_params)
        
        # 系统数据加载
        self.load_channel_data(data_path)
        # 重置系统状态
        self.reset_system_state()

        print("增强版动态网络切片资源调度器初始化完成")

    def setp_default_params(self):
        """设置系统参数 - 根据附录技术参数"""
        # 物理层参数
        self.bandwidth_per_rb = 360e3   # 每个RB带宽,题目要求360kHz
        self.noise_figure_db = 7        # 接收噪声系数    NF = 7db
        self.thermal_noise_dbm = -174   # 热噪声功率谱密度   dbm/Hz

        self.sla_requirement = {
            'URLLC': {
                'min_rb': 5,            # 最小资源块数
                'sla_rate': 10e6,       # 保证传输速率
                'sla_delay': 5e-3,      # 最大时延要求
                'penalty_coeff': 5e-3   # 违规惩罚系数
            },
            'eMBB': {
                'min_rb': 5,
                'sla_rate': 50e6,
                'sla_delay': 100e-3,
                'penalty_coeff': 3
            },
            'mMTC': {
                'min_rb': 2,
                'sla_rate': 10e6,
                'sla_delay': 500e-3,
                'penalty_coeff': 1
            }
        }

        # 任务数据量范围
        self.task_size_ranges = {
            'URLLC': (0.01e6,0.012e6),
            'eMBB':(0.1e6,0.12e6),
            'mMTC': (0.012e6,0.014e6)
        }

        # 到达分布类型
        self.arrival_distributions = {
            'URLLC': 'poisson', # 泊松分布
            'eMBB': 'uniform',  # 均匀分布
            'mMTC': 'uniform'   # 均匀分布
        }

        # 业务到达率
        self.arrival_rates = {
            'URLLC': 0.011e6,
            'eMBB': 01.11e6,
            'mMTC': 0.013e6
        }

        # 资源分配范围
        self.rb_limits = {
            'min' : {'URLLC': 10, 'eMBB': 5, 'mMTC': 2},
            'max' : {'URLLC': 30, 'eMBB': 35, 'mMTC': 15}
        }

        # MOP参数
        self.gamma = 0.95   # 时间折扣系数

        # 质量函数参数
        self.utility_discount = 0.95    # 效用折扣系数

    def update_params(self,params):
        """更新参数"""
        for key,value in params.items():
            if hasattr(self,key):
                setattr(self,key,value)

    def load_channel_data(self,data_path):
        """加载信道参数"""
        try:
            self.df = pd.read_excel(data_path)
            self.process_channel_data()
        except Exception as e:
            print(f"数据加载失败次数:{e}")
            self.create_sample_channel_data()

    def process_channel_data(self):
        """处理信道数据"""
        current_data = self.df.iloc[0]

        # 一种嵌套字典,字典里面嵌套着列表
        self.channel_gain  = {
            'URLLC': [],
            'eMBB': [],
            'mMTC': []
        }

        # 读取信道增益
        for col in self.df.columns:
            if col.startswith('U') and col in current_data:
                self.channel_gain['URLLC'].append(current_data[col])
            elif col.startswith('e') and col in current_data:
                self.channel_gain['eMBB'].append(current_data[col])
            elif col.startswith('m') and col in current_data:
                self.channel_gain['mMTC'].append(current_data[col])

        print(f"信道增益加载完成")
        for slice_type , gains in self.channel_gain.items():
            if gains:
                print(f"{slice_type}: {len(gains)}个用户")

    def reset_system_state(self):
        """重置系统参数"""
        self.queue_lengths = {'URLLC': 0, 'eMBB': 0,'mMTC': 0}
        self.history = {
            'queue_lengths': [],    # 各时间步的队列长度
            'arrivals': [],         # 业务到大量记录
            'allocations': [],      # RB分配方案历史
            'transmissions': [],    # 实际传输量记录
            'qualities': [],        # 每步质量函数值
            'channel_rates': []     # 信道速率历史
        }
        self.sla_violations = {
            'urllc_delay': 0,       # URLLC时违规次数
            "embb_throughput": 0,   # eMBB吞吐量违规次数
            'mmtc_drops': 0         # mMTC丢包违规次数
        }

        self.embb_throughput_accumulators = 0   # eMBB吞吐类及其重置

    def generate_arrivals(self,t):
        """生成业务到达量"""
        arrivals = {}

        # URLLC : 泊松分布
        if self.arrival_distributions['URLLC'] == 'poisson':
            lambda_urllc = self.arrival_rates['URLLC'] / self.step_duration
            arrivals['URLLC'] = np.random.poisson(lambda_urllc) * self.step_duration

        # eMBB : 均匀分布
        if self.arrival_distributions['eMBB'] == 'uniform':
            min_size, max_size = self.task_size_ranges['eMBB']
            arrivals['eMBB'] = np.random.uniform(min_size,max_size)
        # mMTC : 均匀分布
        if self.arrival_distributions['mMTC'] == 'uniform':
            min_size, max_size = self.task_size_ranges['mMTC']
            arrivals['mMTC'] = np.random.uniform(min_size,max_size)

        return arrivals
    
    def get_channel_rate(self,slice_type,num_rb,t):
        """
        计算信道速率
        使用香农公式: r = B * log2(1 + y)
        """
        if not self.channel_gain[slice_type] or num_rb <= 0:
            return 0
        
        user_gain_db = random.choice(self.channel_gain[slice_type])

        # 添加变时性
        time_variatinon = np.random.normal(0,1.0)
        current_gain_db = user_gain_db * time_variatinon

        # 计算噪声功率
        bandwidth_total = num_rb * self.bandwidth_per_rb
        noise_power_dbm = (self.thermal_noise_dbm + 
                           10 * np.log10(bandwidth_total) + 
                           self.noise_figure_db
                           )

        # 转化为线性值
        signal_power_linear = 10 ** (current_gain_db / 10)
        noise_power_linear = 10 ** (noise_power_dbm / 10)

        # 信干燥比
        sinr = signal_power_linear / noise_power_linear

        # 香农容量公式
        rate = bandwidth_total * np.log2(1 + sinr)

        return rate

    def calculate_transmission(slef,slice_type,queue_length,arrival,num_rb,rate_per_rb):
        if num_rb <= 0 or rate_per_rb <= 0:
            return 0
        
        total_data = queue_length + arrival

        max_transmission = rate_per_rb * slef.step_duration

        # 实际传输量：取最小值
        actual_transmission = min(total_data,max_transmission)

        return actual_transmission
    
    def enhanced_quality_function(self,slice_type,queue_length,transmission,num_rb,t,future_considerration=True):
        """
        增强的质量函数
        """
        if num_rb <= 0:
            return -2000
        
        # 计算传输速率和时延
        rate = self.get_channel_rate(slice_type,num_rb,t)
        if rate > 0 and transmission > 0:
            transmission_delay = transmission / rate # 传输时延
        else:
            transmission_delay = float('inf')
        
        # 排队时延
        if rate > 0 :
            queue_delay = queue_length / rate
        else:
            queue_delay = float('inf')

        total_delay = queue_delay + transmission_delay

        if slice_type == 'URLLC':
            # URLLC服务质量函数
            sla_rate = self.sla_requirement['URLLC']['sla_rate']
            sla_delay = self.sla_requirement['URLLC']['sla_delay']
            penalty = self.sla_requirement['URLLC']['penalty_coeff']

            if total_delay == sla_delay:
                quality = self.utility_discount ** total_delay
            else:
                quality = -penalty * 100

            # 速率奖励
            if rate >= sla_rate:
                quality += 50

            return quality * 300

        elif slice_type == 'eMBB':
            sla_rate = self.sla_requirement['eMBB']['sla_rate']
            sla_delay = self.sla_requirement['eMBB']['sla_delay']
            penalty = self.sla_requirement['eMBB']['penalty_coeff']

            if total_delay <= sla_delay:
                if rate >= sla_rate:
                    quality = 1.0
                else:
                    quality = rate / sla_rate
            else:
                quality = -penalty * 100

            # 队列管理奖励
            if queue_length < 0.1e6:
                quality += 0.2

            return quality * 200
        
        elif slice_type == 'mMTC':
            sla_rate = self.sla_requirement['mMTC']['sla_rate']
            sla_delay = self.sla_requirement['mMTC']['sla_rate']
            penalty = self.sla_requirement['mMTC']['penalty_coeff']

            if total_delay <= sla_delay:
                if queue_length + transmission > 0:
                    success_rate = transmission / (queue_length + transmission)
                else:
                    success_rate = 1.0
                quality = success_rate
            else:
                quality = -penalty * 100

            # 可靠性奖励 
            if queue_length < 50000: # 防止队列过长
                quality += 0.3
            
            return quality * 100
        
        return 0

    def predict_embb_sla_requirement(self,t,current_accumulations):
        """预测eMBB的SLA需求 - 基于真实SLA参数"""
        steps_remaining = self.time_steps - t
        # 使用真实的eMBB SLA速率要求
        sla_rate = self.sla_requirement['eMBB']['sla_rate']
        total_required = sla_rate * self.time_steps * self.step_duration
        remaining_required = total_required - current_accumulations

        if steps_remaining <= 0:
            return 0
        
        return max(0,remaining_required / steps_remaining) # 确保非负
    
    def enhanced_single_step_solver(self,arrivals,t):
        """增强的单步求解器"""
        best_allocation = None
        best_quality = float('-inf')
        best_rates = None
        best_transmissions = None

        # 预测eMBB SLA需求
        embb_required_rate = self.predict_embb_sla_requirement(t,self.embb_throughput_accumulators)

        # 智能候选生成:基于当前状态和SLA需求
        candidates = self.generate_smart_candidates(embb_required_rate,t)

        for allocation in candidates:
            # 计算信道速率
            rates = {}
            for slice_type in ['URLLC','eMBB','mMTC']:
                rates[slice_type] = self.get_channel_rate(slice_type,allocation[slice_type],t)

            # 计算传输量
            transmissions = {}
            for slice_type in ['URLLC','eMBB','mMTC']:
                transmissions[slice_type] = self.calculate_transmission(
                    slice_type,
                    self.queue_lengths[slice_type],
                    arrivals[slice_type],
                    allocation[slice_type],
                    rates[slice_type]
                )

            # 计算增强质量函数
            total_quality = 0
            for slice_type in ['URLLC','eMBB','mMTC']:
                q_k = self.enhanced_quality_function(
                    slice_type,
                    self.queue_lengths[slice_type],
                    transmissions[slice_type],
                    allocation[slice_type],
                    t    # 添加当前时间步参数
                )
                total_quality += q_k

            # SLA硬约束检查
            sla_penalty = 0

            # URLLC时延约束
            future_urllc_queue = self.queue_lengths['URLLC'] + arrivals['URLLC'] - transmissions['URLLC']
            if future_urllc_queue > 0:
                sla_penalty += 1000

            # eMBB吞吐量约束与检查
            current_embb_throughput = allocation['eMBB'] * rates['eMBB']
            if current_embb_throughput < embb_required_rate * 0.8: # 语序20%的容忍度
                sla_penalty += 200
            
            # mMTC丢包约束
            future_mmtc_queue = self.queue_lengths['mMTC'] + arrivals['mMTC'] - transmissions['mMTC']
            max_queue_threshold = 100000    # 100kB作为丢包阈值
            if future_mmtc_queue > max_queue_threshold:
                sla_penalty += 500

            final_quality = total_quality - sla_penalty

            if final_quality > best_quality:
                best_quality = final_quality
                best_allocation = allocation
                best_rates = rates
                best_transmissions = transmissions

        return best_allocation,best_quality,best_rates,best_transmissions

    def generate_smart_candidates(self,embb_required_rate,t):
        """智能候选生成 - 基于SLA最小要求"""
        candidates = []

        # 基于SLA需求的eMBB最小RB估算
        if embb_required_rate > 0 and not np.isinf(embb_required_rate):
            # 估算单RB速率(基于平均信道条件
            avg_gain_db = np.mean(self.channel_gain['eMBB']) if self.channel_gain['eMBB'] else 50
            bandwidth_signal = self.bandwidth_per_rb
            noise_power_dbm = (self.thermal_noise_dbm + 10 * np.log10(bandwidth_signal) + self.noise_figure_db)

            siganl_power = 10 ** (avg_gain_db)
            noise_power = 10 ** (noise_power_dbm / 10)
            sinr = siganl_power / noise_power
            estimated_rate_per_db = bandwidth_signal * np.log2(1 + sinr)

            min_embb_rb = max(self.rb_limits['min']['eMBB'],
                              int(np.ceil(embb_required_rate / estimated_rate_per_db)))
            min_embb_rb = min(min_embb_rb,self.rb_limits['max']['eMBB'])
        else:
            min_embb_rb = self.rb_limits['min']['eMBB']
        
        # URLLC优先级: 根据真实最小要求
        min_urllc_rb = self.rb_limits['min']['URLLC']
        if self.queue_lengths['URLLC'] > 0:
            min_urllc_rb = max(min_urllc_rb,12)

        # mMTC需求,根据真实最小要求
        min_urllc_rb = self.rb_limits['min']['URLLC']
        if self.queue_lengths['URLLC'] > 0:
            min_urllc_rb = max(min_urllc_rb,12)

        #mMTC需求:根据真实最小要求
        min_mmtc_rb = self.rb_limits['min']['mMTC'] # 使用附录中的最小占用量
        if self.queue_lengths['mMTC'] > 50000:    # 如果队列较长
            min_mmtc_rb = max(min_mmtc_rb,4)

        # 生成候选
        for x_u in range(min_urllc_rb,min(self.rb_limits['max']['URLLC'],
                                          self.total_rb - min_embb_rb - min_embb_rb) + 1):
            for x_e in range(min_embb_rb,min(self.rb_limits['max']['eMBB'],
                                             self.total_rb - x_u - min_mmtc_rb) + 1):
                x_m = self.total_rb - x_u - x_e
                if (min_mmtc_rb <= x_m <= self.rb_limits['max']['mMTC']):
                    candidates.append({'URLLC': x_u, 'eMBB':x_e,'mMTC':x_m})
            
        return candidates
    
    def enhanced_dynamic_programming(self):
        """增强版动态规划求解"""
        print(f"\n 开始动态规划求解(目标:最大化10步总质量)")

        total_quality = 0
        allocations_history = []
        rates_history = []

        for t in range(1,self.time_steps + 1):
            # 生成业务到达
            arrivals = self.generate_arrivals(t)

            # 当前状态
            current_state = self.queue_lengths.copy()

            # eMBB SLA状态
            embb_required = self.predict_embb_sla_requirement(t, self.embb_throughput_accumulators)

            # 求解当前步最优分配
            best_allocation,step_quality,rates,transmissions = self.enhanced_single_step_solver(arrivals,t)

            # 求解eMBB吞吐量累积器
            embb_throughput = best_allocation['eMBB'] * rates['eMBB'] * self.step_duration
            self.embb_throughput_accumulators += embb_throughput

            # 更新队列状态
            self.update_queue_state(arrivals,transmissions)

            # 记录历史
            allocations_history.append(best_allocation)
            rates_history.append(rates)
            self.history['queue_lengths'].append(current_state.copy())
            self.history['arrivals'].append(arrivals.copy())
            self.history['allocations'].append(best_allocation.copy())
            self.history['transmissions'].append(transmissions.copy())
            self.history['qualities'].append(step_quality)
            self.history['channel_rates'].append(rates.copy())

            # 计算折扣质量
            discounted_quality = (self.gamma ** (t - 1)) * step_quality
            total_quality += discounted_quality

            # 简化输出
            print(f"步骤{t:2d}: URLLC={best_allocation['URLLC']:2d}RB, eMBB={best_allocation['eMBB']:2d}RB, mMTC={best_allocation['mMTC']:2d}RB, "
                f"质量:{step_quality:6.0f}, eMBB吞吐:{embb_throughput/1e6:5.1f}Mb")
            
            # SLA检查
            violations = self.check_enhanced_sla_constraints(t,allocations_history,rates_history)
            if any(violations.values()):
                warnings = []
                if violations['urllc_delay']: warnings.append("U")
                if violations['embb_throughput']: warnings.append("E")
                if violations['mmtc_drops']: warnings.append("M")
                if warnings:
                    print(f"             {''.join(warnings)}")

        print(f" 总质量: {total_quality:.2f}")
        return total_quality,allocations_history,rates_history
    
    def check_enhanced_sla_constraints(self,t,allocations_history,rates_history):
        """增强的SLA约束检查 - 基于真实SLA参数"""
        violations = {}

        # URLLC时延约束,根据附录要求,URLLC要求5ms时延
        # 简化为队必须及时清空
        violations['urllc_delay'] = self.queue_lengths['URLLC'] > 0

        # eMBB吞吐约束，检查是否满足50Mbps平均速率
        if t == self.time_steps: # 最后异步检查总体SLA
            required_total = self.sla_requirement['eMBB']['sla_rate'] * self.time_steps * self.step_duration
            violations['embb_throughput'] = self.embb_throughput_accumulators < required_total
        else:
            violations['embb_throughput'] = False
    
        # mMTC丢包约束,根据附录,检查是否演示要求丢包
        # 简化为队列长度超过阈值
        max_queue_threshold = 100000    # 100KB作为丢包阈值
        violations['mmtc_drops'] = self.queue_lengths['mMTC'] > max_queue_threshold

        return violations
    
    def update_queue_state(self,arrivals,transmissions):
        """更新队列状态"""
        for slice_type in ['URLLC','eMBB','mMTC']:
            new_queue = self.queue_lengths[slice_type] + arrivals[slice_type] - transmissions[slice_type]
            self.queue_lengths[slice_type] = max(0,new_queue)

    def analyze_enhanced_results(self,total_quality,allocation_history,rates_history):
        """分析结果并生成可视化"""
        print("\n 结果分析与可视化")
        print("="*30)

        # eMBB SLA检查
        required_total = self.sla_requirement['eMBB']['sla_rate'] * self.time_steps * self.step_duration
        print(f"总体性能: 质量={total_quality:.0f}")
        print(f"eMBB SLA: {self.embb_throughput_accumulators/required_total*100:.1f} % 完成")
        print(f"SLA违规: {sum(self.sla_violations.values())} 次")

        # 资源分配统计
        avg_allocation = {slice_type: np.mean([alloc[slice_type] for alloc in allocation_history])
                          for slice_type in ['URLLC','eMBB','mMTC']} 
        print(f" 平均分配: URLLC={avg_allocation['URLLC']:.1f},eMBB={avg_allocation['eMBB']:.1f},mMTC={avg_allocation['mMTC']:.1f}")

        # 生成可视化
        self.visualize_results(allocation_history,rates_history,total_quality)

        return {
            'total_quality': total_quality,
            'avg_allocation': avg_allocation,
            'sla_violations': self.sla_violations,
            'final_queues': self.queue_lengths,
            'embb_throughput_ratio':self.embb_throughput_accumulators / required_total
        }

    def visualize_results(self,allocations_history,rates_history,total_quality):
        """生成综合可视化仪表板"""
        fig,axes = plt.subplots(2,3,figsize=(15,20))
        fig.suptitle('问题二:动态资源调度结果分析',fontsize=26,fontweight='bold')

        steps = list(range(1,self.time_steps + 1))

        # 1.资源分配趋势
        ax1 = axes[0,0]
        urllc_alloc = [alloc['URLLC'] for alloc in allocations_history]
        embb_alloc = [alloc['eMBB'] for alloc in allocations_history]
        mmtc_alloc = [alloc['mMTC'] for alloc in allocations_history]

        ax1.plot(steps,urllc_alloc,'r-o',label='URLLC',linewidth=2,markersize=6)
        ax1.plot(steps,urllc_alloc,'b-s',label='eMBB',linewidth=2,markersize=6)
        ax1.plot(steps,urllc_alloc,'g-^',label='mMTC',linewidth=2,markersize=6)
        ax1.set_title('资源分配趋势')
        ax1.legend()
        ax1.grid(True,alpha=0.3)

        # 2.质量函数优化
        ax2 = axes[0,1]
        qualities = self.history['qualities']
        ax2.bar(steps,qualities,color='skyblue',alpha=0.7,edgecolor='navy')
        ax2.set_title('步骤质量函数')
        ax2.set_xlabel('之间步')
        ax2.set_ylabel('质量值')
        ax2.grid(True,alpha=0.3)

        # 3.队列长度演化
        ax3 = axes[0,2]
        urllc_queue = [q['URLLC']/1e6 for q in self.history['queue_lengths']]
        embb_queue = [q['eMBB']/1e6 for q in self.history['queue_lengths']]
        mmtc_queue = [q['mMTC']/1e6 for q in self.history['queue_lengths']]

        ax3.plot(steps,urllc_queue,'r-o',label='URLLC',linewidth=2)
        ax3.plot(steps,embb_queue,'b-s',label='eMBB',linewidth=2)
        ax3.plot(steps,mmtc_queue,'g-^',label='mMTC',linewidth=2)
        ax2.set_title('队列产犊烟花')
        ax2.set_xlabel('时间步')
        ax2.set_ylabel('队列残毒 (Mb)')
        ax3.legend()
        ax2.grid(True,alpha=0.3)

        # 4. 平均资源分配饼图
        ax4 = axes[1,0]
        avg_allocation = {
            'URLLC':np.mean(urllc_alloc),
            'eMBB':np.mean(embb_alloc),
            'mMTC':np.mean(mmtc_alloc)
        }
        colors = ['red','blue','green']
        wedges,texts,autotests = ax4.pie(avg_allocation.values(),
                                        labels = avg_allocation.keys(),
                                        colors=colors,
                                        autopct='%1.1f%%',
                                        startangle=90)
        ax4.set_title('平均资源分配占比')

        # 5. eMBB吞吐量积累
        ax5 = axes[1,1]
        embb_cumulative = []
        cumulative = 0
        for t in range(self.time_steps):
            rate = allocations_history[t]['eMBB'] * rates_history[t]['eMBB']
            throughput = rate * self.step_duration
            cumulative += throughput
            embb_cumulative.append(cumulative/1e6)

        required_total = self.sla_requirement['eMBB']['sla_rate'] * self.time_steps * self.step_duration / 1e6
        ax5.plot(steps,embb_cumulative,'b-o',linewidth=3,markersize=8,label='实际吞吐')
        ax5.axhline(y=required_total,color='red',linestyle='--',linewidth=2,label='SLA要求')
        ax5.fill_between(steps,embb_cumulative,alpha=0.3)
        ax5.set_title('eMBB累计吞吐量')
        ax5.set_xlabel('时间步')
        ax5.set_ylabel('累计吞吐 (Mb)')
        ax5.legend()
        ax5.grid(True,alpha=0.3)

        # 6. SLA违规统计
        ax6 = axes[1,2]
        sla_type = ['URLLC\n时延','eMBB\n吞吐','mMTC丢包']
        sla_counts = [self.sla_violations['urllc_delay'],
                      self.sla_violations['embb_throughput'],
                      self.sla_violations['mmtc_drops']
                      ]
        colors = ['red' if count > 0 else 'lightgreen' for count in sla_counts]

        bars = ax6.bar(sla_type,sla_counts,color=colors,alpha=0.7,edgecolor='black')
        ax6.set_title('SLA违规统计')
        ax6.set_ylabel('违规次数')
        ax6.grid(True,alpha=0.3,axis='y')

        # 在柱子上添加数值标签
        for bar ,count in zip(bars,sla_counts):
            if count > 0:
                ax6.test(bar.get_x() + bar.get_width()/2 ,bar.get_height() + 0.1,
                         str(count),ha='center',va='bottom',fontweight='bold')
                
        plt.tight_layout()
        plt.savefig('问题二_动态调度可视化.png',dpi=300,bbox_inches='tight')


def main():
    """主函数"""
    print("问题二:动态规划资源调度优化")
    print("="*40)

    data_path = "C:\\Users\\dong\\Desktop\\数学建模培训第三轮题目\\B题\\附件\\附件2\\channel_data.xlsx"

    # 
    scenario_params = {
        # 时间折扣因子
        'gamma': 0.95,          
        # 业务到达率配置
        'arrival_rates':{
            'URLLC':0.011e6,    # 平均0.11 Mbits/步(URLLC业务到达率)
            'eMBB' : 0.11e6,    # 平均0.11 Mbits/步(eMBB业务到达率)
            'mMTC': 0.013e6,    # 平均0.013 Mbits/步(mMTC业务到达率)
        }
    }

    # 创建基于真实参数的调度器
    scheduler = EnhancedDynamicScheduler(data_path,scenario_params)

    # 显示配置
    print(f"配置参数")
    print(f"URLLC:{scheduler.rb_limits['min']['URLLC']}RB,{scheduler.sla_requirement['URLLC']['sla_rate']/1e6:.0f}Mbps,{scheduler.sla_requirement}")
    print(f"eMBB:{scheduler.rb_limits['min']['eMBB']}RB,{scheduler.sla_requirement['URLLC']['sla_rate']/1e6:.0f}Mbps,{scheduler.sla_requirement}")
    print(f"mMTC:{scheduler.rb_limits['min']['mMTC']}RB,{scheduler.sla_requirement['mMTC']['sla_rate']/1e6:.0f}Mbps,{scheduler.sla_requirement}")

    # 设置随机种子
    np.random.seed(42)  # 设置Numpy随机种子
    random.seed(42)     # 设置Python标准库随机种子

    # 运行调度
    print(f"\n 开始优化求解")
    """
    输入: 系统状态(当前业务队列长度), 信道增益数据
    输出: 总质量值 资源分配历史 信道速率历史
    """
    total_quality,allocations_history,rates_history = scheduler.enhanced_dynamic_programming()

    # 分析结果并可视化
    results = scheduler.analyze_enhanced_results(total_quality,allocations_history,rates_history)

    # 保存结果
    with open("问题而动态调度结果.txt",'w',encoding="utf-8") as f:
        f.write("问题二: 动态规划调度优化结果")
        f.write("="*40 + "\n\n")

        f.write("性能指标\n")
        f.write(f"总质量:{total_quality:.2f}\n")
        f.write(f"eMBB SLA完成率:{results['embb_throughput_ratio']*100:.1f}%\n")
        f.write(f"SLA违规次数:{sum(results['sla_violations'].values())}\n\n")

        f.write("资源分配方案:\n")
        f.write("步骤 URLLC eMBB mMTC eMBB吞吐(Mbps)\n")
        f.write("-"*50 + "\n")
        for t in range(scheduler.time_steps):
            alloc = allocations_history[t]
            quality = scheduler.history['qualities'][t]
            rates = scheduler.history['channel_rates'][t]
            embb_rate = alloc['eMBB'] * rates['eMBB'] / 1e6
            f.write(f"{t+1:2d}     {alloc['URLLC']:2d}     {alloc['mMTC']:2d}    {quality:6.0f}    {embb_rate:8.1f}\n")
        
        f.write(f"\n   平均分配:    \n")
        for slice_type, avg_rb in results['avg_allocation'].items():
            f.write(f"    {slice_type}: {avg_rb:.1f}    RB ({avg_rb/scheduler.total_rb*100:.1f}%)\n")

    
    print("结果已保存到: 问题而动态调度结果.txt")
    print("可视化图表: 问题二_动态调度结果可视化.png")

    if sum(results['sla_violations'].values()) == 0:
        print(f"成功满足所有SLA约束:eMBB完成率: {results['embb_throughput_ratio']*100:.1f}%")
    else:
        print(f"存在 {sum(results['sla_violations'].values())} 次SLA违规")

if __name__ == "__main__":
    main()




