#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>

void secure_delete(const char* filepath) {
    int fd = open(filepath, O_WRONLY);
    if (fd == -1) {
        std::cerr << "Error opening file: " << strerror(errno) << std::endl;
        return;
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        std::cerr << "Error getting file size: " << strerror(errno) << std::endl;
        close(fd);
        return;
    }

    off_t file_size = st.st_size;
    char null_char = '\0';

    for (off_t i = 0; i < file_size; ++i) {
        if (write(fd, &null_char, 1) != 1) {
            std::cerr << "Error overwriting file: " << strerror(errno) << std::endl;
            close(fd);
            return;
        }
    }

    close(fd);

    if (unlink(filepath) == -1) {
        std::cerr << "Error deleting file: " << strerror(errno) << std::endl;
        return;
    }

    std::cout << "File securely deleted: " << filepath << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <file-path>" << std::endl;
        return 1;
    }

    const char* filepath = argv[1];

    struct stat st;
    if (stat(filepath, &st) == -1) {
        std::cerr << "File does not exist or invalid path: " << strerror(errno) << std::endl;
        return 1;
    }

    secure_delete(filepath);

    return 0;
}
