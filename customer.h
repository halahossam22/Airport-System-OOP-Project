#pragma once
class booking;
#include "user.h"
#include "booking_system.h"
class customer : public user {
protected:
	booking* mybookings[20];
	int booking_count;
public:
	friend class agent;
	customer();
	int getbookingcount();
	void searchflights(string des, booking_system* bs);
	void addbooking(booking* b);
	int get_booking_count();
	booking* get_booking_by_index(int index);
	void view_my_bookings();
	void CancelBooking(int ID);
	string getrole();
};