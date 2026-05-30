#include <iostream>
#include "linkList.h"
#pragma once
using namespace std;

class music
{
    string Mname;
    int id;
    int releaseYear;
    linkList<string> *lyrics;
    linkList<int> *playListsID;
    int singerID;

public:
    static int allTimeMusicCounter;
    music(string Mname, int releaseYear);
    ~music();
    int getId();
    int getReleaseYear();
    int getSingerId();
    string getMname();
    linkList<string> *getLyrics();
    linkList<int> *getPlayListsID();
    void showInfo();
    int findWord(string pattern);
    void countWordAllAppearences(string pattern);
    void addNewPlayList(int plId);
    void removePlayList(int plId);
};
