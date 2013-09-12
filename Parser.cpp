//=======================================
// CSCE 315-501
// Project 1 - Database Management System
// Edgardo Angel
// Lance Elliot
// Ross Hudgins
//=======================================

#include "DBMS.h"
#include "Parser.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>


using namespace std;


//the .db file has to be in the project directory
vector<string> Parser::readfromfile(string tablename) {
	string temp;
	vector<string> toReturn;
	string filename = tablename + ".db";
	//cout << "filename is:" << filename << endl;
	ifstream file;
	file.open(filename.c_str());
	if (file.is_open()) {
		while (!file.eof()){
			getline(file, temp);
			cout << "temp = " << temp << endl;
			toReturn.push_back(temp);
		}
	}
	else cout << "it's not open" << endl;
	file.close();
	return toReturn;
}



