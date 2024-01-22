package MSDNS;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;

public class DNSMessage {
    DNSHeader header_ = new DNSHeader();
    DNSQuestion[] questions_;
    DNSRecord[] answers_, authorityRecords_, additionalRecords_;
    byte[] rawData_;

    /**
     * @return decoded message
     */
    public static DNSMessage decodeMessage(byte[] bytes) throws IOException {
        DNSMessage message = new DNSMessage();
        ByteArrayInputStream byteArrayInputStream = new ByteArrayInputStream(bytes);

        message.rawData_ = bytes;
        message.header_ = DNSHeader.decodeHeader(byteArrayInputStream);
        message.questions_ = new DNSQuestion[message.header_.qdCount_];

        for (int i = 0; i < message.questions_.length; i++) {
            message.questions_[i] = DNSQuestion.decodeQuestion(byteArrayInputStream, message);
        }

        message.answers_ = new DNSRecord[message.header_.anCount_];

        for (int i = 0; i < message.answers_.length; i++) {
            message.answers_[i] = DNSRecord.decodeRecord(byteArrayInputStream, message);
        }

        message.authorityRecords_ = new DNSRecord[message.header_.nsCount_];

        for (int i = 0; i < message.authorityRecords_.length; i++) {
            message.authorityRecords_[i] = DNSRecord.decodeRecord(byteArrayInputStream, message);
        }

        message.additionalRecords_ = new DNSRecord[message.header_.arCount_];

        for (int i = 0; i < message.additionalRecords_.length; i++) {
            message.additionalRecords_[i] = DNSRecord.decodeRecord(byteArrayInputStream, message);
        }

        return message;
    }

    /**
     * read the pieces of a domain name starting from the current position of the input stream
     * @return domain
     */
    public String[] readDomainName(InputStream inputStream) throws IOException {
        ArrayList<String> sections = new ArrayList<>();

        while (true) {
            byte length = (byte) inputStream.read();

            if (length < 0) {
                int mask = 0x3F;
                length = (byte) (length & mask);
                length = (byte) (length << 8);
                length = (byte) (length | inputStream.read());

                return readDomainName(length);
            }

            if (length == 0) {
                break;
            }

            String section = "";

            for (int i = 0; i < length; i++) {
                section += (char) inputStream.read();
            }

            sections.add(section);
        }

        String[] domain = new String[sections.size()];

        for (int i = 0; i < domain.length; i++) {
            domain[i] = sections.get(i);
        }

        return domain;
    }

    /**
     * when there's compression, and we need to find the domain from earlier in the message
     * @return domain name
     */
    public String[] readDomainName(int firstByte) throws IOException {
        ByteArrayInputStream byteArrayInputStream = new ByteArrayInputStream(rawData_);
        byteArrayInputStream.skip(firstByte);

        return readDomainName(byteArrayInputStream);
    }

    /**
     * build a response based on the request and the answers you intend to send back
     * @return response
     */
    public static DNSMessage buildResponse(DNSMessage request, DNSRecord[] answers) {
        DNSMessage response = new DNSMessage();

        response.questions_ = request.questions_;
        response.answers_ = answers;
        response.authorityRecords_ = request.authorityRecords_;
        response.additionalRecords_ = request.additionalRecords_;
        response.header_ = DNSHeader.buildHeaderForResponse(request, response);

        return response;
    }

    /**
     * get the bytes to put in a packet and send back
     */
    public byte[] toBytes() throws IOException {
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
        HashMap<String, Integer> dnLocations = new HashMap<>();
        header_.writeBytes(byteArrayOutputStream);

        for (DNSQuestion curQuestion : questions_) {
            curQuestion.writeBytes(byteArrayOutputStream, dnLocations);
        }
        for (DNSRecord curRecord : answers_) {
            curRecord.writeBytes(byteArrayOutputStream, dnLocations);
        }
        for (DNSRecord curRecord : authorityRecords_) {
            curRecord.writeBytes(byteArrayOutputStream, dnLocations);
        }
        for (DNSRecord curRecord : additionalRecords_) {
            curRecord.writeBytes(byteArrayOutputStream, dnLocations);
        }

        return byteArrayOutputStream.toByteArray();
    }

    /**
     * If this is the first time we've seen this domain name in the packet, write
     * it using the DNS encoding (each segment of the domain prefixed with its
     * length, 0 at the end), and add it to the hash map.
     * Otherwise, write a back pointer to where the domain has been seen previously.
     */
    public static void writeDomainName(ByteArrayOutputStream byteArrayOutputStream,
                                       HashMap<String, Integer> domainLocations,
                                       String[] domainPieces) {
        String domainName = joinDomainName(domainPieces);

        if (domainLocations.containsKey(domainName)) {
            int pointer = domainLocations.get(domainName);
            byte secondByte = (byte) pointer;
            pointer = pointer >> 8;
            byte firstByte = (byte) pointer;
            byte mask = (byte) 0xC0;
            firstByte = (byte) (firstByte | mask);
            byteArrayOutputStream.write(firstByte);
            byteArrayOutputStream.write(secondByte);
        }
        else {
            domainLocations.put(domainName, byteArrayOutputStream.size());

            for (int i = 0; i < domainPieces.length; i++) {
                byteArrayOutputStream.write(domainPieces[i].length());

                for (char c : domainPieces[i].toCharArray()) {
                    byteArrayOutputStream.write(c);
                }
            }

            byteArrayOutputStream.write(0);
        }
    }

    /**
     * join the pieces of a domain name with dots
     */
    public static String joinDomainName(String[] pieces) {
        String domainName = "";

        for (int i = 0; i < pieces.length; i++) {
            domainName += pieces[i];

            if (i < pieces.length - 1) {
                domainName += ".";
            }
        }

        return domainName;
    }

    /**
     * autogenerated by IDE
     * @return a human-readable string version of a header object
     */
    @Override
    public String toString() {
        return "DNSMessage{" + "header=" + header_ + ", questions=" +
                Arrays.toString(questions_) + ", answers=" + Arrays.toString(answers_) +
                ", nsRecords=" + Arrays.toString(authorityRecords_) + ", additionalRecords=" +
                Arrays.toString(additionalRecords_) + '}';
    }

    public static int getOneBit(int inputByte, int bitIndex) {
        return (inputByte >> (7 - bitIndex)) & 1;
    }

    public static byte[] intToByteArray(int num) {
        byte[] bytes = new byte [2];
        bytes[0] = (byte) (num >> 8 & 0xff);
        bytes[1] = (byte) (num & 0xff);

        return bytes;
    }

    public static int getByteGroup(int num, ByteArrayInputStream byteArrayInputStream) {
        int result = 0;

        for (int i = num - 1; i >= 0; i--) {
            int temp = byteArrayInputStream.read();
            temp = temp << (8 * i);
            result = result | temp;
        }

        return result;
    }
}
