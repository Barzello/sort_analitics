#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "sysinfoapi.h"
#include "sort_list.hpp"
using namespace std;
/* Private defines -----------------------------------------------------------*/
#define MAX_OUTPUT_DATA                         (1000)
#define MAX_GENERATED_NUM_OF_VALUES             (20000)
/* Private variables ---------------------------------------------------------*/
int made[MAX_GENERATED_NUM_OF_VALUES]; //storage to work with random values
int arr[MAX_GENERATED_NUM_OF_VALUES]; //storage for start random values

DWORD bubblesort_delta[MAX_OUTPUT_DATA]={0,};
DWORD combsort_delta[MAX_OUTPUT_DATA]={0,};
DWORD insertionsort_delta[MAX_OUTPUT_DATA]={0,};
DWORD treesort_delta[MAX_OUTPUT_DATA]={0,};
DWORD gnomesort_delta[MAX_OUTPUT_DATA]={0,};
DWORD shakersort_delta[MAX_OUTPUT_DATA]={0,};
DWORD selectionsort_delta[MAX_OUTPUT_DATA]={0,};
/* Private function prototypes -----------------------------------------------*/


/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

int randint() //function to generate random values
{
    return rand() * RAND_MAX + rand();
}

void random_generator(uint32_t NUM) //function to generate and fill mass of random values
{   
	for (uint32_t j = 0; j < NUM; j++)
	{
		arr[j] = randint() % (int)10;  //work with global values
	}
		         
}

void prepare_for_sort(uint32_t NUM) //copy random massive to sort it
{
	for (uint32_t j = 0; j < NUM; j++)
	{
		made[j]=arr[j]; //work with global values
	}
}


void writeFile(DWORD *delta, string section) //function used to create txt file
{
    FILE *fp;
    const string s = section + ".txt";
	cout << s.c_str() << endl;
    fp=freopen(s.c_str(), "w", stdout);
	for (int i = 0; i < MAX_OUTPUT_DATA; i++)
    	printf("%d\n", delta[i]);
    fclose(fp);
}

void start_sort_experiment(DWORD *input_delta, void (*fun_ptr)(int* l, int* r), string filename)
{
	for(uint32_t i=0;i<MAX_OUTPUT_DATA;i++)
	{
        if((i*100)>MAX_GENERATED_NUM_OF_VALUES) break;
		prepare_for_sort(i*100);
        printf("%ld\n",i*100);
		DWORD t1 = GetTickCount();
		fun_ptr(made,made+i*100);
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
    random_generator(MAX_GENERATED_NUM_OF_VALUES);
    start_sort_experiment(bubblesort_delta,bubblesort,section_bubble);
    start_sort_experiment(combsort_delta,combsort,"combsort");
    start_sort_experiment(insertionsort_delta,insertionsort,"insertionsort");
    start_sort_experiment(treesort_delta,treesort,"treesort");
    start_sort_experiment(gnomesort_delta,gnomesort,"gnomesort");
    start_sort_experiment(shakersort_delta,shakersort,"shakersort");
    start_sort_experiment(selectionsort_delta,selectionsort,"selectionsort");
    return 0;
}