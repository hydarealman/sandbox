package JAVALAB.lab2;

public class AnimalWorld {
    public static void main(String[] args) {
        Mouse jerry = new Mouse("杰瑞", "奶酪");
        jerry.eat();
        jerry.sleep();
        jerry.digHole();

        Panda panda = new Panda("团团", "竹子");
        panda.eat();
        panda.sleep();
    }
}