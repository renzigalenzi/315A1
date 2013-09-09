//=======================================
// CSCE 315-501
// Project 1 - Database Management System
// Edgardo Angel
// Lance Elliot
// Ross Hudgins
//=======================================

#include "Table.h"

#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
#include <ctime>
using namespace std;





int main()
{
	int NumColumns=5;
	int NumRows=5;
	Table m(NumRows, NumColumns,"Original");
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
	m.setTitle("Row Added");
	m.display();
	m.deleteRow(3);
	m.setTitle("Row Deleted");
	m.display();
	m.deleteColumn(2);
	m.setTitle("Column Deleted");
	m.display();
	Table f(m.getTable(),"Second Table");
	f.display();
	f.changeValue(1,f.getColumn("type"),"0");
	//f.changeValue(4,f.getColumn("type"),"3");
	//f.setColumnName(3,"securit"); //uncomment to show a failed union.
	f.setTitle("Second Table Altered");
	f.display();
	Table end(m.setunion(f.getTable()),"Union Table");
	end.display();

	//test cross product
	Table cross1(5, 3, "Cross 1"); //rows > columns on either table breaks it for some reason, vector out of range
	//Table cross1(3, 3, "Cross 1");
	cross1.fill();
	cross1.setColumnName(0, "one");
	cross1.setColumnName(1, "two");
	//cross1.setColumnName(2, "three");
	cross1.display();

	Table cross2(5, 3, "Cross 2"); 
	cross2.fill();
	cross2.setColumnName(0, "four");
	cross2.setColumnName(1, "five");
	cross2.setColumnName(2, "six");
	cross2.display();

	vector<vector<string> > crossend;
	crossend = cross1.crossproduct(cross2.getTable());
	Table crossfinal(crossend, "Cross 1 X Cross 2");
	crossfinal.display();
	
	system("PAUSE");
	return 0;
}
//show about box info window

