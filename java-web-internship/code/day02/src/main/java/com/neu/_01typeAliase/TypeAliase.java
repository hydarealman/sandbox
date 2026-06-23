package com.neu._01typeAliase;

import com.neu.vo.UserVO;
import org.apache.ibatis.io.Resources;
import org.apache.ibatis.session.SqlSession;
import org.apache.ibatis.session.SqlSessionFactory;
import org.apache.ibatis.session.SqlSessionFactoryBuilder;

import java.io.IOException;
import java.io.InputStream;
import java.util.List;

/**
 * Day02 - 类型别名演示
 *
 * 知识点:
 *   1. typeAliases 包扫描: <package name="com.neu.vo"/>
 *      → 自动生成别名 userVO，可直接在 XML 的 resultType 中使用
 *   2. 传统方式: session.selectList("namespace.id") 直接调用 sqlId
 *   3. 流程: SqlSessionFactoryBuilder → SqlSessionFactory → SqlSession
 */
public class TypeAliase {

    public static void main(String[] args) throws IOException {
        // SqlSessionFactoryBuilder → SqlSessionFactory → SqlSession
        SqlSessionFactoryBuilder builder = new SqlSessionFactoryBuilder();

        InputStream inputStream = Resources.getResourceAsStream("mybatis.xml");
        SqlSessionFactory sqlSessionFactory = builder.build(inputStream);

        // 好比是 Connection
        SqlSession session = sqlSessionFactory.openSession();

        // 传统方式: 通过 namespace + id 调用 SQL
        List<UserVO> result = session.selectList("com.neu.mapper.UserMapper.findAll");
        System.out.println("========== TypeAliase 查询结果 ==========");
        System.out.println(result);

        session.close();
    }
}
