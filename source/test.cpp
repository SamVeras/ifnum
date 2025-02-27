#include "Matriz.hpp"
#include <iostream>

int main()
{
    try
    {
        Matriz<int> A(2, 3, {1, 2, 3, 4, 5, 6});
        A.imprimir();
        Matriz<int> B(3, 2, {7, 8, 9, 10, 11, 12});
        B.imprimir();

        auto C = A * B;

        C.imprimir();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
