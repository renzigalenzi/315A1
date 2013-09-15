//=======================================
// CSCE 315-501
// Project 1 - Database Management System
// Edgardo Angel
// Lance Elliot
// Ross Hudgins
//=======================================

#ifndef PARSER_H_ 

#define PARSER_H_


#include <vector>
#include <string>
#include <fstream>
#include "DBMS.h"
using namespace std;

class Parser {
	vector<DBMS> tablevector; //something like this? - yeah, I am not sure quite yet if we should instantiate here or in DBMS with a function call.
	vector<string> keywords;

public:
	Parser() {
		string keyArray[7] = {"CREATE","INSERT","VARCHAR","INTEGER","VALUES","RELATION","SHOW"};
		keywords.assign(keyArray, keyArray+7);
	}
	vector<string> readfromfile(string filename); //each element is a line, delimited by ';'
	void execute(string s);
	void callFunction(int j, int position, vector<string> words);
	int getTable(string name);
};


#endif