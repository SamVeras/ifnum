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
    size_t linhas;
    size_t colunas;
    std::vector<T> matriz;

public:
    Matriz(size_t linhas, size_t colunas, const std::vector<T> &dados); // Construtor com lista
    Matriz(size_t linhas, size_t colunas);                              // Construtor de matriz nula

    void imprimir() const;
    T determinante() const;
    T modulo() const;
    Matriz<T> transposta() const;
    double autovalor(const Matriz<T> &other, double e, int r) const;
    Matriz<T> linha(int indice) const;  // Retorna matriz 1xn
    Matriz<T> coluna(int indice) const; // Retorna matrix nx1

    T operator()(int linha, int coluna) const; // Operador de acesso (leitura)
    T &operator()(int linha, int coluna);      // Operador de acesso por referência

    Matriz<T> operator+(const Matriz<T> &outro) const;
    Matriz<T> operator-(const Matriz<T> &outro) const;
    Matriz<T> operator*(T escalar) const;              // Multiplicação de matriz por escalar
    Matriz<T> operator/(T escalar) const;              // Divisão de matriz por escalar
    Matriz<T> operator*(const Matriz<T> &outro) const; // Multiplicação de matrizes

    Matriz<T> &operator+=(const Matriz<T> &outro);
    Matriz<T> &operator-=(const Matriz<T> &outro);
    Matriz<T> &operator*=(T escalar); // M. de matriz por escalar e atribuição
    Matriz<T> &operator/=(T escalar); // D. de matriz por escalar e atribuição

    bool operator==(const Matriz<T> &outro) const;
    bool operator!=(const Matriz<T> &outro) const;

    template <typename U> // std::cout << matriz;
    friend std::ostream &operator<<(std::ostream &os, const Matriz<U> &u);

    template <typename U> // escalar à esquerda (2 * matriz)
    friend Matriz<U> operator*(U escalar, const Matriz<U> &matriz);
};

/* CONSTRUTORES */

template <typename T>
Matriz<T>::Matriz(size_t linhas, size_t colunas, const std::vector<T> &dados)
    : linhas(linhas), colunas(colunas), matriz(linhas * colunas)
{
    for (size_t i = 0; i < matriz.size() && i < dados.size(); i++)
        matriz[i] = dados[i];
}

template <typename T>
Matriz<T>::Matriz(size_t linhas, size_t colunas)
    : linhas(linhas), colunas(colunas), matriz(linhas * colunas) {}

/* OPERADORES DE ACESSO */

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

/* MÉTODOS */

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
T Matriz<T>::determinante() const
{
    if (colunas != linhas)
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

    if ((size_t)indice > linhas)
        throw std::out_of_range("Erro: Índice de linha fora dos limites.");

    std::vector<T> nova_linha(&matriz[(indice - 1) * colunas], &matriz[indice * colunas]);

    Matriz<T> novo(1, colunas, nova_linha); // Nova matriz com ordem 1xn

    return novo;
}

template <typename T>
Matriz<T> Matriz<T>::coluna(int indice) const
{
    if (indice <= 0)
        throw std::out_of_range("Erro: Índice deve ser maior que zero.");

    if ((size_t)indice > linhas)
        throw std::out_of_range("Erro: Índice de linha fora dos limites.");

    std::vector<T> nova_coluna(colunas);
    for (size_t i = 0; i < linhas; i++)
        nova_coluna[i] = matriz[i * colunas + (indice - 1)];

    Matriz<T>
        novo(linhas, 1, nova_coluna);
    return novo;
}

template <typename T>
T Matriz<T>::modulo() const // Calcula a norma de um vetor.
{
    if (colunas != 1) {
        throw std::invalid_argument("Erro: A matriz não é um vetor coluna.");
    }

    T soma_quadrados = 0;
    for (size_t i = 0; i < linhas; ++i) {
        soma_quadrados += (*this)(i, 0) * (*this)(i, 0);  // Soma dos quadrados dos elementos
    }

    return std::sqrt(soma_quadrados);  // Retorna a raiz quadrada da soma
}


template <typename T>
Matriz<T> Matriz<T>::transposta() const  // Troca a matriz lxc para cxl.
{
    Matriz<T> novo(this->colunas, this->linhas);  // Usando 'this->' para acessar membros
    for (size_t i = 0; i < this->linhas; i++) {
        for (size_t j = 0; j < this->colunas; j++) {
            novo(j, i) = (*this)(i, j);  
        }
    }
    return novo;
}


template <typename T>
double Matriz<T>::autovalor(const Matriz<T> &other, double e, int r) const
{
    int i = 0;
    double erro = 0;
    Matriz<T> trans = (*this).transposta();  // Corrigido de 'trasposta' para 'transposta'
    Matriz<T> v = other;
    Matriz<T> v2(1,1);  // Inicializando 'v2' com as mesmas dimensões de 'v'

    // Loop de iteração
    while (erro < e && i <= r)
    {
        v2 = trans * v;  // Multiplicação da matriz transposta com o vetor v
        erro = abs(v.modulo() - v2.modulo());  // Calculando o erro com o módulo da diferença

        std::cout << "Iteração " << i << ", Erro: " << erro << std::endl;

        v = v2;  // Atualiza o vetor v
        i++;  // Incrementa o número de iterações

        // Se o erro for muito pequeno, podemos sair do loop antecipadamente
        if (erro < 1e-6) {
            break;
        }
    }

    // Agora, calculamos lambda após o loop
    Matriz<T> transposto_v = v.transposta();
    Matriz<T> produto = transposto_v * (*this) * v;
    Matriz<T> denominador = transposto_v * v;

    // Verificar se o denominador é zero antes de fazer a divisão
    if (denominador(0, 0) == 0) {
        std::cerr << "Erro: Denominador é zero. Não é possível calcular o lambda." << std::endl;
        return std::nan("");  // Retorna um valor NaN ou um erro apropriado.
    }

    double lambda = produto(0, 0) / denominador(0, 0);  // Calculando lambda com a fórmula dada

    std::cout << "Valor de lambda: " << lambda << std::endl;

    return lambda;  // Retorna o valor de lambda
}

/* OPERADORES ARITMÉTICOS */

template <typename T>
Matriz<T> Matriz<T>::operator+(const Matriz<T> &other) const
{
    if (colunas != other.colunas || linhas != other.linhas)
        throw std::invalid_argument("Erro: Matrizes de ordens diferentes.");

    Matriz<T> novo(linhas, colunas);

    for (size_t i = 0; i < matriz.size(); i++)
        novo.matriz[i] = matriz[i] + other.matriz[i];

    return novo;
}

template <typename T>
Matriz<T> Matriz<T>::operator-(const Matriz<T> &other) const
{
    if (colunas != other.colunas || linhas != other.linhas)
        throw std::invalid_argument("Erro: Matrizes de ordens diferentes.");

    Matriz<T> novo(linhas, colunas);

    for (size_t i = 0; i < matriz.size(); i++)
        novo.matriz[i] = matriz[i] - other.matriz[i];

    return novo;
}

template <typename T>
Matriz<T> Matriz<T>::operator*(T escalar) const
{
    Matriz<T> novo(linhas, colunas);

    for (size_t i = 0; i < matriz.size(); i++)
        novo.matriz[i] = matriz[i] * escalar;

    return novo;
}

template <typename T>
Matriz<T> Matriz<T>::operator/(T escalar) const
{
    if (escalar == 0)
        throw std::invalid_argument("Erro: Divisão por zero.");

    Matriz<T> novo(linhas, colunas);

    for (size_t i = 0; i < matriz.size(); i++)
        novo.matriz[i] = matriz[i] / escalar;

    return novo;
}

template <typename T>
Matriz<T> Matriz<T>::operator*(const Matriz<T> &outro) const
{
    if (colunas != outro.linhas)
        throw std::invalid_argument("Erro: Matrizes incompatíveis.");

    Matriz<T> novo(linhas, outro.colunas);

    for (size_t i = 0; i < linhas; i++)
        for (size_t j = 0; j < outro.colunas; j++)
            for (size_t k = 0; k < colunas; k++)
                novo(i, j) += (*this)(i, k) * outro(k, j);

    return novo;
}

/* OPERADORES C/ ATRIBUIÇÃO */

template <typename T>
Matriz<T> &Matriz<T>::operator+=(const Matriz<T> &other)
{
    // return *this = *this + other;

    if (colunas != other.colunas || linhas != other.linhas)
        throw std::invalid_argument("Erro: Matrizes de ordens diferentes.");

    for (size_t i = 0; i < matriz.size(); i++)
        matriz[i] += other.matriz[i];

    return *this;
}
template <typename T>
Matriz<T> &Matriz<T>::operator-=(const Matriz<T> &other)
{
    // return *this = *this - outro;

    if (colunas != other.colunas || linhas != other.linhas)
        throw std::invalid_argument("Erro: Matrizes de ordens diferentes.");

    for (size_t i = 0; i < matriz.size(); i++)
        matriz[i] -= other.matriz[i];

    return *this;
}

template <typename T>
Matriz<T> &Matriz<T>::operator*=(T escalar)
{
    // return *this = *this * escalar;

    for (size_t i = 0; i < matriz.size(); i++)
        matriz[i] *= escalar;

    return *this;
}

template <typename T>
inline Matriz<T> &Matriz<T>::operator/=(T escalar)
{
    // return *this = *this / escalar;

    if (escalar == 0)
        throw std::invalid_argument("Erro: Divisão por zero.");

    for (size_t i = 0; i < matriz.size(); i++)
        matriz[i] /= escalar;

    return *this;
}

/* OPERADORES DE IGUALDADE */

template <typename T>
bool Matriz<T>::operator==(const Matriz<T> &outro) const
{
    if (linhas != outro.linhas || colunas != outro.colunas)
        return false;

    for (size_t i = 0; i < linhas; ++i)
        for (size_t j = 0; j < colunas; ++j)
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

    for (size_t i = 0; i < u.linhas; ++i)
    {
        for (size_t j = 0; j < u.colunas; ++j)
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
