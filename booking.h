#pragma once
class customer;
#include "flight.h"
#include "internationalflight.h"
class booking
{
protected:
	int bookingID;
	flight* fly;
	internationalflight* intflight;
	customer* passenger;
	string status;

public:
	booking(int id, flight* f, customer* p);
	virtual void displaybookingdetails();
	void cancelbooking();
	int getbookingID();
	flight* get_fly();
	friend class agent;
	friend class user;
	friend class flight;
	friend class internationalflight;
};