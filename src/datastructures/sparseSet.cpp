#include <iostream>
#include "sparseSet.h"
#include "../models/singer.h"
#include "MSparseSet.h"
using namespace std;
sparseSet::sparseSet(int maxVal, int Capacity)
{
    n = 0;
    this->maxVal = maxVal;
    this->capacity = Capacity;
    sparse = new int[this->maxVal + 1];
    dense = new singer *[capacity];
    for (int i = 0; i <= this->maxVal; i++)
    {
        sparse[i] = -1;
    }
    for (int i = 0; i < capacity; i++)
    {
        dense[i] = nullptr;
    }
}
sparseSet::~sparseSet()
{
    for (int i = 0; i < capacity; i++)
    {
        delete dense[i];
    }
    delete[] sparse;
    delete[] dense;
}
void sparseSet::clearData()
{
    for (int i = 0; i < capacity; i++)
    {
        delete dense[i];
    }
    delete[] sparse;
    delete[] dense;
    sparse = new int[this->maxVal + 1];
    dense = new singer *[capacity];
    for (int i = 0; i <= this->maxVal; i++)
    {
        sparse[i] = -1;
    }
    for (int i = 0; i < capacity; i++)
    {
        dense[i] = nullptr;
    }
}
void sparseSet::insert(singer *input)
{
    if (input->getid() > maxVal)
        return;
    if (n >= capacity)
        return;
    dense[n] = input;
    sparse[input->getid()] = n;
    n++;
}

void sparseSet::deleteS(int id, MSparseSet &musicSpars) // need fix
{
    if (id < 0 || id > maxVal || n == 0 || sparse[id] >= n || dense[sparse[id]] == nullptr)
        return;
    int index = sparse[id];
    singer *toDelete = dense[index];
    toDelete->removeAllSongs(musicSpars);
    singer *last = dense[n - 1];

    dense[index] = last;
    sparse[last->getid()] = index;

    dense[n - 1] = nullptr;
    sparse[id] = -1;
    delete toDelete;
    n--;
}
singer *sparseSet::searchS(int id)
{
    if (id < 0 || id > maxVal || sparse[id] >= n || sparse[id] < 0)
        return nullptr;
    if (sparse[id] < n && dense[sparse[id]]->getid() == id)
    {
        return dense[sparse[id]];
    }
    return nullptr;
}
void sparseSet::displayAllSingers(MSparseSet &musicSpars)
{
    for (int i = 0; i < n; i++)
    {
        if (dense[i] != nullptr)
            dense[i]->displayAll(musicSpars);
    }
}