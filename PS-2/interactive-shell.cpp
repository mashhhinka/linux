#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>
#include <sstream> 

void executeCommand(const std::vector<std::string>& args, bool silent) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        // Temporarily modify PATH
        std::string currentDir = getcwd(nullptr, 0);
        std::string newPath = "PATH=" + currentDir + ":" + getenv("PATH");
        putenv(const_cast<char*>(newPath.c_str()));

        // Handle silent execution
        if (silent) {
            std::string logFile = std::to_string(getpid()) + ".log";
            int fd = open(logFile.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("Failed to open log file");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            close(fd);
        }

        // Convert args to char* array for execvp
        std::vector<char*> cArgs;
        for (const auto& arg : args) {
            cArgs.push_back(const_cast<char*>(arg.c_str()));
        }
        cArgs.push_back(nullptr);

        execvp(cArgs[0], cArgs.data());
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else { // Parent process
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            std::cout << "Process " << pid << " exited with code " << WEXITSTATUS(status) << std::endl;
        } else {
            std::cerr << "Process " << pid << " terminated abnormally" << std::endl;
        }
    }
}

int main() {
    std::string input;

    while (true) {
        std::cout << "$ ";
        std::getline(std::cin, input);

        if (input.empty()) {
            continue;
        }

        if (input == "exit") {
            break;
        }

        std::vector<std::string> args;
        std::istringstream iss(input);
        std::string token;
        bool silent = false;

        while (iss >> token) {
            if (token == "silent" && args.empty()) {

                silent = true;
            } else {
                args.push_back(token);
            }
        }

        if (!args.empty()) {
            executeCommand(args, silent);
        }
    }

    return 0;
}
