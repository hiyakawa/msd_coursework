import java.util.Scanner;
import java.util.Random;

public class Main {
    public static void main(String[] args) {
        // saying hello
        System.out.println("Hello world from Java!");

        // create an array of 10 ints
        int[] myArray = new int[10];
        int sum = 0;

        // fill it with random values and print out each one
        for (int i = 0; i < 10; i++) {
            GenerateRandom gr = new GenerateRandom();
            myArray[i] = gr.GenerateRandom();
            System.out.println(myArray[i]);
            sum += myArray[i];
        }

        // print out the sum of the numbers in the array.
        System.out.println("The sum of the numbers in the array is " + sum);

        CheckAge result = new CheckAge();
        result.CheckAge();
    }
}

class GenerateRandom {
    public static int GenerateRandom() {
        Random rand = new Random();
        // generate random numbers between 0 and 100
        int upper_bound = 100;
        int int_random = rand.nextInt(upper_bound);
        return int_random;
    }
}

class CheckAge {
    public static void CheckAge() {
        System.out.println("Enter your age:");
        Scanner s = new Scanner(System.in);
        int users_age = s.nextInt();

        // keep prompting the user for their age if they enter negative numbers or zero
        while (users_age < 1 || users_age > 150) {
            System.out.println("Your age should be a positive integer between 1 and 150.");
            System.out.println("Enter your age again:");
            users_age = s.nextInt();
        }

        // check if the user is able to vote
        Boolean is_able_to_vote = false;

        if (users_age > 17) {
            is_able_to_vote = true;
        }

        // check which generation the user belongs to
        String generation = "";

        if (users_age > 80) {
            generation = "greatest generation";
        } else if (users_age > 60) {
            generation = "baby boomers";
        } else if (users_age > 40) {
            generation = "generation X";
        } else if (users_age > 20) {
            generation = "millennial";
        } else {
            generation = "iKid";
        }

        // print the results
        if (is_able_to_vote) {
            System.out.println("Congrats! You are able to vote.");
        } else {
            System.out.println("Sorry, you can only vote if you are over 18 years old.");
        }

        System.out.println("Your generation is " + generation + "!");
    }
}