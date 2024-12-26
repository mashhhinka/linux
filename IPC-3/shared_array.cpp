#include "shared_array.h"

shared_array::shared_array(const std::string& name, size_t size)
    : name(name), size(size) {

    // Create a unique semaphore name
    sem_name = (name + "_sem").c_str();
    shm_name = (name + "_shm").c_str();

    // Open the semaphore (creating it if necessary)
    sem = sem_open(sem_name, O_CREAT | O_EXCL, 0644, 1);
    if (sem == SEM_FAILED) {
        throw std::runtime_error("Failed to create semaphore");
    }

    // Create the shared memory object
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        throw std::runtime_error("Failed to create shared memory object");
    }

    // Set the size of the shared memory object
    if (ftruncate(shm_fd, size * sizeof(int)) == -1) {
        throw std::runtime_error("Failed to set size of shared memory object");
    }

    // Map the shared memory object into the address space
    data = (int*) mmap(nullptr, size * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (data == MAP_FAILED) {
        throw std::runtime_error("Failed to map shared memory object");
    }

    close(shm_fd); // Close the file descriptor for the shared memory object
}

shared_array::~shared_array() {
    if (data != nullptr) {
        munmap(data, size * sizeof(int)); // Unmap the shared memory
    }
    if (sem != SEM_FAILED) {
        sem_close(sem); // Close the semaphore
        sem_unlink(sem_name); // Unlink the semaphore
    }
    shm_unlink(shm_name); // Unlink the shared memory object
}

int& shared_array::operator[](size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

void shared_array::write_to_array(size_t index, int value) {
    sem_wait(sem); // Wait (enter critical section)
    if (index < size) {
        data[index] = value;
    }
    sem_post(sem); // Signal (exit critical section)
}

int shared_array::read_from_array(size_t index) const {
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

size_t shared_array::get_size() const {
    return size;
}
