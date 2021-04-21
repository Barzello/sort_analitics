#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "sysinfoapi.h"
#include "sort_list.hpp"
using namespace std;
/* Private variables ---------------------------------------------------------*/
const int N = 1000000;
int made[N];
int arr[N];
int curt = 1;

DWORD bubblesort_delta[100]={0,};
DWORD combsort_delta[100]={0,};
DWORD insertionsort_delta[100]={0,};
DWORD treesort_delta[100]={0,};
DWORD gnomesort_delta[100]={0,};
DWORD shakersort_delta[100]={0,};
DWORD selectionsort_delta[100]={0,};
/* Private function prototypes -----------------------------------------------*/


/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

int randint() //function to generate random values
{
    return rand() * RAND_MAX + rand();
}


void random_generator(int NUM) //function to generate and fill mass of random values
{   
	for (int j = 0; j < NUM; j++)
	{
		arr[j] = randint() % (int)10;  //work with global values
	}
		         
}

void prepare_for_sort(int NUM) //copy random massive to sort it
{
	for (int j = 0; j < NUM; j++)
	{
		made[j]=arr[j]; //work with global values
	}
}


void writeFile(DWORD *delta, string section) //function used to create txt file
{
    const string s = section + to_string(curt) + ".txt";
	cout << s.c_str() << endl;
    freopen(s.c_str(), "w", stdout);
	for (int i = 0; i < 100; i++)
    	printf("%d\n", delta[i]);
    fclose(stdout);
    curt++;
}

void start_sort_experiment(DWORD *input_delta, void (*fun_ptr)(void), string filename)
{
	for(uint8_t i=0;i<100;i++)
	{
		prepare_for_sort(i);
		DWORD t1 = GetTickCount();
		fun_ptr();
		DWORD t2 = GetTickCount();
		input_delta[i]=t2-t1;
	}
	writeFile(input_delta, filename);
}

int main(void)
{
	string section_bubble="bubblesort";
	string section_comb="combsort";
	string section_insert="insertionsort";
	string section_tree="treesort";
	string section_gnome="gnomesort";
	string section_shaker="shakersort";
	string section_selection="selectionsort";

    return 0;
}