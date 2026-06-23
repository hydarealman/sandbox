# Java Web 实习 — MyBatis 持久层框架

Java Web 课程实习，学习 MyBatis 框架的核心用法：ORM 映射、CRUD 操作、动态代理、类型别名、参数传递。

---

## 📁 目录结构

```
java-web-internship/
├── file/                           # 课程资料（PDF、笔记、视频、参考代码）
│   ├── Day01.pdf                   # Day01 课件 PDF
│   ├── Day01/                      # Day01 补充资料
│   └── Day02/                      # Day02 资料
│       ├── 笔记/Day02.md           # Day02 完整笔记
│       ├── 代码/day02/             # Day02 参考代码
│       └── 视频/                   # 教学视频（avi）
│
└── code/                           # 手写练习代码
    ├── day01/                      # Day01：MyBatis 入门 + CRUD + @Param
    └── day02/                      # Day02：别名配置 + 代理方式 CRUD
```

---

## 🛠️ 环境要求

| 工具 | 版本 | 说明 |
|------|------|------|
| JDK | 25+ | OpenJDK Temurin-25.0.2 |
| MySQL | 8.0+ | 本地数据库，root 用户 |
| Maven | 3.9.9 | 构建工具，已安装至 `C:\tools\apache-maven-3.9.9\` |

### Maven 安装位置

Maven 已配置到 Windows 用户 PATH 中。**重启 PowerShell** 后直接使用 `mvn` 命令：

```powershell
mvn --version   # 验证安装
```

---

## 🗄️ 数据库准备

实习使用两个数据库表：

### Day01 用表 — `t_user`

```sql
CREATE DATABASE IF NOT EXISTS mybatis DEFAULT CHARSET utf8mb4;
USE mybatis;

CREATE TABLE `t_user` (
    `id`       INT NOT NULL AUTO_INCREMENT,
    `name`     VARCHAR(255) NOT NULL,
    `password` CHAR(32) NOT NULL,
    `money`    INT NOT NULL,
    PRIMARY KEY (`id`),
    UNIQUE INDEX `name`(`name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

INSERT INTO `t_user` VALUES (1, 'zs', '111', 100);
INSERT INTO `t_user` VALUES (2, 'zl', '123456', 100);
```

### Day02 用表 — `user`

```sql
USE mybatis;

CREATE TABLE `user` (
    `id`      BIGINT NOT NULL AUTO_INCREMENT,
    `name`    VARCHAR(40) NOT NULL,
    `address` VARCHAR(100) DEFAULT NULL,
    PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

INSERT INTO `user` VALUES (1, 'zs', '广西桂林');
INSERT INTO `user` VALUES (2, 'lisi', '广西南宁');
```

> 数据库密码默认配置为 `123456`，如果不同，请修改对应 `day0X/src/main/resources/mybatis.xml`（Day01 还需修改 `db.properties`）。

---

## 📚 Day01 — MyBatis 入门 + CRUD + @Param

**知识点：** ORM 概念 → SqlSessionFactory 生命周期 → 代理 Mapper → 增删改查 → @Param 传参 → 动态代理原理

### 项目结构

```
day01/
├── pom.xml
└── src/main/
    ├── java/com/neu/
    │   ├── _01hello/
    │   │   ├── HelloWorld.java        # 入门：SqlSession 直接执行 SQL
    │   │   ├── CURDDemo1.java         # 综合 CRUD 演示
    │   │   ├── ParamTest.java         # @Param 注解 + Map 传参
    │   │   ├── ProxyTest.java         # 手写动态代理模拟 MyBatis 底层
    │   │   ├── vo/UserVO.java         # 值对象 (id, name, money)
    │   │   └── dao/UserDao.java       # DAO 标记接口
    │   ├── mapper/UserMapper.java     # Mapper 接口（CRUD + login）
    │   ├── domain/User.java           # 领域对象 (id, name, password, money)
    │   └── util/SqlSessionUtil.java   # SqlSession 工具类
    └── resources/
        ├── mybatis.xml                # 主配置（properties + typeAliases + environments）
        ├── db.properties              # 数据库连接参数
        ├── HelloWorldMapper.xml       # HelloWorld SQL 映射
        └── UserMapper.xml             # CRUD SQL 映射
```

### 运行命令

```powershell
cd java-web-internship\code\day01

# 1. 入门示例 — SqlSession 直接查询
mvn exec:java "-Dexec.mainClass=com.neu._01hello.HelloWorld"

# 2. CRUD 综合演示 — Mapper 代理方式
mvn exec:java "-Dexec.mainClass=com.neu._01hello.CURDDemo1"

# 3. @Param 注解传参 — 多参数登录
mvn exec:java "-Dexec.mainClass=com.neu._01hello.ParamTest"

# 4. 动态代理原理 — 手写 Proxy 模拟 MyBatis 底层
mvn exec:java "-Dexec.mainClass=com.neu._01hello.ProxyTest"
```

### 程序对照表

| 程序 | 运行结果 | 学习重点 |
|------|----------|----------|
| HelloWorld | 查询到 zs、zl (money=100) | SqlSessionFactoryBuilder → SqlSessionFactory → SqlSession 流程 |
| CURDDemo1 | 查询所有 + 显示代理类类型 `$ProxyXX` | `getMapper()` 拿到的是 JDK 动态代理对象 |
| ParamTest | 登录失败（密码不匹配） | `@Param("名字")` 自定义 SQL 参数名 |
| ProxyTest | `sqlId = com.neu.mapper.UserMapper.findById` | namespace + "." + id = sqlId |

---

## 📚 Day02 — 别名配置 + 代理方式 CRUD

**知识点：** typeAliases 类型别名 → 代理 CRUD 约定（五统一） → 三种指定映射文件方式

### 项目结构

```
day02/
├── pom.xml
└── src/main/
    ├── java/com/neu/
    │   ├── domain/User.java              # 领域对象 (id, name, address)
    │   ├── vo/UserVO.java                # 值对象 → 别名 userVO
    │   ├── mapper/UserMapper.java        # Mapper 接口（5 个 CRUD 方法）
    │   ├── utils/SqlSessionUtil.java     # SqlSession 工具类
    │   ├── _01typeAliase/TypeAliase.java # 别名演示
    │   └── _02proxyCRUD/CURDTest.java    # ★ 代理 CRUD 演示（核心）
    └── resources/
        ├── mybatis.xml                   # 主配置（typeAliases 包扫描）
        └── UserMapper.xml                # SQL 映射（别名写法）
```

### 运行命令

```powershell
cd java-web-internship\code\day02

# 1. 别名演示 — typeAliases 包扫描 + 传统方式查询
mvn exec:java "-Dexec.mainClass=com.neu._01typeAliase.TypeAliase"

# 2. 代理 CRUD 演示 ★核心 — session.getMapper()
mvn exec:java "-Dexec.mainClass=com.neu._02proxyCRUD.CURDTest"
```

### 程序对照表

| 程序 | 运行结果 | 学习重点 |
|------|----------|----------|
| TypeAliase | 查到 zs(广西桂林)、lisi(广西南宁) | `<package name="com.neu.vo"/>` 自动生成别名 `userVO` |
| CURDTest | 查到 2 条记录 | `session.getMapper(UserMapper.class)` 代理方式 CRUD |

---

## 🔑 Day01 vs Day02 核心对比

| 维度 | Day01 | Day02 |
|------|-------|-------|
| 数据库表 | `t_user` (id, name, password, money) | `user` (id, name, address) |
| 包结构 | `com.neu._01hello` | `com.neu.vo / com.neu.domain / com.neu.mapper` |
| SQL 调用方式 | `session.selectList("namespace.id")` | `session.getMapper(Xxx.class)` |
| 类型别名 | 全限定名 `com.neu._01hello.vo.UserVO` | 别名 `userVO`（包扫描自动生成） |
| 参数获取 | `#{}` | `#{}`（8大基本类型参数名可随意写） |
| MyBatis 版本 | 3.5.16 | 3.5.16 |

---

## 🔧 三种指定映射文件方式

```xml
<!-- 方式1：指定 XML 路径（通用） -->
<mappers>
    <mapper resource="UserMapper.xml"/>
</mappers>

<!-- 方式2：指定 Mapper 接口（代理专用，XML 须与接口同目录结构） -->
<mappers>
    <mapper class="com.neu.mapper.UserMapper"/>
</mappers>

<!-- 方式3：批量扫描包（代理专用，方式2的简写） -->
<mappers>
    <package name="com.neu.mapper"/>
</mappers>
```

---

## 📋 代理 CRUD 五大约定

| # | 约定 | 说明 |
|---|------|------|
| 1 | 接口全限定名 = namespace | `com.neu.mapper.UserMapper` |
| 2 | 方法名 = id | `findAll()` ↔ `<select id="findAll">` |
| 3 | 参数类型 = parameterType | `User user` ↔ `parameterType="user"` |
| 4 | 返回类型 = resultType | `List<UserVO>` ↔ `resultType="userVO"` |
| 5 | 方法名需要和映射文件id一样 | MyBatis 通过接口名+方法名拼出 sqlId |

---

## ⚠️ 常见问题

**Q: `mvn` 命令找不到？**
```powershell
# 临时生效（当前窗口）
$env:PATH = "C:\tools\apache-maven-3.9.9\bin;" + $env:PATH

# 永久生效：重启 PowerShell（已配置用户级 PATH）
```

**Q: 数据库连接失败？**
检查 `mybatis.xml` 或 `db.properties` 中的 `username` 和 `password` 是否与你的 MySQL 一致。

**Q: 控制台中文乱码？**
正常现象，数据库中的中文字段可以正确存储和查询，只是 PowerShell 渲染问题。

---

> 📅 实习时间：2026-06  
> 🏫 课程：Java Web 实习  
> 🔄 最近更新：2026-06-23
