/*!
 * @file Auxiliar.tpp
 * @brief Implementações das funções utilitárias declaradas em Auxiliar.hpp.
 */

#ifdef __INTELLISENSE__
#include "Auxiliar.hpp"
#endif

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
} // namespace ifnum

namespace ifnum::rng
{
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
    if constexpr (std::is_integral<T>::value) {
        // Se T é tipo inteiro
        std::uniform_int_distribution<T> dist(min, max);
        for (size_t i = 0; i < linhas * colunas; i++)
            vetor[i] = dist(rng::mt);

    } else if constexpr (std::is_floating_point<T>::value) {
        // Se T for ponto flutuante
        std::uniform_real_distribution<T> dist(min, max);
        for (size_t i = 0; i < linhas * colunas; i++)
            vetor[i] = dist(rng::mt);
    }

    return Matriz<T>(linhas, colunas, vetor);
}

} // namespace ifnum::rng