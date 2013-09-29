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
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sstream>
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

	Parser parser;
 
	string user;
	string stringtoparse;

	string command[15] = {"1","2","3","4","5","a","b","c","d","e","f","g","h","i","j"};

	int choice;

	cout<<"Welcome to the DBMS Application \nPlease choose an option below by typing the appropiate character (1-5) or (a-i):";
	while (user!="5" || user.size()>1)
	{
		cout<<"\n(1) OPEN \n(2) WRITE \n(3) SHOW \n(4) CLOSE \n(5) EXIT \n\n"<<
			"(a) CREATE TABLE \n(b) INSERT INTO \n(c) SELECTION \n(d) UNION \n(e) DIFFERENCE \n(f) PRODUCT \n\nOPTION: ";
		//check to see if file is open
		getline(cin, user);

		for (int i = 0; i<=15; i++){ //check with possible input
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
			string tname, numvars, cre_string;
			bool firstcol =false;
			cout<<"Enter name of the new table: ";
			getline(cin, tname);
			cout<<"Amount of variables: ";
			getline(cin, numvars);

			cre_string = "CREATE TABLE "+ tname + " ("; //starts string with table name

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

			for (int k = 0; k<=vars.size()-1; k++){
				cout<<"Variable #"<<k+1<<vars.at(k).getvarname()<<'-'<<vars.at(k).getvartype()<<'-'<<vars.at(k).getvarsize()<<'\n';
				if (vars.at(k).getvartype() == "string"){ //adds string column with respective size
					if (firstcol)
						cre_string+=", ";
					cre_string+=vars.at(k).getvarname()+' '+"VARCHAR("+vars.at(k).getvarsize()+")";
					firstcol=true;
				} else if (vars.at(k).getvartype() == "integer"){ //adds integer column
					if (firstcol)
						cre_string+=", ";
					cre_string+=vars.at(k).getvarname()+' '+"INTEGER";
					firstcol=true;
				}
			}
			cre_string+=");"; //close parsing string
			parser.execute(cre_string); //send to parsing
			break;
			}
		case 7: //INSERT INTO
			{
			string ins_string, tname;
			bool firstcol =false;

			cout<<"Enter table where you are going to be inserting: ";
			getline(cin, tname);

			ins_string="INSERT INTO "+tname+" VALUES FROM (";

			int tcolumn = parser.getcsize(tname); 

			for (int i = 0; i<tcolumn;i++)
			{
				string tempattname;
				cout<<"Enter variable #"<<i+1<<" attribute: ";
				getline(cin, tempattname);
				if (firstcol)
				ins_string+=", ";
				int num = atoi(tempattname.c_str()); 
				if (!tempattname.empty() && tempattname.find_first_not_of("0123456789") == std::string::npos){ //check to see if it is an integer
					stringstream ss;
					ss<<num;
					ins_string+=ss.str();
				} else {
					ins_string+='"'+tempattname+"\"";
				}
				
				firstcol=true;
			}
			
			ins_string+=");"; //close parsing string
			parser.execute(ins_string); //send to parsing
			parser.execute("SHOW "+tname+";"); //display table with new entry

			break;
			}
		case 8: //Selection
			{
				string tname, sname, cond, sel_string;
				
				cout<<"Enter table where you are going to be selecting from: ";
				getline(cin, tname);

				cout<<"Enter name of selection to store values: ";
				getline(cin,sname);

				cout<<"Enter conditional statement for your selection, \n"<<
					"This is in the form of (variable) (relational operator) (variable) \n"<<
					"Do not include '(' or ')' \n" <<
					"You can use '<', '>', '==', '<=' & '>=' \n\n"<<
					"Conditional Statement: ";
				getline(cin,cond);

				sel_string = sname + " <- select (" + cond + ')' + tname + ';'; //create parsing string

				parser.execute(sel_string); //send to parsing
				break;
			}
		case 9: //Union
			{
				string uvarname, ufirst, usecond, uni_string;

				cout<<"Enter name to store union results: ";
				getline(cin,uvarname);

				cout<<"For Union you must have two tables to compare \n";
				
				cout<<"Enter name of first table: ";
				getline(cin,ufirst);

				cout<<"Enter name of second table: ";
				getline(cin,usecond);

				uni_string = uvarname + " <- " + ufirst + " + " + usecond + ';';
				parser.execute(uni_string); //send to parsing
				break;
			}
		case 10: //Difference
			{
				string dvarname, dfirst, dsecond, dif_string;
				cout<<"Enter name to store difference results: ";
				getline(cin,dvarname);

				cout<<"For Difference you must have two tables to compare \n";
				
				cout<<"Enter name of first table: ";
				getline(cin,dfirst);

				cout<<"Enter name of second table: ";
				getline(cin,dsecond);

				dif_string = dvarname + " <- " + dfirst + " - " + dsecond + ';';
				parser.execute(dif_string); //send to parsing
				break;
			}
		case 11: //Product
			{
				string pvarname, pfirst, psecond, pro_string;
				cout<<"Enter name to store product results: ";
				getline(cin,pvarname);

				cout<<"For Product you must have two tables to compare \n";
				
				cout<<"Enter name of first table: ";
				getline(cin,pfirst);

				cout<<"Enter name of second table: ";
				getline(cin,psecond);

				pro_string = pvarname + " <- " + pfirst + " * " + psecond + ';';
				parser.execute(pro_string); //send to parsing
				break;
			}
		case 12: //Relation
			{
				string rel_string;
				parser.execute(rel_string); //send to parsing
				break;
			}
		case 13: //Projection
			{
				string proj_string;
				parser.execute(proj_string); //send to parsing
				break;
			}
		case 14: //Rename
			{
				string ren_string;
				parser.execute(ren_string); //send to parsing
				break;
			}
		case 15: //Update
			{
				string upd_string;
				parser.execute(upd_string); //send to parsing
				break;
			}
		default:
			break;
		}
	}
	system("PAUSE");
	return 0;
}
