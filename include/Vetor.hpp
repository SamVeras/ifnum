#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

template <typename T>
class Vetor
{
private:
    size_t tamanho;             // Mover 'tamanho' para antes de 'coordenadas'
    std::vector<T> coordenadas;

public:
    Vetor(std::vector<T> valores); // Construtor

    void imprimir() const;
    double norma() const;
    Vetor<T> normalizar() const;
    
    Vetor<T> operator+(const Vetor &outro) const;
    Vetor<T> operator-(const Vetor &outro) const;
    T operator*(const Vetor &outro) const;
    
    bool operator==(const Vetor &outro) const;
    bool operator!=(const Vetor &outro) const;
    
    // Métodos para obter o tamanho e as coordenadas
    size_t obterTamanho() const;
    std::vector<T> obterCoordenadas() const;

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Vetor<U> &v);
};

// Implementação dos métodos

template <typename T>
size_t Vetor<T>::obterTamanho() const
{
    return tamanho;
}

template <typename T>
std::vector<T> Vetor<T>::obterCoordenadas() const
{
    return coordenadas;
}

template <typename T>
Vetor<T>::Vetor(std::vector<T> valores)
: tamanho(valores.size()), coordenadas(valores) {}  // Inicializa 'tamanho' antes de 'coordenadas'

template <typename T>
void Vetor<T>::imprimir() const
{
    std::cout << "(";
    for (size_t i = 0; i < tamanho; i++)
    {
        std::cout << coordenadas[i];
        if (i < tamanho - 1)
            std::cout << ", ";
    }
    std::cout << ")\n";
}

template <typename T>
double Vetor<T>::norma() const
{
    double soma = 0;
    for (T val : coordenadas)
        soma += val * val;
    return std::sqrt(soma);
}

template <typename T>
Vetor<T> Vetor<T>::normalizar() const
{
    double n = norma();
    if (n == 0)
        throw std::runtime_error("Não é possível normalizar um vetor nulo");
    Vetor resultado(*this);
    for (T &val : resultado.coordenadas)
        val /= n;
    return resultado;
}

template <typename T>
Vetor<T> Vetor<T>::operator+(const Vetor &outro) const
{
    if (tamanho != outro.tamanho)
        throw std::invalid_argument("Os vetores devem ter o mesmo tamanho");
    Vetor resultado(*this);
    for (size_t i = 0; i < tamanho; i++)
        resultado.coordenadas[i] += outro.coordenadas[i];
    return resultado;
}

template <typename T>
Vetor<T> Vetor<T>::operator-(const Vetor &outro) const
{
    if (tamanho != outro.tamanho)
        throw std::invalid_argument("Os vetores devem ter o mesmo tamanho");
    Vetor resultado(*this);
    for (size_t i = 0; i < tamanho; i++)
        resultado.coordenadas[i] -= outro.coordenadas[i];
    return resultado;
}

template <typename T>
T Vetor<T>::operator*(const Vetor &outro) const
{
    if (tamanho != outro.tamanho)
        throw std::invalid_argument("Os vetores devem ter o mesmo tamanho");
    T produto = 0;
    for (size_t i = 0; i < tamanho; i++)
        produto += coordenadas[i] * outro.coordenadas[i];
    return produto;
}

template <typename T>
bool Vetor<T>::operator==(const Vetor &outro) const
{
    return coordenadas == outro.coordenadas;
}

template <typename T>
bool Vetor<T>::operator!=(const Vetor &outro) const
{
    return !(*this == outro);
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Vetor<T> &v)
{
    os << "(";
    for (size_t i = 0; i < v.tamanho; i++)
    {
        os << v.coordenadas[i];
        if (i < v.tamanho - 1)
            os << ", ";
    }
    os << ")";
    return os;
}
