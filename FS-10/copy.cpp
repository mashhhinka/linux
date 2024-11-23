#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Error: Please provide exactly two arguments: source and destination file paths.\n";
        return 1;
    }

    const char *source_path = argv[1];
    const char *destination_path = argv[2];

    int src_fd = open(source_path, O_RDONLY);
    if (src_fd == -1) {
        std::cerr << "Error: Could not open source file: " << strerror(errno) << "\n";
        return 1;
    }

    int dest_fd = open(destination_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        std::cerr << "Error: Could not open destination file: " << strerror(errno) << "\n";
        close(src_fd);
        return 1;
    }

    char buffer[4096];
    ssize_t total_copied = 0;
    ssize_t total_physical = 0;
    ssize_t total_holes = 0;

    while (true) {
        ssize_t bytes_read = read(src_fd, buffer, sizeof(buffer));
        if (bytes_read == 0) break;  
        if (bytes_read == -1) {
            std::cerr << "Error reading from source file: " << strerror(errno) << "\n";
            close(src_fd);
            close(dest_fd);
            return 1;
        }

        ssize_t bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written == -1) {
            std::cerr << "Error writing to destination file: " << strerror(errno) << "\n";
            close(src_fd);
            close(dest_fd);
            return 1;
        }

        total_copied += bytes_written;
        if (bytes_read < static_cast<ssize_t>(sizeof(buffer))) {
            total_holes += (sizeof(buffer) - bytes_read);
        } else {
            total_physical += bytes_written;
        }
    }

    close(src_fd);
    close(dest_fd);

    std::cout << "Successfully copied " << total_copied << " bytes (data: "
              << total_physical << ", hole: " << total_holes << ").\n";

    return 0;
}
