#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <functional>

#include "mergesort.h"
#include "mtmergesort.h"

// Function to print array elements
void printArray(const std::vector<int>& arr) {
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

// Function to fill array with random integers
void generateRandomArray(std::vector<int>& arr, int size) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 1000);

    for (int i = 0; i < size; ++i) {
        arr[i] = distrib(gen);
    }
}

// Function to check if the array is sorted correctly
template<typename T>
bool isSorted(const std::vector<T>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    int size;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    std::vector<int> arr(size);
    generateRandomArray(arr, size);

    std::vector<int> arr_copy = arr; // Copy for the second sort to use the same input

    using namespace std::chrono;
    steady_clock::time_point begin, end;

    bool sortSuccessful = true;
    bool sortSuccessfulmt = true;

    begin = steady_clock::now();
    mergesort(arr);
    end = steady_clock::now();
    sortSuccessful = isSorted(arr);
    std::cout << "Mergesort completed in " << duration_cast<microseconds>(end - begin).count() << " microseconds.\n";

    begin = steady_clock::now();
    // Uncomment and define `mtmergesort` to use it
    mtmergesort(arr_copy);
    end = steady_clock::now();
    sortSuccessfulmt = isSorted(arr_copy);
    std::cout << "Multithreaded Mergesort completed in " << duration_cast<microseconds>(end - begin).count() << " microseconds.\n";


    std::cout << "Sorting successful: " << (sortSuccessful ? "Yes" : "No") << "\n";
    std::cout << "Sorting successful (multithreaded): " << (sortSuccessfulmt ? "Yes" : "No") << "\n";

    std::cout << "Standard mergesort result:" << std::endl;
    printArray(arr);

    std::cout << "Multithreaded mergesort result:" << std::endl;
    printArray(arr_copy);

    return 0;
}
