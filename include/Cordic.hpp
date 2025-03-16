#pragma once
#include <cmath>
#include <utility>
#include <vector>

namespace ifnum {
namespace Cordic {

const std::vector<double> angles = {
    45.0,      26.565,    14.0362,   7.12502,   3.57633,   1.78991,
    0.895174,  0.447614,  0.223811,  0.111906,  0.055953,  0.027977,
    0.0139887, 0.0069943, 0.0034971, 0.0017486, 0.0008743, 0.0004372,
    0.0002186, 0.0001093, 0.0000546, 0.0000273, 0.0000136, 0.0000068,
    0.0000034, 0.0000017, 0.0000008, 0.0000004, 0.0000002, 0.0000001};
const int MAX_ITERATIONS = 30;
const double K = 0.6072529350088812561694;

inline std::pair<double, double> rotate(double x, double y, double angle) {
  double current_angle = 0.0;
  double power_of_two = 1.0;

  for (int i = 0; i < MAX_ITERATIONS; i++) {
    double angle_step = angles[i];
    double new_x, new_y;

    int direction = (angle < current_angle) ? -1 : 1;
    new_x = x - direction * power_of_two * y;
    new_y = y + direction * power_of_two * x;
    current_angle += direction * angle_step;
    power_of_two *= 0.5;

    x = new_x;
    y = new_y;
  }
  return std::make_pair(x, y);
}

inline double sin(double angle) { return Cordic::rotate(K, 0, angle).second; }

inline double cos(double angle) { return Cordic::rotate(K, 0, angle).first; }

} // namespace Cordic
} // namespace ifnum
