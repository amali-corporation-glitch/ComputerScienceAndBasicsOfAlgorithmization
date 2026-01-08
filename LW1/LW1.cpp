#include <iostream> // поток ввода/вывода
#include <iomanip> // работа с форматированием ввода/вывода (например fixed)
#include <cmath> // математические операций

int main() {

    setlocale(LC_ALL, "ru");
    std::cout << std::fixed << std::setprecision(10); // Для большего отображения знаков после запятой

    /*
    ЗАДАНИЕ №1
    Вычислить значение выражения при различных вещественных типах данных (float и double).
    Вычисления следует выполнять с использованием промежуточных переменных.
    Сравнить и объяснить полученные результаты.
    */

    // Вычисление выражения с типом данных float
    std::cout << "ЗАДАНИЕ №1" << std::endl;
    float a = 1000.0f;
    float b = 0.0001f;
    float first_numerator = pow(a - b, 3);
    float second_numerator = pow(a, 3) - 3 * a * pow(b, 2);
    float final_numenator = first_numerator - second_numerator;
    float denominator = pow(b, 3) - 3 * pow(a, 2) * b;
    float result = final_numenator / denominator;
    std::cout << "=== Значение выражения при типе данных float ===" << std::endl;
    std::cout << "Первый числитель (a - b)^3 = " << first_numerator << std::endl;
    std::cout << "Второй числитель (a^3 - 3 * a^2 * b) = " << second_numerator << std::endl;
    std::cout << "Числитель (a - b)^3 - (a^3 - 3 * a^2 * b) = " << final_numenator << std::endl;
    std::cout << "Знаменатель b^3 - 3 * a^2 * b = " << denominator << std::endl;
    std::cout << "Результат всего выражения равен: " << result << std::endl << std::endl;

    // Вычисление выражения с типом данных double
    double a_dbl = 1000.0;
    double b_dbl = 0.0001;
    double first_numerator_dbl = pow(a_dbl - b_dbl, 3);
    double second_numerator_dbl = pow(a_dbl, 3) - 3 * a_dbl * pow(b_dbl, 2);
    double final_numenator_dbl = first_numerator_dbl - second_numerator_dbl;
    double denominator_dbl = pow(b_dbl, 3) - 3 * pow(a_dbl, 2) * b_dbl;
    double result_dbl = final_numenator_dbl / denominator_dbl;
    std::cout << "=== Значение выражения при типе данных double ===" << std::endl;
    std::cout << "Первый числитель (a - b)^3 = " << first_numerator_dbl << std::endl;
    std::cout << "Второй числитель (a^3 - 3 * a^2 * b) = " << second_numerator_dbl << std::endl;
    std::cout << "Числитель (a - b)^3 - (a^3 - 3 * a^2 * b) = " << final_numenator_dbl << std::endl;
    std::cout << "Знаменатель b^3 - 3 * a^2 * b = " << denominator_dbl << std::endl;
    std::cout << "Результат всего выражения равен: " << result_dbl << std::endl;
    
    // Различные значения из-за разности точности типов (float - 7 знаков, double - 15 знаков)

    // -------------------------------------------------------------------------------------------------------------------------------
    
    /*
    ЗАДАНИЕ №2
    Вычислить значения выражений. Объяснить полученные результаты.
    */

    std::cout << "-----------------------------------------------------------------------------------------" << std::endl;
    std::cout << "ЗАДАНИЕ№2\n\n";
    int n = 0;
    int m = 0;

    std::cout << std::boolalpha; // Для отображения True/False вместо 1/0.
    std::cout << "Введите значение n (целое число): "; std::cin >> n; std::cout;
    std::cout << "Введите значение m (целое число): "; std::cin >> m; std::cout;
    
    int result1 = m - ++n;
    // Сначала n увеличивается на 1, затем m - n
    
    std::cout << "\n1) m - ++n" << std::endl;
    std::cout << "Значения переменных(n = " << n << ", m = " << m << ")" << std::endl;
    std::cout << "Результат: " << result1 << std::endl;
    
    bool result2 = ++m > --n;
    // Сначала n уменьшается на 1 и m увеличиваются на 1, затем результат m > n
    std::cout << "\n2) ++m > --n" << std::endl;
    std::cout << "Значения переменных(n = " << n << ", m = " << m << ")" << std::endl;
    std::cout << "Результат: " << result2 << std::endl;
    
    bool result3 = --n < ++m;
    // Сначала n уменьшается на 1 и m увеличиваются на 1, затем результат m < n
    std::cout << "\n3) --n < ++m" << std::endl;
    std::cout << "Значения переменных(n = " << n << ", m = " << m << ")" << std::endl;
    std::cout << "Результат: " << result3 << std::endl;

    return 0;
}
