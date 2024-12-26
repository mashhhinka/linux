#include <iostream>
#include <csignal>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <ucontext.h>
#include <cstring>

void signal_handler(int signal, siginfo_t* info, void* context) {
    if (signal == SIGUSR1) {
        // Get the sender's PID and UID
        pid_t sender_pid = info->si_pid;
        uid_t sender_uid = info->si_uid;

        // Get the username of the sender
        struct passwd* pw = getpwuid(sender_uid);
        const char* username = pw ? pw->pw_name : "unknown";

        // Get the current values of the EIP, EAX, and EBX registers
        ucontext_t* ucontext = static_cast<ucontext_t*>(context);
#if defined(__x86_64__)
        uintptr_t eip = ucontext->uc_mcontext.gregs[REG_RIP];
        uintptr_t eax = ucontext->uc_mcontext.gregs[REG_RAX];
        uintptr_t ebx = ucontext->uc_mcontext.gregs[REG_RBX];
#elif defined(__i386__)
        uintptr_t eip = ucontext->uc_mcontext.gregs[REG_EIP];
        uintptr_t eax = ucontext->uc_mcontext.gregs[REG_EAX];
        uintptr_t ebx = ucontext->uc_mcontext.gregs[REG_EBX];
#else
        uintptr_t eip = 0, eax = 0, ebx = 0;
#endif

        // Print the signal information
        std::cout << "Received a SIGUSR1 signal from process " << sender_pid
                  << " executed by " << sender_uid << " (" << username << ").\n"
                  << "State of the context: EIP = " << std::hex << eip
                  << ", EAX = " << eax << ", EBX = " << ebx << std::dec << ".\n";
    }
}

int main() {
    // Print the PID of the process
    std::cout << "Process PID: " << getpid() << std::endl;

    // Setup signal handler for SIGUSR1
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_sigaction = signal_handler;
    sa.sa_flags = SA_SIGINFO;

    if (sigaction(SIGUSR1, &sa, nullptr) == -1) {
        perror("sigaction");
        return 1;
    }

    // Enter an infinite loop with sleeping
    while (true) {
        std::cout << "Waiting for signals..." << std::endl;
        sleep(10);
    }

    return 0;
}
