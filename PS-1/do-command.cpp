#include <iostream>
#include <vector>
#include <chrono>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void do_command(char** argv) {
    using namespace std::chrono;

    // Record start time
    auto start = high_resolution_clock::now();

    pid_t pid = fork();
    
    if (pid == -1) {
        // Error forking process
        std::cerr << "Failed to fork process." << std::endl;
        return;
    }
    
    if (pid == 0) {
        // Child process
        execvp(argv[0], argv);
        // If execvp fails, print error and exit
        std::cerr << "Error executing command: " << argv[0] << std::endl;
        exit(1);
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        
        // Record end time
        auto end = high_resolution_clock::now();
        duration<double> duration = end - start;

        // Print exit status
        if (WIFEXITED(status)) {
            std::cout << "Command completed with exit code " 
                      << WEXITSTATUS(status) << " and took "
                      << duration.count() << " seconds." << std::endl;
        } else {
            std::cout << "Command failed." << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./do-command <command> <args>..." << std::endl;
        return 1;
    }

    // Build the argument vector for the command
    std::vector<char*> args;
    for (int i = 1; i < argc; ++i) {
        args.push_back(argv[i]);
    }
    args.push_back(nullptr); // null-terminated

    // Call do_command to execute the command
    do_command(args.data());

    return 0;
}
