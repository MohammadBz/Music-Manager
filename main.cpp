#include <iostream>
#include <string>
#include <windows.h>
#define MAX_VAL 50
#define MAX_CAPACITY 50
#include "sparseSet.h"
#include "MSparseSet.h"
#include "PLSparseSet.h"
#include "functions.cpp"
#include "QueueT.h"
using namespace std;

void help()
{
    cout << "$$$$$$$$$$$$$$$\n";
    cout << "$for adding new singer:adds SingerName\n$for deleting a singer:dels id\n$for finding a singer and display all their information: find id\n";
    cout << "$for printing all the singer and their musics:prints\n$for deleting all the information :cls\n$for finding a music and display its information:findm MusicName\n";
    cout << "$for deleting a music :delm artist_id music_id\n$for adding a new song: addm music_name year \"lyrics\" artist_id\n";
    cout << "$for searching a word in a song:search artist_id music_id word\n$for counting the appearence of a word in a song:countw artist_id music_id word\n";
    cout << "$for creating a new play list :addp name\n$for adding a new song to playList:addmp music_id playList_id\n";
    cout << "$for searching a specific song in a playList:searchm playList_id music_id\n";
    cout << "$for removing a song from a playList:delmp playList_id music_id\n$for seeing the musics in a plaList sorted by release date:showp playList_id\n";
    cout << "$for adding a playList to litening queue:addqp playList_Id\n$for pop a playList from listening queue:pop\n$for seeing the now playing play List:Np\n";
    cout << "$$$$$$$$$$$$$$$\n";
}
void deleteEverything(sparseSet &singersSpars, MSparseSet &musicSpars, PLSparseSet &playListSparse, QueueT<int> &playListQueue)
{
    musicSpars.clearData();
    singersSpars.clearData();
    playListSparse.clearData();
    playListQueue.clearData();
}
// g++ -o main main.cpp music.cpp singer.cpp sparseSet.cpp MSparseSet.cpp playList.cpp PLSparseSet.cpp
void menu()
{
    sparseSet singersSpars(MAX_VAL, MAX_CAPACITY);
    MSparseSet musicSpars(MAX_VAL, MAX_CAPACITY);
    PLSparseSet playListSparse(MAX_VAL, MAX_CAPACITY);
    QueueT<int> playListQueue(MAX_CAPACITY);

    while (true)
    {
        cout << "---------------\n";
        cout << "Please enter your Command :(-h for help and exit for closing the app)\n";
        string input;
        getline(cin, input);
        if (input == "-h")
            help();
        else if (input == "exit")
            return;
        else
        {
            string mode = extractWordAfterIndex(input, 0);
            if (mode == "adds")
                addNewSinger(input, singersSpars);
            else if (mode == "dels")
                deleteSinger(input, singersSpars, musicSpars, playListSparse);
            else if (mode == "find")
                findSinger(input, singersSpars, musicSpars);
            else if (mode == "prints")
                showAllSingers(singersSpars, musicSpars);
            else if (mode == "addm")
                addNewMusic(input, singersSpars, musicSpars);
            else if (mode == "delm")
                deleteMusic(input, singersSpars, musicSpars, playListSparse);
            else if (mode == "findm")
                findMusics(input, singersSpars, musicSpars);
            else if (mode == "search")
                findWord(input, singersSpars, musicSpars);
            else if (mode == "countw")
                findAllApearencesWord(input, singersSpars, musicSpars);
            else if (mode == "addp")
                addNewPlayList(input, playListSparse);
            else if (mode == "addmp")
                addMusicToPlayList(input, playListSparse, musicSpars);
            else if (mode == "searchm")
                searchMusicPlayList(input, playListSparse, musicSpars);
            else if (mode == "delmp")
                removeMusicFromPlayList(input, playListSparse, musicSpars);
            else if (mode == "showp")
                showMusicsInPlayList(input, playListSparse, musicSpars);
            else if (mode == "addqp")
                addPlayListToQeue(input, playListSparse, playListQueue);
            else if (mode == "pop")
                popFromPlayListqueue(playListQueue);
            else if (mode == "Np")
                showNowPlayingPlayList(playListQueue, playListSparse, musicSpars);
            else if (mode == "cls")
                deleteEverything(singersSpars, musicSpars, playListSparse, playListQueue);
            else
                cout << "Invalid Command\n";
        }
    }
    /*   playListQueue.~QueueT();
      playListSparse.~PLSparseSet();
      singersSpars.~sparseSet();
      musicSpars.~MSparseSet(); */
}
int main()
{
    system("color 0a");
    menu();
    return 0;
}