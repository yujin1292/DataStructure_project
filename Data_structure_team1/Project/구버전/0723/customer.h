#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>

using namespace std;

class PT {
public:
	string trainer_name;
	int count;

	void set(string trainer, int c);
};

class customer {
public:
	int id;
	string name;
	string address;
	string phone_num;
	string recommender;
	string  bday;
	int product;

	PT training;
	int pt;

	double first_bmi;
	double bmi;
	double goal_bmi;

	int locker_num;
	int attendance;

	string assigned_date;
	string lastdate;
	string expiration;

	void print();
	void set(vector<string> row);
};

class trainer {
public:
	char* name;

	int num_student;
	int *students_id;
};