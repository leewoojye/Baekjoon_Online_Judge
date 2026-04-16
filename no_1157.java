import java.util.Scanner;

// no.1157
public class no_1157 {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    int[] alphabet = new int[26];
    for (int i = 0; i < 26; ++i) {
      alphabet[i] = 0;
    }
    String input = scanner.nextLine();
    input = input.toUpperCase();
    for (int i = 0; i < input.length(); ++i) {
      alphabet[input.charAt(i) - 'A']++;
    }
    int index = 0;
    boolean flag = false;
    for (int i = 0; i < 26; ++i) {
      if (alphabet[index] < alphabet[i]) {
        index = i;
        flag = false;
      } else if (alphabet[index] == alphabet[i] && index != i) {
        flag = true;
      }
    }
    if (!flag) {
      System.out.println((char) (index + 'A'));
    } else {
      System.out.println("?");
    }
    scanner.close();
  }
}
