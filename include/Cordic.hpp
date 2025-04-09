/*!
 * @file Cordic.hpp
 * @brief Declarações de funções trigonométricas baseadas no algoritmo CORDIC.
 *
 * Define a interface de funções que implementam seno, cosseno e rotação vetorial
 * usando o método iterativo CORDIC.
 */
#pragma once
#include <utility>

namespace ifnum::cordic
{

std::pair<double, double> rotate(double x, double y, double angle);
double sin(double angle);
double cos(double angle);

} // namespace ifnum::cordic
