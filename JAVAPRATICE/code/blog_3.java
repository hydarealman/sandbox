package code;

/**
 * 形式化方法 --- 用断言 assert 描述"必须满足的条件"
 * 推荐阅读《大象 --- Thinking in UML》
 */


/*
    形式化方法 = "把应该满足的条件" 用代码明明白白写出来
    让程序在出错的第一时间暴毙并报信,而不是带着错误继续跑下去,最后留下
    一个找不到原因的Bug
*/

// assert 布尔表达式 : 报错信息;
public class blog_3 {

    static int divide(int a, int b) {
        assert b != 0 : "前置条件：除数不能为0";    // 调用前必须满足
        int r = a / b;
        assert r * b == a : "后置条件：结果能还原";  // 调用后一定满足
        return r;
    }

    public static void main(String[] args) {
        System.out.println("10 / 2 = " + divide(10, 2));

        System.out.println("10 / 0 = " + divide(10, 0));  // 触发断言
    }
}
