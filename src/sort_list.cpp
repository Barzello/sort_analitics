#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <iostream>
#include <stack>
#include <set>
#include "sort_list.hpp"
using namespace std;

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