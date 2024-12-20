#include "mergesort.h"

#include <vector>
#include <functional>

template<typename T>
void mergesort(std::vector<T>& arr, std::function<bool(const T&, const T&)> compare){

    std::vector<T> aux(arr.size());
    _mergesort(arr, 0, (int)arr.size() - 1, aux, compare);
}

template<typename T>
void _mergesort(std::vector<T>& arr, int l, int r, std::vector<T>& aux, std::function<bool(const T&, const T&)> compare){
    if(l < r){
        int m = (l + r) / 2;
        _mergesort(arr, l, m, aux, compare);
        _mergesort(arr, m+1, r, aux, compare);
        merge(arr, l, m, r, aux, compare);
    }
}

template<typename T>
void merge(std::vector<T>& arr, int l, int m, int r, std::vector<T>& aux, std::function<bool(const T&, const T&)> compare){

    int l_cnt = l;
    int r_cnt = m+1;
    int g_cnt = l;

    while(l_cnt <= m && r_cnt <= r){
        if(compare(arr[l_cnt], arr[r_cnt]))
            aux[g_cnt++] = arr[l_cnt++];
        else
            aux[g_cnt++] = arr[r_cnt++];
    }

    while(l_cnt <= m)
        aux[g_cnt++] = arr[l_cnt++];
    while(r_cnt <= r)
        aux[g_cnt++] = arr[r_cnt++];

    g_cnt = l;
    while(g_cnt <= r){
        arr[g_cnt] = aux[g_cnt];
        g_cnt++;
    }

}
