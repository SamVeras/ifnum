/*!
 * @file Auxiliar.hpp
 * @brief Declarações de funções utilitárias gerais para facilitar operações comuns no projeto. *
 */

#pragma once
#include "Matriz.hpp"
#include <iostream>
#include <random>
#include <type_traits>
#include <vector>

namespace ifnum
{

template <typename T>
void show_vector(const std::vector<T> &vec);
} // namespace ifnum

namespace ifnum::rng
{
inline extern std::mt19937 mt;

template <typename T>
ifnum::Matriz<T> matriz_aleatoria(size_t linhas, size_t colunas, T min, T max);

} // namespace ifnum::rng