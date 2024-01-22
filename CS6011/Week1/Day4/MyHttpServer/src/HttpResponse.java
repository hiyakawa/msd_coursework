import java.io.OutputStream;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.File;

public class HttpResponse {
    private static final int BUFFER_SIZE = 1024;

    HttpRequest request;
    OutputStream output;

    public HttpResponse(OutputStream output) {
        this.output = output;
    }

    public void setRequest(HttpRequest request) {
        this.request = request;
    }

    public void sendStaticResource() throws IOException {
        byte[] bytes = new byte[BUFFER_SIZE];
        FileInputStream inputFile = null;

        try {
            File file = new File(HttpServer.WEB_ROOT, request.getUri());

            if (file.exists()) {
                output.write(
                        ("HTTP/1.1 200\n"
                                + "Content-Type: text/html\n"
                                + "\n").getBytes()
                );

                inputFile = new FileInputStream(file);
                int ch = inputFile.read(bytes, 0, BUFFER_SIZE);

                while (ch != -1) {
                    output.write(bytes, 0, ch);
                    ch = inputFile.read(bytes, 0, BUFFER_SIZE);
                }

                output.flush();
                output.close();
            }
            else {
                // if the file is not found
                String result = "404 File Not Found";
                String errorMessage = "HTTP/1.1 "
                        + result + "\r\n"
                        + "Content-Type: text/html\r\n"
                        + "Content-Length: 23\r\n\r\n"
                        + "<h1>File Not Found</h1>";
                output.write(errorMessage.getBytes());
            }
        }
        // if cannot instantiate a File object
        catch (Exception e) {
            System.out.println(e);
        }
        finally {
            if (inputFile != null) {
                inputFile.close();
            }
        }
    }
}
