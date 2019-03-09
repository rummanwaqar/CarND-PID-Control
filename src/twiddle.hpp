#pragma once

#include <iostream>
#include <vector>
#include <tuple>
#include <string>

class Twiddle {
public:
  Twiddle(double tol, double runtime, double init_time, int diff_window_size = 1,
    int output_window_size = 1, double kp=0, double ki=0, double kd=0,
    double dkp = 1., double dki = 1., double dkd = 1.)
    : tol_(tol), runtime_(runtime), init_time_(init_time), p_{kp, ki, kd},
    dp_{dkp, dki, dkd}, count_(0), first_run_(true), err_(0),
    current_index_(0), state_(0), pid_(diff_window_size, output_window_size) {}

  ~Twiddle() = default;

  std::tuple<double, bool> run(double cte) {
    // std::cout << count_ << std::endl;
    if(count_ == 0) { // init run
      pid_.init(p_[0], p_[1], p_[2]);
      err_ = 0;
    }
    double steering = pid_.run(cte);
    bool off_road = cte > of_road_ or cte < -of_road_;
    if(count_ > runtime_ or (off_road and count_ > 1)) { // end of run
      err_ = err_ / (runtime_ - init_time_);
      if(off_road) {
        err_ += 1; // penanlty for driving off the road
      }
      twiddle();
      count_ = 0;
      std::cout << "kp:" << p_[0] << " | ki:" << p_[1]
                << " | kd:" << p_[2]
                << " | err:" << err_ << std::endl;
      return std::make_tuple(steering, true);
    } else if(count_> init_time_) {
      err_ += cte * cte;
    }
    count_++;
    return std::make_tuple(steering, false);
  }

  void twiddle() {
    if(first_run_) {
      best_error_ = err_;
      first_run_ = false;
    } else {
      double sum_dp = dp_[0] + dp_[1] + dp_[2];
      if(sum_dp > tol_) {
        if(state_ == 0) {
          p_[current_index_] += dp_[current_index_];
          state_ = 1;
          return;
        } else if (state_ == 1) {
          if(err_ < best_error_) {
            best_error_ = err_;
            dp_[current_index_] *= 1.1;
            current_index_ = (current_index_ + 1) % 3;
            state_ = 0;
          } else {
            p_[current_index_] -= 2 * dp_[current_index_];
            state_ = 2;
          }
          return;
        } else if (state_ == 2) {
          if(err_ < best_error_) {
            best_error_ = err_;
            dp_[current_index_] *= 1.1;
          } else {
            p_[current_index_] += dp_[current_index_];
            dp_[current_index_] *= 0.9;
          }
          current_index_ = (current_index_ + 1) % 3;
          state_ = 0;
          return;
        }
      } else {
        std::cout << "Twiddle complete" << std::endl;
        std::cout << "kp:" << p_[0] << " | ki:" << p_[1]
                  << " | kd:" << p_[2] << std::endl;
      }
    }
  }

private:
  double tol_;
  double runtime_;
  double init_time_;
  std::vector<double> p_;
  std::vector<double> dp_;
  int count_;
  bool first_run_;
  double best_error_;
  double err_;
  int current_index_;
  int state_;
  PID pid_;
  const int of_road_ = 5.;
};
