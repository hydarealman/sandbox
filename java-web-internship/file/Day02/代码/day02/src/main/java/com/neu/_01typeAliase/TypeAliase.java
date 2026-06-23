package com.neu._01typeAliase;

import com.neu.vo.UserVO;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;
import java.util.List;

public class TypeAliase {


    public static void main(String[] args) throws IOException {
                                    //连接池               //连接
        //SqlSessionFactoryBuilder-->SqlSessionFactory-->SqlSession
        SqlSessionFactoryBuilder builder = new SqlSessionFactoryBuilder();

        InputStream inputStream =  Resources.getResourceAsStream("mybatis.xml");
        SqlSessionFactory sqlSessionFactory = builder.build(inputStream);


        //好比是connection
        SqlSession session = sqlSessionFactory.openSession();


        List<UserVO> result =  session.selectList("com.neu.mapper.UserMapper.findAll");
        System.out.println(result);

        session.close();

    }
}
