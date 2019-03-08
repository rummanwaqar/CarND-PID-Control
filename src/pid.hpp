#pragma once

#include <string>
#include <sstream>

class PID {
 public:
  /**
   * Constructor
   */
  PID() {};

  /**
   * Destructor.
   */
  ~PID() = default;

  /**
   * Initialize PID.
   * @param (ki, ki, kd) PID coefficients
   * @param max_i Maximum integral windup
   * @param effort_limit max absolute error
   */
  void init(double kp, double ki, double kd, double max_i, double effort_limit = 1);

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
  double max_i_;
  double effort_limit_;

  double cte_prev_;
  double cte_sum_;

  std::string debug_string_;
};
