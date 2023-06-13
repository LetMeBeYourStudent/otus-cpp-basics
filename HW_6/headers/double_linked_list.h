#pragma once

#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
#include <algorithm>
#include <stdexcept>

template <typename Type>
class DoubleLinkedList {

    // Узел списка
    struct Node {
        Node() = default;
        Node(const Type& val)
                : value(val)
                , next_node()
                , prev_node() {
        }
        Type value;
        Node* next_node = nullptr;
        Node* prev_node = nullptr;
    };

    // Шаблон класса «Базовый Итератор».
    // Определяет поведение итератора на элементы односвязного списка
    // ValueType — совпадает с Type (для Iterator) либо с const Type (для ConstIterator)
    template <typename ValueType>
    class BasicIterator {
        // Класс списка объявляется дружественным, чтобы из методов списка
        // был доступ к приватной области итератора
        friend class DoubleLinkedList;

        // Конвертирующий конструктор итератора из указателя на узел списка
        explicit BasicIterator(Node* node) {
            node_ = node;
        }

    public:
        // Объявленные ниже типы сообщают стандартной библиотеке о свойствах этого итератора
        // Категория итератора — bidirectional iterator
        // (итератор, который поддерживает операции инкремента и многократное разыменование)
        using iterator_category = std::bidirectional_iterator_tag;
        // Тип элементов, по которым перемещается итератор
        using value_type = Type;
        // Тип, используемый для хранения смещения между итераторами
        using difference_type = std::ptrdiff_t;
        // Тип указателя на итерируемое значение
        using pointer = ValueType*;
        // Тип ссылки на итерируемое значение
        using reference = ValueType&;

        BasicIterator() = default;

        // Конвертирующий конструктор/конструктор копирования
        // При ValueType, совпадающем с Type, играет роль копирующего конструктора
        // При ValueType, совпадающем с const Type, играет роль конвертирующего конструктора
        BasicIterator(const BasicIterator<Type>& other) noexcept {
            node_ = other.node_;
        }

        // Чтобы компилятор не выдавал предупреждение об отсутствии оператора = при наличии
        // пользовательского конструктора копирования, явно объявим оператор = и
        // попросим компилятор сгенерировать его за нас
        BasicIterator& operator=(const BasicIterator& rhs) = default;

        // Оператор сравнения итераторов (в роли второго аргумента выступает константный итератор)
        // Два итератора равны, если они ссылаются на один и тот же элемент списка либо на end()
        [[nodiscard]] bool operator==(const BasicIterator<const Type>& rhs) const noexcept {
            return node_ == rhs.node_;
        }

        // Оператор проверки итераторов на неравенство
        // Противоположен !=
        [[nodiscard]] bool operator!=(const BasicIterator<const Type>& rhs) const noexcept {
            return node_ != rhs.node_;
        }

        // Оператор сравнения итераторов (в роли второго аргумента итератор)
        // Два итератора равны, если они ссылаются на один и тот же элемент списка либо на end()
        [[nodiscard]] bool operator==(const BasicIterator<Type>& rhs) const noexcept {
            return node_ == rhs.node_;
        }

        // Оператор проверки итераторов на неравенство
        // Противоположен !=
        [[nodiscard]] bool operator!=(const BasicIterator<Type>& rhs) const noexcept {
            return node_ != rhs.node_;
        }

        // Оператор прединкремента. После его вызова итератор указывает на следующий элемент списка
        // Возвращает ссылку на самого себя
        // Инкремент итератора, не указывающего на существующий элемент списка, приводит к неопределённому поведению
        BasicIterator& operator++() noexcept {
            assert(node_ != nullptr);
            node_ = node_->next_node;
            return *this;
        }

        // Оператор постинкремента. После его вызова итератор указывает на следующий элемент списка
        // Возвращает прежнее значение итератора
        // Инкремент итератора, не указывающего на существующий элемент списка,
        // приводит к неопределённому поведению
        BasicIterator operator++(int) noexcept {
            BasicIterator temp(node_);
            node_ = node_->next_node;
            return temp;
        }

        // Оператор преддекремента. После его вызова итератор указывает на предыдущий элемент списка
        // Возвращает ссылку на самого себя
        // Декремент итератора, не указывающего на существующий элемент списка, приводит к неопределённому поведению
        BasicIterator& operator--() noexcept {
            assert(node_ != nullptr);
            node_ = node_->prev_node;
            return *this;
        }

        // Оператор постдекремента. После его вызова итератор указывает на следующий элемент списка
        // Возвращает прежнее значение итератора
        // Декремент итератора, не указывающего на существующий элемент списка,
        // приводит к неопределённому поведению
        BasicIterator operator--(int) noexcept {
            BasicIterator temp(node_);
            node_ = node_->prev_node;
            return temp;
        }

        // Операция разыменования. Возвращает ссылку на текущий элемент
        // Вызов этого оператора у итератора, не указывающего на существующий элемент списка,
        // приводит к неопределённому поведению
        [[nodiscard]] reference operator*() const noexcept {
            assert(node_ != nullptr);
            return node_->value;
        }

        // Операция доступа к члену класса. Возвращает указатель на текущий элемент списка
        // Вызов этого оператора у итератора, не указывающего на существующий элемент списка,
        // приводит к неопределённому поведению
        [[nodiscard]] pointer operator->() const noexcept {
            assert(node_ != nullptr);
            return &(node_->value);
        }

    private:
        Node* node_ = nullptr;
    };

public:
    using value_type = Type;
    using reference = value_type&;
    using const_reference = const value_type&;

    // Итератор, допускающий изменение элементов списка
    using Iterator = BasicIterator<Type>;
    // Константный итератор, предоставляющий доступ для чтения к элементам списка
    using ConstIterator = BasicIterator<const Type>;

    // Возвращает итератор, ссылающийся на первый элемент
    // Если список пустой, возвращённый итератор будет равен end()
    [[nodiscard]] Iterator begin() noexcept {
        return Iterator{ head_.next_node };
    }

    // Возвращает итератор, указывающий на позицию, следующую за последним элементом односвязного списка
    // Разыменовывать этот итератор нельзя — попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] Iterator end() noexcept {
        return Iterator(nullptr);
    }

    // Возвращает константный итератор, ссылающийся на первый элемент
    // Если список пустой, возвращённый итератор будет равен end()
    // Результат вызова эквивалентен вызову метода cbegin()
    [[nodiscard]] ConstIterator begin() const noexcept {
        ConstIterator begin(head_.next_node);
        return begin;
    }

    // Возвращает константный итератор, указывающий на позицию, следующую за последним элементом односвязного списка
    // Разыменовывать этот итератор нельзя — попытка разыменования приведёт к неопределённому поведению
    // Результат вызова эквивалентен вызову метода cend()
    [[nodiscard]] ConstIterator end() const noexcept {
        return ConstIterator(nullptr);
    }

    // Возвращает константный итератор, ссылающийся на первый элемент
    // Если список пустой, возвращённый итератор будет равен cend()
    [[nodiscard]] ConstIterator cbegin() const noexcept {
        return ConstIterator{ head_.next_node };
    }

    // Возвращает константный итератор, указывающий на позицию, следующую за последним элементом односвязного списка
    // Разыменовывать этот итератор нельзя — попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] ConstIterator cend() const noexcept {
        return ConstIterator(nullptr);
    }

    // Возвращает итератор, указывающий на позицию перед первым элементом односвязного списка.
    // Разыменовывать этот итератор нельзя - попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] Iterator before_begin() noexcept {
        return Iterator(&head_);
    }

    // Возвращает константный итератор, указывающий на позицию перед первым элементом односвязного списка.
    // Разыменовывать этот итератор нельзя - попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] ConstIterator cbefore_begin() const noexcept {
        return ConstIterator(const_cast<Node*> (&head_));
    }

    // Возвращает константный итератор, указывающий на позицию перед первым элементом односвязного списка.
    // Разыменовывать этот итератор нельзя - попытка разыменования приведёт к неопределённому поведению
    [[nodiscard]] ConstIterator before_begin() const noexcept {
        return ConstIterator(const_cast<Node*> (&head_));
    }

public:
    DoubleLinkedList()
            : head_(), tail_(), size_(0) {
    }

    // Конструктор из списка
    DoubleLinkedList(std::initializer_list<Type> values) :head_(), size_(0) {
        for (auto it = rbegin(values); it != rend(values); ++it) {
            this->push_front(*it);
        }
    }

    // Копирующий конструктор
    DoubleLinkedList(const DoubleLinkedList& other) :head_(), size_(0) {
        DoubleLinkedList tmp;
        auto t = tmp.before_begin();
        for (auto& item : other) {
            t = tmp.InsertAfter(t, item);
        }
        swap(tmp);
    }

    // Оператор равенства
    DoubleLinkedList& operator=(const DoubleLinkedList& rhs) {
        if (this == &rhs) {
            return *this;
        }
        DoubleLinkedList tmp(rhs);
        swap(tmp);
        return *this;
    }

    // Обменивает содержимое списков за время O(1)
    void swap(DoubleLinkedList& other) noexcept {
        std::swap(other.size_, size_);
        std::swap(other.head_.next_node, head_.next_node);
    }

    // Возвращает количество элементов в списке за время O(1)
    [[nodiscard]] size_t size() const noexcept {
        return size_;
    }

    // Сообщает, пустой ли список за время O(1)
    [[nodiscard]] bool is_empty() const noexcept {
        return head_.next_node == nullptr;
    }

    // Вставляет элемент в начало списка
    void push_front(const Type& value) {
        Node* ptr = new Node(value);
        ptr->next_node = head_.next_node;
        if (head_.next_node != nullptr)
            head_.next_node->prev_node = ptr;
        if (tail_ == nullptr)
            tail_ = ptr;
        head_.next_node = ptr;
        ++size_;
    }

    // Вставляет элемент в начало списка
    void push_back(const Type& value) {
        Node* ptr = new Node(value);
        ptr->prev_node = tail_;
        if (tail_ != nullptr)
            tail_->next_node = ptr;
        if (head_->next_node == nullptr)
            head_->next_node = ptr;
        tail_ = ptr;
        ++size_;
    }

     // Вставляет элемент value после элемента, на который указывает pos.
     // Возвращает итератор на вставленный элемент
     // Если при создании элемента будет выброшено исключение, список останется в прежнем состоянии
    Iterator insert_after(ConstIterator pos, const Type& value) {
        assert(pos.node_ != nullptr);
        if (pos != this->before_begin()) {
            Node* new_node = new Node(value);
            new_node->prev_node = pos.node_;
            new_node->next_node = pos.node_->next_node;
            pos.node_->next_node = new_node;
            new_node->next_node->prev_node = new_node;
            ++size_;
            return Iterator(new_node);
        }
        else {
            push_front(value);
            return Iterator(head_.next_node);
        }
    }

    // Удаляет элемент из начала списка
    void pop_front() noexcept {
        if (head_.next_node != nullptr) {
            Node* before_node = head_.next_node;
            head_.next_node = before_node->next_node;
            head_.next_node->prev_node = nullptr;
            --size_;
            delete before_node;
        }
    }

    // Удаляет элемент, следующий за pos.
    // Возвращает итератор на элемент, следующий за удалённым
    Iterator erase_after(ConstIterator pos) noexcept {
        assert(pos.node_ != nullptr);
        Node* before = pos.node_;
        auto after_item = before->next_node->next_node;
        delete before->next_node;
        before->next_node = after_item;
        --this->size_;
        return Iterator(before->next_node);
    }

    ~DoubleLinkedList() {
        clear();
    }

    // Очищаем все
    void clear() noexcept {
        while (head_.next_node != nullptr) {
            // Создаем временный узел
            Node* tmp_node = head_.next_node;
            // Переводим
            head_.next_node = head_.next_node->next_node;
            // Удаляем временный узел
            delete tmp_node;
        }
        size_ = 0;
    }

private:
    // Фиктивный узел, используется для вставки "перед первым элементом"
    Node head_;
    // Последний узел
    Node* tail_;
    size_t size_ = 0;
};

template <typename Type>
void swap(DoubleLinkedList<Type>& lhs, DoubleLinkedList<Type>& rhs) noexcept {
lhs.swap(rhs);
}

template <typename Type>
bool operator==(const DoubleLinkedList<Type>& lhs, const DoubleLinkedList<Type>& rhs) {
    if (lhs.size() == rhs.size()) {
        return std::equal(lhs.begin(), lhs.end(), rhs.begin());
    }
    return false;
}

template <typename Type>
bool operator!=(const DoubleLinkedList<Type>& lhs, const DoubleLinkedList<Type>& rhs) {
    return !(lhs == rhs);
}

template <typename Type>
bool operator<(const DoubleLinkedList<Type>& lhs, const DoubleLinkedList<Type>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
bool operator<=(const DoubleLinkedList<Type>& lhs, const DoubleLinkedList<Type>& rhs) {
    return !(lhs > rhs);
}

template <typename Type>
bool operator>(const DoubleLinkedList<Type>& lhs, const DoubleLinkedList<Type>& rhs) {
    return std::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
}

template <typename Type>
bool operator>=(const DoubleLinkedList<Type>& lhs, const DoubleLinkedList<Type>& rhs) {
    return !(lhs < rhs);
}
