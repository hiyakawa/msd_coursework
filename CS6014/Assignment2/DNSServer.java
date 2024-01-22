package MSDNS;

import java.io.IOException;
import java.net.*;
import java.util.ArrayList;

public class DNSServer {
    private DatagramSocket clientSocket_, googleSocket_;
    private DNSCache cache_;
    private boolean running_ = true;
    int googlePort_ = 53;
    int clientPort_ = 8053;

    public DNSServer() throws SocketException {
        cache_ = new DNSCache();
        googleSocket_ = new DatagramSocket(googlePort_);
        clientSocket_ = new DatagramSocket(clientPort_);
    }

    public void run() {
        while (running_) {
            byte[] buffer = new byte[512];
            DatagramPacket packet = new DatagramPacket(buffer, buffer.length);
            ArrayList<DNSRecord> outputAnswers = new ArrayList<>();

            try {
                clientSocket_.receive(packet);
                DNSMessage message = DNSMessage.decodeMessage(buffer);
                System.out.println("DNS Request Received.");

                for (DNSQuestion question : message.questions_) {
                    System.out.println("Client port: " + packet.getPort() +
                            " requesting " + DNSMessage.joinDomainName(question.qName_));

                    if (DNSCache.contains(question)) {
                        System.out.println("Answer found.");
                        DNSRecord answer = DNSCache.getRecord(question);
                        outputAnswers.add(answer);
                    }
                    else {
                        System.out.println("Answer not found.");
                        InetAddress googleAddress = InetAddress.getByName("8.8.8.8");
                        DatagramPacket outputPacket = new DatagramPacket(message.rawData_,
                                message.rawData_.length, googleAddress, googlePort_);
                        googleSocket_.send(outputPacket);

                        byte[] googleBuffer = new byte[512];
                        DatagramPacket googlePacket = new DatagramPacket(googleBuffer, googleBuffer.length);
                        googleSocket_.receive(googlePacket);
                        DNSMessage googleMessage = DNSMessage.decodeMessage(googleBuffer);

                        if (googleMessage.answers_.length != 0) {
                            DNSCache.addRecord(question, googleMessage.answers_[0]);
                            outputAnswers.add(googleMessage.answers_[0]);
                        }
                    }
                }

                DNSMessage response = DNSMessage.buildResponse(message,
                        outputAnswers.toArray(new DNSRecord[outputAnswers.size()]));
                byte[] responseBytes = response.toBytes();

                System.out.println("Sending response to client port: " + packet.getPort());
                DatagramPacket datagramPacket = new DatagramPacket(responseBytes,
                        responseBytes.length, packet.getAddress(), packet.getPort());
                clientSocket_.send(datagramPacket);

                System.out.println(message);
                System.out.println(response);
            }
            catch (IOException e) {
                e.printStackTrace();
            }
        }

        clientSocket_.close();
    }
}