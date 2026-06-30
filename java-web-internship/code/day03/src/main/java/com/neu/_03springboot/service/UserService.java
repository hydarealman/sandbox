package com.neu._03springboot.service;

import com.neu.domain.User;
import com.neu.vo.UserVO;

import java.util.List;

/**
 * 用户业务层接口
 *
 * 封装 Mapper 的 CRUD 操作，供 Controller 调用
 */
public interface UserService {

    /** 查询所有用户 */
    List<UserVO> findAll();

    /** 按 id 查询 */
    UserVO findById(int id);

    /** 新增用户 */
    int add(User user);

    /** 按 id 删除 */
    int deleteById(int id);
}
