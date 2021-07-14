#include <iostream>
#include <list>
#include <vector>
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
	bool operator<(course c) { return (name < c.name); }
	bool operator==(course c) { return (name == c.name); }
};
//Implement the following function
//Please note that when visiting elements of vector, similar to HW2, you are required to use index (i.e., []) rather than using iterators.

void add_student(map<int, map<int, vector<course *> * > > &DB, int id);
void remove_student(map<int, map<int, vector<course *> * > > &DB, int id);
void add_course(map<int, map<int, vector<course *> * > > &DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017

void drop_course(map<int, map<int, vector<course *> * >> &DB, int semester, int id, course c);
void print_student_semester_courses(map<int, map<int, vector<course *> * >> &DB, int semester, int id);
void print_student_all_courses(map<int, map<int, vector<course *> * > > &DB, int id);
void print_DB(map<int, map<int, vector<course *> * > > &DB);


int main() {
	//Do not change code for main function
	map<int, map<int, vector<course *> *> > DB;
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

	//print_student_semester_courses(DB, 20172, 11111);
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

void add_student(map<int, map<int, vector<course *> * > > &DB, int id) {
	auto it1 = DB.find(id);
	if (it1 != DB.end()) {//map empty what's the DB.end()? meipanduan!
		return;
	}
	map< int, vector<course*>* > DB1;
	DB[id] = DB1;


}

void remove_student(map<int, map<int, vector<course *> * > > &DB, int id) {
	auto it1 = DB.find(id);
	if (it1 == DB.end()) { return; }

	auto it2 = DB[id].begin();
	while (it2 != DB[id].end()) {
		for (size_t i = 0; i < (*((*it2).second)).size(); i++) {
			course *p = (*((*it2).second))[i];// *((*((*it2).second))[i])
			delete p;
		}
		(*((*it2).second)).clear();
		//auto it3 = (*it2).second;
		//delete it3;
		//(*((*it2).second)).erase((*((*it2).second)).begin(), (*((*it2).second)).end());//vector erase
		it2++;
	}
	//DB[id].erase(DB[id].begin(), DB[id].end());// DB[id ]erase;
	DB.erase(id);//DB erase;




}


void add_course(map<int, map<int, vector<course *> * > > &DB, int semester, int id, course c) {
	auto it1 = DB.find(id);
	int j = 0;
	if (it1 == DB.end()) { return; }

	auto it2 = DB[id].find(semester);
	if (it2 != DB[id].end()) {
		//if panduan course shi fou yijing zai vector li meipanduan !
		for (size_t i = 0; i < (*(DB[id][semester])).size(); i++) {

			if (*((*(DB[id][semester]))[i]) == c) {
				j++;
			}
			if (j != 0) { return; }
		}



		course *p = new course(c);//ok?intialize?
		(*(DB[id][semester])).push_back(p);
	}

	else {
		vector<course *> * V = new vector<course *>;
		course *p = new course(c);
		(*V).push_back(p);
		DB[id][semester] = V;

	}


}

void drop_course(map<int, map<int, vector<course *> * > > &DB, int semester, int id, course c) {
	auto it1 = DB.find(id);
	int j = 0;
	if (it1 == DB.end()) { return; }
	auto it2 = DB[id].find(semester);
	if (it2 == DB[id].end()) { return; }

	for (size_t i = 0; i < (*(DB[id][semester])).size(); i++) {

		if (*((*(DB[id][semester]))[i]) == c) {
			course *p = (*(DB[id][semester]))[i];
			delete p;
			(*(DB[id][semester])).erase((*(DB[id][semester])).begin() + i);
			return;


		}
	}

	/*(if ((*(DB[id][semester])).begin() == (*(DB[id][semester])).end()) {
		DB[id].erase(semester);
	}*/

	//how to find c?

}

void print_student_semester_courses(map<int, map<int, vector<course *> * > > &DB, int semester, int id) {
	auto it1 = DB.find(id);
	cout << endl;
	if (it1 == DB.end()) { return; }
	cout << "student id = " << id << endl;
	auto it2 = DB[id].find(semester);
	if (it2 == DB[id].end()) { return; }
	cout << "semester = " << semester << endl;
	for (size_t i = 0; i < (*(DB[id][semester])).size(); i++) {
		cout << (*((*(DB[id][semester]))[i])).name << " ";
		cout << (*((*(DB[id][semester]))[i])).section << " ";
		cout << (*((*(DB[id][semester]))[i])).credits << "  ";
	}
	cout << endl;


}
void print_student_all_courses(map<int, map<int, vector<course *> * > > &DB, int id) {

	auto it1 = DB.find(id);
	if (it1 == DB.end()) { return; }

	cout << endl;

	cout << "student id = " << id << endl;
	auto it2 = DB[id].begin();
	while (it2 != DB[id].end()) {
		cout << "semester = " << (*it2).first << endl;
		//*((*it2).second)
		for (size_t i = 0; i < (*((*it2).second)).size(); i++) {//haishi zhijie bu panduan semester ,yong iterator shuchu?
			cout << (*((*((*it2).second))[i])).name << " ";
			cout << (*((*((*it2).second))[i])).section << " ";
			cout << (*((*((*it2).second))[i])).credits << " ";
		}
		cout << endl;

		it2++;

	}
	//cout << endl;
	/*auto it2 = DB[id].find(20171);
	if (it2 != DB[id].end()) {
		cout << "semester = " << 20171 << endl;
		for (size_t i = 0; i<(*(DB[id][20171])).size(); i++) {//haishi zhijie bu panduan semester ,yong iterator shuchu?
			cout << (*((*(DB[id][20171]))[i])).name << " ";
			cout << (*((*(DB[id][20171]))[i])).section << " ";
			cout << (*((*(DB[id][20171]))[i])).credits << "  ";
		}
		cout << endl;
	}
	auto it3 = DB[id].find(20172);
	if (it3 != DB[id].end()) {
		cout << "semester = " << 20172 << endl;
		for (size_t i = 0; i<(*(DB[id][20172])).size(); i++) {//haishi zhijie bu panduan iterator shuchu?
			cout << (*((*(DB[id][20172]))[i])).name << " ";
			cout << (*((*(DB[id][20172]))[i])).section << " ";
			cout << (*((*(DB[id][20172]))[i])).credits << "  ";
		}
		cout << endl;
	}
	*/

}

void print_DB(map<int, map<int, vector<course *> * > > &DB) {

	auto it1 = DB.begin();
	cout << endl;
	while (it1 != DB.end()) {
		//cout << endl;
		cout << "student id = " << (*it1).first << endl;
		auto it2 = ((*it1).second).begin();
		// << endl;
		while (it2 != ((*it1).second).end()) {
			cout << "semester = " << (*it2).first << endl;
			for (size_t i = 0; i < (*((*it2).second)).size(); i++) {
				cout << (*((*((*it2).second))[i])).name << " ";
				cout << (*((*((*it2).second))[i])).section << " ";
				cout << (*((*((*it2).second))[i])).credits << "  ";
			}
			cout << endl;
			it2++;
		}


		it1++;
	}

}
/*
//Sample Screenshot
student id = 11111
semester = 20171
CIS554 1 3  WRT205 5 3  MAT296 8 4  CSE674 1 3

student id = 11111
semester = 20171
WRT205 5 3  MAT296 8 4  CSE674 1 3

student id = 11111
semester = 20171
WRT205 5 3  MAT296 8 4  CSE674 1 3
semester = 20172
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3

student id = 11112
semester = 20171
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3

student id = 11112
semester = 20172
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3

student id = 11112
semester = 20171
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
semester = 20172
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3

student id = 11111
semester = 20171
WRT205 5 3  MAT296 8 4  CSE674 1 3
semester = 20172
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
student id = 11112
semester = 20171
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
semester = 20172
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3

student id = 11112
semester = 20171
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
semester = 20172
CSE674 1 3  WRT205 5 3  MAT296 8 4  CIS554 1 3
*/
