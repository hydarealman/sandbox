import jakarta.servlet.*;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.*;
import java.io.IOException;

/** 注销Servlet - 销毁Session */
@WebServlet(urlPatterns = {"/logout"})
public class LogoutServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.setCharacterEncoding("UTF-8");
        response.setContentType("text/html;charset=UTF-8");

        // 获取当前Session（不创建新的）
        HttpSession session = request.getSession(false);

        if (session != null) {
            // 销毁Session
            session.invalidate();
        }

        // 重定向到登录页面
        response.sendRedirect("login.jsp?info=您已成功注销！");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doGet(request, response);
    }
}
