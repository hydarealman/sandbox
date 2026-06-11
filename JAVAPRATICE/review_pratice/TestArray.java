package review_pratice;

public class TestArray {
    public static void main(String[] args) {
        int size = 10;
        double[] mylist = new double[size];
        mylist[0] = 1.0;
        mylist[1] = 1.0;
        mylist[2] = 1.0;
        mylist[3] = 1.0;
        mylist[4] = 1.0;
        mylist[5] = 1.0;
        mylist[6] = 1.0;

        for (double each : mylist) {
            System.out.println(each);
        }
    }
}
