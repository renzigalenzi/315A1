//=======================================
// CSCE 315-501
// Project 1 - Database Management System
// Edgardo Angel
// Lance Elliot
// Ross Hudgins
//=======================================

#include "DBMS.h"
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





void DBMS::fill()
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
void DBMS::display()
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
void DBMS::display(int Rows)
{
		for (int j=0; j<vec[Rows].size(); j++)
		{
			cout<<vec[Rows][j];
			for (int k=vec[Rows][j].length(); k<12;k++)
				cout<<" ";
		}
	
	cout<<"\n";
}
int DBMS::getColumn(string s)
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
string DBMS::getElement(int x, int y)
{
		return vec[x][y];
	//cout<<"\n";
}
//UNION----------------------------------------------------------------------------------------
vector<vector<string> > DBMS::setunion(vector<vector<string> > vec2){
	vector< vector<string> > vecFinal;
	bool check = true;
	int offsety=0;
	int resultant = 0;
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
	for (int i=1; i<vec2.size(); i++)
	{
		for (int j=1; j<vec.size(); j++)
		{
			for (int k=0; k<vec[j].size()&&k<vec2[i].size(); k++)
			{

				if (k<vec[j].size()&&k<vec2[i].size()&&vec[j][k]!=vec2[i][k])// if there is something different in a row then dont worry about that row
				k=vec[j].size()+vec2[i].size();
				if (k==vec[j].size()-1||k==vec2[i].size()-1) // if you get to the end of a compared row and everything is the same, there was a duplicate. so delete it.
				{
				resultant=i-offsety;
				vecFinal.erase(vecFinal.begin() + resultant);
				offsety++;
				//cout<<" no discrepancy in the vectors at - "<<j<<" "<<k<<" offset is now "<<offsety<<"\n";
				}
			}
		}
	}
	offsety=vecFinal.size();
	for (int i = 0; i < vec.size(); i++) {// now that the final vector only contains the differences between the first and second vector, add the first vector back in.
		vecFinal.push_back(vec[i]);
	}
	vecFinal.erase(vecFinal.begin() +offsety);
	if (!check)
		cout<<"attributes did not match, union is untesDBMS.\n";
	return vecFinal;
}

// DIFFERENCE ----------------------------------------------------------------------------------------------------
vector<vector<string> > DBMS::setdifference(vector<vector<string> > vec2){
	vector< vector<string> > vecFinal;
	vector< vector<string> > vecFinal2;
	bool check = true;
	int offsety=0;
	int resultant = 0;
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
		vecFinal=vec2;
		vecFinal2=vec;//into the returned vector so values can be manipulated without ruining the compared vector
	for (int i=1; i<vec2.size(); i++)
	{
		for (int j=1; j<vec.size(); j++)
		{
			for (int k=0; k<vec[j].size()&&k<vec2[i].size(); k++)
			{

				if (k<vec[j].size()&&k<vec2[i].size()&&vec[j][k]!=vec2[i][k])// if there is something different in a row then dont worry about that row
				k=vec[j].size()+vec2[i].size();
				if (k==vec[j].size()-1||k==vec2[i].size()-1) // if you get to the end of a compared row and everything is the same, there was a duplicate. so delete it.
				{
				resultant=i-offsety;
				vecFinal.erase(vecFinal.begin() + resultant);
				offsety++;
				//cout<<" no discrepancy in the vectors at - "<<j<<" "<<k<<" offset is now "<<offsety<<"\n";
				}
			}
		}
	}
	offsety = 0;
	for (int i=1; i<vec.size(); i++)
	{
		for (int j=1; j<vec2.size(); j++)
		{
			for (int k=0; k<vec2[j].size()&&k<vec[i].size(); k++)
			{

				if (k<vec2[j].size()&&k<vec[i].size()&&vec2[j][k]!=vec[i][k])// if there is something different in a row then dont worry about that row
				k=vec2[j].size()+vec[i].size();
				if (k==vec2[j].size()-1||k==vec[i].size()-1) // if you get to the end of a compared row and everything is the same, there was a duplicate. so delete it.
				{
				resultant=i-offsety;
				vecFinal2.erase(vecFinal2.begin() + resultant);
				offsety++;
				//cout<<" no discrepancy in the vectors at - "<<j<<" "<<k<<" offset is now "<<offsety<<"\n";
				}
			}
		}
	}
	offsety=vecFinal.size();
	for (int i = 0; i < vecFinal2.size(); i++) {// now that the final vector only contains the differences between the first and second vector, add the first vector back in.
		vecFinal.push_back(vecFinal2[i]);
	}
	vecFinal.erase(vecFinal.begin() +offsety);
	if (!check)
		cout<<"attributes did not match, union is untesDBMS.\n";
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
vector<vector<string> > DBMS::crossproduct(vector<vector<string> > vec2) {
	vector<vector<string> > vecFinal;
	//check column names, if any are the same, abort and return original vector
	for(int i = 0; i < vec[0].size(); i++) {
		for (int j = 0; j < vec2[0].size(); j++) {
			if (vec[0][i] == vec2[0][j]) { //check all elements of vec2[0] with each element of vec1[0]
				cout << "Unable to do cross product, some column is the same" << endl;
				return vec; //abort!
			}
		}
	}
	//construct cross product DBMS
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
void DBMS::deleteRow(int n)
{
	if (vec.size() > n)
	{
		vec.erase(vec.begin() + n);
	}
	cout<<"row "<<n<<" deleted.\n";
}
void DBMS::clear()
{
	vec.erase(vec.begin(),vec.end());
}
void DBMS::deleteAttr(int n,string attr)
{
	for (int i = 0; i< vec.size(); i++)
	{
		if (vec[i][n]==attr)
		{
		vec.erase(vec.begin() + i);
		i--;
		}
	}
	cout<<"row "<<n<<" deleted.\n";
}
void DBMS::deleteColumn(int n)
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

void DBMS::show(string Colname, string comparitor){
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

void DBMS::writeToFile(){
	string filename = title + ".db";
	ofstream file;
	file.open(filename.c_str());
	if (file.is_open()){
		//write creation DML
		file << "CREATE TABLE " << title << " (";
		for (int i = 0; i < vec[0].size() ; i++) { //write column names
			if (i != (vec[0].size()-1))
				file << vec[0][i] << ", ";
			else
				file << vec[0][i];
		}
		file << ");" << endl;

		//write INSERT row DML
		for (int i = 1; i < vec.size(); i++){
			file << "INSERT INTO " << title << " VALUES FROM (";
			for (int j = 0; j < vec[0].size(); j++){
				if (j != (vec[0].size()-1))
					file << vec[i][j] << ", ";
				else
					file << vec[i][j];
			}
			file << ");" << endl;
		}
	}
	else cout << "failed to open file for output" << endl;
}

bool operator==(const DBMS& m1, const DBMS& m2)
{

return true; //LOL

}
std::ostream& operator<<(ostream& os, const DBMS& m)
{
	
os  <<"DBMS color: "/*<< x << "\n" <<"DBMS size: "<< y << "\n"*/;
    return os;
}
std::istream& operator>>(istream& is, DBMS& m)
{
return is;

}
