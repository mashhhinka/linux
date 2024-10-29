#include <iostream> 
#include <fstream> 
#include <unistd.h>   
#include <fcntl.h>   
#include <string.h>  
#include <cerrno>    
 
void initialize(int argc, char** argv) 
{ 
    if (argc < 2) { 
        std::cerr << "Error: No input file provided." << std::endl; 
        exit(1); 
    } 
 
    int file_fd = open(argv[1], O_RDONLY); 
    if (file_fd < 0) { 
        std::cerr << "Error: Cannot open file '" << argv[1] << "': " << strerror(errno) << std::endl; 
        exit(1); 
    } 
 
    if (dup2(file_fd, STDIN_FILENO) < 0) { 
        std::cerr << "Error: Cannot redirect stdin: " << strerror(errno) << std::endl; 
        close(file_fd); 
        exit(1); 
    } 
 
    close(file_fd); 
} 
 
int main(int argc, char** argv) 
{ 
    initialize(argc, argv); 
 
    std::string input; 
    std::cin >> input; 
 
    std::string reversed(input.rbegin(), input.rend()); 
 
    std::cout << reversed << std::endl; 
 
    return 0; 
}
