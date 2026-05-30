#include <iostream>
#pragma once
#include "../datastructures/MSparseSet.h"
#include "../datastructures/linkList.h"
using namespace std;

class singer
{
private:
    string name;
    int id;
    linkList<int> *musicIds;

public:
    singer(string name);
    ~singer();
    static int allTimeSingerCount;
    linkList<int> *getMList();
    int getid();
    string getName();
    void displayAll(MSparseSet &musicSpars);
    void addMusic(int input); // moved to main functions
    void removeAllSongs(MSparseSet &musicSpars);

    // bool findMusic(string input, MSparseSet &musicSpars);
    //   music *findMusic(int id);
    //  void removeMusic(int id);
};