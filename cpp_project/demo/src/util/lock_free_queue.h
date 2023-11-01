#ifndef UTIL_LOCK_FREE_QUEUE_H
#define UTIL_LOCK_FREE_QUEUE_H
#pragma once
#include <atomic>
#include <memory>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE_OF_RING_BUFFER (128)

namespace util {
template <typename ItemT> class LockFreeQueue {
public:
  LockFreeQueue(int s = MAX_SIZE_OF_RING_BUFFER) {
    size_ = s;
    head_index_ = 0;
    tail_index_ = 0;
    item_num_ = 0;

    InitQueue();
  }

  ~LockFreeQueue() { delete[] flags_array_; }

  bool EnQueue(ItemT *item) {
    if (!(item_num_ < size_)) {
      return false;
    }

    int cur_tail_index = tail_index_;
    std::atomic<int> *cur_tail_flag_index = flags_array_ + cur_tail_index;

    while (!CAS(cur_tail_flag_index, 0, 1)) {
      cur_tail_index = tail_index_;
      cur_tail_flag_index = flags_array_ + cur_tail_index;
    }

    int update_tail_index = (cur_tail_index + 1) & (size_ - 1);

    CAS(&tail_index_, cur_tail_index, update_tail_index);
    ring_array_[cur_tail_index] = std::move(*item);

    FetchADD(cur_tail_flag_index, 1);
    FetchADD(&item_num_, 1);

    return true;
  }

  bool DeQueue(ItemT *item) {
    if (!(item_num_ > 0))
      return false;

    int cur_head_index = head_index_;
    std::atomic<int> *cur_head_flag_index = flags_array_ + cur_head_index;
    while (!CAS(cur_head_flag_index, 2, 3)) {
      cur_head_index = head_index_;
      cur_head_flag_index = flags_array_ + cur_head_index;

      if (!(item_num_ > 0))
        return false;
    }

    int update_head_index = (cur_head_index + 1) & (size_ - 1);

    CAS(&head_index_, cur_head_index, update_head_index);

    if (NULL != item) {
      *item = std::move(ring_array_[cur_head_index]);
    }

    FetchSub(cur_head_flag_index, 3);
    FetchSub(&item_num_, 1);

    return true;
  }

  bool IsEmpty() { return (item_num_ <= 0); }

private:
  bool InitQueue(void) {
    flags_array_ = new (std::nothrow) std::atomic<int>[size_];
    if (flags_array_ == NULL)
      return false;
    memset(flags_array_, 0, size_);
    ring_array_ = std::make_unique<ItemT[]>(size_);
    return true;
  }

  inline bool CAS(std::atomic<int> *reg, int old, int newVal) {
    return std::atomic_compare_exchange_weak(reg, &old, newVal);
  }

  inline int FetchADD(std::atomic<int> *v, int add) {
    return std::atomic_fetch_add(v, add);
  }

  inline int FetchSub(std::atomic<int> *v, int add) {
    return std::atomic_fetch_sub(v, add);
  }

private:
  std::unique_ptr<ItemT[]> ring_array_;
  // flags: 0:empty; 1:enqueue-ing; 2:enqueue-able; 3:dequeue-ing.
  std::atomic<int> *flags_array_;
  int size_;
  std::atomic<int> item_num_;
  std::atomic<int> head_index_;
  std::atomic<int> tail_index_;
};
} // namespace util

#endif /* UTIL_LOCK_FREE_QUEUE_H */
