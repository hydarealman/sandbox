import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import torch
import torch.nn as nn
from sklearn.preprocessing import MinMaxScaler, OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.model_selection import train_test_split
import lightgbm as lgb
from sklearn.metrics import accuracy_score, f1_score
import seaborn as sns
from scipy.stats import chi2_contingency
from statsmodels.tsa.statespace.sarimax import SARIMAX
import traceback
import os

# 全局设置
plt.rcParams['figure.dpi'] = 300
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False


def preprocess_data(df, target_col=None):
    """数据预处理：处理缺失值，分类变量编码"""
    print('缺失值情况: ')
    print(df.isnull().sum())

    # 处理缺失值
    for col in df.columns:
        if df[col].dtype == 'object':
            df[col].fillna(df[col].mode()[0], inplace=True)
        else:
            df[col].fillna(df[col].median(), inplace=True)
    
    # ===== 修复：异常值处理 - 排除目标列和ID列 =====
    numerical_cols = df.select_dtypes(include=[np.number]).columns
    
    # 排除目标列
    if target_col and target_col in numerical_cols:
        numerical_cols = numerical_cols.drop(target_col)
    
    # 排除ID列
    id_cols = [col for col in numerical_cols if 'id' in col.lower()]
    numerical_cols = numerical_cols.drop(id_cols)
    
    for col in numerical_cols:
        # 计算IQR
        Q1 = df[col].quantile(0.25)
        Q3 = df[col].quantile(0.75)
        IQR = Q3 - Q1
        
        # 设定上下限
        lower_bound = Q1 - 1.5 * IQR
        upper_bound = Q3 + 1.5 * IQR
        
        # 检测并处理异常值（用中位数替换）
        outlier_mask = (df[col] < lower_bound) | (df[col] > upper_bound)
        if outlier_mask.any():
            median_val = df[col].median()
            df.loc[outlier_mask, col] = median_val
            print(f"处理{col}的异常值: 替换{outlier_mask.sum()}个值")
    
    # 验证目标变量
    if target_col and target_col in df.columns:
        unique_vals = df[target_col].nunique()
        pos_count = df[target_col].sum() if df[target_col].dtype in ['int', 'float'] else 0
        
        print(f"目标变量 '{target_col}' 预处理后分布:")
        print(f"  唯一值数量: {unique_vals}")
        print(f"  阳性样本数: {pos_count}")
        
        if unique_vals < 2:
            print(f"警告: 目标变量'{target_col}'只有{unique_vals}个类别!")
        elif pos_count == 0:
            print(f"警告: 目标变量'{target_col}'无阳性样本!")

    # ===== 新增：针对中风数据集的特征工程 =====
    if target_col == 'stroke':
        # 创建风险特征
        df['age_risk'] = np.where(df['age'] > 65, 1, 0)
        df['glucose_risk'] = np.where(df['avg_glucose_level'] > 140, 1, 0)
        df['bmi_risk'] = np.where(df['bmi'] > 30, 1, 0)
        df['hypertension_risk'] = df['hypertension']
        df['heart_disease_risk'] = df['heart_disease']
        
        # 创建综合风险评分
        df['combined_risk'] = (
            df['age_risk'] + df['glucose_risk'] + df['bmi_risk'] + 
            df['hypertension_risk'] + df['heart_disease_risk']
        )
    
    return df

# 数据分析与可视化
def analyze_and_visualize(df, target_col, title, output_dir):
    """数据分析与可视化：统计特征、分布、相关性"""
    # 数值型变量的基本统计量
    categorical_cols = df.select_dtypes(include=['object']).columns
    numerical_cols = df.select_dtypes(include=[np.number]).columns

    numerical_df = df[numerical_cols]
    print(f'{title} 数值型变量基本统计量')
    print(numerical_df.describe())

    stats = df[numerical_cols].describe()
    print(f'{title} 数值型变量基本统计量')
    print(stats)

    # 数值型变量直方图
    if numerical_cols.size > 0:
        fig,axes = plt.subplots(len(numerical_cols), ncols=1, figsize=(10, 4*len(numerical_cols)))
        for i, col in enumerate(numerical_cols):
            sns.histplot(df[col], bins=15, kde=True, ax=axes[i])
            axes[i].set_title(col)
        plt.suptitle(f'{title} 数值型变量分布图', y=1.005)
        plt.tight_layout()
        plt.show()

    if len(numerical_cols) > 1:  # 确保有多于一个数值列
        # try:
            # 使用只包含数值列的数据框计算相关性
        correlations = numerical_df.corr()[target_col].drop(target_col, errors='ignore')
        if not correlations.empty:
            print(f'{title} 各因素 {target_col} 的相关性: ')
            print(correlations)
            
            # 绘制相关性热力图
            plt.figure(figsize=(12,10))
            # 使用 numerical_df 而不是原始 df
            sns.heatmap(numerical_df.corr(), 
                        annot=True, 
                        cmap='coolwarm', 
                        annot_kws={'size':8})
            plt.title(f'{title} 数值型变量相关性热力图')
            plt.tight_layout()
            plt.savefig(f"{output_dir}/{title.replace(' ', '_')}_heatmap.png", bbox_inches='tight')
            plt.show()
        # except Exception as e:
        #     print(f"绘制热力图时出错: {str(e)}")
        #     traceback.print_exc()  # 打印完整异常堆栈

    # 对分类变量进行卡方检验
    for col in categorical_cols:
        if col != target_col:  # 避免目标列自身
            try:
                contingency_table = pd.crosstab(df[col], df[target_col])
                chi2, p, dof, ex = chi2_contingency(contingency_table)
                print(f'特征"{col}"卡方值: {chi2}, p 值: {p}')
            except:
                print(f'无法计算特征"{col}"的卡方值')

# ==================== 时间序列预测部分 ====================
# BP神经网络模型
# 这段代码定义了一个简单的BP(反向传播) 神经网络模型 主要用于二分类任务
class BPNet(nn.Module):
    """BP神经网络模型"""
    # 初始化方法__init__
    # 输入数据的特征维度(如: 图片像素数,特征向量长度)
    def __init__(self, input_dim):
        # 定义网络层
        super(BPNet, self).__init__()       # 调用父类nn.Module的初始化方法
        self.fc1 = nn.Linear(input_dim, 10) # 全连接层1
        self.relu = nn.ReLU()               # 全激活函数
        self.fc2 = nn.Linear(10, 1)         # 全连接层2
        self.sigmoid = nn.Sigmoid()         # 输出激活函数
    # 前向传播 forward
    def forward(self, x):
        out = self.fc1(x)
        out = self.relu(out)
        out = self.fc2(out)
        out = self.sigmoid(out)
        return out

#SARIMA时间序列预测函数
# SARIMA模型预测
# data: 输入的时间序列数据   # 非季节参数的阶数    # 季节参数的阶数
def sarima_forecast(data, order=(1,1,1), seasonal_order=(0,0,0,0)):
    """SARIMA模型预测"""
    # SARIMAX模型初始化
    model = SARIMAX(data, order=order, seasonal_order=seasonal_order)
    # model.fit()方法拟合模型
    model_fit = model.fit(disp=False)
    
    # 确保至少有1步预测，最多不超过数据长度的25%
    steps = max(1, min(10, len(data) // 4 or 30))
    
    #执行预测并返回结果
    forecast = model_fit.get_forecast(steps=steps)
    return forecast.predicted_mean

# 准备训练数据
# data: 原始时间序列数据    look_back: 时间窗口的大小
def prepare_training_data(data, look_back=1):
    """准备训练数据"""
    # 初始化空列表 
    X, Y = [], []
    # 通过滑动窗口技术将时间序列数据转换为监督学习格式
    # 处理数据长度大于时间窗口的情况
    # 
    if len(data) > look_back:
        for i in range(len(data) - look_back):
            # 这样装换的数据可用于训练多种时间序列模型
            # 创建输入序列
            X.append(data[i:(i + look_back)])
            # 创建目标值
            Y.append(data[i + look_back])# 位于当前窗口之后的下一个时间点的数据
    # 处理数据长度不足的情况
    else:
        # 如果没有足够数据，使用可用数据
        if len(data) > 0:
            X.append(data[-1:])
            Y.append(data[-1])
    # 返回结果
    return np.array(X), np.array(Y)

# 可视化结果
# original_data: 原始时间序列数据
# sarima_prediction:SARIMA模型的预测结果
# bq_prediction: BP神经网络的预测结果
# title: 图表的标题
# output_dir: 图片保存的目录路径
def visualize_results(original_data, sarima_prediction, bp_prediction, title, output_dir):
    """可视化预测结果"""
    plt.figure(figsize=(12,6))  
    
    # 绘制原始数据
    # X轴数据:original_data.index,Y轴数据:original_data.values,'g-': 格式化字符串'g'表示颜色为绿色,'-'表示线性为实线
    plt.plot(original_data.index, original_data.values, 'g-', label='原始数据')
    
    # SARIMA预测结果
    # 条件检查 - 确保有可用的预测数据
    if sarima_prediction is not None and len(sarima_prediction) > 0:
        # 创建预测时间索引
        sarima_index = pd.date_range(start=original_data.index[-1] + pd.DateOffset(days=1), 
                                     periods=len(sarima_prediction))
        plt.plot(sarima_index, sarima_prediction.values, 'bo-', label='SARIMA预测')
    
    # BP神经网络预测
    # 条件检查 - 确保有有效的BP预测数据
    if bp_prediction is not None and len(bp_prediction) > 0:
        # 确定预测起始位置
        start_idx = len(original_data) if sarima_prediction is None else len(sarima_prediction)
        # 创建预测时间序列
        bp_index = pd.date_range(start=original_data.index[-1] + pd.DateOffset(days=start_idx), 
                                 periods=len(bp_prediction))
        plt.plot(bp_index, bp_prediction, 'ro-', label='BP神经网络预测')
    
    plt.xlabel('日期')            #X轴标签
    plt.ylabel('患病概率')        #Y轴标签
    plt.title(title)             #设置图标标题
    plt.legend()                 #添加图例
    plt.grid(True)               #添加网格线
    plt.tight_layout()           #调整布局(自动调整子图/布局)
    # 添加保存代码
    plt.savefig(f"{output_dir}/{title.replace(' ', '_')}_forecast.png", bbox_inches='tight')
    # 显示图表
    plt.show()

# ==================== LSTM与LightGBM部分 ====================
# LSTM模型
# 基于LSTM (长短期记忆网络)的时间序列预测模型
class LSTMModel(nn.Module): 
    """LSTM模型"""
    # input_size:   输入特征维度
    # hidden_size:  隐藏层维度 
    # output_size:  LSTM层数
    def __init__(self, input_size, hidden_size, num_layers, output_size):
        super(LSTMModel, self).__init__()   # 父类初始化 启用神经网络模块的注册机制, 跟踪模型参数和子模块
        self.hidden_size = hidden_size       
        self.num_layers = num_layers
        # LSTM层定义
        self.lstm = nn.LSTM(input_size, hidden_size, num_layers, batch_first=True)
        # 全连接层定义
        self.fc = nn.Linear(hidden_size, output_size)
    # LSTM模型的前向传播过程
    def forward(self, x):
        # 初始化隐藏状态和细胞状态
        h0 = torch.zeros(self.num_layers, x.size(0), self.hidden_size).to(x.device)
        c0 = torch.zeros(self.num_layers, x.size(0), self.hidden_size).to(x.device)

        # LSTM处理序列
        out, _ = self.lstm(x, (h0, c0))

        # 处理输出
        out = self.fc(out[:, -1, :])
        return out

# 为训练准备数据
# 专业的数据预处理流程
# def prepare_data_for_training(df, target_col, disease_name):
#     """为训练准备数据"""
#     print(f"\n处理{disease_name}数据集...")  # 日志记录
#     label = df[target_col].values           # 标签提取

#     # 肝硬化数据集特殊处理
#     if disease_name == "肝硬化":
#         label = (label > 2).astype(int)

#     # 特征分离 
#     features = df.drop(target_col, axis=1)

#     # 识别特征类型
#     # 类别型特征识别
#     # 数值型特征识别
#     # 结果获取
#     categorical_cols = features.select_dtypes(include=['object']).columns
#     numerical_cols = features.select_dtypes(exclude=['object']).columns

#     # 特征信息输出
#     print(f"  类别型特征 ({len(categorical_cols)}): {list(categorical_cols)}")
#     print(f"  数值型特征 ({len(numerical_cols)}): {list(numerical_cols)}")

#     # 创建预处理管道
#     preprocessor = ColumnTransformer(
#         transformers=[
#             # 使用MinMaxScaler()进行归一化
#             ('num', MinMaxScaler(), numerical_cols),
#             # 使用OneHotEncoder()进行独热编码
#             ('cat', OneHotEncoder(handle_unknown='ignore'), categorical_cols)
#         ])
    
#     # 转换特征
#     processed_features = preprocessor.fit_transform(features)
#     print(f"  处理后特征维度: {processed_features.shape}")

#     # 确保训练数据和标签分开
#     X = processed_features
#     y = label
    
#     # 打印数据形状以确保正确
#     print(f"  特征形状: {X.shape}, 标签形状: {y.shape}")

#     # 返回结果
#     return processed_features, label, preprocessor


from imblearn.over_sampling import SMOTE

def prepare_data_for_training(df, target_col, disease_name):
    """为训练准备数据"""
    print(f"\n处理{disease_name}数据集...")  # 日志记录
    label = df[target_col].values           # 标签提取

    # 肝硬化数据集特殊处理
    if disease_name == "肝硬化":
        label = (label > 2).astype(int)

    # 特征分离 
    features = df.drop(target_col, axis=1)

    # 识别特征类型
    categorical_cols = features.select_dtypes(include=['object']).columns
    numerical_cols = features.select_dtypes(exclude=['object']).columns

    # 特征信息输出
    print(f"  类别型特征 ({len(categorical_cols)}): {list(categorical_cols)}")
    print(f"  数值型特征 ({len(numerical_cols)}): {list(numerical_cols)}")

    # 创建预处理管道
    preprocessor = ColumnTransformer(
        transformers=[
            # 使用MinMaxScaler()进行归一化
            ('num', MinMaxScaler(), numerical_cols),
            # 使用OneHotEncoder()进行独热编码
            ('cat', OneHotEncoder(handle_unknown='ignore'), categorical_cols)
        ])
    
    # 转换特征
    processed_features = preprocessor.fit_transform(features)
    print(f"  处理后特征维度: {processed_features.shape}")

    # ===== 新增：针对中风数据集进行过采样 =====
    if disease_name == "中风":
        print("  对中风数据集进行过采样处理...")
        smote = SMOTE(random_state=42)
        processed_features, label = smote.fit_resample(processed_features, label)
        print(f"  过采样后特征维度: {processed_features.shape}, 标签分布: {pd.Series(label).value_counts()}")
    
    # 返回结果
    return processed_features, label, preprocessor


# def train_and_evaluate_lstm(X, Y, input_size, hidden_size, num_layers, output_size, 
#                            epochs, batch_size, learning_rate, disease_name, output_dir):
#     """训练和评估LSTM模型"""
#     print(f"\n训练{disease_name} LSTM模型...")
#     device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    
#     # ==== 修复：正确转换张量形状 ====
#     # 原始数据形状应为 (n_samples, n_features)
#     # LSTM 期望形状为 (n_samples, sequence_length, n_features)
#     # 这里 sequence_length=1，所以我们需要 reshape 而不是 unsqueeze
#     X = torch.tensor(X, dtype=torch.float32).reshape(-1, 1, input_size)  # 修复维度
    
#     # 标签处理
#     Y = torch.tensor(Y, dtype=torch.float32).unsqueeze(1)  # 将标签转换为[batch_size, 1]维度
    
#     # 分割数据集
#     X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.2, random_state=42)
    
#     # 确保有足够的数据
#     if len(X_train) == 0:
#         print(f"错误：没有足够的训练数据用于{disease_name}模型")
#         return None
    
#     # 创建模型并移动到设备
#     model = LSTMModel(input_size, hidden_size, num_layers, output_size).to(device)
#     criterion = nn.BCEWithLogitsLoss()
#     optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)

#     # 训练模型
#     train_losses = []
#     for epoch in range(epochs):
#         model.train()
#         epoch_loss = 0
#         # 批量训练处理
#         for i in range(0, len(X_train), batch_size):
#             # 获取批次数据并移动到设备
#             batch_X = X_train[i:i + batch_size].to(device)
#             batch_Y = Y_train[i:i + batch_size].to(device)
            
#             # 前向传播
#             outputs = model(batch_X)
#             loss = criterion(outputs, batch_Y)
            
#             # 反向传播和优化
#             optimizer.zero_grad()
#             loss.backward()
#             optimizer.step()
            
#             epoch_loss += loss.item() * batch_X.size(0)
        
#         # 计算平均损失
#         epoch_loss /= len(X_train)
#         train_losses.append(epoch_loss)
        
#         # 每10个epoch打印一次
#         if (epoch + 1) % 10 == 0:
#             print(f"Epoch [{epoch + 1}/{epochs}], Loss: {epoch_loss:.4f}")
    
#     # 评估模型
#     model.eval()
#     with torch.no_grad():
#         # 移动测试数据到设备
#         X_test = X_test.to(device)
        
#         # 预测
#         test_outputs = model(X_test)
#         predicted = (torch.sigmoid(test_outputs) > 0.5).float().cpu()
        
#         # 评估指标
#         Y_test_np = Y_test.numpy().flatten()
#         predicted_np = predicted.numpy().flatten()
        
#         # 确保有预测结果
#         if len(Y_test_np) > 0 and len(predicted_np) > 0:
#             accuracy = accuracy_score(Y_test_np, predicted_np)
#             f1 = f1_score(Y_test_np, predicted_np, average='weighted')
#             print(f'{disease_name}模型 Test Accuracy: {accuracy:.4f}, F1 Score: {f1:.4f}')
    
#     # 绘制损失曲线
#     if len(train_losses) > 0:
#         plt.plot(range(1, epochs + 1), train_losses)
#         plt.xlabel('Epoch')
#         plt.ylabel('Training Loss')
#         plt.title(f'{disease_name} LSTM 训练损失曲线')
#         # 添加保存代码
#         plt.savefig(f"{output_dir}/{disease_name}_LSTM_training_loss.png", bbox_inches='tight')
#         plt.show()

#     return model

def train_and_evaluate_lstm(X, Y, input_size, hidden_size, num_layers, output_size, 
                           epochs, batch_size, learning_rate, disease_name, output_dir):
    """训练和评估LSTM模型"""
    print(f"\n训练{disease_name} LSTM模型...")
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    
    # ==== 修复：正确转换张量形状 ====
    X = torch.tensor(X, dtype=torch.float32).reshape(-1, 1, input_size)  # 修复维度
    
    # 标签处理
    Y = torch.tensor(Y, dtype=torch.float32).unsqueeze(1)  # 将标签转换为[batch_size, 1]维度
    
    # 分割数据集
    X_train, X_test, Y_train, Y_test = train_test_split(X, Y, test_size=0.2, random_state=42)
    
    # 确保有足够的数据
    if len(X_train) == 0:
        print(f"错误：没有足够的训练数据用于{disease_name}模型")
        return None
    
    # ===== 新增：计算类别权重 =====
    # 计算阳性样本比例
    pos_count = Y_train.sum().item()
    neg_count = len(Y_train) - pos_count
    weight = neg_count / pos_count  # 用于平衡类别的权重
    
    # 创建模型并移动到设备
    model = LSTMModel(input_size, hidden_size, num_layers, output_size).to(device)
    
    # 使用带权重的损失函数
    criterion = nn.BCEWithLogitsLoss(pos_weight=torch.tensor([weight]).to(device))
    
    optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)

    # 训练模型
    train_losses = []
    for epoch in range(epochs):
        model.train()
        epoch_loss = 0
        # 批量训练处理
        for i in range(0, len(X_train), batch_size):
            # 获取批次数据并移动到设备
            batch_X = X_train[i:i + batch_size].to(device)
            batch_Y = Y_train[i:i + batch_size].to(device)
            
            # 前向传播
            outputs = model(batch_X)
            loss = criterion(outputs, batch_Y)
            
            # 反向传播和优化
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
            
            epoch_loss += loss.item() * batch_X.size(0)
        
        # 计算平均损失
        epoch_loss /= len(X_train)
        train_losses.append(epoch_loss)
        
        # 每10个epoch打印一次
        if (epoch + 1) % 10 == 0:
            print(f"Epoch [{epoch + 1}/{epochs}], Loss: {epoch_loss:.4f}")
    
    # 评估模型
    model.eval()
    with torch.no_grad():
        # 移动测试数据到设备
        X_test = X_test.to(device)
        
        # 预测
        test_outputs = model(X_test)
        predicted = (torch.sigmoid(test_outputs) > 0.5).float().cpu()
        
        # 评估指标
        Y_test_np = Y_test.numpy().flatten()
        predicted_np = predicted.numpy().flatten()
        
        # 确保有预测结果
        if len(Y_test_np) > 0 and len(predicted_np) > 0:
            accuracy = accuracy_score(Y_test_np, predicted_np)
            f1 = f1_score(Y_test_np, predicted_np, average='weighted')
            print(f'{disease_name}模型 Test Accuracy: {accuracy:.4f}, F1 Score: {f1:.4f}')
    
    # 绘制损失曲线
    if len(train_losses) > 0:
        plt.plot(range(1, epochs + 1), train_losses)
        plt.xlabel('Epoch')
        plt.ylabel('Training Loss')
        plt.title(f'{disease_name} LSTM 训练损失曲线')
        # 添加保存代码
        plt.savefig(f"{output_dir}/{disease_name}_LSTM_training_loss.png", bbox_inches='tight')
        plt.show()

    return model


def boost_prediction(X, Y, lstm_model, disease_name, output_dir):
    """使用LightGBM增强预测"""
    print(f"\n训练{disease_name} LightGBM模型...")
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    
    # 获取LSTM特征
    with torch.no_grad():
        # 正确重塑输入数据形状
        lstm_input = torch.tensor(X, dtype=torch.float32).reshape(-1, 1, X.shape[1]).to(device)
        lstm_features = lstm_model(lstm_input).cpu().numpy()
    
    # 确保标签是一维的
    Y = Y.flatten()
    
    # 分割数据集
    X_train, X_test, Y_train, Y_test = train_test_split(lstm_features, Y, test_size=0.2, random_state=42)
    
    # 参数设置
    params = {
        'boosting_type': 'gbdt',
        'objective': 'binary',
        'metric': 'binary_logloss',
        'num_leaves': 31,
        'learning_rate': 0.05,
        'feature_fraction': 0.9,
        'bagging_fraction': 0.8,
        'bagging_freq': 5,
        'verbose': -1
    }
    
    # 训练LightGBM模型
    train_data = lgb.Dataset(X_train, label=Y_train)
    valid_data = lgb.Dataset(X_test, label=Y_test, reference=train_data)
    
    # 创建回调函数列表
    callbacks = [lgb.early_stopping(stopping_rounds=10)]

    # 训练模型
    bst = lgb.train(
        params,
        train_data,
        num_boost_round=100,
        valid_sets=[valid_data],
        callbacks=callbacks
    )
    
    # 评估模型
    Y_pred_proba = bst.predict(X_test)
    Y_pred = (Y_pred_proba > 0.5).astype(int)
    
    if len(Y_test) > 0:
        accuracy = accuracy_score(Y_test, Y_pred)
        f1 = f1_score(Y_test, Y_pred, average='weighted')
        print(f'{disease_name} LightGBM Test Accuracy: {accuracy:.4f}, F1 Score: {f1:.4f}')
    
    return bst

# 模型性能对比图
def plot_model_performance(performance_data, output_dir):
    """绘制模型性能对比图"""
    diseases = list(performance_data.keys())
    models = ['LSTM', 'LightGBM']
    
    # 准备数据
    accuracy_data = {
        model: [performance_data[d][model]['accuracy'] for d in diseases]
        for model in models
    }
    
    f1_data = {
        model: [performance_data[d][model]['f1'] for d in diseases]
        for model in models
    }
    
    # 创建图表
    fig, axes = plt.subplots(1, 2, figsize=(15, 6))
    
    # 准确率对比
    x = np.arange(len(diseases))
    width = 0.35
    for i, model in enumerate(models):
        axes[0].bar(x + i*width, accuracy_data[model], width, label=model)
    
    axes[0].set_xlabel('疾病类型')
    axes[0].set_ylabel('准确率')
    axes[0].set_title('模型准确率对比')
    axes[0].set_xticks(x + width/2)
    axes[0].set_xticklabels(diseases)
    axes[0].legend()
    
    # F1分数对比
    for i, model in enumerate(models):
        axes[1].bar(x + i*width, f1_data[model], width, label=model)
    
    axes[1].set_xlabel('疾病类型')
    axes[1].set_ylabel('F1分数')
    axes[1].set_title('模型F1分数对比')
    axes[1].set_xticks(x + width/2)
    axes[1].set_xticklabels(diseases)
    axes[1].legend()
    
    plt.tight_layout()
    plt.savefig(f"{output_dir}/Model_Performance_Comparison.png", bbox_inches='tight')
    plt.show()

# 预测概率分布图
def plot_prediction_distribution(y_true, y_pred_proba, disease_name, output_dir):
    """绘制预测概率分布图"""
    plt.figure(figsize=(10, 6))
    
    # 分离正负样本的预测概率
    pos_proba = y_pred_proba[y_true == 1]
    neg_proba = y_pred_proba[y_true == 0]
    
    # 绘制分布图
    sns.kdeplot(pos_proba, label='患病', fill=True, color='red', alpha=0.5)
    sns.kdeplot(neg_proba, label='健康', fill=True, color='green', alpha=0.5)
    
    plt.xlabel('预测概率')
    plt.ylabel('密度')
    plt.title(f'{disease_name} 预测概率分布')
    plt.legend()
    plt.grid(True, linestyle='--', alpha=0.7)
    
    plt.tight_layout()
    plt.savefig(f"{output_dir}/{disease_name}_Prediction_Distribution.png", bbox_inches='tight')
    plt.show()

from sklearn.metrics import roc_curve, auc

# ROC曲线
def plot_roc_curve(y_true, y_pred_proba, disease_name, output_dir):
    """绘制ROC曲线"""
    fpr, tpr, _ = roc_curve(y_true, y_pred_proba)
    roc_auc = auc(fpr, tpr)
    
    plt.figure(figsize=(8, 6))
    plt.plot(fpr, tpr, color='darkorange', lw=2, 
             label=f'ROC曲线 (AUC = {roc_auc:.2f})')
    plt.plot([0, 1], [0, 1], color='navy', lw=2, linestyle='--')
    plt.xlim([0.0, 1.0])
    plt.ylim([0.0, 1.05])
    plt.xlabel('假阳性率')
    plt.ylabel('真阳性率')
    plt.title(f'{disease_name} ROC曲线')
    plt.legend(loc="lower right")
    plt.grid(True, alpha=0.3)
    
    plt.tight_layout()
    plt.savefig(f"{output_dir}/{disease_name}_ROC_Curve.png", bbox_inches='tight')
    plt.show()

# 混淆矩阵热力图
from sklearn.metrics import confusion_matrix

def plot_confusion_matrix(y_true, y_pred, disease_name, output_dir):
    """绘制混淆矩阵热力图"""
    cm = confusion_matrix(y_true, y_pred)
    
    plt.figure(figsize=(8, 6))
    sns.heatmap(cm, annot=True, fmt='d', cmap='Blues', 
                xticklabels=['健康', '患病'], 
                yticklabels=['健康', '患病'])
    plt.xlabel('预测标签')
    plt.ylabel('真实标签')
    plt.title(f'{disease_name} 混淆矩阵')
    
    plt.tight_layout()
    plt.savefig(f"{output_dir}/{disease_name}_Confusion_Matrix.png", bbox_inches='tight')
    plt.show()

def plot_feature_importance(model, feature_names, disease_name, output_dir):
    """绘制特征重要性图"""
    # 检查模型是否支持特征重要性
    if not hasattr(model, 'feature_importances_'):
        print(f"警告: {disease_name}模型不支持特征重要性")
        return
    
    # 检查特征数量
    if len(feature_names) == 0:
        print(f"警告: {disease_name}没有可用的特征名称")
        return
    
    # 获取特征重要性
    try:
        importance = model.feature_importances_
        
        # 确保特征数量和重要性数量匹配
        if len(importance) != len(feature_names):
            print(f"警告: {disease_name}特征数量({len(feature_names)})与重要性数量({len(importance)})不匹配")
            return
            
        # 排序特征重要性
        sorted_idx = np.argsort(importance)[::-1]
        sorted_importance = importance[sorted_idx]
        sorted_names = np.array(feature_names)[sorted_idx]
        
        # 创建图表
        plt.figure(figsize=(12, 8))
        plt.bar(range(len(importance)), sorted_importance, align='center')
        plt.xticks(range(len(importance)), sorted_names, rotation=90)
        plt.xlabel('特征')
        plt.ylabel('重要性')
        plt.title(f'{disease_name} 特征重要性')
        plt.tight_layout()
        
        # 保存图表
        plt.savefig(f"{output_dir}/{disease_name}_Feature_Importance.png", bbox_inches='tight')
        plt.show()
        
    except Exception as e:
        print(f"绘制{disease_name}特征重要性时出错: {str(e)}")

def get_prediction_probabilities(model, X, device):
    """
    获取模型预测概率
    model: LSTM模型
    X: 输入数据
    device: 计算设备
    """
    model.eval()
    
    # 正确重塑输入数据形状
    X_tensor = torch.tensor(X, dtype=torch.float32).reshape(-1, 1, X.shape[1]).to(device)
    
    with torch.no_grad():
        outputs = model(X_tensor)
        probabilities = torch.sigmoid(outputs).cpu().numpy().flatten()
    
    return probabilities


def get_feature_names(preprocessor):
    """从预处理器获取特征名称"""
    feature_names = []
    
    # 遍历预处理器中的所有转换器
    for name, transformer, columns in preprocessor.transformers_:
        if name == 'remainder':
            continue
            
        # 获取转换后的特征名称
        if hasattr(transformer, 'get_feature_names_out'):
            # 对于有 get_feature_names_out 方法的转换器
            if name == 'num':
                # 数值特征通常没有变化
                feature_names.extend(columns)
            else:
                # 类别特征经过编码
                feature_names.extend(transformer.get_feature_names_out(columns))
        else:
            # 对于没有该方法的转换器，使用原始列名
            feature_names.extend(columns)
    
    return feature_names

def get_default_coefficients():
    """返回默认关联系数"""
    return {
        'stroke_heart': 1.2,
        'stroke_cirrhosis': 1.1,
        'heart_cirrhosis': 1.3,
        'all': 1.5
    }

def calculate_comorbidity_coefficients(dfs):
    """
    从数据中计算疾病间的关联系数
    dfs: 包含三个疾病数据集的字典+
    """
    try:
        # 检查所有数据集是否有 'id' 列
        if 'id' in dfs['stroke'].columns and 'id' in dfs['heart'].columns and 'id' in dfs['cirrhosis'].columns:
            # 合并数据集（假设有共同的ID列）
            merged_df = pd.merge(
                dfs['stroke'][['id', 'stroke']], 
                dfs['heart'][['id', 'HeartDisease']], 
                on='id'
            )
            merged_df = pd.merge(
                merged_df, 
                dfs['cirrhosis'][['id', 'Stage']], 
                on='id'
            )
            
            # 计算两病共病概率
            stroke_heart_coef = (
                merged_df[(merged_df['stroke'] == 1) & (merged_df['HeartDisease'] == 1)].shape[0] /
                (merged_df['stroke'].mean() * merged_df['HeartDisease'].mean() * merged_df.shape[0])
            )
            
            stroke_cirrhosis_coef = (
                merged_df[(merged_df['stroke'] == 1) & (merged_df['Stage'] > 2)].shape[0] /
                (merged_df['stroke'].mean() * (merged_df['Stage'] > 2).mean() * merged_df.shape[0])
            )
            
            heart_cirrhosis_coef = (
                merged_df[(merged_df['HeartDisease'] == 1) & (merged_df['Stage'] > 2)].shape[0] /
                (merged_df['HeartDisease'].mean() * (merged_df['Stage'] > 2).mean() * merged_df.shape[0])
            )
            
            # 计算三病共病概率
            all_coef = (
                merged_df[
                    (merged_df['stroke'] == 1) & 
                    (merged_df['HeartDisease'] == 1) & 
                    (merged_df['Stage'] > 2)
                ].shape[0] /
                (merged_df['stroke'].mean() * 
                 merged_df['HeartDisease'].mean() * 
                 (merged_df['Stage'] > 2).mean() * 
                 merged_df.shape[0])
            )
            
            return {
                'stroke_heart': max(1.0, stroke_heart_coef),  # 确保至少为1
                'stroke_cirrhosis': max(1.0, stroke_cirrhosis_coef),
                'heart_cirrhosis': max(1.0, heart_cirrhosis_coef),
                'all': max(1.0, all_coef)
            }
        else:
            print("数据集缺少 'id' 列，无法计算关联系数")
            return get_default_coefficients()
    except Exception as e:
        print(f"计算关联系数时出错: {str(e)}")
        return get_default_coefficients()
    
    # 可视化共病风险

def visualize_comorbidity_risk(results, output_dir):
    """可视化共病风险预测结果"""
    # 创建图表
    fig, axes = plt.subplots(1, 2, figsize=(15, 6))
    
    # 单病风险条形图
    diseases = ['中风', '心脏病', '肝硬化']
    probs = [
        results['single_disease']['stroke'],
        results['single_disease']['heart'],
        results['single_disease']['cirrhosis']
    ]
    
    axes[0].bar(diseases, probs, color=['blue', 'green', 'red'])
    axes[0].set_title('单病患病风险')
    axes[0].set_ylabel('患病概率')
    axes[0].set_ylim(0, 1)
    
    # 共病风险条形图
    comorbidity_types = ['中风+心脏病', '中风+肝硬化', '心脏病+肝硬化', '三种疾病']
    comorbidity_probs = [
        results['comorbidity']['stroke_heart'],
        results['comorbidity']['stroke_cirrhosis'],
        results['comorbidity']['heart_cirrhosis'],
        results['comorbidity']['all']
    ]
    
    axes[1].bar(comorbidity_types, comorbidity_probs, color='purple')
    axes[1].set_title('共病风险')
    axes[1].set_ylabel('患病概率')
    axes[1].tick_params(axis='x', rotation=15)
    axes[1].set_ylim(0, max(comorbidity_probs)*1.2)
    
    plt.tight_layout()
    plt.savefig(f"{output_dir}/Comorbidity_Risk.png", bbox_inches='tight')
    plt.show()

# 修改样本患者数据创建方式
def create_sample_patient(datasets):
    """
    创建一个包含所有必要特征的样本患者
    datasets: 包含三个数据集的字典 {'stroke': stroke_df, 'heart': heart_df, 'cirrhosis': cirrhosis_df}
    """
    # 合并所有数据集的列
    all_features = set()
    for df in datasets.values():
        # 排除目标列（这些是我们要预测的，不是输入特征）
        if 'stroke' in df.columns:
            cols = [col for col in df.columns if col != 'stroke']
        elif 'HeartDisease' in df.columns:
            cols = [col for col in df.columns if col != 'HeartDisease']
        elif 'Stage' in df.columns:
            cols = [col for col in df.columns if col != 'Stage']
        else:
            cols = df.columns
        all_features.update(cols)
    
    # 创建样本患者数据 - 使用所有特征的默认值
    sample_data = {}
    for feature in all_features:
        # 尝试从任一数据集中获取特征类型
        found = False
        for df in datasets.values():
            if feature in df.columns:
                # 根据特征类型设置默认值
                if df[feature].dtype == 'object':
                    sample_data[feature] = df[feature].mode()[0]
                    found = True
                    break
                else:
                    sample_data[feature] = df[feature].median()
                    found = True
                    break
        if not found:
            # 如果找不到特征，设置一个中性值
            sample_data[feature] = 0
    
    return pd.DataFrame([sample_data])

# ==================== 主程序 ====================
# 1.设置输出目录
# 2.加载三个数据集
# 3.数据预处理与分析
# 4.为每个疾病数据集准备训练数据
# 5.训练三个疾病数据集准备训练数据
# 6.尝试进行时间序列预测
# 7.打印共病预测框架
def main():
    # 创建图片保存目录
    output_dir = "./output_figures"
    os.makedirs(output_dir, exist_ok=True)
    # 数据文件路径
    stroke_path = "C:\\Users\\dong\\Desktop\\stroke.csv"
    heart_path = "C:\\Users\\dong\\Desktop\\heart.csv"
    cirrhosis_path = "C:\\Users\\dong\\Desktop\\cirrhosis.csv"
    
    # 加载原始数据
    stroke_df = pd.read_csv(stroke_path)
    heart_df = pd.read_csv(heart_path)
    cirrhosis_df = pd.read_csv(cirrhosis_path)
    
    print("\n" + "="*50)
    print("开始数据预处理与分析")
    print("="*50)
    
    # 预处理所有数据集
    stroke_df = preprocess_data(stroke_df, target_col='stroke')
    heart_df = preprocess_data(heart_df, target_col='HeartDisease')
    cirrhosis_df = preprocess_data(cirrhosis_df, target_col='Stage')

    # 预处理后验证目标变量
    print("\n预处理后目标变量分布:")
    print(f"中风数据集阳性样本数: {stroke_df['stroke'].sum()}")
    print(f"心脏病数据集阳性样本数: {heart_df['HeartDisease'].sum()}")
    
    # 肝硬化特殊处理 - 将Stage>2视为阳性
    cirrhosis_positive = (cirrhosis_df['Stage'] > 2).sum()
    print(f"肝硬化数据集阳性样本数(Stage>2): {cirrhosis_positive}")
    
    # 如果阳性样本数为0，抛出异常
    if stroke_df['stroke'].sum() == 0:
        raise ValueError("中风数据集无阳性样本!")
    
    # 分析与可视化
    analyze_and_visualize(stroke_df, 'stroke', '中风数据集',output_dir)
    analyze_and_visualize(heart_df, 'HeartDisease', '心脏病数据集',output_dir)
    analyze_and_visualize(cirrhosis_df, 'Stage', '肝硬化数据集',output_dir)
    
    print("\n" + "="*50)
    print("开始单病预测模型训练")
    print("="*50)
    
    # LSTM模型参数
    hidden_size = 64
    num_layers = 2
    batch_size = 32
    epochs = 50
    learning_rate = 0.001
    
    # 为每个疾病准备训练数据
    stroke_features, stroke_labels, stroke_preprocessor = prepare_data_for_training(
        stroke_df, 'stroke', '中风')
    
    heart_features, heart_labels, heart_preprocessor = prepare_data_for_training(
        heart_df, 'HeartDisease', '心脏病')
    
    cirrhosis_features, cirrhosis_labels, cirrhosis_preprocessor = prepare_data_for_training(
        cirrhosis_df, 'Stage', '肝硬化')
    
    # ============== 新增：存储模型性能用于对比 ==============
    performance_data = {}
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    # ===================================================

    # 训练心脏病模型
    heart_lstm = train_and_evaluate_lstm(
        heart_features, heart_labels,
        input_size=heart_features.shape[1],
        hidden_size=hidden_size,
        num_layers=num_layers,
        output_size=1,
        epochs=epochs,
        batch_size=batch_size,
        learning_rate=learning_rate,
        disease_name="心脏病",output_dir=output_dir)
    
    heart_boost = boost_prediction(
        heart_features, heart_labels, heart_lstm, "心脏病",output_dir)
    

    # ============== 新增：心脏病模型可视化 ==============
    # 划分测试集
    X_train_heart, X_test_heart, Y_train_heart, Y_test_heart = train_test_split(
        heart_features, heart_labels, test_size=0.2, random_state=42
    )
    
    # 获取预测概率
    heart_pred_proba = get_prediction_probabilities(heart_lstm, X_test_heart, device)
    
    # 绘制可视化图表
    plot_prediction_distribution(Y_test_heart, heart_pred_proba, '心脏病', output_dir)
    plot_roc_curve(Y_test_heart, heart_pred_proba, '心脏病', output_dir)
    plot_confusion_matrix(Y_test_heart, (heart_pred_proba > 0.5).astype(int), '心脏病', output_dir)
    
    # 计算并存储性能指标
    heart_lstm_accuracy = accuracy_score(Y_test_heart, (heart_pred_proba > 0.5).astype(int))
    heart_lstm_f1 = f1_score(Y_test_heart, (heart_pred_proba > 0.5).astype(int))
    
    
    with torch.no_grad():
        X_test_heart_tensor = torch.tensor(X_test_heart, dtype=torch.float32).unsqueeze(1).to(device)
        heart_lstm_features_test = heart_lstm(X_test_heart_tensor).cpu().numpy().flatten()
        heart_boost_pred = heart_boost.predict(heart_lstm_features_test.reshape(-1, 1))

    heart_boost_accuracy = accuracy_score(Y_test_heart, (heart_boost_pred > 0.5).astype(int))
    heart_boost_f1 = f1_score(Y_test_heart, (heart_boost_pred > 0.5).astype(int))
# 修改这里 - 结束
    performance_data['心脏病'] = {
        'LSTM': {'accuracy': heart_lstm_accuracy, 'f1': heart_lstm_f1},
        'LightGBM': {'accuracy': heart_boost_accuracy, 'f1': heart_boost_f1}
    }
    
    # 绘制特征重要性图
    feature_names = get_feature_names(heart_preprocessor)
    plot_feature_importance(heart_boost, feature_names, '心脏病', output_dir)
    # ===================================================

    # 训练肝硬化模型
    cirrhosis_lstm = train_and_evaluate_lstm(
        cirrhosis_features, cirrhosis_labels,
        input_size=cirrhosis_features.shape[1],
        hidden_size=hidden_size,
        num_layers=num_layers,
        output_size=1,
        epochs=epochs,
        batch_size=batch_size,
        learning_rate=learning_rate,
        disease_name="肝硬化",output_dir=output_dir)
    
    cirrhosis_boost = boost_prediction(
        cirrhosis_features, cirrhosis_labels, cirrhosis_lstm, "肝硬化",output_dir)
    
    # ============== 新增：肝硬化模型可视化 ==============
    # 划分测试集
    X_train_cirrhosis, X_test_cirrhosis, Y_train_cirrhosis, Y_test_cirrhosis = train_test_split(
        cirrhosis_features, cirrhosis_labels, test_size=0.2, random_state=42
    )
    
    # 获取预测概率
    cirrhosis_pred_proba = get_prediction_probabilities(cirrhosis_lstm, X_test_cirrhosis, device)
    
    # 绘制可视化图表
    plot_prediction_distribution(Y_test_cirrhosis, cirrhosis_pred_proba, '肝硬化', output_dir)
    plot_roc_curve(Y_test_cirrhosis, cirrhosis_pred_proba, '肝硬化', output_dir)
    plot_confusion_matrix(Y_test_cirrhosis, (cirrhosis_pred_proba > 0.5).astype(int), '肝硬化', output_dir)
    
    # 计算并存储性能指标
    cirrhosis_lstm_accuracy = accuracy_score(Y_test_cirrhosis, (cirrhosis_pred_proba > 0.5).astype(int))
    cirrhosis_lstm_f1 = f1_score(Y_test_cirrhosis, (cirrhosis_pred_proba > 0.5).astype(int))
    
    
    with torch.no_grad():
        X_test_cirrhosis_tensor = torch.tensor(X_test_cirrhosis, dtype=torch.float32).unsqueeze(1).to(device)
        cirrhosis_lstm_features_test = cirrhosis_lstm(X_test_cirrhosis_tensor).cpu().numpy().flatten()
        cirrhosis_boost_pred = cirrhosis_boost.predict(cirrhosis_lstm_features_test.reshape(-1, 1))

    cirrhosis_boost_accuracy = accuracy_score(Y_test_cirrhosis, (cirrhosis_boost_pred > 0.5).astype(int))
    cirrhosis_boost_f1 = f1_score(Y_test_cirrhosis, (cirrhosis_boost_pred > 0.5).astype(int))

    performance_data['肝硬化'] = {
        'LSTM': {'accuracy': cirrhosis_lstm_accuracy, 'f1': cirrhosis_lstm_f1},
        'LightGBM': {'accuracy': cirrhosis_boost_accuracy, 'f1': cirrhosis_boost_f1}
    }
    
    # 绘制特征重要性图
    feature_names = get_feature_names(cirrhosis_preprocessor)
    plot_feature_importance(cirrhosis_boost, feature_names, '肝硬化', output_dir)
    # ===================================================


    # 训练中风模型
    stroke_features, stroke_labels, stroke_preprocessor = prepare_data_for_training(
        stroke_df, 'stroke', '中风')
    
    # 添加特征维度检查
    print(f"中风特征维度: {stroke_features.shape[1]}")

    
    
    stroke_lstm = train_and_evaluate_lstm(
        stroke_features, stroke_labels,
        input_size=stroke_features.shape[1],
        hidden_size=hidden_size,
        num_layers=num_layers,
        output_size=1,
        epochs=epochs,
        batch_size=batch_size,
        learning_rate=learning_rate,
        disease_name="中风", output_dir=output_dir)
    
    stroke_boost = boost_prediction(
        stroke_features, stroke_labels, stroke_lstm, "中风", output_dir)
    
    # ============== 新增：中风模型可视化 ==============
    # 划分测试集
    X_train_stroke, X_test_stroke, Y_train_stroke, Y_test_stroke = train_test_split(
        stroke_features, stroke_labels, test_size=0.2, random_state=42
    )
    
    # 获取预测概率
    stroke_pred_proba = get_prediction_probabilities(stroke_lstm, X_test_stroke, device)
    
    # 绘制可视化图表
    plot_prediction_distribution(Y_test_stroke, stroke_pred_proba, '中风', output_dir)
    plot_roc_curve(Y_test_stroke, stroke_pred_proba, '中风', output_dir)
    plot_confusion_matrix(Y_test_stroke, (stroke_pred_proba > 0.5).astype(int), '中风', output_dir)
    
    # 计算并存储性能指标
    stroke_lstm_accuracy = accuracy_score(Y_test_stroke, (stroke_pred_proba > 0.5).astype(int))
    stroke_lstm_f1 = f1_score(Y_test_stroke, (stroke_pred_proba > 0.5).astype(int))
    
    # 同样获取LightGBM的性能
    with torch.no_grad():
        X_test_stroke_tensor = torch.tensor(X_test_stroke, dtype=torch.float32).reshape(-1, 1, X_test_stroke.shape[1]).to(device)
        stroke_lstm_features_test = stroke_lstm(X_test_stroke_tensor).cpu().numpy()
        stroke_boost_pred = stroke_boost.predict(stroke_lstm_features_test)

    stroke_boost_accuracy = accuracy_score(Y_test_stroke, (stroke_boost_pred > 0.5).astype(int))
    stroke_boost_f1 = f1_score(Y_test_stroke, (stroke_boost_pred > 0.5).astype(int))
    
    performance_data['中风'] = {
        'LSTM': {'accuracy': stroke_lstm_accuracy, 'f1': stroke_lstm_f1},
        'LightGBM': {'accuracy': stroke_boost_accuracy, 'f1': stroke_boost_f1}
    }
    
    # 绘制特征重要性图 - 使用原始特征
    feature_names = get_feature_names(stroke_preprocessor)
    plot_feature_importance(stroke_boost, feature_names, '中风', output_dir)

    # 保存模型和预处理管道
    models = {
        'stroke': {'lstm': stroke_lstm, 'boost': stroke_boost},
        'heart': {'lstm': heart_lstm, 'boost': heart_boost},
        'cirrhosis': {'lstm': cirrhosis_lstm, 'boost': cirrhosis_boost}
    }
    
    preprocessors = {
        'stroke': stroke_preprocessor,
        'heart': heart_preprocessor,
        'cirrhosis': cirrhosis_preprocessor
    }

    # ============== 新增：模型性能对比图 ==============
    plot_model_performance(performance_data, output_dir)
    # ===================================================
    
    print("\n" + "="*50)
    print("开始时间序列预测")
    print("="*50)
    
    # 为每个疾病进行时间序列预测
    for disease, file_path in zip(['stroke', 'heart', 'cirrhosis'], [stroke_path, heart_path, cirrhosis_path]):
        try:
            print(f"\n处理疾病: {disease}")
            
            # 加载数据
            data = pd.read_csv(file_path)
            
            # 假设数据包含日期列 'date' 和目标列
            if 'date' in data.columns:
                data = data.set_index('date')
                data.index = pd.to_datetime(data.index)
                
                # 处理目标列
                target_col = data.columns[-1]
                target_data = data[[target_col]].dropna()
                
                if len(target_data) > 10:  # 确保有足够数据
                    # SARIMA预测
                    sarima_pred = sarima_forecast(target_data)
                    
                    # BP神经网络预测
                    norm_data, scaler = MinMaxScaler().fit_transform(target_data.values.reshape(-1, 1))
                    X, Y = prepare_training_data(norm_data)
                    
                    if X.size > 0:
                        # 训练BP神经网络
                        bp_model = BPNet(X.shape[1])
                        criterion = nn.MSELoss()
                        optimizer = torch.optim.Adam(bp_model.parameters(), lr=0.01)
                        
                        for epoch in range(50):
                            inputs = torch.tensor(X, dtype=torch.float32)
                            targets = torch.tensor(Y, dtype=torch.float32).view(-1, 1)
                            
                            outputs = bp_model(inputs)
                            loss = criterion(outputs, targets)
                            
                            optimizer.zero_grad()
                            loss.backward()
                            optimizer.step()
                        
                        # 预测
                        if sarima_pred is not None and len(sarima_pred) > 0:
                            sarima_norm = scaler.transform(sarima_pred.values.reshape(-1, 1))
                            
                            if sarima_norm.shape[0] >= X.shape[1]:
                                X_pred = []
                                for i in range(len(sarima_norm) - X.shape[1] + 1):
                                    X_pred.append(sarima_norm[i:i + X.shape[1]].flatten())
                                
                                if len(X_pred) > 0:
                                    X_pred_tensor = torch.tensor(X_pred, dtype=torch.float32)
                                    bp_pred = bp_model(X_pred_tensor).detach().numpy()
                                    bp_pred = scaler.inverse_transform(bp_pred)
                                    
                                    # 可视化结果
                                    visualize_results(target_data, sarima_pred, bp_pred, 
                                                     title=f'{disease} 患病率预测',output_dir=output_dir)
                                    continue
                    
                    # 如果没有BP预测，只显示SARIMA
                    visualize_results(target_data, sarima_pred, None, 
                                     title=f'{disease} 患病率预测',output_dir=output_dir)
                else:
                    print(f"没有足够的时间序列数据用于{disease}")
            else:
                print(f"{disease}数据中没有日期列 'date'，跳过时间序列预测")
        except Exception as e:
            print(f"{disease}时间序列预测出错: {str(e)}")
    
        
    def predict_comorbidity_risk(patient_data, models, preprocessors, device, comorbidity_coefficients):
        """
        预测患者的共病风险
        """
        # 初始化结果字典
        results = {
            'single_disease': {},
            'comorbidity': {}
        }
        
        # 对每个疾病进行预测
        for disease in ['stroke', 'heart', 'cirrhosis']:
            # 获取对应的预处理器
            preprocessor = preprocessors[disease]
            
            # 预处理患者数据（预处理器会处理特征选择和缺失值）
            processed_data = preprocessor.transform(patient_data)
            
            # 转换为张量并移动到设备
            data_tensor = torch.tensor(processed_data, dtype=torch.float32).unsqueeze(1).to(device)
            
            # 使用LSTM模型预测概率
            with torch.no_grad():
                lstm_output = models[disease]['lstm'](data_tensor)
                prob = torch.sigmoid(lstm_output).item()
            
            # 存储单病概率
            results['single_disease'][disease] = prob
        
        # 使用传入的关联系数计算共病风险
        results['comorbidity']['stroke_heart'] = (
            results['single_disease']['stroke'] * 
            results['single_disease']['heart'] * 
            comorbidity_coefficients['stroke_heart']
        )
        
        results['comorbidity']['stroke_cirrhosis'] = (
            results['single_disease']['stroke'] * 
            results['single_disease']['cirrhosis'] * 
            comorbidity_coefficients['stroke_cirrhosis']
        )
        
        results['comorbidity']['heart_cirrhosis'] = (
            results['single_disease']['heart'] * 
            results['single_disease']['cirrhosis'] * 
            comorbidity_coefficients['heart_cirrhosis']
        )
        
        # 计算三病共病概率
        results['comorbidity']['all'] = (
            results['single_disease']['stroke'] * 
            results['single_disease']['heart'] * 
            results['single_disease']['cirrhosis'] * 
            comorbidity_coefficients['all']
        )
        
        return results


    print("\n" + "="*50)
    print("共病预测框架")
    print("="*50)

    # 计算关联系数（如果数据集有共同ID）
    try:
        comorbidity_coefficients = calculate_comorbidity_coefficients({
            'stroke': stroke_df,
            'heart': heart_df,
            'cirrhosis': cirrhosis_df
        })
        print("从数据中计算的关联系数:")
        print(comorbidity_coefficients)
    except Exception as e:
        print(f"无法从数据中计算关联系数: {str(e)}，使用默认值")
        comorbidity_coefficients = {
            'stroke_heart': 1.2,
            'stroke_cirrhosis': 1.1,
            'heart_cirrhosis': 1.3,
            'all': 1.5
        }

    # 创建示例患者数据（包含所有特征）
    try:
        sample_patient = create_sample_patient({
            'stroke': stroke_df,
            'heart': heart_df,
            'cirrhosis': cirrhosis_df
        })
        print("\n创建的样本患者数据:")
        print(sample_patient)
    except Exception as e:
        print(f"创建样本患者数据失败: {str(e)}")
        return

    # 预测共病风险
    try:
        comorbidity_results = predict_comorbidity_risk(
            sample_patient, 
            models, 
            preprocessors, 
            device,
            comorbidity_coefficients
        )
        
        # 打印结果
        print("\n患者共病风险评估结果:")
        print(f"中风风险: {comorbidity_results['single_disease']['stroke']:.4f}")
        print(f"心脏病风险: {comorbidity_results['single_disease']['heart']:.4f}")
        print(f"肝硬化风险: {comorbidity_results['single_disease']['cirrhosis']:.4f}")
        print(f"中风+心脏病风险: {comorbidity_results['comorbidity']['stroke_heart']:.4f}")
        print(f"中风+肝硬化风险: {comorbidity_results['comorbidity']['stroke_cirrhosis']:.4f}")
        print(f"心脏病+肝硬化风险: {comorbidity_results['comorbidity']['heart_cirrhosis']:.4f}")
        print(f"三种疾病共病风险: {comorbidity_results['comorbidity']['all']:.4f}")
        
        # 可视化结果
        visualize_comorbidity_risk(comorbidity_results, output_dir)
    except Exception as e:
        print(f"共病风险评估失败: {str(e)}")

    print("\n模型训练与评估完成!")

    
if __name__ == '__main__':
    main()