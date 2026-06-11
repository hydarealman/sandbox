package review_pratice;

/**
 * 接口学习示例：展示接口的定义、实现、多实现、继承以及默认方法（Java 8+）
 */
public class InterfaceDemo {
    public static void main(String[] args) {
        // 通过接口引用实现类对象（多态）
        Animal dog = new Dog("小黑");
        Animal cat = new Cat("咪咪");

        dog.eat();
        dog.sleep();
        ((Pet) dog).play();   // Dog 实现了 Pet 接口

        cat.eat();
        cat.sleep();

        // 接口的静态方法调用
        Animal.breathe();

        // 默认方法调用
        dog.run();
        cat.run();
    }
}

// 定义接口 Animal
interface Animal {
    // 接口中的变量默认是 public static final
    int LEGS = 4;

    // 抽象方法（默认 public abstract）
    void eat();
    void sleep();

    // 静态方法（Java 8+），只能通过接口名调用
    static void breathe() {
        System.out.println("动物需要呼吸空气");
    }

    // 默认方法（Java 8+），提供默认实现，子类可重写
    default void run() {
        System.out.println("动物正在奔跑...");
    }
}

// 另一个接口 Pet（展示多实现）
interface Pet {
    void play();
}

// 接口继承（多继承）
interface Furry extends Animal, Pet {
    void groom();   // 梳理毛发
}

// 抽象类实现部分接口方法
abstract class BaseAnimal implements Animal {
    protected String name;

    public BaseAnimal(String name) {
        this.name = name;
    }

    // 实现 sleep 方法，eat 留给具体子类
    @Override
    public void sleep() {
        System.out.println(name + " 正在睡觉 Zzz...");
    }
}

// 实现类 Dog：继承抽象类并实现多个接口
class Dog extends BaseAnimal implements Pet, Furry {
    public Dog(String name) {
        super(name);
    }

    @Override
    public void eat() {
        System.out.println(name + " 喜欢吃骨头");
    }

    @Override
    public void play() {
        System.out.println(name + " 正在玩飞盘");
    }

    @Override
    public void groom() {
        System.out.println(name + " 需要定期梳毛");
    }

    // 重写默认方法
    @Override
    public void run() {
        System.out.println(name + " 四条腿飞奔");
    }
}

// 实现类 Cat：只实现 Animal 接口
class Cat extends BaseAnimal {
    public Cat(String name) {
        super(name);
    }

    @Override
    public void eat() {
        System.out.println(name + " 喜欢吃鱼");
    }

    // 使用 Animal 接口的默认 run 方法，不重写
}
