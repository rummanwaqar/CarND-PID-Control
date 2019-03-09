#include "pid.hpp"

void PID::init(double kp, double ki, double kd, double effort_limit) {
  // update params
  kp_ = kp;
  ki_ = ki;
  kd_ = kd;
  effort_limit_ = effort_limit;

  cte_prev_ = 0;
  cte_sum_ = 0;
}

double PID::run(double cte) {
  double diff, effort;
  if(diff_average_.get_window_size() > 1) {
    diff = diff_average_.get_average(cte - cte_prev_);
  } else {
    diff = cte - cte_prev_;
  }
  cte_prev_ = cte;
  cte_sum_ += cte;
  if(output_average_.get_window_size() > 1) {
    effort = output_average_.get_average(-kp_ * cte - kd_ * diff - ki_ * cte_sum_);
  } else {
    effort = -kp_ * cte - kd_ * diff - ki_ * cte_sum_;
  }
  if (effort > effort_limit_) {
    effort = effort_limit_;
  } else if (effort < -effort_limit_) {
    effort = -effort_limit_;
  }
  debug_string_ = mk_debug_string(-kp_ * cte,- kd_ * diff, - ki_ * cte_sum_, effort, kp_, ki_, kd_);
  return effort;
}

std::string PID::get_debug_string() {
  return debug_string_;
}

std::string PID::mk_debug_string(double cte, double diff, double sum,
  double effort, double kp, double ki, double kd) {
  std::stringstream ss;
  ss << cte << "," << diff << "," << sum << "," << effort << "," <<
        kp << "," << ki << "," << kd;
  return ss.str();
}
