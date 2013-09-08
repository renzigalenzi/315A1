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





void Table::fill()
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
void Table::display()
{
	for (int i=0; i<vec.size(); i++)
	{
		cout<<"\n";
		for (int j=0; j<vec[i].size(); j++)
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
int Table::getColumn(string s)
{
		for (int j=0; j<vec[0].size(); j++)
		{
			if (vec[0][j]==s)
			{
			return j;
			}
		}
		return -1;
	//cout<<"\n";
}
void Table::deleteRow(int n)
{
	if (vec.size() > n)
	{
		vec.erase(vec.begin() + n);
	}
	cout<<"row "<<n<<" deleted.\n";
}
void Table::deleteColumn(int n)
{
	for (unsigned i = 0; i < vec.size(); ++i)
	{
		if (vec[i].size() > n)
		{
			vec[i].erase(vec[i].begin() + n);
		}
	}
	cout<<"column "<<n<<" deleted.\n";
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
