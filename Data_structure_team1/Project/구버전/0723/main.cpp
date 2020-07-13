#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>

#include <time.h>
#include <map>
#pragma warning(disable:4996)

using namespace std;

#include "customer.h"


vector<string> csv_read_row(istream &file, char delimeiter);

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
vector<int> attainment_rate(vector<customer> customer_list, int return_attribute = 1)
{
	vector<int> list;
	int index;
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
		if (customer_list[i].first_bmi > customer_list[i].goal_bmi)
		{
			rate = (customer_list[i].goal_bmi - customer_list[i].bmi)
				/ (customer_list[i].goal_bmi - customer_list[i].first_bmi);

			rate = 1 - rate;

			if (return_attribute == 1)
			{
				if (max < rate)
				{
					index = customer_list[i].id;
					max = rate;
				}
			}
			else if (return_attribute == -1)
			{
				if (max > rate)
				{
					max = rate;
					index = customer_list[i].id;
				}
			}
			else
			{
				rate = (customer_list[i].goal_bmi - customer_list[i].bmi)
					/ (customer_list[i].goal_bmi - customer_list[i].first_bmi);

				rate = 1 - rate;

				if (return_attribute == 1)
				{
					if (max < rate)
					{
						max = rate;
						index = customer_list[i].id;
					}
				}
				else if (return_attribute == -1)
				{
					if (max > rate)
					{
						max = max > rate ? rate : max;
						index = customer_list[i].id;
					}
				}
			}
		}
	}

	for (int i = 0; i < customer_list.size(); i++)
	{
		rate = (customer_list[i].goal_bmi - customer_list[i].bmi)
			/ (customer_list[i].goal_bmi - customer_list[i].first_bmi);

		rate = 1 - rate;

		if (max == rate)
		{
			customer_list[i].print();
			cout << "�޼��� : " << rate * 100 << "%" << endl;
			list.push_back(customer_list[i].id);
		}
	}
	return list;
}

//�Ʒ� ������ ���� ���� Ʈ���̳ʸ� ����ϴ� �Լ�
//ù �μ��� ȸ�� ����Ʈ, ��ȯ���� Ʈ���̳� �̸��� ���� ����
vector<string> best_training_performance(vector<customer> customer_list)
{
	map<string, pair<double, int>> train_per;
	map<string, pair<double, int>>::iterator temp;
	vector<string> rtv;
	double max = -1000.0, dtemp;

	for (int i = 0; i < customer_list.size(); i++)
	{
		if (customer_list[i].pt != 1)
			continue;

		temp = train_per.find(customer_list[i].training.trainer_name);
		if (temp == train_per.end())
		{
			train_per[customer_list[i].training.trainer_name]
				= pair<double, int>((customer_list[i].bmi - customer_list[i].goal_bmi) / customer_list[i].training.count, 1);
		}
		else
		{
			
			dtemp = ((customer_list[i].bmi - customer_list[i].goal_bmi) / customer_list[i].training.count)
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
			cout << "�Ʒ� ������ ���� ���� Ʈ���̳� : " << temp->first << ", �Ʒ� ���� : " << temp->second.first << endl;
			rtv.push_back(temp->first);
		}
	}
	return rtv;
}

//���� ����� �ð� ���� ���� ��ǰ�� ����Ǵ� ȸ���� ���ϴ� �Լ�
//ù �μ��� ȸ�� ����Ʈ. ��ȯ���� ȸ���� id�� ���� ����
vector<int> quick_termination(vector<customer> customer_list)
{
	vector<int> list, CuexTime;
	time_t* Time = new time_t;
	tm *T_st = new tm;
	string Timestr;
	int TodayT, CuexT, RemainT, min = INT_MAX;

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

		CuexTime.push_back(RemainT);

		if (RemainT < min && RemainT > 0)
			min = RemainT;
	}

	for (int i = 0; i < customer_list.size(); i++)
	{
		if (CuexTime[i] == min)
		{
			customer_list[i].print();
			list.push_back(customer_list[i].id);
		}
	}
	return list;
}

//���� �������� ���� ���� ȸ���� ����ϴ� �Լ�
//ù �μ��� ȸ�� ����Ʈ. ��ȯ���� ȸ���� id�� ���� ����
vector<int> latest_attendance(vector<customer> customer_list)
{
	vector<int> list;
	vector<pair<int,int>>CuexTime;
	time_t* Time = new time_t;
	tm *T_st = new tm;
	string Timestr;
	int TodayT, CuexT, RemainT, index = 0, min = INT_MAX;

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
		Timestr = customer_list[i].lastdate;

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

		CuexTime.push_back(pair<int,int>(customer_list[i].id , RemainT));

		if (RemainT < min)
			min = RemainT;
	}

	for (int i = 0; i < index; i++)
	{
		if (CuexTime[i].second == min)
		{
			customer_list[CuexTime[i].first - 1].print();
			list.push_back(customer_list[i].id);
		}
	}
	return list;
}

int main() {
	ifstream file("info.csv");

	vector<customer> customer_list;
	if (file.fail())
		return (cout << "��������x" << endl) && 0;
	vector<string> row = csv_read_row(file, ',');
	while (file.good()) { // file�� ���������� �ݺ�

		row = csv_read_row(file, ',');
		if (!row[0].find("#"))
			continue;
		else {
			customer temp;
			temp.set(row);
			customer_list.push_back(temp);
		}
	}

	//for (int i = 0; i < customer_list.size(); i++) //ȸ�� ���� ���
	//	customer_list[i].print();

	cout << "���� �������� �� �� ȸ��\n";
	latest_attendance(customer_list);
	file.close();


	// ȸ�������� customer_list�� vector �������� ����ֽ��ϴ�! 

	//1. ���� ȸ���� ���� Ȯ���� Ʈ���̳ʴ�? ( ����)
	//2. ���� �Ʒ� ������ ���� Ʈ���̳ʴ�?
	//3. ���� �⼮���� ���� ȸ����?
	//5. ���� ����� ����/���� ����?
	//6. ���� ������ ȸ����?
	//7. ���� ��ǰ�� ���� ����� �ð� ���� �����ϴ� ȸ����?
	//8. ���� ��� ���� ��Ϸ��� �������� ����?
	//11. PT�� �޴� ȸ�� �߿� ��Ŀ�� ������� �ʴ� ȸ����? (����)
	//16. � �޼����� ���� ����/���� ȸ����?
	//19. PT�� ���� ����/ �����̿��ϴ� ���ɴ��?(����)



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