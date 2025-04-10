#include "Matriz.hpp"
#include <tuple>
using namespace std;

namespace ifnum
{

template <typename T>
Matriz<T> sub(Matriz<T> &matriz, Matriz<T> &b)
/*
 * @brief Resolve um sistema linear pelo método de substituição simples.
 * 
 * Recebe uma matriz nxn com a parte inferior zerada e um vetor e retorna a solução do sistema
 * 
 * @param matriz Matriz dos coeficientes
 * @param b Vetor 
 * @param x Vetor solução do sistema
 * 
 * @Autors Lucas Andrei e Giovani
 * @date 20/03/2025
 * @modified 20/03/2025
*/
{
    int n = static_cast<int>(matriz.linhas());
    Matriz<T> x(n, 1);

    for (int i = n - 1; i >= 0; i--) {
        T soma = 0;
        for (int j = i + 1; j < n; j++) {
            soma += matriz(i, j) * x(j, 0);
        }
        if (matriz(i,i)==0){
            throw std::invalid_argument("Sistema não é Possivel e deteminado");
        }
        x(i, 0) = (b(i, 0) - soma) / matriz(i, i);
    }

    return x;
}

template <typename T>
Matriz<T> reversub(const Matriz<T> &matriz,const Matriz<T> &b)
/*
 * @brief Resolve um sistema linear pelo método de  retro substituição.
 * 
 * Recebe uma matriz nxn com a parte superior zerada e um vetor e retorna a solução do sistema
 * 
 * @param matriz Matriz dos coeficientes
 * @param b Vetor 
 * @param x Vetor solução do sistema
 * 
 * @Autors Lucas Andrei e Giovani
 * @date 20/03/2025
 * @modified 20/03/2025
*/
{
    int n = static_cast<int>(matriz.linhas());
    Matriz<T> x(n, 1);

    for (int i = 0; i < n; i++) {
        T soma = 0;
        for (int j = 0; j < i; j++) {
            soma += matriz(i, j) * x(j, 0);
        }
        if (matriz(i,i)==0){
            throw std::invalid_argument("Sistema não é Possivel e deteminado");
        }
        x(i, 0) = (b(i, 0) - soma) / matriz(i, i);
    }

    return x;
}

template <typename T>
bool verificar_matriz_quadrada(Matriz<T> matriz)
{
    if (matriz.colunas() != matriz.linhas())
        return false;
    return true;
}

template <typename T>
Matriz<T> gauss(Matriz<T> &matriz, Matriz<T> &b)
/*
 * @brief Descrição simples da função
 * 
 * Descrição detalahda da função
 * 
 * @param a faz tal coisa
 * @param b serve para guardar alguma coisa
 * 
 * @Autors Pessoa a, Pessoa b, ... 
 * @date 00/00/0000
 * @modified 00/00/0000
*/
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

template <typename T>
Matriz<T> gauss_jordan(Matriz<T> &matriz, Matriz<T> &b)
/*
 * @brief Descrição simples da função
 * 
 * Descrição detalahda da função
 * 
 * @param a faz tal coisa
 * @param b serve para guardar alguma coisa
 * 
 * @Autors Pessoa a, Pessoa b, ... 
 * @date 00/00/0000
 * @modified 00/00/0000
*/

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

template <typename T>
Matriz<T> retorna_U(Matriz<T> &matriz)
/*
 * @brief Calcula a matriz U.
 * 
 * Recebe uma matriz quadrada e calcula a matriz U de LU.
 * 
 * @param matriz Matriz quadrada
 * 
 * @Autors Lucas A. C. Marin e Giovani Z.
 * @date 27/03/2025
 * @modified 27/03/2025
*/
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
    
    return matriz;  // Agora retorna apenas a matriz U    
}

template <typename T>
Matriz<T> retorna_L(Matriz<T>& matriz)
/*
 * @brief Calcula a matriz L 
 * 
 * Recebe uma matriz quadrada e calcula a matriz L de LU
 * 
 * @param matriz Matriz dos coeficientes
 * 
 * @Autors Lucas A. C. Marin e Giovani Z. 
 * @date 27/03/2025
 * @modified 27/03/2025
*/
{
    if (!verificar_matriz_quadrada(matriz)) {
        throw std::invalid_argument("Erro: Matriz não é quadrada.");
    }

    int n = static_cast<int>(matriz.linhas());
    Matriz<T> L(n, n);  // Criamos uma nova matriz L

    // Inicializa a matriz L com a identidade (valores 1 na diagonal e 0 fora da diagonal)
    for (int i = 0; i < n; ++i) {
        L(i, i) = 1;  // Diagonal principal é 1
        for (int j = i + 1; j < n; ++j) {
            L(i, j) = 0;  // Valores acima da diagonal são 0
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int k = i + 1; k < n; ++k) {
            T fator = matriz(k, i) / matriz(i, i);
            L(k, i) = fator;  // Armazena o fator na matriz L
    
            for (int j = i; j < n; ++j) {
                // Atualiza a matriz original (ou já modificada) para a próxima iteração
                matriz(k, j) -= matriz(i, j) * fator;
            }
        }
    }

    return L;  // Retorna a matriz L
}

// Ler um pouco de pivotamento em http://e-maxx.ru/bookz/files/numerical_recipes.pdf
std::tuple<Matriz<double>, Matriz<double>, Matriz<double>> decomposicaoLU(const Matriz<double>& A) 
/*
 * @brief Decompoem uma matriz em L e U com pivotamento completo
 * 
 * Decompoem uma matriz em L e U com pivotamento completo e retorna junto a L e U um matriz de permutação. 
 * 
 * @param A matriz quadrada que será decomposta
 * @param L matriz quadrada triangular inferiro
 * @param U matriz quadrada triangular superior
 * @param P matriz qudrada de permutação
 * 
 * 
 * @Autors Lucas A. C. Marin e Giovani Z.
 * @date 03/04/2025
 * @modified 03/04/2025
*/
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
        size_t maxLinha = k, maxColuna = k; // Guarda os indices do maior valor. 
        
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

Matriz<double> resolverLU(const Matriz<double>& A, const Matriz<double>& b)
/*
 * @brief Resolve um sistema linear pelo método Ax=b
 * 
 * Recebe as matrizes LU e realiza a resolução do sistema pelo método Ax=b
 * 
 * @param A Matriz principal
 * @param b Vetor com os resultados de A * x
 * @param L Matriz triangular superior
 * @param U Matriz triangula inferior
 * @param P Matriz de permutação.
 * @param Pb Mariz com o novo b permutado. 
 * @param y Matriz com a resposta de y de L * y = b
 * @param x Matriz com os valores de x de U * x = y
 * 
 * @Autors Lucas A. C. Marin e Giovani Z.
 * @date 03/04/2025
 * @modified 03/04/2025
*/
{
    auto [L, U, P] = decomposicaoLU(A);
    L.imprimir();    
    // Resolver Pb = Ly
    Matriz<double> Pb = P * b;
    Matriz<double> y = reversub(L, Pb);
    
    // Resolver Ux = y
    Matriz<double> x = sub(U, y);
    
    return x;
}

} // namespace ifnum
