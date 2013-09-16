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
	vector<DBMS> tempvector;


public:
	Parser() {
		string keyArray[14] = {"CREATE","INSERT","VARCHAR","INTEGER","VALUES","RELATION","SHOW","<-","select","project","rename","WRITE","CLOSE","EXIT"};// dont forget to change size after adding anything
		keywords.assign(keyArray, keyArray+14);// change this size too
	}
	vector<string> readfromfile(string filename); //each element is a line, delimited by ';'
	void execute(string s);
	void callFunction(int j, int position, vector<string> words);
	int getTable(string name);
	bool isname(string name);
	string getNextKeyword(vector<string> words, int position);
	int getKeywordPosition(vector<string> words, string keyword);
	int getKeyNum(string keyword);
	string getElementString(vector<string> words, int position, int elementNumber);
	string solveElementString(vector<string> words, int position, int elementNumber);
	bool valid(int length,vector<string> words, int position);
};


#endif