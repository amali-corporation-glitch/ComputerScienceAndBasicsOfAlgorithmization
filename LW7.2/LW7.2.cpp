#include <iostream>  // ввод/вывод
#include <vector>    // динамический массив
#include <algorithm> // std::min_element
#include <random>    // генератор случайных чисел

// Вывод вектора в виде [ a, b, c ]
void print_list(const std::vector<int>& list) { // Передаем по ссылке, чтоб не копировать (const - не дает изменять оригинал)
    std::cout << "[ ";
    for (size_t i = 0; i < list.size(); ++i) { // syze_t - беззнаковый целочисленный тип (для корректного сравнения с размером контейнера в условии)
        std::cout << list[i];
        if (i + 1 < list.size()) std::cout << ", "; // Чтоб не ставить запятую после последнего элемента
    }
    std::cout << " ]";
}

// Функция min для vector<int>
int min(const std::vector<int>& args) {
    if (args.empty()) { // Если списко пуст
        throw std::invalid_argument("Список не должен быть пустым"); // Обработка ошибки
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
        result.push_back(dist(gen)); // добавление в конец вектора случайного числа от -100 до 100
    }
    return result;
}

int main() {

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

/* Теория
* std::vector<int> — это «умный список», который:
* может расти (добавлять элементы),
* помнит свой размер (list.size()),
* автоматически управляет памятью (не нужно new/delete),
* работает безопасно.
* 
* 
* 
* list.size() возвращает size_t (беззнаковый тип, например, unsigned long),
* i — int (знаковый тип).
* Если вы случайно сделаете i = -1, то при сравнении i < list.size():
* i превратится в огромное положительное число (из-за преобразования знакового → беззнакового),
* и условие сломается.
* 
* 
* 
* args.begin() — итератор (указатель) на первый элемент вектора.
* args.end() — итератор на позицию ПОСЛЕ последнего элемента.
* 
* Итератор — это не значение, а "указатель на место".
* * — это "достать значение оттуда".
* 
* 
* 
* Что делает reserve?
* std::vector хранит данные в динамическом массиве.
* Когда вы делаете push_back, а места нет — вектор выделяет новый, больший блок памяти и копирует всё туда.
* Это медленно, если делать часто.

*/