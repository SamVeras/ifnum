/*!
 * @file Matriz.hpp
 * @brief Declaração da classe template Matriz e suas operações associadas.
 *
 * Contém a definição da estrutura genérica de matriz, métodos utilitários e 
 * sobrecargas de operadores para facilitar o uso em operações de álgebra linear.
 */

#pragma once
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace ifnum
{
/*!
 * @brief Classe genérica para representação e manipulação de matrizes.
 *
 * Suporta operações matemáticas, transformações e utilitários com sintaxe intuitiva
 * por meio de sobrecarga de operadores e métodos auxiliares.
 *
 * @tparam T Tipo dos elementos da matriz (ex: int, float, double).
 *
 * @author Samuel Veras
 * @author Lucas Andrei
 * @author Sofia Effting
 * @author Ana Julia Dalmora
 * @author Giovani Zanella
 * @date Março de 2025
 */
template <typename T>
class Matriz
{
  private:
    size_t linhas_;
    size_t colunas_;
    std::vector<T> matriz_;

    T sarrus_() const;

  public:
    Matriz(size_t linhas, size_t colunas, const std::vector<T> &dados);
    Matriz(size_t linhas, size_t colunas);

    size_t linhas() const;
    size_t colunas() const;
    std::vector<T> vector() const;

    void imprimir() const;
    T determinante() const;
    T modulo() const;
    Matriz<T> transposta() const;
    double autovalor(const Matriz<T> &other, double tolerancia, int r) const;

    Matriz<T> linha(int indice) const;
    Matriz<T> coluna(int indice) const;
    void redimensionar(int linhas, int colunas);
    void trocar_linhas(int indice1, int indice2);
    void trocar_colunas(int indice1, int indice2);

    T operator()(int linha, int coluna) const;
    T &operator()(int linha, int coluna);
    Matriz<T> operator-() const;
    Matriz<T> operator+(const Matriz<T> &outro) const;
    Matriz<T> operator-(const Matriz<T> &outro) const;
    Matriz<T> operator*(const Matriz<T> &outro) const;
    Matriz<T> operator*(T escalar) const;
    Matriz<T> operator/(T escalar) const;
    Matriz<T> &operator+=(const Matriz<T> &outro);
    Matriz<T> &operator-=(const Matriz<T> &outro);
    Matriz<T> &operator*=(T escalar);
    Matriz<T> &operator/=(T escalar);
    bool operator==(const Matriz<T> &outro) const;
    bool operator!=(const Matriz<T> &outro) const;

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Matriz<U> &u);
    template <typename U>
    friend Matriz<U> operator*(U escalar, const Matriz<U> &matriz);
};
} // namespace ifnum

#include "Matriz.tpp"