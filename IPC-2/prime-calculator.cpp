#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>

// Function to check if a number is prime
bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

// Function to find the m-th prime number
int getNthPrime(int m) {
    int count = 0;
    int num = 1;
    while (count < m) {
        ++num;
        if (isPrime(num)) {
            ++count;
        }
    }
    return num;
}

int main() {
    int pipe1[2], pipe2[2];

    // Create two pipes: one for parent-to-child communication, one for child-to-parent
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        std::cerr << "Pipe creation failed!" << std::endl;
        return 1;
    }

    // Create child process
    pid_t pid = fork();
    if (pid == -1) {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }

    if (pid == 0) {  // Child process
        close(pipe1[1]);  // Close write end of pipe1 (parent -> child)
        close(pipe2[0]);  // Close read end of pipe2 (child -> parent)

        int m;
        read(pipe1[0], &m, sizeof(m));  // Read m from parent
        close(pipe1[0]);  // Close read end of pipe1

        std::cout << "[Child] Calculating " << m << "-th prime number..." << std::endl;
        int prime = getNthPrime(m);

        write(pipe2[1], &prime, sizeof(prime));
        close(pipe2[1]);  // Close write end of pipe2

        std::cout << "[Child] Sending calculation result of prime(" << m << ")..." << std::endl;
        exit(0);  // Child process exits
    } else {  // Parent process
        close(pipe1[0]);  // Close read end of pipe1
        close(pipe2[1]);  // Close write end of pipe2

        int m;
        while (true) {
            std::cout << "[Parent] Please enter the number: ";
            std::cin >> m;

            if (std::cin.fail()) {
                std::string input;
                std::cin.clear();
                std::cin >> input;
                if (input == "exit") {
                    break;  // Exit the program
                } else {
                    std::cout << "Invalid input, please enter a valid number or 'exit' to quit." << std::endl;
                    continue;
                }
            }

            std::cout << "[Parent] Sending " << m << " to the child process..." << std::endl;
            write(pipe1[1], &m, sizeof(m));  // Send m to the child process

            std::cout << "[Parent] Waiting for the response from the child process..." << std::endl;
            int primeResult;
            read(pipe2[0], &primeResult, sizeof(primeResult));  // Read result from child
            std::cout << "[Parent] Received calculation result of prime(" << m << ") = " << primeResult << "..." << std::endl;
        }

        // Close remaining pipe ends and wait for child process to exit
        close(pipe1[1]);
        close(pipe2[0]);
        wait(nullptr);  // Wait for child to terminate
    }

    return 0;
}
