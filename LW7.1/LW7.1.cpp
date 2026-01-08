#include <iostream>
#include <complex> // Для работы с комлпесными числами
#include <locale>

// Перегрузка 1: вычитание вещественных чисел
double subtract(double a, double b) {
    return a - b;
}

// Перегрузка 2: вычитание комплексных чисел
std::complex<double> subtract(const std::complex<double>& a, const std::complex<double>& b) {
    return a - b;
}

int main() {
    // Настройка локали для корректного отображения русского языка (если используется)
    std::setlocale(LC_ALL, "RU");

    // === Тест: вещественные числа ===
    double x = 5.5, y = 2.3;
    std::cout << "Вещественные: " << x << " - " << y << " = " << subtract(x, y) << "\n";

    // === Тест: комплексные числа ===
    // Инициализация комплексных чисел
    std::complex<double> c1(3.0, 4.0);  // 3 + 4i
    std::complex<double> c2(1.0, 2.0);  // 1 + 2i
    auto result = subtract(c1, c2);     // (3-1) + (4-2)i = 2 + 2i

    std::cout << "Комплексные: (" << c1.real() << "+" << c1.imag() << "i) - ("
        << c2.real() << "+" << c2.imag() << "i) = "
        << result.real() << "+" << result.imag() << "i\n";

    /*  c1.real() — возвращает вещественную часть (double).
        c1.imag() — возвращает мнимую часть (double).
            - Мы вручную форматируем вывод, потому что:
            - По умолчанию std::cout << c1 выводит (3,4), что менее читаемо.
     */

    return 0;
}