#include <iostream>
#include <math.h>
#include "linkList.h"
#include "music.h"
#include "singer.h"
#include "sparseSet.h"
#include "MSparseSet.h"
#include "PLSparseSet.h"
#include "playlist.h"
#include "QueueT.h"
using namespace std;

string extractWordAfterIndex(string input, int index)
{
    string result;
    while (input[index] != ' ' && input[index] != '\0')
    {
        result.push_back(input[index]);
        index++;
    }
    return result;
}
string extractLyricsAfterIndex(string input, int index)
{
    string result;
    result.push_back(input[index++]);
    while (input[index] != '\0' && input[index] != '"')
    {
        result.push_back(input[index++]);
    }
    result.push_back(input[index]);
    return result;
}
int convertStringToInt(string input)
{
    int result = 0;
    int power = pow(10, input.length() - 1);
    for (int i = 0; input[i] != ' ' && input[i] != '\0'; i++)
    {
        result += (input[i] - '0') * power;
        power /= 10;
    }
    return result;
}
void musicGetRemovedInPlayLists(music *temp, PLSparseSet &playListSparse)
{
    linkList<int> *playListsID = temp->getPlayListsID();
    Node<int> *headTemp = playListsID->getHead();
    while (headTemp != nullptr)
    {
        playListSparse.searchPL(headTemp->getData())->deleteS(temp->getId());
        headTemp = headTemp->getNext();
    }
}
void addNewSinger(string input, sparseSet &singersSpars)
{
    string singerName = extractWordAfterIndex(input, 5);
    singersSpars.insert(new singer(singerName));
    cout << "Done!\n";
}
void deleteSinger(string input, sparseSet &singersSpars, MSparseSet &musicSpars, PLSparseSet &playListSparse)
{
    string singerIdS = extractWordAfterIndex(input, 5);
    int singerId = convertStringToInt(singerIdS);
    singer *temp = singersSpars.searchS(singerId);
    if (temp != nullptr)
    {
        linkList<int> *musicList = temp->getMList();
        Node<int> *mTemp = musicList->getHead();
        while (mTemp != nullptr)
        {
            music *MTemp = musicSpars.searchM(mTemp->getData());
            if (MTemp != nullptr)
            {
                musicGetRemovedInPlayLists(MTemp, playListSparse);
            }
            mTemp = mTemp->getNext();
        }
    }
    singersSpars.deleteS(singerId, musicSpars);
    cout << "Done!\n";
}
void findSinger(string input, sparseSet &singerSpars, MSparseSet &musicSpars)
{
    string singerIdS = extractWordAfterIndex(input, 5);
    int singerId = convertStringToInt(singerIdS);
    singer *temp = singerSpars.searchS(singerId);
    if (temp == nullptr)
    {
        cout << "there is no singer with this id!\n";
    }
    else
    {
        temp->displayAll(musicSpars);
        cout << "Done!\n";
    }
}
void showAllSingers(sparseSet &singerSpars, MSparseSet &musicSpars)
{
    singerSpars.displayAllSingers(musicSpars);
}
void addNewMusic(string input, sparseSet &singerSpars, MSparseSet &musicSpars)
{
    string musicName = extractWordAfterIndex(input, 5);
    string yearS = extractWordAfterIndex(input, 6 + musicName.length());
    int year = convertStringToInt(yearS);
    music *newM = new music(musicName, year);
    singer *temp = singerSpars.searchS(newM->getSingerId());
    if (temp == nullptr)
    {
        cout << "there is no singer with this id!\n";
    }
    else
    {
        musicSpars.insert(newM);
        temp->addMusic(newM->getId());
        cout << "Done!\n";
    }
}

void deleteMusic(string input, sparseSet &singerSpars, MSparseSet &musicSpars, PLSparseSet &playListSparse)
{
    string artistIdS = extractWordAfterIndex(input, 5);
    int artistId = convertStringToInt(artistIdS);
    string musicIdS = extractWordAfterIndex(input, 6 + artistIdS.length());
    int musicId = convertStringToInt(musicIdS);
    singer *temp = singerSpars.searchS(artistId);
    if (temp == nullptr)
    {
        cout << "there is no singer with this id!\n";
    }
    else
    {
        music *musicTemp = musicSpars.searchM(musicId);
        if (musicTemp == nullptr)
            cout << "the song does not exist" << endl;
        else
        {
            if (temp->getMList()->search(musicId) == true)
            {
                temp->getMList()->remove(musicId);
                musicGetRemovedInPlayLists(musicTemp, playListSparse);
                musicSpars.deleteM(musicId);
            }
            else
                cout << "this singer don't have a song with that id\n";
        }
        cout << "Done!\n";
    }
}
void findMusics(string input, sparseSet &singerSparse, MSparseSet &musicSpars)
{
    string musicName = extractWordAfterIndex(input, 6);
    musicSpars.searchMusicShowOnly(musicName);
    // singerSparse.findMusics(musicName, musicSpars);
}
void findWord(string input, sparseSet &singersSpars, MSparseSet &musicSpars)
{
    string artistIdS = extractWordAfterIndex(input, 7);
    int artistId = convertStringToInt(artistIdS);
    string musicIdS = extractWordAfterIndex(input, 8 + artistIdS.length());
    int musicId = convertStringToInt(musicIdS);
    string word = extractWordAfterIndex(input, 9 + musicIdS.length() + artistIdS.length());
    singer *temp = singersSpars.searchS(artistId);
    if (temp == nullptr)
    {
        cout << "there is no singer with this id!\n";
    }
    else
    {
        music *musicTemp = musicSpars.searchM(musicId);
        if (musicTemp == nullptr)
            cout << "this artist don't have a song with that id" << endl;
        else
        {
            int result = musicTemp->findWord(word);
        }
    }
}
void findAllApearencesWord(string input, sparseSet &singersSpars, MSparseSet &musicSpars)
{
    string artistIdS = extractWordAfterIndex(input, 7);
    int artistId = convertStringToInt(artistIdS);
    string musicIdS = extractWordAfterIndex(input, 8 + artistIdS.length());
    int musicId = convertStringToInt(musicIdS);
    string word = extractWordAfterIndex(input, 9 + musicIdS.length() + artistIdS.length());
    singer *temp = singersSpars.searchS(artistId);
    if (temp == nullptr)
    {
        cout << "there is no singer with this id!\n";
    }
    else
    {
        music *musicTemp = musicSpars.searchM(musicId);
        if (musicTemp == nullptr)
            cout << "this artist don't have a song with that id" << endl;
        else
            musicTemp->countWordAllAppearences(word);
    }
}
void addNewPlayList(string input, PLSparseSet &playListSparse)
{
    string plName = extractWordAfterIndex(input, 5);
    playList *temp = new playList(plName, MAX_VAL, MAX_CAPACITY);
    playListSparse.insert(temp);
    cout << "Done!\n";
}
void addMusicToPlayList(string input, PLSparseSet &playListSparse, MSparseSet &musicSpars)
{
    string musicIds = extractWordAfterIndex(input, 6);
    int musicId = convertStringToInt(musicIds);
    string plIds = extractWordAfterIndex(input, 7 + musicIds.length());
    int plId = convertStringToInt(plIds);
    playList *pltemp = playListSparse.searchPL(plId);
    if (pltemp == nullptr)
        cout << "there is no playList With this id\n";
    else
    {
        music *musicTemp = musicSpars.searchM(musicId);
        if (musicTemp == nullptr)
            cout << "there is no music with this id\n";
        else
        {
            pltemp->insert(musicId);
            musicTemp->addNewPlayList(plId);
            cout << "Done!\n";
        }
    }
}
void searchMusicPlayList(string input, PLSparseSet &playListSparse, MSparseSet &musicSpars)
{
    string plIds = extractWordAfterIndex(input, 8);
    string musicIds = extractWordAfterIndex(input, 9 + plIds.length());
    int musicId = convertStringToInt(musicIds);
    int plId = convertStringToInt(plIds);
    playList *pltemp = playListSparse.searchPL(plId);
    if (pltemp == nullptr)
        cout << "there is no playList With this id\n";
    else
    {
        music *musicTemp = musicSpars.searchM(musicId);
        if (musicTemp == nullptr)
            cout << "there is no music with this id\n";
        else
        {
            if (pltemp->search(musicId) == true)
            {
                cout << "Founded\nplay list id:" << plId << endl;
                musicTemp->showInfo();
            }
            else
                cout << "Dind't find this song in playlist with this id" << plId << endl;
        }
    }
}
void removeMusicFromPlayList(string input, PLSparseSet &playListSparse, MSparseSet &musicSpars)
{
    string plIds = extractWordAfterIndex(input, 6);
    string musicIds = extractWordAfterIndex(input, 7 + plIds.length());
    int musicId = convertStringToInt(musicIds);
    int plId = convertStringToInt(plIds);
    playList *pltemp = playListSparse.searchPL(plId);
    if (pltemp == nullptr)
        cout << "there is no playList With this id\n";
    else
    {
        music *musicTemp = musicSpars.searchM(musicId);
        if (musicTemp == nullptr)
            cout << "there is no music with this id\n";
        else
        {
            pltemp->deleteS(musicId);
            musicTemp->removePlayList(plId);
            cout << "Done!" << endl;
        }
    }
}
void showMusicsInPlayList(string input, PLSparseSet &playListSparse, MSparseSet &musicspars)
{
    string plIds = extractWordAfterIndex(input, 6);
    int plId = convertStringToInt(plIds);
    playList *pltemp = playListSparse.searchPL(plId);
    if (pltemp == nullptr)
        cout << "there is no playList With this id\n";
    else
    {
        pltemp->displayAllsongs(musicspars);
    }
    cout << "Done!\n";
}
void addPlayListToQeue(string input, PLSparseSet &playListSparse, QueueT<int> &playListQueue)
{
    string ids = extractWordAfterIndex(input, 6);
    int id = convertStringToInt(ids);
    if (playListSparse.searchPL(id) == nullptr)
    {
        cout << "There is no play List with this id\n";
        return;
    }
    playListQueue.enqueue(id);
    cout << "Done!\n";
}
void popFromPlayListqueue(QueueT<int> &playListQueue)
{
    playListQueue.dequeue();
    cout << "Done!\n";
}
void showNowPlayingPlayList(QueueT<int> &playListQueue, PLSparseSet &playListSparse, MSparseSet &musicSparse)
{

    while (playListQueue.getFront() != -1)
    {
        if (playListSparse.searchPL(playListQueue.getArr()[playListQueue.getFront()]) == nullptr)
        {
            playListQueue.dequeue();
        }
        else
            break;
    }
    int nowPl = playListQueue.getFront();
    if (nowPl == -1)
    {
        return;
    }
    cout << "cuurent playList id:" << playListQueue.getArr()[nowPl] << endl
         << "Details:\n";
    playListSparse.searchPL(playListQueue.getArr()[nowPl])->displayAllsongs(musicSparse);
}