#include <iostream>
#include "music.h"
#include "MSparseSet.h"
using namespace std;

MSparseSet::MSparseSet(int maxVal, int Capacity)
{
    n = 0;
    this->maxVal = maxVal;
    this->capacity = Capacity;
    sparse = new int[this->maxVal + 1];
    dense = new music *[capacity];
    for (int i = 0; i <= this->maxVal; i++)
    {
        sparse[i] = -1;
    }
    for (int i = 0; i < capacity; i++)
    {
        dense[i] = nullptr;
    }
}
MSparseSet::~MSparseSet()
{
    cout << "fuck2\n";
/*     for (int i = 0; i < capacity; i++)
    {
        delete dense[i];
    }
    delete[] sparse;
    delete[] dense; */
}
void MSparseSet::clearData()
{
    delete[] sparse;
    delete[] dense;
    sparse = new int[this->maxVal + 1];
    dense = new music *[capacity];
    for (int i = 0; i <= this->maxVal; i++)
    {
        sparse[i] = -1;
    }
    for (int i = 0; i < capacity; i++)
    {
        dense[i] = nullptr;
    }
}
void MSparseSet::insert(music *input)
{
    if (input->getId() > maxVal)
        return;
    if (n >= capacity)
        return;
    dense[n] = input;
    sparse[input->getId()] = n;
    n++;
}
void MSparseSet::deleteM(int id)
{
    if (id < 0 || id > maxVal || n == 0 || sparse[id] >= n || dense[sparse[id]] == nullptr)
        return;
    int index = sparse[id];
    music *toDelete = dense[index];
    music *last = dense[n - 1];
    dense[index] = last;
    sparse[last->getId()] = index;
    dense[n - 1] = nullptr;
    sparse[id] = -1;
    n--;
}
music *MSparseSet::searchM(int id)
{
    if (id < 0 || id > maxVal || sparse[id] >= n || sparse[id] < 0)
        return nullptr;
    if (sparse[id] < n && dense[sparse[id]]->getId() == id)
    {
        return dense[sparse[id]];
    }
    return nullptr;
}
void MSparseSet::searchMusicShowOnly(string Mname)
{
    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        if (dense[i] != nullptr)
        {
            if (dense[i]->getMname() == Mname)
            {
                cout << "Singer id: " << dense[i]->getSingerId() << " ";
                dense[i]->showInfo();
                counter++;
            }
        }
    }
    cout << "Total found :" << counter << endl;
}
