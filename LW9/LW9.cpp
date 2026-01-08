#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <locale>

// Проверка: является ли символ гласной буквой (только латиница)
bool is_vowel(char c) {
    static const std::set<char> vowels = {
        'a', 'e', 'i', 'o', 'u',
        'A', 'E', 'I', 'O', 'U'
    };
    return vowels.count(c) > 0;
}

// Проверка: является ли символ согласной (латинской)
bool is_consonant(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) && !is_vowel(c);
}

// Подсчёт согласных в файле
int count_consonants_in_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для чтения: " << filename << "\n";
        return -1;
    }

    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        for (char c : line) {
            if (is_consonant(c)) {
                ++count;
            }
        }
    }
    return count;
}

int main() {
    std::setlocale(LC_ALL, "");

    const std::string F1 = "F1.txt";
    const std::string F2 = "F2.txt";

    // === 1. Создание файла F1 (не менее 10 строк) ===
    {
        std::ofstream file(F1);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл F1.txt\n";
            return 1;
        }
        file << "Line 1: Hello world!\n";
        file << "Line 2: Programming in C++.\n";
        file << "Line 3: This is a sample text.\n";
        file << "Line 4: The quick brown fox jumps.\n";
        file << "Line 5: Over the lazy dog.\n";
        file << "Line 6: C++ is powerful and fast.\n";
        file << "Line 7: Modern C++ is safe.\n";
        file << "Line 8: Use standard library.\n";
        file << "Line 9: Avoid raw loops.\n";
        file << "Line 10: Prefer algorithms.\n";
        file << "Line 11: Keep learning!\n";
        // Можно добавить больше
    }

    // === 2. Ввод N и K ===
    int N, K;
    std::cout << "Введите номер начальной строки N: ";
    std::cin >> N;
    std::cout << "Введите номер конечной строки K: ";
    std::cin >> K;

    if (N <= 0 || K < N) {
        std::cerr << "Ошибка: N должно быть >= 1, K >= N.\n";
        return 1;
    }

    // === 3. Копирование строк из F1 в F2 (с N по K) ===
    {
        std::ifstream in(F1);
        std::ofstream out(F2);
        if (!in.is_open()) {
            std::cerr << "Ошибка: не удалось открыть F1.txt\n";
            return 1;
        }
        if (!out.is_open()) {
            std::cerr << "Ошибка: не удалось создать F2.txt\n";
            return 1;
        }

        std::string line;
        int current = 1;
        while (std::getline(in, line)) {
            if (current >= N && current <= K) {
                out << line << "\n";
            }
            ++current;
            if (current > K) break; // оптимизация: не читаем лишнее
        }
    }

    // === 4. Подсчёт согласных в F2 ===
    int consonants = count_consonants_in_file(F2);
    if (consonants >= 0) {
        std::cout << "\nКоличество согласных букв в файле F2: " << consonants << "\n";
    }

    return 0;
}