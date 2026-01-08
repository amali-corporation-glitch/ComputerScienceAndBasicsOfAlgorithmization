#include <iostream>
#include <fstream>
#include <memory> // не используем, но можно для идей
#include <locale>

// Узел двунаправленного списка
struct Node {
    int key;
    Node* next;
    Node* prev;
    Node(int k) : key(k), next(nullptr), prev(nullptr) {}
};

// Тип списка — просто указатель на первый узел
using List = Node*;

// 1. Создание пустого списка
List create_list() {
    return nullptr;
}

// 2. Добавление в начало
List push_front(List head, int key) {
    Node* new_node = new Node(key);
    new_node->next = head;
    if (head != nullptr) {
        head->prev = new_node;
    }
    return new_node; // новый узел становится головой
}

// 3. Удаление по номеру (нумерация с 1)
List remove_at(List head, int index) { // index — 0-based внутри
    if (head == nullptr || index < 0) return head;

    Node* current = head;
    for (int i = 0; i < index && current != nullptr; ++i) {
        current = current->next;
    }

    if (current == nullptr) return head; // индекс за пределами

    // Удаление узла current
    if (current->prev != nullptr) {
        current->prev->next = current->next;
    }
    else {
        head = current->next; // удаляем голову
    }

    if (current->next != nullptr) {
        current->next->prev = current->prev;
    }

    delete current;
    return head;
}

// 4. Печать списка
void print_list(List head) {
    if (head == nullptr) {
        std::cout << "Список пустой\n";
        return;
    }

    Node* current = head;
    std::cout << "Список: ";
    while (current != nullptr) {
        std::cout << current->key;
        if (current->next != nullptr) std::cout << " <-> ";
        current = current->next;
    }
    std::cout << "\n";
}

// 5. Запись списка в файл (только ключи)
bool save_list_to_file(List head, const char* filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для записи: " << filename << "\n";
        return false;
    }

    Node* current = head;
    while (current != nullptr) {
        file.write(reinterpret_cast<const char*>(&current->key), sizeof(int));
        current = current->next;
    }

    if (file.fail()) {
        std::cerr << "Ошибка записи в файл: " << filename << "\n";
        return false;
    }
    return true;
}

// 6. Уничтожение списка
void destroy_list(List head) {
    while (head != nullptr) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

// 7. Восстановление списка из файла
List load_list_from_file(const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для чтения: " << filename << "\n";
        return nullptr;
    }

    List head = nullptr;
    int key;
    // Читаем ключи и добавляем в начало (или в конец — но в начало проще)
    while (file.read(reinterpret_cast<char*>(&key), sizeof(int))) {
        head = push_front(head, key);
    }

    // Но: push_front перевернёт порядок! Поэтому лучше добавлять в конец.
    // Перепишем правильно:
    destroy_list(head); // удалим то, что накопили
    head = nullptr;
    Node* tail = nullptr;

    file.clear();
    file.seekg(0); // вернуться в начало

    while (file.read(reinterpret_cast<char*>(&key), sizeof(int))) {
        Node* new_node = new Node(key);
        if (head == nullptr) {
            head = tail = new_node;
        }
        else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
    }

    return head;
}

// Основная программа
int main() {
    std::setlocale(LC_ALL, "");

    const char* filename = "list.dat";

    // 1. Создание списка
    List list = create_list();

    // 2. Добавляем несколько элементов (в начало → порядок обратный)
    list = push_front(list, 10);
    list = push_front(list, 20);
    list = push_front(list, 30); // список: 30 <-> 20 <-> 10

    std::cout << "Исходный список:\n";
    print_list(list);

    // 3. Удаляем элемент по номеру (например, 2-й)
    int k;
    std::cout << "Введите номер удаляемого элемента (от 1 до 3): ";
    std::cin >> k;
    list = remove_at(list, k - 1); // перевод в 0-based

    std::cout << "После удаления:\n";
    print_list(list);

    // 4. Добавляем элемент в начало
    list = push_front(list, 99);
    std::cout << "После добавления 99 в начало:\n";
    print_list(list);

    // 5. Запись в файл
    if (!save_list_to_file(list, filename)) {
        destroy_list(list);
        return 1;
    }

    // 6. Уничтожение списка
    destroy_list(list);
    list = nullptr;

    std::cout << "После уничтожения:\n";
    print_list(list); // должно быть "Список пустой"

    // 7. Восстановление из файла
    list = load_list_from_file(filename);
    std::cout << "После восстановления из файла:\n";
    print_list(list);

    // 8. Финальное уничтожение
    destroy_list(list);

    return 0;
}