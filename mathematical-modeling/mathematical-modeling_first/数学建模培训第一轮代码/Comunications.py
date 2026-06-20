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

# 设置图片清晰度
plt.rcParams['figure.dpi'] = 300
# 设置中文字体
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

def load_and_preprocess_data(stroke_path, heart_path, cirrhosis_path):
    # 加载数据
    stroke_df = pd.read_csv(stroke_path)
    heart_df = pd.read_csv(heart_path)
    cirrhosis_df = pd.read_csv(cirrhosis_path)


    # 数据探索 - 打印各数据集样本量
    print(f"中风数据样本量: {len(stroke_df)}")
    print(f"心脏病数据集样本量: {len(heart_df)}")
    print(f"肝硬化数据集样本量: {len(cirrhosis_df)}")

    #提取特征和标签
    def prepare_data(df, target_col, disease_name):
        print(f"\n处理{disease_name}数据集...")
        label = df[target_col].values

        # 如果是肝硬化数据集,二值化处理
        if disease_name == "肝硬化":
            label = (label > 2).astype(int)

        features = df.drop(target_col, axis=1)

        # 识别类别型列和数值型列
        categorical_cols = features.select_dtypes(include={'object'}).columns
        numerical_cols = features.select_dtypes(exclude={'object'}).columns

        print(f"  类别型特征: {list(categorical_cols)}")
        print(f"  数值型特征: {list(numerical_cols)}")

        # 创建预处理管道
        preprocessor = ColumnTransformer(
            transformers=[
                ('num', MinMaxScaler() ,numerical_cols),
                ('cat', OneHotEncoder(handle_unknown='ignore'), categorical_cols)
            ])
        
        # 转换特征
        processed_features = preprocessor.fit_transform(features)
        print(f"  处理后特征维度: {processed_features.shape}")

        return processed_features, label, preprocessor
    
    #分别处理三个数据集
    stroke_features, stroke_labels, stroke_preprocessor = prepare_data(
        stroke_df, target_col='stroke', disease_name='中风')

    heart_features, heart_labels, heart_preprocessor = prepare_data(
        heart_df, target_col='HeartDisease', disease_name='心脏病')

    cirrhosis_features, cirrhosis_labels, cirrhosis_preprocessor = prepare_data(
        cirrhosis_df, target_col='Stage', disease_name='肝硬化')

    #保存预处理管道,用于后续预测
    preprocessors = {
        'stroke': stroke_preprocessor,
        'heart' : heart_preprocessor,
        'cirrhosis': cirrhosis_preprocessor
    }

    return (stroke_features, stroke_labels,
            heart_features, heart_labels,
            cirrhosis_features,cirrhosis_labels,
            preprocessors)
    
class LSTMModel(nn.Module): 
    def __init__(self, input_size, hidden_size, num_layers, output_size):
        super(LSTMModel,self).__init__()
        self.hidden_size = hidden_size
        self.num_layers = num_layers
        self.lstm = nn.LSTM(input_size, hidden_size, num_layers, batch_first=True)
        self.fc = nn.Linear(hidden_size, output_size)
    
    def forward(self, x):
        h0 = torch.zeros(self.num_layers, x.size(0), self.hidden_size)
        c0 = torch.zeros(self.num_layers, x.size(0), self.hidden_size)

        out, _ = self.lstm(x, (h0,c0))
        out = self.fc(out[:,-1,:])
        return out
    

def train_and_evalute_lstm(X, Y, input_size, hidden_size, num_layers, output_size, epochs, batch_size,learning_rate, disease_name):
    print(f"\n训练{disease_name}LSTM模型...")
    # 转换数据为张量,并确保标签维度与输出一致
    X = torch.tensor(X, dtype=torch.float32).unsqueeze(1) # 添加序列维度
    Y = torch.tensor(Y, dtype=torch.float32).unsqueeze(1) # 将标签转换为[batch_size, 1]维度

    X_train, X_test, Y_train, Y_test = train_test_split(X, Y,test_size=0.2, random_state=42)

    model = LSTMModel(input_size, hidden_size, num_layers, output_size)
    criterion = nn.BCEWithLogitsLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)

    train_losses = []
    for epoch in range(epochs):
        model.train()
        epoch_loss = 0
        for i in range(0, len(X_train),batch_size):
            batch_X = X_train[i:i + batch_size]
            batch_Y = Y_train[i:i + batch_size]
            

            outputs = model(batch_X)
            loss = criterion(outputs, batch_Y) # 现在Outputs和batch_Y维度都是[batch_size, 1]

            optimizer.zero_grad()
            loss.backward()
            optimizer.step()

            epoch_loss += loss.item()  * batch_X.size(0)

    epoch_loss /= len(X_train)
    train_losses.append(epoch_loss)
    if (epoch + 1) % 10 == 0:
        print(f"Epoch [{epoch + 1}/{epochs}], Loss: {epoch_loss:.4f}")

    model.eval()
    with torch.no_grad():
        test_outputs = model(X_test)
        predicted = (torch.sigmoid(test_outputs) > 0.5).float()

        # 评估师将标签和预测结果展平为一维
        Y_test_np = Y_test.numpy().flatten()
        predicted_np = predicted.numpy().flatten()

        accuracy = accuracy_score(Y_test_np, predicted_np)
        f1 = f1_score(Y_test_np, predicted_np)
        f1 = f1_score(Y_test_np, predicted_np, average='weighted')
        print(f'{disease_name}模型 Test Accuracy: {accuracy:.4f}, F1 Score: {f1:.4f}')

    plt.plot(range(1, epochs + 1), train_losses)
    plt.xlabel('Epoch')
    plt.ylabel('Training Loss')
    plt.title(f'{disease_name}LSTM Training Loss')
    plt.show()

    return model 

def boost_prediction(X,Y, lstm_model,disease_name):
    print(f"\n训练{disease_name}LightGBM模型...")
    lstm_model.eval()
    with torch.no_grad():
        lstm_input = torch.tensor(X, dtype=torch.float32).unsqueeze(1)
        lstm_features = lstm_model(lstm_input).numpy().flatten()    # 展平为一维特征

    # 确保标签是一维的
    Y = Y.flatten()

    X_train,X_test,Y_train,Y_test = train_test_split(lstm_features.reshape(-1,1),Y)

    # 单标签二分类设置
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

    lgb_train = lgb.Dataset(X_train,Y_train)
    lgb_test = lgb.Dataset(X_test,Y_test, reference=lgb_train)

    num_round = 100
    bst = lgb.train(params, lgb_train, num_round, valid_sets=[lgb_test], early_stopping_rounds=10)
    
    Y_pred_proba = bst.predict(X_test)
    Y_pred = (Y_pred_proba > 0.5).astype(int)

    accuracy = accuracy_score(Y_test, Y_pred)
    f1 = f1_score(Y_test, Y_pred, average='weighted')
    print(f'{disease_name}LightGBM Test Accuracy: {accuracy:.4f}, F1 Score: {f1:.4f}')

    return bst


hidden_size = 64
num_layers = 2
batch_size = 32
epochs = 50
learning_rate = 0.001

def main():
    stroke_path = "C:\\Users\\dong\\Desktop\\stroke.csv"
    heart_path = "C:\\Users\\dong\\Desktop\\heart.csv"
    cirrhosis_path = "C:\\Users\\dong\\Desktop\\cirrhosis.csv"

    # 加载和预处理数据
    (stroke_features, stroke_labels, heart_features, heart_labels, cirrhosis_features, cirrhosis_labels,  # 添加这行
     preprocessors) = load_and_preprocess_data(stroke_path,heart_path, cirrhosis_path)

    #训练单个疾病预测模型
    print("\n=== 训练单个疾病预测模型 ===")

    # 中风模型
    stroke_lstm_model = train_and_evalute_lstm(
        stroke_features, stroke_labels,
        input_size= stroke_features.shape[1],
        hidden_size=hidden_size,
        num_layers= num_layers,
        output_size=1,
        epochs=epochs,
        batch_size = batch_size,
        learning_rate= learning_rate,
        disease_name= "中风"
    )

    stroke_boost_model = boost_prediction(
        stroke_features, stroke_labels,
        stroke_lstm_model,
        disease_name="中风"
    )

    # 心脏病模型
    heart_lstm_model = train_and_evalute_lstm(
        stroke_features, stroke_labels,
        input_size=stroke_features.shape[1],
        hidden_size=hidden_size,
        num_layers=num_layers,
        output_size=1,
        epochs=epochs,
        batch_size=batch_size,
        learning_rate=learning_rate,
        disease_name="中风"
    )

    #心脏病模型
    heart_lstm_model = train_and_evalute_lstm(
        heart_features, heart_labels,
        input_size=heart_features.shape[1],
        hidden_size=hidden_size,
        num_layers=num_layers,
        output_size=1,
        epochs=epochs,
        batch_size=batch_size,
        learning_rate=learning_rate,
        disease_name="心脏病"
    )

    heart_boost_model = train_and_evalute_lstm(
        heart_features, heart_labels,
        heart_lstm_model,
        disease_name="心脏病"
    )

    # 肝硬化模型
    cirrhosis_lstm_model = train_and_evalute_lstm(
        cirrhosis_features, cirrhosis_labels,
        input_size=cirrhosis_features.shape[1],
        hidden_size=hidden_size,
        num_layers=num_layers,
        output_size=1,
        epochs=epochs,
        batch_size=batch_size,
        learning_rate=learning_rate,
        disease_name="肝硬化"
    )

    cirrhosis_boost_model = boost_prediction(
        cirrhosis_features, cirrhosis_labels,
        cirrhosis_lstm_model,
        disease_name="肝硬化" 
    )

    #保存模型和预处理管道
    models = {
        'stroke': {
            'lstm': stroke_lstm_model,
            'boost': stroke_boost_model
        },
        'heart': {
            'lstm': heart_lstm_model,
            'boost': heart_boost_model,
        },
        'cirrhosis': {
            'lstm': cirrhosis_lstm_model,
            'boost': cirrhosis_boost_model
        }
    }


    # 共病预测模型说明
    print("\n=== 共病预测框架 ===")
    print("1. 对新患者数据,分别使用三个模型预测患每种疾病的概率")
    print("2. 基于单病概率计算共病风险")
    print("  - 两种疾病共病概率 = 单病A概率 * 单病B概率 * 共病关联系数")
    print("  - 三种疾病共病概率 = 三种单病概率的乘积 * 多重共病关联系数")

    # 特征重要性可视化
    lgb.plot_importance(stroke_boost_model, title='中风 LightGBM 特征重要性')
    plt.show()
    lgb.plot_importance(heart_boost_model, title='心脏病 LightGBM 特征重要性')
    plt.show()
    lgb.plot_importance(cirrhosis_boost_model, title='肝硬化 LightGBM 特征重要性')
    plt.show()


if __name__ == '__main__':
    main()