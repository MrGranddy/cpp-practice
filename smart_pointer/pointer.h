#ifndef POINTER_H
#define POINTER_H

template <typename T>
class SmartPointer{
    private:
        T* ptr;

    public:
        SmartPointer(T* p = nullptr);
        SmartPointer(const SmartPointer& other);
        SmartPointer(SmartPointer&& other) noexcept;
        ~SmartPointer();
        T& operator*() const;
        T* operator->() const;
        SmartPointer& operator=(const SmartPointer& other);
        SmartPointer& operator=(SmartPointer&& other) noexcept;
        bool operator==(const T* rhs) const;
        bool operator!=(const T* rhs) const;
};

#include "pointer.cpp"
#endif