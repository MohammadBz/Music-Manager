#include <iostream>
#include "MSparseSet.h"
#include "playlist.h"

using namespace std;
int playList::allTimeCounter = 0;
int playList::getid()
{
    return this->id;
}
string playList::getName()
{
    return this->name;
}
playList::playList(string name, int maxVal, int Capacity)
{
    this->id = allTimeCounter++;
    capacity = Capacity;
    this->maxVal = maxVal;
    sparse = new int[maxVal + 1];
    dense = new int[Capacity];
    n = 0;
    for (int i = 0; i <= this->maxVal; i++)
    {
        sparse[i] = -1;
    }
    for (int i = 0; i < capacity; i++)
    {
        dense[i] = -1;
    }
}
playList::~playList()
{
    delete[] dense;
    delete[] sparse;
}
void playList::insert(int inputId) // play list should be added to song too ( can be fixed in the original function)
{
    if (inputId > maxVal)
        return;
    if (n >= capacity)
        return;
    dense[n] = inputId;
    sparse[inputId] = n;
    n++;
}
bool playList::search(int inputId)
{
    if (inputId > this->maxVal)
        return false;
    if (sparse[inputId] < n && dense[sparse[inputId]] == inputId)
        return true;

    return false;
}
void playList::deleteS(int inputId) // playList should be deleted in music too
{
    if (search(inputId) == false)
        return;
    int temp = dense[n - 1];
    dense[sparse[inputId]] = temp;
    sparse[temp] = sparse[inputId];
    n--;
}
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}
int partition(int *arr, int high, int low, MSparseSet &musicSpars)
{
    // int pivot = arr[high];
    int pivot = musicSpars.searchM(arr[high])->getReleaseYear();
    int i = low - 1;
    for (int j = low; j < high - 1; j++)
    {
        if (musicSpars.searchM(arr[j])->getReleaseYear() < pivot)
        {
            i++;
            swap(arr[j], arr[i]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}
void quickSort(int *arr, int high, int low, MSparseSet &musicSpars)
{
    if (low < high)
    {
        int pi = partition(arr, high, low, musicSpars);
        quickSort(arr, pi - 1, low, musicSpars);
        quickSort(arr, high, pi + 1, musicSpars);
    }
}

void playList::displayAllsongs(MSparseSet &musicSpars)
{
    if (this->n == 0)
    {
        cout << "PlayList is empty!\n";
        return;
    }
    int *arr = new int[this->n];
    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        if (dense[i] != -1)
            arr[counter++] = dense[i];
    }
    quickSort(arr, n - 1, 0, musicSpars);
    for (int i = 0; i < n; i++)
    {
        cout << "Singer Id:" << musicSpars.searchM(arr[i])->getSingerId()<<" ";
        musicSpars.searchM(arr[i])->showInfo();
    }
    delete[] arr;
}
