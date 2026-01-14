#include <iostream>
#include <iomanip>
#include <random>
#include <vector> // чтобы удобно и безопасно хранить промежуточные массивы (row_min, col_max и т.д.).

// Вывод матрицы
void print_matrix(const int mat[][100], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << std::setw(4) << mat[i][j];
        }
        std::cout << "\n";
    }
}

int main() {
    constexpr int MAX_SIZE = 100;
    int mat[MAX_SIZE][MAX_SIZE];
    int n, m;

    // Ввод размеров
    std::cout << "Введите количество строк N (<=100): ";
    std::cin >> n;
    std::cout << "Введите количество столбцов M (<=100): ";
    std::cin >> m;
    if (n <= 0 || m <= 0 || n > MAX_SIZE || m > MAX_SIZE) {
        std::cout << "Некорректные размеры!\n";
        return 1;
    }

    // Генерация матрицы
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-50, 50);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            mat[i][j] = dist(gen);
        }
    }

    // Вывод исходной матрицы
    std::cout << "Исходная матрица:\n";
    print_matrix(mat, n, m);

    // Предварительные массивы: мин/макс по строкам и столбцам (безопасное промежуточное хранение)
    std::vector<int> row_min(n, mat[0][0]);
    std::vector<int> row_max(n, mat[0][0]);
    std::vector<int> col_min(m, mat[0][0]);
    std::vector<int> col_max(m, mat[0][0]);

    // Минимум и максимум по строкам
    for (int i = 0; i < n; ++i) {
        row_min[i] = mat[i][0];
        row_max[i] = mat[i][0];
        for (int j = 1; j < m; ++j) {
            if (mat[i][j] < row_min[i]) row_min[i] = mat[i][j];
            if (mat[i][j] > row_max[i]) row_max[i] = mat[i][j];
        }
    }

    // Минимум и максимум по столбцам
    for (int j = 0; j < m; ++j) {
        col_min[j] = mat[0][j];
        col_max[j] = mat[0][j];
        for (int i = 1; i < n; ++i) {
            if (mat[i][j] < col_min[j]) col_min[j] = mat[i][j];
            if (mat[i][j] > col_max[j]) col_max[j] = mat[i][j];
        }
    }

    // Поиск седловых точек
    bool found = false; // флаг
    std::cout << "\nСедловые точки (строка, столбец, значение):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int val = mat[i][j];
            bool case1 = (val == row_min[i] && val == col_max[j]); // мин в строке, макс в столбце
            bool case2 = (val == row_max[i] && val == col_min[j]); // макс в строке, мин в столбце

            if (case1 || case2) {
                std::cout << "(" << i << ", " << j << ") = " << val << "\n";
                found = true;
            }
        }
    }

    if (!found) {
        std::cout << "Седловых точек нет.\n";
    }

    return 0;
}