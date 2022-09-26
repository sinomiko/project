//
// Created by miko on 2021/12/13.
//
#ifndef PROBLEM_SET_LEECODE_QUICK_SORT_H
#define PROBLEM_SET_LEECODE_QUICK_SORT_H
#include <iostream>
#include <unordered_map>
#include <string>
#include <iostream>
#include <view/util/Timer.h>
#include <charconv>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <queue>

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
int TestSort(int argc, char* argv[]) {
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
    printf("vec=%lu \n", vec.size());
    std::sort(vec.begin(), vec.end(), NodeCpm);
    auto a = std::to_string(0.75);
    std::cout << a << std::endl;
    printf("end \n");
    return 0;
}

void QuickSortV1(std::vector<int>& arr, int begin, int end) {
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
    QuickSortV1(arr, begin, i-1);
    QuickSortV1(arr, i+1, end);
}

void topK() {
    std::priority_queue<int, std::vector<int>, std::greater<int>> p_queue;
}
void QuickSortV2(std::vector<int>& arr, int begin, int end) {
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
    QuickSortV2(arr, begin, i-1);
    QuickSortV2(arr, i+1, end);
}

#endif PROBLEM_SET_LEECODE_QUICK_SORT_H
