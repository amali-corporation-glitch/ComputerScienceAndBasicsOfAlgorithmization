#include <iostream>  // ввод/вывод
#include <vector>    // динамический массив
#include <algorithm> // std::min_element
#include <random>    // генератор случайных чисел
#include <locale>    // поддержка русского языка

// Вывод вектора в виде [ a, b, c ]
void print_list(const std::vector<int>& list) {
    std::cout << "[ ";
    for (size_t i = 0; i < list.size(); ++i) {
        std::cout << list[i];
        if (i + 1 < list.size()) std::cout << ", ";
    }
    std::cout << " ]";
}

// Функция min для vector<int>
int min(const std::vector<int>& args) {
    if (args.empty()) {
        throw std::invalid_argument("Список не должен быть пустым");
    }
    return *std::min_element(args.begin(), args.end());
}

// Генерация вектора случайных целых чисел
std::vector<int> generate_random_list(int size, int min_val = -100, int max_val = 100) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min_val, max_val);

    std::vector<int> result;
    result.reserve(size); // оптимизация: сразу выделяем память
    for (int i = 0; i < size; ++i) {
        result.push_back(dist(gen));
    }
    return result;
}

int main() {
    std::setlocale(LC_ALL, "");

    auto list1 = generate_random_list(5);
    auto list2 = generate_random_list(10);
    auto list3 = generate_random_list(12);

    // Список 1: 5 чисел
    std::cout << "Список (5 параметров): ";
    print_list(list1);
    std::cout << "\nМинимальное значение = " << min(list1) << "\n\n";

    // Список 2: 10 чисел
    std::cout << "Список (10 параметров): ";
    print_list(list2);
    std::cout << "\nМинимальное значение = " << min(list2) << "\n\n";

    // Список 3: 12 чисел
    std::cout << "Список (12 параметров): ";
    print_list(list3);
    std::cout << "\nМинимальное значение = " << min(list3) << "\n";

    return 0;
}