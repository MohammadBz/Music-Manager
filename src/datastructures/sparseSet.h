#include <iostream>
#pragma once
#include "../models/singer.h"
#include "MSparseSet.h"
using namespace std;
class sparseSet
{
private:
    int *sparse;
    int n;
    int maxVal;
    int capacity;
    singer **dense;
public:
    sparseSet(int maxVal, int Capacity);
    ~sparseSet();
    void insert(singer *input);
    void deleteS(int id,MSparseSet &musicSpars); // need fix
    singer *searchS(int id);
    void displayAllSingers(MSparseSet &musicSpars);
    void clearData();
};
