#include "Matriz.hpp"
#include <tuple>
using namespace std;

namespace ifnum
{

/*!
    * @brief Resolve um sistema linear pelo método de substituição simples.
    *
    * Recebe uma matriz nxn com a parte inferior zerada e um vetor e retorna a solução do sistema
    *
    * @param matriz Matriz dos coeficientes
    * @param b Vetor
    * @param x Vetor solução do sistema
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
 * @brief Resolve um sistema linear pelo método de  retro substituição.
 *
 * Recebe uma matriz nxn com a parte superior zerada e um vetor e retorna a solução do sistema
 *
 * @param matriz Matriz dos coeficientes
 * @param b Vetor
 * @param x Vetor solução do sistema
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
 * @brief Resolve um sistema linear pelo método de substituição simples.
 *
 * Recebe uma matriz nxn com a parte inferior zerada e um vetor e retorna a solução do sistema
 *
 * @param matriz Matriz dos coeficientes
 *
 * @author Sofia Effting
 * @author Ana Julia Dalmora
 * @date 20/03/2025
*/
template <typename T>
Matriz<T> gauss(Matriz<T> &matriz, Matriz<T> &b)
{
    if (!verificar_matriz_quadrada(matriz)) {
        throw std::invalid_argument("Erro: Matriz não é quadrada.");
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
 * @brief Resolve um sistema linear pelo método de substituição simples.
 *
 * Recebe uma matriz nxn com a parte inferior zerada e um vetor e retorna a solução do sistema
 *
 * @param matriz Matriz dos coeficientes
 *
 * @author Sofia Effting
 * @author Ana Julia Dalmora
 * @date 20/03/2025
*/
template <typename T>
Matriz<T> gauss_jordan(Matriz<T> &matriz, Matriz<T> &b)
{
    if (!verificar_matriz_quadrada(matriz)) {
        throw std::invalid_argument("Erro: Matriz não é quadrada.");
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
        throw std::invalid_argument("Erro: Matriz não é quadrada.");
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
        throw std::invalid_argument("Erro: Matriz não é quadrada.");
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

// Ler um pouco de pivotamento em http://e-maxx.ru/bookz/files/numerical_recipes.pdf
/*!
 * @brief Decompoem uma matriz em L e U com pivotamento completo
 *
 * Decompoem uma matriz em L e U com pivotamento completo e retorna junto a L e U um matriz de permutação.
 *
 * @param A matriz quadrada que será decomposta
 * @param L matriz quadrada triangular inferiro
 * @param U matriz quadrada triangular superior
 * @param P matriz qudrada de permutação
 *
 * @author Lucas Andrei
 * @author Giovani Zanella
 * @date 03/04/2025
*/
std::tuple<Matriz<double>, Matriz<double>, Matriz<double>> decomposicaoLU(const Matriz<double> &A)
{

    size_t n = A.linhas();
    Matriz<double> L(n, n);
    Matriz<double> U = A;
    Matriz<double> P(n, n);

    // Inicializar P como identidade
    for (size_t i = 0; i < n; i++) {
        P(i, i) = 1;
    }

    for (size_t k = 0; k < n; k++) {
        // Pivotamento completo
        double maxValor = 0.0;
        size_t maxLinha = k, maxColuna = k;

        for (size_t i = k; i < n; i++) {
            for (size_t j = k; j < n; j++) {
                if (std::abs(U(i, j)) > maxValor) {
                    maxValor = std::abs(U(i, j));
                    maxLinha = i;
                    maxColuna = j;
                }
            }
        }

        if (maxValor == 0.0) {
            throw std::runtime_error("Matriz singular");
        }

        // Trocar linhas na matriz U e P
        U.trocar_linhas(k, maxLinha);
        P.trocar_linhas(k, maxLinha);
        L.trocar_linhas(k, maxLinha);

        // Trocar colunas na matriz U
        U.trocar_colunas(k, maxColuna);
        P.trocar_colunas(k, maxColuna);

        // Atualizar L e U
        for (size_t i = k + 1; i < n; i++) {
            L(i, k) = U(i, k) / U(k, k);
            for (size_t j = k; j < n; j++) {
                U(i, j) -= L(i, k) * U(k, j);
            }
        }
    }

    // Completar a diagonal de L com 1s
    for (size_t i = 0; i < n; i++) {
        L(i, i) = 1.0;
    }

    return std::make_tuple(L, U, P);
}

/*!
 * @brief Resolve um sistema linear pelo método de substituição simples.
 *
 * Recebe uma matriz nxn com a parte inferior zerada e um vetor e retorna a solução do sistema
 *
 * @param matriz Matriz dos coeficientes
 *
 * @author Lucas Andrei
 * @author Giovani Zanella
 * @date 03/04/2025
*/
Matriz<double> resolverLU(const Matriz<double> &A, const Matriz<double> &b)
{
    auto [L, U, P] = decomposicaoLU(A);

    // Resolver Pb = Ly
    Matriz<double> Pb = P * b;
    Matriz<double> y = reversub(L, Pb);

    // Resolver Ux = y
    Matriz<double> x = sub(U, y);

    return x;
}

} // namespace ifnum
