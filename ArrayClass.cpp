#include <iostream>
#include <vector>
#include <mutex>
#include <thread>

class ArrayClass {
private:
    std::vector<std::vector<std::vector<int>>> array;
    std::mutex mtx;  // Mutex for synchronizing access

public:
    ArrayClass(int x, int y, int z) : array(x, std::vector<std::vector<int>>(y, std::vector<int>(z, 0))) {}

    // Set value in the array with mutex protection
    void set(int x, int y, int z, int value) {
        std::lock_guard<std::mutex> lock(mtx);  // Lock the mutex
        array[x][y][z] = value;
    }

    // Get value from the array with mutex protection
    int get(int x, int y, int z) {
        std::lock_guard<std::mutex> lock(mtx);  // Lock the mutex
        return array[x][y][z];
    }

};