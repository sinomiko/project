
#include <algorithm>
#include <atomic>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
typedef int32_t docid_t;
std::vector<std::pair<docid_t, docid_t>>
GetTaskDocPoint(docid_t total_doc, int seek_parallel_task_num) {
  std::vector<std::pair<docid_t, docid_t>> task_doc_point;
  docid_t offset = total_doc / seek_parallel_task_num;
  docid_t doc_end = offset;
  docid_t doc_begin = 0;

  while (doc_begin < total_doc && doc_end <= total_doc) {
    if (task_doc_point.size() == seek_parallel_task_num - 1) {
      task_doc_point.emplace_back(
          std::pair<docid_t, docid_t>{doc_begin, total_doc});
      break;
    }

    task_doc_point.emplace_back(
        std::pair<docid_t, docid_t>{doc_begin, doc_end});
    doc_end += offset;
    doc_begin += offset;
  }
  return task_doc_point;
}

int main(int argc, char *argv[]) {
  std::vector<std::pair<docid_t, docid_t>> task_doc_points =
      GetTaskDocPoint(10, 2);
  std::cout << "main execute" << std::endl;
  for (int i = 0; i < task_doc_points.size(); i++) {
    std::cout << "1:"
              << "first:" << task_doc_points[i].first
              << ", second:" << task_doc_points[i].second << std::endl;
  }

  task_doc_points = GetTaskDocPoint(10, 3);
  for (int i = 0; i < task_doc_points.size(); i++) {
    std::cout << "2:"
              << "first:" << task_doc_points[i].first
              << ", second:" << task_doc_points[i].second << std::endl;
  }

  task_doc_points = GetTaskDocPoint(10, 9);
  for (int i = 0; i < task_doc_points.size(); i++) {
    std::cout << "3:"
              << "first:" << task_doc_points[i].first
              << ", second:" << task_doc_points[i].second << std::endl;
  }

  task_doc_points = GetTaskDocPoint(100, 3);
  for (int i = 0; i < task_doc_points.size(); i++) {
    std::cout << "4:"
              << "first:" << task_doc_points[i].first
              << ", second:" << task_doc_points[i].second << std::endl;
  }

  return 0;
}