package com.neu._03springboot.controller;

import com.neu.domain.User;
import com.neu.vo.UserVO;
import com.neu._03springboot.service.UserService;
import org.springframework.web.bind.annotation.*;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * 用户 REST 控制器
 *
 * @RestController = @Controller + @ResponseBody
 *   所有方法自动返回 JSON（无需手动解析）
 *
 * 接口设计（RESTful 风格）:
 *   GET    /api/users       — 查询全部用户
 *   GET    /api/user/{id}   — 按 id 查询用户
 *   POST   /api/user        — 添加用户
 *   DELETE /api/user/{id}   — 按 id 删除用户
 */
@RestController
@RequestMapping("/api")
public class UserController {

    private final UserService userService;

    /**
     * 构造器注入
     */
    public UserController(UserService userService) {
        this.userService = userService;
    }

    /**
     * 功能1: 查询全部用户
     *
     * 请求方式: GET
     * 接口地址: http://localhost:8080/api/users
     * 返回示例:
     *   {
     *     "success": true,
     *     "data": [
     *       { "id": 1, "name": "zs", "address": "北京" },
     *       { "id": 2, "name": "lisi", "address": "上海" }
     *     ]
     *   }
     */
    @GetMapping("/users")
    public Map<String, Object> findAll() {
        List<UserVO> userList = userService.findAll();

        Map<String, Object> result = new HashMap<>();
        result.put("success", true);
        result.put("data", userList);
        return result;
    }

    /**
     * 功能2: 按 id 查询用户
     *
     * 请求方式: GET
     * 接口地址: http://localhost:8080/api/user/1
     *
     * @PathVariable: 将 URL 中的 {id} 绑定到方法参数
     */
    @GetMapping("/user/{id}")
    public Map<String, Object> findById(@PathVariable int id) {
        UserVO user = userService.findById(id);

        Map<String, Object> result = new HashMap<>();
        if (user != null) {
            result.put("success", true);
            result.put("data", user);
        } else {
            result.put("success", false);
            result.put("message", "未找到 id=" + id + " 的用户");
        }
        return result;
    }

    /**
     * 功能3: 添加用户
     *
     * 请求方式: POST
     * 接口地址: http://localhost:8080/api/user
     * 请求体 (JSON):
     *   {
     *     "name": "小王",
     *     "address": "上海"
     *   }
     *
     * @RequestBody: 将请求体中的 JSON 自动绑定到 User 对象
     */
    @PostMapping("/user")
    public Map<String, Object> add(@RequestBody User user) {
        Map<String, Object> result = new HashMap<>();

        if (user.getName() == null || user.getName().isEmpty()) {
            result.put("success", false);
            result.put("message", "姓名不能为空");
            return result;
        }
        if (user.getAddress() == null || user.getAddress().isEmpty()) {
            result.put("success", false);
            result.put("message", "地址不能为空");
            return result;
        }

        int rows = userService.add(user);
        if (rows > 0) {
            result.put("success", true);
            result.put("message", "添加成功");
            result.put("data", user);
        } else {
            result.put("success", false);
            result.put("message", "添加失败");
        }
        return result;
    }

    /**
     * 功能4: 按 id 删除用户
     *
     * 请求方式: DELETE
     * 接口地址: http://localhost:8080/api/user/1
     */
    @DeleteMapping("/user/{id}")
    public Map<String, Object> delete(@PathVariable int id) {
        Map<String, Object> result = new HashMap<>();

        // 先查是否存在
        UserVO user = userService.findById(id);
        if (user == null) {
            result.put("success", false);
            result.put("message", "未找到 id=" + id + " 的用户，无法删除");
            return result;
        }

        int rows = userService.deleteById(id);
        if (rows > 0) {
            result.put("success", true);
            result.put("message", "删除成功，已删除 id=" + id + " 的用户");
        } else {
            result.put("success", false);
            result.put("message", "删除失败");
        }
        return result;
    }
}
