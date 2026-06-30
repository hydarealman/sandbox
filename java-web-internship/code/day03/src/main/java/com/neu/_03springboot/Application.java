package com.neu._03springboot;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

/**
 * Day03 - Spring Boot 启动类
 *
 * 功能:
 *   1. 按 id 查询用户  (GET /api/user/{id})
 *   2. 查询全部用户    (GET /api/users)
 *   3. 添加用户        (POST /api/user)
 *   4. 按 id 删除用户  (DELETE /api/user/{id})
 *
 * 核心知识点:
 *   - @SpringBootApplication: 组合注解（@Configuration + @EnableAutoConfiguration + @ComponentScan）
 *   - @MapperScan: 扫描 Mapper 接口（也可以用每个 Mapper 上的 @Mapper 注解）
 */
@SpringBootApplication(scanBasePackages = "com.neu")
@MapperScan("com.neu.mapper")
public class Application {

    public static void main(String[] args) {
        SpringApplication.run(Application.class, args);
        System.out.println("========================================");
        System.out.println("  用户管理系统启动成功!");
        System.out.println("  接口地址: http://localhost:8080");
        System.out.println("  全部用户: GET    /api/users");
        System.out.println("  查询用户: GET    /api/user/{id}");
        System.out.println("  添加用户: POST   /api/user");
        System.out.println("  删除用户: DELETE /api/user/{id}");
        System.out.println("========================================");
    }
}
