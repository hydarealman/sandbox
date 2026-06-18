package JAVALAB.lab5;

import java.io.*;
import java.util.*;

/**
 * 实验2 - 英文单词统计
 * 读取英文文本文件，统计所有单词和互不相同单词
 */
public class WordStatistic {
    Vector<String> allWord, noSameWord;
    File file = new File("JAVALAB/lab5/english.txt");
    Scanner sc = null;
    String regex;

    WordStatistic() {
        allWord = new Vector<String>();
        noSameWord = new Vector<String>();
        // regex 是由空格、数字和符号组成的正则表达式，用于分割单词
        regex = "[\\s\\d\\p{Punct}]+";
        try {
            // 创建指向 file 的 Scanner 对象
            sc = new Scanner(file);
            // sc 调用 useDelimiter 方法设置分隔符
            sc.useDelimiter(regex);
        } catch (IOException exp) {
            System.out.println("文件读取异常: " + exp.toString());
        }
    }

    /**
     * 切换待统计的文件
     */
    void setFileName(String name) {
        file = new File(name);
        try {
            sc = new Scanner(file);
            sc.useDelimiter(regex);
        } catch (IOException exp) {
            System.out.println("文件读取异常: " + exp.toString());
        }
    }

    /**
     * 执行单词统计：读取所有单词，分别存入 allWord 和 noSameWord
     */
    public void wordStatistic() {
        try {
            while (sc.hasNext()) {
                String word = sc.next();
                allWord.add(word);
                if (!noSameWord.contains(word))
                    noSameWord.add(word);
            }
        } catch (Exception e) {
            System.out.println("统计异常: " + e.toString());
        }
    }

    /** 获取所有单词列表 */
    public Vector<String> getAllWord() {
        return allWord;
    }

    /** 获取不重复单词列表 */
    public Vector<String> getNoSameWord() {
        return noSameWord;
    }
}
