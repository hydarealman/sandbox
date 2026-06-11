package review_pratice;

// 抽象类: 员工(封装 + 抽象方法)
abstract class Employee{
    private String name;
    private int id;

    public Employee(String name,int id) {
        this.name = name;
        this.id = id;
    }

    public String getName() {return name;}
    public void setName(String name) {this.name = name;}
    public int getId() {return this.id;}
    public void setId(int id) {this.id = id;}

    // 抽象方法: 由子类实现要求重写
    public abstract double calculateSalary();

    public void printInfo() {
        System.out.println("姓名: " + name + ",工号: " + id);
    }

    public void printInfo(boolean showSalary) {
        printInfo();
        if (showSalary) {
            System.out.println("工资" + calculateSalary());
        }
    }
}


// 子类：固定工资员工（继承 + 重写）
class SalariedEmployee extends Employee {
    private double monthlySalary;   // 封装月薪

    public SalariedEmployee(String name, int id, double monthlySalary) {
        super(name, id);
        this.monthlySalary = monthlySalary;
    }

    public double getMonthlySalary() { return monthlySalary; }
    public void setMonthlySalary(double monthlySalary) { this.monthlySalary = monthlySalary; }

    @Override
    public double calculateSalary() {   // 重写（Override）抽象方法
        return monthlySalary;
    }

    // 重载（Overload）演示：两种调薪方式
    public void raise(double percent) {                     // 百分比调薪
        if (percent > 0) monthlySalary += monthlySalary * percent / 100;
    }
    public void raise(double amount, boolean isAbsolute) {  // 绝对值调薪
        if (isAbsolute && amount > 0) monthlySalary += amount;
    }
}

// 子类：小时工（继承 + 重写）
class HourlyEmployee extends Employee {
    private double hourlyRate;   // 时薪
    private int hoursWorked;     // 工作时数

    public HourlyEmployee(String name, int id, double hourlyRate, int hoursWorked) {
        super(name, id);
        this.hourlyRate = hourlyRate;
        this.hoursWorked = hoursWorked;
    }

    public double getHourlyRate() { return hourlyRate; }
    public void setHourlyRate(double hourlyRate) { this.hourlyRate = hourlyRate; }
    public int getHoursWorked() { return hoursWorked; }
    public void setHoursWorked(int hoursWorked) { this.hoursWorked = hoursWorked; }

    @Override
    public double calculateSalary() {   // 重写（Override）抽象方法
        return hourlyRate * hoursWorked;
    }

    // 重载（Overload）演示：两种计算预估工资的方式
    public double projectedSalary(double newRate) {
        return newRate * hoursWorked;
    }
    public double projectedSalary(double newRate, int extraHours) {
        return newRate * (hoursWorked + extraHours);
    }
}
public class OOPdemo {
    public static void main(String[] args) {
        Employee emp1 = new SalariedEmployee("张三", 1001, 8000);
        Employee emp2 = new HourlyEmployee("李四", 1002, 25.0, 160);

        System.out.println("===== 多态演示 =====");
        emp1.printInfo(true);   // 输出固定工资员工信息
        emp2.printInfo(true);   // 输出小时工信息


        // 使用数组统一处理，动态绑定
        Employee[] staff = {emp1, emp2};
        System.out.println("\n===== 循环调用（多态）=====");
        for (Employee e : staff) {
            System.out.println(e.getName() + " 的实际工资: " + e.calculateSalary());
        }

        // 重载演示：测试类中的重载方法
        System.out.println("\n===== 重载（Overload）演示 =====");
        printDetails(emp1);
        printDetails(emp1, "正式员工");

        // 子类特有方法调用（结合重载）
        SalariedEmployee sal = (SalariedEmployee) emp1;  // 向下转型
        System.out.println("\n---- 固定员工调薪重载 ----");
        System.out.println("原月薪: " + sal.calculateSalary());
        sal.raise(10);               // 调用 raise(double) 增加10%
        System.out.println("加薪10%后: " + sal.calculateSalary());
        sal.raise(500, true);        // 调用 raise(double, boolean) 增加绝对值500
        System.out.println("再加500后: " + sal.calculateSalary());

        HourlyEmployee hourly = (HourlyEmployee) emp2;
        System.out.println("\n---- 小时工预估工资重载 ----");
        System.out.println("当前工资: " + hourly.calculateSalary());
        System.out.println("提高时薪到30元: " + hourly.projectedSalary(30.0));
        System.out.println("提高时薪到30元并加班20小时: " + hourly.projectedSalary(30.0, 20));
    }

    // 重载方法1：仅打印基本信息
    public static void printDetails(Employee e) {
        System.out.println("员工: " + e.getName() + ", ID: " + e.getId());
    }

    // 重载方法2：打印基本信息 + 备注
    public static void printDetails(Employee e, String remark) {
        System.out.println("员工: " + e.getName() + ", ID: " + e.getId() + " [" + remark + "]");
    }
}
