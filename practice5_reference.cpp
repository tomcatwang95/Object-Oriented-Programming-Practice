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
		num_cols = j;
		num_rows = i;
		if (num_cols == 0 || num_rows == 0)
		{
			ring();
		}
		node first(0);
		head = make_shared<node>(first);
		shared_ptr<node> line_end;
		shared_ptr<node> pre_line_begin;
		shared_ptr<node> south_marker;
		for (int m = 0; m < num_rows; m++)
		{
			if (m == 0)
			{
				shared_ptr<node> flag = head;
				for (int k = 0; k < num_cols-1; k++)
				{
					node plus(k+1);
					flag->east = make_shared<node>(plus);
					flag = flag->east;
				}
				line_end = flag;
				if (num_rows == 1)
				{
					flag->east = head;
					shared_ptr<node>M = head;
					for (int k = 0; k < num_cols; k++)
					{
						M->south = M->east;
						if (k != num_cols - 1)
						{
							M = M->east;
						}
					}
					M->south = head;
					
				}
			}
			else
			{
				node add;
				shared_ptr<node> connect = head;
				if (m==1)
				{
					south_marker = head;
				}
				else
				{
					south_marker = pre_line_begin;
				}
				shared_ptr<node> flag = line_end;
				for (int n = 0; n < num_cols; n++)
				{
					node plus(m*num_cols + n);
					flag->east = make_shared<node>(plus);
					flag = flag->east;
					if (n == 0)
					{
						pre_line_begin = flag;
					}
					south_marker->south = flag;
					if (n < num_cols - 1)
					{
						south_marker = south_marker->east;
					}
					line_end = flag;
					if (m == num_rows - 1 && n < num_cols - 1)
					{
						connect = connect->east;
						flag->south = connect;
					}
				}
				if (m == num_rows - 1)
				{
					flag->east= head;
					flag->south = head;
				}
			}
		}
	};
	~ring()//destructor; do as little work as possible
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
		head.reset();
	};
	ring(const ring &r) //copy constructor
	{
		shared_ptr<node> P;
		for (int i = 0; i < r.num_cols*r.num_rows; i++)
		{
			P = make_shared<node>();
			P->east = head;
			head = P;
		}
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

	ring(ring &&r) //move constructor
	{
		num_cols = r.num_cols;
		num_rows = r.num_rows;
		head = r.head;
		r.head = nullptr;
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
		head = nullptr;
		num_cols = 0;
		num_rows = 0;
		for (int i = 0; i < r.num_cols*r.num_rows; i++)
		{
			P = make_shared<node>();
			P->east = head;
			head = P;
		}
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
		/*ring(num_rows, num_cols);
		auto fill = V.end() -1;
		while (fill != V.begin() + 1)
		{
			shared_ptr<node> p1 = make_shared<node>(*fill);
			p1->east = head;
			head = p1;
			fill--;
		}*/
		node first(*it);
		it++;
		head = make_shared<node>(first);
		shared_ptr<node> line_end;
		shared_ptr<node> pre_line_begin;
		shared_ptr<node> south_marker;
		for (int m = 0; m < num_rows; m++)
		{
			if (m == 0)
			{
				shared_ptr<node> flag = head;
				for (int k = 0; k < num_cols - 1; k++)
				{
					node plus(*it);
					flag->east = make_shared<node>(plus);
					flag = flag->east;
					it++;
				}
				line_end = flag;
				if (num_rows == 1)
				{
					flag->east = head;
					shared_ptr<node>M = head;
					for (int k = 0; k < num_cols; k++)
					{
						M->south = M->east;
						if (k != num_cols - 1)
						{
							M = M->east;
						}
					}
					M->south = head;
				}
			}
			else
			{
				node add;
				shared_ptr<node> connect = head;
				if (m == 1)
				{
					south_marker = head;
				}
				else
				{
					south_marker = pre_line_begin;
				}
				shared_ptr<node> flag = line_end;
				for (int n = 0; n < num_cols; n++)
				{
					node plus(*it);
					it++;
					flag->east = make_shared<node>(plus);
					flag = flag->east;
					if (n == 0)
					{
						pre_line_begin = flag;
					}
					south_marker->south = flag;
					if (n < num_cols - 1)
					{
						south_marker = south_marker->east;
					}
					line_end = flag;
					if (m == num_rows - 1 && n < num_cols - 1)
					{
						connect = connect->east;
						flag->south = connect;
					}
				}
				if (m == num_rows - 1)
				{
					flag->east = head;
					flag->south = head;
				}
			}
		}
	};
	int & operator[](int a);
	int & operator[](pair<int, int> p); //first is row number and second is col number

	void DelCol(int i);//delete col i of *this
	ring Threetimes();
	//return a ring with the same dimenstion as *this, and the value of every node is three times of that of *this.
};

void ring::DelCol(int i)
{
	num_cols--;
	if (i > num_cols)
	{
		cout << "Cannot find such columns!" << endl;
	}
	else
	{
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
			shared_ptr<node>find=head;
			shared_ptr<node>marker = head;
			for (int h = 0; h < num_cols-1; h++)
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
			shared_ptr<node> find=head;
			for (int k = 0; k < i-2; k++)
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
			(*con1).south.reset();
			con1->south = con2;
		}
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
	/*for (int i = 0; i < R.num_cols; i++)
	{
		for (int j = 0; j < R.num_rows; j++)
		{
			cout << P->value << "  ";
			P = P->south;
		}
		cout << endl;
	}*/
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
