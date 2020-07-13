#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>
#include <map>

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
	string name;

	int num_student;
	
};

void print_all(vector<customer> customer_list);
void q01(vector<customer> customer_list);
void q05(vector<customer> customer_list);
void q08(vector<customer> customer_list);
void q13(vector<customer> customer_list);
void q19(vector<customer> customer_list);
void q02(vector<customer> customer_list);
void q16(vector<customer> customer_list);
void q07(vector<customer> customer_list);
void q11(vector<customer> customer_list);

map<int, int> registration_rate(vector<customer> customer_list, int return_attribute);
vector<pair<int, double>> attainment_rate(vector<customer> customer_list, int return_attribute = 1);
vector<pair<string, double>> best_training_performance(vector<customer> customer_list);
vector<pair<int, int>> quick_termination(vector<customer> customer_list);
vector<pair<int,int>> latest_attendance(vector<customer> customer_list);
