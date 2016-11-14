import java.util.*;
public class median_of_integer {
    public static void main(String[] args) {
        String string;
        Scanner scanner = new Scanner(System.in);
        int[] buffer = new int[1001];
        int total = 0;
        while (scanner.hasNextLine() && !(string = scanner.nextLine()).equals("")) {
            int num = Integer.valueOf(string);
            total++;
            buffer[num]++;
            int count = 0;
            int temp = total / 2;
            int m1=-1,m2=-1, median=0;
            if (total % 2 == 1) {
                for (int i = 0; i <= 1000; ++i) {
                    count += buffer[i];
                    if (count < temp + 1) continue;
                    median = i;
                    break;
                }
            } else {
                for (int i = 0; i <= 1000; ++i) {
                    count += buffer[i];
                    if (count >= temp && m1 == -1) {
                        m1 = i;
                    }
                    if (count < temp + 1) continue;
                    m2 = i;
                    median = (m1 + m2) / 2;
                    break;
                }
            }
            System.out.println("median:" + median);
        }
        scanner.close();
    }
}
