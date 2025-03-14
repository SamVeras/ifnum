#include "../include/Cordic.hpp"
#include <iostream>

int main() {

  double sin30 = ifnum::Cordic::sin(30);
  std::cout << "sin(30) = " << sin30 << std::endl;
  return 0;
}
