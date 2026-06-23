package com.neu._02proxyCRUD;

import com.neu.domain.User;
import com.neu.mapper.UserMapper;
import com.neu.utils.SqlSessionUtil;
import com.neu.vo.UserVO;
import org.apache.ibatis.session.SqlSession;

import java.util.List;

/**
 * Day02 - 基于代理方式的 CRUD 演示
 *
 * 代理 CRUD 核心:
 *   session.getMapper(Mapper.class) → 返回 JDK 动态代理对象
 *   MyBatis 底层根据接口 + XML 映射自动生成代理实现
 *
 * 好处: 避免 sqlId 写错、参数类型不匹配、返回类型不匹配等问题
 *
 * 约定 (五统一):
 *   1. 接口全限定名 = XML 的 namespace
 *   2. 方法名 = XML 的 id
 *   3. 参数类型 = parameterType
 *   4. 返回类型 = resultType
 */
public class CURDTest {

    public static void main(String[] args) {
        // ========== 依次演示 CRUD ==========
        findAll();

        // 取消注释来运行其他方法:
        // findById(1);
        // addUser();
        // updateById();
        // deleteById();
    }

    /**
     * 查询所有 —— 代理方式
     *
     * 对比传统方式:
     *   传统: session.selectList("com.neu.mapper.UserMapper.findAll")
     *   代理: userMapper.findAll()
     */
    private static void findAll() {
        SqlSession session = SqlSessionUtil.openSession();

        // getMapper() 返回 JDK 动态代理对象
        UserMapper userMapper = session.getMapper(UserMapper.class);

        // 打印代理类类型，证明它不是真实实现
        System.out.println("代理类: " + userMapper.getClass());

        List<UserVO> result = userMapper.findAll();
        System.out.println("========== findAll 查询所有 ==========");
        for (UserVO vo : result) {
            System.out.println(vo);
        }

        session.close();
    }

    /**
     * 按 id 查询
     * 注意: 8大基本数据类型没有属性，SQL 中 #{xxx} 参数名可随便写
     */
    private static void findById(int id) {
        SqlSession session = SqlSessionUtil.openSession();
        UserMapper userMapper = session.getMapper(UserMapper.class);

        UserVO result = userMapper.findById(id);
        System.out.println("========== findById(" + id + ") ==========");
        System.out.println(result);

        session.close();
    }

    /**
     * 新增用户 —— 增删改需要 commit()
     */
    private static void addUser() {
        SqlSession session = SqlSessionUtil.openSession();
        UserMapper userMapper = session.getMapper(UserMapper.class);

        User user = new User();
        user.setName("小王");
        user.setAddress("上海");

        int result = userMapper.add(user);
        System.out.println("========== add 新增 ==========");
        System.out.println("影响行数: " + result);

        session.commit();
        session.close();
    }

    /**
     * 更新用户地址
     */
    private static void updateById() {
        SqlSession session = SqlSessionUtil.openSession();
        UserMapper userMapper = session.getMapper(UserMapper.class);

        User user = new User();
        user.setId(3);
        user.setAddress("北京");
        int result = userMapper.updateById(user);

        System.out.println("========== updateById 更新 ==========");
        System.out.println("影响行数: " + result);

        session.commit();
        session.close();
    }

    /**
     * 按 id 删除
     */
    private static void deleteById() {
        SqlSession session = SqlSessionUtil.openSession();
        UserMapper userMapper = session.getMapper(UserMapper.class);

        int result = userMapper.deleteById(3);
        System.out.println("========== deleteById(3) ==========");
        System.out.println("影响行数: " + result);

        session.commit();
        session.close();
    }
}
