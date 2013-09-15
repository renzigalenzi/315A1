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
		  //cout<< words[counter]<< " ";
      }
	  else if (s[i]==')' || s[i]=='(' || s[i]==',')
		{
			if (temp.size()>0)
			{
				counter ++;
				words.push_back(temp);
				//cout<< words[counter]<< " ";
			}
			temp = s[i];
			words.push_back(temp);
			counter ++;
			//cout<< words[counter]<< " ";
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
				//cout<<"\nkeyword found! - "<<keywords[j]<<"\n";
				callFunction(j, i, words);// call function dothis(keyword[j], i//-we will need the words that follow the keyword so keeping position is important)
			}
		}
	}
}

void Parser::callFunction(int keyword, int position, vector<string> words)
{	
	int tablecolumns = 0;
	int columnCounter = 0;
	switch(keyword)
	{
	case 0: cout << "I am creating a table called "<<words[position+2]<< "\n";
			
			if (words[position+3]=="(")
				cout<< "setting Columns to - \n";
				cout<< "Column "<<columnCounter<<" = "<<words[position+4]<<"\n";
			for (int i = position+2; i<words.size(); i++)
			{
				if (words[i]=="PRIMARY")
				{
					break;
				}
				if (words[i]==",")
				{
					columnCounter++;
					cout<< "Column "<<columnCounter<<" = "<<words[i+2]<<"\n";
				}
			}

		break;
	case 1: cout << "Inserting element into table "<<words[position+2]<<"\n";
		break;
	case 2: cout << "char value with "<<words[position+2]<<" characters will be possible in items within table.getColumn("<<words[position-1]<<")\n";
		break;
	case 3: cout << "int value at table.getColumn("<<words[position-1]<<")\n";
		break;
	case 4:	if (words[position+2]=="RELATION")
		/**/		break;
			columnCounter=0;
			cout<< "Setting attribute "<<columnCounter<<" to "<<words[position+3]<<"\n";
			for (int i = position+2; i<words.size(); i++)
			{
				if (words[i]==",")
				{	
					columnCounter++;
					cout<< "Setting attribute "<<columnCounter<<" to "<<words[i+2]<<"\n";
					
				}
			} 
		break;
	case 5: cout << "that something is from something else :D\n";
		break;
	case 6: cout << "show me your stuff :D\n";
		break;
	default: cout << "how did that happen?\n";
		break;
	}
}


