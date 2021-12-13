//
// Created by miko on 2021/12/13.
//
#include <iostream>
#include <unordered_map>
#include <string>
#include <iostream>
#include <chrono>
#include <charconv>
#include <sstream>
#include <stdio.h>

class ScopedTimer {
public:
    ScopedTimer(const char* name)
    : m_name(name),
    m_beg(std::chrono::high_resolution_clock::now()) { }
    ~ScopedTimer() {
        auto end = std::chrono::high_resolution_clock::now();
        auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_beg);
        std::cout << m_name << " : " << dur.count() << " ns\n";
    }
private:
    const char* m_name;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_beg;
};

#include <stdint.h>
struct Node {
    int64_t val;
    Node(int val_) {
        val = val_;
    }
};
bool NodeCpm(const Node* a, const Node* b) {
    return a->val >= b->val;
}

#include <unordered_map>
#include <vector>
int testSort(int argc, char* argv[]) {
    ScopedTimer sr("unordered_map sort");
    std::unordered_map<int32_t, std::vector<Node*>> mvec;
    auto& vec = mvec[1];
    for (int i = 0; i < 50; ++i) {
        vec.push_back(new Node(i));
    }

    vec.push_back(new Node(2));
    vec.push_back(new Node(1));
    vec.push_back(new Node(6));
    vec.push_back(new Node(6));
    vec.push_back(new Node(1));
    vec.push_back(new Node(1));
    printf("vec=%d \n", vec.size());
    std::sort(vec.begin(), vec.end(), NodeCpm);
    auto a = std::to_string(0.75);
    std::cout << a << std::endl;
    printf("end \n");
    return 0;
}

void quickSort(std::vector<int>& arr, int begin, int end) {
    if(begin > end) {
        return;
    }
    int tmp = arr[begin];
    int i = begin;
    int j = end;
    while(i < j) {
        while(i < j && arr[j] >= tmp) {
            j--;
        }
        while(i < j && arr[i] <= tmp) {
            i++;
        }
        if (i<j){
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i], arr[begin]);
    quickSort(arr, begin, i-1);
    quickSort(arr, i+1, end);
}
void Quick_Sort(std::vector<int>& arr, int begin, int end) {
    if(begin > end)
        return;
    int tmp = arr[begin];
    int i = begin;
    int j = end;
    while(i != j){
        while(arr[j] >= tmp && j > i)
            j--;
        while(arr[i] <= tmp && j > i)
            i++;
        if(j > i){
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }

    arr[begin] = arr[i];
    arr[i] = tmp;
    Quick_Sort(arr, begin, i-1);
    Quick_Sort(arr, i+1, end);
}

int testQuickSort() {
    std::vector<int> arr;
    for (int i = 50; i > 35; --i) {
        arr.push_back(i);
    }
    for (int i = 50; i < 65; ++i) {
        arr.push_back(i);
    }
    for (auto i :arr) {
        std::cout << i << " ";
    }
    std::cout << "" << std::endl;

    quickSort(arr, 0, arr.size()-1);
    for (auto i :arr) {
        std::cout << i << " ";
    }
    return 0;
}
