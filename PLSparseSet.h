#include <iostream>
#include "playList.h"
#pragma once

using namespace std;
class PLSparseSet
{
private:
    int *sparse;
    int n;
    int maxVal;
    int capacity;
    playList **dense;
public:
    PLSparseSet(int maxVal, int Capacity);
    ~PLSparseSet();
    playList *searchPL(int id);
    void insert(playList *input);
    int binarySearch(int id,int low,int high);
    void deletePL(int id);
    void leftShift(int index);
    void clearData();
    
};