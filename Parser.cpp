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
#include <sstream>


using namespace std;


//the .db file has to be in the project directory

vector<string> Parser::readfromfile(string tablename) {
	string temp;
	vector<string> toReturn;
	string filename = tablename + ".db";
	ifstream file;
	file.open(filename.c_str());
	if (file.is_open()) {
		while (!file.eof()){
			getline(file, temp/*, ';'*/);
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
	int keywordsFound=0;
	//cout<<s.size()<<"\n";
	if (s.size()>=1&&*s.rbegin()!=';')// line doesnt end with a ;
	{
    cout<<"ERROR: not a valid line, please use a ; so signal the end of a statement\n";
	return;
	}
	for(int i = 0; i<s.size(); i++)// find all ; and spaces and doesnt count them as words.
	{		
      if(isspace(s[i])||s[i]==';')
      {
          counter ++;
		  words.push_back(temp);
		  temp = "";
		  //cout<< words[counter]<< " ";
      }
	  else if (s[i]==')' || s[i]=='(' || s[i]==',') // ends a word if one of these symbols comes up
		{
			if (temp.size()>0)
			{
				counter ++;
				words.push_back(temp);
				//cout<< words[counter]<< " ";
			}
			temp = s[i];                          //proceeds to then add the symbol by itself as a word.
			words.push_back(temp);
			counter ++;
			//cout<< words[counter]<< " ";
			temp = "";
		}
	  else
		  temp += s[i]; // add any words to the sentence
	  
	}
	for (int i = 0; i< words.size(); i++) // go through all the words and find any keywords. then execute them.
	{
		for (int j = 0; j< keywords.size(); j++)
		{
			if (words[i] == keywords[j])
			{
				keywordsFound++;//cout<<"\nkeyword found! - "<<keywords[j]<<"\n";
				callFunction(j, i, words);// call function dothis(keyword[j], i//-we will need the words that follow the keyword so keeping position is important)
			}
		}
	}
	if (keywordsFound==0&&s.size()>0)
		cout<<"Not a valid line.\n";
}

void Parser::callFunction(int keyword, int position, vector<string> words)
{	
	int tablecolumns = 0;
	int columnCounter = 0;
	string tablename;
	string tablename2;
	bool isStatement=true;
	string column;
	int tempposition;
	vector<string> tempkeyword;
	int validity;

	//     starting with case 0: -  "CREATE","INSERT","VARCHAR","INTEGER","VALUES","RELATION","SHOW","<-","select","project","rename"
	switch(keyword)
	{
	case 0: 
		validity = 4;
		if (!valid(validity,words,position)) // if there isnt enough information provided, the create will not work.
		{
		cout<< "ERROR: not a valid statement, needs 2 arguments with parenthesis\n";
		break;
		}
		cout << "I am creating a table called "<<words[position+2]<< "\n"; // all of this is just to visualize what is going on, the work is done later
			tablename = words[position+2];
			if (words[position+3]=="(")
				cout<< "setting Columns to - \n";
			else
			{
				cout<<"ERROR: not a valid statement\n";
				break;
			}
				cout<< "Column "<<columnCounter<<" = "<<words[position+4]<<"\n";
				columnnames.push_back(words[position+4]);
			for (int i = position+2; i<words.size(); i++) // continue to intake column headers until there is a stopping point.
			{
				if (words[i]=="PRIMARY")
				{
					break;
				}
				if (words[i]==",")
				{
					columnCounter++;
					cout<< "Column "<<columnCounter<<" = "<<words[i+2]<<"\n";
					columnnames.push_back(words[i+2]);
				}
			}
		tablevector.push_back(DBMS(1,columnCounter+1,tablename)); // here is where the table is created and edited. 
		for (int i = 0; i <columnCounter+1; i++)
		{
			tablevector[getTable(tablename)].setColumnName(i,columnnames[i]);
		}
		//tablevector[getTable(tablename)].display();
		columnnames.clear();
		break;
	case 1:																// INSERT, make sure there is enough information for it, then execute.
		validity = 2;
		if (!valid(validity,words,position))
		{
		cout<< "ERROR: not a valid statement, needs 2 arguments with parenthesis\n";
		break;
		}

		cout << "\nInserting element into table "<<words[position+2]<<"\n";
		if (!isname(words[position+2]))
		{
			cout<<tablename<<" - ERROR: is not a created table at the moment.\n";
			break;
		}
		tablevector[getTable(words[position+2])].add();
		break;
	case 2:																		// VARCHAR, make sure there is enough information for it (really just for show).
		validity = 2;
		if (!valid(validity,words,position))
		{
		cout<< "ERROR: not a valid statement, needs 1 argument \"tablename\"\n";
		break;
		}
		
		cout << "char value with "<<words[position+2]<<" characters will be possible in items within table.getColumn("<<words[position-1]<<")\n";
		break;
	case 3:																	// INTEGER, make sure there is enough information for it (really just for show).

		cout << "int value at table.getColumn("<<words[position-1]<<")\n";
		break;
	case 4:																		// VALUES, make sure there is enough information for it, then apply values according to order.
		validity = 3;
		if (!valid(validity,words,position))
		{
		cout<< "ERROR: not a valid statement, needs at least one value to add\n";
		break;
		}
		
		if (words[position+2]=="RELATION")
		/**/		break;
			columnCounter=0;
			cout<< "\nSetting attribute "<<columnCounter<<" to "<<words[position+3]<<"\n";
			tablevector[getTable(words[position-1])].changeValue(tablevector[getTable(words[position-1])].getLastRow(),columnCounter,words[position+3]); //apply the first column info
			for (int i = position+2; i<words.size(); i++)
			{
				if (words[i]==",")// if there are any more columns to add, then add them
				{		
					columnCounter++;
					cout<< "Setting attribute "<<columnCounter<<" to "<<words[i+2]<<"\n";
					tablevector[getTable(words[position-1])].changeValue(tablevector[getTable(words[position-1])].getLastRow(),columnCounter,words[i+2]);
					
				}
			} 
			//tablevector[0].display();
		break;
	case 5:																		// RELATION, check for validity, execute.
		validity = 3;
		if (!valid(validity,words,position))
		{
		cout<< "ERROR: not a valid statement, needs at least one comparitor\n";
		break;
		}
		columnCounter=0;
		tablename=words[words.size()-1];
		tablename2=words[position-3];
		if (!isname(tablename))
		{
			cout<<tablename<<" - ERROR: is not a created table at the moment.\n";
			break;
		}
		if (!isname(tablename2))
		{
			cout<<tablename<<" - ERROR: is not a created table at the moment.\n";
			break;
		}
		column = words[position+3];
		cout<<"\nfor "<<tablename<<" "<<tablevector[getTable(tablename)].getRows()<<",  -  "<<tablename2<<" . add()\n";
		if(tablevector[getTable(tablename)].getColumn(column)==-1||tablevector[getTable(tablename2)].getColumn(column)==-1)
		{
			cout<<column<<" - ERROR: is not a created column at the moment.\n";
			break;
		}
		for (int i=1; i<tablevector[getTable(tablename)].getRows(); i++) // add new rows to the table being created, then fill the row with the information desired.
		{
			tablevector[getTable(tablename2)].add();
			tablevector[getTable(tablename2)].changeValue(tablevector[getTable(tablename2)].getLastRow(),tablevector[getTable(tablename2)].getColumn(column)
				,tablevector[getTable(tablename)].getElement(i,tablevector[getTable(tablename)].getColumn(column)));
		}
		tablevector[getTable(tablename)].display();
		tablevector[getTable(tablename2)].display();
		break;
	case 6: cout << "displaying "<< words[position+1]<<"\n";						//SHOW, shows the table if it exists.
		tablename = words[position+1];
		if (isname(tablename))
			tablevector[getTable(words[position+1])].display();
		else
			cout<<tablename<<" - ERROR:  is not a created table at the moment.\n";
		break;


	case 7: cout << "solving for <-\n";												//<- this one is really rough, but basically it knows there has to be an INSTRUCTION on the right side of the <-
			tempposition = position;												//so it goes through and finds all instructions, which have 2 elements to them, the LIMITER, and TABLE reference.
			while (getNextKeyword(words,position) != "null"&&tempposition!=-1)		//then it executes the command and becomes a new TABLE reference itself, so that any prior commands can be executed using its new information
			{																		// INSTRUCTION (LIMITER) (INSTRUCTION (LIMITER) (TABLE)) -becomes- INSTRUCTION (LIMITER) (NEWTABLE) -becomes- NEWTABLE
				if (getNextKeyword(words,tempposition)!="null")						// the final table is copies over to the left of the "<-"
				{
					cout<< "keywords are/is "<<getNextKeyword(words,tempposition)<<" at "<<getKeywordPosition(words, getNextKeyword(words,tempposition))<<"\n";
					tempkeyword.push_back(getNextKeyword(words,tempposition));	
				}tempposition = getKeywordPosition(words, getNextKeyword(words,tempposition));
			}
			cout<<"\n";
			for (int i = tempkeyword.size()-1;i>-1; i--)
			{
				switch(getKeyNum(tempkeyword[i])) //"select","project","rename"
				{
				case 8: cout<<"dealing with a selection \n";
						cout<<"first element is "<< getElementString(words,getKeywordPosition(words, tempkeyword[i]), 1)<<"\n";
						cout<<"second element is "<<getElementString(words,getKeywordPosition(words, tempkeyword[i]), 2)<<"\n";
						cout<<"\n";
						if (getElementString(words,getKeywordPosition(words, tempkeyword[i]), 1)==""||
							getElementString(words,getKeywordPosition(words, tempkeyword[i]), 2)=="")
						{
							isStatement=false;
							cout<< "ERROR: not a valid statement, needs 2 arguments\n";
							break;
						}
						tablename="tempvector";
						if(!isname("tempvector"))
						{
						tablevector.push_back(DBMS(tablevector[getTable(solveElementString(words,getKeywordPosition(words, tempkeyword[i]), 2))]));
						tablevector[tablevector.size()-1].setTitle(tablename);
						}
						else
						{
						tablename=solveElementString(words,getKeywordPosition(words, tempkeyword[i]), 2);
						tablevector[getTable("tempvector")].clear();
						copy(tablevector[getTable("tempvector")],tablevector[getTable(tablename)]);
						}
						cout<<solveElementString(words,getKeywordPosition(words, tempkeyword[i]), 1)<<"\n";
						tablevector[getTable("tempvector")]=tablevector[getTable(solveElementString(words,getKeywordPosition(words, tempkeyword[i]), 1))];
						words=replaceWords(words,getKeywordPosition(words, tempkeyword[i]),words.size(),"tempvector");
						
						//tempvector = solve(solveElementString(words,getKeywordPosition(words, tempkeyword[i]), 1),solveElementString(words,getKeywordPosition(words, tempkeyword[i]), 2))
					break;


				case 9:cout<<"dealing with a projection \n";
						cout<<"first element is "<< getElementString(words,getKeywordPosition(words, tempkeyword[i]), 1)<<"\n";
						cout<<"second element is "<<getElementString(words,getKeywordPosition(words, tempkeyword[i]), 2)<<"\n";
						cout<<"\n";
						if (getElementString(words,getKeywordPosition(words, tempkeyword[i]), 1)==""||
							getElementString(words,getKeywordPosition(words, tempkeyword[i]), 2)=="")
							{
							cout<< "ERROR: not a valid statement, needs 2 arguments\n";
							break;
							}
						tablename="tempvector";
						columnnames.clear();
						if(!isname("tempvector"))
						{
						tablevector.push_back(DBMS(tablevector[getTable(solveElementString(words,getKeywordPosition(words, tempkeyword[i]), 1))]));
						tablevector[tablevector.size()-1].setTitle(tablename);
						}
						else
						tablevector[getTable("tempvector")]=tablevector[getTable(solveElementString(words,getKeywordPosition(words, tempkeyword[i]), 1))];
						
						tablevector[getTable(solveElementString(words,getKeywordPosition(words, tempkeyword[i]), 2))].display();
						words=replaceWords(words,getKeywordPosition(words, tempkeyword[i]),words.size(),solveElementString(words,getKeywordPosition(words, tempkeyword[i]), 2));
					break;



				case 10:cout<<"dealing with a renaming \n";
						cout<<"first element is "<< getElementString(words,getKeywordPosition(words, tempkeyword[i]), 1)<<"\n";
						cout<<"second element is "<<getElementString(words,getKeywordPosition(words, tempkeyword[i]), 2)<<"\n";
						cout<<"\n";
						if (getElementString(words,getKeywordPosition(words, tempkeyword[i]), 1)==""||
							getElementString(words,getKeywordPosition(words, tempkeyword[i]), 2)=="")
						{
							cout<< "ERROR: not a valid statement, needs 2 arguments\n";
							break;
						}
						tablename="tempvector";
						if(!isname("tempvector"))
						{
						tablevector.push_back(DBMS(tablevector[getTable(solveElementString(words,getKeywordPosition(words, tempkeyword[i]), 2))]));
						tablevector[tablevector.size()-1].setTitle(tablename);
						}
						else
						{
						tablename=solveElementString(words,getKeywordPosition(words, tempkeyword[i]), 2);
						//tablevector[getTable("tempvector")].clear();
						copy(tablevector[getTable("tempvector")],tablevector[getTable(tablename)]);
						}
						rename(words,getKeywordPosition(words, tempkeyword[i]),tablevector[getTable("tempvector")]);
						tablevector[getTable("tempvector")]=tablevector[getTable(solveElementString(words,getKeywordPosition(words, tempkeyword[i]), 1))];
						words=replaceWords(words,getKeywordPosition(words, tempkeyword[i]),words.size(),"tempvector");
					break;
				default: cout << "Null keyword\n";
					break;
				}
			}
			if(isStatement)
			{
			combineTables(words,position);
			tablevector.push_back(DBMS(tablevector[getTable("tempvector")]));
			tablevector[tablevector.size()-1].setTitle(words[position-1]);
			tablevector[getTable(words[position-1])].display();
			}
		break;
	
	
	case 8: //cout<<"dealt with a selection \n";
					break;
	case 9://cout<<"dealt with a projection \n";
					break;
	case 10://cout<<"dealt with a renaming \n";
					break;
	case 11: cout << "Wrtiting "<< words[position+1]<<" to output file\n";					//WRITE
		tablename = words[position+1];
		if (isname(tablename))
			tablevector[getTable(words[position+1])].writeToFile();
		else
			cout<<tablename<<" - ERROR:  is not a created table at the moment.\n";
		break;
					
	case 12:cout << "Closing "<< words[position+1]<<" output file\n";						//CLOSE
					break;
	case 13:cout << "EXITING\n";
			system("PAUSE");
			exit(0);//EXIT
					break;



	default: cout << "how did that happen?\n";
		break;
	}
}
int Parser::getTable(string name)
{
	for (int i=0; i<tablevector.size(); i++)
	{
		if (tablevector[i].getTitle()==name)
			return i;
	}
	return -1;
}
bool Parser::isname(string name)
{
	for (int i=0; i<tablevector.size(); i++)
	{
		if (tablevector[i].getTitle()==name)
			return 1;
	}
	return 0;
}
string Parser::getNextKeyword(vector<string> words, int position)
{
	string keyword= "null";
	for(int i=position+1; i<words.size();i++)
	{
		for (int j = 0; j< keywords.size(); j++)
		{
			if (words[i] == keywords[j])
			{
				keyword = words[i];
				return keyword;
			}
		}
	}
	return keyword;
}
int Parser::getKeywordPosition(vector<string> words, string keyword)
{
	int position = -1;
	for(int i=0; i<words.size();i++)
	{
			if (words[i] == keyword)
			{
				position = i;
				return position;
			}
	}
	return position;
}
int Parser::getKeyNum(string keyword)
{
	int position = -1;
	for(int i=0; i<keywords.size();i++)
	{
			if (keywords[i] == keyword)
			{
				position = i;
				return position;
			}
	}
	return position;
}
string Parser::getElementString(vector<string> words, int position, int elementNumber)
{
	string returnString;
	int parenthesis = 0;
	int element=-1;
	for(int i=position; i<words.size();i++)
	{
		if (words[i] == "(")
			{
				if (parenthesis==0)
				{element++;}
				parenthesis++;
			}
		else if(words[i] == ")")
			{
				if (parenthesis==0)
				{element++;}
				parenthesis--;
				
			}
		else if(words[i] != "(" && words[i] != ")" && words[i] != ""&& parenthesis ==0)
			{
				element ++;
				//cout<<"new element "<<element<<" starts with - "<<words[i]<<"\n";
			}
		if(element==elementNumber)
			{
				returnString+=words[i];
			}
	}
	return returnString;
}
string Parser::solveElementString(vector<string> words, int position, int elementNumber)
{
	vector<string> expression;
	string returnString;
	string tablename = " ";
	int parenthesis = 0;
	int element=-1;
	int rows;
	for(int i=position; i<words.size();i++)
	{
		if (words[i] == "(")
			{
				if (parenthesis==0)
				{element++;}
				parenthesis++;
			}
		else if(words[i] == ")")
			{
				if (parenthesis==0)
				{element++;}
				parenthesis--;
				
			}
		else if(words[i] != "(" && words[i] != ")" && words[i] != ""&& parenthesis ==0)
			{
				element ++;
				//cout<<"new element "<<element<<" starts with - "<<words[i]<<"\n";
			}
		if(element==elementNumber)
			{
				expression.push_back(words[i]);
			}
		if (elementNumber==1&&element ==2)
		{
			tablename=words[i];
		}

	}
	switch(elementNumber)
	{
	case 1:
		rows=tablevector[getTable("tempvector")].getRows()-1;
		for (int i=0; i<expression.size(); i++)
		{
			if (expression[i]=="("||expression[i]==")")
			{
			expression[i].erase();
			}
				
			else if(expression[i]=="==")
			{
				for (int j=1; j<=tablevector[getTable("tempvector")].getRows()-1; j++)
				{
					if(tablevector[getTable("tempvector")].getElement(j,tablevector[getTable("tempvector")].getColumn(expression[i-1]))!=expression[i+1])
					{
						tablevector[getTable("tempvector")].deleteRow(j);
						j--;
					}
				}
				expression[i-1]="tempvector";
				expression[i].erase();
				expression[i+1].erase();
				i--;
			}
			else if(expression[i]==",")
			{
				bool check1 = false;
				bool check2 = false;
				for (int j=0; j<columnnames.size(); j++)
				{
					if (columnnames[j]==expression[i-1])
						check1=true;
					if (columnnames[j]==expression[i+2])
						check2=true;
				}
				if (check1==false)
				{columnnames.push_back(expression[i-1]);}
				if (check2==false)
					{columnnames.push_back(expression[i+2]);}
			}
			else if(expression[i]==">"&&tablevector[getTable("tempvector")].getColumn(expression[i-1])!=-1)
			{
				for (int j=1; j<=tablevector[getTable("tempvector")].getRows()-1; j++)
				{
					int n1=StringToNumber(tablevector[getTable("tempvector")].getElement(j,tablevector[getTable("tempvector")].getColumn(expression[i-1])));
					int n2=StringToNumber(expression[i+1]);
					if(n1<=n2)
					{
						tablevector[getTable("tempvector")].deleteRow(j);
						j--;
					}
				}
				expression[i-1]="tempvector";
				expression[i].erase();
				expression[i+1].erase();
				i--;
			}
			else if(expression[i]=="<")
			{
				for (int j=1; j<=tablevector[getTable("tempvector")].getRows()-1; j++)
				{
					int n1=StringToNumber(tablevector[getTable("tempvector")].getElement(j,tablevector[getTable("tempvector")].getColumn(expression[i-1])));
					int n2=StringToNumber(expression[i+1]);
					if(n1>=n2)
					{
						tablevector[getTable("tempvector")].deleteRow(j);
						j--;
					}
				}
				expression[i-1]="tempvector";
				expression[i].erase();
				expression[i+1].erase();
				i--;
			}
		else if(expression[i]=="!=")
			{
				for (int j=1; j<=tablevector[getTable("tempvector")].getRows()-1; j++)
				{
					if(tablevector[getTable("tempvector")].getElement(j,tablevector[getTable("tempvector")].getColumn(expression[i-1]))==expression[i+1])
					{
						tablevector[getTable("tempvector")].deleteRow(j);
						j--;
					}
				}
				expression[i-1]="tempvector";
				expression[i].erase();
				expression[i+1].erase();
				i--;
			}
		}
		returnString="tempvector";
		break;
	case 2:
		for (int i=0; i<expression.size(); i++)
		{
			if (expression[i]=="("||expression[i]==")")
				expression[i].erase();
			else if(expression[i]=="*")
			{
				//copy(tablevector[getTable("tempvector")],tablevector[getTable("tempvector")].crossproduct(tablevector[getTable(words[i-1])].getDBMS()));
				tablevector[getTable("tempvector")].clear();
				copy(tablevector[getTable("tempvector")],tablevector[getTable(expression[i-1])]);
				tablevector[getTable("tempvector")].crossproduct(tablevector[getTable(expression[i+1])].getDBMS());
				expression[i-1]="tempvector";
				expression[i].erase();
				expression[i+1].erase();
				i--;
			}
			
		}
		returnString=expression[0];
		break;
	default :
		break;
	}
	return returnString;
}
void Parser::rename(vector<string> words, int position, DBMS vec)
{
	vector<string> expression;
	string returnString;
	string tablename = " ";
	int parenthesis = 0;
	int element=-1;
	int elementNumber=1;
	int rows;
	for(int i=position; i<words.size();i++)
	{
		if (words[i] == "(")
			{
				if (parenthesis==0)
				{element++;}
				parenthesis++;
			}
		else if(words[i] == ")")
			{
				if (parenthesis==0)
				{element++;}
				parenthesis--;
				
			}
		else if(words[i] != "(" && words[i] != ")" && words[i] != ""&& parenthesis ==0)
			{
				element ++;
				//cout<<"new element "<<element<<" starts with - "<<words[i]<<"\n";
			}
		if(element==elementNumber)
			{
				expression.push_back(words[i]);
			}
	}
	int counter=0;
	for (int i=0; i<expression.size(); i++)
		{
			if (expression[i]=="("||expression[i]==")")
			{
			expression[i].erase();
			}
			else if(expression[i]==",")
			{
				if(counter==0)
				{
					vec.setColumnName(vec.getColumn(columnnames[counter]),expression[i-1]);
					counter++;
				}
				if(counter>0)
				{
					vec.setColumnName(vec.getColumn(columnnames[counter]),expression[i+2]);
					counter++;
				}
			}
		}
	copy(tablevector[getTable("tempvector")],vec);
}
bool Parser::valid(int length, vector<string> words, int position)
{
	int whatsLeft=words.size()-position;
	if (whatsLeft<length)
	{
		cout<<whatsLeft<<" " <<length<<"\n";
		return false;
	}
		
	else 
		return true;
}
void Parser::copy(DBMS vec1,DBMS vec2)
{
	for (unsigned i = 0; i < vec2.getRows(); ++i)
	{
		tablevector[getTable("tempvector")].add();
		for (unsigned j = 0; j < vec2.getColumns(); ++j)
		{
			tablevector[getTable("tempvector")].changeValue(i,j,vec2.getElement(i,j));
		}
	}
	//cout<<"column "<<n<<" deleted.\n";
}
vector<string> Parser::replaceWords(vector<string> words,int begin, int end,string replacement)
{
	for(int i=end-1; i>=begin; i--)
	{
		words[i].erase();
	}
	words[begin-1]=(replacement);
	return words;
}
void Parser::combineTables(vector<string> words, int position)
{
	int counter=0;
	for (int i=0; i<words.size(); i++)
	{
		cout<<words[i];
	}
	cout<<"\n";
	for (int i=position; i<words.size(); i++)
	{
		if (words[i]=="("||words[i]==")")
				words[i].erase();
		cout<<words[i];
	}
	for (int i=words.size()-1; i>=position; i--)
		{	
			if (words[i]=="("||words[i]==")")
				words[i].erase();
			else if(words[i]=="+"||words[i]=="-"||words[i]=="*")
			{
				
				if (words[i+1]=="tempvector")
				{
				tablevector[getTable("tempvector")].display();
				tablevector[getTable(words[i-1])].display();
				if (words[i]=="+")
				copy(tablevector[getTable("tempvector")],tablevector[getTable("tempvector")].setdifference(tablevector[getTable(words[i-1])].getDBMS()));
				else if (words[i]=="-")
				copy(tablevector[getTable("tempvector")],tablevector[getTable("tempvector")].setunion(tablevector[getTable(words[i-1])].getDBMS()));
				else if (words[i]=="*")
				copy(tablevector[getTable("tempvector")],tablevector[getTable("tempvector")].crossproduct(tablevector[getTable(words[i-1])].getDBMS()));
				words[i-1]="tempvector";
				words[i].erase();
				words[i+1].erase();
				tablevector[getTable("tempvector")].display();
				
				}
			}
			
		}
}
int Parser::StringToNumber( const string &Text )//Text not by const reference so that the function can be used with a 
{                               //character array as argument
	stringstream ss(Text);
	int result;
	return ss >> result ? result : 0;
}
