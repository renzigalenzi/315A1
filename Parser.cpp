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
			getline(file, temp/*, ';'*/);
			//cout << "temp = " << temp << endl;
			toReturn.push_back(temp);
		}
	}
	else cout << "it's not open" << endl;
	file.close();
	return toReturn;
}

void Parser::execute(string s){
	vector<string> words;
	string temp = "";
	int counter = -1;
	//cout<<s.size();
	for(int i = 0; i<s.size(); i++)
	{		
      if(isspace(s[i])||s[i]==';')
      {
          counter ++;
		  words.push_back(temp);
		  temp = "";
		  cout<< words[counter]<< " ";
      }
	  else if (s[i]==')' || s[i]=='(' || s[i]==',')
		{
			if (temp.size()>0)
			{
				counter ++;
				words.push_back(temp);
				cout<< words[counter]<< " ";
			}
			temp = s[i];
			words.push_back(temp);
			counter ++;
			cout<< words[counter]<< " ";
			temp = "";
		}
	  else
		  temp += s[i];
	  
	}
	for (int i = 0; i< words.size(); i++)
	{
		for (int j = 0; j< keywords.size(); j++)
		{
			if (words[i] == keywords[j])
			{
				cout<<"\nkeyword found! - "<<keywords[j]<<"\n";
				// call function dothis(keyword, i//-we will need the words that follow the keyword so keeping position is important)
			}
		}
	}



}



