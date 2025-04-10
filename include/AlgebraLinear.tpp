/*!
 * @file AlgebraLinear.tpp
 * @brief Implementações de templates para operações de álgebra linear.
 *
 * Contém as definições das funções template declaradas em AlgebraLinear.hpp.
 */

#ifdef __INTELLISENSE__
#include "AlgebraLinear.hpp"
#endif

namespace ifnum
{
/*!
 * @brief Resolve um sistema triangular superior via substituição reversa.
 *
 * Recebe uma matriz com a parte inferior zerada e um vetor, e retorna o vetor solução.
 *
 * @param matriz Matriz triangular superior.
 * @param b Vetor de constantes.
 * @return Vetor solução do sistema.
 *
 * @author Lucas Andrei
 * @author Giovani Zanella
 * @date 20/03/2025
 */
template <typename T>
Matriz<T> sub(Matriz<T> &matriz, Matriz<T> &b)
{
    int n = static_cast<int>(matriz.linhas());
    Matriz<T> x(n, 1);

    for (int i = n - 1; i >= 0; i--) {
        T soma = 0;
        for (int j = i + 1; j < n; j++) {
            soma += matriz(i, j) * x(j, 0);
        }
        x(i, 0) = (b(i, 0) - soma) / matriz(i, i);
    }

    return x;
}

/*!
 * @brief Resolve um sistema triangular inferior via substituição direta.
 *
 * Recebe uma matriz com a parte superior zerada e um vetor, e retorna o vetor solução.
 *
 * @param matriz Matriz triangular inferior.
 * @param b Vetor de constantes.
 * @return Vetor solução do sistema.
 *
 * @author Lucas Andrei
 * @author Giovani Zanella
 * @date 20/03/2025
 */
template <typename T>
Matriz<T> reversub(const Matriz<T> &matriz, const Matriz<T> &b)
{
    int n = static_cast<int>(matriz.linhas());
    Matriz<T> x(n, 1);

    for (int i = 0; i < n; i++) {
        T soma = 0;
        for (int j = 0; j < i; j++) {
            soma += matriz(i, j) * x(j, 0);
        }
        x(i, 0) = (b(i, 0) - soma) / matriz(i, i);
    }

    return x;
}

/*!
 * @brief Verifica se uma matriz é quadrada.
 *
 * @tparam T Tipo dos elementos da matriz.
 * @param matriz A matriz a ser verificada.
 * @return true se a matriz for quadrada; false caso contrário.
 *
 * @author Sofia Effting
 * @author Ana Julia Dalmora
 * @author Samuel Veras
 * @date 20/03/2025
 */
template <typename T>
bool verificar_matriz_quadrada(Matriz<T> matriz)
{
    if (matriz.colunas() != matriz.linhas())
        return false;
    return true;
}

/*!
 * @brief Aplica o método de eliminação de Gauss para escalonar uma matriz.
 *
 * Realiza a triangularização superior de uma matriz de coeficientes e modifica o vetor de constantes correspondente.
 * Não realiza substituição para encontrar a solução — apenas escalona o sistema.
 *
 * @param matriz Matriz dos coeficientes (modificada no processo).
 * @param b Vetor de constantes do sistema (modificado no processo).
 * @return Matriz escalonada.
 *
 * @throws std::invalid_argument Se a matriz não for quadrada.
 *
 * @author Sofia Effting
 * @author Ana Julia Dalmora
 * @date 20/03/2025
 */
template <typename T>
Matriz<T> gauss(Matriz<T> &matriz, Matriz<T> &b)
{
    if (!verificar_matriz_quadrada(matriz)) {
        throw std::invalid_argument("Matriz não é quadrada.");
    };
    int n = static_cast<int>(matriz.linhas());

    for (int i = 0; i < n - 1; ++i) {
        for (int k = i + 1; k < n; ++k) {
            T fator = matriz(k, i) / matriz(i, i);

            for (int j = i; j < n; ++j) {
                matriz(k, j) -= matriz(i, j) * fator;
            }

            b(k, 0) -= b(i, 0) * fator;
        }
    }

    return matriz;
}

/*!
 * @brief Aplica o método de Gauss-Jordan para resolver um sistema linear.
 *
 * Executa o escalonamento direto seguido do escalonamento reverso, resultando na matriz identidade e no vetor solução.
 *
 * @param matriz Matriz dos coeficientes (modificada no processo).
 * @param b Vetor de constantes do sistema (modificado no processo e se torna o vetor solução).
 * @return Matriz identidade resultante do processo.
 *
 * @throws std::invalid_argument Se a matriz não for quadrada.
 *
 * @author Sofia Effting
 * @author Ana Julia Dalmora
 * @date 20/03/2025
 */
template <typename T>
Matriz<T> gauss_jordan(Matriz<T> &matriz, Matriz<T> &b)
{
    if (!verificar_matriz_quadrada(matriz)) {
        throw std::invalid_argument("Matriz não é quadrada.");
    };
    int n = static_cast<int>(matriz.linhas());

    // Aplicação do escalonamento direto (Gauss)
    gauss(matriz, b);

    // Aplicação do escalonamento reverso (Jordan)
    for (int i = n - 1; i >= 0; --i) {
        T divisor = matriz(i, i);
        for (int j = 0; j < n; ++j) {
            matriz(i, j) /= divisor;
        }
        b(i, 0) /= divisor;

        for (int k = i - 1; k >= 0; --k) {
            T fator = matriz(k, i);
            for (int j = 0; j < n; ++j) {
                matriz(k, j) -= matriz(i, j) * fator;
            }
            b(k, 0) -= b(i, 0) * fator;
        }
    }

    return matriz;
}

/*!
 * @brief Calcula a matriz U.
 *
 * Recebe uma matriz quadrada e calcula a matriz U de LU.
 *
 * @param matriz Matriz quadrada
 *
 * @author Lucas Andrei
 * @author Giovani Zanella
 * @date 27/03/2025
*/
template <typename T>
Matriz<T> retorna_U(Matriz<T> &matriz)
{
    if (!verificar_matriz_quadrada(matriz)) {
        throw std::invalid_argument("Matriz não é quadrada.");
    }

    int n = static_cast<int>(matriz.linhas());

    for (int i = 0; i < n - 1; ++i) {
        for (int k = i + 1; k < n; ++k) {
            T fator = matriz(k, i) / matriz(i, i);

            for (int j = i; j < n; ++j) {
                matriz(k, j) -= matriz(i, j) * fator;
            }
        }
    }

    return matriz; // Agora retorna apenas a matriz U
}

/*!
* @brief Calcula a matriz L
*
* Recebe uma matriz quadrada e calcula a matriz L de LU
*
* @param matriz Matriz dos coeficientes
*
* @author Lucas Andrei
* @author Giovani Zanella
* @date 27/03/202
*/
template <typename T>
Matriz<T> retorna_L(Matriz<T> &matriz)
{
    if (!verificar_matriz_quadrada(matriz)) {
        throw std::invalid_argument("Matriz não é quadrada.");
    }

    int n = static_cast<int>(matriz.linhas());
    Matriz<T> L(n, n); // Criamos uma nova matriz L

    // Inicializa a matriz L com a identidade (valores 1 na diagonal e 0 fora da diagonal)
    for (int i = 0; i < n; ++i) {
        L(i, i) = 1; // Diagonal principal é 1
        for (int j = i + 1; j < n; ++j) {
            L(i, j) = 0; // Valores acima da diagonal são 0
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int k = i + 1; k < n; ++k) {
            T fator = matriz(k, i) / matriz(i, i);
            L(k, i) = fator; // Armazena o fator na matriz L

            for (int j = i; j < n; ++j) {
                // Atualiza a matriz original (ou já modificada) para a próxima iteração
                matriz(k, j) -= matriz(i, j) * fator;
            }
        }
    }

    return L; // Retorna a matriz L
}

} // namespace ifnum