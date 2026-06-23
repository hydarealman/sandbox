package com.neu._02proxyCRUD;

import com.neu.domain.User;
import com.neu.mapper.UserMapper;
import com.neu.utils.SqlSessionUtil;
import com.neu.vo.UserVO;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;
import java.util.List;

public class CURDTest {


    public static void main(String[] args) throws IOException {

        //findAll();
        //findById(1);


        //addUser();

        //updateById();

        deleteById();

    }

    /**
     * 查询全部的
     */
    private static void findAll(){

        //好比是connection
        SqlSession session = SqlSessionUtil.openSession();

        //代理方式的CURD
        //步骤
        //第一:新建一个接口,接口的全限定名要和映射文件的NameSpace一致
        //第二:定义方法，方法名字要和id一样
        //第三:返回类型、参数都要吻合


        //List<UserVO> result =  session.selectList("com.neu.mapper.UserMapper.findAll");
        //System.out.println(result);

        UserMapper userMapper =  session.getMapper(UserMapper.class);

        System.out.println(userMapper.getClass());

        List<UserVO> result = userMapper.findAll();
        System.out.println(result);

        session.close();

        //8大基本数据类型是没有属性的
    }


    private static void findById(int id){

        SqlSession session = SqlSessionUtil.openSession();

        UserMapper userMapper = session.getMapper(UserMapper.class);

        UserVO result = userMapper.findById(id);
        System.out.println(result);
        session.close();
    }


    private static void addUser(){

        SqlSession session = SqlSessionUtil.openSession();
        UserMapper userMapper = session.getMapper(UserMapper.class);

        User user = new User();
        user.setName("小王");
        user.setAddress("上海");

        int result = userMapper.add(user);
        System.out.println(result);

        session.commit();
        session.close();

    }

    private static void updateById(){
        SqlSession session = SqlSessionUtil.openSession();
        UserMapper userMapper = session.getMapper(UserMapper.class);


        User user = new User();
        user.setId(3);
        user.setAddress("北京");
        int result = userMapper.updateById(user);
        System.out.println(result);


        session.commit();
        session.close();
    }


    private static void deleteById(){
        SqlSession session = SqlSessionUtil.openSession();
        UserMapper userMapper = session.getMapper(UserMapper.class);

        int result = userMapper.deleteById(3);
        System.out.println(result);

        session.commit();
        session.close();
    }
}
