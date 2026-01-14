#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>

// Проверка: является ли символ гласной буквой (только латиница)
bool is_vowel(char c) {
    static const std::set<char> vowels = {
        // static - чтобы создать только один раз за всю программу (а не каждый раз при вызове)
        // std::set — это контейнер, который хранит уникальные элементы в отсортированном виде. 
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
    std::ifstream file(filename); // поток для чтения текстового файла
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для чтения: " << filename << "\n";
        return -1; // Сообщение об ошибке
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

// Вспомогательная функция: вывод содержимого файла
void print_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для просмотра: " << filename << "\n";
        return;
    }

    std::string line;
    int line_num = 1;
    while (std::getline(file, line)) {
        std::cout << line_num << ": " << line << "\n";
        ++line_num;
    }
}

int main() {

    const std::string F1 = "F1.txt";
    const std::string F2 = "F2.txt";

    // === 1. Создание файла F1 (не менее 10 строк) ===
    /*
    * std::ofstream file(F1); создаёт локальный объект file,
    * Когда выполнение доходит до }, объект автоматически уничтожается,
    * Деструктор ofstream закрывает файл.
    */
    {
        std::ofstream file(F1);
        if (!file.is_open()) {
            std::cerr << "Ошибка: не удалось создать файл F1.txt\n";
            return 1;
        }
        file << "Why don't programmers like nature? It has too many bugs!\n";
        file << "I told my computer I needed a break... now it won't stop sending me Kit-Kats.\n";
        file << "Why did the programmer quit his job? He didn't get arrays.\n";
        file << "My code has no errors, but my cat sat on the keyboard – new feature unlocked!\n";
        file << "Why do Java developers wear glasses? Because they don't C#!\n";
        file << "I'm reading a book on anti-gravity – it's impossible to put down!\n";
        file << "Why did the scarecrow win an award? He was outstanding in his field!\n";
        file << "Parallel lines have so much in common... it's a shame they'll never meet.\n";
        file << "I used to be a baker, but I couldn't make enough dough – so I turned to bread() functions!\n";
        file << "What's a computer's favorite snack? Microchips, but it prefers cookies!\n";
        file << "Why do Java developers wear glasses? Because they don't C#!\n";
        // Можно добавить больше
    }

    std::cout << "Содержимое файла F1:\n";
    print_file(F1);
    std::cout << "\n";

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
        std::ifstream in(F1); // читаем из F1
        std::ofstream out(F2); // пишем в F2
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

    std::cout << "\nСодержимое результирующего файла F2:\n";
    print_file(F2);
    std::cout << "\n";

    // === 4. Подсчёт согласных в F2 ===
    int consonants = count_consonants_in_file(F2);
    if (consonants >= 0) {
        std::cout << "\nКоличество согласных букв в файле F2: " << consonants << "\n";
    }

    return 0;
}

/*
* «Функция is_vowel использует static const std::set для хранения гласных,
* чтобы избежать повторного создания множества при каждом вызове.
* Проверка выполняется через count, что делает код читаемым и легко расширяемым.
* Работа ограничена латинскими буквами, что соответствует условиям лабораторной работы».
* 
* 
* «Функция is_consonant определяет согласную как букву, которая не является гласной.
* Для проверки буквы используется std::isalpha с приведением к unsigned char — это необходимо для корректной работы
* на платформах, где char знаковый. Такой подход безопасен, лаконичен и соответствует стандартным практикам C++».
* 
* 
* «Функция print_file читает текстовый файл построчно и выводит каждую строку с нумерацией, начиная с 1.
* Это позволяет пользователю наглядно видеть содержимое файла и корректно выбрать диапазон строк для копирования.
* Все операции сопровождаются проверкой ошибок открытия файла».
* 
* 
* «Файл F1 создаётся в отдельном блоке, чтобы он автоматически закрылся после записи благодаря RAII.
* Используется английский текст, чтобы функции анализа символов корректно распознавали буквы.
* Проверка is_open() обеспечивает надёжность программы».
* 
* 
* 
* 
*/