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

//가장 등록이 많은/적은 달 함수
//첫번째 인수는 회원 리스트, 두번째 원소는 출력할 달의 개수
//1~12 : 입력한 수만큼 내림차순 출력, -1~-12 : 입력한 수만큼 오름차순 출력
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
		cout << ITER->first << "월 : " << ITER->second << "회" << endl;
		month_list.erase(ITER);
		if (aoc == -1)
			max = customer_list.size();
		else
			max = 0;
	}

	return return_list;
}

//운동 달성률 높은/낮은 회원 구하는 함수
//첫 번째 인수는 회원 리스트, 두 번째 인수를 1로 설정시 높은 회원, -1로 설정시 낮은 회원, default는 1
//반환값은 회원의 id를 담은 벡터
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
			cout << "달성률 : " << rate * 100 << "%" << endl;
			list.push_back(customer_list[i].id);
		}
	}
	return list;
}

//훈련 성과가 제일 좋은 트레이너를 출력하는 함수
//첫 인수는 회원 리스트, 반환값은 트레이너 이름을 담은 벡터
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
			cout << "훈련 성과가 가장 좋은 트레이너 : " << temp->first << ", 훈련 성과 : " << temp->second.first << endl;
			rtv.push_back(temp->first);
		}
	}
	return rtv;
}

//가장 가까운 시간 내에 구매 상품이 종료되는 회원을 구하는 함수
//첫 인수는 회원 리스트. 반환값은 회원의 id를 담은 벡터
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

//가장 오랫동안 오지 않은 회원을 출력하는 함수
//첫 인수는 회원 리스트. 반환값은 회원의 id를 담은 벡터
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

	//for (int i = 0; i < customer_list.size(); i++) //회원 정보 출력
	//	customer_list[i].print();

	cout << "제일 오랫동안 안 온 회원\n";
	latest_attendance(customer_list);
	file.close();


	// 회원정보는 customer_list에 vector 형식으로 담겨있습니다! 

	//1. 가장 회원을 많이 확보한 트레이너는? ( 지현)
	//2. 가장 훈련 성과가 좋은 트레이너는?
	//3. 가장 출석률이 좋은 회원은?
	//5. 가장 등록이 많은/적은 달은?
	//6. 가장 오래된 회원은?
	//7. 구매 상품이 가장 가까운 시간 내에 종료하는 회원은?
	//8. 전월 대비 가장 등록률이 떨어지는 달은?
	//11. PT를 받는 회원 중에 라커를 사용하지 않는 회원은? (정연)
	//16. 운동 달성률이 갖아 높은/낮은 회원은?
	//19. PT를 가장 많이/ 적게이용하는 연령대는?(유진)



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