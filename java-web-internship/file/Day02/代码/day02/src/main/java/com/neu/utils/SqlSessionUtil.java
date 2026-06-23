package com.neu.utils;

import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;

public class SqlSessionUtil {

    private static SqlSessionFactory sqlSessionFactory;

    static {
        //SqlSessionFactoryBuilder-->SqlSessionFactory-->SqlSession
        SqlSessionFactoryBuilder builder = new SqlSessionFactoryBuilder();

        InputStream inputStream = null;
        try {
            inputStream = Resources.getResourceAsStream("mybatis.xml");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        sqlSessionFactory = builder.build(inputStream);
    }

    public static SqlSession openSession(){
        return sqlSessionFactory.openSession();
    }
}
