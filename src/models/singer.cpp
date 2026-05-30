#include <iostream>
#define MAX_Music_Capacity 50
#include "singer.h"
using namespace std;
int singer::allTimeSingerCount = 0;
singer::singer(string name)
{
    this->name = name;
    this->id = allTimeSingerCount++;
    musicIds = new linkList<int>(MAX_Music_Capacity);
}
singer::~singer()
{
    this->musicIds->~linkList();
}
int singer::getid()
{
    return this->id;
}
linkList<int> *singer::getMList()
{
    return this->musicIds;
}
string singer::getName()
{
    return this->name;
}
void singer::addMusic(int Musicid)
{
    this->musicIds->add(Musicid);
}
void singer::displayAll(MSparseSet &musicSpars)
{
    cout << "***************\nsinger id: " << this->id << " singer name: " << this->name << " " << endl;
    if (this->musicIds->length() > 0)
    {
        Node<int> *firstId = this->getMList()->getHead();

        cout << "Singer songs:\n";
        while (firstId != nullptr)
        {
            music *temp = musicSpars.searchM(firstId->getData());
            temp->showInfo();
            firstId = firstId->getNext();
        }
    }
    else
    {
        cout << "this artist has no music" << endl;
    }
    cout << "***************" << endl;
}
void singer::removeAllSongs(MSparseSet &musicSpars)
{
    if (this->musicIds->length() > 0)
    {
        Node<int> *firstId = this->getMList()->getHead();
        while (firstId != nullptr)
        {
            musicSpars.deleteM(firstId->getData());
            firstId = firstId->getNext();
        }
    }
}
/* bool singer::findMusic(string input, MSparseSet &musicSpars)
{
    if (this->musicList->length() == 0)
        return false;
    bool checkFlag = false;
    Node<int> *temp = musicList->getHead();
    while (temp != nullptr)
    {
        music *tempp = musicSpars.searchM(temp->getData());
        if (tempp->getMname() == input)
        {
            cout << "Singer id: " << this->id << " ";
            tempp->showInfo();
            checkFlag = true;
        }
        temp = temp->getNext();
    }

    return checkFlag;
} */
/* music *singer::findMusic(int id)
{
    Node<music *> *temp = musicList->getHead();
    while (temp != nullptr)
    {
        if (temp->getData()->getId() == id)
        {
            return temp->getData();
        }
        temp = temp->getNext();
    }
    return nullptr;
} */