#include "headers/simple_vector.h"
#include "headers/single_linked_list.h"
#include "headers/double_linked_list.h"

#include <cassert>
#include <iostream>
#include <numeric>
#include <string>

using namespace std;

class X {
public:
    X()
        : X(5) {
    }
    X(size_t num)
        : x_(num) {
    }
    X(const X& other) = delete;
    X& operator=(const X& other) = delete;
    X(X&& other) {
        x_ = exchange(other.x_, 0);
    }
    X& operator=(X&& other) {
        x_ = exchange(other.x_, 0);
        return *this;
    }
    size_t GetX() const {
        return x_;
    }

private:
    size_t x_;
};

SimpleVector<int> GenerateVector(size_t size) {
    SimpleVector<int> v(size);
    iota(v.begin(), v.end(), 1);
    return v;
}

void TestTemporaryObjConstructor() {
    const size_t size = 1000000;
    cout << "Test with temporary object, copy elision"s << endl;
    SimpleVector<int> moved_vector(GenerateVector(size));
    assert(moved_vector.size() == size);
    cout << "Done!"s << endl << endl;
}

void TestTemporaryObjOperator() {
    const size_t size = 1000000;
    cout << "Test with temporary object, operator="s << endl;
    SimpleVector<int> moved_vector;
    assert(moved_vector.size() == 0);
    moved_vector = GenerateVector(size);
    assert(moved_vector.size() == size);
    cout << "Done!"s << endl << endl;
}

void TestNamedMoveConstructor() {
    const size_t size = 1000000;
    cout << "Test with named object, move constructor"s << endl;
    SimpleVector<int> vector_to_move(GenerateVector(size));
    assert(vector_to_move.size() == size);

    SimpleVector<int> moved_vector(move(vector_to_move));
    assert(moved_vector.size() == size);
    assert(vector_to_move.size() == 0);
    cout << "Done!"s << endl << endl;
}

void TestNamedMoveOperator() {
    const size_t size = 1000000;
    cout << "Test with named object, operator="s << endl;
    SimpleVector<int> vector_to_move(GenerateVector(size));
    assert(vector_to_move.size() == size);

    SimpleVector<int> moved_vector = move(vector_to_move);
    assert(moved_vector.size() == size);
    assert(vector_to_move.size() == 0);
    cout << "Done!"s << endl << endl;
}

void TestNoncopiableMoveConstructor() {
    const size_t size = 5;
    cout << "Test noncopiable object, move constructor"s << endl;
    SimpleVector<X> vector_to_move;
    for (size_t i = 0; i < size; ++i) {
        vector_to_move.push_back(X(i));
    }

    SimpleVector<X> moved_vector = move(vector_to_move);
    assert(moved_vector.size() == size);
    assert(vector_to_move.size() == 0);

    for (size_t i = 0; i < size; ++i) {
        assert(moved_vector[i].GetX() == i);
    }
    cout << "Done!"s << endl << endl;
}

void TestNoncopiablePushBack() {
    const size_t size = 5;
    cout << "Test noncopiable push back"s << endl;
    SimpleVector<X> v;
    for (size_t i = 0; i < size; ++i) {
        v.push_back(X(i));
    }

    assert(v.size() == size);

    for (size_t i = 0; i < size; ++i) {
        assert(v[i].GetX() == i);
    }
    cout << "Done!"s << endl << endl;
}

void TestNoncopiableInsert() {
    const size_t size = 5;
    cout << "Test noncopiable insert"s << endl;
    SimpleVector<X> v;
    for (size_t i = 0; i < size; ++i) {
        v.push_back(X(i));
    }

    // в начало
    v.insert(v.begin(), X(size + 1));
    assert(v.size() == size + 1);
    assert(v.begin()->GetX() == size + 1);
    // в конец
    v.insert(v.end(), X(size + 2));
    assert(v.size() == size + 2);
    assert((v.end() - 1)->GetX() == size + 2);
    // в середину
    v.insert(v.begin() + 3, X(size + 3));
    assert(v.size() == size + 3);
    assert((v.begin() + 3)->GetX() == size + 3);
    cout << "Done!"s << endl << endl;
}

void TestNoncopiableErase() {
    const size_t size = 3;
    cout << "Test noncopiable erase"s << endl;
    SimpleVector<X> v;
    for (size_t i = 0; i < size; ++i) {
        v.push_back(X(i));
    }

    auto it = v.erase(v.begin());
    assert(it->GetX() == 1);
    cout << "Done!"s << endl << endl;
}

void TestOtusBasicCPP() {
    SimpleVector<int> values;
    cout << "Test OTUS Basic CPP"s << endl;
    values.push_back(0);
    values.push_back(1);
    
    int *ptr = &values[0];
    assert(*ptr == 0);
    ptr += 1;
    assert(*ptr == 1);

    cout << "Done!"s << endl << endl;
}

// Эта функция проверяет работу класса SingleLinkedList
void TestSingleLinkedList() {
    cout << "Test Single Linked List"s << endl;

    struct DeletionSpy {
        ~DeletionSpy() {
            if (deletion_counter_ptr) {
                ++(*deletion_counter_ptr);
            }
        }
        int* deletion_counter_ptr = nullptr;
    };

    // Проверка pop_front
    {
        SingleLinkedList<int> numbers{3, 14, 15, 92, 6};
        numbers.pop_front();
        assert((numbers == SingleLinkedList<int>{14, 15, 92, 6}));

        SingleLinkedList<DeletionSpy> list;
        list.push_front(DeletionSpy{});
        int deletion_counter = 0;
        list.begin()->deletion_counter_ptr = &deletion_counter;
        assert(deletion_counter == 0);
        list.pop_front();
        assert(deletion_counter == 1);
    }

    // Доступ к позиции, предшествующей begin
    {
        SingleLinkedList<int> empty_list;
        const auto& const_empty_list = empty_list;
        assert(empty_list.before_begin() == empty_list.cbefore_begin());
        assert(++empty_list.before_begin() == empty_list.begin());
        assert(++empty_list.cbefore_begin() == const_empty_list.begin());

        SingleLinkedList<int> numbers{1, 2, 3, 4};
        const auto& const_numbers = numbers;
        assert(numbers.before_begin() == numbers.cbefore_begin());
        assert(++numbers.before_begin() == numbers.begin());
        assert(++numbers.cbefore_begin() == const_numbers.begin());
    }

    // Вставка элемента после указанной позиции
    {  // Вставка в пустой список
        {
            SingleLinkedList<int> lst;
            const auto inserted_item_pos = lst.insert_after(lst.before_begin(), 123);
            assert((lst == SingleLinkedList<int>{123}));
            assert(inserted_item_pos == lst.begin());
            assert(*inserted_item_pos == 123);
        }

        // Вставка в непустой список
        {
            SingleLinkedList<int> lst{1, 2, 3};
            auto inserted_item_pos = lst.insert_after(lst.before_begin(), 123);

            assert(inserted_item_pos == lst.begin());
            assert(inserted_item_pos != lst.end());
            assert(*inserted_item_pos == 123);
            assert((lst == SingleLinkedList<int>{123, 1, 2, 3}));

            inserted_item_pos = lst.insert_after(lst.begin(), 555);
            assert(++SingleLinkedList<int>::Iterator(lst.begin()) == inserted_item_pos);
            assert(*inserted_item_pos == 555);
            assert((lst == SingleLinkedList<int>{123, 555, 1, 2, 3}));
        };
    }

    // Вспомогательный класс, бросающий исключение после создания N-копии
    struct ThrowOnCopy {
        ThrowOnCopy() = default;
        explicit ThrowOnCopy(int& copy_counter) noexcept
            : countdown_ptr(&copy_counter) {
        }
        ThrowOnCopy(const ThrowOnCopy& other)
            : countdown_ptr(other.countdown_ptr)  //
        {
            if (countdown_ptr) {
                if (*countdown_ptr == 0) {
                    throw std::bad_alloc();
                } else {
                    --(*countdown_ptr);
                }
            }
        }
        // Присваивание элементов этого типа не требуется
        ThrowOnCopy& operator=(const ThrowOnCopy& rhs) = delete;
        // Адрес счётчика обратного отсчёта. Если не равен nullptr, то уменьшается при каждом копировании.
        // Как только обнулится, конструктор копирования выбросит исключение
        int* countdown_ptr = nullptr;
    };

    // Проверка обеспечения строгой гарантии безопасности исключений
    {
        bool exception_was_thrown = false;
        for (int max_copy_counter = 10; max_copy_counter >= 0; --max_copy_counter) {
            SingleLinkedList<ThrowOnCopy> list{ThrowOnCopy{}, ThrowOnCopy{}, ThrowOnCopy{}};
            try {
                int copy_counter = max_copy_counter;
                list.insert_after(list.cbegin(), ThrowOnCopy(copy_counter));
                assert(list.size() == 4u);
            } catch (const std::bad_alloc&) {
                exception_was_thrown = true;
                assert(list.size() == 3u);
                break;
            }
        }
        assert(exception_was_thrown);
    }

    // Удаление элементов после указанной позиции
    {
        {
            SingleLinkedList<int> lst{1, 2, 3, 4};
            const auto& const_lst = lst;
            const auto item_after_erased = lst.erase_after(const_lst.cbefore_begin());
            assert((lst == SingleLinkedList<int>{2, 3, 4}));
            assert(item_after_erased == lst.begin());
        }
        {
            SingleLinkedList<int> lst{1, 2, 3, 4};
            const auto item_after_erased = lst.erase_after(lst.cbegin());
            assert((lst == SingleLinkedList<int>{1, 3, 4}));
            assert(item_after_erased == (++lst.begin()));
        }
        {
            SingleLinkedList<int> lst{1, 2, 3, 4};
            const auto item_after_erased = lst.erase_after(++(++lst.cbegin()));
            assert((lst == SingleLinkedList<int>{1, 2, 3}));
            assert(item_after_erased == lst.end());
        }
        {
            SingleLinkedList<DeletionSpy> list{DeletionSpy{}, DeletionSpy{}, DeletionSpy{}};
            auto after_begin = ++list.begin();
            int deletion_counter = 0;
            after_begin->deletion_counter_ptr = &deletion_counter;
            assert(deletion_counter == 0u);
            list.erase_after(list.cbegin());
            assert(deletion_counter == 1u);
        }
    }

    cout << "Done!"s << endl << endl;
}

// Эта функция проверяет работу класса SingleLinkedList
void TestDoubleLinkedList() {
    cout << "Test Double Linked List"s << endl;

    // Проверка PopFront
    {
        DoubleLinkedList<int> numbers{3, 14, 15, 92, 6};
        numbers.pop_front();
        assert((numbers == DoubleLinkedList<int>{14, 15, 92, 6}));
    }

    // Доступ к позиции, предшествующей begin
    {
        DoubleLinkedList<int> empty_list;
        const auto& const_empty_list = empty_list;
        assert(empty_list.before_begin() == empty_list.cbefore_begin());
        assert(++empty_list.before_begin() == empty_list.begin());
        assert(++empty_list.cbefore_begin() == const_empty_list.begin());

        DoubleLinkedList<int> numbers{1, 2, 3, 4};
        const auto& const_numbers = numbers;
        assert(numbers.before_begin() == numbers.cbefore_begin());
        assert(++numbers.before_begin() == numbers.begin());
        assert(++numbers.cbefore_begin() == const_numbers.begin());
    }

    // Вставка элемента после указанной позиции
    {  // Вставка в пустой список
        {
            DoubleLinkedList<int> lst;
            const auto inserted_item_pos = lst.insert_after(lst.before_begin(), 123);
            assert((lst == DoubleLinkedList<int>{123}));
            assert(inserted_item_pos == lst.begin());
            assert(*inserted_item_pos == 123);
        }

        // Вставка в непустой список
        {
            DoubleLinkedList<int> lst{1, 2, 3};
            auto inserted_item_pos = lst.insert_after(lst.before_begin(), 123);

            assert(inserted_item_pos == lst.begin());
            assert(inserted_item_pos != lst.end());
            assert(*inserted_item_pos == 123);
            assert((lst == DoubleLinkedList<int>{123, 1, 2, 3}));

            inserted_item_pos = lst.insert_after(lst.begin(), 555);
            assert(++DoubleLinkedList<int>::Iterator(lst.begin()) == inserted_item_pos);
            assert(*inserted_item_pos == 555);
            assert((lst == DoubleLinkedList<int>{123, 555, 1, 2, 3}));
        };
    }

    // Удаление элементов после указанной позиции
    {
        {
            DoubleLinkedList<int> lst{1, 2, 3, 4};
            const auto& const_lst = lst;
            const auto item_after_erased = lst.erase_after(const_lst.cbefore_begin());
            assert((lst == DoubleLinkedList<int>{2, 3, 4}));
            assert(item_after_erased == lst.begin());
        }
        {
            DoubleLinkedList<int> lst{1, 2, 3, 4};
            const auto item_after_erased = lst.erase_after(lst.cbegin());
            assert((lst == DoubleLinkedList<int>{1, 3, 4}));
            assert(item_after_erased == (++lst.begin()));
        }
        {
            DoubleLinkedList<int> lst{1, 2, 3, 4};
            const auto item_after_erased = lst.erase_after(++(++lst.cbegin()));
            assert((lst == DoubleLinkedList<int>{1, 2, 3}));
            assert(item_after_erased == lst.end());
        }
    }

    cout << "Done!"s << endl << endl;
}

int main() {
    TestTemporaryObjConstructor();
    TestTemporaryObjOperator();
    TestNamedMoveConstructor();
    TestNamedMoveOperator();
    TestNoncopiableMoveConstructor();
    TestNoncopiablePushBack();
    TestNoncopiableInsert();
    TestNoncopiableErase();
    TestOtusBasicCPP();
    TestSingleLinkedList();
    TestDoubleLinkedList();
    return 0;
}
