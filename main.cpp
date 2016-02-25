#include <iostream>
#include <vector>

#ifndef TABLE_H
#include "table.h"
#endif

#ifndef CLASSIFICATION_H
#include "classification.h"
#endif

using namespace std;

//PROTOTYPE
void menu(string cl);

//MAIN
int main() {
	
	int class_choice, choice;
	string errors[] = {
			"",
			"FILE COULD NOT OPENED",
			"COLUMN NUMBER INCORECT",
			"ROW NUMBER INCORECT",
			"YOU ENTER MORE VALUES THAN YOU NEED",
			"COLUMN NUMBER IN LEARNING DATA AND DATA DOES NOT MUCH",
			"ROW NUMBER IN LEARNING DATA AND LEARNING DATA LABELS DOES NOT MUCH",
			"LEARNING DATA LABELS HAS MORE THAN ONE COLUMN",
			"NUMBER INSERTED (K) IS LARGER THAN ROWS IN LEARNING DATA OR NUMBER INSERTED (K)  IS NOT POSITIVE",
			"DATA LABELS AND CORRECT DATA LABELS ARE DIFFERENT SIZE"
	
	};
	
	//START MAIN MENU
	do {
		
		menu("m");
		cin >> class_choice;
		
		if(class_choice == 1) {
		
			//DECLARE VARIABLES CLASS TABLE
			vector<double> newElements;
			unsigned int x, y; //x stands for row, y stands for column
			double new_val;
			
			
			//THROW AN EXCEPTION FROM CLASS/FUNCTIONS
			try{
				
				//CREATE AN INSTANCE OF CLASS Table & READ CSV
				cout << "Reading CSV file...";
				Table tbl("files/Data.csv");
				
				//MENU AND REPEAT LOOP FOR MULTIPLE TESTING
				do {
					menu("t");
					cin >> choice;
					switch(choice) {
						
						//EXIT
						case 0:
						cout 	<< "End of Class Table!! \n";
						break;
						
						//AVERAGE
						case 1:
						cout 	<< "Give column number to calculate average: ";
						cin 	>> y;
						cout 	<< "Average: " << tbl.averageTable(y);
						break;
						
						//GET THE CORRECTED STANDAR DEVIATION
						case 2:
					 	cout 	<< "Give column number to calculate standard deviation: ";
						cin 	>> y;
						cout 	<< "Standard Deviation: " << tbl.deviationTable(y);
						break;
						
						//GET NUMBER OF ROWS OF THE TABLE
						case 3:
						cout 	<< "Total rows of table: " << tbl.rowsTable();
						break;
						
						//GET NUMBER OF COLUMNS OF THE TABLE
						case 4:
						cout 	<< "Total columns of table: " << tbl.columnsTable();
						break;
						
						//GET THE VALUE OF CERTAIN CELL
						case 5:
					 	cout 	<< "Give coordinates x and y of cell, to show value: \n";
						cout 	<< "ROW: ";
						cin 	>> x;
						cout 	<< "COLUMN: ";
						cin 	>> y;
						cout 	<< "Value of cell: " << tbl.cellTable(x, y); 
						break;
						
						//CHANGE THE VALUE OF CERTAIN CELL
						case 6:
					 	cout 	<< "Give coordinates x and y of cell, to change value: \n";
						cout 	<< "ROW: ";
						cin 	>> x;
						cout 	<< "COLUMN: ";
						cin 	>> y;
						cout 	<< "New value of cell: ";
						cin 	>> new_val;
						tbl.newValueTable(x, y, new_val);
						cout << "Value has been changed";
						break;
						
						//STANDARIZED THE DATA
						case 7:
					 	cout 	<< "Standarization begin... \n";
						tbl.standarizedTable();
					 	cout 	<< "Standarization finish. \n";
						break;
						
						//REMOVE A ROW
						case 8:
					 	cout 	<< "Give row to delete: ";
					 	cin 	>> x;
					 	tbl.removeRowTable(x); 
					 	cout 	<< "Row deleted";
						break;
						
						//REMOVE A COLUMN
						case 9:
						cout 	<< "Give column to delete: ";
					 	cin 	>> y;
					 	tbl.removeColumnTable(y);
					 	cout << "Column deleted";
						break;
						
						//ADD A ROW
						case 10:
						cout 	<< "Give " << tbl.columnsTable() << " values for the new row:\n";
						newElements.clear();
						for(int i = 0; i < tbl.columnsTable(); i++) {
							cout 	<< "Enter " << i + 1 << " value: ";
							if(cin >> new_val) {
								newElements.push_back(new_val);
							} else {
								cin.clear();
					 			cin.ignore();
								cout << "Wrong input. Try again. \n";
							}
						}
						tbl.addRowTable(newElements);
						cout 	<< "Row added successfully! ";
						break;
						
						//ADD A COLUMN
						case 11:
						cout 	<< "Give " << tbl.rowsTable() << " values for the new column:\n";
						newElements.clear();
						for(int i = 0; i < tbl.rowsTable(); i++) {
							cout 	<< "Enter " << i + 1 << " value: ";	
							if(cin >> new_val) {
								newElements.push_back(new_val);	
							} else {
								cin.clear();
					 			cin.ignore();
								cout << "Wrong input. Try again. \n";
							}
						}
						tbl.addColumnTable(newElements);
						cout 	<< "Column added successfully! ";
						break;
						
						//OVERLOADING FOR PRINTING TABLE
						case 12:
						cout 	<< tbl;
						break;
						
						//ENTER WRONG CHOICE
						default:
						cout 	<< "You entered something else! Try again!";
					}
				
				} while(choice != 0);
			
			} catch (int i){
				cout << endl << "ERROR " << i << ": " << errors[i] << endl << endl;
			}
	
			
		} else if(class_choice == 2) {
			//THROW AN EXCEPTION FROM FUNCTION
			try{
				
				//CREATE AN INSTANCES OF CLASS Table
				cout << "Reading CSV files... \n";
				Table d_obj("files/Data.csv");
				Table ld_obj("files/Learning_Data.csv");
				Table ldl_obj("files/Learning_Data_Labels.csv");
				Table cdl_obj("files/Correct_Data_Labels.csv");
				
				//DECLARE VARIABLES CLASS CLASSIFICATION
				unsigned int K;
				vector<vector<double> > dl;
				
				cout << "Give me a positive insteger: ";
				do {
					cin >> K;
					if(K <= 0) {
						cout << "Please enter a positive integer number";
					}
				} while(K <= 0);
				
				//CREATE AN INSTANCE OF CLASS Classification AND VERIFY TABLES
				Classification cls(ld_obj, ldl_obj, d_obj, K);
				
				//MENU AND REPEAT LOOP
				do {
					menu("c");
					cin >> choice;
					switch(choice) {
						
						//EXIT
						case 0:
						cout 	<< "End of Class Classification!! \n";
						break;
						
						//CLASSIFICATION
						case 1:
						cout 	<< "Starting Tables Classification... \n";
						dl = cls.classificationTable();
						cout 	<< "End of Tables Classification. \n";
						break;
						
						//ACCURACY
						case 2:
						cout 	<< "Accuracy: " << cls.accuracy(dl, cdl_obj.getTable()) << "%";
						break;
						
						//PRINT TABLES
						case 3:
						cout << "\n\n Data \n";
						cout << d_obj;
						cout << "\n\n Learning_Data \n";
						cout << ld_obj;
						cout << "\n\n Learning_Data_Labels \n";
						cout << ldl_obj;
						cout << "\n\n Correct_Data_Labels \n";
						cout << cdl_obj;
						break;
						
						//ENTER WRONG CHOICE
						default:
						cout 	<< "You entered something else! Try again! \n";
					}
					
					
				} while(choice != 0);
			
			} catch (int i){
				cout << endl << "ERROR " << i << ": " << errors[i] << endl;
			}
		} else {
			cout 	<< "You entered something else! Try again! \n";
			
		}
	} while(class_choice != 0);
	
 	return 0;
}


//MENU
void menu(string cl) {
	
	//MAIN MENU
	if(cl == "m") {
		cout << endl << "\n ========================-MAIN MENU-============================== \n";
		cout << "What class do you want to test? \n";
		cout << "1. Class Table \n";
		cout << "2. Class Classification \n";
		cout << "0. EXIT";
		cout << endl << "\n ================================================================ \n";
		cout << "OPTION: ";
		
	//MENU CLASS TABLE
	} else if(cl == "t") {
		
		cout << endl << "\n ========================-TABLE MENU-============================= \n";
		cout << "\n PLEASE CHOOSE AN OPTION \n";
		cout << "1.  GET THE AVERAGE OF A COLUMN \n";
		cout << "2.  GET THE CORRECTED SAMPLE STANDARD DEVIATION OF A COLUMN \n";
		cout << "3.  GET THE NUMBER OF ROWS \n";
		cout << "4.  GET THE NUMBER OF COLUMNS \n";
		cout << "5.  GET THE VALUE OF SPECIFIC CELL \n";
		cout << "6.  CHANGE THE VALUE OF SPECIFIC CELL\n";
		cout << "7.  STANDARDISE THE DATA \n";
		cout << "8.  REMOVE A SPECIFIC ROW \n";
		cout << "9.  REMOVE A SPECIFIC COLUMN\n";
		cout << "10. ADD A ROW \n";
		cout << "11. ADD A COLUMN \n";
		cout << "12. PRINT TABLE (USING OVERLOAD <<)\n";
		cout << "0.  RETURN TO MAIN MENU ";
		cout << endl << "\n ================================================================ \n";
		cout << "OPTION: ";
		
	//MENU CLASS CLASSIFICATION
	} else if(cl == "c") {
		
		cout << endl << "\n ====================-CLASSIFICATION MENU-======================== \n";
		cout << "\n PLEASE CHOOSE AN OPTION \n";
		cout << "1.  CLASSIFICATION \n";
		cout << "2.  ACCURACY \n";
		cout << "3.  PRINT TABLES \n";
		cout << "0.  RETURN TO MAIN MENU ";
		cout << endl << "\n ================================================================ \n";
		cout << "OPTION: ";
		
	}
}

