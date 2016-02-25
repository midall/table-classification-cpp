#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <string>

#include "table.h"

using namespace std;

//CONSTRUCTOR && CREATING TABLE FROM CSV
Table::Table(string path) {
	
	setTable(path);
}

//DESTRUCTOR
Table::~Table() {
	
}

//READ CSV
void Table::setTable(string path) {
	
	//VARIABLES
	int row = 0;
	string csvLine, val;
	double dval;
	
	//OPEN THE FILE
	ifstream inf(path.c_str());
	
	//CHECK THE FILE (IF EXIST && CORRECT NAME)
	if (!inf) {
        throw 1;
    }
    
    while (inf) {
		//READ THE LINE
        getline(inf, csvLine);
        istringstream stream(csvLine);
		
		//BREAK THE LINE IN COMMAS
     	while(getline(stream, val, ',')) {
     		tableCSV.resize(row + 1);
     		//CONVERT STRING TO DECIMAL - double
			dval = atof(val.c_str());
			tableCSV[row].push_back(dval);   
    	}
        row++;
    }
}

//GET CSV
vector<vector<double> > Table::getTable() {
	
	return tableCSV;
}

//CALCULATE THE AVERAGE
double Table::averageTable(const unsigned int &column) {
	
	double 	sum;
	int 	j = 0;
	
	//CHECK IF "column number" IS VALID
	if(column >= 1 && column <= tableCSV[0].size()) {
		for(register int i=0; i<tableCSV.size(); i++) {
			sum += 	tableCSV[i][column-1];
			j++;
		}		
		return sum/j;
		
	} else {
		throw 2;
	} 
}

//CALCULATE THE DEVIATION
double Table::deviationTable(const unsigned int &column) {
	
	double dvt 	= 0;
	int N 		= tableCSV.size();
	
	if(column >= 1 && column <= tableCSV[0].size()) {
		double avg = averageTable(column);
		
		for(int i=0; i<N; i++) {
			dvt += pow(tableCSV[i][column-1]  - avg, 2);
		}
		dvt = pow(dvt/(N-1), 0.5);
		
		return dvt;
	} else {
		throw 2;
	}
}

//CALCULATE THE ROWS OF TABLE
int Table::rowsTable() {
	
	return tableCSV.size();
}

//CALCULATE THE COLUMNS OF TABLE
int Table::columnsTable() {
	
	return tableCSV[0].size();
}

//COUT VALUE OF A CELL
double Table::cellTable(const int unsigned &row, const unsigned int &column) {
	
	if(column < 1 || column > tableCSV[0].size()) {
		throw 2;
	
	} else if(row < 1 || row > tableCSV.size()) {
		throw 3;
	
	} else {
		
		return tableCSV[row-1][column-1];
	}	
}

//CHANGE VALUE OF A CELL
void Table::newValueTable(const unsigned int &row, const unsigned int &column, const double &nv) {
	
	if(column < 1 || column > tableCSV[0].size()) {
		throw 2;
	
	} else if(row < 1 || row > tableCSV.size()) {
		throw 3;
	
	} else {
		tableCSV[row-1][column-1] = nv;
		
	}	
}

//STANDARIZED THE DATA
void Table::standarizedTable() {
	
	double std 	= 0;
	vector<vector<double> > newTableCSV;
	newTableCSV.resize(tableCSV.size());
	
	for(register int i=0; i<tableCSV.size(); i++) {
		for(register int ii=0; ii<tableCSV[i].size(); ii++) {
			std = tableCSV[i][ii] - averageTable(ii+1);
			std = std / deviationTable(ii+1);
			newTableCSV[i].push_back(std);
		}
	}
	tableCSV = newTableCSV;
	
}

//REMOVE ROW OF TABLE
void Table::removeRowTable(const unsigned int &row) {
	
	if(row >= 1 && row <= tableCSV.size()) {
		tableCSV.erase(tableCSV.begin() + row - 1);
	
	} else {
		throw 3;
	
	}
}

//REMOVE COLUMN OF TABLE
void Table::removeColumnTable(const unsigned int &column) {
	
	//CHECK IF "column number" IS VALID
	if(column >= 1 && column <= tableCSV[0].size()) {
		for(register int i=0; i<tableCSV.size(); i++) {
			tableCSV[i].erase(tableCSV[i].begin() + column - 1);
		}
		
	} else {
		throw 2;
		
	}
}

//ADD ROW
void Table::addRowTable(vector<double> &newElements) {
	
	//CHECK IF INPUT VALUES ARE VALID
	if(tableCSV[0].size() == newElements.size()) {
		tableCSV.resize(tableCSV.size() + 1);
		tableCSV[tableCSV.size() - 1].insert(tableCSV[tableCSV.size() - 1].end(), newElements.begin(), newElements.end());
		
	} else {
		throw 4;
		
	}
}

//ADD COLUMN
void Table::addColumnTable(vector<double> &newElements) {
	
	//CHECK IF INPUT VALUES ARE VALID
	if(tableCSV.size() == newElements.size()) {
		for(int i = 0; i < tableCSV.size(); i++) {
			tableCSV[i].push_back(newElements[i]);
		}
		
	} else {
		throw 4;
	
	}
}

//OVERLOAD FOR PRINTING CSV DATA
ostream &operator<<(ostream &stream, Table &tbl) {
 	
	for(register int i=0; i<tbl.tableCSV.size(); i++) {
 		stream << endl << "ROW: " << i + 1 << " (COLUMNS:" << tbl.tableCSV[i].size() << ")" << endl;
 		
 		for(register int ii=0; ii<tbl.tableCSV[i].size(); ii++) {
			stream  << tbl.tableCSV[i][ii] <<' ';
		}
	}
 	return stream;
}
