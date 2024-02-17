#include "vector.hpp"

#include <iostream>

namespace lasd {

/* ************************************************************************** */

template<typename Data>
Vector<Data>::Vector(const unsigned long s){
    size = s;
    elements = new Data[size]{};
}

template<typename Data>
Vector<Data>::Vector(const MappableContainer<Data>& con){
    size = con.Size();
    elements = new Data[size]{};
    unsigned long i = 0;
    con.Map([this, &i](const Data& dat){
        elements[i] = dat;
        ++i;
    });
}

template<typename Data>
Vector<Data>::Vector(MutableMappableContainer<Data>&& con) noexcept {
    size = con.Size();
    elements = new Data[size]{};
    unsigned long i = 0;
    con.Map([this, &i](Data& dat){
        elements[i] = std::move(dat);
        ++i;
    });
}

template<typename Data>
Vector<Data>::Vector(const Vector<Data>& con) {
    size = con.size;
    elements = new Data[size]{};
    std::copy(con.elements, con.elements + con.size, elements);
}

template<typename Data>
Vector<Data>::Vector(Vector<Data>&& con) noexcept {
    std::swap(con.size, size);
    std::swap(con.elements, elements);
}

template<typename Data>
Vector<Data>::~Vector(){
    delete[] elements;
}

template<typename Data>
Vector<Data>& Vector<Data>::operator=(const Vector& con){
    Vector * newcon = new Vector(con);
    std::swap(*newcon, *this);
    delete newcon;
    return *this;
}

template<typename Data>
Vector<Data>& Vector<Data>::operator=(Vector&& con) noexcept {
    std::swap(con.size, size);
    std::swap(con.elements, elements);
    return *this;
}

template<typename Data>
inline bool Vector<Data>::operator==(const Vector& con) const noexcept {
    if(size == con.size){
        for(unsigned long i=0; i<Size(); ++i){
            if(elements[i] != con.elements[i]){
                return false;
            }
        }
        return true;
    }
    else{
        return false;
    }
}

template<typename Data>
inline bool Vector<Data>::operator!=(const Vector& con) const noexcept {
    return (! operator==(con));
}

template<typename Data>
inline void Vector<Data>::Clear() {
    size = 0;
    delete[] elements;
    elements = nullptr;
}

template<typename Data>
inline void Vector<Data>::Resize(const unsigned long newsize) {
    if(newsize>0){
        Data * temp = new Data[newsize]{};
        unsigned long lim = (size < newsize)? size : newsize;
        unsigned long i = 0;
        while(i<lim){
            std::swap(temp[i], elements[i]);
            ++i;
        }
        std::swap(elements, temp);
        delete[] temp;
        size = newsize;
    }
    else{
        Clear();
    }
}

template<typename Data>
inline bool Vector<Data>::Exists(const Data& dat) const noexcept {
    for(unsigned long i=0; i<Size(); ++i){
        if(elements[i] == dat){
            return true;
        }
    }
    return false;
}

template<typename Data>
inline const Data& Vector<Data>::operator[](const unsigned long i) const {
    if(i>=Size()){
        throw std::out_of_range("Index out of range!");
    }
    return elements[i];
}

template<typename Data>
inline Data& Vector<Data>::operator[](const unsigned long i) {
    if(i>=Size()){
        throw std::out_of_range("Index out of range!");
    }
    return elements[i];
}

template<typename Data>
inline const Data& Vector<Data>::Front() const {
    if(Empty()){
        throw std::length_error("Empty container!");
    }
    return elements[0];
}

template<typename Data>
inline Data& Vector<Data>::Front(){
    if(Empty()){
        throw std::length_error("Empty container!");
    }
    return elements[0];
}

template<typename Data>
inline const Data& Vector<Data>::Back() const {
    if(Empty()){
        throw std::length_error("Empty container!");
    }
    return elements[Size() - 1];
}

template<typename Data>
inline Data& Vector<Data>::Back(){
    if(Empty()){
        throw std::length_error("Empty container!");
    }
    return elements[Size() - 1];
}

template<typename Data>
inline void Vector<Data>::Sort() {
    MergeSort(0, Size()-1);
}

template<typename Data>
inline void Vector<Data>::View() const noexcept{
    unsigned long i = 0;

    std::cout << "Size = " << this->Size() << "\n\n";

    this->Map([&i](const Data& dat){
        std::cout << "[Index: " << i++ << "]     " << dat << "\n";
    });
}

template<typename Data>
inline void Vector<Data>::MergeSort(unsigned long p, unsigned long r){
    unsigned long q;
    if(p < r){
        q = (p+r)/2;
        MergeSort(p, q);
        MergeSort(q+1, r);
        Merge(p, q, r);
    }
}

template<typename Data>
inline void Vector<Data>::Merge(unsigned long p, unsigned long q, unsigned long r){
    unsigned long x, y, z;
    Data* temp = new Data[r-p+1]{};
    x = p;
    y = q+1;
    z = 0;

    while(x<=q && y<=r){
        if(elements[x] < elements[y]){
            temp[z] = elements[x++];
        }
        else{
            temp[z] = elements[y++];
        }
        ++z;
    }

    while(x<=q){
        temp[z++] = elements[x++];
    }

    while(y<=r){
        temp[z++] = elements[y++];
    }

    std::swap(elements, temp);
    delete[] temp;
}

/* ************************************************************************** */

}
