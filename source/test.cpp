#include <iostream>
#include "Matriz.hpp"
#include "AlgebraLinear.hpp"

using namespace ifnum;

int main() {
    try {
        // Criando a matriz A (3x3)
        Matriz<double> A(3, 3);
        A(0, 0) = 2; A(0, 1) = -1; A(0, 2) = 1;
        A(1, 0) = 1; A(1, 1) = 3;  A(1, 2) = 2;
        A(2, 0) = 1; A(2, 1) = -1; A(2, 2) = 2;

        // Vetor b (3x1)
        Matriz<double> b(3, 1);
        b(0, 0) = 2;
        b(1, 0) = 5;
        b(2, 0) = 2;

        // Exibindo matriz original
        std::cout << "Matriz A antes do escalonamento:\n";
        A.imprimir();
        std::cout << "\nVetor b antes do escalonamento:\n";
        b.imprimir();

        // Aplicando Gauss sem pivoteamento
        Matriz<double> A_escalonada = gaussJordan(A, b);

        // Exibindo resultados
        std::cout << "\nMatriz A após o escalonamento:\n";
        A_escalonada.imprimir();
        std::cout << "\nVetor b após o escalonamento:\n";
        b.imprimir();
    }
    catch (const std::exception &e) {
        std::cerr << "Erro: " << e.what() << std::endl;
    }
    return 0;
}
