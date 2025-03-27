#pragma once
#include <iostream>
#include <vector>

template <typename T>
void show_vector(const std::vector<T> &vec)
{
    std::cout << "[";
    for (auto it = vec.begin(); it != vec.end(); it++) {
        std::cout << *it;
        if (it != vec.end() - 1)
            std::cout << ", ";
    }
    std::cout << "]\n";
}