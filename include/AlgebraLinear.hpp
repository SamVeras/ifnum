/*!
 * @file AlgebraLinear.hpp
 * @brief Declarações de funções relacionadas à álgebra linear.
 *
 * Este arquivo contém as declarações de funções utilizadas em operações de álgebra linear
 * utilizando a classe Matriz.
 */

#pragma once
#include "Matriz.hpp"
#include <tuple>

namespace ifnum
{

template <typename T>
Matriz<T> sub(Matriz<T> &matriz, Matriz<T> &b);

template <typename T>
Matriz<T> reversub(const Matriz<T> &matriz, const Matriz<T> &b);

template <typename T>
bool verificar_matriz_quadrada(Matriz<T> matriz);

template <typename T>
Matriz<T> gauss(Matriz<T> &matriz, Matriz<T> &b);

template <typename T>
Matriz<T> gauss_jordan(Matriz<T> &matriz, Matriz<T> &b);

template <typename T>
Matriz<T> retorna_U(Matriz<T> &matriz);

template <typename T>
Matriz<T> retorna_L(Matriz<T> &matriz);

std::tuple<Matriz<double>, Matriz<double>, Matriz<double>> decomposicaoLU(const Matriz<double> &A);
Matriz<double> resolverLU(const Matriz<double> &A, const Matriz<double> &b);

} // namespace ifnum

#include "AlgebraLinear.tpp"