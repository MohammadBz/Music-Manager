#include <iostream>
#pragma once

template <typename T>
class Node
{
private:
    T data;
    Node<T> *next;

public:
    Node(T data)
    {
        this->data = data;
        this->next = nullptr;
    }
    void setNext(Node<T> *Next)
    {
        this->next = Next;
    }
    Node<T> *getNext()
    {
        return this->next;
    }
    T getData()
    {
        return data;
    }
};
template <typename N>
class linkList
{
private:
    int n;
    int capacity;
    Node<N> *head;

public:
    linkList(int Capacity)
    {
        n = 0;
        capacity = Capacity;
        head = nullptr;
    }

    ~linkList()
    {
        Node<N> *current = head;
        while (current != nullptr)
        {
            Node<N> *next = current->getNext();
            delete current;
            current = next;
        }
    }
    Node<N> *getHead()
    {
        return this->head;
    }
    void add(N data)
    {
        if (n >= capacity)
        {
            std::cout << "Not enough space on list" << std::endl;
            return;
        }

        if (head == nullptr)
        {
            head = new Node<N>(data);
        }
        else
        {
            Node<N> *temp = head;
            while (temp->getNext() != nullptr)
            {
                temp = temp->getNext();
            }
            Node<N> *newnode = new Node<N>(data);
            temp->setNext(newnode);
        }
        n++;
    }
    int length()
    {
        return n;
    }
    void remove(N data)
    {
        if (head == nullptr)
            return;

        if (data == head->getData())
        {
            Node<N> *temp = head;
            head = head->getNext();
            delete temp;
            n--;
            return;
        }

        Node<N> *temp = head;
        Node<N> *prev = nullptr;

        while (temp != nullptr)
        {
            if (temp->getData() == data)
            {
                prev->setNext(temp->getNext());
                delete temp;
                n--;
                return;
            }
            prev = temp;
            temp = temp->getNext();
        }
    }
    void display()
    {
        Node<N> *temp = head;
        while (temp != nullptr)
        {
            std::cout << temp->getData() << " ";
            temp = temp->getNext();
        }
        std::cout << std::endl;
    }
    bool search(N data)
    {
        if (head == nullptr)
            return false;
        if (head->getData() == data)
            return true;
        Node<N> *temp = this->head;
        while (temp != nullptr)
        {
            if (temp->getData() == data)
                return true;
            temp = temp->getNext();
        }
        return false;
    }
};