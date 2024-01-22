import javax.crypto.*;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.io.*;
import java.math.BigInteger;
import java.net.ServerSocket;
import java.net.Socket;
import java.security.*;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.spec.InvalidKeySpecException;

public class Server {
    private static ServerSocket serverSocket_;

    private static byte[] serverNonce_;
    private static byte[] signedDHPublicKey;

    private static BigInteger DHPublicKey_;
    private static BigInteger DHPrivateKey_;
    private static PrivateKey RSAPrivateKey_;

    private static Certificate signedServerCertificate_;

    private static SecretKeySpec serverEncrypt_;
    private static SecretKeySpec clientEncrypt_;
    private static SecretKeySpec serverMAC_;
    private static IvParameterSpec serverIV_;
    private static IvParameterSpec clientIV_;

    public Server() {
        try {
            serverSocket_ = new ServerSocket(8080);
            signedDHPublicKey = Helper.getSignedKey(RSAPrivateKey_, DHPublicKey_);
            DHPublicKey_ = Helper.getDHPublicKey(DHPrivateKey_);
            DHPrivateKey_ = new BigInteger(Integer.toString(new SecureRandom().nextInt()));
            RSAPrivateKey_ = Helper.getRSAPrivateKey("serverPrivateKey.der");
            signedServerCertificate_ = Helper.getCertificate("CASignedServerCertificate.pem");

        }
        catch (IOException | NoSuchAlgorithmException |
               InvalidKeySpecException | SignatureException |
               InvalidKeyException | CertificateException e) {
            e.printStackTrace();
        }
    }

    public void generateSecretKey(byte[] sharedSecretKey) throws NoSuchAlgorithmException, InvalidKeyException {
        final Mac HMAC = Mac.getInstance("HmacSHA256");
        byte[] prk = HMAC.doFinal(sharedSecretKey);

        SecretKeySpec secretKeySpec = new SecretKeySpec(serverNonce_, "HmacSHA256");
        HMAC.init(secretKeySpec);

        serverEncrypt_ = new SecretKeySpec(Helper.HKDFExpand(prk, "server encrypt"), "AES");
        clientEncrypt_ = new SecretKeySpec(Helper.HKDFExpand(serverEncrypt_.getEncoded(), "client encrypt"), "AES");
        serverMAC_ = new SecretKeySpec(Helper.HKDFExpand(clientEncrypt_.getEncoded(), "server MAC"), "AES");
        SecretKeySpec clientMAC_ = new SecretKeySpec(Helper.HKDFExpand(serverMAC_.getEncoded(), "client MAC"), "AES");
        serverIV_ = new IvParameterSpec(Helper.HKDFExpand(clientMAC_.getEncoded(), "server IV"));
        clientIV_ = new IvParameterSpec(Helper.HKDFExpand(serverIV_.getIV(), "client IV"));
    }

    public static void handShakeWithClient() {
        Server server = new Server();

        while(true) {
            try {
                Socket socket_ = serverSocket_.accept();

                ObjectOutputStream objectOutputStream = new ObjectOutputStream(socket_.getOutputStream());
                ObjectInputStream objectInputStream = new ObjectInputStream(socket_.getInputStream());

                ByteArrayOutputStream history = new ByteArrayOutputStream();
                serverNonce_ = (byte[]) objectInputStream.readObject();
                history.write(serverNonce_);

                objectOutputStream.flush();
                objectOutputStream.writeObject(signedServerCertificate_);
                objectOutputStream.writeObject(DHPublicKey_);
                objectOutputStream.writeObject(signedDHPublicKey);
                history.write(signedServerCertificate_.getEncoded());
                history.write(DHPublicKey_.toByteArray());
                history.write(signedDHPublicKey);

                Certificate clientCertificate;
                BigInteger clientDHPublicKey;
                byte[] clientSignedDHPublicKey;

                clientCertificate = (Certificate) objectInputStream.readObject();
                clientDHPublicKey = (BigInteger) objectInputStream.readObject();
                clientSignedDHPublicKey = (byte[]) objectInputStream.readObject();

                history.write(clientCertificate.getEncoded());
                history.write(clientDHPublicKey.toByteArray());
                history.write(clientSignedDHPublicKey);

                BigInteger secret = Helper.getDHSharedSecretKey(clientDHPublicKey, DHPrivateKey_);
                server.generateSecretKey(secret.toByteArray());

                byte[] message = Helper.HMAC(history.toByteArray(), serverMAC_);
                objectOutputStream.writeObject(message);
                history.write(message);

                byte[] inputFileBytes = new FileInputStream("test.txt").readAllBytes();
                byte[] hashedFileBytes = Helper.HMAC(inputFileBytes, serverEncrypt_);
                byte[] concatBytes = Helper.concatenate(inputFileBytes, hashedFileBytes);

                Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
                cipher.init(Cipher.ENCRYPT_MODE, serverEncrypt_, serverIV_);
                byte[] encryptedBytes = cipher.doFinal(concatBytes);
                objectOutputStream.writeObject(encryptedBytes);
                byte[] clientReceipt = (byte[]) objectInputStream.readObject();
                cipher.init(Cipher.DECRYPT_MODE, clientEncrypt_, clientIV_);
                byte[] decryptedReceipt = cipher.doFinal(clientReceipt);
                byte[] decryptedData = new byte[decryptedReceipt.length - 32];

                System.arraycopy(decryptedReceipt, 0, decryptedData, 0, decryptedReceipt.length - 32);

                FileOutputStream fileOutputStream = new FileOutputStream("clientReceiptDecrypted.txt");
                fileOutputStream.write(decryptedData);
                fileOutputStream.flush();
                fileOutputStream.close();

                objectOutputStream.flush();
                objectOutputStream.close();

                objectInputStream.close();
            }
            catch (Exception e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        handShakeWithClient();
    }
}
