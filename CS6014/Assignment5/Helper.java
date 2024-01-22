import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import java.io.*;
import java.math.BigInteger;
import java.security.*;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.PKCS8EncodedKeySpec;
import java.util.Random;

public class Helper {
    private static final BigInteger K = new BigInteger(2048, new Random());
    private static final BigInteger N = new BigInteger(2048, new Random());

    public static BigInteger getDHPublicKey(BigInteger K) {
        return Helper.K.modPow(K, N);
    }

    public static BigInteger getDHSharedSecretKey(BigInteger DHKey, BigInteger privateKey) {
        return DHKey.modPow(privateKey, N);
    }

    public static PrivateKey getRSAPrivateKey(String filename) throws IOException, NoSuchAlgorithmException, InvalidKeySpecException {
        InputStream file = new FileInputStream(filename);
        PKCS8EncodedKeySpec keySpec = new PKCS8EncodedKeySpec(file.readAllBytes());
        KeyFactory keyFactory = KeyFactory.getInstance("RSA");

        return keyFactory.generatePrivate(keySpec);
    }

    public static byte[] getSignedKey(PrivateKey rsaPrivateKey, BigInteger dhPublicKey) throws NoSuchAlgorithmException, InvalidKeyException, SignatureException {
        Signature signature = Signature.getInstance("SHA256WithRSA");
        signature.initSign(rsaPrivateKey);
        signature.update(dhPublicKey.toByteArray());

        return signature.sign();
    }

    public static Certificate getCertificate(String filename) throws CertificateException, FileNotFoundException {
        CertificateFactory certificateFactory = CertificateFactory.getInstance("X.509");
        InputStream file = new FileInputStream(filename);

        return certificateFactory.generateCertificate(file);
    }

    public static Boolean verifyCertificate(Certificate certificate) throws FileNotFoundException, CertificateException {
        Certificate CaCertificate = getCertificate("CAcertificate.pem");

        try {
            certificate.verify(CaCertificate.getPublicKey());

            return true;
        }
        catch (NoSuchAlgorithmException | InvalidKeyException | NoSuchProviderException | SignatureException e) {
            e.printStackTrace();
        }

        return false;
    }

    public static boolean verifyHost(Certificate clientCert, BigInteger clientDHPublicKey, byte[] clientSignedDHPublicKey) throws FileNotFoundException, CertificateException, NoSuchAlgorithmException, InvalidKeyException, SignatureException {
        if (! verifyCertificate(clientCert)) {
            return false;
        }

        Signature signature = Signature.getInstance("SHA256WithRSA");
        signature.initVerify(clientCert);
        signature.update(clientDHPublicKey.toByteArray());

        return signature.verify(clientSignedDHPublicKey);
    }

    public static byte[] HKDFExpand(byte[] input, String tag) throws NoSuchAlgorithmException, InvalidKeyException {
        byte[] tags = new byte[tag.getBytes().length + 1];
        byte[] temp = tag.getBytes();

        System.arraycopy(temp, 0, tags, 0, tags.length - 1);
        tags[tags.length - 1] = 1;

        final Mac HMAC = Mac.getInstance("HmacSHA256");
        SecretKeySpec secretKeySpec = new SecretKeySpec(input, "HmacSHA256");
        HMAC.init(secretKeySpec);

        byte[] okm = HMAC.doFinal(tags);
        byte[] result = new byte[16];

        System.arraycopy(okm, 0, result, 0, result.length);

        return result;
    }

    public static byte[] HMAC(byte[] message, SecretKeySpec MAC) throws NoSuchAlgorithmException, InvalidKeyException {
        Mac HMAC = Mac.getInstance("HmacSHA256");
        HMAC.init(MAC);

        return HMAC.doFinal(message);
    }

    public static byte[] concatenate(byte[] array1, byte[] array2) {
        int n = array1.length + array2.length;
        byte[] result = new byte[n];

        for (int i = 0; i < n; i++) {
            if (i < array1.length) {
                result[i] = array1[i];
            }
            else {
                result[i] = array2[i - array1.length];
            }
        }

        return result;
    }

    public static byte[] getNonceObject() {
        byte[] nonce = new byte[32];
        new SecureRandom().nextBytes(nonce);

        return nonce;
    }
}
