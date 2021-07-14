// Homework6G.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <thread>
#include <fstream>
#include<time.h>
#include <windows.h>
using namespace std;

class node {
public:
	int value;
	node * next;
	node() { next = nullptr; }
	node(int i) {
		value = i; next = nullptr;
	}
};

class linked_list {
public:
	int num_nodes;
	node * head;
	linked_list() { num_nodes = 0; head = nullptr; }
	void make_list(int m, int n) {
		for (int i = 0; i < m; i++) {
			node * p = new node(rand() % n);
			p->next = head;
			head = p;
		}
		num_nodes = m;
	}
};

void sort(linked_list & L, node * p, int n)//using merge_sort to n nodes of L, with
						   //first nodes pointed by p
{
	cout << "Begin sort!" << endl;
	clock_t cstart, cends;
	cstart = clock();
	node *pos = p;
	for (int j = 0; j < n - 1; j++)
	{
		int smallest = pos->value;
		node *exam = pos->next;
		node *small_one = pos;
		for (int i = j; i < n - 1; i++)
		{
			if (exam->value < smallest)
			{
				smallest = exam->value;
				small_one = exam;
			}
			exam = exam->next;
		}
		int m = pos->value;
		pos->value = smallest;
		small_one->value = m;
		pos = pos->next;

	}
	cends = clock();
	cout << "The time is:" << cends - cstart << "ms" << endl;
}

void merge(linked_list & L, node * p1, int n1, node * p2, int n2)
//Merge n1 sorted nodes starting at p1 and n2 sorted nodes starting at p2.
//Assume that the n1+n2 nodes are adjacent nodes in L
{
	clock_t cstart, cends;
	cstart = clock();
	cout << endl << "merge begin!" << endl;
	int compare_time = n1;
	node *big = p2;
	for (int k = 0; k < n2 - 1; k++)
	{
		big = big->next;
	}
	while (compare_time != 0)
	{
		node *compare_pos = p1;
		for (int i = 0; i < compare_time - 1; i++)
		{
			compare_pos = compare_pos->next;
		}
		node *compare_tar = compare_pos->next;
		while (compare_tar != big)
		{
			int stop_sign = 0;
			if (compare_pos->value > compare_tar->value)
			{
				int L = compare_pos->value;
				int R = compare_tar->value;
				compare_pos->value = R;
				compare_tar->value = L;
			}
			else
			{
				break;
			}
			compare_pos = compare_pos->next;
			compare_tar = compare_tar->next;
		}
		compare_time--;
	}
	cout << endl << "merge coplete!" << endl;//
	cends = clock();
	cout << "The time is:" << cends - cstart << "ms" << endl;
};

//For the sort and merge, you can change both node values and pointers.
//Your implementation has to be an in-place sorting -- no external data structures are allowed

int main() {

	DWORD start_time = GetTickCount();
	linked_list L;
	L.make_list(10000, 1500);
	int process, process_odd = 0;
	if (L.num_nodes % 4 != 0)
	{
		process_odd = L.num_nodes % 4;
	}
	process = L.num_nodes / 4;
	/*
	clock_t cstart, cends;
	cstart = clock();
	sort(L, L.head, L.num_nodes);
	cends = clock();
	cout << "The sort time is:" << cends - cstart << "ms" << endl;
	*/
	clock_t cstart, cends;
	cstart = clock();
	node *marker_nex = L.head;
	node *marker_pre = L.head;
	thread t1(sort, ref(L), marker_pre, process);

	for (int j = 0; j < process; j++)
	{
		marker_nex = marker_nex->next;
	}
	thread t2(sort, ref(L), marker_nex, process);
	for (int j = 0; j < process; j++)
	{
		marker_nex = marker_nex->next;
	}
	thread t3(sort, ref(L), marker_nex, process);

	for (int j = 0; j < process; j++)
	{
		marker_nex = marker_nex->next;
	}
	thread t4(sort, ref(L), marker_nex, process+ process_odd);
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	cends = clock();
	cout << "The sort use thread time is:" << cends - cstart << "ms" << endl;

	node *left=L.head, *right=L.head;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < process; j++)
		{
			right = right->next;
		}
		if (i != 2)
		{
			merge(ref(L), left, process*(i+1), right, process);
		}
		else
		{
			merge(ref(L), left, process*(i + 1), right, process + process_odd);
		}
	}

	node *out = L.head;
	ofstream out1("output.txt");
	for (int i = 0; i < L.num_nodes; i++) 
	{
		out1 << out->value<<" ";
		out = out->next;
	}
	out1.close();
	cout << endl << "Program finish!" << endl;

	DWORD end_time = GetTickCount();
	cout << "The program running time is:" << (end_time - start_time) << "ms." << endl;
	//Create 4 threads to speed up the merge sort.
	//Implement the sort and merge funcitons
	//Write the sorted results to HW6data.txt
	getchar();//
	getchar();//
	return 0;
}
