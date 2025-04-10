#include "Auxiliar.hpp"

namespace ifnum::rng
{
/*! @brief Gerador de números aleatórios Mersenne Twister, inicializado com std::random_device. */
std::mt19937 mt{std::random_device{}()};

} // namespace ifnum::rng

namespace ifnum::debug
{
/*!
 * @brief Construtor da classe Timer.
 *
 * Marca o ponto de início da contagem de tempo.
 *
 * @author Samuel Veras
 * @date 10/04/2025
 */
Timer::Timer()
{
    start = std::chrono::high_resolution_clock::now();
}

/*!
 * @brief Destrutor da classe Timer.
 *
 * Calcula e imprime o tempo decorrido desde a criação do objeto, em milissegundos,
 * microssegundos e nanossegundos.
 *
 * @author Samuel Veras
 * @date 10/04/2025
 */
Timer::~Timer()
{
    auto end = std::chrono::high_resolution_clock::now();

    auto m = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    auto u = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    auto n = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    std::cout << "Tempo de execução: " << m.count() << " ms, " << u.count() << " µs, " << n.count()
              << " ns\n\n";
}
} // namespace ifnum::debug