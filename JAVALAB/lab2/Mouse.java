package JAVALAB.lab2;

public class Mouse extends Animal {
    public Mouse(String name, String food) {
        super(name, food);
    }

    public void digHole() {
        System.out.println(name + " 正在打洞");
    }
}
