#pragma once
#include "flight.h"
class internationalflight :public flight {
	bool visarequired;
	float internationaltaxs;
	string additionalservices;
public:
	friend class payment;
	internationalflight(string fno, string s, string des, double pr, int seat, bool visa, float taxs, string services);
	double getprice();
	void display();
	bool getvisa();
	float gettax();
	string getservice();
	bool checkvisarequirment();
};