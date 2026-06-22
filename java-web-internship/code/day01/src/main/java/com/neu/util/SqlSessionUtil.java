package com.neu.util;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;

/**
 * SqlSession 工具类
 * 使用静态代码块初始化 SqlSessionFactory（全局唯一）
 */
public class SqlSessionUtil {

    private static SqlSessionFactory sqlSessionFactory;

    static {
        SqlSessionFactoryBuilder sqlSessionFactoryBuilder = new SqlSessionFactoryBuilder();
        try {
            sqlSessionFactory = sqlSessionFactoryBuilder.build(
                    Resources.getResourceAsStream("mybatis.xml"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * 获取一个新的 SqlSession（类比 JDBC 的 Connection）
     */
    public static SqlSession openSession() {
        return sqlSessionFactory.openSession();
    }
}
