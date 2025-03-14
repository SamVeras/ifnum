#pragma once
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cmath>

template <typename T>
class Matriz
{
private:
    size_t linhas_;
    size_t colunas_;
    std::vector<T> matriz_;

public:
    /* ---------------------------- CONSTRUTORES ---------------------------- */

    Matriz(size_t linhas, size_t colunas, const std::vector<T> &dados);
    Matriz(size_t linhas, size_t colunas); // Matriz nula

    /* ------------------------------- GETTERS ------------------------------ */

    size_t linhas() const;
    size_t colunas() const;

    /* ------------------------------- MÉTODOS ------------------------------ */

    void imprimir() const;
    T determinante() const;
    T modulo() const;
    Matriz<T> transposta() const;
    double autovalor(const Matriz<T> &other, double tolerancia, int r) const;
    Matriz<T> linha(int indice) const;  // Retorna matriz 1xn
    Matriz<T> coluna(int indice) const; // Retorna matrix nx1
    void redimensionar(int linhas, int colunas);

    /* ---------------------- SOBRECARGAS DE OPERADORES --------------------- */

    T operator()(int linha, int coluna) const; // Operador de acesso (leitura)
    T &operator()(int linha, int coluna);      // Operador de acesso por referência

    Matriz<T> operator-() const; // Negativar matriz

    Matriz<T> operator+(const Matriz<T> &outro) const;
    Matriz<T> operator-(const Matriz<T> &outro) const;
    Matriz<T> operator*(const Matriz<T> &outro) const; // Multiplicação de matrizes
    Matriz<T> operator*(T escalar) const;              // Multiplicação de matriz por escalar
    Matriz<T> operator/(T escalar) const;              // Divisão de matriz por escalar

    Matriz<T> &operator+=(const Matriz<T> &outro);
    Matriz<T> &operator-=(const Matriz<T> &outro);
    Matriz<T> &operator*=(T escalar); // M. de matriz por escalar e atribuição
    Matriz<T> &operator/=(T escalar); // D. de matriz por escalar e atribuição

    bool operator==(const Matriz<T> &outro) const;
    bool operator!=(const Matriz<T> &outro) const;

    /* ------------------------------- FRIENDS ------------------------------ */

    template <typename U> // std::cout << matriz;
    friend std::ostream &operator<<(std::ostream &os, const Matriz<U> &u);

    template <typename U> // escalar à esquerda (2 * matriz)
    friend Matriz<U> operator*(U escalar, const Matriz<U> &matriz);
};

/* ------------------------------ CONSTRUTORES ------------------------------ */

template <typename T>
Matriz<T>::Matriz(size_t linhas, size_t colunas, const std::vector<T> &dados)
    : linhas_(linhas), colunas_(colunas), matriz_(linhas * colunas)
{
    for (size_t i = 0; i < matriz_.size() && i < dados.size(); i++)
        matriz_[i] = dados[i];
}

template <typename T>
Matriz<T>::Matriz(size_t linhas, size_t colunas)
    : linhas_(linhas), colunas_(colunas), matriz_(linhas * colunas) {}

/* --------------------------------- GETTERS -------------------------------- */

template <typename T>
inline size_t Matriz<T>::linhas() const
{
    return this->linhas_;
}

template <typename T>
inline size_t Matriz<T>::colunas() const
{
    return this->colunas_;
}

/* ------------------------ SOBRECARGAS DE OPERADORES ----------------------- */

template <typename T>
T Matriz<T>::operator()(int linha, int coluna) const
{
    if (linha < 0 || coluna < 0)
        throw std::out_of_range("Erro: Índices negativos.");

    if ((size_t)linha >= linhas_ || (size_t)coluna >= colunas_)
        throw std::out_of_range("Erro: Índices fora dos limites da matriz.");

    return matriz_[linha * colunas_ + coluna];
}

template <typename T>
T &Matriz<T>::operator()(int linha, int coluna)
{
    if (linha < 0 || coluna < 0)
        throw std::out_of_range("Erro: Índices negativos.");

    if ((size_t)linha >= linhas_ || (size_t)coluna >= colunas_)
        throw std::out_of_range("Erro: Índices fora dos limites da matriz.");

    return matriz_[linha * colunas_ + coluna];
}

template <typename T>
inline Matriz<T> Matriz<T>::operator-() const
{
    Matriz<T> novo = *this;

    for (auto &e : novo.matriz_)
        e *= -1;

    return novo;
}

/* --------------------------------- MÉTODOS -------------------------------- */

template <typename T>
void Matriz<T>::imprimir() const
{
    std::cout << (*this) << std::endl;
}

template <typename T>
T Matriz<T>::determinante() const
{
    if (colunas_ != linhas_)
        throw std::invalid_argument("Erro: Matriz não é quadrada.");

    T det = 0;

    // TO-DO

    return det;
}

template <typename T>
Matriz<T> Matriz<T>::linha(int indice) const
{
    if (indice <= 0)
        throw std::out_of_range("Erro: Índice deve ser maior que zero.");

    if ((size_t)indice > linhas_)
        throw std::out_of_range("Erro: Índice de linha fora dos limites.");

    std::vector<T> nova_linha(&matriz_[(indice - 1) * colunas_], &matriz_[indice * colunas_]);

    Matriz<T> novo(1, colunas_, nova_linha); // Nova matriz com ordem 1xn

    return novo;
}

template <typename T>
Matriz<T> Matriz<T>::coluna(int indice) const
{
    if (indice <= 0)
        throw std::out_of_range("Erro: Índice deve ser maior que zero.");

    if ((size_t)indice > linhas_)
        throw std::out_of_range("Erro: Índice de linha fora dos limites.");

    std::vector<T> nova_coluna(colunas_);
    for (size_t i = 0; i < linhas_; i++)
        nova_coluna[i] = matriz_[i * colunas_ + (indice - 1)];

    Matriz<T> novo(linhas_, 1, nova_coluna); // Nova matriz com ordem nx1
    return novo;
}

template <typename T>
void Matriz<T>::redimensionar(int linhas, int colunas)
{
    // Nós não precisamos criar uma nova matriz nem nada do tipo, basta
    // aumentar o tamanho do vetor que guarda os dados (matriz), atualizar o
    // índice dos valores internos e atualizar os valores de linhas e colunas.

    matriz_.resize(linhas * colunas, 0);
    // Esse 0 indica que, se houverem novos valores na matriz, eles serão zero.

    this->linhas_ = linhas;
    this->colunas_ = colunas;
}

template <typename T>
T Matriz<T>::modulo() const // Calcula a norma de um vetor.
{
    if (colunas_ != 1)
    {
        throw std::invalid_argument("Erro: A matriz não é um vetor coluna.");
    }

    T soma_quadrados = 0;
    for (size_t i = 0; i < linhas_; ++i)
    {
        soma_quadrados += (*this)(i, 0) * (*this)(i, 0); // Soma dos quadrados dos elementos
    }

    return std::sqrt(soma_quadrados); // Retorna a raiz quadrada da soma
}

template <typename T>
Matriz<T> Matriz<T>::transposta() const // Troca a matriz lxc para cxl.
{
    Matriz<T> novo(this->colunas_, this->linhas_);
    for (size_t i = 0; i < this->linhas_; i++)
    {
        for (size_t j = 0; j < this->colunas_; j++)
        {
            novo(j, i) = (*this)(i, j);
        }
    }
    return novo;
}

template <typename T>
double Matriz<T>::autovalor(const Matriz<T> &other, double tolerancia, int r) const
{
    if (colunas_ != linhas_)
        throw std::invalid_argument("Erro: Matriz deve ser quadrada.");

    if (other.colunas_ != 1 || other.linhas_ != linhas_)
        throw std::invalid_argument("Erro: O vetor inicial deve ser um vetor coluna com a mesma quantidade de linhas da matriz.");

    Matriz<T> v = other;
    Matriz<T> v2(linhas_, 1);
    Matriz<T> transposta = this->transposta();

    double erro = tolerancia + 1; // Garantir entrada no loop
    int i = 0;

    while (erro > tolerancia && i < r)
    {
        v2 = transposta * v;

        double modulo_v = v.modulo();
        double modulo_v2 = v2.modulo();
        erro = std::abs(modulo_v2 - modulo_v);

        v = v2 / modulo_v2; // Normaliza o vetor para evitar crescimento descontrolado
        i++;
    }

    // Cálculo do autovalor final
    Matriz<T> produto = v.transposta() * (*this) * v;
    Matriz<T> denominador = v.transposta() * v;

    if (denominador(0, 0) == 0)
        throw std::runtime_error("Erro: Denominador zero, impossibilitando o cálculo do autovalor.");

    return produto(0, 0) / denominador(0, 0);
}

/* OPERADORES ARITMÉTICOS */

template <typename T>
Matriz<T> Matriz<T>::operator+(const Matriz<T> &other) const
{
    if (colunas_ != other.colunas_ || linhas_ != other.linhas_)
        throw std::invalid_argument("Erro: Matrizes de ordens diferentes.");

    Matriz<T> novo(linhas_, colunas_);

    for (size_t i = 0; i < matriz_.size(); i++)
        novo.matriz_[i] = matriz_[i] + other.matriz_[i];

    return novo;
}

template <typename T>
Matriz<T> Matriz<T>::operator-(const Matriz<T> &other) const
{
    if (colunas_ != other.colunas_ || linhas_ != other.linhas_)
        throw std::invalid_argument("Erro: Matrizes de ordens diferentes.");

    Matriz<T> novo(linhas_, colunas_);

    for (size_t i = 0; i < matriz_.size(); i++)
        novo.matriz_[i] = matriz_[i] - other.matriz_[i];

    return novo;
}

template <typename T>
Matriz<T> Matriz<T>::operator*(T escalar) const
{
    Matriz<T> novo(linhas_, colunas_);

    for (size_t i = 0; i < matriz_.size(); i++)
        novo.matriz_[i] = matriz_[i] * escalar;

    return novo;
}

template <typename T>
Matriz<T> Matriz<T>::operator/(T escalar) const
{
    if (escalar == 0)
        throw std::invalid_argument("Erro: Divisão por zero.");

    Matriz<T> novo(linhas_, colunas_);

    for (size_t i = 0; i < matriz_.size(); i++)
        novo.matriz_[i] = matriz_[i] / escalar;

    return novo;
}

template <typename T>
Matriz<T> Matriz<T>::operator*(const Matriz<T> &outro) const
{
    if (colunas_ != outro.linhas_)
        throw std::invalid_argument("Erro: Matrizes incompatíveis.");

    Matriz<T> novo(linhas_, outro.colunas_);

    for (size_t i = 0; i < linhas_; i++)
        for (size_t j = 0; j < outro.colunas_; j++)
            for (size_t k = 0; k < colunas_; k++)
                novo(i, j) += (*this)(i, k) * outro(k, j);

    return novo;
}

/* OPERADORES C/ ATRIBUIÇÃO */

template <typename T>
Matriz<T> &Matriz<T>::operator+=(const Matriz<T> &other)
{
    // return *this = *this + other;

    if (colunas_ != other.colunas_ || linhas_ != other.linhas_)
        throw std::invalid_argument("Erro: Matrizes de ordens diferentes.");

    for (size_t i = 0; i < matriz_.size(); i++)
        matriz_[i] += other.matriz_[i];

    return *this;
}
template <typename T>
Matriz<T> &Matriz<T>::operator-=(const Matriz<T> &other)
{
    // return *this = *this - outro;

    if (colunas_ != other.colunas_ || linhas_ != other.linhas_)
        throw std::invalid_argument("Erro: Matrizes de ordens diferentes.");

    for (size_t i = 0; i < matriz_.size(); i++)
        matriz_[i] -= other.matriz_[i];

    return *this;
}

template <typename T>
Matriz<T> &Matriz<T>::operator*=(T escalar)
{
    // return *this = *this * escalar;

    for (auto &e : matriz_)
        e *= escalar;

    return *this;
}

template <typename T>
inline Matriz<T> &Matriz<T>::operator/=(T escalar)
{
    // return *this = *this / escalar;

    if (escalar == 0)
        throw std::invalid_argument("Erro: Divisão por zero.");

    for (auto &e : matriz_)
        e /= escalar;

    return *this;
}

/* OPERADORES DE IGUALDADE */

template <typename T>
bool Matriz<T>::operator==(const Matriz<T> &outro) const
{
    if (linhas_ != outro.linhas_ || colunas_ != outro.colunas_)
        return false;

    for (size_t i = 0; i < linhas_; ++i)
        for (size_t j = 0; j < colunas_; ++j)
            if ((*this)(i, j) != outro(i, j))
                return false;

    return true;
}

template <typename T>
bool Matriz<T>::operator!=(const Matriz<T> &outro) const
{
    return !(*this == outro);
}

/* FRIENDS */

template <typename U>
std::ostream &operator<<(std::ostream &os, const Matriz<U> &u)
{
    const size_t largura = 10;

    for (size_t i = 0; i < u.linhas_; ++i)
    {
        for (size_t j = 0; j < u.colunas_; ++j)
        {
            os << std::setw(largura) << u(i, j);
        }
        os << std::endl;
    }

    return os;
}

template <typename U>
Matriz<U> operator*(U escalar, Matriz<U> &matriz)
{
    return matriz * escalar;
}
