#include "mergesort.h"
#include "mtmergesort.h"

#include <vector>
#include <functional>
#include <thread>
#include <cmath>

#define NUM_THREADS 8


template<typename T>
void merge_all(std::vector<T>& arr, std::vector<std::vector<T>>& sorted_segments, std::function<bool(const T&, const T&)> compare) {
    while (sorted_segments.size() > 1) {
        std::vector<std::vector<T>> temp_segments;

        // Merge pairs of segments
        for (size_t i = 0; i < sorted_segments.size(); i += 2) {
            if (i + 1 < sorted_segments.size()) {
                std::vector<T> merged;
                merge_two_segments(sorted_segments[i], sorted_segments[i + 1], merged, compare);
                temp_segments.push_back(merged);
            } else {
                // If it's an odd segment, just move it to the next round
                temp_segments.push_back(sorted_segments[i]);
            }
        }

        // Update the segments vector with merged segments
        sorted_segments.swap(temp_segments);
    }

    // If only one segment remains, it is the completely sorted array
    if (!sorted_segments.empty()) {
        arr.swap(sorted_segments[0]);
    }
}

template<typename T>
void merge_two_segments(const std::vector<T>& left, const std::vector<T>& right, std::vector<T>& merged, std::function<bool(const T&, const T&)> compare) {
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (compare(left[i], right[j])) {
            merged.push_back(left[i++]);
        } else {
            merged.push_back(right[j++]);
        }
    }
    while (i < left.size()) {
        merged.push_back(left[i++]);
    }
    while (j < right.size()) {
        merged.push_back(right[j++]);
    }
}

template<typename T>
void mtmergesort(std::vector<T>& arr, std::function<bool(const T&, const T&)> compare) {
    std::vector<T> aux(arr.size());
    std::vector<std::vector<T>> sorted_segments(NUM_THREADS);

    // Multithreaded sorting of each segment
    std::vector<std::thread> threads;
    int seg_size = arr.size() / NUM_THREADS;
    int extra = arr.size() % NUM_THREADS;

    int start = 0;
    for (int i = 0; i < NUM_THREADS; ++i) {
        int end = start + seg_size + (extra > 0 ? 1 : 0) - 1;
        if (extra > 0) --extra;

        threads.emplace_back([&, start, end, i]() {
            _mtmergesort(arr, start, end, aux, compare);
            sorted_segments[i] = std::vector<T>(arr.begin() + start, arr.begin() + end + 1);
        });

        start = end + 1;
    }

    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }

    // Merge all sorted segments into the final sorted array
    merge_all(arr, sorted_segments, compare);
}


template<typename T>
void _mtmergesort(std::vector<T>& arr, int l, int r, std::vector<T>& aux, std::function<bool(const T&, const T&)> compare){
    if(l < r){
        int m = (l + r) / 2;
        _mtmergesort(arr, l, m, aux, compare);
        _mtmergesort(arr, m+1, r, aux, compare);
        merge(arr, l, m, r, aux, compare);
    }
}
