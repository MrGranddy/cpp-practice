#ifndef MERGESORT_H
#define MERGESORT_H

#include <vector>
#include <functional>

template<typename T>
void mergesort(std::vector<T>& arr, std::function<bool(const T&, const T&)> compare = std::less<T>());
template<typename T>
void _mergesort(std::vector<T>& arr, int l, int r, std::vector<T>& aux, std::function<bool(const T&, const T&)> compare = std::less<T>());
template<typename T>
void merge(std::vector<T>& arr, int l, int m, int r, std::vector<T>& aux, std::function<bool(const T&, const T&)> compare = std::less<T>());

#include "mergesort.cpp"
#endif