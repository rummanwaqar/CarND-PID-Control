#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <cmath>

#include "io.hpp"
#include "pid.hpp"
#include "twiddle.hpp"

const int PORT = 4567;
const double REF_SPEED = 80;
const double SPEED_REDUCTION_FACTOR = 20;

int main(int argc, char** argv) {
  bool train = false;
  std::string log_name = "";
  if(argc == 2) {
    auto arg = std::string(argv[1]);
    if(arg.compare("train") == 0) {
      train = true;
    } else if(arg.substr(arg.find_last_of(".") + 1) == "csv") {
      log_name = arg;
    }
  }

  std::ofstream logger;
  if(log_name != "") {
    logger.open(log_name);
  }

  // twiddle for steering
  Twiddle twiddle(0.2, 1500, 200, 5, 3, 0.1, 0.0008, 5.0, 0.05, 0.0001, 1.0);

  PID steering_pid(5, 3);
  steering_pid.init(0.1, 0.0008, 5.0);

  PID throttle_pid(5, 1);
  throttle_pid.init(0.5, 0.00001, 1.0);
  std::cout << "Connecting to simulator" << std::endl;
  SimIO simulator(PORT, [&](double cte, double speed, double angle) {
    double steering, throttle;
    bool reset = false;
    if(train) {
      std::tie(steering, reset) = twiddle.run(cte);
    } else {
      steering = steering_pid.run(cte);
    }
    throttle = throttle_pid.run(speed - (REF_SPEED -
      fabs(cte) * SPEED_REDUCTION_FACTOR));
    if(log_name != "") {
      logger << steering_pid.get_debug_string() << std::endl;
    }
    return std::make_tuple(steering, throttle, reset);
  });
  simulator.run();

  if(log_name != "") {
    logger.close();
  }
  return 0;
}
