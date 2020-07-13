#pragma once


class PT {
public:
	char *trainer_name;
	int count;
};

class customer {
public:
	int id;
	char *name;
	char *address;
	char *phone_num;
	char *recommender;
	int bday;
	int product;

	PT training;
	int pt;

	double first_bmi;
	double bmi;
	double goal_bmi;

	int locker_num;
	int attendance;

	int assigned_date;
	int lastdate;
	int expiration;
};

class trainer {
public:
	char* name;

	int num_student;
	int *students_id;
};