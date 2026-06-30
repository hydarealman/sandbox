         package com.neu._03springboot.service.impl;

import com.neu.domain.User;
import com.neu.mapper.UserMapper;
import com.neu.vo.UserVO;
import com.neu._03springboot.service.UserService;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * 用户业务层实现
 *
 * @Service: 将当前类标记为 Spring 管理的 Service 组件
 *           底层通过构造器注入 UserMapper（Spring 自动装配）
 */
@Service
public class UserServiceImpl implements UserService {

    private final UserMapper userMapper;

    /**
     * 构造器注入（Spring 推荐的方式）
     * 相比 @Autowired 字段注入，更利于测试和不可变性
     */
    public UserServiceImpl(UserMapper userMapper) {
        this.userMapper = userMapper;
    }

    @Override
    public List<UserVO> findAll() {
        return userMapper.findAll();
    }

    @Override
    public UserVO findById(int id) {
        return userMapper.findById(id);
    }

    @Override
    public int add(User user) {
        return userMapper.add(user);
    }

    @Override
    public int deleteById(int id) {
        return userMapper.deleteById(id);
    }
}
