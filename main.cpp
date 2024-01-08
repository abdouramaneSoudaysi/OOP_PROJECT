#include <iostream>
#include "login.h"
#include <cstdlib>
#define RESET "\x1B[0m"
#define C1 "\x1B[31m"
#define C2 "\x1B[32m"

using namespace std;

int main()
{
    //if(system("mkdir db")){}
    cout<<C2"\t\t------------------------------------------------------------------------\t\t";
    cout <<"\n\t\t\t*********WELCOME HOTEL MANAGEMENT SYSTEM*********\t\t\t\n" << endl;
    cout<<"\t\t------------------------------------------------------------------------\t\t\n";
    cout<<RESET"\t\t*please enter your choice*:\t\t\n\n";
    cout << "1) CREATE ACCOUNT FORM" << endl;
    cout << "2) LOGIN FORM" << endl;
    

    int operation;
    scanf("%d" , &operation);

    switch(operation)
    {
        case 1:
            //login
           createAccount();
            break;
        case 2 : 
            //create Account
             login();
            break;  

    }
    return 0;
}
//ROOM rooms();

