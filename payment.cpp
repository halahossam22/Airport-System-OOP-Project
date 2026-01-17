#include "payment.h"
#include <iostream>
payment::payment() {}
payment::payment(string paydate, string paymethod)
{
	paymentdate = paydate;
	paymentmethod = paymethod;
	paymentID = "PAY-" + to_string(transactionCounter++);
	paymentstatus = "pending";
}

void payment::setamount(double amo)
{
	amount = amo;
}

bool payment::processpayment(flight* f)
{
	bool isdatavaild = false;
	amount = f->getprice();
	if (paymentmethod == "credit card") {
		string cardno;
		cout << "Please enter your card number" << endl;
		cin >> cardno;
		if (cardno.length() != 16) {
			cout << "ERROR:card number must be 16 digits!" << endl;
			paymentstatus = "Failed";
			return false;
		}
		isdatavaild = true;
	}
	else if (paymentmethod == "paypal") {
		string email;
		cout << "Please enter your email!" << endl;
		cin >> email;

		if (email.find('@') == string::npos || email.find('.') == string::npos) {
			cout << "invaild paypal account format!" << endl;
			paymentstatus = "failed";
			return false;
		}
		string paypalpassword;
		cout << "Please enter your paypal password: " << endl;
		cin >> paypalpassword;
		if (paypalpassword.empty() || paypalpassword.length() < 8) {
			cout << "invaild paypal password!" << endl;
			return false;
		}
		double fakebalance = 100000.0;
		if (amount > fakebalance) {
			cout << "Insufficient paypal balance!" << endl;
			paymentstatus = "failed";
			return false;
		}
		isdatavaild = true;
	}
	else if (paymentmethod == "cash") {
		cout << "Please ensure the amount of $" << amount << " is handed to the office agent" << endl;
		isdatavaild = true;
	}
	if (isdatavaild) {
		char confirm;
		cout << "Authorize payment of $" << amount << " ?(y/n)" << endl;
		cin >> confirm;
		if (confirm == 'y' || confirm == 'Y') {
			paymentstatus = "completed";
			cout << "transaction successful via " << paymentmethod << ".thank you!" << endl;
			return true;
		}
		else
		{
			paymentstatus = "failed";
			cout << "payment process is rejected by user!" << endl;
			return false;

		}
	}
	else {
		paymentstatus = "cancelled";
		cout << "payment cancelled by user." << endl;
		return false;
	}
}

void payment::generatereceipt()
{
	cout << "------RECEIPT------" << endl;
	cout << "Payment date:" << paymentdate << endl;
	cout << "PaymentID:" << paymentID << endl;
	cout << "total paid: $" << amount << endl;
	cout << "Status:" << paymentstatus << endl;
	cout << "-------------------" << endl;
}

