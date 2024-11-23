#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    const char *file_path = argv[1];
    
    int fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    int fd2 = dup(fd);
    if (fd2 == -1) {
        perror("Error duplicating file descriptor");
        close(fd);
        return 1;
    }

    const char* first_line = "first line\n";
    if (write(fd, first_line, std::strlen(first_line)) == -1) {
        perror("Error writing to file");
        close(fd);
        close(fd2);
        return 1;
    }

    const char* second_line = "second line\n";
    if (write(fd2, second_line, std::strlen(second_line)) == -1) {
        perror("Error writing to file");
        close(fd);
        close(fd2);
        return 1;
    }

    close(fd);
    close(fd2);

    return 0;
}
