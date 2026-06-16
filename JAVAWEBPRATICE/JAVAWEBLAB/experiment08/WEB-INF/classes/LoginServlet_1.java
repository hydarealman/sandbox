import jakarta.servlet.*;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.*;
import java.io.IOException;

/** Servlet实现登录验证 */
@WebServlet(urlPatterns = {"/loginServlet_1"})
public class LoginServlet_1 extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.setCharacterEncoding("UTF-8");
        response.setContentType("text/html;charset=UTF-8");

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // 验证用户名和密码是否完整
        if (username == null || username.trim().isEmpty() ||
            password == null || password.trim().isEmpty()) {
            response.sendRedirect("login_1.jsp?error=用户名和密码不能为空！");
            return;
        }

        // 验证用户名和密码是否正确
        if ("zhangsan".equals(username) && "123".equals(password)) {
            // 登录成功 - 使用forward转发
            request.setAttribute("username", username);
            request.setAttribute("password", password);
            request.getRequestDispatcher("/loginSuccess_1.jsp").forward(request, response);
        } else {
            // 登录失败 - 使用sendRedirect重定向
            response.sendRedirect("login_1.jsp?error=用户名或密码错误！");
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doPost(request, response);
    }
}
