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
public: 

	vector<string> ColumnNames;
private: 



public: 

   // constructors 
	

    Table(int r, int c){
	columns = c;
	rows = r;
    vector< vector<string> > vec2(rows, vector<string>(columns));
	vec=vec2;
    // Write
    vec[0][0] = 10;
    // Read
	}
	void fill();
	void display();
	void display(int rows);
	int getRows(){
	return rows;
	}
	int getColumns(){
	return columns;
	}

	int getColumn(string s);

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

