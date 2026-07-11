#include <iostream>
#include <concepts>
// шаблонная функция copyValue(), принимающаю два параметра одинакового типа


template<typename T, typename U>
void copyValue( T& destination,  U& source) {
    std::cout << "Parametrs have not the same type of data" << std::endl;
}

template <typename T, typename U>
requires std::same_as<T,U>
void copyValue(T& destination, const U& source) {
    destination = source;
}

// Концепт - предикат, который проверяет, обладает ли тип определенными свойствами
// 1) Понятные ошибки компиляции + 2) Перегрузка функции для разных концептов
//1)std::integral<T>,2) std::floating_point<T>,3)std::derived_from<Derived, Base> --- Derived унаследован от Base, std::convertible_to<From, to>
int main() {
    double a = 5.23;
    int b = 31548;

    copyValue(a,b);
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    return 0;
}