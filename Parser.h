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
	vector<string> columnnames;
	bool twoTables;

public:
	Parser() {
		string keyArray[15] = {"CREATE","INSERT","VARCHAR","INTEGER","VALUES","RELATION","SHOW","<-","select","project","rename","WRITE","CLOSE","EXIT", "OPEN"};// dont forget to change size after adding anything
		keywords.assign(keyArray, keyArray+15);// change this size too
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
	void rename(vector<string> words, int position, DBMS vec);
	bool valid(int length,vector<string> words, int position);
	int StringToNumber( const string &Text );
	vector<string> replaceWords(vector<string> words,int begin, int end,string replacement);
	void copy(DBMS vec1,DBMS vec2);
	void combineTables(vector<string> words, int position);

	void Equals(vector<string> expression, int i);
	void NotEquals(vector<string> expression, int i);
	void doubleExpression(vector<string> expression, int i,int first, int second);

	int getcsize(string tname);
};


#endif