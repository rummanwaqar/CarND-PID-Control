#include <iostream>
#include <tuple>

#include "io.hpp"

const int PORT = 4567;

int main() {
  std::cout << "Connecting to simulator" << std::endl;
  SimIO simulator(PORT, [&](double cte, double speed, double angle) {
    std::cout << cte << "\t" << speed << "\t" << angle << std::endl;
    return std::make_tuple(0,1);
  });

  simulator.run();

  return 0;
}
