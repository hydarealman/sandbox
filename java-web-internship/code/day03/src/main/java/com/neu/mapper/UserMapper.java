package com.neu.mapper;

import com.neu.domain.User;
import com.neu.vo.UserVO;
import org.apache.ibatis.annotations.Mapper;

import java.util.List;

/**
 * 用户 Mapper 接口
 *
 * 代理 CRUD 约定:
 *   1. 接口全限定名 = 映射文件的 namespace
 *   2. 方法名 = 映射文件中对应 SQL 的 id
 *   3. 方法参数类型 ↔ parameterType
 *   4. 方法返回类型 ↔ resultType
 *
 * Spring Boot 中使用 @Mapper 注解让 MyBatis 扫描注册
 */
@Mapper
public interface UserMapper {

    /** 查询所有用户 */
    List<UserVO> findAll();

    /** 按 id 查询 */
    UserVO findById(int id);

    /** 新增用户 */
    int add(User user);

    /** 更新用户地址 */
    int updateById(User user);

    /** 按 id 删除 */
    int deleteById(int id);
}
