
#include "util/lock_free_queue.h"
#include <algorithm>
#include <atomic>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

std::atomic<int> g_seek_tasks_num(0);
struct DocBatch {
  DocBatch() {}
  bool IsEmpty() { return docs.empty(); }
  std::vector<int> docs;
};

util::LockFreeQueue<DocBatch> g_lfq(200);

void GenBatchDocs(int taskid, int repeat_times, int sleep_time) {
  std::cout << "GenBatchDocs... taskid:" << taskid
            << "repeat_times:" << repeat_times << "\n"
            << std::flush;
  while (repeat_times-- > 0) {
    if (sleep_time > 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    }
    std::unique_ptr<DocBatch> docs_ptr = std::make_unique<DocBatch>();
    int doc_num = 0;
    while (docs_ptr->docs.size() < 10000) {
      docs_ptr->docs.push_back(2);
    }
    auto docs_raw_ptr = docs_ptr.release();
    while (!g_lfq.EnQueue(docs_raw_ptr)) {
      std::this_thread::sleep_for(std::chrono::nanoseconds(100));
    }
    delete docs_raw_ptr;
    std::cout << "GenBatchDocs... "
              << " taskid:" << taskid << ", repeat_times:" << repeat_times
              << "\n"
              << std::flush;
  }
  std::cout << "GenBatchDocs... "
            << " taskid:" << taskid << " end"
            << "\n"
            << std::flush;

  std::atomic_fetch_sub(&g_seek_tasks_num, 1);
}

bool DispatchTask(int seek_task_num, int repeat_times, int seek_sleeptime) {
  std::cout << "DispatchTask..."
            << " seek_task_num:" << seek_task_num
            << ",repeat_times:" << repeat_times << "\n"
            << std::flush;

  for (int i = 0; i < seek_task_num; i++) {
    std::thread t(GenBatchDocs, i, repeat_times, seek_sleeptime);
    std::atomic_fetch_add(&g_seek_tasks_num, 1);
    t.detach();
  }

  std::cout << "DispatchTask after..."
            << "\n"
            << std::flush;

  return true;
}

int main(int argc, char *argv[]) {
  int seek_task_num = 2, repeat_times = 500, seek_sleeptime = 1;
  std::cout << "main execute" << std::endl;
  for (int i = 0; i < argc; i++) {
    std::cout << argv[i] << std::endl;
  }

  DispatchTask(seek_task_num, repeat_times, seek_sleeptime);
  int batch_num = 0;
  while (g_seek_tasks_num.load() > 0 || !g_lfq.IsEmpty()) {
    if (!g_lfq.IsEmpty()) {
      DocBatch batch_doc;
      g_lfq.DeQueue(&batch_doc);
      int sum;
      std::for_each(batch_doc.docs.begin(), batch_doc.docs.end(),
                    [&sum](int &n) { sum += n; });
      std::cout << "main execute: sum " << sum
                << ",g_seek_tasks_num:" << g_seek_tasks_num.load()
                << ",batch_num:" << ++batch_num << "\n"
                << std::flush;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // std::cout << "main execute: loop " << ",g_seek_tasks_num:" <<
    // g_seek_tasks_num.load() << ",batch_num:" << batch_num << "\n" <<
    // std::flush;
  }

  std::cout << "main execute end \n" << std::flush;
  return 0;
}