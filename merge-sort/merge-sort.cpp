#include "merge-sort.hpp"
#include <memory>

List::List(std::initializer_list<int> list) {
    // Задание №1: сделать список из list
    ListElement * tail = nullptr;
    for (auto number : list) {
        // TODO: Добавить в создаваемый односвязный список
        if (tail == nullptr) {
            head = make_unique<ListElement>(number);
            tail = head.get();
        } else {
            // TODO: Создать элемент списка в tail->next
            tail->next = make_unique<ListElement>(number);
            tail = tail->next.get();
        }
    }
}

auto merge(List a, List b) noexcept -> List {
    // Слияние двух упорядоченных списков
    List result;
    ListElement *tail = 
        nullptr; // должен указывать на последний элемент списка result
    result.head->next = unique_ptr<ListElement>(tail);
    while (a.head && b.head) {
        // Выбираем меньший из a.head.value и b.head.value
        // и переносим a.head или b.head в конец result,
        // после чего переносим tail->next обратно
        // в a.head или b.head
        if (a.head->value < b.head->value)
        {
            tail = a.head.get();
            a.head = std::move(tail->next);
        }
        else
        {
            tail = b.head.get();
            b.head = std::move(tail->next);
        }
    }
    // переносим оставшийся список в конец result
    while (a.head)
    {
        tail = a.head.get();
        a.head = std::move(tail->next);
    }
    while (b.head) {
        tail = b.head.get();
        b.head = std::move(tail->next);
    }
    result.head = move(result.head->next);
    return result;
}

auto mergesort(List &list) noexcept -> void {
    // Сортировка слиянием
    // 1. Определяем середину списка (см. ветку list-algo семинаров)
    ListElement *middle = nullptr;
    size_t list_size = 0;
    auto dummy = list.head.get();
    while (dummy) 
    {
        list_size++;
        dummy = dummy->next.get();
    }
    List first;
    list_size /= 2;
    while (list_size)
    {
        middle = list.head.get();
        first.head = move(list.head);
        list.head = move(middle->next);
        list_size--;
    }
    // 2. Переносим вторую половину в новый список
    List second;
    // second.head = std::move(middle->next);
    second.head = std::move(middle->next);
    // 3. Для каждой половины запускаем mergesort
    mergesort(first);
    mergesort(second);
    // 4. Делаем merge от результатов,
    // не забыв std::move в аргументах,
    // присваивая результат в list
    list = merge(std::move(first), std::move(second));
}
