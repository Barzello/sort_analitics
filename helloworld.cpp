#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <stack>
#include <cassert>
#include <queue>
#include <map>
#include <set>
#include <iterator>
#include <bitset>
//https://habr.com/ru/post/335920/
//https://pastebin.com/M08sgZS6
#include "sysinfoapi.h"

using namespace std;
 
const int N = 10000;
int made[N];
int arr[N];
int curt = 1;

//deltas to write
DWORD bubblesort_delta[100]={0,};
DWORD combsort_delta[100]={0,};
DWORD insertionsort_delta[100]={0,};
DWORD treesort_delta[100]={0,};
DWORD gnomesort_delta[100]={0,};
DWORD shakersort_delta[100]={0,};
DWORD selectionsort_delta[100]={0,};

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


//bubble sort
void bubblesort(int* l, int* r)
{
    int sz = r - l;
    if (sz <= 1) return;
    bool b = true;
    while (b) {
        b = false;
        for (int* i = l; i + 1 < r; i++) {
            if (*i > *(i + 1)) {
                swap(*i, *(i + 1));
                b = true;
            }
        }
        r--;
    }
}
// Comb sort
void combsort(int* l, int* r) 
{
	int sz = r - l;
	if (sz <= 1) return;
	double k = 1.2473309;
	int step = sz - 1;
	while (step > 1) 
	{
		for (int* i = l; i + step < r; i++) 
		{
			if (*i > *(i + step))
				swap(*i, *(i + step));
		}
		step /= k;
	}
	bool b = true;
	while (b) 
	{
		b = false;
		for (int* i = l; i + 1 < r; i++) 
		{
			if (*i > *(i + 1)) 
			{
				swap(*i, *(i + 1));
				b = true;
			}
		}
	}
}
// Insertion sort
void insertionsort(int* l, int* r) 
{
	for (int *i = l + 1; i < r; i++) 
	{
		int* j = i;
		while (j > l && *(j - 1) > *j) 
		{
			swap(*(j - 1), *j);
			j--;
		}
	}
}
// Tree sort
void treesort(int* l, int* r) 
{
	multiset<int> m;
	for (int *i = l; i < r; i++)
		m.insert(*i);
	for (int q : m)
		*l = q, l++;
}


// Gnome sort
void gnomesort(int* l, int* r) 
{
	int *i = l;
	while (i < r) {
		if (i == l || *(i - 1) <= *i) i++;
		else swap(*(i - 1), *i), i--;
	}
}

//shakesort
void shakersort(int* l, int* r)
{
    int sz = r - l;
    if (sz <= 1) return;
    bool b = true;
    int* beg = l - 1;
    int* end = r - 1;
    while (b) {
        b = false;
        beg++;
        for (int* i = beg; i < end; i++) 
		{
            if (*i > *(i + 1)) 
			{
                swap(*i, *(i + 1));
                b = true;
            }
        }
        if (!b) break;
        end--;
        for (int* i = end; i > beg; i--) 
		{
            if (*i < *(i - 1)) 
			{
                swap(*i, *(i - 1));
                b = true;
            }
        }
    }
}

//selectionsort
void selectionsort(int* l, int* r)
 {
    for (int *i = l; i < r; i++) 
	{
        int minz = *i, *ind = i;
        for (int *j = i + 1; j < r; j++)
		{
            if (*j < minz) minz = *j, ind = j;
        }
        swap(*i, *ind);
    }
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

	test_random_gen();
	
	prepare_for_sort();
	DWORD t1_b = GetTickCount();
	bubblesort(made,made+N);
	DWORD t2_b = GetTickCount();
	// bubblesort(made,made+N);

	prepare_for_sort();
	DWORD t1_c = GetTickCount();
	combsort(made,made+N);
	DWORD t2_c = GetTickCount();
	// combsort(made,made+N);

	prepare_for_sort();
	DWORD t1_i = GetTickCount();
	insertionsort(made,made+N);
	DWORD t2_i = GetTickCount();
	// insertionsort(made,made+N);
	
	prepare_for_sort();
	DWORD t1_t = GetTickCount();
	treesort(made,made+N);
	DWORD t2_t = GetTickCount();
	// treesort(made,made+N);

	prepare_for_sort();
	DWORD t1_g = GetTickCount();
	gnomesort(made,made+N);
	DWORD t2_g = GetTickCount();
	// gnomesort(made,made+N);

	prepare_for_sort();
	DWORD t1_sh = GetTickCount();
	shakersort(made,made+N);
	DWORD t2_sh = GetTickCount();
	// gnomesort(made,made+N);

	prepare_for_sort();
	DWORD t1_se = GetTickCount();
	selectionsort(made,made+N);
	DWORD t2_se = GetTickCount();
	// gnomesort(made,made+N);
	


	printf("bubblesort delta: %d\n",t2_b-t1_b);
	printf("combsort delta: %d\n",t2_c-t1_c);
	printf("insertionsort delta: %d\n",t2_i-t1_i);
	printf("treesort delta: %d\n",t2_t-t1_t);
	printf("gnomesort delta: %d\n",t2_g-t1_g);
	printf("shakersort delta: %d\n",t2_sh-t1_sh);
	printf("selectionsort delta: %d\n",t2_se-t1_se);

    return 0;
}