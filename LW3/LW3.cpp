#include <iostream> //для ввода/вывода (std::cout)
#include <iomanip> // для управления форматом вывода (std::setprecision)
#include <cmath> // для математических функций (std::cos, std::sin, std::exp, std::abs)

int main() {
    setlocale(LC_ALL, "ru");
    constexpr double pi = 3.141592653589793;
    const double cos_pi_4 = std::cos(pi / 4.0); // Вычисляем значения cos
    const double sin_pi_4 = std::sin(pi / 4.0); // Вычисляем значения sin


    constexpr double a = 0.1; // Начало диапазона изменений x
    constexpr double b = 1.0; // Конец диапазона изменений x
    constexpr int k_steps = 10; // Коэффициент k
    constexpr int n_terms = 25; // Значение n
    constexpr double eps = 1e-4; // Эпсилон 0.0001


    const double h = (b - a) / k_steps; // Вычисление шага изменений


    std::cout << std::fixed << std::setprecision(6);


    for (int i = 0; i <= k_steps; ++i) { // Для каждого значения x (11 значений)
        const double x = a + i * h; // Значение x

        double sum_n = 0.0;
        double term = 1.0; // k = 0: cos(0)/0! * x^0 = 1

        sum_n = term;

        for (int k = 1; k <= n_terms; ++k) {
            term = term * x / k;                     // обновляем x^k / k!
            term = term * std::cos(k * pi / 4.0) / std::cos((k - 1) * pi / 4.0);
            // ⚠️ Осторожно! Деление на cos может быть нестабильным (cos = 0)

            // Лучше: пересчитывать term "с нуля" через рекуррентную формулу для всего члена
            // Но проще (и надёжнее) — перепишем полностью через накопление x^k/k!
        }

        // 🔁 Перепишем правильно — через отдельное накопление x^k/k!
        sum_n = 0.0;
        double x_pow_over_fact = 1.0; // x^0 / 0! = 1
        for (int k = 0; k <= n_terms; ++k) {
            if (k > 0) {
                x_pow_over_fact *= x / k; // рекуррентно: x^k/k! = x^(k-1)/(k-1)! * x/k
            }
            sum_n += std::cos(k * pi / 4.0) * x_pow_over_fact;
        }

        // --- Часть (b): сумма до достижения точности eps ---
        double sum_eps = 0.0;
        x_pow_over_fact = 1.0;
        int m = 0;
        double current_term;

        do {
            if (m > 0) {
                x_pow_over_fact *= x / m;
            }
            current_term = std::cos(m * pi / 4.0) * x_pow_over_fact;
            sum_eps += current_term;
            ++m;
        } while (std::abs(current_term) >= eps);

        // --- Точное значение ---
        double y = std::exp(x * cos_pi_4) * std::cos(x * sin_pi_4);

        // --- Вывод ---
        std::cout << "X=" << x << " SN=" << sum_n << " SE=" << sum_eps << " Y=" << y << "\n";
    }

    return 0;
}