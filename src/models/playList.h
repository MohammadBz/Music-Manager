#include <iostream>
#pragma once
#include "../datastructures/MSparseSet.h"
using namespace std;

class playList
{
private:
    string name;
    int capacity;
    int *dense;
    int *sparse;
    int n;
    int maxVal;
    int id;

public:
    static int allTimeCounter;
    playList(string name,int maxVal, int Capacity);
    ~playList();
    int getid();
    string getName();
    void insert(int inputId);
    void deleteS(int inputId);
    bool search(int inputId);
    void displayAllsongs(MSparseSet &musicSpars);
};