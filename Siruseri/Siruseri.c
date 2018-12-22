/*
* For problem: https://www.codechef.com/problems/SIRUSERI
*/
#include <stdio.h>
static int noOfTestCases;
static int noOfStates;
static int noOfDistricts;
int main()
{
    char* line;
    unsigned long lineSz;
    getline(&line, &lineSz, stdin);
    printf("Read line:%s \n", line);
    printf("Line Size:%ld \n", lineSz);
    sscanf(line, "%d", &noOfTestCases);
    printf("Number of test cases:%d", noOfTestCases);

    return 0;

}