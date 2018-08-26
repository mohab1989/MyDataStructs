#include<iostream>
template <class T>
class Node {
    public:
        Node() = default;
    protected:
        virtual void SetValue(T value) = 0;
        virtual T GetValue() const = 0;
        T value_;
};
