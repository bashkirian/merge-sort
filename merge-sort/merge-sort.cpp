#include "merge-sort.hpp"
#include <memory>

List::List(std::initializer_list<int> list) {
    // Задание №1: сделать список из list
    ListElement* tail = nullptr;
    for (auto number : list) {
        // TODO: Добавить в создаваемый односвязный список
        if (tail == nullptr) {
            // TODO: Создать первый элемент списка в head
            head = std::make_unique<ListElement>(number);
            tail = head.get();
        } else {
            // TODO: Создать элемент списка в tail->next
            tail->next = std::make_unique<ListElement>(number);
            tail = tail->next.get();
        }
    }
}

auto merge(List a, List b) noexcept -> List {
    // Слияние двух упорядоченных списков
    List result;
    ListElement *tail = 
        nullptr; // должен указывать на последний элемент списка result
    ListElement dummy(0);
    tail = &dummy;
    dummy.next = nullptr;
    while (1) 
    {
        if (a.head == nullptr) {
            tail->next = move(b.head);
            break;
        } 
        else if (b.head == nullptr) {
            tail->next = move(a.head);
            break;
        }
        if (a.head->value <= b.head->value) 
        {
            auto newNode = move(a.head);
            a.head = move(newNode->next);
            newNode->next = move(tail->next);
            tail->next = move(newNode);
        } 
        else 
        {
            auto newNode = move(b.head);
            b.head = move(newNode->next);
            newNode->next = move(tail->next);
            tail->next = move(newNode);
        }
        tail = tail->next.get(); 
    }
    result.head = move(dummy.next);
    return result;
}

auto mergesort(List &list) noexcept -> void 
{
    List first, second;
    if ((list.head == nullptr) || (list.head->next == nullptr)) {
        return;
    }
    ListElement *ptr1;
    ListElement *ptr2;
    ptr1 = list.head.get();
    ptr2 = list.head->next.get();

    while (ptr2 != nullptr) {
        ptr2 = ptr2->next.get();
        if (ptr2 != nullptr) {
            ptr1 = ptr1->next.get();
            ptr2 = ptr2->next.get();
        }
    }

    first.head = move(list.head);
    second.head = move(ptr1->next);

    mergesort(first);
    mergesort(second);

    List result = merge(std::move(first), std::move(second));
    list.head = move(result.head);
    return;
}
