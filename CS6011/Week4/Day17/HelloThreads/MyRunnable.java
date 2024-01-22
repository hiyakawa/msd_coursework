public class MyRunnable implements Runnable {
    @Override
    public void run() {
//        int count = (int) (Thread.currentThread().getId() * 100);
        int count = 0;

        while (count <= 100) {
            if (count % 10 == 9) {
                System.out.println("");
            }

            System.out.print("Hello number " + count + " from thread number " + Thread.currentThread().getId() + "    ");
            count++;
        }

        System.out.println("\n");
    }
}
