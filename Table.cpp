//=======================================
// CSCE 315-501
// Project 1 - Database Management System
// Edgardo Angel
// Lance Elliot
// Ross Hudgins
//=======================================

#include "Table.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <time.h>
using namespace std;





void Table::fill(int Columns, int Rows)
{
	for (int i=0; i<vec.size(); i++)
	{
		for (int j=0; j<vec[i].size(); j++)
		{	
			int n = rand() % 4+1;
			stringstream ss;
			ss << n;
			vec[i][j]=ss.str();

		}
	}
}
void Table::display(int Columns, int Rows)
{
	for (int i=0; i<Columns; i++)
	{
		cout<<"\n";
		for (int j=0; j<Rows; j++)
		{
			cout<<vec[i][j];
			for (int k=vec[i][j].length(); k<12;k++)
				cout<<" ";
		}
	}
	cout<<"\n\n";
}
void Table::display(int Rows)
{
		for (int j=0; j<vec[Rows].size(); j++)
		{
			cout<<vec[Rows][j];
			for (int k=vec[Rows][j].length(); k<12;k++)
				cout<<" ";
		}
	
	cout<<"\n";
}
void Table::show(string Colname, string comparitor){
	cout<<"finding elements of column \""<<Colname<<"\" with type \""<< comparitor<<"\".\n";
	int keyColumn = -1;
	for (int j=0; j<vec[0].size(); j++)
		{	
			if (vec[0][j]==Colname)
			{
			keyColumn=j;
			break;
			}
		}
	if (keyColumn>=0)
	{
	for (int j=0; j<vec.size(); j++)
		{	
			if (vec[j][keyColumn]==comparitor){
			cout<<"Item Found!\n";
			display(j);
			break;
			}
		}
	}

}

bool operator==(const Table& m1, const Table& m2)
{

return true;

}
std::ostream& operator<<(ostream& os, const Table& m)
{
	
os  <<"Table color: "/*<< x << "\n" <<"Table size: "<< y << "\n"*/;
    return os;
}
std::istream& operator>>(istream& is, Table& m)
{
return is;

}
