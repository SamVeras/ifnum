/*!
 * @file Auxiliar.hpp
 * @brief Declarações de funções e classes utilitárias gerais para facilitar operações comuns e testes.
 */

#pragma once
#include "Matriz.hpp"
#include <chrono>
#include <iostream>
#include <random>
#include <type_traits>
#include <vector>

namespace ifnum
{

template <typename T>
void show_vector(const std::vector<T> &vec);

} // namespace ifnum

namespace ifnum::debug
{
/*!
 * @class Timer
 * @brief Classe utilitária para medir tempo de execução de trechos de código.
 *
 * Ao instanciar, marca o tempo inicial. Ao ser destruída, ou sair de escopo, imprime o tempo decorrido.
 *
 * @author Samuel Veras
 * @date 10/04/2025
 */
class Timer
{
  private:
    std::chrono::high_resolution_clock::time_point start;

  public:
    Timer();
    ~Timer();
};
} // namespace ifnum::debug

namespace ifnum::rng
{

inline extern std::mt19937 mt;

template <typename T>
ifnum::Matriz<T> matriz_aleatoria(size_t linhas, size_t colunas, T min, T max);

} // namespace ifnum::rng