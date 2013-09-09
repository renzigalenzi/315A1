//=======================================
// CSCE 315-501
// Project 1 - Database Management System
// Edgardo Angel
// Lance Elliot
// Ross Hudgins
//=======================================

#ifndef TABLE_H_ 

#define TABLE_H_

#include <vector>
#include <string>
#include <iostream> 



using namespace std;

class Table { 
	int rows; 
	int columns;
	vector< vector<string> > vec;
	string title;
public: 

	vector<string> ColumnNames;
private: 



public: 

   // constructors 
	
	Table(vector< vector<string> > vec2){
	vec=vec2;
	title = "default";
	}
	Table(vector< vector<string> > vec2,string title2){
	vec=vec2;
	title = title2;
	}
    Table(int r, int c){
	columns = c;
	rows = r;
    vector< vector<string> > vec2(rows, vector<string>(columns));
	vec=vec2;
	title = "default";
	}
	Table(int r, int c,string title2){
	columns = c;
	rows = r;
    vector< vector<string> > vec2(rows, vector<string>(columns));
	vec=vec2;
	title = title2;
	}
	void fill();
	void display();
	void deleteRow(int n);
	void deleteColumn(int n);
	void display(int rows);
	int getRows(){
	return rows;
	}
	int getColumns(){
	return columns;
	}
	void setTitle(string n){
	title = n;
	}
	string getTitle(){
	return title;
	}

	int getColumn(string s);
	vector<vector<string> > getTable()
	{
    return vec;
	}
	vector<vector<string> > setunion(vector<vector<string> > vec2);
	vector<vector<string> > crossproduct(vector<vector<string> > vec2);
	void setColumnName(int number, string name){
	vec[0][number]=name;
	}
	void changeValue(int row, int column, string name){
	if (row>=0&&column>=0)
	vec[row][column]=name;
	}
	
	void show(string Colname, string comparitor);
	void add(){
	vec.push_back(vector<string>(columns));
	}
	int getLastRow(){
		return vec.size()-1;
	}
  

};




// helper functions

     
bool operator==(const Table& m1, const Table& m2); 

std::ostream& operator<<(ostream& os, const Table& m);


std::istream& operator>>(istream& is, Table& m);




#endif // end of the file Table.h  

