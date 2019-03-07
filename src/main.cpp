#include <iostream>
#include <tuple>

#include "io.hpp"

const int PORT = 4567;

int main() {
  std::cout << "Connecting to simulator" << std::endl;
  int cnt = 0;
  SimIO simulator(PORT, [&](double cte, double speed, double angle) {
    cnt += 1;
    std::cout << cnt << "\t" << cte << "\t" << speed << "\t" << angle << std::endl;
    if (cnt > 200) {
      cnt = 0;
      return std::make_tuple(0,0,true);
    }
    return std::make_tuple(0,1, false);
  });

  simulator.run();

  return 0;
}
