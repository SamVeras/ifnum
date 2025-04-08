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
    /* ---------------------------- CONSTRUTORES ---------------------------- */

    Matriz(size_t linhas, size_t colunas, const std::vector<T> &dados);
    Matriz(size_t linhas, size_t colunas); // Matriz nula

    /* ------------------------------- GETTERS ------------------------------ */

    size_t linhas() const;
    size_t colunas() const;
    std::vector<T> vector() const; // Retornar por valor para evitar modificação

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

/*!
 * @brief Calcula o determinante de matrizes 2x2 ou 3x3 utilizando a Regra de Sarrus.
 *
 * Esta função é válida apenas para matrizes quadradas de ordem 2 ou 3.
 * Para matrizes de ordem diferente, o retorno padrão é 0.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @return Determinante da matriz, ou 0 se a matriz não for 2x2 ou 3x3.
 *
 * @author Samuel Veras
 * @date 20/03/2025
 */
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

/*!
 * @brief Construtor da matriz com dados iniciais.
 *
 * Inicializa uma matriz com as dimensões especificadas e preenche com os dados fornecidos.
 * Caso o vetor de dados seja menor que a quantidade necessária, apenas os primeiros elementos são copiados.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 * @param dados Vetor com os elementos a serem copiados para a matriz.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
template <typename T>
Matriz<T>::Matriz(size_t linhas, size_t colunas, const std::vector<T> &dados)
    : linhas_(linhas), colunas_(colunas), matriz_(linhas * colunas)
{
    size_t count = std::min(matriz_.size(), dados.size());
    std::copy_n(dados.begin(), count, matriz_.begin());
}

/*!
 * @brief Construtor da matriz sem dados iniciais.
 *
 * Inicializa uma matriz com as dimensões especificadas e aloca espaço para os elementos,
 * deixando-os com valor padrão.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param linhas Número de linhas da matriz.
 * @param colunas Número de colunas da matriz.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
template <typename T>
Matriz<T>::Matriz(size_t linhas, size_t colunas)
    : linhas_(linhas), colunas_(colunas), matriz_(linhas * colunas)
{
}

/* --------------------------------- GETTERS -------------------------------- */

/*!
 * @brief Retorna a quantidade de linhas da matriz.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @return Número de linhas da matriz.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
template <typename T>
inline size_t Matriz<T>::linhas() const
{
    return this->linhas_;
}

/*!
 * @brief Retorna a quantidade de colunas da matriz.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @return Número de colunas da matriz.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
template <typename T>
inline size_t Matriz<T>::colunas() const
{
    return this->colunas_;
}

/*!
 * @brief Retorna uma cópia dos dados da matriz em formato de vetor linear.
 *
 * Os elementos são organizados em ordem linear conforme armazenados internamente.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @return Vetor contendo os elementos da matriz.
 *
 * @author Samuel Veras
 * @date 27/03/2025
 */
template <typename T>
inline std::vector<T> Matriz<T>::vector() const
{
    return matriz_;
}

/* --------------------------------- MÉTODOS -------------------------------- */

/*!
 * @brief Imprime a matriz no console.
 *
 * Utiliza a sobrecarga do operador de saída para exibir o conteúdo da matriz.
 *
 * @tparam T Tipo dos elementos da matriz.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
template <typename T>
void Matriz<T>::imprimir() const
{
    std::cout << (*this) << std::endl;
}

/*!
 * @brief Calcula o determinante da matriz.
 *
 * Utiliza a regra de Sarrus para matrizes de ordem até 3. Para ordens maiores, 
 * a funcionalidade ainda não está implementada.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @return Determinante da matriz.
 * @throws std::invalid_argument Se a matriz não for quadrada.
 *
 * @author Samuel Veras
 * @date 15/03/2025
 */
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

/*!
 * @brief Calcula o módulo (norma Euclidiana) de um vetor.
 *
 * A matriz deve ser um vetor coluna. Retorna a raiz quadrada da soma dos quadrados dos elementos.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @return Norma Euclidiana do vetor.
 * @throws std::invalid_argument Se a matriz não for um vetor coluna.
 *
 * @author Lucas Andrei
 * @date 27/02/2025
 */
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

/*!
 * @brief Retorna a transposta da matriz.
 *
 * Troca as linhas pelas colunas da matriz original.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @return Uma nova matriz transposta da original.
 *
 * @author Lucas Andrei
 * @date 27/02/2025
 */
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

/*!
 * @brief Calcula um autovalor da matriz utilizando o método do poder com normalização.
 *
 * Recebe um vetor inicial e itera até atingir a tolerância especificada ou o número máximo de repetições.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param other Vetor inicial (deve ser um vetor coluna com dimensões compatíveis).
 * @param tolerancia Erro aceitável para a convergência.
 * @param r Número máximo de iterações.
 * @return Valor aproximado do autovalor dominante.
 * @throws std::invalid_argument Se a matriz não for quadrada ou o vetor for inválido.
 * @throws std::runtime_error Se houver divisão por zero ao final do cálculo.
 *
 * @author Lucas Andrei
 * @date 27/02/2025
 */
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

/*!
 * @brief Retorna a linha da matriz no índice especificado como uma nova matriz.
 *
 * A linha extraída é retornada como uma matriz com uma única linha e múltiplas colunas.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param indice Índice da linha a ser extraída (inicia em 0).
 * @return Matriz contendo a linha especificada.
 * @throws std::out_of_range Se o índice for negativo ou estiver fora dos limites.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
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

/*!
 * @brief Retorna a coluna da matriz no índice especificado como uma nova matriz.
 *
 * A coluna extraída é retornada como uma matriz com uma única coluna e múltiplas linhas.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param indice Índice da coluna a ser extraída (inicia em 0).
 * @return Matriz contendo a coluna especificada.
 * @throws std::out_of_range Se o índice for negativo ou estiver fora dos limites.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
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

/*!
 * @brief Redimensiona a matriz para o número de linhas e colunas especificado.
 *
 * Preserva os dados existentes até onde for possível. Quando o número de colunas
 * muda, os elementos são realocados corretamente para manter a coerência dos dados.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param linhas Novo número de linhas.
 * @param colunas Novo número de colunas.
 * @throws std::invalid_argument Se linhas ou colunas forem negativas.
 *
 * @author Samuel Veras
 * @date 13/03/2025
 */
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

/*!
 * @brief Troca duas linhas da matriz entre si.
 *
 * Utiliza `std::swap_ranges` para trocar os elementos linha a linha.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param indice1 Índice da primeira linha.
 * @param indice2 Índice da segunda linha.
 * @throws std::out_of_range Se qualquer índice for negativo ou estiver fora dos limites da matriz.
 *
 * @author Samuel Veras
 * @date 20/03/2025
 */
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

/*!
 * @brief Troca duas colunas da matriz entre si.
 *
 * Realiza a troca elemento por elemento em cada linha.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param indice1 Índice da primeira coluna.
 * @param indice2 Índice da segunda coluna.
 * @throws std::out_of_range Se qualquer índice for negativo ou estiver fora dos limites da matriz.
 *
 * @author Samuel Veras
 * @date 20/03/2025
 */
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

/*!
 * @brief Acesso de leitura a um elemento da matriz.
 *
 * Retorna o valor na posição especificada da matriz.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param linha Índice da linha (inicia em 0).
 * @param coluna Índice da coluna (inicia em 0).
 * @return Valor do elemento na posição (linha, coluna).
 * @throws std::out_of_range Se os índices forem negativos ou estiverem fora dos limites.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
template <typename T>
T Matriz<T>::operator()(int linha, int coluna) const
{
    if (linha < 0 || coluna < 0)
        throw std::out_of_range("Erro: Índices negativos.");

    if ((size_t)linha >= linhas_ || (size_t)coluna >= colunas_)
        throw std::out_of_range("Erro: Índices fora dos limites da matriz.");

    return matriz_[linha * colunas_ + coluna];
}

/*!
 * @brief Acesso de escrita a um elemento da matriz.
 *
 * Retorna uma referência ao valor na posição especificada da matriz.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param linha Índice da linha (inicia em 0).
 * @param coluna Índice da coluna (inicia em 0).
 * @return Referência ao elemento na posição (linha, coluna).
 * @throws std::out_of_range Se os índices forem negativos ou estiverem fora dos limites.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
template <typename T>
T &Matriz<T>::operator()(int linha, int coluna)
{
    if (linha < 0 || coluna < 0)
        throw std::out_of_range("Erro: Índices negativos.");

    if ((size_t)linha >= linhas_ || (size_t)coluna >= colunas_)
        throw std::out_of_range("Erro: Índices fora dos limites da matriz.");

    return matriz_[linha * colunas_ + coluna];
}

/*!
 * @brief Operador unário de negação.
 *
 * Retorna uma nova matriz cujos elementos são os negativos da matriz original.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @return Nova matriz com os sinais dos elementos invertidos.
 *
 * @author Samuel Veras
 * @date 13/03/2025
 */
template <typename T>
inline Matriz<T> Matriz<T>::operator-() const
{
    Matriz<T> novo = *this;

    for (auto &e : novo.matriz_)
        e *= -1;

    return novo;
}

/*!
 * @brief Soma duas matrizes elemento a elemento.
 *
 * Retorna uma nova matriz com os elementos somados.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param other Outra matriz a ser somada.
 * @return Resultado da soma.
 * @throws std::invalid_argument Se as dimensões das matrizes forem diferentes.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
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

/*!
 * @brief Subtrai duas matrizes elemento a elemento.
 *
 * Retorna uma nova matriz com os elementos resultantes da subtração.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param other Outra matriz a ser subtraída.
 * @return Resultado da subtração.
 * @throws std::invalid_argument Se as dimensões das matrizes forem diferentes.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
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

/*!
 * @brief Multiplica todos os elementos da matriz por um escalar.
 *
 * Retorna uma nova matriz com cada elemento multiplicado pelo escalar dado.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param escalar Valor escalar a ser multiplicado.
 * @return Nova matriz resultante da multiplicação escalar.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
template <typename T>
Matriz<T> Matriz<T>::operator*(T escalar) const
{
    Matriz<T> novo(linhas_, colunas_);

    for (size_t i = 0; i < matriz_.size(); i++)
        novo.matriz_[i] = matriz_[i] * escalar;

    return novo;
}

/*!
 * @brief Divide todos os elementos da matriz por um escalar.
 *
 * Retorna uma nova matriz com cada elemento dividido pelo escalar dado.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param escalar Valor escalar divisor.
 * @return Nova matriz resultante da divisão escalar.
 * @throws std::invalid_argument Se o escalar for zero.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
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

/*!
 * @brief Multiplica duas matrizes.
 *
 * Retorna o produto matricial entre esta matriz e outra.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param outro Matriz a ser multiplicada.
 * @return Nova matriz resultante do produto.
 * @throws std::invalid_argument Se o número de colunas desta matriz for
 *         diferente do número de linhas da outra.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
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

/*!
 * @brief Soma outra matriz a esta matriz.
 *
 * Cada elemento da matriz atual é somado com o correspondente da outra matriz.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param other Matriz a ser somada.
 * @return Referência para esta matriz modificada.
 * @throws std::invalid_argument Se as matrizes tiverem ordens diferentes.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
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

/*!
 * @brief Subtrai outra matriz desta matriz.
 *
 * Cada elemento da matriz atual é subtraído com o correspondente da outra matriz.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param other Matriz a ser subtraída.
 * @return Referência para esta matriz modificada.
 * @throws std::invalid_argument Se as matrizes tiverem ordens diferentes.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
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

/*!
 * @brief Multiplica todos os elementos da matriz por um escalar.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param escalar Valor escalar multiplicador.
 * @return Referência para esta matriz modificada.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
template <typename T>
Matriz<T> &Matriz<T>::operator*=(T escalar)
{
    // return *this = *this * escalar;

    for (auto &e : matriz_)
        e *= escalar;

    return *this;
}

/*!
 * @brief Divide todos os elementos da matriz por um escalar.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param escalar Valor escalar divisor.
 * @return Referência para esta matriz modificada.
 * @throws std::invalid_argument Se o escalar for zero.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
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

/*!
 * @brief Compara duas matrizes quanto à igualdade.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param outro Matriz a ser comparada.
 * @return true se forem iguais, false caso contrário.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
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

/*!
 * @brief Compara duas matrizes quanto à desigualdade.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param outro Matriz a ser comparada.
 * @return true se forem diferentes, false caso contrário.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
template <typename T>
bool Matriz<T>::operator!=(const Matriz<T> &outro) const
{
    return !(*this == outro);
}

/*!
 * @brief Sobrecarga do operador de saída para impressão de matriz.
 *
 * Imprime os elementos da matriz formatados com largura fixa.
 *
 * @tparam U Tipo dos elementos da matriz.
 * @param os Stream de saída.
 * @param u Matriz a ser impressa.
 * @return Stream de saída.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
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

/*!
 * @brief Multiplica escalar por matriz (escalar à esquerda).
 *
 * Permite a multiplicação de um escalar por uma matriz, com escalar antes.
 *
 * @tparam U Tipo dos elementos da matriz.
 * @param escalar Valor escalar multiplicador.
 * @param matriz Matriz a ser multiplicada.
 * @return Nova matriz resultante da multiplicação.
 *
 * @author Samuel Veras
 * @date 27/02/2025
 */
template <typename U>
Matriz<U> operator*(U escalar, Matriz<U> &matriz)
{
    return matriz * escalar;
}

} // namespace ifnum