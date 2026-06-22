package com.neu._01hello;

import com.neu._01hello.vo.UserVO;
import com.neu.mapper.UserMapper;
import com.neu.util.SqlSessionUtil;
import org.apache.ibatis.session.SqlSession;

import java.util.HashMap;
import java.util.Map;

/**
 * Day01 - @Param 注解与 Map 传参演示
 *
 * 知识点:
 *   1. Mapper 接口方法有多个参数时，MyBatis 默认将参数封装为 map
 *      - 默认 key: arg0, arg1 ... 或 param1, param2 ...
 *   2. 使用 @Param("名字") 注解可以自定义 map 的 key
 *   3. 也可以直接传入 Map<String, String>
 */
public class ParamTest {

    public static void main(String[] args) {
        // ========== 方式1: @Param 注解方式 ==========
        testWithParam();

        // ========== 方式2: Map 传参方式 ==========
        // testWithMap();
    }

    /**
     * 方式1: 使用 @Param 注解指定参数名
     * Mapper 接口: UserVO login(@Param("name") String name, @Param("xx") String password)
     * SQL 中通过 #{name} 和 #{xx} 引用
     */
    public static void testWithParam() {
        SqlSession sqlSession = SqlSessionUtil.openSession();
        UserMapper userMapper = sqlSession.getMapper(UserMapper.class);

        // @Param("name") → SQL 中 #{name}
        // @Param("xx")   → SQL 中 #{xx}
        UserVO userVO = userMapper.login("zs", "123");

        System.out.println("========== @Param 方式登录 ==========");
        if (userVO == null) {
            System.out.println("登录失败：用户名或密码错误");
        } else {
            System.out.println(userVO);
            System.out.println("登录成功！");
        }
        sqlSession.close();
    }

    /**
     * 方式2: 使用 Map 传参
     * Map 的 key 对应 SQL 中的 #{key}
     */
    public static void testWithMap() {
        SqlSession sqlSession = SqlSessionUtil.openSession();
        UserMapper userMapper = sqlSession.getMapper(UserMapper.class);

        Map<String, String> param = new HashMap<>();
        param.put("name", "zs");
        param.put("xx", "123");

        UserVO userVO = userMapper.login(param);

        System.out.println("========== Map 方式登录 ==========");
        if (userVO == null) {
            System.out.println("登录失败：用户名或密码错误");
        } else {
            System.out.println(userVO);
            System.out.println("登录成功！");
        }
        sqlSession.close();
    }
}
