#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""Generate all 10 JavaWeb experiment reports as HTML files."""

import os
import base64
import re

BASE_DIR = r'd:\sandbox\JAVAWEBPRATICE\JAVAWEBLAB'
REPORTS_DIR = os.path.join(BASE_DIR, 'reports')
SCREENSHOTS_DIR = os.path.join(REPORTS_DIR, 'screenshots')
EXPERIMENT_TEXTS_DIR = os.path.join(BASE_DIR, 'experiment_texts')

# Experiment definitions
EXPERIMENTS = [
    {
        'num': 1,
        'title': '调查问卷制作',
        'subtitle': 'HTML常用标签的应用',
        'purpose': [
            '掌握HTML的常用标签；',
            '认真书写实验报告，如实填写各项实验内容。'
        ],
        'content': [
            '编写网页practice1_1.html，具体要求如下：',
            '（1）网页中有个form表单，表单处理程序为本页面程序，表单提交方式为"post"，表单提交编码方式为"multipart/form-data"；',
            '（2）页面包含用户名、密码、性别（单选）、年龄（下拉选择）、爱好（多选）、学历（下拉选择）、自我介绍（文本域）等表单元素；',
            '（3）使用CSS对页面进行美化，包含提交和重置按钮。'
        ],
        'source_files': [
            ('experiment01/practice1_1.html', 'practice1_1.html - 调查问卷页面')
        ],
        'screenshots': ['experiment01.png'],
        'notes': '本次实验通过编写HTML表单页面，掌握了form标签、input标签（text/password/radio/checkbox）、select标签、textarea标签等常用HTML标签的使用方法。同时学习了CSS基本样式设置，包括字体、颜色、边框、背景等属性的应用。',
        'deploy': '直接使用浏览器打开 experiment01/practice1_1.html 文件即可运行'
    },
    {
        'num': 2,
        'title': '页面布局',
        'subtitle': 'DIV+CSS布局类型',
        'purpose': [
            '掌握CSS的基本语法；',
            '掌握常见的DIV+CSS布局类型；',
            '认真书写实验报告，如实填写各项实验内容。'
        ],
        'content': [
            '按照以下步骤编写网页practice1_2.html：',
            '步骤1：使用DIV定义结构——页头(#header)、导航栏(#navigator)、内容(#content)、版权(#footer)，全部放入body容器中；',
            '步骤2：定义body属性——width:800px, margin:0px auto居中, border边框；',
            '步骤3：定义页头#header——height:100px，背景图片background-image；',
            '步骤4：定义导航栏#navigator——横向排列6个链接，float:left，hover变色效果；',
            '步骤5：定义内容#content——文本缩进text-indent:2em，行高line-height:1.5em；',
            '步骤6：定义页脚#footer——居中版权信息，背景色#009966。'
        ],
        'source_files': [
            ('experiment02/practice1_2.html', 'practice1_2.html - DIV+CSS页面布局')
        ],
        'screenshots': ['experiment02.png'],
        'notes': '本次实验学习了DIV+CSS进行网页布局的方法。通过将页面划分为header、navigator、content、footer四个结构块，使用CSS的float属性实现导航栏的横向排列，使用margin:0px auto实现整体居中。理解了盒子模型的概念以及CSS选择器的使用方法。',
        'deploy': '直接使用浏览器打开 experiment02/practice1_2.html 文件即可运行'
    },
    {
        'num': 3,
        'title': '表单验证',
        'subtitle': 'JavaScript事件处理机制',
        'purpose': [
            '掌握JavaScript的语法基础；',
            '掌握JavaScript的事件处理机制；',
            '认真书写实验报告，如实填写各项实验内容。'
        ],
        'content': [
            '制作一个用户注册页面practice1_3.html，具体要求如下：',
            '（1）包含登录账号、密码、确认密码、姓名、身份证号码（18位）、出生年月日、住址、邮编、E-mail等输入区域；',
            '（2）在提交时使用JavaScript检验输入是否符合要求，alert出非法的输入，并将焦点返回对应控件；',
            '（3）根据出生年月日判断身份证号码是否合法（只考虑18位身份证）；',
            '（4）验证规则：登录账号只能是字母或数字且以字母开头；密码8位以上且需要有字母、数字和特殊字符；出生年月日格式为yyyy-mm-dd且与身份证号一致；邮编为6位数字；E-mail格式验证。'
        ],
        'source_files': [
            ('experiment03/practice1_3.html', 'practice1_3.html - JavaScript表单验证')
        ],
        'screenshots': ['experiment03.png'],
        'notes': '本次实验学习了JavaScript的表单验证技术。掌握了onsubmit事件、正则表达式验证、字符串操作、DOM元素访问（getElementById）等知识点。特别是身份证号码与出生日期的交叉验证，加深了对JavaScript逻辑编程的理解。',
        'deploy': '直接使用浏览器打开 experiment03/practice1_3.html 文件即可运行'
    },
    {
        'num': 4,
        'title': 'JSP脚本元素的应用',
        'subtitle': 'Java程序片、成员变量与表达式',
        'purpose': [
            '掌握Java程序片的定义与使用（<% %>）；',
            '掌握JSP成员变量与方法的定义与使用（<%! %>）；',
            '掌握Java表达式的定义与使用（<%= %>）；',
            '认真书写实验报告，如实填写各项实验内容。'
        ],
        'content': [
            '编写1个JSP页面index.jsp，在JSP页面中使用以下JSP脚本元素：',
            '1、使用Java程序片（<%%>）实现循环输出，在浏览器中输出大小为15*10的表格；',
            '2、利用成员变量（<%! %>）被所有客户共享这一性质，实现一个简单的访问计数器；',
            '3、使用JSP表达式（<%= %>）输出当前日期时间；',
            '4、使用JSP声明（<%! %>）定义方法和成员变量，综合演示JSP脚本元素的使用。'
        ],
        'source_files': [
            ('experiment04/index.jsp', 'index.jsp - JSP脚本元素综合演示')
        ],
        'screenshots': ['experiment04.png'],
        'notes': '本次实验深入学习了JSP的三种脚本元素：声明（<%! %>）用于定义成员变量和方法，脚本段（<% %>）用于编写Java逻辑代码，表达式（<%= %>）用于输出数据。特别是通过访问计数器的实现，理解了JSP成员变量的共享特性——声明在<%! %>中的变量属于Servlet的实例变量，被所有请求共享。',
        'deploy': '部署在Tomcat webapps/experiment04/目录下，通过 http://localhost:8088/experiment04/ 访问'
    },
    {
        'num': 5,
        'title': 'JSP动作标记的应用',
        'subtitle': 'include、forward和param动作标记',
        'purpose': [
            '掌握动作标记include、forward和param的应用；',
            '认真书写实验报告，如实填写各项实验内容。'
        ],
        'content': [
            '1、include和param动作标记的应用：编写3个JSP页面input.jsp、first.jsp和second.jsp。input.jsp使用<jsp:include>动作标记加载first.jsp和second.jsp页面，并通过<jsp:param>传递参数。first.jsp根据参数生成动态表格，second.jsp根据参数计算两个正整数的最大公约数和最小公倍数。',
            '2、登录验证：编写3个JSP页面login.jsp、validate.jsp和success.jsp。login.jsp输入用户名与密码，提交给validate.jsp进行验证（合法用户：tom/jenny），如果验证通过则使用<jsp:forward>转发到success.jsp，否则转发回login.jsp并显示错误信息。'
        ],
        'source_files': [
            ('experiment05/input.jsp', 'input.jsp - include和param动作标记加载页面'),
            ('experiment05/first.jsp', 'first.jsp - 动态生成表格'),
            ('experiment05/second.jsp', 'second.jsp - 计算最大公约数和最小公倍数'),
            ('experiment05/login.jsp', 'login.jsp - 登录页面'),
            ('experiment05/validate.jsp', 'validate.jsp - 验证页面（使用forward动作）'),
            ('experiment05/success.jsp', 'success.jsp - 登录成功页面')
        ],
        'screenshots': ['experiment05_input.png', 'experiment05_login.png'],
        'notes': '本次实验学习了JSP动作标记的使用。通过<jsp:include>实现了页面的模块化包含，通过<jsp:param>实现了参数传递，使得被包含的页面能够动态获取参数。同时学习了<jsp:forward>的使用，理解了服务端转发和客户端跳转的区别。',
        'deploy': '部署在Tomcat webapps/experiment05/目录下，通过 http://localhost:8088/experiment05/input.jsp 和 http://localhost:8088/experiment05/login.jsp 访问'
    },
    {
        'num': 6,
        'title': 'JSP内置对象的应用',
        'subtitle': 'request、response、session、application对象',
        'purpose': [
            '掌握JSP内置对象的定义及常用方法；',
            '理解request、session以及application的区别；',
            '认真书写实验报告，如实填写各项实验内容。'
        ],
        'content': [
            '1、编写index.jsp页面，综合演示JSP四大内置对象（request、response、session、application）的常用方法。包括：获取请求参数、获取客户端信息、设置响应头、Session属性存取、Application属性存取、访问计数等。',
            '2、编写shop.jsp页面，实现基于HttpSession的购物车功能。商品包括：《Java编程思想》、《JSP实战指南》、《Servlet核心技术》、《Web开发大全》。用户可以添加商品到购物车、查看购物车、清空购物车。购物车数据存储在session中。'
        ],
        'source_files': [
            ('experiment06/index.jsp', 'index.jsp - JSP内置对象综合演示'),
            ('experiment06/shop.jsp', 'shop.jsp - 基于Session的购物车')
        ],
        'screenshots': ['experiment06_index.png', 'experiment06_shop.png'],
        'notes': '本次实验深入理解了JSP四大内置对象的区别：request的作用域仅限于一次请求，response用于响应客户端，session的作用域是一次会话（多个请求间共享），application的作用域是整个Web应用（所有用户共享）。通过购物车的实现，加深了对Session跟踪机制的理解。',
        'deploy': '部署在Tomcat webapps/experiment06/目录下，通过 http://localhost:8088/experiment06/ 访问'
    },
    {
        'num': 7,
        'title': 'JavaBean的应用',
        'subtitle': 'jsp:useBean、jsp:setProperty、jsp:getProperty',
        'purpose': [
            '掌握JavaBean的定义规范；',
            '掌握JSP中useBean、setProperty、getProperty动作标记的使用；',
            '认真书写实验报告，如实填写各项实验内容。'
        ],
        'content': [
            '编写三角形JavaBean（Triangle.java）和JSP页面（inputTriangle.jsp、showTriangle.jsp）。',
            'Triangle.java包含三个属性：sideA、sideB、sideC（double类型）。提供方法：isValid()判断三角形是否合法（两边之和大于第三边），getPerimeter()计算周长，getArea()使用海伦公式计算面积。',
            'inputTriangle.jsp提供表单输入三边长，提交到showTriangle.jsp。showTriangle.jsp使用<jsp:useBean>实例化Triangle，<jsp:setProperty property="*">自动填充属性，<jsp:getProperty>显示属性值。'
        ],
        'source_files': [
            ('experiment07/WEB-INF/classes/Triangle.java', 'Triangle.java - 三角形JavaBean'),
            ('experiment07/inputTriangle.jsp', 'inputTriangle.jsp - 输入三角形边长'),
            ('experiment07/showTriangle.jsp', 'showTriangle.jsp - 显示三角形计算结果')
        ],
        'screenshots': ['experiment07_input.png', 'experiment07_show.png'],
        'notes': '本次实验学习了JavaBean的编写规范和使用方法。JavaBean需要有无参构造方法、私有属性、getter/setter方法。通过<jsp:useBean>创建Bean实例，<jsp:setProperty property="*">可以自动将请求参数填充到Bean属性中，大大简化了参数获取代码。海伦公式的实现加深了对Java面向对象编程的理解。',
        'deploy': '部署在Tomcat webapps/experiment07/目录下，Triangle.java编译为WEB-INF/classes/beans/Triangle.class，通过 http://localhost:8088/experiment07/inputTriangle.jsp 访问'
    },
    {
        'num': 8,
        'title': 'Servlet的应用',
        'subtitle': 'Servlet登录验证、forward与redirect',
        'purpose': [
            '掌握Servlet的编写与配置（@WebServlet注解）；',
            '理解RequestDispatcher.forward()与response.sendRedirect()的区别；',
            '认真书写实验报告，如实填写各项实验内容。'
        ],
        'content': [
            '编写一个Servlet（LoginServlet_1.java）实现登录验证，使用@WebServlet注解配置URL映射。',
            'login_1.jsp提供登录表单，提交到LoginServlet_1。Servlet在doPost()方法中验证用户名和密码，如果为合法用户（zhangsan/123），使用RequestDispatcher.forward()转发到loginSuccess_1.jsp；否则使用response.sendRedirect()重定向回login_1.jsp并显示错误信息。',
            'loginSuccess_1.jsp显示登录成功信息，展示用户名和密码，并说明forward和redirect的区别。'
        ],
        'source_files': [
            ('experiment08/WEB-INF/classes/LoginServlet_1.java', 'LoginServlet_1.java - Servlet登录验证'),
            ('experiment08/login_1.jsp', 'login_1.jsp - 登录表单页面'),
            ('experiment08/loginSuccess_1.jsp', 'loginSuccess_1.jsp - 登录成功页面')
        ],
        'screenshots': ['experiment08_login.png'],
        'notes': '本次实验学习了Servlet的编写方法，掌握了@WebServlet注解配置URL映射。深入理解了forward和redirect的区别：forward是服务器内部转发，URL不变，可以传递请求属性；redirect是客户端重定向，URL改变，不能直接传递请求属性。',
        'deploy': '部署在Tomcat webapps/experiment08/目录下，LoginServlet_1.java编译为WEB-INF/classes/LoginServlet_1.class，通过 http://localhost:8088/experiment08/login_1.jsp 访问'
    },
    {
        'num': 9,
        'title': 'MVC模式的应用',
        'subtitle': 'Model（JavaBean）+ View（JSP）+ Controller（Servlet）',
        'purpose': [
            '理解MVC设计模式的基本思想；',
            '掌握使用Servlet+JSP+JavaBean实现MVC模式的方法；',
            '认真书写实验报告，如实填写各项实验内容。'
        ],
        'content': [
            '使用MVC模式实现一个简单的计算器应用：',
            'Model层：Computer.java（实体模型，封装操作数和结果）、CalculateBean.java（业务模型，执行加减乘除运算）；',
            'View层：inputNumber.jsp（输入两个数和运算符）、showResult.jsp（显示计算结果）；',
            'Controller层：HandleComputer.java（Servlet控制器，获取请求参数、调用Model、转发到View）。',
            'inputNumber.jsp提交到HandleComputer，HandleComputer调用CalculateBean进行计算，将结果存储到Computer实体中，转发到showResult.jsp显示。'
        ],
        'source_files': [
            ('experiment09/WEB-INF/classes/model/Computer.java', 'Computer.java - 实体模型'),
            ('experiment09/WEB-INF/classes/model/CalculateBean.java', 'CalculateBean.java - 业务模型'),
            ('experiment09/WEB-INF/classes/model/HandleComputer.java', 'HandleComputer.java - Servlet控制器'),
            ('experiment09/inputNumber.jsp', 'inputNumber.jsp - 计算器输入页面'),
            ('experiment09/showResult.jsp', 'showResult.jsp - 计算结果页面')
        ],
        'screenshots': ['experiment09_input.png'],
        'notes': '本次实验完整实践了MVC设计模式。Model（Computer+CalculateBean）负责数据和业务逻辑，View（JSP）负责页面展示，Controller（HandleComputer）负责协调Model和View。这种分层架构使代码职责清晰，便于维护和扩展。',
        'deploy': '部署在Tomcat webapps/experiment09/目录下，Java类编译到WEB-INF/classes/model/，通过 http://localhost:8088/experiment09/inputNumber.jsp 访问'
    },
    {
        'num': 10,
        'title': '会话跟踪技术',
        'subtitle': 'HttpSession、URL重写、session.invalidate()',
        'purpose': [
            '掌握HttpSession会话跟踪技术；',
            '掌握URL重写（response.encodeURL()）的使用；',
            '理解session.invalidate()注销机制；',
            '认真书写实验报告，如实填写各项实验内容。'
        ],
        'content': [
            '实现一个基于HttpSession的登录注销系统：',
            '1、LoginServlet.java：处理登录请求，验证用户名与密码相同即为合法（如admin/admin），创建session并保存用户信息（username、loginTime、sessionId），重定向到welcome.jsp；',
            '2、LogoutServlet.java：处理注销请求，获取当前session并调用session.invalidate()销毁，重定向到login.jsp；',
            '3、login.jsp：登录表单页面，显示错误或提示信息；',
            '4、welcome.jsp：欢迎页面（需登录后访问），显示session详细信息（ID、创建时间、最后访问时间、最大不活动间隔），所有链接使用response.encodeURL()进行URL重写；',
            '5、profile.jsp：个人信息页面（需登录后访问），展示用户资料和会话信息，使用encodeURL确保Cookie禁用时仍能正常工作。'
        ],
        'source_files': [
            ('experiment10/WEB-INF/classes/LoginServlet.java', 'LoginServlet.java - 登录Servlet'),
            ('experiment10/WEB-INF/classes/LogoutServlet.java', 'LogoutServlet.java - 注销Servlet'),
            ('experiment10/login.jsp', 'login.jsp - 登录页面'),
            ('experiment10/welcome.jsp', 'welcome.jsp - 欢迎页面（含URL重写）'),
            ('experiment10/profile.jsp', 'profile.jsp - 个人信息页面（含URL重写）')
        ],
        'screenshots': ['experiment10_login.png', 'experiment10_welcome.png', 'experiment10_profile.png'],
        'notes': '本次实验深入学习了HttpSession会话跟踪技术。理解了session的创建、属性存取、超时设置和销毁机制。通过URL重写（response.encodeURL()）技术，确保了在浏览器禁用Cookie的情况下session仍能正常工作。掌握了登录注销系统的完整实现流程。',
        'deploy': '部署在Tomcat webapps/experiment10/目录下，Servlet编译到WEB-INF/classes/，通过 http://localhost:8088/experiment10/login.jsp 访问'
    }
]

def img_to_base64(path):
    """Convert an image to base64 data URI."""
    if os.path.exists(path):
        with open(path, 'rb') as f:
            data = base64.b64encode(f.read()).decode('utf-8')
        return f'data:image/png;base64,{data}'
    return ''

def read_source_file(rel_path):
    """Read source file content with HTML escaping."""
    full_path = os.path.join(BASE_DIR, rel_path)
    if os.path.exists(full_path):
        with open(full_path, 'r', encoding='utf-8', errors='replace') as f:
            content = f.read()
        # Escape HTML entities
        content = content.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')
        return content
    return f'<!-- File not found: {rel_path} -->'

def read_java_source(rel_path):
    """Read Java source file."""
    # Try multiple possible locations
    paths_to_try = [
        os.path.join(BASE_DIR, rel_path),
        rel_path,
    ]
    for full_path in paths_to_try:
        if os.path.exists(full_path):
            with open(full_path, 'r', encoding='utf-8', errors='replace') as f:
                content = f.read()
            content = content.replace('&', '&amp;').replace('<', '&lt;').replace('>', '&gt;')
            return content
    return f'<!-- File not found: {rel_path} -->'

def generate_report(exp):
    """Generate a single experiment report as HTML."""
    num = exp['num']
    title = exp['title']
    subtitle = exp['subtitle']

    html = f'''<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <title>实验{num} {title} - JavaWeb实验报告</title>
    <style>
        @media print {{
            body {{ margin: 0; }}
            .page-break {{ page-break-before: always; }}
        }}
        * {{ margin: 0; padding: 0; box-sizing: border-box; }}
        body {{
            font-family: "SimSun", "宋体", serif;
            font-size: 14px;
            line-height: 1.8;
            color: #333;
            background: #f0f0f0;
        }}
        .container {{
            max-width: 900px;
            margin: 20px auto;
            background: white;
            padding: 40px 50px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }}
        h1 {{
            text-align: center;
            font-size: 22px;
            margin-bottom: 5px;
            font-family: "SimHei", "黑体", sans-serif;
        }}
        .subtitle {{
            text-align: center;
            font-size: 16px;
            color: #555;
            margin-bottom: 20px;
            font-family: "SimHei", "黑体", sans-serif;
        }}
        .info-table {{
            width: 100%;
            border-collapse: collapse;
            margin: 15px 0 25px 0;
        }}
        .info-table td {{
            padding: 6px 10px;
            border: 1px solid #999;
            font-size: 14px;
        }}
        .info-table .label {{
            background: #f5f5f5;
            width: 12%;
            font-weight: bold;
            text-align: center;
        }}
        .info-table .value {{
            width: 38%;
        }}
        h2 {{
            font-size: 16px;
            margin: 25px 0 10px 0;
            padding: 6px 12px;
            background: #009966;
            color: white;
            font-family: "SimHei", "黑体", sans-serif;
            border-radius: 3px;
        }}
        h3 {{
            font-size: 14px;
            margin: 15px 0 8px 0;
            padding-left: 10px;
            border-left: 3px solid #009966;
            font-family: "SimHei", "黑体", sans-serif;
        }}
        p {{ margin: 8px 0; text-indent: 2em; }}
        ul, ol {{ margin: 8px 0 8px 2em; }}
        li {{ margin: 4px 0; }}
        .code-block {{
            background: #1e1e1e;
            color: #d4d4d4;
            padding: 15px;
            margin: 10px 0;
            border-radius: 5px;
            overflow-x: auto;
            font-family: "Consolas", "Courier New", monospace;
            font-size: 12px;
            line-height: 1.5;
            white-space: pre-wrap;
            word-wrap: break-word;
        }}
        .code-filename {{
            background: #333;
            color: #ddd;
            padding: 4px 15px;
            margin: 12px 0 0 0;
            border-radius: 5px 5px 0 0;
            font-family: "Consolas", monospace;
            font-size: 12px;
        }}
        .code-filename + .code-block {{
            margin-top: 0;
            border-radius: 0 0 5px 5px;
        }}
        .screenshot {{
            margin: 15px 0;
            text-align: center;
        }}
        .screenshot img {{
            max-width: 100%;
            border: 1px solid #ddd;
            box-shadow: 0 2px 8px rgba(0,0,0,0.1);
            border-radius: 4px;
        }}
        .screenshot .caption {{
            font-size: 12px;
            color: #666;
            margin-top: 5px;
        }}
        .env-box {{
            background: #f9f9f9;
            border: 1px solid #ddd;
            padding: 15px;
            margin: 10px 0;
            border-radius: 4px;
        }}
        .env-box p {{ text-indent: 0; }}
        .footer {{
            text-align: center;
            margin-top: 30px;
            padding-top: 15px;
            border-top: 1px solid #ddd;
            color: #999;
            font-size: 12px;
        }}
    </style>
</head>
<body>
<div class="container">
    <h1>JavaWeb实验报告</h1>
    <div class="subtitle">实验{num}：{title} —— {subtitle}</div>

    <table class="info-table">
        <tr>
            <td class="label">班级</td><td class="value"></td>
            <td class="label">学号</td><td class="value"></td>
        </tr>
        <tr>
            <td class="label">姓名</td><td class="value"></td>
            <td class="label">实验日期</td><td class="value">2026年6月16日</td>
        </tr>
    </table>

    <h2>一、实验目的</h2>
'''
    for item in exp['purpose']:
        html += f'    <p>{item}</p>\n'

    html += '''
    <h2>二、实验环境</h2>
    <div class="env-box">
        <p><strong>操作系统：</strong>Windows 11 Home China</p>
        <p><strong>JDK版本：</strong>JDK 25.0.2 (Temurin)</p>
        <p><strong>Web服务器：</strong>Apache Tomcat 11.0.22 (Jakarta EE)</p>
        <p><strong>开发工具：</strong>VS Code / 文本编辑器</p>
        <p><strong>浏览器：</strong>Microsoft Edge</p>
        <p><strong>运行方式：</strong>''' + exp['deploy'] + '''</p>
    </div>

    <h2>三、实验内容</h2>
'''
    for item in exp['content']:
        html += f'    <p>{item}</p>\n'

    html += '''
    <h2>四、实验练习</h2>
'''
    # Source code section
    for i, (file_path, desc) in enumerate(exp['source_files']):
        html += f'    <h3>{i+1}. {desc}</h3>\n'
        html += f'    <div class="code-filename">📄 {file_path}</div>\n'
        code = read_source_file(file_path)
        # Determine language for syntax hint
        ext = file_path.split('.')[-1]
        lang = 'java' if ext == 'java' else 'html' if ext in ('html', 'jsp') else ''
        html += f'    <div class="code-block">{code}</div>\n'

    # Screenshots section
    html += '''
    <h2>五、运行结果截图</h2>
'''
    for i, shot in enumerate(exp['screenshots']):
        shot_path = os.path.join(SCREENSHOTS_DIR, shot)
        b64 = img_to_base64(shot_path)
        if b64:
            html += f'''    <div class="screenshot">
        <img src="{b64}" alt="{shot}">
        <div class="caption">图{i+1}：{exp["title"]} - 运行效果截图</div>
    </div>
'''
        else:
            html += f'    <p>⚠ 截图未找到: {shot}</p>\n'

    # Experiment notes
    html += '''
    <h2>六、实验心得</h2>
'''
    html += f'    <p>{exp["notes"]}</p>\n'

    html += '''
    <div class="footer">
        <p>JavaWeb实验报告 | 实验''' + str(num) + ''' | 生成时间：2026年6月16日</p>
    </div>
</div>
</body>
</html>'''

    return html

def main():
    os.makedirs(REPORTS_DIR, exist_ok=True)

    for exp in EXPERIMENTS:
        num = exp['num']
        print(f'Generating report for experiment {num:02d}...')
        html = generate_report(exp)
        filename = f'实验{num:02d}_{exp["title"]}.html'
        filepath = os.path.join(REPORTS_DIR, filename)
        with open(filepath, 'w', encoding='utf-8') as f:
            f.write(html)
        size_kb = os.path.getsize(filepath) / 1024
        print(f'  [OK] {filename} ({size_kb:.0f} KB)')

    # Generate index page
    index_html = '''<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <title>JavaWeb实验报告索引</title>
    <style>
        body { font-family: "Microsoft YaHei", sans-serif; max-width: 800px; margin: 40px auto; background: #f5f5f5; }
        h1 { text-align: center; color: #009966; }
        .report-list { background: white; padding: 30px; border-radius: 8px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }
        .report-list a { display: block; padding: 12px 15px; margin: 8px 0; text-decoration: none; color: #333; border-left: 4px solid #009966; background: #f9f9f9; border-radius: 0 5px 5px 0; transition: all 0.2s; }
        .report-list a:hover { background: #e8f5e9; border-left-color: #006633; padding-left: 25px; }
        .report-list .num { font-weight: bold; color: #009966; margin-right: 10px; }
        .p { text-align: center; color: #999; font-size: 12px; margin-top: 20px; }
    </style>
</head>
<body>
    <h1>📚 JavaWeb实验报告</h1>
    <div class="report-list">
'''
    for exp in EXPERIMENTS:
        num = exp['num']
        title = exp['title']
        subtitle = exp['subtitle']
        filename = f'实验{num:02d}_{title}.html'
        index_html += f'        <a href="{filename}"><span class="num">实验{num}</span> {title} —— {subtitle}</a>\n'

    index_html += '''    </div>
    <p class="p">共 10 次实验 | Apache Tomcat 11.0.22 | JDK 25.0.2</p>
</body>
</html>'''

    index_path = os.path.join(REPORTS_DIR, 'index.html')
    with open(index_path, 'w', encoding='utf-8') as f:
        f.write(index_html)
    print(f'\n[OK] Index page generated: {index_path}')
    print(f'[OK] All {len(EXPERIMENTS)} experiment reports generated successfully!')
    print(f'  Reports directory: {REPORTS_DIR}')

if __name__ == '__main__':
    main()
