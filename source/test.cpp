#include <iostream>
#include "Matriz.hpp"

template <typename T>
Matriz<T> sub(const Matriz<T> &matriz, const Matriz<T> &b) {
    size_t n = matriz.linhas();
    Matriz<T> x(n, 1);

    for (size_t i = n; i >= 1; i--) {
        T soma = 0;
        for (size_t j = i + 1; j <= n && j <= matriz.colunas(); j++) {
            std::cout << "Acessando matriz(" << i << ", " << j << ") e x(" << j << ", 1)\n";
            soma += matriz(i, j) * x(j, 1);
        }
    
        if (matriz(i, i) == 0) {
            throw std::runtime_error("Divisão por zero detectada.");
        }
    
        std::cout << "Acessando b(" << i << ", 1) e matriz(" << i << ", " << i << ")\n";
        x(i, 1) = (b(i, 1) - soma) / matriz(i, i);
    }    

    return x;
}

int main() {
    // Matriz de exemplo (2x2)
    std::vector<double> dados = {2,3,1,
                                 0,1,-2,
                                 0,0,4};
    Matriz<double> A(3, 3, dados);

    // Vetor inicial (2x1)
    std::vector<double> vetor_inicial = {4,2,8};
    Matriz<double> v0(3, 1, vetor_inicial);

    Matriz<double> v = sub(A,v0);
    //v.imprimir();

    return 0;
}

