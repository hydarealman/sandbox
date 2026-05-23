package JAVALAB.lab1;

import JAVALAB.lab1.ClassRoom.Teacher.Student;

public class ClassRoom {
    public static void main(String args[]) {
        System.out.println("教学活动从教室开始");
        Teacher zhang = new Teacher();
        Student jiang = new Student();
        zhang.introduceSelf();
        jiang.introduceSelf();
    }

    public static class Teacher {
    void introduceSelf() {
        System.out.println("我是张老师"); // 【代码2】
    }

    public static class Student {
    void introduceSelf() {
        System.out.println("我是学生，名字是：奖励"); // 【代码3】
    }
}
}
}
