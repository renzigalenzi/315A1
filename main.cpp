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
	crossfinal.display();*/
	
	//checking read file
	Parser parser;
	cout << "reading from file" << endl;
	vector<string> stuff = parser.readfromfile("table");
	for each (string s in stuff) {
		cout <<"\nPARSING:: \n"<< s << "\n\n";
		parser.execute(s);
		
	}
	string user;
	string stringtoparse;
	while (user!="EXIT;")
	{
		cout<<"Please enter a line. To exit, type \"EXIT;\"\n";
		getline(cin, user);
		parser.execute(user);

	}
	system("PAUSE");
	return 0;
}
//show about box info window

