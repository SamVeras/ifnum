#include "Auxiliar.hpp"

namespace ifnum::rng
{
/*! @brief Gerador de números aleatórios Mersenne Twister, inicializado com std::random_device. */
std::mt19937 mt{std::random_device{}()};

} // namespace ifnum::rng