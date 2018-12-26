/*
* For problem: https://www.codechef.com/problems/SIRUSERI
*/
using namespace std;
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>
#include <list>
typedef struct vote
{
    unsigned int party1;
    unsigned int party2;
    char picked;
}vote_t;

typedef struct voteList
{
    vote_t district;
    struct voteList* next;
}node_t;

typedef enum partyType
{
    Party1 =0,
    Party2
}partyType_t;
list<vote_t> p1Winners;
list<vote_t> p2Winners;
static int noOfTestCases;
static int noOfStates;
static int noOfDistricts;
static vote_t* voteList;


void printList(list<vote_t> list)
{
    #if 0
    while(list!=NULL)
    {
        printf("%d\t%d\n", list->district.party1, list->district.party2);
        list = list->next;
    }
    #endif
    for(auto it = list.begin(); it != list.end();it++)
    {
        printf("%d\t%d\n", it->party1, it->party2);
    }
}

unsigned int getSmallestElementIndex(unsigned int* sortedArray, int maxIndex)
{
    unsigned int smallestIndex = 0;
    for (int index = 0; index < maxIndex; index++)
    {
        if(sortedArray[smallestIndex] > sortedArray[index])
        {
            smallestIndex = index;
        }
    }
    return smallestIndex;
}

int getNBiggestNumber(unsigned int N, unsigned int *sortedArray)
{
    if (N > noOfStates)
    {
        return -1;
    }
    else
    {
        sortedArray = (unsigned int *) malloc(sizeof(unsigned int) * N);
        if (sortedArray == NULL)
        {
            return -1;
        }
        memset(sortedArray, 0, sizeof(unsigned int) * N);
        for(int index = 0; index <(noOfDistricts * noOfStates); index++)
        {
            if (index < N)
            {
                sortedArray[index] = voteList[index].party1;
            }
            else
            {
                int smallestIndex = getSmallestElementIndex(sortedArray, N);
                {
                    if (sortedArray[smallestIndex] < voteList[index].party1)
                    {
                        sortedArray[smallestIndex] = voteList[index].party1;
                    }
                }
            }

        }
        for(int index = 0; index < N; index++)
        {
            printf("%d\n", sortedArray[index]);
        }
    }
}
void printVoteList()
{
    unsigned int index = 0;
    printf("District\t party1\t party2\n");
    for(index = 0; index <(noOfDistricts * noOfStates); index++)
    {
        printf("%d\t%d\t%d\n", index, voteList[index].party1, voteList[index].party2);
    }
    return;
}

list<vote_t> getWinners(partyType_t party)
{

    list<vote_t> p1List;
    /*node_t* newEntry = NULL;
    node_t* nodeEntry = NULL;*/
    for(int index = 0; index < (noOfDistricts * noOfStates); index ++)
    {
        if((party == Party1 && voteList[index].party1 > voteList[index].party2) || (party == Party2 && voteList[index].party1 < voteList[index].party2))
        {
            #if 0
            if(p1List == NULL)
            {
                p1List = malloc(sizeof(node_t));
                p1List->district.party1 = voteList[index].party1;
                p1List->district.party2 = voteList[index].party2;
                p1List->next = NULL;
            }
            else
            {
                newEntry = malloc(sizeof(node_t));
                newEntry->district.party1 = voteList[index].party1;
                newEntry->district.party2 = voteList[index].party2;
                newEntry->next = NULL;
                nodeEntry = p1List;
                while(nodeEntry->next!=NULL)
                {
                    nodeEntry = nodeEntry->next;
                }
                nodeEntry->next = newEntry;
            }
            #endif
            vote_t voteCount = *(voteList + index);

            p1List.push_back(voteCount);
        }
    }
    return p1List;
}

void calculateP1Winners()
{
    int totalWinners = 0;
    int maxOpponentCnt = noOfDistricts -1;
    int pickedCnt = 0;
    int currentOpponentCnt = 0;
    int endReached = 0;
    for(auto p1Iter = p1Winners.begin(); p1Iter != p1Winners.end(); p1Iter++)
    {
        currentOpponentCnt = 0;
        pickedCnt = 0;
        printf("Current p1 entry:%d\n", p1Iter->party1);
        for (auto p2Iter = p2Winners.begin(); p2Iter != p2Winners.end(); p2Iter++)
        {
            // printf("Current p2 entry:%d\n", p2Iter->party2);
            auto dummy = p2Iter;
            dummy++;
            if(dummy == p2Winners.end())
            {
                endReached = 1;
                printf("Last element reachhed\n");
            }
            if(p2Iter->picked == 1)
            {
                pickedCnt++;
                continue;
            }
            if(p1Iter->party1 > p2Iter->party2)
            {
                currentOpponentCnt++;
                if(currentOpponentCnt == maxOpponentCnt || endReached == 1)
                {
                    printf("Erasing p1 Entry:%d\n", p1Iter->party1);
                    printf("Erasing p2 Entry:%d..%d\n", p2Winners.begin()->party2, p2Iter->party2);
                    for (auto iter = p2Winners.begin(); iter != p2Winners.end(); iter++)
                    {
                        if(iter == p2Iter)
                        {
                            break;
                        }
                        iter->picked = 1;
                    }
                    p2Iter->picked = 1;
                    /*p1Winners.erase(p1Iter);
                    p2Winners.erase(p2Winners.begin(), p2Iter);*/
                    totalWinners++;
                    break;
                }
            }
            else
            {
                break;
            }
        }
        printf("Picked cooount:%d\n", pickedCnt);
        if(p2Winners.size() - pickedCnt == 0)
        {
            totalWinners += p1Winners.size() / noOfDistricts;
            break;
        }

    }
    printf("Max P1 winners:%d\n", totalWinners);
    return;
}

int getVoteCount()
{
    char* party1VoteList = NULL;
    char* party2VoteList = NULL;
    size_t lineSz;
    int retVal = 0;
    char* vote;
    unsigned int voteVal = 0;
    unsigned int* maxVoteList = NULL;
    getline(&party1VoteList, &lineSz, stdin);
    getline(&party2VoteList, &lineSz, stdin);
    voteList = (vote_t*) malloc(sizeof(vote_t) * noOfDistricts * noOfStates);
    vote = strtok(party1VoteList, " ");
    if (vote != NULL)
    {
        voteList[0].party1 = strtoul(vote,NULL, 10);
    }
    for(int index = 1; index < (noOfDistricts * noOfStates); index++)
    {
        vote = strtok(NULL, " ");
        if(NULL == vote)
        {
            return -1;
        }
        voteList[index].party1 = strtoul(vote, NULL, 10);
    }
    vote = strtok(party2VoteList, " ");
    if (vote != NULL)
    {
        voteList[0].party2 = strtoul(vote,NULL, 10);
    }
    for(int index = 1; index < (noOfDistricts * noOfStates); index++)
    {
        vote = strtok(NULL, " ");
        if(NULL == vote)
        {
            return -1;
        }
        voteList[index].party2 = strtoul(vote, NULL, 10);
        voteList[index].picked = 0;
    }
    printVoteList();
    //getNBiggestNumber(noOfStates, maxVoteList);
    p1Winners = getWinners(Party1);
    p2Winners = getWinners(Party2);
    p1Winners.sort([](const vote_t&a, const vote_t &b){return a.party1 < b.party1;});
    p2Winners.sort([](const vote_t&a, const vote_t &b){return a.party2 < b.party2;});
    printf("P1 Winners\n");
    printList(p1Winners);
    printf("P2 Winners\n");
    printList(p2Winners);
    calculateP1Winners();
    return 0;
}

int getStateAndDistrictCount()
{
    char* line = NULL;
    unsigned long lineSz;
    getline(&line, &lineSz, stdin);
    sscanf(line, "%d %d", &noOfStates, &noOfDistricts);
    free(line);
    line = NULL;
    return 0;
}

int getUserInput()
{

    char* line = NULL;
    unsigned long lineSz;
    getline(&line, &lineSz, stdin);
    sscanf(line, "%d", &noOfTestCases);
    free(line);
    line = NULL;
    printf("Number of test cases:%d\n", noOfTestCases);
    for (int index =0; index < noOfTestCases; index++)
    {
        getStateAndDistrictCount();
        printf("Number of States:%d\n", noOfStates);
        printf("Number of Districts:%d\n", noOfDistricts);
        getVoteCount();
    }

    return 0;
}

int main()
{
    getUserInput();
    return 0;

}