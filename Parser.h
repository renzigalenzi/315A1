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
	vector<DBMS> tablevector; //something like this?

public:
	Parser() {}
	
	vector<string> readfromfile(string filename); //each element is a line, delimited by ';'

};


#endif