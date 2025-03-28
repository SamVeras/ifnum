#include "Matriz.hpp"

namespace ifnum
{

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

    Matriz<T> result = (matriz*x -b) * (matriz *x -b);

    return result;
}

template <typename T>
Matriz<T> reversub(const Matriz<T> &matriz,const Matriz<T> &b)
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
    Matriz<T> result = (matriz*x -b) * (matriz *x -b);

    return result;
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
template <typename T>
void pivotamento_completoU(Matriz<T>& matriz, Matriz<T>& vetor) {
    int n = static_cast<int>(matriz.linhas());

    if (!verificar_matriz_quadrada(matriz)) {
        throw std::invalid_argument("Erro: Matriz não é quadrada.");
    }

    for (int i = 0; i < n - 1; ++i) {
        // Encontrar o maior elemento absoluto na matriz para pivotamento
        int linha_pivot = i;
        int coluna_pivot = i;
        T max_val = std::abs(matriz(i, i));

        for (int k = i; k < n; ++k) {
            for (int l = i; l < n; ++l) {
                if (std::abs(matriz(k, l)) > max_val) {
                    max_val = std::abs(matriz(k, l));
                    linha_pivot = k;
                    coluna_pivot = l;
                }
            }
        }

        // Trocar as linhas no caso de um pivotamento
        if (linha_pivot != i) {
            for (int j = 0; j < n; ++j) {
                std::swap(matriz(i, j), matriz(linha_pivot, j));
            }
            // Trocar as linhas no vetor também
            std::swap(vetor(i, 0), vetor(linha_pivot, 0));
        }

        // Trocar as colunas no caso de um pivotamento
        if (coluna_pivot != i) {
            for (int j = 0; j < n; ++j) {
                std::swap(matriz(j, i), matriz(j, coluna_pivot));
            }
            // Trocar os elementos correspondentes no vetor
            std::swap(vetor(i, 0), vetor(coluna_pivot, 0));
        }

        // Agora a matriz está preparada para a eliminação de Gauss
        for (int k = i + 1; k < n; ++k) {
            T fator = matriz(k, i) / matriz(i, i);

            for (int j = i; j < n; ++j) {
                matriz(k, j) -= matriz(i, j) * fator;
            }

            vetor(k, 0) -= vetor(i, 0) * fator;  // Atualizar vetor de soluções
            matriz.imprimir();
            vetor.imprimir();
        }
    }
}

} // namespace ifnum
