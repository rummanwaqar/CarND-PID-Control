#pragma once

#include <deque>
#include <numeric>

/**
 * Applies windowing average
 */
class WindowedAverage {
public:
  WindowedAverage(int window_size) : window_size_(window_size), data_queue_() {}
  ~WindowedAverage() = default;

  void add_data(double data) {
    data_queue_.push_back(data);
    if(data_queue_.size() > window_size_) { // maintain queue size
      data_queue_.pop_front();
    }
  }

  double get_average() {
    double sum = std::accumulate(data_queue_.begin(), data_queue_.end(), 0.0);
    return sum / data_queue_.size();
  }

  double get_average(double data) {
    add_data(data);
    return get_average();
  }

  int get_window_size() {
    return window_size_;
  }

private:
  int window_size_;
  std::deque<double> data_queue_;
};
