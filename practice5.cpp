#include "pch.h"
#include <iostream>
#include <memory>
using namespace std;

class node {
public:
	shared_ptr<node> east;
	shared_ptr<node> south;
	int value;
	node() {}
	node(int i) { value = i; }
};

class ring {
public:
	//Implement all functions described below
	//funciton operator[] can be invoked by other functions
	shared_ptr<node> head;
	int num_rows;
	int num_cols;
	ring() {}
	ring(int i, int j)//constructor
					   //i rows and j cols
					   //values from 0 to i*j-1
					//See the photo for ring structures.
	{
		if (i == 0 || j == 0)
		{
			cout << "The ring does not exist!" << endl;
			return;
		}
		num_cols = j;
		num_rows = i;
		node first(0);
		head = make_shared<node>(first);
		shared_ptr<node> flag=head;
		shared_ptr<node> pre_line_marker = head;
		for (int m = 0; m < num_rows; m++)
		{
			if (m == 0)
			{
				for (int n = 0; n < num_cols - 1; n++)
				{
					node plus(n + 1);
					flag->east = make_shared<node>(plus);
					flag = flag->east;
				}
			}
			else
			{
				for (int n = 0; n < num_cols; n++)
				{
					node plus(m * num_cols + n);
					flag->east = make_shared<node>(plus);
					flag = flag->east;
					pre_line_marker->south = flag;
					pre_line_marker = pre_line_marker->east;
				}
			}
		}
		shared_ptr<node> last_row_connect_south = head->east;
		for (int i = 0; i < num_cols - 1; i++)
		{
			pre_line_marker->south = last_row_connect_south;
			last_row_connect_south = last_row_connect_south->east;
			pre_line_marker = pre_line_marker->east;
		}
		flag->south = head;
		flag->east = head;
	};
	~ring()//destructor; do as little work as possible
	{
		shared_ptr<node>find = head;
		if (num_cols > 1 && num_rows > 1)
		{
			for (int h = 0; h < num_cols - 2; h++)
			{
				find = find->east;
			}
			for (int m = 0; m < num_rows - 1 ; m++)
			{
				find->east.reset();
				find = find->south;
			}
		}
		head.reset();
	};
	ring(const ring &r) //copy constructor
	{
		shared_ptr<node>P;
		node first(0);
		head = make_shared<node>(first);
		shared_ptr<node> flag = head;
		shared_ptr<node> pre_line_marker = head;
		for (int m = 0; m < r.num_rows; m++)
		{
			if (m == 0)
			{
				for (int n = 0; n < r.num_cols - 1; n++)
				{
					node plus(m * r.num_cols + n + 1);
					flag->east = make_shared<node>(plus);
					flag = flag->east;
				}
			}
			else
			{
				for (int n = 0; n < r.num_cols; n++)
				{
					node plus(m * r.num_cols + n);
					flag->east = make_shared<node>(plus);
					flag = flag->east;
					pre_line_marker->south = flag;
					pre_line_marker = pre_line_marker->east;
				}
			}
		}
		shared_ptr<node> last_row_connect_south = head->east;
		for (int i = 0; i < r.num_cols - 1; i++)
		{
			pre_line_marker->south = last_row_connect_south;
			last_row_connect_south = last_row_connect_south->east;
			pre_line_marker = pre_line_marker->east;
		}
		flag->south = head;
		flag->east = head;
		num_cols = r.num_cols;
		num_rows = r.num_rows;
		P = head;
		shared_ptr<node>Look = r.head;
		for (int i = 0; i < r.num_cols*r.num_rows; i++)
		{
			P->value = Look->value;
			Look = Look->east;
			P = P->east;
		}
	};

	ring(ring &&r) //move constructor
	{
		num_cols = r.num_cols;
		num_rows = r.num_rows;
		head = r.head;
		r.head = nullptr;
		cout << "move" << endl;
	};

	void operator=(ring &&r) //R-value operator=
	{
		head = nullptr;
		num_cols = r.num_cols;
		num_rows = r.num_rows;
		head = r.head;
		r.head = nullptr;
		r.num_cols = 0;
		r.num_rows = 0;
	};

	void operator=(const ring &r) //L-value operator=
	{
		shared_ptr<node>P;
		node first(0);
		head = make_shared<node>(first);
		shared_ptr<node> flag = head;
		shared_ptr<node> pre_line_marker = head;
		for (int m = 0; m < r.num_rows; m++)
		{
			if (m == 0)
			{
				for (int n = 0; n < r.num_cols - 1; n++)
				{
					node plus(m * r.num_cols + n + 1);
					flag->east = make_shared<node>(plus);
					flag = flag->east;
				}
			}
			else
			{
				for (int n = 0; n < r.num_cols; n++)
				{
					node plus(m * r.num_cols + n);
					flag->east = make_shared<node>(plus);
					flag = flag->east;
					pre_line_marker->south = flag;
					pre_line_marker = pre_line_marker->east;
				}
			}
		}
		shared_ptr<node> last_row_connect_south = head->east;
		for (int i = 0; i < r.num_cols - 1; i++)
		{
			pre_line_marker->south = last_row_connect_south;
			last_row_connect_south = last_row_connect_south->east;
			pre_line_marker = pre_line_marker->east;
		}
		flag->south = head;
		flag->east = head;
		num_cols = r.num_cols;
		num_rows = r.num_rows;
		P = head;
		shared_ptr<node>Look = r.head;
		for (int i = 0; i < r.num_cols*r.num_rows; i++)
		{
			P->value = Look->value;
			P = P->east;
			Look = Look->east;
		}
	};

	ring(const initializer_list<int> &V)//see the explanation in main function
	{
		auto it = V.begin();
		num_rows = (*it);
		it++;
		num_cols = (*it);
		it++;
		node first(*it);
		it++;
		head = make_shared<node>(first);
		shared_ptr<node> flag = head;
		shared_ptr<node> pre_line_marker = head;
		for (int m = 0; m < num_rows; m++)
		{
			if (m == 0)
			{
				for (int n = 0; n < num_cols - 1; n++)
				{
					node plus(*it);
					it++;
					flag->east = make_shared<node>(plus);
					flag = flag->east;
				}
			}
			else
			{
				for (int n = 0; n < num_cols; n++)
				{
					node plus(*it);
					it++;
					flag->east = make_shared<node>(plus);
					flag = flag->east;
					pre_line_marker->south = flag;
					pre_line_marker = pre_line_marker->east;
				}
			}
		}
		shared_ptr<node> last_row_connect_south = head->east;
		for (int i = 0; i < num_cols - 1; i++)
		{
			pre_line_marker->south = last_row_connect_south;
			last_row_connect_south = last_row_connect_south->east;
			pre_line_marker = pre_line_marker->east;
		}
		flag->south = head;
		flag->east = head;
	};
	int & operator[](int a);
	int & operator[](pair<int, int> p); //first is row number and second is col number

	void DelCol(int i);//delete col i of *this
	ring Threetimes();
	//return a ring with the same dimenstion as *this, and the value of every node is three times of that of *this.
};

void ring::DelCol(int i)
{
	if (num_cols==1)
	{
		head.reset();
	}
	if (i >= num_cols)
	{
		cout << "Cannot find such columns!" << endl;
		return;
	}
	num_cols--;
	if (i == 0)
	{
		shared_ptr<node> mov = head;
		for (int m = 0; m < num_cols; m++)
		{
			mov = mov->east;
		}
		for (int n = 0; n < num_rows-1; n++)
		{
			mov->east = mov->east->east;
			mov = mov->south;
		}
		head->south.reset();
		head = head->east;
		mov->east = head;
		mov->south = head;
	}
	else if (i == num_cols)
	{
		shared_ptr<node>find = head;
		shared_ptr<node>marker = head;
		for (int h = 0; h < num_cols - 1; h++)
		{
			find = find->east;
		}
		for (int o = 0; o < num_rows; o++)
		{
			marker = marker->south;
			if (o != num_rows - 1)
			{
				find->east.reset();
				find->east = marker;
				find = find->south;
			}
			else
			{
				find->east = head;
				find->south = head;
			}
		}
	}
	else
	{
		shared_ptr<node> find = head;
		for (int k = 0; k < i - 1; k++)
		{
			find = find->east;
		}
		shared_ptr<node>con1, con2;
		for (int j = 0; j < num_rows; j++)
		{
			shared_ptr<node>pre, nex;
			pre = find;
			nex = find->east->east;
			find->east.reset();
			pre->east = nex;
			if (j == 0)
			{
				con2 = nex;
			}
			if (j == num_rows - 1)
			{
				con1 = pre;
			}
			find = find->south;
		}
		con1->south = con2;
	}
}

int &ring::operator[](int a)
{
	shared_ptr<node> p = head;
	for (int i = 0; i < a; i++)
	{
		p = p->east;
	}
	return p->value;
}

int &ring::operator[](pair<int, int> p)
{
	shared_ptr<node> mark = head;
	for (int i=0; i < p.first; i++)
	{
		mark = mark->south;
	}
	for (int j=0; j < p.second; j++)
	{
		mark = mark->east;
	}
	return mark->value;
}

ring ring::Threetimes()
{
	shared_ptr<node> p = head;
	for (int i = 0; i < num_cols*num_rows; i++)
	{
		p->value = p->value * 3;
		p = p->east;
	}
	return *this;
}

//overload operator<<
ostream & operator<<(ostream &output, const ring&R)
{
	cout << "The ring is:"<<endl;
	shared_ptr<node> P = R.head;
	for (int i = 0; i < R.num_rows; i++)
	{
		for (int j = 0; j < R.num_cols; j++)
		{
			cout << P->value << "  ";
			P = P->east;
		}
		cout << endl;
	}
	/*cout << "The head is"<<P->value << endl;
	cout << "The ring is:" << endl;
	for (int i = 0; i < R.num_cols; i++)
	{
		for (int j = 0; j < R.num_rows; j++)
		{
			cout << P->value << "  ";
			P = P->south;
		}
		cout << endl;
	}
	cout << "The head is" << P->value << endl;*/
	return output;
}

int main() {

	ring R1(4, 6);//24 numbers from 0 to 23 will be initialized to nodes.
	cout << R1 << endl;
	R1[14] = 1000;
	R1[{2, 4}] = 2000;
	cout << R1[14] << " " << R1[{2, 4}] << endl;
	R1.DelCol(3);
	cout << R1 << endl;
	R1.DelCol(4);
	cout << R1 << endl;
	R1.DelCol(0);
	cout << R1 << endl;
	shared_ptr<ring> p1 = make_shared<ring>(3, 5);
	cout << *p1 << endl;
	p1.reset();
	ring R2 = { 3, 5, 10,20,30,40,50, 100, 200, 300, 400, 500, 1000, 2000, 3000, 4000, 5000 };
	//first two numbers are num_rows and num_cols; followed by values of nodes of ring
	cout << R2 << endl;
	ring R3(R2);
	cout << R3 << endl;
	ring R4;
	R4 = R3;
	cout << R4 << endl;
	ring R5;
	R5 = R4.Threetimes();
	cout << R5 << endl;


	getchar();
	getchar();
	return 0;
}
