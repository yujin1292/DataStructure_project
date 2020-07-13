#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "customer.h"
#pragma warning(disable:4996)

customer *memberlist;
int memberlistcnt = 0;

bool Isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return true;
	else
		return false;
}

void load(FILE *fp)
{
	char buf[256];
	int index = 0, bufindex = 0, charcount = 0;
	bool fractional_parts = false;
	int gum = 1;

	fgets(buf, 256, fp);

	while (true)
	{
		if (fgets(buf, 256, fp) != NULL)
			break;
		if (buf[0] == ',')
			break;
		index++;
	}

	rewind(fp);

	memberlist = new customer[index];
	index = 0;
	fgets(buf, 256, fp);

	while (true)
	{
		//루프의 종료조건
		//파일의 끝을 만나거나, 의미 없는 데이터를 만나거나.
		if (fgets(buf, 256, fp) == NULL)
			break;
		if (buf[0] == ',')
			break;

		//id 입력
		memberlist[index].id = 0;
		while (buf[bufindex] != ',')
		{
			memberlist[index].id *= 10;
			memberlist[index].id += buf[bufindex++] - '0';
		}
		bufindex++;

		//name 입력
		while (buf[bufindex] != ',')
		{
			bufindex++;
			charcount++;
		}

		memberlist[index].name = new char[charcount + 1];
		bufindex -= charcount;
		charcount = 0;

		while (buf[bufindex] != ',')
			memberlist[index].name[charcount++] = buf[bufindex++];
		memberlist[index].name[charcount] = '\0';

		bufindex++;
		charcount = 0;

		//address 입력
		while (buf[bufindex] != ',')
		{
			bufindex++;
			charcount++;
		}

		memberlist[index].address = new char[charcount + 1];
		bufindex -= charcount;
		charcount = 0;

		while (buf[bufindex] != ',')
			memberlist[index].address[charcount++] = buf[bufindex++];
		memberlist[index].address[charcount] = '\0';

		bufindex++;
		charcount = 0;

		//phone_num 입력
		while (buf[bufindex] != ',')
		{
			bufindex++;
			charcount++;
		}

		memberlist[index].phone_num = new char[charcount + 1];
		bufindex -= charcount;
		charcount = 0;

		while (buf[bufindex] != ',')
			memberlist[index].phone_num[charcount++] = buf[bufindex++];
		memberlist[index].phone_num[charcount] = '\0';

		bufindex++;
		charcount = 0;

		//recommender 입력
		while (buf[bufindex] != ',')
		{
			bufindex++;
			charcount++;
		}

		memberlist[index].recommender = new char[charcount + 1];
		bufindex -= charcount;
		charcount = 0;

		while (buf[bufindex] != ',')
			memberlist[index].recommender[charcount++] = buf[bufindex++];
		memberlist[index].recommender[charcount] = '\0';

		bufindex++;
		charcount = 0;

		//bday 입력
		memberlist[index].bday = 0;
		while (buf[bufindex] != ',')
		{
			if (Isdigit(buf[bufindex]))
			{
				memberlist[index].bday *= 10;
				memberlist[index].bday += buf[bufindex] - '0';
			}
			bufindex++;
		}
		bufindex++;

		//product 입력
		memberlist[index].product = 0;
		while (Isdigit(buf[bufindex]))
		{
			memberlist[index].product *= 10;
			memberlist[index].product += buf[bufindex++] - '0';
		}

		while (buf[bufindex++] != ',');

		//pt 입력받음
		if (buf[bufindex] == 'Y')
			memberlist[index].pt = 1;
		else
			memberlist[index].pt = 0;

		bufindex += 2;

		//tranining.trainer_name 입력받음
		if (buf[bufindex] == '-')
		{
			memberlist[index].training.trainer_name = NULL;
			memberlist[index].training.count = 0;
			bufindex++;
		}
		else
		{
			bufindex++;
			while (buf[bufindex] != ',')
			{
				bufindex++;
				charcount++;
			}
			memberlist[index].training.trainer_name = new char[charcount + 1];
			bufindex -= charcount;
			charcount = 0;
			while (buf[bufindex] != ',')
				memberlist[index].training.trainer_name[charcount++] = buf[bufindex++];
			memberlist[index].training.trainer_name[charcount] = '\0';
			charcount = 0;
		}
		bufindex++;

		//first_bmi 입력받음
		memberlist[index].first_bmi = 0;

		while (buf[bufindex] != ',')
		{
			if (buf[bufindex] == '.')
			{
				fractional_parts = true;
				bufindex++;
				continue;
			}
			if (fractional_parts)
				gum *= 10;
			memberlist[index].first_bmi *= 10;
			memberlist[index].first_bmi += buf[bufindex++] - '0';
		}
		memberlist[index].first_bmi /= gum;
		fractional_parts = false;
		gum = 1;
		bufindex++;

		//bmi 입력받음
		memberlist[index].bmi = 0;

		while (buf[bufindex] != ',')
		{
			if (buf[bufindex] == '.')
			{
				fractional_parts = true;
				bufindex++;
				continue;
			}
			if (fractional_parts)
				gum *= 10;
			memberlist[index].bmi *= 10;
			memberlist[index].bmi += buf[bufindex++] - '0';
		}
		memberlist[index].bmi /= gum;

		fractional_parts = false;
		gum = 1;
		bufindex++;

		//goal_bmi 입력받음
		memberlist[index].goal_bmi = 0;

		while (buf[bufindex] != ',')
		{
			if (buf[bufindex] == '.')
			{
				fractional_parts = true;
				bufindex++;
				continue;
			}
			if (fractional_parts)
				gum *= 10;
			memberlist[index].goal_bmi *= 10;
			memberlist[index].goal_bmi += buf[bufindex++] - '0';
		}
		memberlist[index].goal_bmi /= gum;

		fractional_parts = false;
		gum = 1;
		bufindex++;

		//locker_num 입력받음
		memberlist[index].locker_num = 0;

		if (buf[bufindex] == '-')
			memberlist[index].locker_num = -1;
		else
		{
			while (buf[bufindex] != ',')
			{
				memberlist[index].locker_num *= 10;
				memberlist[index].locker_num += buf[bufindex++] - '0';
			}
		}
		bufindex++;

		//assigned_date 입력받음
		memberlist[index].assigned_date = 0;
		while (buf[bufindex] != ',')
		{
			if (Isdigit(buf[bufindex]))
			{
				memberlist[index].assigned_date *= 10;
				memberlist[index].assigned_date += buf[bufindex] - '0';
			}
			bufindex++;
		}
		bufindex++;

		//attendance 입력받음
		memberlist[index].attendance = 0;
		while (buf[bufindex] != ',')
		{
			memberlist[index].attendance *= 10;
			memberlist[index].attendance += buf[bufindex++] - '0';
		}
		bufindex++;

		//training.count 입력받음
		memberlist[index].training.count = 0;
		while (buf[bufindex] != ',')
		{
			memberlist[index].training.count *= 10;
			memberlist[index].training.count += buf[bufindex++] - '0';
		}
		bufindex++;

		//lastdate 입력받음
		memberlist[index].lastdate = 0;
		while (buf[bufindex] != ',')
		{
			if (Isdigit(buf[bufindex]))
			{
				memberlist[index].lastdate *= 10;
				memberlist[index].lastdate += buf[bufindex] - '0';
			}
			bufindex++;
		}
		bufindex++;

		//expiration 입력받음
		memberlist[index].expiration = 0;
		while (buf[bufindex] != '\0' && buf[bufindex] != ',')
		{
			if (Isdigit(buf[bufindex]))
			{
				memberlist[index].expiration *= 10;
				memberlist[index].expiration += buf[bufindex] - '0';
			}
			bufindex++;
		}
		bufindex++;

		index++;
		bufindex = 0;
	}
	memberlistcnt = index;
}

int main(void)
{
	FILE *fp = fopen("회원 정보_통합_최종.csv", "r");

	printf("load start\n");
	load(fp);
	printf("load end\n");

	for (int i = 0; i < memberlistcnt; i++)
	{
		printf("id : %d\nname : %s\naddress : %s\nphone_num : %s\nrecommender : %s\n", memberlist[i].id, memberlist[i].name, memberlist[i].address, memberlist[i].phone_num, memberlist[i].recommender);
		printf("bday : %d\nproduct : %d\npt : %d\nTrain.name : %s\n", memberlist[i].bday, memberlist[i].product, memberlist[i].pt, memberlist[i].training.trainer_name);
		printf("first_bmi : %lf\nbmi : %lf\ngoal_bmi : %lf\nlocker_num : %d\n", memberlist[i].first_bmi, memberlist[i].bmi, memberlist[i].goal_bmi, memberlist[i].locker_num);
		printf("attendance : %d\n, train.count : %d\nassigned_date : %d, lastdate : %d, expiration : %d\n\n", memberlist[i].attendance, memberlist[i].training.count, memberlist[i].assigned_date, memberlist[i].lastdate, memberlist[i].expiration);
	}
	return 0;
}