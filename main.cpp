//=======================================
// CSCE 315-501
// Project 1 - Database Management System
// Edgardo Angel
// Lance Elliot
// Ross Hudgins
//=======================================

#include "DBMS.h"
#include "Parser.h"

#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <ctime>
using namespace std;

class colvar{

	string varname;
	string vartype;
	string varsize;

public:

	void setvarname(string name) {
		varname = name;
	}

	void setvartype(string type) {
		vartype = type;
	}

	void setvarsize(string size) {
		varsize = size;
	}

	string getvarname(){
		return varname;
	}

	string getvartype(){
		return vartype;
	}

	string getvarsize(){
		return varsize;
	}

};


int main()
{
	/*int NumColumns=5;
	int NumRows=5;
	DBMS m(NumRows, NumColumns,"Original");
	m.fill();
	m.display();
	m.setColumnName(0,"type");
	m.setColumnName(1,"name");
	m.setColumnName(2,"age");
	m.setColumnName(3,"sex");
	m.setColumnName(4,"security");
	m.changeValue(2,3,"changed");
	m.setTitle("Attributes Added");
	
	m.display();
	m.show("sex", "changed");
	m.add();
	m.changeValue(m.getLastRow(),m.getColumn("type"),"0");
	m.changeValue(m.getLastRow(),m.getColumn("name"),"Panda");
	m.changeValue(m.getLastRow(),m.getColumn("age"),"19");
	m.changeValue(m.getLastRow(),m.getColumn("sex"),"F");
	m.changeValue(m.getLastRow(),m.getColumn("securit"),"3");
	m.changeValue(3,m.getColumn("age"),"2");
	m.display();
	m.deleteAttr(m.getColumn("age"),"2");
	m.display();
	m.setTitle("Row Added");
	m.display();
	m.deleteRow(3);
	m.setTitle("Row Deleted");
	m.display();
	m.deleteColumn(2);
	m.setTitle("Column Deleted - Original Final");
	m.display();
	m.writeToFile();
	/*
	DBMS f(m.getDBMS(),"Second DBMS");
	f.display();
	f.changeValue(1,f.getColumn("type"),"0");
	f.changeValue(4,f.getColumn("type"),"3");
	//f.setColumnName(3,"securit"); //uncomment to show a failed union.
	f.setTitle("Second DBMS Altered");
	f.display();
	DBMS tunion(m.setunion(f.getDBMS()),"Union DBMS - Original Final x Second Altered");
	tunion.display();
	DBMS tdifference(m.setdifference(f.getDBMS()),"Difference DBMS - Original Final x Second Altered");
	tdifference.display();
	//test cross product
	DBMS cross1(5, 3, "Cross 1"); //rows > columns on either DBMS breaks it for some reason, vector out of range
	//DBMS cross1(3, 3, "Cross 1");
	cross1.fill();
	cross1.setColumnName(0, "one");
	cross1.setColumnName(1, "two");
	//cross1.setColumnName(2, "three");
	cross1.display();

	DBMS cross2(5, 3, "Cross 2"); 
	cross2.fill();
	cross2.setColumnName(0, "four");
	cross2.setColumnName(1, "five");
	cross2.setColumnName(2, "six");
	cross2.display();

	vector<vector<string> > crossend;
	crossend = cross1.crossproduct(cross2.getDBMS());
	DBMS crossfinal(crossend, "Cross 1 X Cross 2");
	crossfinal.display();
	*/
	//checking read file
	Parser parser;
	/*cout << "reading from file" << endl;
	vector<string> stuff = parser.readfromfile("table");
	for each (string s in stuff) {
		if (s.size()>0)
		{
		cout <<"\nPARSING:: \n"<< s << "\n\n";
		parser.execute(s);
		}
		
	}*/
	string user;
	string stringtoparse;

	string command[15] = {"1","2","3","4","5","a","b","c","d","e","f","g","h","i","j"};

	int choice;

	cout<<"Welcome to the DBMS Application \nPlease choose an option below by typing the appropiate character (1-5) or (a-i):";
	while (user!="5")
	{
		cout<<"\n(1) OPEN \n(2) WRITE \n(3) SHOW \n(4) CLOSE \n(5) EXIT \n\n"<<
			"(a) Create table \n(b) Insert into table \n\nOPTION: ";
		//check to see if file is open
		getline(cin, user);

		for (int i = 0; i<=15; i++){
			if (user==command[i]){
				choice=i+1;
				i=15;
			}
		}

		switch(choice)
		{
		//Numerical options 1 through 5 are about file management
		case 1: //OPEN
			{
			string file_name;
			cout<<"Enter name of .db file to load into the DBMS: ";
			getline(cin, file_name);
			string open_string = "OPEN "+file_name+";";
			parser.execute(open_string);
			break;
			}
		case 2: // WRITE
			{
			string write_table;
			cout<<"Enter name of table to be written: ";
			getline(cin, write_table);
			string write_string = "WRITE "+write_table+";";
			parser.execute(write_string);
			break;
			}
		case 3:// SHOW
			{
			string show_table;
			cout<<"Enter name of table to be displayed: ";
			getline(cin, show_table);
			string show_string = "SHOW "+show_table+";";
			parser.execute(show_string);
			break;
			}
		case 4: // CLOSE
			break;
		//Alphabetical options deal with the DBMS
		case 6:// CREATE TABLE
			{
			vector<colvar> vars;
			string tname, numvars;
			cout<<"Enter name of the new table: ";
			getline(cin, tname);
			cout<<"Amount of variables: ";
			getline(cin, numvars);

			for (int j = 0 ; j <=(atoi(numvars.c_str())-1); j++)
			{
				string tempnamevar, temptypevar, tempsizevar;
				colvar tempvar;
				cout<<"Enter NAME of a column variable #"<<j+1<<": ";
				getline(cin, tempnamevar);
				tempvar.setvarname(tempnamevar);
				cout<<"Enter TYPE of a column variable #"<<j+1<<": ";
				getline(cin, temptypevar);
				tempvar.setvartype(temptypevar);
				if (temptypevar=="string")
				{
					cout<<"Enter SIZE of a column variable #"<<j+1<<": ";
					getline(cin, tempsizevar);
					tempvar.setvarsize(tempsizevar);
				} else {
					tempvar.setvarsize("-");
				}
				vars.push_back(tempvar);
			}

			string ct_string = "CREATE TABLE "+ tname + " ("; //starts string with table name

			for (int k = 0; k<=vars.size()-1; k++){
				cout<<"Variable #"<<k+1<<vars.at(k).getvarname()<<'-'<<vars.at(k).getvartype()<<'-'<<vars.at(k).getvarsize()<<'\n';
				if (vars.at(k).getvartype() == "string"){ //adds string column with respective size
					ct_string+=vars.at(k).getvarname()+' '+"VARCHAR("+vars.at(k).getvarsize()+"), ";
				} else if (vars.at(k).getvartype() == "integer"){ //adds integer column
					ct_string+=vars.at(k).getvarname()+' '+"INTEGER, ";
				}
			}
			ct_string+=');'; //close parsing string
			parser.execute(ct_string); //send to parsing
			break;
			}
		case 7: //INSERT INTO
			{
			string ii_string;
			string tname;
			
			cout<<"Enter table where you are going to be inserting: ";
			getline(cin, tname);

			ii_string="INSERT INTO "+tname+" VALUES FROM (";

			int tcolumn;
			tcolumn = parser.getcsize(); // Needs to take the amount of columns of a given table name
			cout<<"Column Size: "<<tcolumn<<'\n';

			for (int i = 0; i<=tcolumn;i++)
			{
				string tempattname;
				cout<<"Enter variable attribute: ";
				getline(cin, tempattname);
				ii_string+='"'+tempattname+"\", ";
			}
			
			ii_string+=');'; //close parsing string
			parser.execute(ii_string); //send to parsing

			break;
			}
		default:
			break;
		}
	}
	system("PAUSE");
	return 0;
}
//show about box info window

