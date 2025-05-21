#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <memory>

template <typename T>
class SetImpl
{
public:
    virtual void insert(T element) = 0;
    virtual void erase(T element) = 0;
    virtual bool find(T element) = 0;
    virtual std::vector<T> getElements() = 0;
};

template <typename T>
class HashSetImpl : public SetImpl<T>
{
private:
    std::unordered_set<T> elements;
public:
    HashSetImpl() {}
    HashSetImpl(std::vector<T> elements) : elements(std::unordered_set<T>(elements.begin(), elements.end())) {}

    bool find(T element) override
    {
        return elements.find(element) != elements.end();
    }
    void insert(T element) override
    {
        elements.insert(element);
    }
    void erase(T element) override
    {
        if (this->find(element))
            elements.erase(element);
    }

    std::vector<T> getElements() override
    {
        return std::vector<T>(elements.begin(), elements.end());
    }
};

template <typename T>
class VecSetImpl : public SetImpl<T>
{
private:
    std::vector<T> elements;
public:
    VecSetImpl(std::vector<T> elements) : elements(elements) {}
    VecSetImpl() {}

    bool find(T element) override
    {
        return std::find(elements.begin(), elements.end(), element) != elements.end();
    }

    void insert(T element) override
    {
        if (!this->find(element))
            elements.push_back(element);
    }
    void erase(T element) override
    {
        auto el_it = std::find(elements.begin(), elements.end(), element);
        if (el_it != elements.end())
            elements.erase(el_it);
    }
    std::vector<T> getElements() override
    {
        return elements;
    }
};

template<typename T>
class Set
{
private:
    std::unique_ptr<SetImpl<T>> impl;
    int threshold = 10; 
    void changeImpl(bool toHash)
    {
        if (toHash)
            impl = std::make_unique<HashSetImpl<T>>(HashSetImpl<T>(impl->getElements()));
        else
            impl = std::make_unique<VecSetImpl<T>>(VecSetImpl<T>(impl->getElements()));
    }
public: 
    Set() : impl(std::make_unique<VecSetImpl<T>>(VecSetImpl<T>())) {}

    void addElement(T element)
    {
        impl->insert(element);
        if (impl->getElements().size() == threshold + 1)
            changeImpl(1);
    }

    void deleteElement(T element)
    {
        impl->erase(element);
        if (impl->getElements().size() == threshold - 1)
            changeImpl(0);
    }

    bool containsElement(T element)
    {
        return impl->find(element);
    }

    Set<T>* intersectSet(Set<T>* other)
    {
        Set<T>* newSet = new Set<T>();
        for (T element : impl->getElements())
        {
            if (other->containsElement(element))
                newSet->addElement(element);
        }
        return newSet;
    }

    Set<T>* unionSet(Set<T>* other)
    {
        Set<T>* newSet = new Set<T>();
        for (T element : impl->getElements())
            newSet->addElement(element);
        
        for (T element : other->impl->getElements())
            newSet->addElement(element);
        return newSet;
    }

    void printElements()
    {
        for (T element : impl->getElements())
        {
            std::cout << element << ' ';
        }
        std::cout << '\n';
    }
};

int main()
{
    Set<int>* set1 = new Set<int>();
    Set<int>* set2 = new Set<int>();
    set1->addElement(2);
    for (int i = 0; i < 8; i++)
    {
        set1->addElement(i);
    }
    for (int i = 5; i < 20; i++)
    {
        set2->addElement(i);
    }
    set1->printElements();
    set2->printElements();
    Set<int>* set3 = set1->intersectSet(set2);
    Set<int>* set4 = set1->unionSet(set2);
    set3->printElements();
    set4->printElements();
    delete set1;
    delete set2;
    delete set3;
    delete set4;
}