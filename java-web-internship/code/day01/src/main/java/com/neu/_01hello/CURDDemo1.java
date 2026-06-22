package com.neu._01hello;

import com.neu._01hello.vo.UserVO;
import com.neu.domain.User;
import com.neu.mapper.UserMapper;
import com.neu.util.SqlSessionUtil;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.defaults.DefaultSqlSession;

import java.util.List;

/**
 * Day01 - CRUD 综合演示
 *
 * 核心概念:
 *   1. 使用 SqlSessionUtil 工具类获取 SqlSession
 *   2. 通过 sqlSession.getMapper(Mapper.class) 获取 Mapper 代理对象
 *   3. MyBatis 底层使用 JDK 动态代理，根据接口 + XML 生成实现
 *
 * 运行方式: 取消 main() 中对应方法的注释即可
 */
public class CURDDemo1 {

    public static void main(String[] args) {
        // ========== 依次演示 CRUD 操作 ==========
        findAll();

        // 取消下面的注释来运行其他方法：
        // findById();
        // add();
        // deleteById();
        // update();
    }

    /**
     * 查询所有 —— 两种方式:
     *   方式1: session.selectList("namespace.id")  —— 直接使用 sqlId
     *   方式2: mapper.findAll()                      —— 通过 Mapper 接口代理 (推荐)
     */
    public static void findAll() {
        SqlSession sqlSession = SqlSessionUtil.openSession();

        // 方式1: 传统 sqlId 方式
        // List<UserVO> userVOList = sqlSession.selectList("com.neu.mapper.UserMapper.findAll");

        // 方式2: Mapper 接口代理方式 (推荐)
        UserMapper userMapper = sqlSession.getMapper(UserMapper.class);
        System.out.println("Mapper 代理类: " + userMapper.getClass());

        List<UserVO> userVOList = userMapper.findAll();
        System.out.println("========== findAll 查询所有 ==========");
        for (UserVO userVO : userVOList) {
            System.out.println(userVO);
        }
        sqlSession.close();
    }

    /**
     * 按 id 查询
     */
    public static void findById() {
        DefaultSqlSession sqlSession = (DefaultSqlSession) SqlSessionUtil.openSession();
        UserMapper userMapper = sqlSession.getMapper(UserMapper.class);
        UserVO userVO = userMapper.findById(1);
        System.out.println("========== findById(1) ==========");
        System.out.println(userVO);
        sqlSession.close();
    }

    /**
     * 新增用户 —— 注意: 增删改需要手动 commit()
     */
    public static void add() {
        SqlSession sqlSession = SqlSessionUtil.openSession();

        User user = new User();
        user.setName("新用户");
        user.setMoney(100);
        user.setPassword("123456");

        UserMapper userMapper = sqlSession.getMapper(UserMapper.class);
        int count = userMapper.add(user);
        System.out.println("========== add 新增 ==========");
        System.out.println("影响行数: " + count);

        // 增删改必须 commit!
        sqlSession.commit();
        sqlSession.close();
    }

    /**
     * 按 id 删除
     */
    public static void deleteById() {
        DefaultSqlSession sqlSession = (DefaultSqlSession) SqlSessionUtil.openSession();
        UserMapper userMapper = sqlSession.getMapper(UserMapper.class);
        int count = userMapper.deleteById(1);
        System.out.println("========== deleteById(1) ==========");
        System.out.println("影响行数: " + count);

        sqlSession.commit();
        sqlSession.close();
    }

    /**
     * 更新用户 —— 先查再改
     */
    public static void update() {
        SqlSession sqlSession = SqlSessionUtil.openSession();
        UserMapper userMapper = sqlSession.getMapper(UserMapper.class);

        // 先查出要修改的记录
        UserVO userVO = userMapper.findById(1);

        // 构造要更新的数据
        User user = new User();
        user.setId(userVO.getId());
        user.setPassword("123456");
        user.setName("zhangsan");
        user.setMoney(userVO.getMoney() + 100);

        int count = userMapper.update(user);
        System.out.println("========== update 更新 ==========");
        System.out.println("影响行数: " + count);

        sqlSession.commit();
        sqlSession.close();
    }
}
