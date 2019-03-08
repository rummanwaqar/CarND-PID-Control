#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

#include "io.hpp"
#include "pid.hpp"
#include "twiddle.hpp"

const int PORT = 4567;

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

  Twiddle twiddle(0.2, 3000, 200, 0.05, 0.0001, 1.0, 1, 1, 1);

  PID pid;
  pid.init(1.6, 0.00048, 19.3, 0);
  std::cout << "Connecting to simulator" << std::endl;

  SimIO simulator(PORT, [&](double cte, double speed, double angle) {
    double steering;
    bool reset = false;
    if(train) {
      std::tie(steering, reset) = twiddle.run(cte);
    }
    steering = pid.run(cte);
    if(log_name != "") {
      logger << pid.get_debug_string() << std::endl;
    }
    return std::make_tuple(steering, 0.3, reset);
  });
  simulator.run();

  if(log_name != "") {
    logger.close();
  }
  return 0;
}
