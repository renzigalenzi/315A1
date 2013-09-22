//=======================================
// CSCE 315-501
// Project 1 - Database Management System
// Edgardo Angel
// Lance Elliot
// Ross Hudgins
//=======================================

#ifndef DBMS_H_ 

#define DBMS_H_

#include <vector>
#include <string>
#include <iostream> 



using namespace std;

class DBMS { 
	int rows; 
	int columns;
	vector< vector<string> > vec;
	string title;
public: 
	vector<string> ColumnNames; //not used anywhere?

   // constructors 
	
	DBMS(vector< vector<string> > vec2){
		columns = vec2.size();
		rows = vec2[0].size();
		vec=vec2;
		title = "default";
	}
	DBMS(vector< vector<string> > vec2,string title2){
		columns = vec2.size();
		rows = vec2[0].size();
		vec=vec2;
		title = title2;
	}
    DBMS(int r, int c){
		columns = c;
		rows = r;
		vector< vector<string> > vec2(rows, vector<string>(columns));
		vec=vec2;
		title = "default";
	}
	DBMS(int r, int c,string title2){
		columns = c;
		rows = r;
		vector< vector<string> > vec2(rows, vector<string>(columns));
		vec=vec2;
		title = title2;
	}

	//Functions
	void fill();
	void display();
	void deleteAttr(int attribute,string comparitor);
	void deleteRow(int n);
	void deleteColumn(int n);
	void display(int rows);
	int getRows(){
		return vec.size();
	}
	int getColumns(){
		return vec[0].size();
	}
	void setTitle(string n){
		title = n;
	}
	string getTitle(){
		return title;
	}

	int getColumn(string s);
	string getElement(int x, int y);
	vector<vector<string> > getDBMS() {
		return vec;
	}
	vector<vector<string> > setunion(vector<vector<string> > vec2);
	vector<vector<string> > setdifference(vector<vector<string> > vec2);
	vector<vector<string> > crossproduct(vector<vector<string> > vec2); // DBMSs must have rows <= columns
	void setColumnName(int number, string name){
		vec[0][number]=name;
	}
	void changeValue(int row, int column, string name){
		if (row>=0&&column>=0&&vec.size()>row&&vec[0].size()>column)
		vec[row][column]=name;
	}
	
	void show(string Colname, string comparitor);
	void clear();
	void add(){
		vec.push_back(vector<string>(columns));
	}
	int getLastRow(){
		return vec.size()-1;
	}
	void writeToFile();

};

//Overloading 
bool operator==(const DBMS& m1, const DBMS& m2); 

std::ostream& operator<<(ostream& os, const DBMS& m);


std::istream& operator>>(istream& is, DBMS& m);


#endif // end of the file DBMS.h  

