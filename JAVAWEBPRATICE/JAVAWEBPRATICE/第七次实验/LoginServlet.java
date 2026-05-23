package JAVAWEBPRATICE.JAVAWEBPRATICE.第七次实验;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/LoginServlet")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // 验证用户名和密码（可根据需要修改）
        if (("tom".equals(username) || "zhangsan".equals(username)) && "123".equals(password)) {
            // 登录成功：保存用户信息到 session
            HttpSession session = request.getSession();
            session.setAttribute("loginUser", username);
            // 重定向到欢迎页，使用 encodeRedirectURL 支持无 Cookie 情况
            response.sendRedirect(response.encodeRedirectURL("welcome.jsp"));
        } else {
            // 登录失败：重定向回登录页
            response.sendRedirect(response.encodeRedirectURL("login.jsp?error=invalid"));
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doPost(request, response);
    }
}