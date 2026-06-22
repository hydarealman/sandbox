package com.neu._01hello;

import com.neu._01hello.vo.UserVO;
import com.neu.mapper.UserMapper;
import com.neu.util.SqlSessionUtil;
import org.apache.ibatis.session.SqlSession;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

/**
 * Day01 - MyBatis 动态代理原理演示
 *
 * 核心原理:
 *   MyBatis 底层通过 JDK 动态代理 (Proxy.newProxyInstance) 为 Mapper 接口生成代理对象。
 *   当调用 Mapper 接口方法时，实际执行的是 InvocationHandler.invoke()：
 *     1. 获取接口全限定名 → namespace
 *     2. 获取方法名         → id (sqlId)
 *     3. 拼接: namespace + "." + id
 *     4. 调用 sqlSession.selectOne(sqlId, args) 执行 SQL
 *
 * 这就是 getMapper(UserMapper.class) 背后的工作原理!
 */
public class ProxyTest {

    public static void main(String[] args) {
        // 使用 JDK 动态代理手动模拟 MyBatis 的 Mapper 代理

        Class<?>[] clazz = new Class[]{UserMapper.class};

        UserMapper proxy = (UserMapper) Proxy.newProxyInstance(
                ProxyTest.class.getClassLoader(),
                clazz,
                new InvocationHandler() {
                    @Override
                    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
                        // 1. 获取 namespace (接口全限定名)
                        String namespace = proxy.getClass().getInterfaces()[0].getName();

                        // 2. 获取 id (方法名)
                        String id = method.getName();

                        // 3. 拼接 sqlId = namespace + "." + id
                        String sqlId = namespace + "." + id;
                        System.out.println("动态代理 sqlId: " + sqlId);

                        // 4. 获取 SqlSession 并执行 SQL
                        SqlSession sqlSession = SqlSessionUtil.openSession();
                        Object result = sqlSession.selectOne(sqlId, args[0]);
                        sqlSession.close();

                        return result;
                    }
                }
        );

        // 调用代理对象的 findById 方法 → 实际执行上面的 invoke()
        UserVO userVO = proxy.findById(1);
        System.out.println("========== ProxyTest 结果 ==========");
        System.out.println(userVO);
    }
}
