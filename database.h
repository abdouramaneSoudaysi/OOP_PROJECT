#pragma once
#include"class.h"
#include<string>

#define CUSTOMER_FILE "db/customer.txt"
#define STAFF_FILE "db/staff.txt"
#define MANAGER_FILE "db/manager.txt"
#define ROOM_FILE "db/room.txt"
#define RESERVATION_FILE "db/reservation.txt"

using namespace std;

typedef struct Credentials{
    string user_name;
    string user_pass;
}Credentials;

void dbInsertCustomer(Customer& c , string pass);
Credentials dbRetreiveCustomerCredentials(string _name);

void dbInsertStaff(Staff& s , string pass);
Credentials dbRetreiveStaffCredentials(string _name);

void dbInsertManager(Manager& m, string pass);
Credentials dbRetreiveManagerCredentials(string _name);