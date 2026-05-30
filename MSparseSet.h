#include <iostream>
#pragma once
#include "music.h"
using namespace std;

class MSparseSet
{
private:
    int *sparse;
    music **dense;
    int n;
    int maxVal;
    int capacity;

public:
    MSparseSet(int maxVal, int Capacity);
    ~MSparseSet();
    void insert(music *input);
    void deleteM(int id);
    music *searchM(int id);
    void searchMusicShowOnly(string Mname);
    void clearData();
};
