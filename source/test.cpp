#include "Matriz.hpp"
#include <iostream>

int main()
{
    /*try
    {
        Matriz<int> A(2, 3, {1, 2, 3, 4, 5, 6});
        A.imprimir();
        Matriz<int> B = A.transposta();
        B.imprimir();

        auto C = A * B;

        // C.imprimir();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;*/
    // Criando uma matriz 2x2
    std::vector<double> dados = {1, 2, 3, 4};
    Matriz<double> A(2, 2, dados);

    // Criando um vetor (matriz coluna) 2x1
    std::vector<double> dados_vetor = {1, 1};
    Matriz<double> b(2, 1, dados_vetor);

    // Chamando a função tendência
    double erro_tolerado = 0.01; // Erro tolerável
    int max_iteracoes = 100;      // Número máximo de iterações
    Matriz<double> resultado = A.tendencia(b, erro_tolerado, max_iteracoes);

    // Imprimindo o resultado
    std::cout << "Resultado da tendência:\n" << resultado << std::endl;

    return 0;
}
