package code;

/**
 * 单一职责原则 + 开闭原则
 */
public class blog_4 {

    public static void main(String[] args) {

        // 单一职责：一个方法只做一件事
        String user = "admin";
        String pwd = "123";

        boolean ok = checkUser(user, pwd);   // 只负责验证
        writeLog(user, ok);                  // 只负责记日志

        System.out.println("登录结果: " + ok);

        // 开闭原则：有新需求加新方法，不改旧方法
        drawChart("pie");
        drawChart("bar");
    }

    // ---- 单一职责：每个方法只干一件事 ----
    static boolean checkUser(String user, String pwd) {
        return user.equals("admin") && pwd.equals("123");
    }

    static void writeLog(String user, boolean ok) {
        System.out.println("日志: " + user + (ok ? "登录成功" : "登录失败"));
    }

    // ---- 开闭原则：新增图表类型只加 case，不改已有逻辑 ----
    static void drawChart(String type) {
        if ("pie".equals(type)) {
            System.out.println("画饼状图");
        } else if ("bar".equals(type)) {
            System.out.println("画柱状图");
        }
    }
}
