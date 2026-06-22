package com.neu.mapper;

import com.neu._01hello.vo.UserVO;
import com.neu.domain.User;
import org.apache.ibatis.annotations.Param;

import java.util.List;
import java.util.Map;

/**
 * 用户 Mapper 接口
 * 对应 UserMapper.xml 中的 namespace
 * MyBatis 通过动态代理自动生成实现类
 */
public interface UserMapper {

    /** 查询所有用户 */
    List<UserVO> findAll();

    /** 按 id 查询 */
    UserVO findById(int id);

    /** 新增用户 */
    int add(User user);

    /** 按 id 删除 */
    int deleteById(int userId);

    /** 更新用户 */
    int update(User user);

    /**
     * 登录 —— 使用 @Param 注解指定参数名
     * @param name   用户名，对应 SQL 中的 #{name}
     * @param password 密码，对应 SQL 中的 #{xx}
     */
    UserVO login(@Param("name") String name, @Param("xx") String password);

    /**
     * 登录 —— 使用 Map 传参
     * Map 的 key 对应 SQL 中的 #{key}
     */
    UserVO login(Map<String, String> param);
}
