#include <iostream>
#include <fstream>

// Узел двунаправленного списка
struct Node {
    int key; // данные
    Node* next; // указатель на следующий узел
    Node* prev;// указатель на предыдущий узел
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
List remove_at(List head, int index) {
    if (head == nullptr || index < 0) return head; // защита от ошибок

    Node* current = head;
    for (int i = 0; i < index && current != nullptr; ++i) { // поиск удаляемого значения по индексу
        current = current->next;
    }

    if (current == nullptr) return head; // индекс за пределами

    // Удаление узла current
    if (current->prev != nullptr) { // если current не первый
        current->prev->next = current->next; // обновляем предыдущий
    }
    else {
        head = current->next; // удаляем голову
    }

    if (current->next != nullptr) { // если current не последний
        current->next->prev = current->prev; // обновляем следующий
    }

    delete current; // освобождаем память
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
    std::ofstream file(filename, std::ios::binary); // поток для записи в файл (двоичный режим)
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл для записи: " << filename << "\n";
        return false;
    }

    Node* current = head;
    while (current != nullptr) {
        file.write(reinterpret_cast<const char*>(&current->key), sizeof(int)); // (указатель на байты(записываем только данные(key)), сколько байт записать (4))
        current = current->next;
    }

    if (file.fail()) {
        std::cerr << "Ошибка записи в файл: " << filename << "\n";
        return false;
    }
    return true;
}

// 6. Уничтожение списка (каждый узел отдельно)
void destroy_list(List head) {
    while (head != nullptr) {
        Node* next = head->next;    // 1. Запоминаем следующий узел
        delete head;                // 2. Удаляем текущий
        head = next;                // 3. Переходим к следующему
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

    // push_front перевернёт порядок! Поэтому лучше добавлять в конец.
    // Перепишем правильно:
    destroy_list(head); // удалим то, что накопили
    head = nullptr;
    Node* tail = nullptr; // указатель на последний узел

    // после первого цикла чтения файла дошли до конца
    file.clear(); // сброс ошибок
    file.seekg(0); // вернуться в начало
    // теперь можно читать сначала

    while (file.read(reinterpret_cast<char*>(&key), sizeof(int))) {
        Node* new_node = new Node(key);
        if (head == nullptr) {
            head = tail = new_node; // первый узел
        }
        else {
            tail->next = new_node; // текущий хвост -> новый узел
            new_node->prev = tail; // новый узел <- текущий хвост
            tail = new_node; // обновляем хвост
        }
    }

    return head;
}

// Основная программа
int main() {

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
    list = remove_at(list, k - 1);

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



/*
Пример: удаление из середины
Список: [30] <-> [20] <-> [10], index = 1
current = 20,
current->prev (30)->next = 10,
current->next (10)->prev = 30,
Удаляем 20.
Результат:
[30] <-> [10]


«Функция print_list выполняет линейный обход списка от головы до конца.
Для каждого узла выводится его значение, а между элементами добавляется стрелка <->.
Проверка current->next != nullptr предотвращает вывод лишнего разделителя после последнего элемента».


«Функция save_list_to_file записывает в двоичный файл только значения key из узлов списка, без указателей.
Это необходимо, потому что адреса памяти недействительны при следующем запуске программы.
Запись выполняется побайтово с помощью write, а все операции сопровождаются проверкой ошибок».


«Функция destroy_list итеративно удаляет все узлы списка.
Перед удалением текущего узла сохраняется указатель на следующий, чтобы не потерять доступ к остальной части списка.
Такой подход предотвращает утечки памяти и безопасен для списков любого размера».


«При восстановлении списка важно сохранить исходный порядок элементов.
Использование push_front приводит к инверсии, поэтому реализовано добавление в конец с помощью указателя tail.
Перед повторным чтением файл возвращается в начальное состояние через clear() и seekg(0). Это обеспечивает корректное восстановление данных».

*/