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
    size_t tamanho; // Mover 'tamanho' para antes de 'coordenadas'
    std::vector<T> coordenadas;

  public:
    Vetor(std::vector<T> valores); // Construtor

    void imprimir() const;
    double norma() const;
    Vetor<T> normalizar() const;

    Vetor<T> operator+(const Vetor &outro) const;
    Vetor<T> operator-(const Vetor &outro) const;
    T operator*(const Vetor &outro) const;

    bool operator==(const Vetor &outro) const;
    bool operator!=(const Vetor &outro) const;

    // Métodos para obter o tamanho e as coordenadas
    size_t obter_tamanho() const;
    std::vector<T> obter_coordenadas() const;

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Vetor<U> &v);
};

// Implementação dos métodos

/*!
 * @brief Retorna o tamanho (dimensão) do vetor.
 *
 * @return Número de coordenadas do vetor.
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
size_t Vetor<T>::obter_tamanho() const
{
    return tamanho;
}

/*!
 * @brief Retorna as coordenadas do vetor como um std::vector.
 *
 * @return Vetor contendo as coordenadas.
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
std::vector<T> Vetor<T>::obter_coordenadas() const
{
    return coordenadas;
}

/*!
 * @brief Construtor da classe Vetor.
 *
 * Inicializa o vetor com os valores fornecidos.
 *
 * @param valores Vetor com os valores das coordenadas.
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
Vetor<T>::Vetor(std::vector<T> valores) : tamanho(valores.size()), coordenadas(valores)
{
} // Inicializa 'tamanho' antes de 'coordenadas'

/*!
 * @brief Imprime o vetor no formato (x, y, z, ...).
 *
 * Exibe o vetor no terminal.
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
void Vetor<T>::imprimir() const
{
    std::cout << "(";
    for (size_t i = 0; i < tamanho; i++) {
        std::cout << coordenadas[i];
        if (i < tamanho - 1)
            std::cout << ", ";
    }
    std::cout << ")\n";
}

/*!
 * @brief Calcula a norma (magnitude) do vetor.
 *
 * Usa a raiz quadrada da soma dos quadrados das coordenadas.
 *
 * @return Norma do vetor (double).
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
double Vetor<T>::norma() const
{
    double soma = 0;
    for (T val : coordenadas)
        soma += val * val;
    return std::sqrt(soma);
}

/*!
 * @brief Retorna uma versão normalizada do vetor.
 *
 * Divide cada componente pela norma. Lança exceção se a norma for zero.
 *
 * @return Vetor unitário correspondente.
 *
 * @throws std::runtime_error Se o vetor for nulo.
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
Vetor<T> Vetor<T>::normalizar() const
{
    double n = norma();
    if (n == 0)
        throw std::runtime_error("Não é possível normalizar um vetor nulo");
    Vetor resultado(*this);
    for (T &val : resultado.coordenadas)
        val /= n;
    return resultado;
}

/*!
 * @brief Soma vetorial.
 *
 * Soma componente a componente entre dois vetores do mesmo tamanho.
 *
 * @param outro Vetor a ser somado.
 * @return Resultado da soma.
 *
 * @throws std::invalid_argument Se os vetores tiverem tamanhos diferentes.
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
Vetor<T> Vetor<T>::operator+(const Vetor &outro) const
{
    if (tamanho != outro.tamanho)
        throw std::invalid_argument("Os vetores devem ter o mesmo tamanho");
    Vetor resultado(*this);
    for (size_t i = 0; i < tamanho; i++)
        resultado.coordenadas[i] += outro.coordenadas[i];
    return resultado;
}

/*!
 * @brief Subtração vetorial.
 *
 * Subtrai componente a componente entre dois vetores do mesmo tamanho.
 *
 * @param outro Vetor a ser subtraído.
 * @return Resultado da subtração.
 *
 * @throws std::invalid_argument Se os vetores tiverem tamanhos diferentes.
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
Vetor<T> Vetor<T>::operator-(const Vetor &outro) const
{
    if (tamanho != outro.tamanho)
        throw std::invalid_argument("Os vetores devem ter o mesmo tamanho");
    Vetor resultado(*this);
    for (size_t i = 0; i < tamanho; i++)
        resultado.coordenadas[i] -= outro.coordenadas[i];
    return resultado;
}

/*!
 * @brief Produto escalar entre dois vetores.
 *
 * Multiplica e soma os pares de componentes dos vetores.
 *
 * @param outro Vetor com o qual calcular o produto escalar.
 * @return Resultado do produto escalar.
 *
 * @throws std::invalid_argument Se os vetores tiverem tamanhos diferentes.
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
T Vetor<T>::operator*(const Vetor &outro) const
{
    if (tamanho != outro.tamanho)
        throw std::invalid_argument("Os vetores devem ter o mesmo tamanho");
    T produto = 0;
    for (size_t i = 0; i < tamanho; i++)
        produto += coordenadas[i] * outro.coordenadas[i];
    return produto;
}
/*!
 * @brief Verifica se dois vetores são iguais.
 *
 * Compara as coordenadas diretamente.
 *
 * @param outro Vetor a ser comparado.
 * @return true se iguais, false caso contrário.
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
bool Vetor<T>::operator==(const Vetor &outro) const
{
    return coordenadas == outro.coordenadas;
}

/*!
 * @brief Verifica se dois vetores são diferentes.
 *
 * Inverso do operador ==.
 *
 * @param outro Vetor a ser comparado.
 * @return true se diferentes, false caso contrário.
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
bool Vetor<T>::operator!=(const Vetor &outro) const
{
    return !(*this == outro);
}

/*!
 * @brief Sobrecarga do operador << para impressão de vetor.
 *
 * Imprime o vetor no formato (x, y, z, ...).
 *
 * @param os Stream de saída.
 * @param v Vetor a ser impresso.
 * @return Referência para o stream de saída.
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
std::ostream &operator<<(std::ostream &os, const Vetor<T> &v)
{
    os << "(";
    for (size_t i = 0; i < v.tamanho; i++) {
        os << v.coordenadas[i];
        if (i < v.tamanho - 1)
            os << ", ";
    }
    os << ")";
    return os;
}

} // namespace ifnum
