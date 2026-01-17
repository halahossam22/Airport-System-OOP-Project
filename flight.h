#pragma once
#include "user.h"
class flight {
protected:
	string flightnumber, source, destination;
	int availableseats;
	double price;
public:
	flight();
	friend class booking;
	friend class booking_system;
	friend class payment;
	flight(string fno, string s, string des, double pr, int seat);
	bool checkavailability();
	bool bookseat();
	void releaseseat();
	virtual double getprice();
	virtual void display();
	int getavailableseats();
	string getflightnum();
	string getdestination();
};