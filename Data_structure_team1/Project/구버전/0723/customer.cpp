#include "customer.h"
#include <vector>
#include <sstream>
#include <istream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


void PT::set(string trainer, int c) {
	trainer_name = trainer;
	count = c;
}

void customer::print() {
	cout << "id\t:" << id << endl;
	cout << "name\t:" << name << endl;
	cout << "address\t:" << address << endl;
	cout << "phone_number\t :" << phone_num << endl;
	cout << "recommender\t :" << recommender << endl;
	cout << "bday\t:" << bday << endl;
	cout << "product \t :" << product << "개월권" << endl;
	cout << "pt 여부 \t:";
	if (pt == 0)
		cout << " X " << endl;
	else
		cout << " O " << endl;
	cout << "first bmi\t :" << first_bmi << endl;
	cout << "bmi\t :" << bmi << endl;
	cout << "goal_bmi\t :" << goal_bmi << endl;
	cout << "locer_num\t:" << locker_num << endl;
	cout << "attendance\t:" << attendance << endl;
	cout << "assigned_date\t :" << assigned_date << endl;
	cout << "last_date\t :" << lastdate << endl;
	cout << "expiration\t :" << expiration << endl;

	cout << endl;

}
void customer::set(vector<string> row) {
	id = atoi(row[0].c_str());
	name = row[1];
	address = row[2];
	phone_num = row[3];
	recommender = row[4];
	bday = row[5];
	product = atoi(row[6].c_str());

	if (row[7] == "Y") {
		pt = 1;
		training.set(row[8], atoi(row[15].c_str()));
	}
	else
		pt = 0;

	first_bmi = atof(row[9].c_str());
	bmi = atof(row[10].c_str());
	goal_bmi = atof(row[11].c_str());

	locker_num = atoi(row[12].c_str());
	assigned_date = row[13];
	attendance = atoi(row[14].c_str());
	lastdate = row[16];
	expiration = row[17];
}