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

    return x;
}

template <typename T>
Matriz<T> reversub(Matriz<T> &matriz, Matriz<T> &b)
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

template <typename T>
Matriz<T> gauss(Matriz<T> &matriz, Matriz<T> &b)
{
    if(!matriz.verificarMatrizQuadrada()) {
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
Matriz<T> gaussJordan(Matriz<T> &matriz, Matriz<T> &b)
{
    if (!matriz.verificarMatrizQuadrada())   
    {
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

} // namespace ifnum