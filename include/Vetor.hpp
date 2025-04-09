#pragma once
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace ifnum
{
/*!
 * @brief Classe que representa um vetor matemático genérico.
 *
 * Armazena as coordenadas do vetor e fornece operações básicas como
 * soma, subtração, normalização, produto escalar e comparação.
 *
 * @tparam T Tipo dos elementos do vetor (ex: int, float, double).
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
class Vetor
{
  private:
    size_t tamanho_;
    std::vector<T> elementos_;

  public:
    Vetor(const std::vector<T> &dados);
    Vetor(size_t tamanho, const std::vector<T> &dados = {});

    void imprimir() const;
    double norma() const;
    Vetor<T> normalizar() const;

    Vetor<T> operator+(const Vetor &outro) const;
    Vetor<T> operator-(const Vetor &outro) const;
    T operator*(const Vetor &outro) const;

    bool operator==(const Vetor &outro) const;
    bool operator!=(const Vetor &outro) const;

    size_t tamanho() const;
    std::vector<T> vector() const;

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Vetor<U> &v);
};

} // namespace ifnum

#include "Vetor.tpp"