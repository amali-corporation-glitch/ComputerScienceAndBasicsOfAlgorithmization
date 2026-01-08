#ifdef _MSC_VER // макрос, определённый только в Microsoft Visual C++.
#define _CRT_SECURE_NO_WARNINGS // отключает предупреждения о «небезопасных» C-функциях (strncpy, fopen и др.).
#endif

#include <iostream>  // ввод/вывод
#include <fstream>   // работа с файлами
#include <cstring>   // std::strncpy
#include <locale>    // setlocale для русского языка

// Структура "Школьник" — только POD-типы (без std::string!)
struct Student {
    char surname[30];     // фамилия
    char name[30];        // имя
    char patronymic[30];  // отчество
    int grade;            // класс
    char phone[20];       // номер телефона
    int marks[4];         // оценки: [матем, физика, русский, литература]
};

// Создание студента
Student make_student(
    const char* surname, const char* name, const char* patronymic,
    int grade, const char* phone,
    int math, int physics, int rus, int lit
) {
    Student s{};
    std::strncpy(s.surname, surname, sizeof(s.surname) - 1);
    std::strncpy(s.name, name, sizeof(s.name) - 1);
    std::strncpy(s.patronymic, patronymic, sizeof(s.patronymic) - 1);
    s.grade = grade;
    std::strncpy(s.phone, phone, sizeof(s.phone) - 1);
    s.marks[0] = math;
    s.marks[1] = physics;
    s.marks[2] = rus;
    s.marks[3] = lit;
    // Обеспечим завершение строк нулём (на всякий случай)
    s.surname[sizeof(s.surname) - 1] = '\0';
    s.name[sizeof(s.name) - 1] = '\0';
    s.patronymic[sizeof(s.patronymic) - 1] = '\0';
    s.phone[sizeof(s.phone) - 1] = '\0';
    return s;
}

// Печать студента
void print_student(const Student& s) {
    std::cout << s.surname << " " << s.name << " " << s.patronymic
        << ", " << s.grade << " класс, тел: " << s.phone
        << ", оценки: " << s.marks[0] << " " << s.marks[1]
        << " " << s.marks[2] << " " << s.marks[3] << "\n";
}

// Проверка: есть ли двойка?
bool has_bad_mark(const Student& s) {
    for (int i = 0; i < 4; ++i) {
        if (s.marks[i] == 2) return true;
    }
    return false;
}

// Запись массива студентов в бинарный файл
bool write_students_to_file(const char* filename, const Student* students, size_t count) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для записи: " << filename << "\n";
        return false;
    }
    file.write(reinterpret_cast<const char*>(students), count * sizeof(Student));
    if (file.fail()) {
        std::cerr << "Ошибка записи в файл: " << filename << "\n";
        return false;
    }
    return true;
}

// Чтение всех студентов из файла
bool read_all_students(const char* filename, Student* buffer, size_t max_count, size_t& out_count) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для чтения: " << filename << "\n";
        return false;
    }
    file.read(reinterpret_cast<char*>(buffer), max_count * sizeof(Student));
    if (!file && !file.eof()) {
        std::cerr << "Ошибка чтения из файла: " << filename << "\n";
        return false;
    }
    out_count = file.gcount() / sizeof(Student);
    return true;
}

// Печать содержимого файла
void print_file(const char* filename) {
    constexpr size_t MAX_STUDENTS = 100;
    Student students[MAX_STUDENTS];
    size_t count = 0;
    if (!read_all_students(filename, students, MAX_STUDENTS, count)) {
        return;
    }
    std::cout << "\nСодержимое файла (" << count << " записей):\n";
    for (size_t i = 0; i < count; ++i) {
        std::cout << (i + 1) << ". ";
        print_student(students[i]);
    }
}

// Удаление всех студентов с двойками
bool remove_bad_students(const char* filename) {
    constexpr size_t MAX_STUDENTS = 100;
    Student students[MAX_STUDENTS];
    size_t count = 0;
    if (!read_all_students(filename, students, MAX_STUDENTS, count)) {
        return false;
    }

    Student filtered[MAX_STUDENTS];
    size_t new_count = 0;
    for (size_t i = 0; i < count; ++i) {
        if (!has_bad_mark(students[i])) {
            filtered[new_count++] = students[i];
        }
    }

    return write_students_to_file(filename, filtered, new_count);
}

// Добавление студента в начало файла
bool add_student_to_front(const char* filename, const Student& new_student) {
    constexpr size_t MAX_STUDENTS = 100;
    Student students[MAX_STUDENTS];
    size_t count = 0;
    if (!read_all_students(filename, students, MAX_STUDENTS, count)) {
        return false;
    }

    if (count >= MAX_STUDENTS) {
        std::cerr << "Ошибка: файл уже содержит максимальное количество записей.\n";
        return false;
    }

    Student temp[MAX_STUDENTS + 1];
    temp[0] = new_student;
    for (size_t i = 0; i < count; ++i) {
        temp[i + 1] = students[i];
    }

    return write_students_to_file(filename, temp, count + 1);
}

// Основная программа
int main() {
    std::setlocale(LC_ALL, "");

    const char* filename = "students.dat";

    // Исходные данные
    Student initial[] = {
        make_student("Иванов", "Иван", "Иванович", 10, "123-45-67", 5, 4, 5, 5),
        make_student("Петров", "Пётр", "Петрович", 9, "987-65-43", 2, 3, 4, 5),  // есть 2
        make_student("Сидоров", "Сидор", "Сидорович", 11, "555-55-55", 4, 4, 2, 5), // есть 2
        make_student("Кузнецов", "Андрей", "Владимирович", 10, "111-22-33", 5, 5, 5, 5)
    };

    // Запись в файл
    if (!write_students_to_file(filename, initial, sizeof(initial) / sizeof(initial[0]))) {
        return 1;
    }

    // Печать до изменений
    print_file(filename);

    // Удаление студентов с двойками
    std::cout << "\n--- Удаляем студентов с двойками ---\n";
    if (!remove_bad_students(filename)) {
        return 1;
    }
    print_file(filename);

    // Добавление в начало
    Student new_student = make_student("Новиков", "Александр", "Сергеевич", 9, "999-99-99", 5, 5, 5, 5);
    std::cout << "\n--- Добавляем студента в начало ---\n";
    if (!add_student_to_front(filename, new_student)) {
        return 1;
    }
    print_file(filename);

    return 0;
}