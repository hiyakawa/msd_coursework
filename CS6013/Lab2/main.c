#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // set up the pipe
    char buff;
    int p[2];

    // exit the program if argc is not proper
    if (argc != 2) {
        perror("Invalid input\n");
        exit(1);
    }

    if (pipe(p) < 0) {
        perror("Pipe failed\n");
        exit(1);
    }

    pid_t rc = fork();

    // exit the program if fork failed
    if (rc < 0) {
        perror("Fork failed\n");
        exit(1);
    }

    // child (new process)
    if (rc == 0) {
        printf("hello from child\n");
        // close write end
        close(p[1]);

        // print argv[1]
        while (read(p[0], &buff, 1) > 0) {
            write(STDOUT_FILENO, &buff, 1);
        }

        write(STDOUT_FILENO, "\n", 1);

        // close read end
        close(p[0]);
    }
    else {
        printf("hello from parent\n");
        // close read end
        close(p[0]);

        // send argv[1] and its length to the child
        write(p[1], argv[1], strlen(argv[1]));

        // close write end
        close(p[1]);

        // wait for the child process to exit
        waitpid(0, NULL, 0);
    }

    return 0;
}