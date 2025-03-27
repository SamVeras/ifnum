#pragma once
#include <iostream>
#include <random>
#include <type_traits>
#include <vector>

namespace ifnum
{

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