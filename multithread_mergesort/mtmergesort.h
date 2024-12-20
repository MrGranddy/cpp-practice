#ifndef MTMERGESORT_H
#define MTMERGESORT_H

#include <vector>
#include <functional>

template<typename T>
void mtmergesort(std::vector<T>& arr, std::function<bool(const T&, const T&)> compare = std::less<T>());
template<typename T>
void _mtmergesort(std::vector<T>& arr, int l, int r, std::vector<T>& aux, std::function<bool(const T&, const T&)> compare);
template<typename T>
void merge_two_segments(const std::vector<T>& left, const std::vector<T>& right, std::vector<T>& merged, std::function<bool(const T&, const T&)> compare);
template<typename T>
void merge_all(std::vector<T>& arr, std::vector<std::vector<T>>& sorted_segments, std::function<bool(const T&, const T&)> compare);

#include "mtmergesort.cpp"
#endif