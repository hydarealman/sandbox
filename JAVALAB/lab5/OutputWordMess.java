package JAVALAB.lab5;

import java.util.*;

/**
 * 实验2 - 英文单词统计主程序
 * 统计文本中的单词数量、互不相同单词数，并按出现频率排序输出
 */
public class OutputWordMess {
    public static void main(String args[]) {
        Vector<String> allWord, noSameWord;
        WordStatistic statistic = new WordStatistic();
        // 先统计 english.txt，再统计 hello.txt
        statistic.setFileName("JAVALAB/lab5/english.txt");

        // statistic 调用 wordStatistic() 方法进行统计
        statistic.wordStatistic();
        allWord = statistic.getAllWord();
        noSameWord = statistic.getNoSameWord();

        System.out.println("========== 实验2：统计英文单词 ==========");
        System.out.println("文件: english.txt");
        System.out.println("共有 " + allWord.size() + " 个英文单词");
        System.out.println("有 " + noSameWord.size() + " 个互不相同英文单词");
        System.out.println("按出现频率排列:");

        // 统计每个不重复单词的出现次数
        int count[] = new int[noSameWord.size()];
        for (int i = 0; i < noSameWord.size(); i++) {
            String s1 = noSameWord.elementAt(i);
            for (int j = 0; j < allWord.size(); j++) {
                String s2 = allWord.elementAt(j);
                if (s1.equals(s2))
                    count[i]++;
            }
        }

        // 按出现次数降序排序（冒泡排序）
        for (int m = 0; m < noSameWord.size(); m++) {
            for (int n = m + 1; n < noSameWord.size(); n++) {
                if (count[n] > count[m]) {
                    String temp = noSameWord.elementAt(m);
                    noSameWord.setElementAt(noSameWord.elementAt(n), m);
                    noSameWord.setElementAt(temp, n);
                    int t = count[m];
                    count[m] = count[n];
                    count[n] = t;
                }
            }
        }

        // 输出频率
        for (int m = 0; m < noSameWord.size(); m++) {
            double frequency = (1.0 * count[m]) / allWord.size();
            System.out.printf("%-15s: %-7.3f (%d次)\n",
                    noSameWord.elementAt(m), frequency, count[m]);
        }
        System.out.println();

        // 同样统计 hello.txt
        statistic.setFileName("JAVALAB/lab5/hello.txt");
        statistic.wordStatistic();
        allWord = statistic.getAllWord();
        noSameWord = statistic.getNoSameWord();

        System.out.println("文件: hello.txt");
        System.out.println("共有 " + allWord.size() + " 个英文单词");
        System.out.println("有 " + noSameWord.size() + " 个互不相同英文单词");
        System.out.println();
    }
}
