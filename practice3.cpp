#include "pch.h"
#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

class course {
public:
	string name;
	int section;
	int credits;
	course() {}
	course(string n, int s, int c) { name = n; section = s; credits = c; }
	friend ostream & operator<<(ostream &output, const course &C)
	{
		output << C.name << "  " << C.section << "  " << C.credits;
		return output;
	}
	bool operator==(course c) const
	{
		return (this->name == c.name);
	}
	void operator=(course c)
	{
		this->name = c.name;
		this->section = c.section;
		this->credits = c.credits;
	}
};

void add_student(map<int, map<int, list<course *> * > *> &DB, int id);
void remove_student(map<int, map<int, list<course *> * > *> &DB, int id);
void add_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c); 
void drop_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c);
void print_student_semester_courses(map<int, map<int, list<course *> * > *> &DB, int semester, int id);
void print_student_all_courses(map<int, map<int, list<course *> * > *> &DB, int id);
void print_DB(map<int, map<int, list<course *> * > *> &DB);

int main() {
	//Do not change code for main function
	map<int, map<int, list <course *> *> *> DB;
	add_student(DB, 11111);
	course C1("CIS554", 1, 3), C2("CSE674", 1, 3), C3("MAT296", 8, 4), C4("WRT205", 5, 3);


	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111);

	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111);

	add_course(DB, 20172, 11111, C2);
	add_course(DB, 20172, 11111, C4);
	add_course(DB, 20172, 11111, C3);
	add_course(DB, 20172, 11111, C1);
	print_student_all_courses(DB, 11111);

	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C4);
	add_course(DB, 20171, 11112, C3);
	add_course(DB, 20171, 11112, C1);
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C2);
	add_course(DB, 20172, 11112, C4);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);
	print_student_all_courses(DB, 11112);
	print_DB(DB);
	remove_student(DB, 11111);
	print_DB(DB);
	getchar();
	getchar();
	return 0;
}

void add_student(map<int, map<int, list<course *> * > *> &DB, int id)
{
	if (DB.find(id) != DB.end())
	{
		return;
	}
	map<int, list<course *> * >*N = new map<int, list<course *> * >;
	DB[id] = N;
}

void remove_student(map<int, map<int, list<course *> * > *> &DB, int id)
{
	if (DB.find(id) == DB.end())
	{
		return;
	}
	map<int, map<int, list<course *> * > *> ::iterator it1 = DB.find(id);
	if (it1->second == nullptr)
	{
		DB.erase(id);
		return;
	}
	map<int, list<course *> * >::iterator it2;
	list<course *>::iterator it3;
	for (it2 = it1->second->begin(); it2 != it1->second->end(); it2++)
	{
		if (it2->second != nullptr)
		{
			for (it3 = it2->second->begin(); it3 != it2->second->end(); it3++)
			{
				delete *it3;
			}
			it2->second->clear();
			delete it2->second;
		}
	}
	it1->second->clear();
	delete it1->second;
	DB.erase(id);
}
void add_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c)
{
	if (DB.find(id) == DB.end())
	{
		return;
	}
	map<int, map<int, list<course *> * > *> ::iterator it1 = DB.find(id);
	if (it1->second == nullptr)
	{
		map<int, list<course *> * >*S = new map<int, list<course *> * >;
		(DB[id])[semester] = *S;
	}
	if (it1->second->find(semester) == it1->second->end())
	{
		list<course*>*L = new list<course*>;
		it1->second->insert_or_assign(semester, L);
	}
	map<int, list<course *> * >::iterator it2 = it1->second->find(semester);
	list<course *>::iterator it3;
	if (it2->second->size() != 0)
	{
		for (it3 = it2->second->begin(); it3 != it2->second->end(); it3++)
		{
			if (**it3 == c)
			{
				return;
			}
		}
	}
	it2->second->push_back(new course(c));
}

void drop_course(map<int, map<int, list<course *> * > *> &DB, int semester, int id, course c)
{
	if (DB.find(id) == DB.end())
	{
		return;
	}
	map<int, map<int, list<course *> * > *> ::iterator it1 = DB.find(id);
	if (it1->second == nullptr)
	{
		return;
	}
	if (it1->second->find(semester) == it1->second->end())
	{
		return;
	}
	map<int, list<course *> * >::iterator it2 = it1->second->find(semester);

	for (list<course *>::iterator it3 = it2->second->begin(); it3 != it2->second->end(); it3++)
	{
		if (**it3 == c)
		{
			delete *it3;
			it2->second->erase(it3);
			break;
		}
	}
}

void print_student_semester_courses(map<int, map<int, list<course *> * > *> &DB, int semester, int id)
{
	if (DB.size() == 0)
	{
		return;
	}
	if (DB.find(id) == DB.end())
	{
		return;
	}
	map<int, map<int, list<course *> * > *> ::iterator it1 = DB.find(id);
	map<int, list<course *> * >::iterator it2 = it1->second->find(semester);
	if (it2 == it1->second->end())
	{
		return;
	}
	cout << "Student ID = " << id << endl;
	cout << "Semester = " << semester << endl;
	for (list<course *>::iterator it3 = it2->second->begin(); it3 != it2->second->end(); it3++)
	{
		cout << **it3;
	}
	cout << endl;
	cout << endl;
}
void print_student_all_courses(map<int, map<int, list<course *> * > *> &DB, int id)
{
	if (DB.size() == 0)
	{
		return;
	}
	if (DB.find(id) == DB.end())
	{
		return;
	}
	map<int, map<int, list<course *> * > *> ::iterator it1 = DB.find(id);
	cout << "Student ID = " << id << endl;
	for (map<int, list<course *> * >::iterator it2 = it1->second->begin(); it2 != it1->second->end(); it2++)
	{
		cout << "Semester = " << it2->first << endl;
		for (list<course *>::iterator it3 = it2->second->begin(); it3 != it2->second->end(); it3++)
		{
			cout << **it3;
		}
		cout << endl;
	}
	cout << endl;
}

void print_DB(map<int, map<int, list<course *> * > *> &DB)
{
	if (DB.size() == 0)
	{
		return;
	}
	map<int, map<int, list<course *> * > *> ::iterator it1 = DB.begin();
	while (it1 != DB.end())
	{
		cout << "student id = " << it1->first << endl;
		for (map<int, list<course *> * >::iterator it2 = it1->second->begin(); it2 != it1->second->end(); it2++)
		{
			cout << "semester = " << it2->first << endl;
			for (list<course *>::iterator it3 = it2->second->begin(); it3 != it2->second->end(); it3++)
			{
				if (it2->second->size() != 0)
				{
					cout << **it3;
				}
			}
			cout << endl;
		}
		it1++;
	}
	cout << endl;
}
