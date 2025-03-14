#include <iostream>
#include "Matriz.hpp"


Matriz<T> sub(Matriz<T> &matriz, Matriz<T> &b)
{
    Matriz<T> x(matriz.linhas,1);
    for(int i = matriz.linhas ; i <= 1; i--){
        for(int j = matriz.linhas; j <= i ; j--){
            if (j == matriz.linhas && i == matriz.linhas && i == j){
                x(i,1) = b(i,1) / matriz(i,j)  

            } else if (j <= matriz.linhas && i >= matriz.linhas && i != j){
                x(i,1) += b(i,1) - matriz(i,j) * x(j,1);

            }else if(j == i && j < matriz.linhas && i < matriz.linhas){
                x(i,1) += x(i,1) / matriz(i,j);

            }
            }
        }
    return x;   
}


int main() {
    // Matriz de exemplo (2x2)
    std::vector<double> dados = {2,3,1
                                 0,1,-2
                                 0,0,4};
    Matriz<double> A(3, 3, dados);

    // Vetor inicial (2x1)
    std::vector<double> vetor_inicial = {4,2,1};
    Matriz<double> v0(3, 1, vetor_inicial);

    Matriz<double> v = sub(A , v0);

    v.imprimir();

    return 0;
}

