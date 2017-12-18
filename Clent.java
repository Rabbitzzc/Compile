import java.io.*;
import java.util.regex.Pattern;

public class Clent {
    public static int[] ArrNum = new int[100];
    public static String ArrString = "";
    public static boolean flag = false;
    public static int index = 0;
    public static void main(String[] args) throws IOException {

        ReadArr();
        System.out.println("分析语句为： " + ArrString + "\n");
        System.out.println("开始进行分析");
        E();
        System.out.print("分析结束，返回结果为： ");
        if(flag) {
            System.out.println("语句正确");
        } else {
            System.out.println("语句错误");
        }
        //System.out.println(ArrNum.length);
    }

    // 读取文件函数-分理出数组
    public static void ReadArr() throws IOException {
        try {
            String pathname = "C:\\Users\\zhouzhechao\\Desktop\\Code\\result.txt";
            File filename = new File(pathname); // 要读取以上路径的input。txt文件
            InputStreamReader reader = new InputStreamReader(
                    new FileInputStream(filename)); // 建立一个输入流对象reader
            BufferedReader br = new BufferedReader(reader); // 建立一个对象，它把文件内容转成计算机能读懂的语言
            String line = "";
            line = br.readLine();

            int i = 0;
            while (line != null) {
                Pattern regex = Pattern.compile("\\d+$");
                ArrString += line.split("   ")[0] + " ";
                ArrNum[i] = Integer.parseInt(line.split("   ")[1]); // 将字符串变为数字
                i++;
                line = br.readLine(); // 一次读入一行数据
            }

        } catch (Exception e) {
            System.out.println("读取错误");
        }
    }
    public static void E() {
        if(ArrNum[index] == 1) {
            index++;
            T();
            if(ArrNum[index] == 6) {
                index++;
                if(ArrNum[index] == 0) {
                    flag = true;
                } else {
                    System.out.println("#缺失，请确认!!!");
                }
            } else {
                System.out.println("end缺失，请确认!!!");
            }
        } else {
            System.out.println("begin缺失，请确认!!!");
        }
    }

    private static void T() {
        //boolean boo = true;
        X();

        if(ArrNum[index] == 26) {
            index++;
            T();
        }


    }

    private static void X() {
        F();
    }

    private static void F() {
        if(ArrNum[index] == 10) {
            index++;
            if(ArrNum[index] == 18) {
                index++;
                B();
            }
        }
    }

    private static void B() {
        C();
        if(ArrNum[index] == 13) { // +分析
            index++;
            B();
        } else if(ArrNum[index] == 14) { // -分析
            index++;
            B();
        }
    }

    private static void C() {
        Y();
        if(ArrNum[index] == 15) { // * 分析
            index++;
            C();
        } else if(ArrNum[index] == 16) { // /分析
            index++;
            C();
        }
    }

    private static void Y() {
        if(ArrNum[index] == 10) {
            index++;
        } else if(ArrNum[index] == 11) {
            index++;
        } else {
            B();
        }
    }
}
