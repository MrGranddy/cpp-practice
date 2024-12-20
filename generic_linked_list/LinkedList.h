#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template<typename T>
class Node{
    public:
        Node(T value);
        ~Node() = default;

        T value;
        Node<T> *next;
};

template<typename T>
class LinkedList{
    public:
        LinkedList();
        void insert(T value); // Add to the end
        void remove(T value); // Remove first instance from left to right
        void display();
        ~LinkedList();

        Node<T> *root;
};

#include "LinkedList.cpp"
#endif