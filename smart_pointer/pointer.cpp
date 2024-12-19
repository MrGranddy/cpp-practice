template <typename T>
SmartPointer<T>::SmartPointer(T* p){
    this -> ptr = p;
}

// Copy constructor
template <typename T>
SmartPointer<T>::SmartPointer(const SmartPointer& other){
    if(other.ptr)
        ptr = new T(*other.ptr);
    else
        ptr = nullptr;
}


// Move constructor
template <typename T>
SmartPointer<T>::SmartPointer(SmartPointer&& other) noexcept{
    ptr = other.ptr;
    other.ptr = nullptr;
}

template <typename T>
SmartPointer<T>::~SmartPointer(){
    delete ptr; // Delete handles the case where nullptr
}

template <typename T>
T& SmartPointer<T>::operator*() const{
    if( ptr == nullptr ){
        throw std::runtime_error("Attempting to dereference a null pointer.");
    }
    return *ptr;
}

template <typename T>
T* SmartPointer<T>::operator->() const{
    if( ptr == nullptr ){
        throw std::runtime_error("Attempting to access a member of a null pointer.");
    }
    return ptr;
}

// Copy assignemnt
template <typename T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer<T>& other){
    if(this != &other){
        T* temp = other.ptr ? new T(*other.ptr) : nullptr;
        delete ptr;
        ptr = temp;
    }
    return *this;
}

// Move assignment
template <typename T>
SmartPointer<T>& SmartPointer<T>::operator=(SmartPointer<T>&& other) noexcept{
    if(this != &other){
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    return *this;
}


template <typename T>
bool SmartPointer<T>::operator==(const T* rhs) const{
    return ptr == rhs;
}

template <typename T>
bool SmartPointer<T>::operator!=(const T* rhs) const{
    return ptr != rhs;
}