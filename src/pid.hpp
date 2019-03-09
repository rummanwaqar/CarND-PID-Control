#pragma once

#include <string>
#include <sstream>
#include "windowed_average.hpp"

class PID {
 public:
  /**
   * Constructor
   * @param diff_windows_size: difference average window size
   * @param output_window_size: output average window size
   */
  PID(double diff_window_size = 1, double output_window_size = 1)
    : diff_average_(diff_window_size), output_average_(diff_window_size) {};

  /**
   * Destructor.
   */
  ~PID() = default;

  /**
   * Initialize PID.
   * @param (ki, ki, kd) PID coefficients
   * @param effort_limit max absolute error
   */
  void init(double kp, double ki, double kd, double effort_limit = 1);

  /**
   * return effort for the given CTE error
   * @param cte The current cross track error
   * @return effort
   */
  double run(double cte);

  /*
   * returns the debug string
   */
  std::string get_debug_string();

 private:
  /**
   * generate a debug string for logging
   */
  std::string mk_debug_string(double cte, double diff, double sum,
    double effort, double kp, double ki, double kd);

  /**
   * PID params
   */
  double kp_;
  double ki_;
  double kd_;
  double effort_limit_;

  // PID class state
  double cte_prev_;
  double cte_sum_;
  WindowedAverage diff_average_;
  WindowedAverage output_average_;

  std::string debug_string_;
};
