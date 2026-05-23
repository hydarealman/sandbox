package JAVAWEBPRATICE.JAVAWEBPRATICE.第六次实验.java2;

import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/HandleComputer")   // 表单提交的 URL
public class HandleComputer extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // 1. 获取表单数据
        String num1Str = request.getParameter("num1");
        String num2Str = request.getParameter("num2");
        String operator = request.getParameter("operator");

        double num1 = 0, num2 = 0;
        try {
            num1 = Double.parseDouble(num1Str);
            num2 = Double.parseDouble(num2Str);
        } catch (NumberFormatException e) {
            request.setAttribute("error", "请输入有效的数字");
            request.getRequestDispatcher("inputNumber.jsp").forward(request, response);
            return;
        }

        // 2. 创建实体模型并填充
        Computer computer = new Computer();
        computer.setNum1(num1);
        computer.setNum2(num2);
        computer.setOperator(operator);

        // 3. 调用业务模型计算
        CalculateBean calculateBean = new CalculateBean();
        try {
            calculateBean.calculate(computer);
        } catch (ArithmeticException e) {
            request.setAttribute("error", "除数不能为零");
            request.getRequestDispatcher("inputNumber.jsp").forward(request, response);
            return;
        } catch (UnsupportedOperationException e) {
            request.setAttribute("error", "不支持的运算符");
            request.getRequestDispatcher("inputNumber.jsp").forward(request, response);
            return;
        }

        // 4. 将实体模型存入请求作用域
        request.setAttribute("computer", computer);

        // 5. 转发到结果页面
        request.getRequestDispatcher("showResult.jsp").forward(request, response);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        doPost(request, response);
    }
}