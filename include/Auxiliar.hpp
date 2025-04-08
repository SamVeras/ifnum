#pragma once
#include <iostream>
#include <random>
#include <type_traits>
#include <vector>

namespace ifnum
{

/*!
 * @brief Imprime os elementos de um std::vector no formato [a, b, c, ...].
 *
 * @tparam T Tipo dos elementos do std::vector.
 * @param vec std::vector a ser impresso.
 *
 * @author Samuel Veras
 * @date 27/03/2025
 */
template <typename T>
void show_vector(const std::vector<T> &vec)
{
    std::cout << "[";
    for (auto it = vec.begin(); it != vec.end(); it++) {
        std::cout << *it;
        if (it != vec.end() - 1)
            std::cout << ", ";
    }
    std::cout << "]\n";
}

namespace rng
{

inline std::mt19937 mt{std::random_device{}()}; // Marsenne Twister (RNG)

/*!
 * @brief Gera uma matriz aleatória de valores numéricos.
 *
 * Gera uma matriz com os valores distribuídos uniformemente no intervalo [min, max],
 * usando distribuição inteira ou contínua, dependendo do tipo T.
 *
 * @tparam T Tipo numérico dos elementos (int, float, double...).
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 * @param min Valor mínimo dos elementos.
 * @param max Valor máximo dos elementos.
 * @return Matriz preenchida com valores aleatórios.
 * @throws static_assert Se T não for um tipo numérico.
 *
 * @author Samuel Veras
 * @date 27/03/2025
 */
template <typename T>
ifnum::Matriz<T> matriz_aleatoria(size_t linhas, size_t colunas, T min, T max)
{
    static_assert(std::is_arithmetic<T>::value, "T deve ser um tipo numérico.");

    std::vector<T> vetor(linhas * colunas);
    // Se T é tipo inteiro
    if constexpr (std::is_integral<T>::value) {
        std::uniform_int_distribution<T> dist(min, max);
        for (size_t i = 0; i < linhas * colunas; i++)
            vetor[i] = dist(rng::mt);

        // Se T for ponto flutuante
    } else if constexpr (std::is_floating_point<T>::value) {
        std::uniform_real_distribution<T> dist(min, max);
        for (size_t i = 0; i < linhas * colunas; i++)
            vetor[i] = dist(rng::mt);
    }

    Matriz<T> novo(linhas, colunas, vetor);

    return novo;
}

} // namespace rng

} // namespace ifnum