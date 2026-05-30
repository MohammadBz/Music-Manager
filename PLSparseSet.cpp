#include <iostream>
#include "PLSparseSet.h"

using namespace std;

PLSparseSet::PLSparseSet(int maxVal, int Capacity)
{
    n = 0;
    this->maxVal = maxVal;
    this->capacity = Capacity;
    sparse = new int[this->maxVal + 1];
    dense = new playList *[Capacity];
    for (int i = 0; i <= this->maxVal; i++)
    {
        sparse[i] = -1;
    }
    for (int i = 0; i < capacity; i++)
    {
        dense[i] = nullptr;
    }
}
PLSparseSet::~PLSparseSet()
{
    cout << "fuck1\n";
    for (int i = 0; i < capacity; i++)
    {
        delete dense[i];
    }
    delete[] sparse;
    delete[] dense;
}
void PLSparseSet::clearData()
{
    delete[] sparse;
    delete[] dense;
    sparse = new int[this->maxVal + 1];
    dense = new playList *[capacity];
    for (int i = 0; i <= this->maxVal; i++)
    {
        sparse[i] = -1;
    }
    for (int i = 0; i < capacity; i++)
    {
        dense[i] = nullptr;
    }
}
void PLSparseSet::insert(playList *input)
{
    if (input->getid() > maxVal)
        return;
    if (n >= capacity)
        return;
    dense[n] = input;
    sparse[input->getid()] = n;
    n++;
}
int PLSparseSet::binarySearch(int id, int low, int high)
{
    if (high < low)
        return -1;
    int mid = (high + low) / 2;
    if (dense[mid]->getid() == id)
        return mid;
    if (dense[mid]->getid() > id)
    {
        return binarySearch(id, low, mid - 1);
    }
    else
    {
        return binarySearch(id, mid + 1, high);
    }
}
playList *PLSparseSet::searchPL(int id)
{
    if (id < 0 || id > maxVal || sparse[id] >= n || sparse[id] < 0)
        return nullptr;
    int result = binarySearch(id, 0, n - 1);
    if (result < 0)
        return nullptr;
    else
        return dense[result];
}
void PLSparseSet::leftShift(int index)
{
    for (int i = index; i < n - 1; i++)
    {
        dense[i] = dense[i + 1];
        if (dense[i])
        {
            sparse[dense[i]->getid()] = i;
        }
    }
    dense[n - 1] = nullptr;
}
void PLSparseSet::deletePL(int id)
{
    if (id < 0 || id > maxVal || n == 0 || sparse[id] >= n || dense[sparse[id]] == nullptr)
        return;
    int index = sparse[id];
    playList *toDelete = dense[index];
    leftShift(index);
    dense[n - 1] = nullptr;
    sparse[id] = -1;
    delete toDelete;
    n--;
}