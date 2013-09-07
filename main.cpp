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
	Table m(NumColumns, NumRows);
	m.fill(m.getColumns(), m.getRows());
	m.display(m.getColumns(), m.getRows());
	m.setColumnName(0,"type");
	m.setColumnName(1,"name");
	m.setColumnName(2,"age");
	m.setColumnName(3,"sex");
	m.setColumnName(4,"security");
	m.display(m.getColumns(), m.getRows());
	m.show("name", "1");
	//create the main window and display it



	system("PAUSE");
	return 0;
}
//show about box info window

