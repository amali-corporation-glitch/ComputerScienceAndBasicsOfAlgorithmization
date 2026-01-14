// Ругается MSVC на strncpy
#ifdef _MSC_VER // макрос, определённый только в Microsoft Visual C++.
#define _CRT_SECURE_NO_WARNINGS // отключает предупреждения о «небезопасных» C-функциях (strncpy, fopen и др.).
#endif

#include <iostream>  // ввод/вывод
#include <fstream>   // работа с файлами
#include <cstring>   // std::strncpy

// Структура "Школьник"
struct Student {
    char surname[30];     // фамилия
    char name[30];        // имя
    char patronymic[30];  // отчество
    int grade;            // класс
    char phone[20];       // номер телефона
    int marks[4];         // оценки: [математика, физика, русский, литература]
};

// Создание студента
Student make_student(
    const char* surname, const char* name, const char* patronymic,
    int grade, const char* phone,
    int math, int physics, int rus, int lit
) {
    Student s{};
    std::strncpy(s.surname, surname, sizeof(s.surname) - 1); // std::strncpy(куда, откуда, сколько_байт)
    std::strncpy(s.name, name, sizeof(s.name) - 1); // srntcpy - безопасное копирование без переполнения (заполняет свободное пространство \0)
    std::strncpy(s.patronymic, patronymic, sizeof(s.patronymic) - 1);
    s.grade = grade;
    std::strncpy(s.phone, phone, sizeof(s.phone) - 1);
    s.marks[0] = math;
    s.marks[1] = physics;
    s.marks[2] = rus;
    s.marks[3] = lit;

    // Функция srntcpy не ставит \0, если кол-во символов строки равно размеру массива
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
    for (int i = 0; i < 4; ++i) { // Простой перебор через цикл
        if (s.marks[i] == 2) return true;
    }
    return false;
}

// Запись массива студентов в бинарный файл
bool write_students_to_file(const char* filename, const Student* students, size_t count) { // write_students_to_file(имя файла, указатель на 1 элемент массива, кол-во студентов)
    std::ofstream file(filename, std::ios::binary); // поток для записи в файл. td::ios::binary — двоичный режим (избежание искажения символов)
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для записи: " << filename << "\n";
        return false;
    }
    file.write(reinterpret_cast<const char*>(students), count * sizeof(Student)); // reinterpret_cast - указатель students указывает не на Student, а на массив байтов
    
    // проверка ошибок записи
    if (file.fail()) {
        std::cerr << "Ошибка записи в файл: " << filename << "\n";
        return false;
    }
    return true;
}

// Чтение всех студентов из файла
bool read_all_students(const char* filename, Student* buffer, size_t max_count, size_t& out_count) {
    // read_all_students (имя файла, указатель на массив, макс. кол-во записей, реальное кол-во записей)
    std::ifstream file(filename, std::ios::binary); // поток для чтения
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для чтения: " << filename << "\n";
        return false;
    }
    // Чтение данных
    file.read(reinterpret_cast<char*>(buffer), max_count * sizeof(Student));
    if (!file && !file.eof()) { // если поток в хорошем состоянии и достигнут конец файла
        std::cerr << "Ошибка чтения из файла: " << filename << "\n";
        return false;
    }
    out_count = file.gcount() / sizeof(Student);
    // file.gcount() - возвращает количество байт, реально прочитанных последней операцией read
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

    const char* filename = "students.dat";

    // Исходные данные
    Student initial[] = {
        make_student("Иванов", "Иван", "Иванович", 10, "123-45-67", 5, 4, 5, 5),
        make_student("Петров", "Пётр", "Петрович", 9, "987-65-43", 2, 3, 4, 5),  // есть 2
        make_student("Сидоров", "Кирилл", "Сидорович", 11, "555-55-55", 4, 4, 2, 5), // есть 2
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

/*
* Массивы вместо std::string
* Это сделано специально для двоичных файлов.
* std::string нельзя просто записать в файл через write() — он содержит указатели, а не сами символы.
* char[30] — это 30 байт подряд в памяти → можно писать/читать как есть.
* 
* 
* Фиксированный размер
* sizeof(Student) всегда одинаков (≈130 байт).
*Это обязательное условие для побайтовой записи в файл.
* 
* 
* Каждая строка обязательно заканчивается символом '\0' (код 0, означает конец строки).
* Функции (std::cout, strlen, strcpy) читают до первого '\0'
*
* 
* «Функция read_all_students читает данные из двоичного файла в один вызов, используя read.
* Поскольку размер файла может быть меньше ожидаемого, она использует gcount(),
* чтобы определить реальное количество прочитанных байт, и делит его на sizeof(Student),
* получая число записей. Проверка !file && !file.eof() позволяет отличить настоящую ошибку чтения
* от штатного достижения конца файла».
* 
* 
* «Функция print_file читает весь файл за один вызов с помощью read_all_students,
* используя статический буфер на 100 записей. Она получает реальное количество прочитанных данных
* через параметр count и выводит каждую запись с нумерацией, начиная с 1.
* 
* 
* «Функция add_student_to_front. Поскольку двоичные файлы не поддерживают вставку данных в произвольное место,
* функция читает всё содержимое файла в память, создаёт новый массив с новым студентом в начале,
* копирует туда старые записи и перезаписывает файл целиком. Это стандартный подход для операций вставки вначало при работе с последовательными файлами».
* 
* 
* «Функция читает все записи из файла, фильтрует их с помощью has_bad_mark,
* оставляя только тех, у кого нет двоек, и перезаписывает файл отфильтрованным содержимым.
* Поскольку двоичные файлы не поддерживают частичное удаление, такой подход — единственно корректный».

*/