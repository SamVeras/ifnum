#include <iostream>
#include "Matriz.hpp"

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

int main() {
    // Matriz de exemplo (2x2)
    std::vector<double> dados = {2,3,1,
                                 0,1,-2,
                                 0,0,4};
    Matriz<double> A(3, 3, dados);
    
    std::vector<double> dados2 = {2,0,0,
                                 3,1,0,
                                 1,-2,4};
    Matriz<double> B(3, 3, dados2);

    // Vetor inicial (2x1)
    std::vector<double> vetor_inicial = {4,2,8};
    Matriz<double> v0(3, 1, vetor_inicial);

    std::vector<double> vetor_inicial2 = {4,2,8};
    Matriz<double> v1(3, 1, vetor_inicial2);

    Matriz<double> v = sub(A,v0);
    v.imprimir();

    Matriz<double> v2 = reversub(B,v1);
    v2.imprimir();

    return 0;
}

