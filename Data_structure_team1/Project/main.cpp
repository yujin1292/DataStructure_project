#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>

using namespace std;
#include "customer.h"

vector<string> csv_read_row(istream &file, char delimeiter);

int main() {
	ifstream file("info.csv");

	vector<customer> customer_list;
	if (file.fail())
		return (cout << "파일존재x" << endl) && 0;
	vector<string> row = csv_read_row(file, ',');
	while (file.good()) { // file이 끝날때까지 반복
		row = csv_read_row(file, ',');
		if (!row[0].find("#"))
			continue;
		else {
			customer temp;
			temp.set(row);
			customer_list.push_back(temp);			
		}
	}
	file.close();
	cout << "\n============================= 1조 ====================================\n" << endl;
	q01(customer_list);
	q02(customer_list); 
	q05(customer_list);
	q07(customer_list);
	q08(customer_list);
	q11(customer_list);
	q13(customer_list);	
	q16(customer_list);
	q19(customer_list);
	return 0;
}


vector<string> csv_read_row(istream &file, char delimiter) {
	stringstream ss;
	bool inquotes = false;
	vector<string> row;

	while (file.good()) {
		char c = file.get();

		if (!inquotes  &&  c == '"')
			inquotes = true;
		else if (inquotes  &&  c == '"') {
			if (file.peek() == '"')
				ss << (char)file.get();
			else
				inquotes = false;
		}
		else if (!inquotes  &&  c == delimiter) {
			row.push_back(ss.str());
			ss.str("");
		}
		else if (!inquotes && (c == '\r' || c == '\n')) {
			if (file.peek() == '\n')
				file.get();
			row.push_back(ss.str());
			return row;
		}
		else
			ss << c;
	}
}