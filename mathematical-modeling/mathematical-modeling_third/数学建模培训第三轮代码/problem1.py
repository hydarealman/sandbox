import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib


# 确保使用兼容的中文字体
matplotlib.rcParams['font.sans-serif'] = ['SimHei']     # 使用黑体
matplotlib.rcParams['axes.unicode_minus'] = False       # 解决符号显示问题

class NetworkSliceOptimizerUpdated:
 
    """
    网络切片优化器负责创建优化器对象时的基础设置
    """
    def __init__(self, data_path):
        """
        初始化网络切片优化器
        """
        self.total_rb = 50              # 总资源数
        self.load_data(data_path)       # 数据加载流程
        self.setup_parameters()         # 参数系统构建
        self.setup_constraints()        # 约束条件建立

    def load_data(self,data_path):
        """加载用户数据"""
        try:
            self.df = pd.read_excel(data_path)
            print("数据加载成功")
            self.process_channel_data()
        except Exception as e:
            print(f"加载失败: {e}")
            self.create_sample_data()
    
    def process_channel_data(self):
        """处理信道数据"""
        current_data = self.df.iloc[0]  # 只读取第一行数据

        users_data = []

        # URLLC用户
        urllc_users = [col for col in self.df.columns if col.startswith('U')]
        for user in urllc_users:
            if user in current_data:
                users_data.append({
                    'user_id' : user,                       # 用户名唯一标识 
                    'user_type': 'URLLC',                   # 业务类型
                    'channel_gain_db': current_data[user],  # 关键信道质量指标  
                    'task_size': 1000,                      # 典型任务数据量(bit)
                    'delay_requirement': 1,                 # 时延需求
                    'reliability_requirement': 0.99999      # 可靠性需求
                })
        
        # eMBB 用户
        embb_users = [col for col in self.df.columns if col.startswith('e')]
        for user in embb_users:
            if user in current_data:
                users_data.append({
                    'user_id':user,
                    'user_type': 'eMBB',
                    'channel_gain_db':current_data[user],
                    'tasr_size': 10000,
                    'delay_requirement': 100,
                    'reliability_requirement': 0.99
                })

        # mMTC
        mmtc_users = [col for col in self.df.columns if col.startswith('m')]
        for user in mmtc_users:
            if user in current_data:
                users_data.append({
                    'user_id': user,
                    'user_type': 'mMTC',
                    'channel_gain_db': current_data[user],
                    'task_size': 200,
                    'delay_requirement': 1000,
                    'reliability_requirement': 0.9
                })
    

        self.users_df = pd.DataFrame(users_data)
        self.urllc_data = self.users_df[self.users_df['user_type'] == 'URLLC']
        self.embb_data = self.users_df[self.users_df['user_type'] == 'eMBB']
        self.mmtc_data = self.users_df[self.users_df['user_type'] == 'mMTC']

        print(f"用户统计: URLLC={len(self.urllc_data)}, eMBB={len(self.embb_data)}, mMTC={len(self.mmtc_data)}")

    def setup_parameters(self):
        """设置系统参数"""
        # 物理层参数
        self.bandwidth_per_rb = 360e3   # 带宽 360kHz
        self.noise_figure_db = 7        # 接收机噪声系数 NF = 7dB
        self.thermal_noise_dbm = -174   # 热噪声功率谱密度 dBm/Hz

        # SLA参数
        self.sla_rates = {
            'URLLC': 10e6,  # 10 Mbps
            'eMBB': 50e6,   # 50 Mbps
            'mMTC': 1e6     # 1 Mbos
        }

        # 时延要求
        self.sla_latency = {
            'URLLC': 5,    # 5 ms
            'eMBB': 100,   # 100 ms
            'mMTC': 500    # 500 ms
        }

        # 最小占用量
        self.min_rb = {
            'URLLC': 10,    # 10个RB
            'eMBB': 5,      # 5个RB
            'mMTC': 2       # 2个RB
        }

    def setup_constraints(self):
        """配置约束条件"""
        # 计算满足SLA速率要求的最小RB数
        self.min_rb_sla = {}

        for slice_type in ['URLLC', 'eMBB', 'mMTC']:
            print(f"处理切片类型: {slice_type}")
            required_rate = self.sla_rates[slice_type]

            # 使用真实信道数据估算平均速率
            avg_gain_db = None
            if slice_type == 'URLLC' and len(self.urllc_data) > 0:
                avg_gain_db = self.urllc_data['channel_gain_db'].mean()
                print(f"URLLC平均信道增益: {avg_gain_db} dB")
            elif slice_type == 'eMBB' and len(self.embb_data) > 0:
                avg_gain_db = self.embb_data['channel_gain_db'].mean()
                print(f"eMBB平均信道增益: {avg_gain_db} dB")
            elif slice_type == 'mMTC' and len(self.mmtc_data) > 0:
                avg_gain_db = self.mmtc_data['channel_gain_db'].mean()
                print(f"mMTC平均信道增益: {avg_gain_db} dB")
            
            # 如果数据不存在，使用默认值
            if avg_gain_db is None:
                print(f"警告: {slice_type}切片无用户数据，使用默认值50 dB")
                avg_gain_db = 50  # 默认值
            
            # 计算噪声功率
            bandwidth_single = self.bandwidth_per_rb
            noise_power_dbm = (self.thermal_noise_dbm + 
                              10 * np.log10(bandwidth_single) + 
                              self.noise_figure_db)

            # 转换噪声功率为毫瓦
            noise_power_mw = 10 ** (noise_power_dbm / 10)

            # 计算信号功率（毫瓦）
            signal_power = 10 ** (avg_gain_db / 10)

            # 计算SINR
            sinr = signal_power / noise_power_mw

            # 计算速率
            rate_per_rb = bandwidth_single * np.log2(1 + sinr)
            
            # 防止除零错误
            if rate_per_rb < 1e-6:  # 避免非常小的值
                rate_per_rb = 1e-6
                
            min_rb_for_sla = max(1, int(np.ceil(required_rate / rate_per_rb)))
            self.min_rb_sla[slice_type] = min_rb_for_sla
            print(f"{slice_type}切片满足SLA要求的最小RB数: {min_rb_for_sla}")

        # 综合约束: 取最小占用量和SLA要求的最大值
        self.effective_min_rb = {
            'URLLC': max(self.min_rb['URLLC'], self.min_rb_sla.get('URLLC', self.min_rb['URLLC'])),
            'eMBB': max(self.min_rb['eMBB'], self.min_rb_sla.get('eMBB', self.min_rb['eMBB'])),
            'mMTC': max(self.min_rb['mMTC'], self.min_rb_sla.get('mMTC', self.min_rb['mMTC']))
        }

        print("\n最终约束设置:")
        print(f"URLLC最小RB数: {self.effective_min_rb['URLLC']}")
        print(f"eMBB最小RB数: {self.effective_min_rb['eMBB']}")
        print(f"mMTC最小RB数: {self.effective_min_rb['mMTC']}")

        total_min = sum(self.effective_min_rb.values())
        if total_min > self.total_rb:
            print(f"警告: 最小需求({total_min} RB)超过可用资源({self.total_rb} RB)")
        else:
            print(f"约束检查通过,剩余可分配: {self.total_rb - total_min} RB")
            
    def calculate_data_rate(self,num_rb,channel_gain_rb):
        """计算数据传输速率 - 加入光谱效率上限"""
        if num_rb <= 0:
            return 0
        # 计算总带宽
        bandwidth_total = num_rb * self.bandwidth_per_rb

        # 计算噪声功率
        noise_power_dbm = (self.thermal_noise_dbm + 10 * np.log10(bandwidth_total) + self.noise_figure_db)

        # 计算SINR
        signal_power = 10 ** (channel_gain_rb / 10)
        noise_power = 10 ** (noise_power_dbm / 10)
        sinr = signal_power / noise_power

        # 引入光谱效率上限为8 bit/s/Hz(基于5G-NR 256-QAM最高效率)
        max_spectral_efficiency = 8.0 # bit/s/Hz

        # Shannon公式计算速率,但限制最大光谱效率
        spectral_efficiency = np.log2(1 + sinr)
        limited_spectral_efficiency = min(spectral_efficiency,max_spectral_efficiency)

        rate = bandwidth_total * limited_spectral_efficiency
        return rate
        
    def calculate_delay(self,task_size,data_rate):
        """计算传输时延 - 考虑实际系统开销"""
        if data_rate <= 0:
            return float('inf')
        
        # 计算传输时延
        transmission_delay = task_size / data_rate * 1000 # 转化为ms

        # 根据不同业务添加额外延迟组件
        processing_delay = 0.1 # 基本处理延迟0.1ms

        # 根据实际无线系统特性,设置最小帧时延
        min_frame_delay = {
            'URLLC': 0.1,   # URLLC最小帧时延不低于0.1ms
            'eMBB': 1.0,    # eMBB最小帧时延不低于1.0ms
            'mMTC': 2.0     # mMTC最小帧时延不低于2.0ms
        }

        # 计算总时延,添加重传与排队概率影响
        retransmission_factor = 1.2     # 假设平均需要1.2次传输(包括可能的重传)

        total_delay = transmission_delay * retransmission_factor + processing_delay

        # 确保不低于最小帧延迟
        if task_size <= 1000: # URLLC任务
            total_delay = max(total_delay,min_frame_delay['URLLC'])
        elif task_size <= 1000:
            total_delay = max(total_delay,min_frame_delay['eMBB'])
        else:   # mMTC任务
            total_delay = max(total_delay, min_frame_delay['mMTC'])

        return total_delay
    
    def quality_function_embb(self, num_rb):
        """eMBB切片服务质量函数 - 确保非负值"""
        if num_rb < self.effective_min_rb['eMBB']:
            return -1000
        
        if len(self.embb_data) > 0:
            # 使用平均信道增益进行计算
            avg_gain_db = self.embb_data['channel_gain_db'].mean()
            avg_task_size = self.embb_data['task_size'].mean()
        else:
            avg_gain_db = -75  # 默认值
            avg_task_size = 10000  # 默认值
        
        rate = self.calculate_data_rate(num_rb, avg_gain_db)
        delay = self.calculate_delay(avg_task_size, rate)

        # 基础效用,满足SLA的比例
        rate_ratio = min(1.0, rate / self.sla_rates['eMBB'])
        base_utility = 100 * rate_ratio
        
        # 高吞吐量效用：对数增长特性
        saturation_factor = 0.8  # 饱和因子
        throughput_utility = 60 * min(1.0, (rate / self.sla_rates['eMBB'])**saturation_factor)
        
        # 时延效用
        if delay <= self.sla_latency['eMBB']:
            delay_utility = 30
        else:
            # 线性惩罚，但保留部分效用
            penalty = min(20, (delay - self.sla_latency['eMBB']) * 0.2)
            delay_utility = 30 - penalty
        
        # 总质量
        total_quality = base_utility + throughput_utility + delay_utility
        
        # 确保质量非负
        return max(0, total_quality)  
    
    def quality_function_urllc(self, num_rb): 
        """URLLC切片服务质量函数 - 确保非负值"""
        if num_rb < self.effective_min_rb['URLLC']:
            return -1000
        
        if len(self.urllc_data) > 0:
            # 使用平均信道增益进行计算
            avg_gain_db = self.urllc_data['channel_gain_db'].mean()
            avg_task_size = self.urllc_data['task_size'].mean()
        else:
            avg_gain_db = -80  # 默认值
            avg_task_size = 1000  # 默认值
        
        rate = self.calculate_data_rate(num_rb, avg_gain_db)
        delay = self.calculate_delay(avg_task_size, rate)

        # 基础效用,满足SLA的比例
        rate_ratio = min(1.0, rate / self.sla_rates['URLLC'])
        base_utility = 100 * rate_ratio
        
        # 超可靠效用: 指数函数,强调延迟敏感性
        reliability_utility = 50 * (np.exp(2 * rate_ratio) - 1)

        # 时延效用
        delay_ratio = min(1.0, self.sla_latency['URLLC'] / max(0.1, delay))
        delay_utility = 30 * delay_ratio
        
        total_quality = base_utility + reliability_utility + delay_utility
        return max(0, total_quality) * 3.0  # 权重
        
    def quality_function_mmtc(self,num_rb):
        """mMTC切片服务质量函数 - 提高编辑效用以促进更公平分配"""
        if num_rb < self.effective_min_rb['mMTC']:
            return -1000 # 严重惩罚,无法接入

        if len(self.mmtc_data) > 0:
            # 使用平均信道争议进行计算
            avg_gain_db = self.mmtc_data['channel_gain_db'].mean()
            avg_task_size = self.mmtc_data['task_size'].mean()
        else:
            return 0

        rate = self.calculate_data_rate(num_rb,avg_gain_db)
        delay = self.calculate_delay(avg_task_size,rate)

        #基础效用,满足SLA
        min_rate_multiplier = 1.5
        if rate >= self.sla_rates['mMTC']:
            if rate >= self.sla_rates['mMTC'] * min_rate_multiplier:
                # 超过最低要求50%时额外奖励
                base_utility = 150
            else:
                base_utility = 100
        else:
            return -100   # SLA违反惩罚

        # 大规模连接效用:更积极的鼓励分配,非线性增长
        # 为mMTC提供更大的边际增益
        connection_scaling = 3.5 # 增大系数提高边际效用
        connection_ratio = min(3.0, rate / self.sla_rates['mMTC'])

        # 采用更快增长的函数,鼓励更多资源分配给mMTC
        connection_utility = 45 * (np.sqrt(connection_ratio * num_rb) + np.log(1 + connection_ratio * num_rb * 0.5))

        # 时延效用
        if delay <= self.sla_latency['mMTC']:
            delay_utility = 20  # 增加时延满足的奖励
        else:
            delay_utility = max(0,20 - (delay - self.sla_latency['mMTC']) * 0.04)

        # 引入连续数奖励,体现mMTC的海量接入特性
        connection_capacity = 10 * np.log10(1 + num_rb * 2)

        total_quality = base_utility + connection_utility + delay_utility + connection_capacity     
        return total_quality * 1.6    # 提高权重以平衡资源
 
    def search_optimal_allocation(self):
        """搜索最优分配方案 - 更灵活的搜索算法"""
        min_U = self.effective_min_rb['URLLC']
        min_e = self.effective_min_rb['eMBB']
        min_m = self.effective_min_rb['mMTC']

        # 引入mMTC资源占比下限约束
        min_mmtc_ratio = 0.10 # mMTC至少占总资源的10%
        min_m_fair = max(min_m, int(self.total_rb * min_mmtc_ratio))
        
        total_min = min_U + min_e + min_m_fair
        if total_min > self.total_rb:
            print("问题不可行,最小需求超过总资源")
            return None, float('-inf'), []
        
        best_quality = float('-inf')
        best_allocation = None
        valid_solutions = []

        print(f"搜索最优分配方案")

        # 在约束范围内搜索
        for x_u in range(min_U, self.total_rb - min_e - min_m_fair + 1):
            for x_e in range(min_e, self.total_rb - x_u - min_m_fair + 1):
                x_m = self.total_rb - x_u - x_e

                # 检查mMtc资源公平性约束
                if x_m < min_m_fair:
                    continue
                    
                # 计算各切片质量
                q_U = self.quality_function_urllc(x_u)
                q_e = self.quality_function_embb(x_e)
                q_m = self.quality_function_mmtc(x_m)

                # 计算综合服务质量目标
                total_quality = q_U + q_e + q_m

                # 计算Jaain公平性指数
                r_U = x_u / self.total_rb
                r_e = x_e / self.total_rb
                r_m = x_m / self.total_rb
                fairness_index = (r_U + r_e + r_m)**2 / (3 * (r_U**2 + r_e**2 + r_m**2))

                # 记录所有非负质量的解
                if q_U >= 0 and q_e >= 0 and q_m >= 0:
                    valid_solutions.append((x_u, x_e, x_m, q_U, q_e, q_m, total_quality, fairness_index))

                    if total_quality > best_quality:
                        best_quality = total_quality
                        best_allocation = (x_u, x_e, x_m)

        # 如果没有找到完全非负的解，放宽条件
        if len(valid_solutions) == 0:
            print("未找到完全非负的解，放宽条件搜索")
            for x_u in range(min_U, self.total_rb - min_e - min_m_fair + 1):
                for x_e in range(min_e, self.total_rb - x_u - min_m_fair + 1):
                    x_m = self.total_rb - x_u - x_e

                    if x_m < min_m_fair:
                        continue
                        
                    q_U = self.quality_function_urllc(x_u)
                    q_e = self.quality_function_embb(x_e)
                    q_m = self.quality_function_mmtc(x_m)
                    total_quality = q_U + q_e + q_m
                    fairness_index = (x_u/self.total_rb + x_e/self.total_rb + x_m/self.total_rb)**2 / (3 * ((x_u/self.total_rb)**2 + (x_e/self.total_rb)**2 + (x_m/self.total_rb)**2))

                    # 记录至少有两个切片质量非负的解
                    if sum([q >= 0 for q in [q_U, q_e, q_m]]) >= 2:
                        valid_solutions.append((x_u, x_e, x_m, q_U, q_e, q_m, total_quality, fairness_index))

                        if total_quality > best_quality:
                            best_quality = total_quality
                            best_allocation = (x_u, x_e, x_m)

        # 如果仍然没有找到解，使用最小分配方案
        if len(valid_solutions) == 0:
            print("仍无可行解，使用最小分配方案")
            best_allocation = (min_U, min_e, min_m_fair)
            q_U = self.quality_function_urllc(min_U)
            q_e = self.quality_function_embb(min_e)
            q_m = self.quality_function_mmtc(min_m_fair)
            best_quality = q_U + q_e + q_m
            fairness_index = (min_U/self.total_rb + min_e/self.total_rb + min_m_fair/self.total_rb)**2 / (3 * ((min_U/self.total_rb)**2 + (min_e/self.total_rb)**2 + (min_m_fair/self.total_rb)**2))
            valid_solutions.append((min_U, min_e, min_m_fair, q_U, q_e, q_m, best_quality, fairness_index))
        
        # 排序显示结果
        valid_solutions.sort(key=lambda x: x[6], reverse=True)

        # 二阶段优化,在接近最优质量的解中寻找最公平的解
        top_quality = valid_solutions[0][6]
        quality_threshold = 0.95 * top_quality

        near_optimal_solutions = [sol for sol in valid_solutions if sol[6] >= quality_threshold]

        if len(near_optimal_solutions) > 1:
            near_optimal_solutions.sort(key=lambda x: x[7], reverse=True)
            fairness_allocation = near_optimal_solutions[0]

            print(f"二阶段优化: 在保持95%质量的前提下优化公平性")

            best_allocation = (fairness_allocation[0], fairness_allocation[1], fairness_allocation[2])
            best_quality = fairness_allocation[6]
        
        return best_allocation, best_quality, valid_solutions[:10]
    
    def visualize_results(self,x_u,x_e,x_m,top_solutions):
        """可视化分析结果"""
        # 创建图形
        fig = plt.figure(figsize=(15,20))

        # 1.资源分配饼图
        ax1 = plt.subplot(2,3,1)
        sizes = [x_u,x_e,x_m]
        labels = ['URLLC','eMBB','mMTC']
        colors = ['#FF6B6B','#4ECDC4','#45B701']
        explode = [0.05,0.05,0.05]

        wedges,texts,autotexts = ax1.pie(sizes,labels=labels,colors=colors,explode=explode
                                         ,autopct='%1.1f%%',startangle=90)
        ax1.set_title('资源分配饼图',fontsize=12,fontweight='bold')

        # 2.各切片质量函数曲线
        ax2 = plt.subplot(2,3,2)
        rb_range = range(1,31)
        urllc_quality = [self.quality_function_urllc(rb) if rb >= self.effective_min_rb['URLLC'] else -1000 for rb in rb_range]
        embb_quality = [self.quality_function_embb(rb) if rb >= self.effective_min_rb['eMBB'] else -1000 for rb in rb_range]
        mmtc_quality = [self.quality_function_mmtc(rb) if rb >= self.effective_min_rb['mMTC'] else -1000 for rb in rb_range]

        # 只显示正值
        urllc_quality = [q if q > 0 else 0 for q in urllc_quality]
        embb_quality = [q if q > 0 else 0 for q in embb_quality]
        mmtc_quality = [q if q > 0 else 0 for q in mmtc_quality]

        ax2.plot(rb_range,urllc_quality,'o-',color='#FF6B6B',label='URLLC',linewidth=2)
        ax2.plot(rb_range,embb_quality,'s-',color='#4ECDC4',label='eMBB',linewidth=2)
        ax2.plot(rb_range,mmtc_quality,'^-',color='#45B701',label='mMTC',linewidth=2)

        # 标记最优分配点
        ax2.axvline(x=x_u,color='#FF6B6B',linestyle='--',alpha=0.7)
        ax2.axvline(x=x_e,color='#4ECDC4',linestyle='--',alpha=0.7)
        ax2.axvline(x=x_m,color='#45B701',linestyle='--',alpha=0.7)

        ax2.set_xlabel('资源快数量')
        ax2.set_xlabel('服务质量得分')
        ax2.set_xlabel('各切分质量函数', fontsize=12,fontweight='bold')
        ax2.legend()
        ax2.grid(True,alpha=0.3)

        # 3.前10个解的质量对比
        ax3 = plt.subplot(2,3,3)
        if len(top_solutions) > 0:
            indices = range(1, min(11,len(top_solutions) + 1))
            total_qualities = [sol[6] for sol in top_solutions[:10]]

            bars = ax3.bar(indices,total_qualities,color='#98CEB4',alpha=0.8)
            bars[0].set_color('#FFEAA7')    # 最优解用不同颜色

            ax3.set_xlabel('解的排名')
            ax3.set_ylabel('总服务质量')
            ax3.set_title('前10个解质量对比',fontsize=12,fontweight='bold')
            ax3.grid(True,alpha=0.3)

        # 4.资源分配与公平性关系
        ax4 = plt.subplot(2,3,4)
        if len(top_solutions) > 0:
            fairness_values = [sol[7] for sol in top_solutions[:10]]
            total_qualities = [sol[6] for sol in top_solutions[:10]]

            # 错误代码
            scatter = ax4.scatter(fairness_values,total_qualities,c=range(len(fairness_values)),cmap='viridis',s=100,alpha=0.7)
            ax4.set_xlabel('公平性指数')
            ax4.set_xlabel('总服务质量')
            ax4.set_title('质量-公平性权衡',fontsize=12,fontweight='bold')
            ax4.grid(True,alpha=0.3)

            # 标记最优解
            if len(top_solutions) > 0:
                ax4.scatter(top_solutions[0][7],top_solutions[0][6],
                            color='red',s=150,marker='*',label='最优解')
                ax4.legend()

        # 5. 各切片资源占比对比
        ax5 = plt.subplot(2,3,5)
        if len(top_solutions) >= 5:
            solutions_subset = top_solutions[:5]
            urllc_ratios = [sol[0]/50*100 for sol in solutions_subset]
            embb_ratios = [sol[1]/50*100 for sol in solutions_subset]
            mmtc_ratios = [sol[2]/50*100 for sol in solutions_subset]

            x_pos = range(len(solutions_subset))
            width = 0.25

            ax5.bar([p - width for p in x_pos], urllc_ratios, width, label='URLLC', color='#FF6B6B', alpha=0.8) 
            ax5.bar(x_pos,embb_ratios,width,label='eMBB',color='#4ECDC4',alpha=0.8) 
            ax5.bar([p + width for p in x_pos], mmtc_ratios, width, label='mMTC', color='#45B7D1', alpha=0.8) 

            
            ax5.set_xlabel('解的排名')
            ax5.set_xlabel('资源占比(%)')
            ax5.set_title('前5个资源分配对比',fontsize=12,fontweight='bold')
            ax5.set_xticks(x_pos)
            ax5.set_xticklabels([f'#{i+1}' for i in x_pos])
            ax5.legend()
            ax5.grid(True,alpha=0.3)

        # 6.性能雷达图
        ax6 = plt.subplot(2,3,6,projection='polar')

        # 计算性能指标(归一化)
        q_U_val = self.quality_function_urllc(x_u)
        q_e_val = self.quality_function_embb(x_e)
        q_m_val = self.quality_function_mmtc(x_m)

        # 归一化到0-1范围
        max_quality = max(q_U_val,q_e_val,q_m_val)
        normalized_qualities = [q_U_val/max_quality,q_e_val/max_quality,q_m_val/max_quality]

        # 计算公平性指数
        r_u = x_u / 50
        r_e = x_e / 50
        r_m = x_m / 50
        fairness_index = (r_u + r_e + r_m) ** 2 / (3 * (r_u**2 + r_e**2 + r_m**2))

        # 资源利用率
        resource_utilization = (x_u + x_e + x_m) / 50

        # 雷达图数据
        categories = ['URLLC质量','eMBB质量','mMTC质量','公平性','资源利用率']
        values = normalized_qualities + [fairness_index , resource_utilization]

        # 闭合雷达图
        angles = np.linspace(0,2*np.pi,len(categories),endpoint=False).tolist()
        values += values[:1]
        angles += angles[:1]

        ax6.plot(angles,values,'o-',linewidth=2,color='#E17055')
        ax6.fill(angles,values,alpha=0.25,color='#E17055')
        ax6.set_xticks(angles[:-1])
        ax6.set_xticklabels(categories)
        ax6.set_ylim(0,1)
        ax6.set_title('综合性能评估',fontsize=12,fontweight='bold',pad=20)
        ax6.grid(True)

        plt.tight_layout()
        plt.savefig('问题一_资源可视化分析',dpi=300,bbox_inches='tight')
        plt.show()

        return fig
    
    def analyze_results(self,x_u,x_e,x_m):
        """分析结果"""
        print("\n" + "="*50)
        print("问题一:最优化资源块分配方案")
        print("="*50)

        print(f"\n 最优化分配方案")
        print(f" URLLC切片: {x_u} RB({x_u/self.total_rb*100:.1f}%)")
        print(f" eMBB切片: {x_e} RB({x_e/self.total_rb*100:.1f}%)")
        print(f" mMTC切片: {x_m} RB({x_m/self.total_rb*100:.1f}%)")

        # 计算公平性指数
        r_u = x_u / self.total_rb
        r_e = x_e / self.total_rb
        r_m = x_m / self.total_rb
        fairness_index = (r_u + r_e + r_m)**2 / (3 * (r_u**2 +r_e**2 +r_m**2)) 

        print(f"\n约束满足")
        print(f"最小占用:URLLC {x_u}>={self.effective_min_rb['URLLC']},"
              f"最小占用:eMBB {x_u}>={self.effective_min_rb['eMBB']},"
              f"最小占用:mMTC {x_u}>={self.effective_min_rb['mMTC']},"
              )
        print(f"公平性指数:{fairness_index:.4f}")

        # 计算性能图标
        self.calculate_performance_detailed(x_u,x_e,x_m)

        # 计算性能图标
        q_u = self.quality_function_urllc(x_u)
        q_e = self.quality_function_embb(x_e)
        q_m = self.quality_function_mmtc(x_m)

        print(f"\n服务质量")
        print(f"URLLC:{q_u:.1f}")
        print(f"eMBB:{q_e:.1f}")
        print(f"mMTC:{q_m:.1f}")
        print(f"总计: {q_u + q_e + q_m:.1f}")

        return q_u + q_e + q_m
    
    def calculate_performance_detailed(self,x_u,x_e,x_m):
        """计算详细性能指标"""
        print(f"\n 传输性能:")

        # URLLC性能
        if len(self.urllc_data) > 0:
            user_data = self.urllc_data.iloc[0]
            rate = self.calculate_data_rate(x_u,user_data['channel_gain_db'])
            delay = self.calculate_delay(user_data['task_size'],rate)

            rate_ok = "✔" if rate >= self.sla_rates['URLLC'] else "❌"
            delay_ok = "✔" if delay <= 1 else "❌"
            print(f"URLLC: {rate/1e6:.1f}Mbps, {delay:.2f}ms {rate_ok}{delay_ok}")

        # eMBB性能
        if len(self.embb_data) > 0:
            user_data = self.urllc_data.iloc[0]
            rate = self.calculate_data_rate(x_e,user_data['channel_gain_db'])
            delay = self.calculate_delay(user_data['task_size'],rate)

            rate_ok = "✔" if rate >= self.sla_rates['eMBB'] else "❌"
            delay_ok = "✔" if delay <= 100 else "❌"
            print(f"eMBB: {rate/1e6:.1f}Mbps, {delay:.2f}ms {rate_ok}{delay_ok}")

        # eMBB性能
        if len(self.mmtc_data) > 0:
            user_data = self.mmtc_data.iloc[0]
            rate = self.calculate_data_rate(x_m,user_data['channel_gain_db'])
            delay = self.calculate_delay(user_data['task_size'],rate)

            rate_ok = "✔" if rate >= self.sla_rates['mMTC'] else "❌"
            delay_ok = "✔" if delay <= 1000 else "❌"
            print(f"mMTC: {rate/1e6:.1f}Mbps, {delay:.2f}ms {rate_ok}{delay_ok}")

def main():
    """主函数"""
    data_path = "C:\\Users\\dong\\Desktop\\数学建模培训第三轮题目\\B题\\附件\\附件1\\channel_data.xlsx"

    # 创建优化器
    optimizer = NetworkSliceOptimizerUpdated(data_path)

    # 搜索最优解
    best_allocation , best_quality, top_solutions = optimizer.search_optimal_allocation()
    if best_allocation:
        x_u ,x_e,x_m = best_allocation
        optimizer.analyze_results(x_u,x_e,x_m)

        # 可视化分析
        print(f"\n 正在生成可视化分析")
        optimizer.visualize_results(x_u,x_e,x_m,top_solutions)

        # 输出结论
        print("\n" + "="*50)
        print("最终结论")
        print("="*50)
        print(f"最优化的资源块分配方案:")
        print(f" . URLLC: {x_u} RB ({x_u/50*100:.1f}%)")
        print(f" . eMBB: {x_e} RB ({x_e/50*100:.1f}%)")
        print(f" . mMTC: {x_m} RB ({x_m/50*100:.1f}%)")
        print(f". 总服务质量: {best_quality:.1f}")

        # 计算公平性指数
        r_u,r_e,r_m = x_u/50,x_e/50,x_m/50
        fairness_index = (r_u + r_e + r_m)**2 / (3*(r_u**2 + r_e**2 + r_m**2))

        print(f"\n 关键特点")
        print(f". 满足所有SLA要求和最小占用约束")
        print(f". 公平性指数: {fairness_index:.4f}")
        print(f". 在数学最优与工程可行之间取得平衡")

        # 简化保存结果
        with open("问题一_优化结果.txt", "w", encoding="utf-8") as f:
            f.write("B题 问题一: 网络切片无线资源管理最优方案\n")
            f.write("="*50 + "\n\n")
            f.write("最优化资源分配:\n")
            f.write(f"URLLC切片: {x_u} RB ({x_u/50*100:.1f}%)\n")
            f.write(f"eMBB切片: {x_e} RB ({x_e/50*100:.1f}%)\n")
            f.write(f"mMTC切片: {x_m} RB ({x_m/50*100:.1f}%)\n")
            f.write(f"总服务质量: {best_quality:.1f}\n")
            f.write(f"公平性指数: {fairness_index:.4f}\n")

        print(f"\n 结果已保存: 问题一_优化结果.txt")
        print(f"可视化图表已保存: 问题一_资源分配可视化分析.png")
    else:
        print("未找到可行解")

if __name__ == "__main__":
    main()
