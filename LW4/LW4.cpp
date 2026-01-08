#include <iostream>
#include <iomanip>
#include <random> // для современного генератора случайных чисел (вместо устаревшего rand)

// Вывод массива
void print_array(const int arr[], int n) {
    // Печатаем каждый элемент массива в поле ширины 4
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << "\t";
    }
    std::cout << "\n";
}

int main() {
    setlocale(LC_ALL, "RU");
    constexpr int MAX_SIZE = 100;
    int arr[MAX_SIZE];
    int n;

    // 1. Ввод реальной длины массива
    std::cout << "Введите длину массива N (<=100): ";
    std::cin >> n;
    if (n <= 0 || n > MAX_SIZE) { // Проверка на корректность ввода (диапазон от 1 до 100)
        std::cout << "Некорректная длина!\n";
        return 1;
    }

    // 2. Настройка качественного генератора чисел
    std::random_device rd; // Энтропия из ОС
    std::mt19937 gen(rd()); // Быстрый и надежный генератор
    std::uniform_int_distribution<int> dist(-50, 50); // Диапазон случайных значений

    // Заполнение массива случайными числами
    for (int i = 0; i < n; ++i) {
        arr[i] = dist(gen);
    }

    // 3. Печать исходного массива
    std::cout << "Исходный массив:\n";
    print_array(arr, n);

    // 4. Удаление элемента с заданным номером.
    int k;
    std::cout << "Введите номер удаляемого элемента K (от 1 до " << n << "): ";
    std::cin >> k;
    int remove_index = k - 1; // - 1 потому что индекс начинается с 0

    if (remove_index >= 0 && remove_index < n) {
        // Сдвигаем все элементы после remove_index влево
        for (int i = remove_index; i < n - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        --n; // уменьшаем реальную длину
    }
    else {
        std::cout << "Некорректный номер K. Удаление пропущено.\n";
    }

    // 5. Поиск ПЕРВОГО ЧЁТНОГО ЭЛЕМЕНТА (по значению)
    int even_idx = -1;
    for (int i = 0; i < n; ++i) {
        if (arr[i] % 2 == 0) {
            even_idx = i;
            break; // первый найденный — искомый
        }
    }

    // 6. Вставка после чётного элемента: значение = arr[even_idx - 1] + 2
    if (even_idx != -1          // чётный найден
        && even_idx > 0         // не первый элемент (есть предыдущий)
        && n < MAX_SIZE) {      // есть место для вставки

        int value_to_insert = arr[even_idx - 1] + 2; // Новое значение под предыдущим индексом

        // Сдвигаем элементы [even_idx+1 ... n-1] на одну позицию вправо
        for (int i = n; i > even_idx + 1; --i) {
            arr[i] = arr[i - 1];
        }

        // Вставляем новый элемент ПОСЛЕ чётного
        arr[even_idx + 1] = value_to_insert;
        ++n; // увеличиваем реальную длину
    }

    // 7. Печать результата
    std::cout << "Результат:\n";
    print_array(arr, n);

    return 0;
}