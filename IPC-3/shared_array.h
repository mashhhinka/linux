#ifndef SHARED_ARRAY_H
#define SHARED_ARRAY_H

#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <unistd.h>
#include <cstring>

class shared_array {
public:
    shared_array(const std::string& name, size_t size);
    ~shared_array();

    int& operator[](size_t index);
    void write_to_array(size_t index, int value);
    int read_from_array(size_t index) const;
    
    size_t get_size() const; // Getter for size

private:
    std::string name;
    size_t size;
    int* data;
    sem_t* sem;
    const char* sem_name;
    const char* shm_name;
};

#endif
