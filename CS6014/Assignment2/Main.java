package MSDNS;

import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        DNSServer server = new DNSServer();

        System.out.println("Port: " + server.clientPort_);
        System.out.println("Listening for incoming DNS requests...");

        server.run();
    }
}