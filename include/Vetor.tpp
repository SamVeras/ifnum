#ifdef __INTELLISENSE__
#include "Vetor.hpp"
#endif

namespace ifnum
{
/*!
 * @brief Construtor que inicializa o vetor com uma lista de valores.
 *
 * Define o tamanho e os elementos do vetor a partir do vetor passado como parâmetro.
 *
 * @tparam T Tipo dos elementos do vetor.
 * @param valores Vetor com os valores dos elementos.
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
Vetor<T>::Vetor(const std::vector<T> &valores) : tamanho_(valores.size()), elementos_(valores)
{
}

/*!
 * @brief Construtor que inicializa o vetor com um tamanho fixo e dados fornecidos.
 *
 * Copia os elementos de `dados` para o vetor até o limite de `tamanho`. Se `dados` tiver menos elementos,
 * o restante será preenchido com valores padrão de T. Caso `dados` seja vazio, o vetor será totalmente
 * preenchido com valores padrão.
 *
 * @tparam T Tipo dos elementos do vetor.
 * @param tamanho Tamanho final do vetor.
 * @param dados Vetor com os dados a serem copiados (opcional).
 *
 * @author Samuel Veras
 * @date 09/04/2025
 */

template <typename T>
Vetor<T>::Vetor(size_t tamanho, const std::vector<T> &dados)
    : tamanho_(tamanho), elementos_(tamanho)
{
    // Tamanho pode ser maior, igual ou menor que dados.size()
    size_t min = std::min(tamanho, dados.size());
    std::copy_n(dados.begin(), min, elementos_.begin());
}

/*!
 * @brief Retorna o tamanho (dimensão) do vetor.
 *
 * @tparam T Tipo dos elementos do vetor.
 * @return Número de delementos do vetor.
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
size_t Vetor<T>::tamanho() const
{
    return tamanho_;
}

/*!
 * @brief Retorna os elementos do vetor como um std::vector.
 *
 * @tparam T Tipo dos elementos do vetor.
 * @return std::vector contendo os elementos.
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
std::vector<T> Vetor<T>::vector() const
{
    return elementos_;
}

/*!
 * @brief Imprime o vetor no formato (x, y, z, ...).
 *
 * Exibe o vetor no terminal.
 * 
 * @tparam T Tipo dos elementos do vetor.
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
void Vetor<T>::imprimir() const
{
    std::cout << "(";
    for (size_t i = 0; i < tamanho_; i++) {
        std::cout << elementos_[i];
        if (i < tamanho_ - 1)
            std::cout << ", ";
    }
    std::cout << ")\n";
}

/*!
 * @brief Calcula a norma (magnitude) do vetor.
 *
 * Usa a raiz quadrada da soma dos quadrados dos elementos.
 * @tparam T Tipo dos elementos do vetor.
 * @return Norma do vetor (double).
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
double Vetor<T>::norma() const
{
    double soma = 0;
    for (T val : elementos_)
        soma += val * val;
    return std::sqrt(soma);
}

/*!
 * @brief Retorna uma versão normalizada do vetor.
 *
 * Cada componente é dividido pela norma do vetor.
 *
 * @tparam T Tipo dos elementos do vetor.
 * @return Vetor unitário correspondente.
 *
 * @throws std::runtime_error Se a norma for zero ou o vetor for nulo.
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
    for (T &val : resultado.elementos_)
        val /= n;
    return resultado;
}

/*!
 * @brief Soma vetorial.
 *
 * Soma componente a componente entre dois vetores do mesmo tamanho.
 *
 * @tparam T Tipo dos elementos do vetor.
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
    if (tamanho_ != outro.tamanho_)
        throw std::invalid_argument("Os vetores devem ter o mesmo tamanho");
    Vetor resultado(*this);
    for (size_t i = 0; i < tamanho_; i++)
        resultado.elementos_[i] += outro.elementos_[i];
    return resultado;
}

/*!
 * @brief Subtração vetorial.
 *
 * Subtrai componente a componente entre dois vetores do mesmo tamanho.
 *
 * @tparam T Tipo dos elementos do vetor.
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
    if (tamanho_ != outro.tamanho_)
        throw std::invalid_argument("Os vetores devem ter o mesmo tamanho");
    Vetor resultado(*this);
    for (size_t i = 0; i < tamanho_; i++)
        resultado.elementos_[i] -= outro.elementos_[i];
    return resultado;
}

/*!
 * @brief Produto escalar entre dois vetores.
 *
 * Multiplica e soma os pares de componentes dos vetores.
 *
 * @tparam T Tipo dos elementos do vetor.
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
    if (tamanho_ != outro.tamanho_)
        throw std::invalid_argument("Os vetores devem ter o mesmo tamanho");
    T produto = 0;
    for (size_t i = 0; i < tamanho_; i++)
        produto += elementos_[i] * outro.elementos_[i];
    return produto;
}
/*!
 * @brief Verifica se dois vetores são iguais.
 *
 * Compara os elementos diretamente.
 *
 * @tparam T Tipo dos elementos do vetor.
 * @param outro Vetor a ser comparado.
 * @return true se iguais, false caso contrário.
 *
 * @author Lucas Andrei
 * @date 06/03/2025
 */
template <typename T>
bool Vetor<T>::operator==(const Vetor &outro) const
{
    return elementos_ == outro.elementos_;
}

/*!
 * @brief Verifica se dois vetores são diferentes.
 *
 * Inverso do operador ==.
 *
 * @tparam T Tipo dos elementos do vetor.
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
 * @tparam T Tipo dos elementos do vetor.
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
    for (size_t i = 0; i < v.tamanho_; i++) {
        os << v.elementos_[i];
        if (i < v.tamanho_ - 1)
            os << ", ";
    }
    os << ")";
    return os;
}

} // namespace ifnum