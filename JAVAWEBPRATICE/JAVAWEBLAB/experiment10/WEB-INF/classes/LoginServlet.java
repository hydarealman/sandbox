import jakarta.servlet.*;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.*;
import java.io.IOException;
import java.util.Date;

/** 登录Servlet - 处理登录请求并创建Session */
@WebServlet(urlPatterns = {"/login"})
public class LoginServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.setCharacterEncoding("UTF-8");
        response.setContentType("text/html;charset=UTF-8");

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        // 验证用户名和密码（用户名为空则重定向回登录页）
        if (username == null || username.trim().isEmpty() ||
            password == null || password.trim().isEmpty()) {
            response.sendRedirect("login.jsp?error=用户名和密码不能为空！");
            return;
        }

        // 验证规则：用户名与密码相同即为合法用户
        if (username.equals(password)) {
            // 创建Session并保存用户信息
            HttpSession session = request.getSession(true);
            session.setAttribute("username", username);
            session.setAttribute("loginTime", new Date().toString());
            session.setAttribute("sessionId", session.getId());

            // 使用URL重写进行重定向
            response.sendRedirect(response.encodeRedirectURL("welcome.jsp"));
        } else {
            response.sendRedirect("login.jsp?error=用户名或密码错误！");
        }
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doPost(request, response);
    }
}
