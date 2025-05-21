#include <iostream>
#include <cassert>

template <typename T>
class less_than_comparable
{
};

template <typename T>
bool operator==(const less_than_comparable<T>& a, const less_than_comparable<T>& b)
{
    return !(static_cast<const T&>(a) < static_cast<const T&>(b)) && !(static_cast<const T&>(b) < static_cast<const T&>(a));
}

template <typename T>
bool operator>=(const less_than_comparable<T>& a, const less_than_comparable<T>& b)
{
    return !(static_cast<const T&>(a) < static_cast<const T&>(b));
}

template <typename T>
bool operator>(const less_than_comparable<T>& a, const less_than_comparable<T>& b)
{
    return !(static_cast<const T&>(a) < static_cast<const T&>(b)) && !(a == b);
}

template <typename T>
bool operator!=(const less_than_comparable<T>& a, const less_than_comparable<T>& b)
{
    return !(a == b);
}

template <typename T>
bool operator<=(const less_than_comparable<T>& a, const less_than_comparable<T>& b)
{
    return !(a > b);
}

template <typename T>
class сounter
{
private:
    static int created;
public:
    сounter() { created++; }

    static int count() { return created; }
};

template <typename T>
int сounter<T>::created = 0;

class Number: public less_than_comparable<Number>, public сounter<Number> {
public:
    Number(int value): m_value{value} {}

    int value() const { return m_value; }

    bool operator<(Number const& other) const {
        return m_value < other.m_value;
    }

private:
    int m_value;
};

int main()
{
    Number one{1};
    Number two{2};
    Number three{3};
    Number four{4};
    assert(one >= one);
    assert(three <= four);
    assert(two == two);
    assert(three > two);
    assert(one < two);
    std::cout << "Count: " << Number::count() << std::endl;
    return 0;
}