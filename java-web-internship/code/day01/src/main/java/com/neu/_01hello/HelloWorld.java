package com.neu._01hello;

import com.neu._01hello.vo.UserVO;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;
import java.util.List;

/**
 * Day01 - HelloWorld 入门示例
 *
 * 核心流程:
 *   SqlSessionFactoryBuilder  →  SqlSessionFactory  →  SqlSession
 *   读取 mybatis.xml 配置       创建工厂 (全局唯一)      执行 SQL / 提交 / 关闭
 *
 * 通过 sqlId (namespace + id) 直接调用 SQL:
 *   session.selectList("com.neu._01hello.dao.UserDao.find")
 */
public class HelloWorld {

    public static void main(String[] args) throws IOException {
        // 1. 创建 SqlSessionFactoryBuilder
        SqlSessionFactoryBuilder builder = new SqlSessionFactoryBuilder();

        // 2. 读取 mybatis.xml 配置文件
        InputStream inputStream = Resources.getResourceAsStream("mybatis.xml");

        // 3. 构建 SqlSessionFactory (全局唯一，类比 DataSource)
        SqlSessionFactory sqlSessionFactory = builder.build(inputStream);

        // 4. 获取 SqlSession (类比 JDBC 的 Connection)
        SqlSession session = sqlSessionFactory.openSession();

        // 5. 执行 SQL：参数为 namespace + id
        List<UserVO> result = session.selectList("com.neu._01hello.dao.UserDao.find");

        // 6. 输出结果
        System.out.println("========== HelloWorld 查询结果 ==========");
        for (UserVO userVO : result) {
            System.out.println(userVO);
        }

        // 7. 关闭 session
        session.close();
    }
}
