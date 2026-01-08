#include <iostream>
#include <iomanip>

int main() {
    constexpr double eps = 1e-4; //constexpr - для вычисления значения на этапе компиляции(безопаснее и быстрее)
    double sum = 0.0; // Итоговая сумма
    int n = 1; // Номер текущего члена

    double pow2 = 0.5;     // 1/2^1
    double pow3 = 1.0 / 3.0; // 1/3^1

    std::cout << std::fixed << std::setprecision(6); // Увеличение знаков после запятой
    std::cout << "Вычисление суммы ряда: a_n = 1/2^n + 1/3^n\n";
    std::cout << "Точность: " << eps << "\n\n";

    // Бесконечный цикл
    while (true) {
        double term = pow2 + pow3; // Вычисление значения a_n
        if (term < eps) break; // Выходим из цикла при значении a_n меньшем, чем эпсилон

        sum += term; // Прибавляем значение a_n к общей сумме
        pow2 *= 0.5;     // следующая степень: 1/2^(n+1) - рекурентная формула
        pow3 *= (1.0 / 3.0); // следующая степень: 1/3^(n+1)
        ++n;
    }

    std::cout << "Сумма ряда: " << sum << "\n";
    std::cout << "Итераций: " << n - 1 << "\n";
    std::cout << "Точное значение: 1.5\n";
    std::cout << "Погрешность: " << (1.5 - sum) << "\n";

    return 0;
}