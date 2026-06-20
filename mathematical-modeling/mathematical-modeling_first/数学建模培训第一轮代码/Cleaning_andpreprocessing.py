import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
# import torch
# import torch.nn as nn
from sklearn.preprocessing import MinMaxScaler, OneHotEncoder
from sklearn.compose import ColumnTransformer
from sklearn.model_selection import train_test_split
import lightgbm as lgb
from sklearn.metrics import accuracy_score, f1_score
import seaborn as sns
from scipy.stats import chi2_contingency # 用于卡方校验

# 设置中文字体
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

# 设置图片清晰度
plt.rcParams['figure.dpi'] = 300

# 使用原始字符串路径
stroke_df = pd.read_csv("C:\\Users\\dong\\Desktop\\stroke.csv")
heart_df = pd.read_csv("C:\\Users\\dong\\Desktop\\heart.csv")
cirrhosis_df = pd.read_csv("C:\\Users\\dong\\Desktop\\cirrhosis.csv")

# 数据预处理函数
def preprocess_data(df):
    # 检查缺失值
    print('缺失值情况: ')
    print(df.isnull().sum())

    # 处理缺失值(这里简单填充为均值或众数: 可根据实际情况调整)
    for col in df.columns:
        if df[col].dtype == 'object':
            df[col].fillna(df[col].mode()[0], inplace=True)
        else:
            df[col].fillna(df[col].mean(), inplace=True)
    
    # 对分类变量进行编码
    for col in df.columns:
        if df[col].dtype == 'object':
            df[col] = pd.Categorical(df[col]).codes

    return df

# 统计分析与可视化
def analyze_and_visualize(df,target_col,title):
    # 数值型变量的基本统计量
    categorical_cols = df.select_dtypes(include=['object']).columns
    numerical_cols = df.select_dtypes(include=[np.number]).columns
    stats = df[numerical_cols].describe()
    print(f'{title} 数值型变量基本统计量')
    print(stats)

    # 调参数值型变量直方图的大小
    fig,axes = plt.subplots(len(numerical_cols), ncols=1, figsize=(10, 4*len(numerical_cols)))
    for i, col in enumerate(numerical_cols):
        sns.histplot(df[col], bins=15, kde=True, ax=axes[i])
        axes[i].set_title(col)
    plt.suptitle(f'{title} 数值型变量分布图', y=1.005)
    plt.tight_layout()
    plt.savefig(f'{title} 数值型变量分布直方图.png')
    plt.show()

    # 绘制分类变量的柱状图,调整大小
    correlations = df.corr()[target_col].drop(target_col)
    print(f'{title} 各因素 {target_col} 的相关性: ')

    # 绘制相关性热力图,调整大小
    plt.figure(figsize=(12,10))
    sns.heatmap(df.corr(), annot=True, cmap='coolwarm', annot_kws={'size':8})
    plt.title(f'{title} 相关性热力图.png')
    plt.tight_layout()
    plt.savefig(f'{title} 相关性热力图.png')
    plt.show()

    # 对分类变量进行卡方校验 (与目标变量的关系)
    for col in categorical_cols:
        contingency_table = pd.crosstab(df[col],df[target_col])
        chi2,p,dof,ex = chi2_contingency(contingency_table)
        print(f'卡方值: {chi2}, p 值: {p}')

# 预处理数据集
stroke_df = preprocess_data(stroke_df)
heart_df = preprocess_data(heart_df)
cirrhosis_df = preprocess_data(cirrhosis_df)

# 分析中风数据集
analyze_and_visualize(stroke_df, target_col='stroke', title='中风数据集')

# 分析心脏病数据集
analyze_and_visualize(heart_df, target_col= 'HeartDisease', title='心脏病数据集')

# 分析肝硬化数据集
analyze_and_visualize(cirrhosis_df, target_col= 'Stage', title='肝硬化数据集')
