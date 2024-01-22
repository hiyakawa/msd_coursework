import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

// prob 1
class TextAnalyzer {
    private static class Dict {
        private char letter_;
        private int counter_;

        Dict(char letter, int counter) {
            letter_ = letter;
            counter_ = counter;
        }
    }
    public static void parseFile(String file_name) {
        File file = new File(file_name);

        while (! file.exists() || file.isDirectory()) {
            System.out.println("File does not exist. Enter a valid file path:");
            Scanner s = new Scanner(System.in);
            file_name = s.next();
            file = new File(file_name);
        }

        try {
            Scanner fileReader = new Scanner(file);
            int[] counterList = new int[26];

            while (fileReader.hasNext()) {
                String line = fileReader.nextLine().toLowerCase();

                for (int i = 0; i < line.length(); i++) {
                    char cur_char = line.charAt(i);

                    if (cur_char >= 'a' && cur_char <= 'z') {
                        counterList[cur_char - 'a']++;
                    }
                }
            }

            Dict[] letterCountList = new Dict[26];

            for (int i = 0; i < counterList.length; i++) {
                letterCountList[i] = new Dict((char) ('a' + i), counterList[i]);
            }

            Arrays.sort(letterCountList, (c1, c2) -> (c2.counter_ - c1.counter_));
            for (Dict d : letterCountList) {
                System.out.println("Letter " + d.letter_ + " appears " + d.counter_ + " times");
            }
        }
        catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
}

// prob 2
class GuessNum {
    
}

// prob 3
class Calendar {
    public static void getWeekday() {
        System.out.println("Enter a day of the year:");
        Scanner sc = new Scanner(System.in);
        try {
            int inputDay = sc.nextInt();

            while (inputDay < 1 || inputDay > 365) {
                System.out.println("The day should be a positive integer between 1 and 365.");
                System.out.println("Enter a day of the year:");
                inputDay = sc.nextInt();
            }

            String[] weekdays = new String[] {"Monday", "Tuesday",
                    "Wednesday", "Thursday", "Friday", "Saturday"};
            System.out.println("The " + inputDay + "th day is " + weekdays[(inputDay + 6) % 7]);
        }
        catch (Exception e) {
            throw e;
        }
    }
}

public class Main {
    public static void main(String[] args) throws FileNotFoundException {
//        prob 1
//        String file_name = "/Users/laurazhang/myLocalGithubRepo/CS6011/Week2/Day10/Midterm/src/wireshark_lab.txt";
//        TextAnalyzer.parseFile(file_name);

//        prob 3
//        Calendar.getWeekday();
    }
}

/*
 prob 5.1
 * int  x = 130;
 * byte b = (byte)x;
 * System.out.println( b );
 * -126
 * int: 32 bits (4 bytes)
 * byte: 8 bits
 * 130 -> 0000...0000 1000 0010
 * -> 1000 0010 -> -128 + 2 -> 126
 *

 prob 5.2
 * Non-static field 'x' cannot be referenced from a static context

 */