import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from statsmodels.tsa.statespace.sarimax import SARIMAX
from sklearn.preprocessing import MinMaxScaler
import torch
import torch.nn as nn

# 设置中文字体
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False
# 加载数据函数,这里假设数据是CSV 格式且第一列是日期,后序列是疾病相关特征
def load_data(file_path): 
    try:
        data = pd.read_csv(file_path, parse_dates=[0], index_col=[0], date_format='%Y-%m-%d')
    except:
        data = pd.read_csv(file_path, parse_dates=[0], index_col=[0])
    
    data.index = pd.to_datetime(data.index)
    
    # 处理重复索引 - 解决方案
    if data.index.duplicated().any():
        # 仅保留第一次出现的行（或根据业务需求选择其他方式）
        data = data[~data.index.duplicated(keep='first')]
        # 或者使用众数（对分类数据）: 
        # data = data.groupby(data.index).agg(lambda x: x.mode()[0])
    
    if data.index.freq is None:
        data = data.asfreq('D').ffill()
    
    return data

# SARIMA 模型拟合与预测
def sarima_forecast(data, order, seasonal_order): 
    model = SARIMAX(data, order=order, seasonal_order=seasonal_order)
    model_fit = model.fit(disp=False)
    
    # 确保至少有 1 步预测，最多不超过数据长度的 10%
    steps = max(1, min(len(data), len(data) // 10 or 30))
    
    forecast = model_fit.get_forecast(steps=steps)
    return forecast.predicted_mean

# 定义 BP 神经网络模型
class BPNet(nn.Module):
    def __init__(self,input_dim):
        super(BPNet,self).__init__()
        self.fc1 = nn.Linear(input_dim, 10)
        self.relu = nn.ReLU()
        self.fc2 = nn.Linear(10, 1)
        self.sigmoid = nn.Sigmoid()

    def forward(self, x):
        out = self.fc1(x)
        out = self.relu(out)
        out = self.fc2(out)
        out = self.sigmoid(out)
        return out
    
# 数据归一化
def normalize_data(data, look_back=1):
    scaler = MinMaxScaler(feature_range=(0,1))
    normalized_data = scaler.fit_transform(data)
    return normalized_data, scaler

# 准备训练数据
def prepare_training_data(data, look_back=1):
    X, Y = [], []
    # 计算有效索引最大值
    max_index = len(data) - look_back - 1
    
    # 确保有足够的数据点 (修改此处)
    if len(data) > look_back:
        # 调整循环范围 (修改此处)
        for i in range(len(data) - look_back):
            X.append(data[i:(i + look_back), 0])
            Y.append(data[i + look_back, 0])
    else:
        # 如果没有足够数据，使用可用数据
        # 添加安全检查 (修改此处)
        if len(data) > 0:
            # 使用最后一个数据点作为输入和输出
            X.append(data[-1:, 0].tolist())
            Y.append(data[-1, 0])
    
    # 添加安全返回
    if not X: 
        return np.empty((0, look_back)), np.empty((0,))
        
    return np.array(X), np.array(Y)

# 可视化
def visualize_results(original_data, sarima_prediction, bp_prediction, title):
    plt.figure(figsize=(12,6))
    print(f"可视化函数: {title}")
    
    # 转换预测值为NumPy数组以确保一致性
    sarima_pred_arr = sarima_prediction.values if isinstance(sarima_prediction, pd.Series) else sarima_prediction
    
    if bp_prediction is not None:
        # 打印调试信息
        print(f"BP预测原始形状: {bp_prediction.shape}")
        print(f"BP预测值: {bp_prediction}")
        
        # 确保是一维数组
        bp_pred_arr = bp_prediction.ravel()
        print(f"BP预测扁平化形状: {bp_pred_arr.shape}")
    
    # 绘制原始数据
    plt.plot(original_data.index, original_data.values, 'g-', label='原始数据')
    
    # 计算预测的开始时间
    if original_data.index.freq is None:
        base_freq = 'D'
    else:
        base_freq = original_data.index.freq
    
    # 为SARIMA预测创建索引
    if sarima_prediction is not None and len(sarima_prediction) > 0:
        sarima_start_date = original_data.index[-1] + pd.DateOffset(days=1)
        sarima_index = pd.date_range(start=sarima_start_date, 
                                     periods=len(sarima_prediction),
                                     freq=base_freq)
        
        # 使用点线图加标记
        plt.plot(sarima_index, sarima_pred_arr, 'bo-', markersize=8, 
                 linewidth=2, label='SARIMA预测')
    
    # 为BP预测创建索引
    if bp_prediction is not None and len(bp_prediction) > 0:
        if sarima_prediction is not None and len(sarima_prediction) > 0:
            bp_start_date = sarima_index[-1] + pd.DateOffset(days=1)
        else:
            bp_start_date = original_data.index[-1] + pd.DateOffset(days=1)
        
        bp_index = pd.date_range(start=bp_start_date, 
                                periods=len(bp_prediction),
                                freq=base_freq)
        
        # 转换为线形图数据
        plt.plot(bp_index, bp_pred_arr, 'ro-', markersize=8, 
                 linewidth=2, label='BP神经网络预测')
    
    # 删除重复的标注代码
    # ... (此处删除上面提到的重复代码块) ...
    
    plt.xlabel('日期')
    plt.ylabel('患病概率')
    plt.title(title)
    plt.legend()
    plt.grid(True, linestyle='--', alpha=0.7)
    
    # 自动调整日期显示格式
    plt.gcf().autofmt_xdate()
    
    if bp_prediction is None or len(bp_prediction) == 0:
        plt.annotate('注意: 由于数据不足未进行BP神经网络预测', 
                     xy=(0.5, 0.95), xycoords='figure fraction',
                     ha='center', fontsize=12, color='red')
    
    plt.tight_layout()
    plt.savefig(f'{title}_预测结果.png')
    plt.show()

    
主函数
def main():
    # 疾病数据文件路径,需要替换为你的实际文件路径
    disease_files = {
        'stroke': "C:\\Users\\dong\\Desktop\\stroke.csv",
        'heart': "C:\\Users\\dong\\Desktop\\heart.csv",
        'cirrhosis': "C:\\Users\\dong\\Desktop\\cirrhosis.csv"
    }

    for disease, file_path in disease_files.items():
        print(f"\n处理疾病: {disease}")

        # 加载数据
        data = load_data(file_path)
        print(f"加载数据成功，数据形状: {data.shape}")

        # 假设最后一列是目标列(患病概率)
        target_column = data.columns[-1]   # 最后一列是目标列
        target_data = data[[target_column]]
        print(f"目标列: {target_column}")

        # SARIMA 参数设置,这里需要根据具体数据进行调整
        order = (1,1,1)
        seasonal_order = (0,0,0,0)
        print(f"使用SARIMA参数: order={order}, seasonal_order={seasonal_order}")

        # SARIMA 预测
        sarima_pred = sarima_forecast(target_data,order,seasonal_order)
        print(f"SARIMA预测成功，预测长度: {len(sarima_pred)}")

        # 数据与归一化
        norm_data, scaler  = normalize_data(target_data)
        print("数据归一化完成")

        # 准备训练数据
        look_back = 1
        X, Y = prepare_training_data(norm_data, look_back)

        # 检查是否有有效训练数据
        if X.size == 0 or Y.size == 0:
            print("警告: 没有足够的训练数据,跳过神经网络训练")
            # 创建空模型以避免后续错误 - 这部分是新增的
            class DummyModel:
                def __call__(self, x): 
                    return torch.empty(0)
            bp_model = DummyModel()
        else:
            # 将数据转换为 PyTorch 张量
            X_tensor = torch.from_numpy(X).float()
            Y_tensor = torch.from_numpy(Y).float().view(-1,1)
            print("数据已转换为PyTorch张量")
            
            # 创建 BP 神经网络模型
            bp_model = BPNet(look_back)
            print(f"创建BP神经网络模型，输入维度: {look_back}")

            # 定义损失函数和优化器
            criterion = nn.BCELoss()
            optimizer = torch.optim.Adam(bp_model.parameters(), lr=0.001)
            print("优化器已定义")

            # 训练 BP 神经网络
            num_epochs = 100
            print(f"开始训练神经网络，训练轮次: {num_epochs}")

            for epoch in range(num_epochs):
                outputs = bp_model(X_tensor)
                loss = criterion(outputs, Y_tensor)

                optimizer.zero_grad()
                loss.backward()
                optimizer.step()

                if (epoch + 1) % 10 == 0:
                    print(f'轮次 [{epoch + 1}/{num_epochs}], 损失: {loss.item():.4f}')

            print("神经网络训练完成")

        # 创建 BP 神经网络模型
        bp_model = BPNet(look_back)
        print(f"创建BP神经网络模型，输入维度: {look_back}")

        # 定义损失函数和优化器
        criterion = nn.BCELoss()
        optimizer = torch.optim.Adam(bp_model.parameters(), lr=0.001)
        print("优化器已定义")

        # 训练 BP 神经网络
        num_epochs = 100
        print(f"开始训练神经网络，训练轮次: {num_epochs}")

        for epoch in range(num_epochs):
            outputs = bp_model(X_tensor)
            loss = criterion(outputs, Y_tensor)

            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

            if (epoch + 1) % 10 == 0:
                print(f'轮次 [{epoch + 1}/{num_epochs}], 损失: {loss.item():.4f}')

        print("神经网络训练完成")

        # 使用 SARIMA 预测结果进行 BP 神经网络
        print("使用SARIMA结果进行BP神经网络预测...")

        # SARIMA预测结果归一化
        sarima_pred_normalized = scaler.transform(sarima_pred.values.reshape(-1,1))

        # 准备BP神经网络的输入数据
        X_bp = []

        # 确保有足够数据点
        if len(sarima_pred_normalized) >= look_back:
            # 修改循环条件 - 使用len(sarima_pred_normalized) - look_back + 1
            for i in range(len(sarima_pred_normalized) - look_back + 1):
                X_bp.append(sarima_pred_normalized[i:(i + look_back), 0])
                
        # 检查是否有数据
        if not X_bp:
            print("警告: 没有足够的SARIMA预测数据进行神经网络输入")
            bp_pred = np.array([])
        else:
            X_bp = np.array(X_bp)
            print(f"BP输入数据准备完成,形状: {X_bp.shape}")
            
            # 转换为张量并预测
            X_bp_tensor = torch.from_numpy(X_bp).float()

            with torch.no_grad():
                bp_pred = bp_model(X_bp_tensor).numpy()
                # 反归一化
                if bp_pred.size > 0:
                    bp_pred = scaler.inverse_transform(bp_pred)

        # 转换为张量并预测
        X_bp_tensor = torch.from_numpy(X_bp).float()

        with torch.no_grad():
            bp_pred = bp_model(X_bp_tensor).numpy()
            # 反归一化获得最终预测值
            bp_pred = scaler.inverse_transform(bp_pred)

        print("BP神经网络预测成功")

        # 可视化结果
        visualize_results(target_data, sarima_pred, bp_pred, title=f'{disease} Disease Probability')



if __name__ == '__main__':
    main()

if __name__ == '__main__':
    print("开始疾病预测分析...")
    main()
    print("所有疾病预测分析完成")