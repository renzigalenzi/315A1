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
	cout<<"\nTable name: "<<title;
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
vector<vector<string> > Table::setunion(vector<vector<string> > vec2){
	vector< vector<string> > vecFinal;
	bool check = true;
	int offsety=0;
	if (vec[0].size()!=vec2[0].size())
	return vecFinal;
	for (int j=0; j<vec[0].size(); j++)//comparing only the first (attribute) row.
		{
			if (vec[0][j]!=vec2[0][j])//if any differences in attributes - then nothing will happen. (I believe) -LE
			{
			check = false;
			}
		}
	if (check == true)// preliminary check to make sure all attributes are the same, after which the compared vector is moved
		vecFinal=vec2;//into the returned vector so values can be manipulated without ruining the compared vector
	for (int j=1; j<vec.size()&&j<vecFinal.size(); j++)
		{
		for (int k=0; k<vec[0].size()&&k<vecFinal[0].size(); k++)
			{

				if (vec[j+offsety][k]!=vecFinal[j][k])
				{
				vecFinal.erase(vecFinal.begin() + j);
				offsety++;
				k=0;
				cout<<"discrepancy in the vectors at - "<<j<<" "<<k<<"\n";
				}
			}
	}
	if (!check)
		cout<<"attributes did not match, union is untestable.\n";
	return vecFinal;
}
//helper for cross product---------------------------------------------
vector<string> appendvector(vector<string> vec1, vector<string> vec2) {
	vector<string> tempvec = vec1;
	for (int i = 0; i < vec2.size(); i++) {
		tempvec.push_back(vec2[i]);
	}
	return tempvec;
}
//---------------------------------------------------------------------
vector<vector<string> > Table::crossproduct(vector<vector<string> > vec2) {
	vector<vector<string> > vecFinal;
	//check column names, if any are the same, abort and return original vector
	for(int i = 0; i < vec.size(); i++) {
		for (int j = 0; j < vec2.size(); j++) {
			if (vec[0][i] == vec2[0][j]) { //check all elements of vec2[0] with each element of vec1[0]
				cout << "Unable to do cross product, some column is the same" << endl;
				return vec; //abort!
			}
		}
	}
	//construct cross product table
	int finalrows = vec[0].size() * vec2[0].size(); //hmm, i don't even use this
	int finalcolumns = vec.size() + vec2.size(); //or this
	vector<string> tempvec;
	vecFinal.push_back(appendvector(vec[0], vec2[0]));

	for (int i = 1; i < vec.size(); i++) {
		for (int j = 1; j < vec2.size(); j++) {
			tempvec = appendvector(vec[i], vec2[j]);
			vecFinal.push_back(tempvec);
		}
	}
	return vecFinal;
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
