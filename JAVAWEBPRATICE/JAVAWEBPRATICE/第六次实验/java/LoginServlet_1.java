package JAVAWEBPRATICE.JAVAWEBPRATICE.第六次实验.java;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/loginServlet_1")   // 注意：urlPatterns 需要与表单 action 一致
public class LoginServlet_1 extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // 检查数据是否完整
        if (username == null || username.trim().isEmpty() ||
            password == null || password.trim().isEmpty()) {
            response.sendRedirect("login_1.jsp?error=incomplete");
            return;
        }

        // 验证用户名和密码
        if ("zhangsan".equals(username) && "123".equals(password)) {
            // 验证成功，转发到 success 页面（可以携带用户信息）
            request.setAttribute("loginUser", username);
            request.getRequestDispatcher("loginSuccess_1.jsp").forward(request, response);
        } else {
            // 验证失败，重定向回登录页并携带错误标识
            response.sendRedirect("login_1.jsp?error=invalid");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doPost(request, response);
    }
}