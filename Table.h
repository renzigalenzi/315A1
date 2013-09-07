
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
	

    Table(int c, int r){
	columns = c;
	rows = r;
    vector< vector<string> > vec2(columns, vector<string>(rows));
	vec=vec2;
    // Write
    vec[0][0] = 10;
    // Read
	}
	void fill(int columns, int rows);
	void display(int columns, int rows);
	void display(int rows);
	int getRows(){
	return rows;
	}
	int getColumns(){
	return columns;
	}
	void setColumnName(int number, string name){
	vec[0][number]=name;
	}
	void show(string Colname, string comparitor);
   
  

};




// helper functions

     
bool operator==(const Table& m1, const Table& m2); 

std::ostream& operator<<(ostream& os, const Table& m);


std::istream& operator>>(istream& is, Table& m);




#endif // end of the file Table.h  

