#include "shelpers.hpp"

#include <iostream>
#include <vector>

int main() {
    system("clear");
    std::string line;

    while (std::getline(std::cin, line)) {
        std::vector<std::string> tokens = tokenize(line);
        std::vector<Command> commands = getCommands(tokens);
        std::vector<pid_t> pids;
        std::vector<pid_t> backgroundPids;
        int loc;

        for (int i = 0; i < commands.size(); i++) {
            Command command = commands[i];

            if (builtins(command) >= 0) {
                break;
            }

            pid_t cpid = fork();

            if (! command.background) {
                pids.push_back(cpid);
            }
            else {
                backgroundPids.push_back(cpid);
                std::cout << "Waiting for " << cpid << std::endl;
            }

            if (cpid == 0) {
                // child
                if (command.fdStdin != STDIN_FILENO) {
                    if (dup2(command.fdStdin, STDIN_FILENO) == -1) {
                        perror("dup2 input");
                        exit(1);
                    }
                }
                if (command.fdStdout != STDOUT_FILENO) {
                    if (dup2(command.fdStdout, STDOUT_FILENO) == -1) {
                        perror("dup2 output");
                        exit(1);
                    }
                }

                for (const Command& curCommand : commands) {
                    if (curCommand.fdStdin != STDIN_FILENO) {
                        close(curCommand.fdStdin);
                    }
                    if (curCommand.fdStdout != STDOUT_FILENO) {
                        close(curCommand.fdStdout);
                    }
                }

                if (execvp(command.exec.c_str(), const_cast<char *const *>(command.argv.data())) == -1) {
                    perror("execution");
                    exit(1);
                }
                exit(0);
            }
            else if (cpid < 0) {
                perror("fork");
                exit(1);
            }
        }

        for (const Command& curCommand : commands) {
            if (curCommand.fdStdin != STDIN_FILENO) {
                close(curCommand.fdStdin);
            }
            if (curCommand.fdStdout != STDOUT_FILENO) {
                close(curCommand.fdStdout);
            }
        }

        for (pid_t p : pids) {
            waitpid(p, &loc, WUNTRACED);

            if (loc < 0) {
                perror("waitpid");
                exit(1);
            }
        }
    }
}
