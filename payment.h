#pragma once
#include "flight.h"
#include "internationalflight.h"
class payment {
protected:
	flight* f;
	internationalflight* intf;
	static int transactionCounter;
	string paymentdate, paymentID;
	double amount;
	string paymentmethod;
	string paymentstatus;
public:
	friend class booking_system;
	payment();
	payment(string paydate, string paymethod);
	void setamount(double amo);
	bool processpayment(flight* f);
	void generatereceipt();
};
