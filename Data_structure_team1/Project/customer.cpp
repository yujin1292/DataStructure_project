#include "customer.h"
#include <vector>
#include <sstream>
#include <istream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <map>
#include <set>
#pragma warning(disable:4996)
#pragma warning(disable:4018)

using namespace std;


void PT::set(string trainer, int c) {
	trainer_name = trainer;
	count = c;
}
void customer::print() {
	cout << "id\t:" << id << endl;
	cout << "name\t:" << name << endl;
	cout << "locer_num\t:" << locker_num << endl;
	cout << "address\t:" << address << endl;
	cout << "phone_number\t :" << phone_num << endl;
	cout << "recommender\t :" <<recommender << endl;
	cout << "bday\t:" << bday << endl;
	cout << "product \t :" << product <<"������"<< endl;
	cout << "pt ���� \t:";
	if (pt == 0)
		cout << " X " << endl;
	else
		cout << " O " << endl;
	cout << endl;
	cout << "first bmi\t :" << first_bmi << endl;
	cout << "last bmi\t :" << bmi << endl;
	cout << "goal_bmi\t :" << goal_bmi << endl;
	cout << endl;
	cout << "attendance\t:" << attendance << endl;
	cout << "assigned_date\t :" << assigned_date << endl;
	cout << "last_date\t :" << lastdate << endl;
	cout << "expiration\t :" <<expiration << endl;

	cout << endl;

}
void customer::set(vector<string> row) {
	id = atoi(row[0].c_str());
	name = row[1];
	address =row[2];
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



map<int, int*> assigned;
set<int> year;

void print_all(vector<customer> customer_list) {
	for (int i = 0; i < customer_list.size(); i++) //ȸ�� ���� ���
		customer_list[i].print();
}
void q01(vector<customer> customer_list) {
	cout << "01. ���� ȸ���� ���� Ȯ���� Ʈ���̳ʴ�?" << endl << endl;
	vector <customer> ptcu;  //ptȸ�� ������ ����
	vector <trainer> trainer_list;


	//pt�� �޴� customer ����
	for (int i = 0; i < customer_list.size(); i++) {
		if (customer_list[i].pt == 1) {
			ptcu.push_back(customer_list[i]);
		}
	}

	int check;
	// ��Ż Ʈ���̳� ����?
	for (int k = 1; k < ptcu.size(); k++) {
		check = 1;
		for (int i = 0; i < trainer_list.size(); i++) {
			if (trainer_list[i].name == ptcu[k].training.trainer_name)
				check = 0;
		}
		if (check) {
			trainer temp;
			temp.name = ptcu[k].training.trainer_name;
			temp.num_student = 0;
			trainer_list.push_back(temp);
		}
	}

	//pt ȸ�� Ȯ���ϸ鼭 �л��� ++ ��Ŵ
	for (int p = 0; p < ptcu.size(); p++) {
		for (int j = 0; j < trainer_list.size(); j++) {
			if (ptcu[p].training.trainer_name == trainer_list[j].name) {
				trainer_list[j].num_student++;
			}
		}
	}

	//find max
	int max = 0;
	for (int o = 0; o < trainer_list.size(); o++) {
		if (trainer_list[o].num_student > max) {
			max = trainer_list[o].num_student;
		}
	}

	for (int o = 0; o < trainer_list.size(); o++) {
		if (trainer_list[o].num_student == max) {
			cout << trainer_list[o].name << " Ʈ���̳ʰ� ȸ���� ���� ���� (" << max << "��) �����߽��ϴ�." << endl;
		}
	}
	cout << "\n--------------------------------------------------------------------" << endl<<endl;
}
void q02(vector<customer> customer_list)
{
	vector<pair<string, double>> list = best_training_performance(customer_list);

	cout << "02. �Ʒ� ������ ���� ���� Ʈ���̳ʴ�?" << endl << endl;

	for (int i = 0; i < list.size(); i++)
		cout << "�̸� : " << list[i].first << ", �Ʒ� ���� : " << list[i].second << "%" << endl;

	cout << "\n--------------------------------------------------------------------" << endl << endl;
}
void q05(vector<customer> customer_list) {

	cout << "05. ���� ����� ���� / ���� ���� ?" << endl << endl;
	
	//�⵵�� ����.
	
	for (int i = 0; i < customer_list.size(); i++) {
		int y = (customer_list[i].assigned_date[2]-'0') * 10 +
			(customer_list[i].assigned_date[3]-'0');
		year.insert(y);
	}

	//�ʱ�ȭ 
	set<int>::iterator iter;
	for (iter = year.begin(); iter != year.end(); ++iter) {
		int temp = *iter;
		int* list = (int*)malloc(sizeof(int) * 12);
		for (int i = 0; i < 12; i++)
			list[i] = 0;
		assigned[temp] = list;
	}

	time_t t = time(nullptr);
	tm tm;
	
	localtime_s(&tm, &t);

	int this_year = tm.tm_year + 1900 - 2000;
	int this_month = tm.tm_mon + 1;

	//��ϼ� count 
	for (int i = 0; i < customer_list.size(); i++) {
		int y = (customer_list[i].assigned_date[2] - '0') * 10 + (customer_list[i].assigned_date[3] - '0');
		int m = (customer_list[i].assigned_date[7] - '0') * 10 + (customer_list[i].assigned_date[8] - '0');
		assigned[y][m-1] ++;
	}

	//min max ã�Ƽ� ���
	for (iter = year.begin(); iter != year.end(); ++iter) {
		int max = 0;
		int min = 9999;
		int max_month, min_month;
		cout <<"[20"<< *iter << "�� �����Ȳ]" << endl;
		cout << "______________________________________________________________________________________________" << endl;
		cout << "01\t02\t03\t04\t05\t06\t07\t08\t09\t10\t11\t12" << endl;
		cout << "______________________________________________________________________________________________" << endl;
		for (int i = 0; i < 12; i++) {
			//printf("%d %d | %d \n", *iter, i,min);
			if (max < assigned[*iter][i])
				max = assigned[*iter][i];
			if (min > assigned[*iter][i]) {
				if (*iter != this_year || this_month > i) {
					min = assigned[*iter][i];
				}
			}

			cout <<  assigned[*iter][i] << "\t";
		}
		cout << endl<<"______________________________________________________________________________________________" << endl;
		cout << endl;
		cout <<"20"<< *iter <<"�⵵�� ���� ����� ���� ���� ";
		for (int i = 0; i < 12; i++) {
			if (max == assigned[*iter][i])
				cout << i + 1 << "�� ";
		}
		cout << "�Դϴ�." << endl;


		cout << "���� ����� ���� ���� ";
		for (int i = 0; i < 12; i++) {
			
			if (min == assigned[*iter][i])
				cout << i + 1 << "�� ";
		}
		cout << "�Դϴ�." << endl << endl<<endl;
	}

	cout << "\n--------------------------------------------------------------------" << endl << endl;

}
void q07(vector<customer> customer_list)
{
	vector<pair<int, int>> list = quick_termination(customer_list);

	cout << "07. ���� ��ǰ�� ���� ����� �ð� ���� �����ϴ� ȸ����?" << endl << endl;

	for (int i = 0; i < list.size(); i++)
	{
		customer_list[list[i].first - 1].print();
		cout << "<���� ���� : " << list[i].second << "��>" << endl<<endl;
	}

	cout << "\n--------------------------------------------------------------------" << endl << endl;
}
void q08(vector<customer> customer_list) {

	time_t t = time(nullptr);
	tm tm;
	localtime_s(&tm, &t);


	cout << "8. ���⵵ ���� ��� ���� ��Ϸ��� �������� ���� ?" << endl<<endl;

	int this_year;
	int this_month = tm.tm_mon - 1;

	map<int,double*> month_assigned;

	set<int>::iterator iter;
	for (iter = year.begin(); iter != year.end(); ++iter) {
		int temp = *iter;
		double* list = (double*)malloc(sizeof(double) * 12);
		for (int i = 0; i < 12; i++)
			list[i] = 0;
		month_assigned[temp] = list;
	}
	
	int last_year = 0;
	for (iter = year.begin(); iter != year.end(); ++iter) {
	
		this_year = *iter;
		for (int i = 0; i < 12; i++) {
			if (i == 0) {
				//�۳� ����� �ִ��� üũ ������ last_year = 1
				set<int>::iterator iter2;
				int last_year = 0;
				for (iter2 = year.begin(); iter2 != year.end(); ++iter2) {
					if (*iter2 == *iter - 1)
						last_year = 1;
				}


				if (last_year) { //�۳� ��� ����
					if (assigned[this_year - 1][11] != 0)
						month_assigned[*iter][0] = (double)assigned[this_year][0] / assigned[*iter- 1][11] * 100;
					else
						month_assigned[*iter][0] = (double)assigned[this_year][0] * 100;
				}
				else
					month_assigned[*iter][0] = -1;

			}
			else {
				if (assigned[this_year][i - 1] == 0)
					month_assigned[*iter][i] =(double)assigned[*iter][i] * 100;
				else
					month_assigned[*iter][i] = (double)assigned[*iter][i] / assigned[*iter][i - 1] * 100;
			}
		}
	}



	for (iter = year.begin(); iter != year.end(); ++iter) {

		double max = 0;
		double min = 9999;
		int max_month, min_month;
		cout << "[20" << *iter << "�� ��Ϸ� ��Ȳ]" << endl;
		cout << "______________________________________________________________________________________________" << endl;
		cout << "01\t02\t03\t04\t05\t06\t07\t08\t09\t10\t11\t12" << endl;
		cout << "______________________________________________________________________________________________" << endl;
		for (int i = 0; i < 12; i++) {
			if (max < month_assigned[*iter][i])
				max = month_assigned[*iter][i];

			if (min > month_assigned[*iter][i]) {
				if (*iter != this_year || this_month > i) {
					min = month_assigned[*iter][i];
				}
			}

			cout << month_assigned[*iter][i] << "\t";
		}
		cout << endl << "______________________________________________________________________________________________" << endl;
		cout << endl;
		cout << "20" << *iter << "�⵵�� ���� ��Ϸ��� ���� ���� ";
		for (int i = 0; i < 12; i++) {
			if (max == month_assigned[*iter][i])
				cout << i + 1 << "�� ";
		}
		cout << "�Դϴ�." << endl;

		cout << "���� ��Ϸ��� ���� ���� ";
		for (int i = 0; i < 12; i++) {
			if (min == month_assigned[*iter][i])
				cout << i + 1 << "�� ";
		}
		cout << "�Դϴ�." << endl << endl << endl;
	}
}
void q11(vector<customer> customer_list) {
	cout << "11. PT�� �޴� ȸ�� �߿� ��Ŀ�� ������� �ʴ� ȸ����?" << endl << endl;
	for (int i = 0; i < customer_list.size(); i++)
		if (customer_list[i].pt == 1 && customer_list[i].locker_num == NULL)
			customer_list[i].print();
	cout << "\n--------------------------------------------------------------------" << endl << endl;
}
void q13(vector<customer> customer_list) {

	vector<pair<int, int>> list = latest_attendance(customer_list);

	cout << "13. ���� �������� ���� ���� ȸ����?" << endl << endl;

	for (int i = 0; i < list.size(); i++)
	{
		customer_list[list[i].first - 1].print();
		cout << "<���������� �� �� : " << list[i].second << "�� ��>" << endl << endl;
	}

	cout << "\n--------------------------------------------------------------------" << endl << endl;
}
void q16(vector<customer> customer_list)
{
	vector<pair<int, double>> list = attainment_rate(customer_list);

	cout << "16. � �޼����� ���� ����/���� ȸ����?" << endl << endl;

	for (int i = 0; i < list.size(); i++)
	{
		customer_list[list[i].first - 1].print();
		cout << "�޼��� : " << list[i].second << "%" << endl;
	}

	cout << endl;

	list = attainment_rate(customer_list, -1);

	for (int i = 0; i < list.size(); i++)
	{
		customer_list[list[i].first - 1].print();
		cout << "�޼��� : " << list[i].second << "%" << endl;
	}

	cout << "\n--------------------------------------------------------------------" << endl << endl;
}
void q19(vector<customer> customer_list) {
	cout << "19. PT�� ���� ���� / �����̿��ϴ� ���ɴ�� ? " << endl << endl;
	
	time_t t = time(nullptr);
	tm tm;

	localtime_s(&tm, &t);

	int age_group[10] = { 0 };
	for (int i = 0; i < customer_list.size(); i++) {
		char * year = (char*)malloc(sizeof(char)*10);
		int age;
		localtime_s(&tm, &t);
		customer_list[i].bday.copy(year,2);
		if (0 <= atoi(year) && atoi(year) <= 19) 
			age = tm.tm_year + 1900 - (2000 + atoi(year)) + 1;
		else
			age = tm.tm_year + 1900 - (1900 + atoi(year)) + 1;
		age_group[age / 10] ++;
	}

	int max = 0;
	int min = 400;


	for (int i = 0; i < 10; i++) {
		if (max < age_group[i]) {
			max = age_group[i];
		}
		if (min > age_group[i] && age_group[i] != 0) {
			min = age_group[i];
		}
	}	
	
	
	cout << "���� ���� �̿��ϴ� ���ɴ�� ";
	for(int i = 0 ; i< 10 ; i++){
		if (age_group[i] == max) {

			if (i == 0)
				cout << "���(10���̸�) " << "(" << max << "��)";
			else
				cout << i * 10 << "�� " << "(" << max << "��)";
		}
	}
	cout << "�̰� " << endl;
	cout << "(�̿�����) ���� ���� �̿��ϴ� ���ɴ�� ";
	for (int i = 0; i < 10; i++) {

		if (age_group[i] == min) {
			if (i == 0)
				cout << "���(10���̸�) " << "(" << min << "��)";
			else
				cout << i * 10 << "�� " << "(" << min << "��)";
		}
	}
	cout <<"�Դϴ�." << endl;

	cout << "[�̿����� �ʴ� ���ɴ�� ";
	for (int i = 0; i < 9; i++) {
		if (age_group[i] == 0) {
			if (i == 0)
				cout << "���(10���̸�) ,";
			else
				cout << i * 10 << "�� ";

		}
	}
	cout << "�Դϴ�.]" << endl;

	cout << "\n--------------------------------------------------------------------" << endl<<endl;
}


//���� ����� ����/���� �� �Լ�
//ù��° �μ��� ȸ�� ����Ʈ, �ι�° ���Ҵ� ����� ���� ����
//1~12 : �Է��� ����ŭ �������� ���, -1~-12 : �Է��� ����ŭ �������� ���
map<int, int> registration_rate(vector<customer> customer_list, int return_attribute)
{
	map<int, int> month_list;
	map<int, int>::iterator ITER;
	char str[3];
	int aoc, max;

	if (return_attribute > 12)
		return_attribute = 12;
	else if (return_attribute < -12)
		return_attribute = -12;

	for (int i = 1; i < 13; i++)
		month_list[i] = 0;


	for (int i = 0; i < customer_list.size(); i++)
	{
		int j = customer_list[i].assigned_date.find_first_of(' ');
		str[0] = customer_list[i].assigned_date[j + 1];
		str[1] = customer_list[i].assigned_date[j + 2];
		str[2] = '\0';

		month_list.find(atoi(str))->second += 1;
	}

	map<int, int> return_list = month_list;

	if (return_attribute > 0)
	{
		aoc = 1;
		max = 0;
	}
	else
	{
		aoc = -1;
		max = customer_list.size();
	}

	for (int i = 0; i != return_attribute; i += aoc)
	{
		for (map<int, int>::iterator iter = month_list.begin(); iter != month_list.end(); iter++)
		{
			if (aoc == -1)
			{
				if (iter->second < max)
				{
					max = iter->second;
					ITER = iter;
				}
			}
			else
			{
				if (iter->second > max)
				{
					max = iter->second;
					ITER = iter;
				}
			}
		}
		cout << ITER->first << "�� : " << ITER->second << "ȸ" << endl;
		month_list.erase(ITER);
		if (aoc == -1)
			max = customer_list.size();
		else
			max = 0;
	}

	return return_list;
}

//� �޼��� ����/���� ȸ�� ���ϴ� �Լ�
//ù ��° �μ��� ȸ�� ����Ʈ, �� ��° �μ��� 1�� ������ ���� ȸ��, -1�� ������ ���� ȸ��, default�� 1
//��ȯ���� ȸ���� id�� ���� ����
vector<pair<int, double>> attainment_rate(vector<customer> customer_list, int return_attribute)
{
	vector<pair<int, double>> list;
	vector<double> ratelist;
	double max;
	double rate;

	if (return_attribute == 1)
		max = -1000.0;
	else if (return_attribute == -1)
		max = 1000.0;
	else
	{
		return_attribute = 1;
		max = -1000.0;
	}

	for (int i = 0; i < customer_list.size(); i++)
	{
		if (customer_list[i].first_bmi == customer_list[i].goal_bmi)
		{
			if (customer_list[i].goal_bmi == customer_list[i].first_bmi)
				rate = 1;
			else
				rate = 0;
		}
		else
		{
			rate = (customer_list[i].bmi - customer_list[i].first_bmi)
				/ (customer_list[i].goal_bmi - customer_list[i].first_bmi);
		}

		if (return_attribute == 1)
		{
			if (max < rate)
				max = rate;
		}
		else if (return_attribute == -1)
		{
			if (max > rate)
				max = rate;
		}
		ratelist.push_back(rate);
	}

	for (int i = 0; i < customer_list.size(); i++)
	{
		if (max == ratelist[i])
			list.push_back(pair<int, double>(customer_list[i].id, ratelist[i] * 100));
	}
	return list;
}

//�Ʒ� ������ ���� ���� Ʈ���̳ʸ� ����ϴ� �Լ�
//ù �μ��� ȸ�� ����Ʈ, ��ȯ���� Ʈ���̳� �̸��� ���� ����
vector<pair<string, double>> best_training_performance(vector<customer> customer_list)
{
	map<string, pair<double, int>> train_per;
	map<string, pair<double, int>>::iterator temp;
	vector<pair<string, double>> rtv;
	double max = -1000.0, dtemp;

	for (int i = 0; i < customer_list.size(); i++)
	{
		if (customer_list[i].pt != 1)
			continue;

		temp = train_per.find(customer_list[i].training.trainer_name);
		if (temp == train_per.end())
		{
			train_per[customer_list[i].training.trainer_name]
				= pair<double, int>((customer_list[i].bmi - customer_list[i].first_bmi) / (customer_list[i].goal_bmi - customer_list[i].first_bmi), 1);
		}
		else
		{

			dtemp = (customer_list[i].bmi - customer_list[i].first_bmi) / (customer_list[i].goal_bmi - customer_list[i].first_bmi)
				/ (temp->second.second + 1);
			temp->second.first = temp->second.first * (temp->second.second / (temp->second.second + 1));
			temp->second.first += dtemp;
			temp->second.second++;
		}
	}

	for (temp = train_per.begin(); temp != train_per.end(); temp++)
	{
		if (temp->second.first > max)
			max = temp->second.first;
	}

	for (temp = train_per.begin(); temp != train_per.end(); temp++)
	{
		if (max == temp->second.first)
		{
			rtv.push_back(pair<string, double>(temp->first, temp->second.first * 100));
		}
	}
	return rtv;
}

int mon_day(int mon, int year)
{
	switch (mon)
	{
	case 1: case 3: case 4: case 7: case 8: case 10: case 12:
		return 31;
	case 2:
		if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))
			return 29;
		else
			return 28;
	default:
		return 30;
	}
}

//���� ����� �ð� ���� ���� ��ǰ�� ����Ǵ� ȸ���� ���ϴ� �Լ�
//ù �μ��� ȸ�� ����Ʈ. ��ȯ���� ȸ���� id�� ���� �ϼ��� ���� ����
vector<pair<int, int>> quick_termination(vector<customer> customer_list)
{
	vector<int> CuexTime;
	vector<pair<int, int>> list;
	time_t* Time = new time_t;
	tm *T_st = new tm;
	string Timestr;
	int Cuexy, Cuexm, Cuexd, RemainT = -1, min = INT_MAX;

	time(Time);
	T_st = gmtime(Time);

	for (int i = 0; i < customer_list.size(); i++)
	{
		Timestr = customer_list[i].expiration;

		T_st = gmtime(Time);
		RemainT = -1;

		Cuexy =
			(Timestr[0] - '0') * 1000 +
			(Timestr[1] - '0') * 100 +
			(Timestr[2] - '0') * 10 +
			(Timestr[3] - '0') - 1900;
		Cuexm =
			(Timestr[7] - '0') * 10 +
			(Timestr[8] - '0') - 1;
		Cuexd =
			(Timestr[12] - '0') * 10 +
			(Timestr[13] - '0');

		if (T_st->tm_year < Cuexy)
		{
			RemainT = (mon_day(T_st->tm_mon + 1, T_st->tm_year + 1900) - T_st->tm_mday);
			T_st->tm_mon++;
			T_st->tm_mday = 1;
			while (T_st->tm_mon < 12)
			{
				RemainT += (mon_day(T_st->tm_mon + 1, T_st->tm_year + 1900));
				T_st->tm_mon++;
			}
			T_st->tm_year++;
			T_st->tm_mon = 0;

			while (T_st->tm_year < Cuexy)
			{
				if (((T_st->tm_year + 1900) % 4 == 0) && ((T_st->tm_year + 1900) % 100 != 0) || ((T_st->tm_year + 1900) % 400 == 0))
					RemainT += 366;
				else
					RemainT += 365;
				T_st->tm_year++;
			}

			while (T_st->tm_mon < Cuexm)
			{
				RemainT += mon_day(T_st->tm_mon + 1, T_st->tm_year + 1900);
				T_st->tm_mon++;
			}
			RemainT += Cuexd;
		}
		else if (T_st->tm_year == Cuexy)
		{
			if (T_st->tm_mon <= Cuexm)
			{
				if (T_st->tm_mon == Cuexm)
				{
					if (T_st->tm_mday <= Cuexd)
						RemainT = Cuexd - T_st->tm_mday;
				}
				else
				{
					RemainT = mon_day(T_st->tm_mon + 1, T_st->tm_year + 1900) - T_st->tm_mday;
					T_st->tm_mon++;
					T_st->tm_mday = 0;

					while (T_st->tm_mon < Cuexm)
					{
						RemainT += mon_day(T_st->tm_mon + 1, T_st->tm_year + 1900);
						T_st->tm_mon++;
					}
					RemainT += Cuexd;
				}
			}
		}

		CuexTime.push_back(RemainT);

		if (RemainT < min && RemainT > 0)
			min = RemainT;

		if (RemainT < min && RemainT > 0)
			min = RemainT;
		RemainT = -1;
	}

	for (int i = 0; i < customer_list.size(); i++)
	{
		if (CuexTime[i] == min)
			list.push_back(pair<int,int>(customer_list[i].id, CuexTime[i]));
	}
	return list;
}

//���� �������� ���� ���� ȸ���� ����ϴ� �Լ�
//ù �μ��� ȸ�� ����Ʈ. ��ȯ���� ȸ���� id�� ���� ����
vector<pair<int, int>> latest_attendance(vector<customer> customer_list)
{
	vector<pair<int,int>>CuexTime, list;
	time_t* Time = new time_t;
	tm *T_st = new tm;
	string Timestr;
	int Cuexy, Cuexm, Cuexd, TodayT, CuexT, RemainT, index = 0, min = 0;

	time(Time);
	T_st = gmtime(Time);
	TodayT = (T_st->tm_year + 1900) * 10000 + (T_st->tm_mon + 1) * 100 + T_st->tm_mday;

	for (int i = 0; i < customer_list.size(); i++)
	{
		Timestr = customer_list[i].expiration;
		CuexT = 0;
		CuexT =
			(Timestr[0] - '0') * 10000000 +
			(Timestr[1] - '0') * 1000000 +
			(Timestr[2] - '0') * 100000 +
			(Timestr[3] - '0') * 10000 +
			(Timestr[7] - '0') * 1000 +
			(Timestr[8] - '0') * 100 +
			(Timestr[12] - '0') * 10 +
			(Timestr[13] - '0');

		RemainT = CuexT - TodayT;
		if (RemainT < 0)
			continue;

		index++;
		T_st = gmtime(Time);
		Timestr = customer_list[i].lastdate;

		RemainT = -1;

		Cuexy =
			(Timestr[0] - '0') * 1000 +
			(Timestr[1] - '0') * 100 +
			(Timestr[2] - '0') * 10 +
			(Timestr[3] - '0') - 1900;
		Cuexm =
			(Timestr[7] - '0') * 10 +
			(Timestr[8] - '0') - 1;
		Cuexd =
			(Timestr[12] - '0') * 10 +
			(Timestr[13] - '0');

		if (Cuexy < T_st->tm_year)
		{
			RemainT = (mon_day(Cuexm + 1, Cuexy + 1900) - Cuexd);
			Cuexm++;
			Cuexd = 1;
			while (Cuexm < 12)
			{
				RemainT += (mon_day(Cuexm + 1, Cuexy + 1900));
				Cuexm++;
			}
			Cuexy++;
			Cuexm = 0;

			while (Cuexy < T_st->tm_year)
			{
				if (((Cuexy + 1900) % 4 == 0) && ((Cuexy + 1900) % 100 != 0) || ((Cuexy + 1900) % 400 == 0))
					RemainT += 366;
				else
					RemainT += 365;
				Cuexy++;
			}

			while (Cuexm < T_st->tm_mon)
			{
				RemainT += mon_day(Cuexm + 1, Cuexy + 1900);
				Cuexm++;
			}
			RemainT += T_st->tm_mday;
		}
		else if (Cuexy == T_st->tm_year)
		{
			if (Cuexm <= T_st->tm_mon)
			{
				if (Cuexm == T_st->tm_mon)
				{
					if (Cuexd <= T_st->tm_mday)
						RemainT = T_st->tm_mday - Cuexd;
				}
				else
				{
					RemainT = mon_day(Cuexm + 1, Cuexy + 1900) - Cuexd;
					Cuexm++;
					Cuexd = 0;

					while (Cuexm < T_st->tm_mon)
					{
						RemainT += mon_day(Cuexm + 1, Cuexy + 1900);
						Cuexm++;
					}
					RemainT += T_st->tm_mday;
				}
			}
		}

		CuexTime.push_back(pair<int, int>(customer_list[i].id, RemainT));

		if (RemainT > min)
			min = RemainT;
	}

	for (int i = 0; i < index; i++)
	{
		if (CuexTime[i].second == min)
			list.push_back(pair<int, int>(customer_list[CuexTime[i].first - 1].id, CuexTime[i].second));
	}
	return list;
}