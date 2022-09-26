//
// Created by mikoxmsong on 2021/12/13.
//

#ifndef PROBLEM_SET_UTIL_INDEX_MANAGER_H
#define PROBLEM_SET_UTIL_INDEX_MANAGER_H
#include <chrono>
#include <thread>
#include <random>
#include <memory>
#include <vector>
#include <iostream>
class IndexPartition
{
public:
    explicit IndexPartition(int index_):index(index_) 
    {

    }
public:
    int index;
};

class IndexHolder
{

public:
    std::shared_ptr<IndexPartition> index_partition_ptr;
};

class GlobalData
{
public:
    std::shared_ptr<IndexHolder> index_holder_ptr;
    std::weak_ptr<IndexHolder> index_holder_wptr;
};

GlobalData global_data;

shared_ptr<IndexHolder> GetIndexHolderWptr() {
    if (auto index_holder_ptr = global_data.index_holder_wptr.lock(); index_holder_ptr)
    {
        return index_holder_ptr;
    }
    
    return nullptr;
}

void MockRpc(int idx)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        auto index_holder_ptr = GetIndexHolderWptr();
        if (!index_holder_ptr)
        {
            std::cout << "index_holder_ptr is nullptr" << std::endl;
            continue;
        }
        std::random_device rd;

        auto start = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds(rd()% 100));
        auto end = std::chrono::high_resolution_clock::now();
        //std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    
        std::chrono::duration<double> diff = end - start;
        std::string out;
        out = std::to_string(idx) +  "-RPC:"  + std::to_string(diff.count()) + " sec, count" + std::to_string(index_holder_ptr->index_partition_ptr.use_count()) + ", index_partition_ptr->index:" 
        + std::to_string(index_holder_ptr->index_partition_ptr->index) + "\n";
        std::cout << out;  // 秒
    }
    

}
std::atomic<int> g_index = 1;
void SetData(int index) {
    global_data.index_holder_ptr = std::make_shared<IndexHolder>();
    global_data.index_holder_ptr->index_partition_ptr = std::make_shared<IndexPartition>(index);
    global_data.index_holder_wptr = global_data.index_holder_ptr;
}

#endif //PROBLEM_SET_UTIL_INDEX_MANAGER_H
