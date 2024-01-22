import javax.crypto.Cipher;
import javax.crypto.Mac;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.io.*;
import java.math.BigInteger;
import java.net.Socket;
import java.security.*;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.spec.InvalidKeySpecException;
import java.util.Arrays;

public class Client {
    private static Socket socket_;

    private static byte[] clientNonce_;
    private static byte[] signedDHPublicKey_;

    private static BigInteger DHPublicKey_;
    private static BigInteger DHPrivateKey_;
    private static PrivateKey RSAPrivateKey_;

    private static Certificate signedClientCertificate_;

    private static SecretKeySpec serverEncrypt_;
    private static SecretKeySpec clientEncrypt_;
    private static SecretKeySpec serverMAC_;
    private static SecretKeySpec clientMAC_;
    private static IvParameterSpec serverIV_;
    private static IvParameterSpec clientIV_;

    public Client() {
        try {
            socket_ = new Socket("127.0.0.1", 8080);
            clientNonce_ = Helper.getNonceObject();
            signedDHPublicKey_ = Helper.getSignedKey(RSAPrivateKey_, DHPublicKey_);
            DHPublicKey_ = Helper.getDHPublicKey(DHPrivateKey_);
            DHPrivateKey_ = new BigInteger(Integer.toString(new SecureRandom().nextInt()));
            RSAPrivateKey_ = Helper.getRSAPrivateKey("clientPrivateKey.der");
            signedClientCertificate_ = Helper.getCertificate("CASignedClientCertificate.pem");
        }
        catch (IOException | NoSuchAlgorithmException |
               CertificateException | InvalidKeySpecException |
               InvalidKeyException | SignatureException e) {
            e.printStackTrace();
        }
    }

    public void generateSecretKey(byte[] sharedSecretKey) throws NoSuchAlgorithmException, InvalidKeyException {
        final Mac HMAC = Mac.getInstance("HmacSHA256");
        byte[] prk = HMAC.doFinal(sharedSecretKey);

        SecretKeySpec secretKeySpec = new SecretKeySpec(clientNonce_, "HmacSHA256");
        HMAC.init(secretKeySpec);

        serverEncrypt_ = new SecretKeySpec(Helper.HKDFExpand(prk, "server encrypt"), "AES");
        clientEncrypt_ = new SecretKeySpec(Helper.HKDFExpand(serverEncrypt_.getEncoded(), "client encrypt"), "AES");

        serverMAC_ = new SecretKeySpec(Helper.HKDFExpand(clientEncrypt_.getEncoded(), "server MAC"), "AES");
        clientMAC_ = new SecretKeySpec(Helper.HKDFExpand(serverMAC_.getEncoded(), "client MAC"), "AES");

        serverIV_ = new IvParameterSpec(Helper.HKDFExpand(clientMAC_.getEncoded(), "server IV"));
        clientIV_ = new IvParameterSpec(Helper.HKDFExpand(serverIV_.getIV(), "client IV"));
    }

    private static void handshakeWithServer() {
        try {
            Client client = new Client();

            ObjectInputStream objectInputStream = new ObjectInputStream(socket_.getInputStream());
            ObjectOutputStream objectOutputStream = new ObjectOutputStream(socket_.getOutputStream());

            ByteArrayOutputStream history = new ByteArrayOutputStream();

            objectOutputStream.flush();
            objectOutputStream.writeObject(clientNonce_);
            history.write(clientNonce_);

            Certificate serverCertificate;
            BigInteger serverDHPublicKey;
            byte[] serverSignedDHPublicKey;

            serverCertificate = (Certificate) objectInputStream.readObject();
            serverDHPublicKey = (BigInteger) objectInputStream.readObject();
            serverSignedDHPublicKey = (byte[]) objectInputStream.readObject();

            history.write(serverCertificate.getEncoded());
            history.write(serverDHPublicKey.toByteArray());
            history.write(serverSignedDHPublicKey);

            objectOutputStream.writeObject(signedClientCertificate_);
            objectOutputStream.writeObject(DHPublicKey_);
            objectOutputStream.writeObject(signedDHPublicKey_);
            history.write(signedClientCertificate_.getEncoded());
            history.write(DHPublicKey_.toByteArray());
            history.write(signedDHPublicKey_);

            if (! Helper.verifyHost(serverCertificate, serverDHPublicKey, serverSignedDHPublicKey)) {
                System.exit(1);
            }

            BigInteger secret = Helper.getDHSharedSecretKey(serverDHPublicKey, DHPrivateKey_);
            client.generateSecretKey(secret.toByteArray());

            byte[] serverHistory = (byte[]) objectInputStream.readObject();
            byte[] clientHistory = Helper.HMAC(history.toByteArray(), serverMAC_);

            if (! Arrays.equals(clientHistory, serverHistory)) {
                System.exit(1);
            }

            history.write(serverHistory);
            byte[] message = Helper.HMAC(history.toByteArray(), clientMAC_);
            objectOutputStream.writeObject(message);

            byte[] encryptedData = (byte[]) objectInputStream.readObject();
            FileOutputStream fileOutputStream = new FileOutputStream("index.txt");
            fileOutputStream.write(encryptedData);
            fileOutputStream.flush();
            fileOutputStream.close();

            Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
            cipher.init(Cipher.DECRYPT_MODE, serverEncrypt_, serverIV_);
            byte[] decryptedData = cipher.doFinal(encryptedData);

            fileOutputStream = new FileOutputStream("decrypted.txt");
            fileOutputStream.write(decryptedData);
            fileOutputStream.flush();
            fileOutputStream.close();

            String response = "file received";
            cipher.init(Cipher.ENCRYPT_MODE, clientEncrypt_, clientIV_);
            byte[] hashedResponseBytes = Helper.HMAC(response.getBytes(), clientEncrypt_);
            byte[] concatBytes = Helper.concatenate(response.getBytes(), hashedResponseBytes);
            objectOutputStream.writeObject(cipher.doFinal(concatBytes));
            objectOutputStream.flush();
            objectOutputStream.close();

            objectInputStream.close();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        handshakeWithServer();
    }
}
