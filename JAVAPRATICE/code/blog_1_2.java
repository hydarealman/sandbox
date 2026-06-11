package code;

import java.lang.reflect.Method;

/**
 * Java 反射机制 --- 运行时获取类的信息、调用方法
 * 反射就是让程序在运行是"照镜子 --- 看见自己的结构,并动态操作他"
 */
public class blog_1_2 {
    public static void main(String[] args) throws Exception {
        // 1. 拿到 String 类的 Class 对象（反射的入口）
        Class<?> cls = Class.forName("java.lang.String");

        // 2. 打印类名
        System.out.println("类名: " + cls.getName());

        // 3. 拿到 length() 方法，然后调用它
        Method m = cls.getMethod("length");          // 获取方法
        String s = "hello java";
        int len = (int) m.invoke(s);                 // 调用 s.length()
        System.out.println("字符串 \"" + s + "\" 的长度: " + len);
    }
}