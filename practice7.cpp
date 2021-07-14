#include "pch.h"
#include <iostream>
#include <thread>
#include <list>
#include <condition_variable>
#include <mutex>
#include <chrono> 
#include <time.h>

using namespace std;
mutex locker;
condition_variable cv1, cv2;

ostream & operator<<(ostream &string, list<int> &t)
{
	string << "( ";
	list<int>::iterator it = t.begin();
	for (int i = 1; i <= t.size(); i++)
	{
		if (i < t.size())
		{
			string << *it << ", ";
		}
		else
		{
			string << *it << " )";
		}
		it++;
	}
	return string;
}

class Plant
{
public:
	int checktime = 1;
	list<int>capacity = { 0,0,0,0 };
	list<int>realtime_load;
	Plant(list<int>&l)
	{
		auto it = capacity.begin();
		auto value = l.begin();
		for (int i = 0; i < 4; i++)
		{
			*it = *value;
			it++;
			value++;
		}
		realtime_load = { 0,0,0,0 };
	};
	list<int> buffer_input_order(list<int>&l);
	list<int> buffer_output_order(list<int>&l);
	list<int> place_part_request();
	list<int> place_product_request();
	bool order_checking(list<int>&l, list<int>&k);
	void partworker(int i);
	void productworker(int i);
	int list_sum(list<int>&l);
};

list<int> Plant::place_part_request()
{
	srand(time(NULL) + rand());
	list<int> partproduced = { 0,0,0,0 };
	int parttype = rand() % 2 + 1;//create[1,2]
	int ABCD = rand() % 4;//create[0,3]
	if (parttype == 1)
	{
		auto it1 = partproduced.begin();
		for (int i = 0; i < ABCD; i++)
		{
			it1++;
		}
		*it1 = 4;
	}
	if (parttype == 2)
	{
		int num1 = rand() % 3 + 1;//create[1,4)
		int num2 = 4 - num1;
		int pos1 = ABCD;
		int pos2 = rand() % 3;//create[0,2];
		auto it2 = partproduced.begin();
		for (int i = 0; i < pos1; i++)
		{
			it2++;
		}
		*it2 = num1;
		if (pos2 >= pos1)
		{
			pos2++;
		}
		auto it3 = partproduced.begin();
		for (int i = 0; i < pos2; i++)
		{
			it3++;
		}
		*it3 = num2;
	}
	return partproduced;
}

list<int> Plant::place_product_request()
{
	srand(time(NULL) + rand());
	list<int> pickup_req = { 0,0,0,0 };
	int choice = rand() % 2 + 1;
	int p1 = rand() % 4;//create[0,3]
	auto it1 = pickup_req.begin();
	for (int i = 0; i < p1; i++)
	{
		it1++;
	}
	*it1 = choice;
	int next, last;
	if (choice == 2)
	{
		next = 1;
	}
	else
	{
		next = 2;
	}
	last = 4 - choice - next;
	int p2 = rand() % 4;
	while (p2 == p1)
	{
		p2 = rand() % 4;
		//cout << "find p2" << endl;
	}
	auto it2 = pickup_req.begin();
	for (int i = 0; i < p2; i++)
	{
		it2++;
	}
	*it2 = next;

	int p3 = rand() % 4;
	while (p3 == p2 || p3 == p1)
	{
		p3 = rand() % 4;
		//cout << "find p3" << endl;
	}
	auto it3 = pickup_req.begin();
	for (int i = 0; i < p3; i++)
	{
		it3++;
	}
	*it3 = last;
	return pickup_req;
}

int Plant::list_sum(list<int>&l)
{
	auto it = l.begin();
	int sum = 0;
	for (int i = 0; i < l.size(); i++)
	{
		sum = sum + *it;
		it++;
	}
	return sum;
}

bool Plant::order_checking(list<int>&l, list<int>&k)
{
	auto check = l.begin();
	auto check1 = k.begin();
	int test = 0;
	for (int i = 0; i < l.size(); i++)
	{
		if (*check == *check1)
		{
			test++;
		}
		check++;
		check1++;
	}
	if (test == l.size())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

list<int> Plant::buffer_output_order(list<int>&l)
{
	auto value = l.begin();
	auto load = realtime_load.begin();
	for (int i = 0; i < 4; i++)
	{
		if (*load >= *value)
		{
			*load = *load - *value;
			*value = 0;
		}
		else
		{
			*load = 0;
			*value = *value - *load;
		}
		value++;
		load++;
	}
	return l;
}

list<int> Plant::buffer_input_order(list<int>&l)
{
	auto cap = capacity.begin();
	auto value = l.begin();
	auto load = realtime_load.begin();
	for (int i = 0; i < 4; i++)
	{
		if (*cap - *load == 0)
		{

		}
		else
		{
			if (*cap - *load == *value)
			{
				*load = *cap;
				*value = 0;
			}
			else if (*cap - *load < *value)
			{
				*value = *value - (*cap - *load);
				*load = *cap;
			}
			else
			{
				*load = *load + *value;
				*value = 0;
			}
		}
		cap++;
		value++;
		load++;
	}
	return l;
}

void Plant::partworker(int i)
{
	list<int>part_order = { 0,0,0,0 };
	int num_of_part_order = 0;
	int partworkerID = i;
	srand(time(NULL) + rand());
	while (num_of_part_order < 6)
	{
		unique_lock<mutex> ulock1(locker);
		this_thread::sleep_for(chrono::milliseconds(rand() % 5 + 2));//sleep[2,6]ms
		part_order = place_part_request();//if previous order is done, create a new order
		if (num_of_part_order != 0)
		{
			cv1.wait(ulock1);
		}
		int check = 0;
		while (list_sum(part_order) != 0 && check!=checktime)
		{
			cout << "Part Worker ID: " << partworkerID << endl;
			cout << "Iteration: " << num_of_part_order + 1 << endl;
			cout << "Buffer State: " << realtime_load << endl;
			cout << "Place Request: " << part_order << endl;
			part_order = buffer_input_order(part_order);
			cout << "Updated Buffer State: " << realtime_load << endl;
			cout << "Updated Place Request: " << part_order << endl;
			list<int> save_buffer_state = realtime_load;
			this_thread::sleep_for(chrono::milliseconds(1));
			if (order_checking(save_buffer_state, realtime_load))
			{
				check++;
			}
			else
			{
				check = 0;
			}
			if (check == checktime)
			{
				cout << "Deadlock Detected" << endl;
				cout << "Aborted Iteration: " << num_of_part_order + 1 << endl;
				auto it = part_order.begin();
				for (int i = 0; i < part_order.size(); i++)
				{
					*it = 0;
					it++;
				}
			}
			cout << endl;
		}
		num_of_part_order++;
		cout << endl;
		cv2.notify_one();
	}
}

void Plant::productworker(int i)
{
	list<int>product_order = { 0,0,0,0 };
	int num_of_product_order = 0;
	int productworkerID = i;
	srand(time(NULL) + rand());
	while (num_of_product_order < 6)
	{
		unique_lock<mutex> ulock2(locker);

		this_thread::sleep_for(chrono::milliseconds(rand() % 5 + 2));
		product_order = place_product_request();
		if (num_of_product_order != 0)
		{
			cv2.wait(ulock2);
		}
		int check = 0;
		while (list_sum(product_order) != 0 && check != checktime)
		{
			cout << "Product Worker ID: " << productworkerID << endl;
			cout << "Iteration: " << num_of_product_order + 1 << endl;
			cout << "Buffer State: " << realtime_load << endl;
			cout << "Pickup Request: " << product_order << endl;
			product_order = buffer_output_order(product_order);
			cout << "Updated Buffer State: " << realtime_load << endl;
			cout << "Updated Pickup Request: " << product_order << endl;
			list<int> save_buffer_state = realtime_load;
			this_thread::sleep_for(chrono::milliseconds(1));
			if (order_checking(save_buffer_state, realtime_load))
			{
				check++;
			}
			else
			{
				check = 0;
			}
			if (check == checktime)
			{
				cout << "Deadlock Detected" << endl;
				cout << "Aborted Iteration: " << num_of_product_order + 1 << endl;
				auto it = product_order.begin();
				for (int i = 0; i < product_order.size(); i++)
				{
					*it = 0;
					it++;
				}
			}
			cout << endl;
		}
		num_of_product_order++;
		cout << endl;
		cv1.notify_one();
	}
		
}

int main() 
{
	const int number_of_part_workers = 20, number_of_product_workers = 20;//m>=n
	list<int>capacity = { 5,5,4,3 };
	Plant *P = new Plant(capacity);
	thread partworker[number_of_part_workers];
	thread productworker[number_of_product_workers];
	for (int i = 0; i < number_of_product_workers; i++)
	{
		partworker[i] = thread(&Plant::partworker, P, i);
		productworker[i] = thread(&Plant::productworker, P, i);
	}
	for (int i = number_of_product_workers; i < number_of_part_workers; i++) 
	{
		partworker[i] = thread(&Plant::partworker, P, i);
	}

	for (int i = 0; i < number_of_product_workers; i++) {
		partworker[i].join();
		productworker[i].join();
	}
	for (int i = number_of_product_workers; i < number_of_part_workers; i++)
	{
		partworker[i].join();
	}
	cout << "Program Finish!" << endl;
	getchar();
	getchar();
	return 0;
}
