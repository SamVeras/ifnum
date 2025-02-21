#include <iostream>
#include <vector>
#include <stdexcept> // Para std::invalid_argument

template <typename T>
class Matriz
{
private:
    size_t linhas;
    size_t colunas;
    std::vector<T> matriz;

public:
    Matriz(size_t linhas, size_t colunas, std::vector<T> dados) : linhas(linhas), colunas(colunas), matriz(linhas * colunas)
    {
        for (size_t i = 0; i < matriz.size(); i++)
            matriz[i] = dados[i];
    }

    Matriz(size_t linhas, size_t colunas) : linhas(linhas), colunas(colunas), matriz(linhas * colunas)
    {
    }

    T operator()(int linha, int coluna) const
    {
        if (linha >= linhas || linha < 0 || coluna >= colunas || coluna < 0)
        {
            throw std::out_of_range("Erro: Índices fora dos limites da matriz.");
        }
        return matriz[linha * colunas + coluna];
    }

    T &operator()(int linha, int coluna)
    {
        if (linha >= linhas || coluna >= colunas)
        {
            throw std::out_of_range("Erro: Índices fora dos limites da matriz.");
        }
        return matriz[linha * colunas + coluna];
    }

    void imprimir() const
    {
        for (size_t i = 0; i < linhas; ++i)
        {
            for (size_t j = 0; j < colunas; ++j)
            {
                std::cout << (*this)(i, j) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    Matriz<T> operator+(const Matriz<T> other)
    {
        if (colunas != other.colunas || linhas != other.linhas)
        {
            throw std::invalid_argument("Erro: Matrizes de ordens diferentes.");
        }

        Matriz<T> novo(linhas, colunas);

        for (size_t i = 0; i < matriz.size(); i++)
        {
            novo.matriz[i] = matriz[i] + other.matriz[i];
        }
        return novo;
    }

    Matriz<T> &operator+=(const Matriz<T> other)
    {
        if (colunas != other.colunas || linhas != other.linhas)
        {
            throw std::invalid_argument("Erro: Matrizes de ordens diferentes.");
        }

        for (size_t i = 0; i < matriz.size(); i++)
        {
            matriz[i] += other.matriz[i];
        }

        return *this;
    }

    Matriz<T> operator-(const Matriz<T> other)
    {
        if (colunas != other.colunas || linhas != other.linhas)
        {
            throw std::invalid_argument("Erro: Matrizes de ordens diferentes.");
        }

        Matriz<T> novo(linhas, colunas);

        for (size_t i = 0; i < matriz.size(); i++)
        {
            novo.matriz[i] = matriz[i] - other.matriz[i];
        }
        return novo;
    }

    Matriz<T> &operator-=(const Matriz<T> outro)
    {
        if (colunas != outro.colunas || linhas != outro.linhas)
        {
            throw std::invalid_argument("Erro: Matrizes de ordens diferentes.");
        }

        for (size_t i = 0; i < matriz.size(); i++)
        {
            matriz[i] -= outro.matriz[i];
        }

        return *this;
    }

    Matriz<T> operator*(T escalar)
    {
        Matriz<T> novo(linhas, colunas);

        for (size_t i = 0; i < matriz.size(); i++)
        {
            novo.matriz[i] = matriz[i] * escalar;
        }

        return novo;
    }

    Matriz<T> &operator*=(T escalar)
    {
        for (size_t i = 0; i < matriz.size(); i++)
        {
            matriz[i] *= escalar;
        }

        return *this;
    }

    Matriz<T> operator*(Matriz<T> outro)
    {
        if (colunas != outro.linhas)
            throw std::invalid_argument("Erro: Matrizes incompatíveis.");

        Matriz<T> novo(linhas, outro.colunas);

        for (size_t i = 0; i < linhas; i++)
        {
            for (size_t j = 0; j < outro.colunas; j++)
            {
                for (size_t k = 0; k < colunas; k++)
                {
                    novo(i, j) += (*this)(i, k) * outro(k, j);
                }
            }
        }

        return novo;
    }
};

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
