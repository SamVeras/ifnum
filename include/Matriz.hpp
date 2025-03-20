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

template <typename T>
class Matriz
{
  private:
    size_t linhas_;
    size_t colunas_;
    std::vector<T> matriz_;

    T sarrus_() const;

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
    void trocar_linhas(int indice1, int indice2);
    void trocar_colunas(int indice1, int indice2);

    /* ---------------------- SOBRECARGAS DE OPERADORES --------------------- */

    T operator()(int linha, int coluna) const; // Operador de acesso (leitura)
    T &operator()(int linha, int coluna);      // Operador de acesso por referência

    Matriz<T> operator-() const; // Negativar matriz

    Matriz<T> operator+(const Matriz<T> &outro) const; // Soma de matrizes
    Matriz<T> operator-(const Matriz<T> &outro) const; // Subtração de matrizes
    Matriz<T> operator*(const Matriz<T> &outro) const; // Multiplicação de matrizes
    Matriz<T> operator*(T escalar) const;              // Multiplicação de matriz por escalar
    Matriz<T> operator/(T escalar) const;              // Divisão de matriz por escalar

    Matriz<T> &operator+=(const Matriz<T> &outro); // Soma de matrizes e atribuição
    Matriz<T> &operator-=(const Matriz<T> &outro); // Subtração de matrizes e atribuição
    Matriz<T> &operator*=(T escalar);              // Multiplicação matriz por escalar e atribuição
    Matriz<T> &operator/=(T escalar);              // Divisão matriz por escalar e atribuição

    bool operator==(const Matriz<T> &outro) const; // Igualdade entre matrizes
    bool operator!=(const Matriz<T> &outro) const;

    /* ------------------------------- FRIENDS ------------------------------ */

    template <typename U> // std::cout << matriz;
    friend std::ostream &operator<<(std::ostream &os, const Matriz<U> &u);

    template <typename U> // escalar à esquerda (x * matriz)
    friend Matriz<U> operator*(U escalar, const Matriz<U> &matriz);
};

/* -------------------------------------------------------------------------- */
/*                                 DEFINIÇÕES                                 */
/* -------------------------------------------------------------------------- */

/* ------------------------------ CONSTRUTORES ------------------------------ */

template <typename T>
T Matriz<T>::sarrus_() const
{
    auto m = this;
    if (linhas_ == 2)
        return (*m)(0, 0) * (*m)(1, 1) - (*m)(0, 1) * (*m)(1, 0);

    if (linhas_ == 3)
        return (*m)(0, 0) * (*m)(1, 1) * (*m)(2, 2) + (*m)(0, 1) * (*m)(1, 2) * (*m)(2, 0) +
               (*m)(0, 2) * (*m)(1, 0) * (*m)(2, 1) - (*m)(0, 2) * (*m)(1, 1) * (*m)(2, 0) -
               (*m)(0, 0) * (*m)(1, 2) * (*m)(2, 1) - (*m)(0, 1) * (*m)(1, 0) * (*m)(2, 2);

    return 0; // matrix 0x0?
}

template <typename T>
Matriz<T>::Matriz(size_t linhas, size_t colunas, const std::vector<T> &dados)
    : linhas_(linhas), colunas_(colunas), matriz_(linhas * colunas)
{
    for (size_t i = 0; i < matriz_.size() && i < dados.size(); i++)
        matriz_[i] = dados[i];
}

template <typename T>
Matriz<T>::Matriz(size_t linhas, size_t colunas)
    : linhas_(linhas), colunas_(colunas), matriz_(linhas * colunas)
{
}

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

    if (linhas_ == 1)
        return (*this)(0, 0);

    if (linhas_ <= 3)
        return sarrus_();

    T det = 0;

    // TO-DO

    return det;
}

template <typename T>
T Matriz<T>::modulo() const // Calcula a norma de um vetor.
{
    if (colunas_ != 1) {
        throw std::invalid_argument("Erro: A matriz não é um vetor coluna.");
    }

    T soma_quadrados = 0;
    for (size_t i = 0; i < linhas_; ++i) {
        soma_quadrados += (*this)(i, 0) * (*this)(i, 0); // Soma dos quadrados dos elementos
    }

    return std::sqrt(soma_quadrados); // Retorna a raiz quadrada da soma
}

template <typename T>
Matriz<T> Matriz<T>::transposta() const // Troca a matriz lxc para cxl.
{
    Matriz<T> novo(this->colunas_, this->linhas_);
    for (size_t i = 0; i < this->linhas_; i++) {
        for (size_t j = 0; j < this->colunas_; j++) {
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
        throw std::invalid_argument("Erro: O vetor inicial deve ser um vetor "
                                    "coluna com a mesma quantidade "
                                    "de linhas da matriz.");

    Matriz<T> v = other;
    Matriz<T> v2(linhas_, 1);
    Matriz<T> transposta = this->transposta();

    double erro = tolerancia + 1; // Garantir entrada no loop
    int i = 0;

    while (erro > tolerancia && i < r) {
        v2 = transposta * v;

        double modulo_v = v.modulo();
        double modulo_v2 = v2.modulo();
        erro = std::abs(modulo_v2 - modulo_v);

        v = v2 / modulo_v2; // Normaliza o vetor para evitar crescimento
                            // descontrolado
        i++;
    }

    // Cálculo do autovalor final
    Matriz<T> produto = v.transposta() * (*this) * v;
    Matriz<T> denominador = v.transposta() * v;

    if (denominador(0, 0) == 0)
        throw std::runtime_error(
            "Erro: Denominador zero, impossibilitando o cálculo do autovalor.");

    return produto(0, 0) / denominador(0, 0);
}

template <typename T>
Matriz<T> Matriz<T>::linha(int indice) const
{
    if (indice < 0)
        throw std::out_of_range("Erro: Índice deve ser maior ou igual a zero.");

    if ((size_t)indice >= linhas_)
        throw std::out_of_range("Erro: Índice de linha fora dos limites.");

    std::vector<T> nova_linha(&matriz_[indice * colunas_], &matriz_[(indice + 1) * colunas_]);

    Matriz<T> novo(1, colunas_, nova_linha); // Nova matriz com ordem 1xn

    return novo;
}

template <typename T>
Matriz<T> Matriz<T>::coluna(int indice) const
{
    if (indice < 0)
        throw std::out_of_range("Erro: Índice deve ser maior ou igual a zero.");

    if ((size_t)indice >= linhas_)
        throw std::out_of_range("Erro: Índice de coluna fora dos limites.");

    std::vector<T> nova_coluna(colunas_);
    for (size_t i = 0; i < linhas_; i++)
        nova_coluna[i] = matriz_[i * colunas_ + indice];

    Matriz<T> novo(linhas_, 1, nova_coluna); // Nova matriz com ordem nx1
    return novo;
}

template <typename T>
void Matriz<T>::redimensionar(int linhas, int colunas)
{
    if (linhas < 0 || colunas < 0)
        throw std::invalid_argument("Erro: Valores devem ser positivos.");

    const size_t novo_linhas = static_cast<size_t>(linhas);
    const size_t novo_colunas = static_cast<size_t>(colunas);
    const size_t novo_tamanho = novo_linhas * novo_colunas;

    if (novo_linhas == linhas_ && novo_colunas == colunas_)
        return; // Uai?

    // Nós não precisamos criar uma nova matriz nem nada do tipo, basta aumentar
    // o tamanho do vetor que guarda os dados (matriz), atualizar o índice dos
    // valores internos e atualizar os valores de linhas e colunas.

    // Nota: fazer resize em um vetor é equivalente a realocá-lo na memória. :)

    const size_t min_linhas = std::min(novo_linhas, linhas_);
    const size_t min_colunas = std::min(novo_colunas, colunas_);

    // Nós só vamos precisar shiftar valores se o número de COLUNAS mudar.
    // Se o novo número de colunas for maior, nós precisamos shiftar os valores
    // para direita começando de trás pra frente, para evitar sobrescrita.

    if (novo_colunas > colunas_) {
        // Mover linhas existentes de trás pra frente (evitando sobrescrita)
        matriz_.resize(novo_tamanho, T()); // T() ao invés de 0 para inicializar
        for (size_t i = min_linhas; i > 0; --i) {
            const size_t lin = i - 1;

            auto *dest = &matriz_[lin * novo_colunas];
            auto *src = &matriz_[lin * colunas_];
            std::memmove(dest, src, min_colunas * sizeof(T));

            // std::memmove não esvazia as posições antigas, precisamos zerar
            auto *fill_pos = &matriz_[lin * novo_colunas + min_colunas];
            std::fill_n(fill_pos, novo_colunas - min_colunas, T());
        }
    } else if (novo_colunas < colunas_) {
        // Mover linhas esquerda pra direita, sem risco de sobrescrita
        for (size_t lin = 0; lin < min_linhas; ++lin) {
            auto *dest = &matriz_[lin * novo_colunas];
            auto *src = &matriz_[lin * colunas_];
            std::memmove(dest, src, min_colunas * sizeof(T));
        }
        matriz_.resize(novo_tamanho, T());
    } else {
        // Colunas permanecem as mesmas, redimensionar de acordo com as linhas
        matriz_.resize(novo_tamanho, T());
    }

    linhas_ = novo_linhas;
    colunas_ = novo_colunas;
}

template <typename T>
void Matriz<T>::trocar_linhas(int indice1, int indice2)
{
    if (indice1 < 0 || indice2 < 0)
        throw std::out_of_range("Erro: Índice/s de linha negativo/s.");

    if ((size_t)indice1 >= linhas_ || (size_t)indice2 >= linhas_)
        throw std::out_of_range("Erro: Índice/s de linha além do limite da matriz.");

    auto start1 = matriz_.begin() + indice1 * colunas_; // inicio do intervalo [
    auto last1 = start1 + colunas_;                     // fim do intervalo    )
    auto start2 = matriz_.begin() + indice2 * colunas_; // inicio do destino
    std::swap_ranges(start1, last1, start2);
}

template <typename T>
void Matriz<T>::trocar_colunas(int indice1, int indice2)
{

    if (indice1 < 0 || indice2 < 0)
        throw std::out_of_range("Erro: Índice/s de coluna negativo/s.");

    if ((size_t)indice1 >= colunas_ || (size_t)indice2 >= colunas_)
        throw std::out_of_range("Erro: Índice/s de coluna além do limite da matriz.");

    for (size_t i = 0; i < linhas_; i++)
        std::swap(matriz_[i * colunas_ + indice1], matriz_[i * colunas_ + indice2]);
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

template <typename U>
std::ostream &operator<<(std::ostream &os, const Matriz<U> &u)
{
    const size_t largura = 10;

    for (size_t i = 0; i < u.linhas_; ++i) {
        for (size_t j = 0; j < u.colunas_; ++j) {
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

} // namespace ifnum