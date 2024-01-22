public class Main {
    public static int answer_ = 0;

    public static void sayHello() throws InterruptedException {
        int threadSize = 10;

        Thread[] myThreads = new Thread[threadSize];

        for (int i = 0; i < threadSize; i++) {
            MyRunnable runnable = new MyRunnable();
            Thread myThread = new Thread(runnable);
            myThread.start();
            myThreads[i] = myThread;
        }

        for (int j = 0; j < myThreads.length; j++) {
            myThreads[j].join();
        }
    }

    public static void badSum() throws InterruptedException {
        int maxValue = 100;

        Thread[] myThreads = new Thread[10];
        int numThreads = myThreads.length;
        for (int i = 0; i < numThreads; i++) {
            final int finalI = i;

            // make a thread that uses finalI inside it's runnable
            Thread thread = new Thread(() -> {
                for (int j = (finalI * maxValue / numThreads);
                     j < Math.min((finalI + 1) * maxValue / numThreads, maxValue);
                     j++) {
                    answer_ += j;
                }
            });

            myThreads[i] = thread;
            myThreads[i].start();
        }

        for (Thread myThread : myThreads) {
            myThread.join();
        }

        int correctAnswer = maxValue * (maxValue - 1) / 2;
        System.out.println("Correct answer: " + correctAnswer);
        System.out.println("Bad answer: " + answer_);
    }

    public static void main(String[] args) throws InterruptedException {
        sayHello();
        /*
         * Q: Do all the threads run in order?
         * A: No!
         *
         * Q: Does the same thread always print the 1st hello? The last hello?
         * A: No...?
         */

        badSum();
        /*
         * Q: Try setting maxValue to 100. Run you program multiple times. What do you see? Why?
         * A: The bad answer is always equal to the correct answer.
         */
    }
}