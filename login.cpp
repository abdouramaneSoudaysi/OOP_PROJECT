#include <iostream>
#include <cstdio>
#include <string>
#include "functions.h"
#include "class.h"
#include "database.h"

using namespace std;

void login()
{
    clearScreen();
    cout << "\t\t\t---LOGIN TO ACCOUNT---\t\t\t\n";
    cout <<"\t\t*please enter your choice*:\t\n\n";
    cout << "1) Customer\n";
    cout << "2) Staff\n";
    cout << "3) Manager\n";


    int accountType;
    cin >> accountType;
    cin.ignore();

    switch(accountType)
    {
        case 1: //customer
        {
            while(1)
            {
            string _name;
            string _password;
            cout << "Enter Name: ";
            getline(cin , _name);
            cout << "Enter Password: ";
            getline(cin , _password);
           
            Credentials c = dbRetreiveCustomerCredentials(_name);
            if(c.user_name == "not found") cout << "Account Not Found\n";
            else
            {
                if(c.user_pass == _password) 
                {
                    Customer cus;
                    cus.setName(c.user_name);
                    cus.customerScreen();
                }
                else cout << "Incorrect Password\n\n";
            }
            }
            
            break;
        }
        case 2: //staff
        {
            while(1)
            {
            string _name;
            string _password;
            cout << "Enter Name: ";
            getline(cin , _name);
            cout << "Enter Password: ";
            getline(cin , _password);
           
            Credentials c = dbRetreiveStaffCredentials(_name);
            if(c.user_name == "not found") cout << "Account Not Found\n";
            else
            {
                Staff s;
                if(c.user_pass == _password) s.staffScreen();
                else cout << "Incorrect Password\n\n";
            }
            }
            
            break;
        }
        case 3://manager
        {
            while(1)
            {
            string _name;
            string _password;
            cout << "Enter Name: ";
            getline(cin , _name);
            cout << "Enter Password: ";
            getline(cin , _password);
           
            Credentials c = dbRetreiveManagerCredentials(_name);
            if(c.user_name == "not found") cout << "Account Not Found\n";
            else
            {
                if(c.user_pass == _password)
                {
                    Manager m;
                    m.managerScreen();
                }
                else cout << "Incorrect Password\n\n";
            }
            }
            
            break;
        }
    }


}
void createAccount()
{
    clearScreen();
    cout << "\t\t\t---CREATE ACCOUNT---\t\t\t\n";
    cout <<"\t\t*please enter your choice*:\t\n\n";
    cout << "1) Customer\n";
    cout << "2) Manager\n";


    int accountType;
    cin >> accountType;
    cin.ignore();

    switch(accountType)
    {
        case 1: //customer
        {
            string n;
            string c;
            string pass;
            cout << "Enter Name : ";
            getline(cin , n);
            cout << "Enter NID : ";
            getline(cin , c);
            cout << "Choose Password : ";
            getline(cin , pass);

            Customer my_customer(n , c , time(NULL));
            dbInsertCustomer(my_customer , pass);
            break;
        }
        case 2://manager
        {
            string n  , email , pass , dob, designation;
            int id,salary;
            cout << "Enter Name : ";
            getline(cin , n);
            cout << "Enter Date Of Birth : ";
            getline(cin , dob);
            cout << "Enter Id : ";
            cin >> id;
            cin.ignore();
            cout << "Enter salary : ";
            cin >> salary;
            cin.ignore();
            cout << "Enter email : ";
            getline(cin , email);
            cout << "Choose Password : ";
            getline(cin , pass);

            Manager myMan(n , dob , email , id, salary);
            dbInsertManager(myMan , pass);
        }
       
    }
}
        
          
     
