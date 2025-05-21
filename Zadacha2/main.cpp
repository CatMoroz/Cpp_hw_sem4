#include <iostream>

namespace TypeListImpl {

    template <typename... Types>
    struct TypeList {};

    template <typename TypeList, int Index>
    struct GetType;

    template <typename Head, typename... Tail, int Index>
    struct GetType<TypeList<Head, Tail...>, Index> {
        using type = typename GetType<TypeList<Tail...>, Index - 1>::type;
    };

    template <typename Head, typename... Tail>
    struct GetType<TypeList<Head, Tail...>, 0> {
        using type = Head;
    };

    template <int Index>
    struct GetType<TypeList<>, Index> {
        static_assert(Index < 0, "Index out of bounds");
    };

    template <typename TypeList>
    struct Size; 

    template <typename... Types>
    struct Size<TypeList<Types...>> {
        static constexpr int value = sizeof...(Types);
    };

    template <typename TypeList, typename T>
    struct Contains;

    template <typename T, typename... Types>
    struct Contains<TypeList<Types...>, T> {
        static constexpr bool value = (std::is_same_v<T, Types> || ...);
    };

    template <typename TypeList, typename T, int Index = 0>
    struct IndexOf;

    template <typename T, typename... Types, int Index>
    struct IndexOf<TypeList<T, Types...>, T, Index> {
        static constexpr int value = Index;
    };

    template <typename Head, typename... Tail, typename T, int Index>
    struct IndexOf<TypeList<Head, Tail...>, T, Index> {
        static constexpr int value = IndexOf<TypeList<Tail...>, T, Index + 1>::value;
    };

    template <typename TypeList, typename T>
    struct PushBack;

    template <typename... Types, typename T>
    struct PushBack<TypeList<Types...>, T> {
        using type = TypeList<Types..., T>;
    };

    template <typename TypeList, typename T>
    struct PushFront;

    template <typename... Types, typename T>
    struct PushFront<TypeList<Types...>, T> {
        using type = TypeList<T, Types...>;
    };

}

// Тестовые типы
struct A {};
struct B {};
struct C {};
struct D {};

int main() {
    using namespace TypeListImpl;
    
    // 1. Тестирование базового TypeList
    using EmptyList = TypeList<>;
    using SingleList = TypeList<A>;
    using MultiList = TypeList<A, B, C>;
    using DuplicateList = TypeList<A, B, A, C>;
    
    // 2. Тестирование Size
    static_assert(Size<EmptyList>::value == 0, "Size test failed for empty list");
    static_assert(Size<SingleList>::value == 1, "Size test failed for single element");
    static_assert(Size<MultiList>::value == 3, "Size test failed for multiple elements");
    
    // 3. Тестирование GetType
    static_assert(std::is_same_v<GetType<SingleList, 0>::type, A>, "GetType test failed for single element");
    static_assert(std::is_same_v<GetType<MultiList, 0>::type, A>, "GetType test failed for first element");
    static_assert(std::is_same_v<GetType<MultiList, 1>::type, B>, "GetType test failed for middle element");
    static_assert(std::is_same_v<GetType<MultiList, 2>::type, C>, "GetType test failed for last element");
    
    // 4. Тестирование Contains
    static_assert(Contains<EmptyList, A>::value == false, "Contains test failed for empty list");
    static_assert(Contains<SingleList, A>::value == true, "Contains test failed for present element");
    static_assert(Contains<SingleList, B>::value == false, "Contains test failed for absent element");
    static_assert(Contains<MultiList, B>::value == true, "Contains test failed for middle element");
    static_assert(Contains<MultiList, D>::value == false, "Contains test failed for absent element");
    static_assert(Contains<DuplicateList, A>::value == true, "Contains test failed for duplicate elements");
    
    // 5. Тестирование IndexOf
    static_assert(IndexOf<SingleList, A>::value == 0, "IndexOf test failed for single element");
    static_assert(IndexOf<MultiList, A>::value == 0, "IndexOf test failed for first element");
    static_assert(IndexOf<MultiList, B>::value == 1, "IndexOf test failed for middle element");
    static_assert(IndexOf<MultiList, C>::value == 2, "IndexOf test failed for last element");
    static_assert(IndexOf<DuplicateList, A>::value == 0, "IndexOf test failed should return first occurrence");
    
    // 6. Тестирование PushBack
    using PushedBack = PushBack<MultiList, D>::type;
    static_assert(Size<PushedBack>::value == 4, "PushBack size test failed");
    static_assert(std::is_same_v<GetType<PushedBack, 3>::type, D>, "PushBack element test failed");
    
    // 7. Тестирование PushFront
    using PushedFront = PushFront<MultiList, D>::type;
    static_assert(Size<PushedFront>::value == 4, "PushFront size test failed");
    static_assert(std::is_same_v<GetType<PushedFront, 0>::type, D>, "PushFront element test failed");
    
    // 8. Комбинированные тесты
    using ComplexList = PushBack<PushFront<MultiList, D>::type, A>::type;
    static_assert(Size<ComplexList>::value == 5, "Combined operations size test failed");
    static_assert(std::is_same_v<GetType<ComplexList, 0>::type, D>, "Combined operations front test failed");
    static_assert(std::is_same_v<GetType<ComplexList, 4>::type, A>, "Combined operations back test failed");
    static_assert(IndexOf<ComplexList, A>::value == 1, "Combined operations index test failed");
    
    std::cout << "All TypeList tests passed successfully!\n";

    // Эти тесты должны вызывать ошибки компиляции - раскомментируйте для проверки

    // 1. Выход за границы списка
    // using OutOfBounds = GetType<MultiList, 3>::type; // Должна быть ошибка компиляции

    // 2. Отрицательный индекс
    // using NegativeIndex = GetType<MultiList, -1>::type; // Должна быть ошибка компиляции

    return 0;
}
