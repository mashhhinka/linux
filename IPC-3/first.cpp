#include "shared_array.h"
#include <iostream>
#include <thread>

void worker(shared_array& arr) {
    size_t index = 0;
    while (true) {
        arr.write_to_array(index, index);
        std::cout << "First process wrote: " << index << std::endl;
        index = (index + 1) % arr.get_size();  // Use get_size() here
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    try {
        shared_array arr("shared_array_example", 100);
        worker(arr);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
