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

	cout<<"Welcome to the DBMS Application \n";
	
	parser.execute("OPEN test;"); //Preload DBMS
	cout<<"Convicts Database preloaded... \n";

	while (user!="5" || user.size()>1)
	{
		cout<<"Please choose an option below by typing the appropiate character (1-5) or (a-i):";
		cout<<"--------------------\n(1) OPEN \n(2) WRITE \n(3) SHOW \n(4) CLOSE \n(5) EXIT \n--------------------\n"<<
			"(a) CREATE TABLE \n(b) INSERT INTO \n(c) SELECTION \n(d) UNION \n(e) DIFFERENCE \n(f) PRODUCT \n"<<
			"(g) PROJECTION \n(h) RENAME \n(i) UPDATE \n(j) DELETE \n\nOPTION: ";

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
				string tname, tname2, tnumber, sname, cond, sel_string;
				while (tnumber != "2"&&tnumber != "1")
				{
				tnumber="";
				cout<<"Selection using 1 or 2 Tables? : ";
				getline(cin, tnumber);
				cout<<tnumber<<"\n";
				}
				if (tnumber == "2")
				{
					cout<<"Enter first table where you are going to be selecting from: ";
					getline(cin, tname);
					cout<<"Enter second table where you are going to be selecting from: ";
					getline(cin, tname2);
				}
				else
				{
				cout<<"Enter table where you are going to be selecting from: ";
				getline(cin, tname);
				}

				cout<<"Enter name of selection to store values: ";
				getline(cin,sname);

				cout<<"Enter conditional statement for your selection, \n"<<
					"This is in the form of (variable) (relational operator) (variable) \n"<<
					"Do not include '(' or ')' \n" <<
					"You can use '<', '>', '==', '<=', '&&', '>=' \n\n"<<
					"Conditional Statement: ";
				getline(cin,cond);

				if (tnumber == "2")
				{
					sel_string = sname + " <- select (" + cond + ')' + '(' + tname + " * " + tname2 +')'+ ';';
				}
				else
					sel_string = sname + " <- select (" + cond + ')' + tname + ';'; //create parsing string

				parser.execute(sel_string); //send to parsing
				break;
			}
		case 9: //Union
			{
				string ctname1, ctname2, uvarname, ufirst, usecond, uni_string;

				cout<<"Enter name to store union results: ";
				getline(cin,uvarname);

				uni_string += uvarname + " <- ";

				cout<<"\nFor Union you must have two tables to compare \n\n"
					<<"If you wish to make a conditional statement,\n"
					<<"please type the conditional statement inside parentheses\n"
					<<"(conditional statement)\n"
					<<"then type the TABLE NAME for the conditional statement \n\n";
				
				cout<<"Enter NAME of FIRST table or ENTIRE conditional statement: ";
				getline(cin,ufirst);

				if (ufirst.at(0)=='(')
				{
					cout<<"TABLE NAME for conditional statement: ";
					getline(cin,ctname1);
					uni_string += "(select " + ufirst + ' ' + '(' + ctname1;
				} else {
					uni_string += ufirst + " + ";
				}

				cout<<"Enter NAME of SECOND table: ";
				getline(cin,usecond);

				if (ufirst.at(0)=='(')
				{
					/*cout<<"TABLE NAME for conditional statement: ";
					getline(cin,ctname2);*/
					uni_string += " * " + usecond+ "))";
				} else {
					uni_string += usecond;
				}

				uni_string += ';';
				cout<<uni_string<<'\n';

				parser.execute(uni_string); //send to parsing
				break;
			}
		case 10: //Difference -- Copy from Union until it works
			{
				string ctname1, ctname2, dvarname, dfirst, dsecond, dif_string;

				cout<<"Enter name to store union results: ";
				getline(cin,dvarname);

				dif_string += dvarname + " <- ";

				cout<<"\nFor Union you must have two tables to compare \n\n"
					<<"If you wish to make a conditional statement,\n"
					<<"please type the conditional statement inside parentheses\n"
					<<"(conditional statement)\n"
					<<"then type the TABLE NAME for the conditional statement \n\n";
				
				cout<<"Enter NAME of FIRST table or conditional statement: ";
				getline(cin,dfirst);

				if (dfirst.at(0)=='(')
				{
					cout<<"TABLE NAME for conditional statement: ";
					getline(cin,ctname1);
					dif_string += "(select " + dfirst + ' ' + ctname1 + ") - ";
				} else {
					dif_string += dfirst + " - ";
				}

				cout<<"Enter NAME of SECOND table or conditional statement: ";
				getline(cin,dsecond);

				if (dsecond.at(0)=='(')
				{
					cout<<"TABLE NAME for conditional statement: ";
					getline(cin,ctname2);
					dif_string += "(select " + dsecond + ' ' + ctname2 + ")";
				} else {
					dif_string += dsecond;
				}

				dif_string += ';';
				cout<<dif_string<<'\n';

				parser.execute(dif_string); //send to parsing
				break;
			}
		case 11: //Product -- Copy from Union until it works
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
				cout<<pro_string;
				parser.execute(pro_string); //send to parsing
				break;
			}
		case 12: //Projection
			{
				string relvarname, tname, tcolumn, pnum, proj_string;
				int pint;
				cout<<"Enter NAME to store relation results: ";
				getline(cin,relvarname);

				cout<<"Enter NAME of the table your are going to work on: ";
				getline(cin,tname);

				cout<<"Enter # of projections to extract: ";
				getline(cin,pnum);
				pint = atoi(pnum.c_str());

				proj_string = "INSERT INTO " + relvarname + " VALUES FROM RELATION project (";
				for (int i = 0; i<pint; i++)
				{
					string tempname;
					cout<<"Enter NAME of relation #"<<i+1<<": ";
					getline(cin,tempname);
					if (i+1==pint)
					{
						proj_string+=tempname+")";
					} else {
						proj_string+=tempname+", ";
					}
				}
				proj_string+=' ' + tname + ';' ;
				cout<<'\n'<<proj_string<<'\n';
				parser.execute(proj_string); //send to parsing
				break;
			}
		case 13: //Rename
			{
				string renvarname, tname, ren_string;

				cout<<"To rename you must save to a new location.\nEnter NAME to store renaming results: ";
				getline(cin,renvarname);

				cout<<"Enter NAME of table to rename: ";
				getline(cin, tname);

				int tcolumn = parser.getcsize(tname);
				cout<<"You must RENAME "<<tcolumn<<" variables... \n";

				ren_string = renvarname + " <- rename (";

				for (int i = 0; i<tcolumn; i++)
				{
					string tempnewname;
					cout<<"Enter NAME of new variables #"<<i+1<<": ";
					getline(cin,tempnewname);
					if (i+1==tcolumn)
					{
						ren_string+=tempnewname+")";
					} else {
						ren_string+=tempnewname+", ";
					}
				}

				ren_string+=' ' + tname + ';' ;
				cout<<'\n'<<ren_string<<'\n';
				parser.execute(ren_string); //send to parsing
				break;
			}
		case 14: //Update
			{
				string upd_string;
				parser.execute(upd_string); //send to parsing
				break;
			}
		case 15: //Delete
			{
				string del_string;
				parser.execute(del_string); //send to parsing
				break;
			}
		default:
			break;
		}
	}
	system("PAUSE");
	return 0;
}
