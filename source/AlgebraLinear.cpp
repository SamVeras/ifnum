/*!
 * @file AlgebraLinear.cpp
 * @brief Implementações auxiliares para operações de álgebra linear.
 *
 * Define funções não-template relacionadas à manipulação de matrizes.
 */

#include "AlgebraLinear.hpp"

namespace ifnum
{
// Ler um pouco de pivotamento em http://e-maxx.ru/bookz/files/numerical_recipes.pdf
/*!
 * @brief Decompõe uma matriz quadrada em L, U e P com pivotamento completo.
 *
 * A função realiza a decomposição LU com pivotamento completo, retornando:
 * - L: matriz triangular inferior,
 * - U: matriz triangular superior,
 * - P: matriz de permutação.
 *
 * @param A Matriz quadrada a ser decomposta.
 * @return Tupla contendo as matrizes L, U e P, respectivamente.
 *
 * @throws std::runtime_error Se a matriz for singular.
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
 * @brief Resolve um sistema linear utilizando a decomposição LU com pivotamento completo.
 *
 * Resolve o sistema \( Ax = b \) através de:
 * 1. Decomposição LU com pivotamento completo.
 * 2. Substituição direta e reversa para encontrar o vetor solução.
 *
 * @param A Matriz dos coeficientes (matriz quadrada).
 * @param b Vetor coluna com os termos independentes.
 * @return Vetor solução do sistema.
 *
 * @throws std::runtime_error Se a decomposição não for possível (matriz singular).
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