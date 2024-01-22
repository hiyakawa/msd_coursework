import java.io.InputStream;
import java.io.IOException;

public class HttpRequest {
    private final InputStream input;
    private String uri;

    public HttpRequest(InputStream inputStream) {
        input = inputStream;
    }

    public void parse() {
        StringBuffer request = new StringBuffer(2048);
        int i;
        byte[] buffer = new byte[2048];

        // read request from InputStream and get uri
        try {
            i = input.read(buffer);
        }
        catch (IOException e) {
            e.printStackTrace();
            i = -1;
        }

        // GET /index.html HTTP/1.1
        for (int j = 0; j < i; j++) {
            request.append((char) buffer[j]);
        }

        uri = parseUri(request.toString());
    }

    private String parseUri(String requestString) {
        int index1, index2;
        index1 = requestString.indexOf(' ');

        if (index1 != -1) {
            index2 = requestString.indexOf(' ', index1 + 1);

            if (index2 > index1) {
                return requestString.substring(index1 + 1, index2);
            }
        }
        return null;
    }

    public String getUri() {
        if (uri.equals("/")) {
            uri = "/index.html";
        }
        return uri;
    }
}
