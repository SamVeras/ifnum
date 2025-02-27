#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>

template <typename T>
class Matriz
{
private:
    size_t linhas;
    size_t colunas;
    std::vector<T> matriz;

public:
    Matriz(size_t linhas, size_t colunas, std::vector<T> dados);
    Matriz(size_t linhas, size_t colunas); // Construtor de matriz nula
    void imprimir() const;

    T operator()(int linha, int coluna) const; // Operador de acesso
    T &operator()(int linha, int coluna);      // Operador de acesso por ref.

    Matriz<T> operator+(const Matriz<T> outro);
    Matriz<T> &operator+=(const Matriz<T> outro);
    Matriz<T> operator-(const Matriz<T> outro);
    Matriz<T> &operator-=(const Matriz<T> outro);
    Matriz<T> operator*(T escalar); // Multiplicação de matriz por escalar
    Matriz<T> &operator*=(T escalar);
    Matriz<T> operator*(Matriz<T> outro); // Multiplicação de matrizes
};

// IMPLEMENTAÇÕES DOS MÉTODOS (c/ TEMPLATE)

template <typename T>
Matriz<T>::Matriz(size_t linhas, size_t colunas, std::vector<T> dados)
    : linhas(linhas), colunas(colunas), matriz(linhas * colunas)
{
    for (size_t i = 0; i < matriz.size(); i++)
        matriz[i] = dados[i];
}

template <typename T>
Matriz<T>::Matriz(size_t linhas, size_t colunas)
    : linhas(linhas), colunas(colunas), matriz(linhas * colunas) {}

template <typename T>
T Matriz<T>::operator()(int linha, int coluna) const
{
    if (linha < 0 || coluna < 0)
        throw std::out_of_range("Erro: Índices negativos.");

    if ((size_t)linha >= linhas || (size_t)coluna >= colunas)
        throw std::out_of_range("Erro: Índices fora dos limites da matriz.");

    return matriz[linha * colunas + coluna];
}

template <typename T>
T &Matriz<T>::operator()(int linha, int coluna)
{
    if (linha < 0 || coluna < 0)
        throw std::out_of_range("Erro: Índices negativos.");

    if ((size_t)linha >= linhas || (size_t)coluna >= colunas)
        throw std::out_of_range("Erro: Índices fora dos limites da matriz.");

    return matriz[linha * colunas + coluna];
}

template <typename T>
void Matriz<T>::imprimir() const
{
    for (size_t i = 0; i < linhas; ++i)
    {
        for (size_t j = 0; j < colunas; ++j)
        {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template <typename T>
Matriz<T> Matriz<T>::operator+(const Matriz<T> other)
{
    if (colunas != other.colunas || linhas != other.linhas)
        throw std::invalid_argument("Erro: Matrizes de ordens diferentes.");

    Matriz<T> novo(linhas, colunas);

    for (size_t i = 0; i < matriz.size(); i++)
        novo.matriz[i] = matriz[i] + other.matriz[i];

    return novo;
}

template <typename T>
Matriz<T> &Matriz<T>::operator+=(const Matriz<T> other)
{
    if (colunas != other.colunas || linhas != other.linhas)
        throw std::invalid_argument("Erro: Matrizes de ordens diferentes.");

    for (size_t i = 0; i < matriz.size(); i++)
        matriz[i] += other.matriz[i];

    return *this;
}

template <typename T>
Matriz<T> Matriz<T>::operator-(const Matriz<T> other)
{
    if (colunas != other.colunas || linhas != other.linhas)
        throw std::invalid_argument("Erro: Matrizes de ordens diferentes.");

    Matriz<T> novo(linhas, colunas);

    for (size_t i = 0; i < matriz.size(); i++)
        novo.matriz[i] = matriz[i] - other.matriz[i];

    return novo;
}

template <typename T>
Matriz<T> &Matriz<T>::operator-=(const Matriz<T> outro)
{
    if (colunas != outro.colunas || linhas != outro.linhas)
        throw std::invalid_argument("Erro: Matrizes de ordens diferentes.");

    for (size_t i = 0; i < matriz.size(); i++)
        matriz[i] -= outro.matriz[i];

    return *this;
}

template <typename T>
Matriz<T> Matriz<T>::operator*(T escalar)
{
    Matriz<T> novo(linhas, colunas);

    for (size_t i = 0; i < matriz.size(); i++)
        novo.matriz[i] = matriz[i] * escalar;

    return novo;
}

template <typename T>
Matriz<T> &Matriz<T>::operator*=(T escalar)
{
    for (size_t i = 0; i < matriz.size(); i++)
        matriz[i] *= escalar;

    return *this;
}

template <typename T>
Matriz<T> Matriz<T>::operator*(Matriz<T> outro)
{
    if (colunas != outro.linhas)
        throw std::invalid_argument("Erro: Matrizes incompatíveis.");

    Matriz<T> novo(linhas, outro.colunas);

    for (size_t i = 0; i < linhas; i++)
    {
        for (size_t j = 0; j < outro.colunas; j++)
        {
            for (size_t k = 0; k < colunas; k++)
            {
                novo(i, j) += (*this)(i, k) * outro(k, j);
            }
        }
    }

    return novo;
}
