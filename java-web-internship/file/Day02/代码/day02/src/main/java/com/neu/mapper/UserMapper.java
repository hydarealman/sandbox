package com.neu.mapper;

import com.neu.domain.User;
import com.neu.vo.UserVO;

import java.util.List;

public interface UserMapper {
    List<UserVO> findAll();

    UserVO findById(int id);


    //返回的int代表所影响的记录数
    int add(User user);

    int updateById(User user);

    int deleteById(int id);
}