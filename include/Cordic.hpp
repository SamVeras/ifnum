#pragma once
#include <utility>

namespace ifnum
{

namespace cordic
{

std::pair<double, double> rotate(double x, double y, double angle);
double sin(double angle);
double cos(double angle);

} // namespace cordic

} // namespace ifnum
