#include <iostream>
#include <random>
#include <iomanip>
#include <locale>

int main() {
    std::setlocale(LC_ALL, "");

    // 1. Ввод размеров
    int rows, cols;
    std::cout << "Введите количество строк: ";
    std::cin >> rows;
    std::cout << "Введите количество столбцов: ";
    std::cin >> cols;

    if (rows <= 0 || cols <= 0) {
        std::cerr << "Ошибка: размеры должны быть положительными.\n";
        return 1;
    }

    // 2. Создание динамического двумерного массива
    int** matrix = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new int[cols];
    }

    // 3. Заполнение случайными числами
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-50, 50);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = dist(gen);
        }
    }

    // 4. Вывод исходной матрицы
    std::cout << std::fixed << std::setprecision(0);
    std::cout << "\nИсходная матрица:\n";
    for (int i = 0; i < rows; ++i) {
        std::cout << "Строка " << (i + 1) << ": ";
        for (int j = 0; j < cols; ++j) {
            std::cout << std::setw(5) << matrix[i][j];
        }
        std::cout << "\n";
    }

    // 5. Ввод номера удаляемой строки
    int k;
    std::cout << "\nВведите номер удаляемой строки (от 1 до " << rows << "): ";
    std::cin >> k;

    if (k < 1 || k > rows) {
        std::cerr << "Ошибка: некорректный номер строки.\n";
        // Освобождение памяти
        for (int i = 0; i < rows; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
        return 1;
    }

    int remove_index = k - 1; // перевод в 0-based

    // 6. Создание нового массива без удалённой строки
    int new_rows = rows - 1;
    int** new_matrix = nullptr;

    if (new_rows > 0) {
        new_matrix = new int* [new_rows];
        int new_i = 0;
        for (int i = 0; i < rows; ++i) {
            if (i == remove_index) continue;
            new_matrix[new_i] = new int[cols];
            for (int j = 0; j < cols; ++j) {
                new_matrix[new_i][j] = matrix[i][j];
            }
            ++new_i;
        }
    }

    // 7. Вывод результата
    if (new_rows == 0) {
        std::cout << "\nРезультирующий массив пуст (все строки удалены).\n";
    }
    else {
        std::cout << "\nМатрица после удаления строки " << k << ":\n";
        for (int i = 0; i < new_rows; ++i) {
            std::cout << "Строка " << (i + 1) << ": ";
            for (int j = 0; j < cols; ++j) {
                std::cout << std::setw(5) << new_matrix[i][j];
            }
            std::cout << "\n";
        }
    }

    // 8. Освобождение памяти
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    if (new_matrix) {
        for (int i = 0; i < new_rows; ++i) {
            delete[] new_matrix[i];
        }
        delete[] new_matrix;
    }

    return 0;
}