#include "internationalflight.h"
#include "flight.h"
#include <string>
#include <iostream>
using namespace std;
internationalflight::internationalflight(string fno, string s, string des, double pr, int seat, bool visa, float taxs, string services) :flight(fno, s, des, pr, seat)
{
	visarequired = visa;
	internationaltaxs = taxs;
	additionalservices = services;
}
double internationalflight::getprice()
{
	return price + internationaltaxs;
}
void internationalflight::display() {
	flight::display();
	if (visarequired) {
		cout << "[!]Note:visa is REQUIRED for this flight." << endl;
	}
	else
		cout << "[]Note:NO visa required for this international destination." << endl;

	cout << additionalservices << endl;
}

bool internationalflight::getvisa()
{
	return visarequired;
}

float internationalflight::gettax()
{
	return internationaltaxs;
}

string internationalflight::getservice()
{
	return additionalservices;
}

bool internationalflight::checkvisarequirment()
{
	char hasvisa;
	if (visarequired) {
		cout << "Does passenger has visa (y/n)" << endl;
		cin >> hasvisa;
		return(hasvisa == 'y' || hasvisa == 'Y');
	}
	return true;
}