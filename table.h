#ifndef TABLE_H
#define TABLE_H

using namespace std;

//CLASS TABLE
class Table {
	
	private:
		
		//DECLARE PRIVATE VARIABLES
		vector<vector<double> > tableCSV;
		
		//READ CSV
		void setTable(string path);	
	
	public:
		
		//CONSTRUCTOR && CREATING TABLE FROM CSV
		Table(string path);
		
		//DESTRUCTOR
		~Table();
		
		//GET CSV
		vector<vector<double> > getTable();
		
		//CALCULATE THE AVERAGE
		double averageTable(const unsigned int &column);
		
		//CALCULATE THE DEVIATION
		double deviationTable(const unsigned int &column);
		
		//CALCULATE THE ROWS OF TABLE
		int rowsTable();
		
		//CALCULATE THE COLUMNS OF TABLE
		int columnsTable();
		
		//COUT VALUE OF A CELL
		double cellTable(const unsigned int &row, const unsigned int &column);
		
		//CHANGE VALUE OF A CELL
		void newValueTable(const unsigned int &row, const unsigned int &column, const double &nv);
		
		//STANDARIZED THE DATA
		void standarizedTable();
		
		//REMOVE ROW OF TABLE
		void removeRowTable(const unsigned int &row);
		
		//REMOVE COLUMN OF TABLE
		void removeColumnTable(const unsigned int &column);
		
		//ADD ROW
		void addRowTable(vector<double> &newElements);
		
		//ADD COLUMN
		void addColumnTable(vector<double> &newElements);
		
		//OVERLOAD FOR PRINTING CSV TABLE
		friend ostream &operator<<(ostream &stream, Table &tbl);		
};

#endif
