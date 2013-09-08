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
	Table m(NumRows, NumColumns);
	m.fill();
	m.display();
	m.setColumnName(0,"type");
	m.setColumnName(1,"name");
	m.setColumnName(2,"age");
	m.setColumnName(3,"sex");
	m.setColumnName(4,"security");
	m.changeValue(2,3,"changed");
	m.display();
	m.show("sex", "changed");
	m.add();
	m.changeValue(m.getLastRow(),m.getColumn("type"),"0");
	m.changeValue(m.getLastRow(),m.getColumn("name"),"Panda");
	m.changeValue(m.getLastRow(),m.getColumn("age"),"19");
	m.changeValue(m.getLastRow(),m.getColumn("sex"),"F");
	m.changeValue(m.getLastRow(),m.getColumn("securit"),"3");
	m.display();
	m.deleteRow(3);
	m.display();
	m.deleteColumn(2);
	m.display();
	Table f(m.getTable());
	f.display();
	f.changeValue(1,m.getColumn("type"),"0");
	f.display();
	Table end(m.setunion(f.getTable()));
	end.display();


	//create the main window and display it



	system("PAUSE");
	return 0;
}
//show about box info window

