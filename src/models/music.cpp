#include "music.h"
#include "math.h"
#include <string>
#define Max_PLayList_Count 10
#define MAx_Lines_Lyrics 50
using namespace std;

struct suffix
{
    int index;
    int rank[2];
};

int convertStringToIntMu(string input)
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

int music::allTimeMusicCounter = 0;
music::music(string Mname, int releaseYear)
{
    this->id = allTimeMusicCounter++;
    this->Mname = Mname;
    this->releaseYear = releaseYear;
    this->playListsID = new linkList<int>(Max_PLayList_Count);
    this->lyrics = new linkList<string>(MAx_Lines_Lyrics);
    string temp;
    getline(cin, temp);
    while (temp[temp.size() - 1] == '\"')
    {
        this->lyrics->add(temp);
        getline(cin, temp);
    }
    this->singerID = convertStringToIntMu(temp);
}
music::~music()
{
    lyrics->~linkList();
    playListsID->~linkList();
    delete[] lyrics;
    delete[] playListsID;
}
int music::getId()
{
    return this->id;
}
int music::getSingerId()
{
    return this->singerID;
}
int music::getReleaseYear()
{
    return this->releaseYear;
}
linkList<string> *music::getLyrics()
{
    return lyrics;
}
string music::getMname()
{
    return this->Mname;
}
void music::showInfo()
{
    cout << "*music id: " << this->id << "\nmusic name:" << this->Mname << "\nrelease year:" << this->releaseYear << endl
         << "lyrics:\n";
    Node<string> *temp = this->lyrics->getHead();
    while (temp != nullptr)
    {
        cout << temp->getData() << endl;
        temp = temp->getNext();
    }
}

int cmp(struct suffix a, struct suffix b)
{
    if (a.rank[0] == b.rank[0])
    {
        if (a.rank[1] > b.rank[1])
            return 1;
        else
            return 0;
    }
    else
    {
        if (a.rank[0] > b.rank[0])
            return 1;
        else
            return 0;
    }
}
void manualSort(struct suffix suffixes[], int n)
{

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (cmp(suffixes[j], suffixes[j + 1]) == 1)
            {
                struct suffix temp = suffixes[j];
                suffixes[j] = suffixes[j + 1];
                suffixes[j + 1] = temp;
            }
        }
    }
}

int *buildSuffixArray(string txt, int n)
{

    struct suffix suffixes[n];
    for (int i = 0; i < n; i++)
    {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = ((i + 1) < n) ? (txt[i + 1] - 'a') : -1;
    }

    manualSort(suffixes, n);
    int ind[n];
    for (int k = 4; k < 2 * n; k = k * 2)
    {
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;

        for (int i = 1; i < n; i++)
        {
            if (suffixes[i].rank[0] == prev_rank && suffixes[i].rank[1] == suffixes[i - 1].rank[1])
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }

        for (int i = 0; i < n; i++)
        {
            int nextindex = suffixes[i].index + k / 2;
            suffixes[i].rank[1] = (nextindex < n) ? suffixes[ind[nextindex]].rank[0] : -1;
        }

        manualSort(suffixes, n);
    }
    int *suffixArr = new int[n];
    for (int i = 0; i < n; i++)
    {
        suffixArr[i] = suffixes[i].index;
    }
    return suffixArr;
}
int findPattern(string text, int n, int suffixArray[], string pattern)
{
    int m = pattern.length();
    int left = 0;
    int right = n - 1;
    int firstAppearance = -1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int cmp = 0;
        for (int i = 0; i < m; i++)
        {
            if (suffixArray[mid] + i >= n || text[suffixArray[mid] + i] != pattern[i])
            {
                if (suffixArray[mid] + i >= n || text[suffixArray[mid] + i] < pattern[i])
                {
                    cmp = -1;
                }
                else
                    cmp = 1;
                break;
            }
        }
        if (cmp == 0)
        {
            firstAppearance = suffixArray[mid];
            right = mid - 1;
        }
        else if (cmp < 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return firstAppearance;
}
int music::findWord(string pattern)
{
    Node<string> *temp = this->lyrics->getHead();
    int lineCounter = 1;
    while (temp != nullptr)
    {
        int *suffixArray = new int[pattern.length()];
        suffixArray = buildSuffixArray(temp->getData(), temp->getData().length());
        int result = findPattern(temp->getData(), temp->getData().length(), suffixArray, pattern);
        delete[] suffixArray;
        if (result != -1)
        {
            cout << "found the word at position " << result << " at line : " << lineCounter << " in lyrics\n";
            return 1;
        }
        lineCounter++;
        temp = temp->getNext();
    }
    cout << "dind't find that word in the music\n";
    return -1;
}
/* int *lpsCal(string pat)
{
    int len = 0;
    int i = 1;
    int *res = new int[pat.length()]{0};
    for (; i < pat.size(); i++)
    {
        if (pat[i] == pat[len])
        {
            len++;
            res[i] = len;
        }
        else
        {
            if (len != 0)
            {
                len = res[len - 1];
                i--;
            }
        }
    }
    return res;
}
int findPat(string txt, string pat, int *indexess)
{
    int *lps = lpsCal(pat);
    int resultCounter = 0;
    int i = 0;
    int j = 0;
    while (j < txt.size())
    {
        if (txt[j] == pat[i])
        {
            i++;
            j++;
            if (i == pat.size())
            {
                indexess[resultCounter++] = j - i;
                i = lps[i - 1];
            }
        }
        else
        {
            if (i == 0)
            {
                j++;
            }
            else
            {
                i = lps[i - 1];
            }
        }
    }
    delete[] lps;
    return resultCounter;
} */
int countOccurrences(string text, int n, int suffixArray[], string pattern)
{
    int m = pattern.length();
    int left = 0, right = n - 1;
    int firstOccurrence = -1, lastOccurrence = -1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int cmp = 0;
        for (int i = 0; i < m; i++)
        {
            if (suffixArray[mid] + i >= n || text[suffixArray[mid] + i] != pattern[i])
            {
                if (suffixArray[mid] + i >= n || text[suffixArray[mid] + i] < pattern[i])
                {
                    cmp = -1;
                }
                else
                {
                    cmp = 1;
                }
                break;
            }
        }
        if (cmp == 0)
        {
            firstOccurrence = mid;
            right = mid - 1;
        }
        else if (cmp < 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    if (firstOccurrence == -1)
    {
        return 0;
    }

    left = 0;
    right = n - 1;
    while (left <= right)
    {
        int mid = left + (right - left) / 2;
        int cmp = 0;
        for (int i = 0; i < m; i++)
        {
            if (suffixArray[mid] + i >= n || text[suffixArray[mid] + i] != pattern[i])
            {
                if (suffixArray[mid] + i >= n || text[suffixArray[mid] + i] < pattern[i])
                {
                    cmp = -1;
                }
                else
                {
                    cmp = 1;
                }
                break;
            }
        }
        if (cmp == 0)
        {
            lastOccurrence = mid;
            left = mid + 1;
        }
        else if (cmp < 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    return lastOccurrence - firstOccurrence + 1;
}

void music::countWordAllAppearences(string pattern)
{
    Node<string> *temp = this->lyrics->getHead();
    int totalFound = 0;
    while (temp != nullptr)
    {
        /*         int *indexess = new int[temp->getData().length()];
                int counter = findPat(temp->getData(), pattern, indexess);
                if (counter > 0)
                {
                    cout << "Found this word at line " << lineCounter << " in this positions in lyrics :";
                    for (int i = 0; i < counter; i++)
                    {
                        cout << indexess[i] << " ";
                    }
                    cout << endl;
                } */
        int *suffixArray = new int[temp->getData().length()];
        suffixArray = buildSuffixArray(temp->getData(), temp->getData().length());
        int counter = countOccurrences(temp->getData(), temp->getData().size(), suffixArray, pattern);
        totalFound += counter;
        // delete[] indexess;
        temp = temp->getNext();
        delete[] suffixArray;
    }
    if (totalFound == 0)
        cout << "dind't find that word in the music\n";
    else
        cout << "Total Count: " << totalFound << endl;
}
void music::addNewPlayList(int plId)
{
    this->playListsID->add(plId);
}
void music::removePlayList(int plId)
{
    this->playListsID->remove(plId);
}

linkList<int> *music::getPlayListsID()
{
    return this->playListsID;
}
