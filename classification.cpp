#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "table.h"
#include "classification.h"

//CONSTRUCTOR
Classification::Classification(Table& ld, Table& ldl, Table& d, unsigned int k) {
	
	verifyTable(ld, ldl, d, k);
}

//DESTRUCTOR
Classification::~Classification() {
	
}

//VERIFY TABLES
void Classification::verifyTable(Table& ld, Table& ldl, Table& d, unsigned int k) {
	
	//CHECK COLUMNS "learning data" AND "data"
	if(ld.columnsTable() != d.columnsTable()) {
		throw 5;
		
	//CHECK ROWS "learning data" AND "learning data labels"
	} else if(ld.rowsTable() != ldl.rowsTable()) {
		throw 6;
		
	//CHECK IF "learning data labels" HAS MORE THAN ONE COLUMNS
	} else if(ldl.columnsTable() != 1) {
		throw 7;
		
	//CHECK VALUE OF "k" IS BIGGER THAN "learning data" ROWS
	} else if(k > ld.rowsTable() || k <=0 ) {
		throw 8;
	
	//SET THE PRIVATE VARIABLES
	} else {
		learning_data 			= ld.getTable();
		learning_data_labels 	= ldl.getTable();
		data 					= d.getTable();
		key 					= k;
	
	}
}

//CLASSIFICATION TABLES
vector<vector<double> > Classification::classificationTable() {
	
	vector<vector<double> > data_labels;
	vector<double> distances;
	vector<int> rows;
	int temp1;
	double temp2;
	
	//FOR EACH ROW IN "DATA" | STEP A
	for(int i=0; i<data.size(); i++) {
		//EMPTY THE CONTENTS OF DISTANCES AND ROWS
		rows.clear();
		distances.clear();
		
		//FOR EACH ROW IN "LEARNING_DATA"
		for(int ii=0; ii<learning_data.size(); ii++) {
			distances.push_back(euclidean(data[i], learning_data[ii]));
			rows.push_back(ii);
		}
		
		//SORTING THE DISTANCES USING BUBBLE SORT
		for(int ii=1; ii<distances.size(); ii++) {
			for(int j=distances.size()-1; j>=ii; j--) {
				if(distances[j] < distances[j-1]) {
					temp2 			= distances[j];
					distances[j] 	= distances[j-1];
					distances[j-1] 	= temp2;
					
					temp1 			= rows[j];
					rows[j] 		= rows[j-1];
					rows[j-1] 		= temp1;	
				}
			}
		}
		
		//KEEP ONLY THE key ELEMENTS OF ROWS - LEARNING DATA
		rows.erase (rows.begin()+key, rows.end());
		
		//STEP B
		vector<double> ldl_values;
		for(int ii=0; ii<rows.size(); ii++) {
			ldl_values.push_back(learning_data_labels[rows[ii]][0]);	
		}
		
		//STEP C
		double max_val_lbl 	= ldl_values[0];
		int times 			= count(ldl_values.begin(), ldl_values.end(), ldl_values[0]);
		int max_lbl 		= times;
		
		for(int ii=1; ii<ldl_values.size(); ii++) {
			//FIND MAX
			times = count(ldl_values.begin(), ldl_values.end(), ldl_values[ii]);
			if(times > max_lbl){
				max_val_lbl = ldl_values[ii];
				max_lbl 	= times;
				
			//IF MAX EQUAL, CHOOSE RANDOM
			} else if (times == max_lbl && ldl_values[ii] != max_val_lbl && rand() % 2 == 1) {
				max_val_lbl = ldl_values[ii];
				
			}
		}
		
		//STEP D
		data_labels.resize(i + 1);
		data_labels[i].push_back(double(max_val_lbl));
		
	}
	
	return data_labels;
}

//EUCLIDEAN DISTANCE
double Classification::euclidean(vector<double> &data_row, vector<double> &learning_data_row) {
	
	double dis = 0;
	
	for(int j=0; j<data_row.size(); j++) {
		dis += pow((data_row[j] - learning_data_row[j]), 2);
	}
	
	return pow(dis, 0.5);
}

//ACCURACY
double Classification::accuracy(vector<vector<double> > data_labels, vector<vector<double> > correct_data_labels) {
	
	if(data_labels.size() != correct_data_labels.size()) {
		throw 9;
	}
	
	int sum = 0;
	for(int i=0; i<data_labels.size(); i++) {
		if(data_labels[i][0] == correct_data_labels[i][0]) {
		 	sum ++;
		 }
	}	
	
	return (100*sum)/data_labels.size();
}
