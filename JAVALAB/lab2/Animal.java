package JAVALAB.lab2;

public class Animal {
    protected String name;
    protected String food;

    public Animal(String name, String food) {
        this.name = name;
        this.food = food;
    }

    public void eat() {
        System.out.println(name + " 正在吃 " + food);
    }

    public void sleep() {
        System.out.println(name + " 正在睡觉");
    }
}