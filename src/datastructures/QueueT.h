#include <iostream>
#pragma once
using namespace std;

template <typename T>
class QueueT
{
private:
    int front;
    int rear;
    T *arr;
    int capacity;

public:
    QueueT(int Capacity)
    {
        capacity = Capacity;
        front = 0;
        rear = -1;
        arr = new T[capacity];
    }
    ~QueueT()
    {
        cout << "fuck 3\n";
        delete[] arr;
    }
    void clearData()
    {
        delete[] arr;
        arr = new T[capacity];
    }
    void enqueue(T data)
    {
        if (rear + 1 == capacity)
        {
            cout << "queue is full\n";
            return;
        }
        arr[rear + 1] = data;
        rear++;
    }
    void dequeue()
    {
        if (rear == -1)
        {
            cout << "queue is empty bemola\n";
            return;
        }
        for (int i = 0; i < rear; i++)
        {
            arr[i] = arr[i + 1];
        }
        rear--;
    }
    int getFront()
    {
        if (rear == -1)
        {
            cout << "queue is empty bemola\n";
            return -1;
        }
        return front;
    }
    T *getArr()
    {
        return this->arr;
    }
};