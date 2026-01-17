#pragma once
#include "user.h"
#include "flight.h"
#include "booking_system.h"
#include "customer.h"
#include "payment.h"
class agent : public user
{
protected:
	customer* cust;
	flight* flightdetails;
	booking_system* system;
	double totalsales;
	double commissionrate;
public:
	agent();
	double calculatecommision();
	void processbooking(customer* c, flight* f, booking_system* system, payment* p);
	void generatereports();
	string getrole();
};
