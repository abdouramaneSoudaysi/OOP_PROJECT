#include<iostream>
#include<string>
#include<cstring>
#include "class.h"
#include "database.h"
#include "functions.h"

using namespace std;

Customer:: Customer()
{

}
void Customer::customerScreen()
{
    clearScreen();

    //read reservations from file
    Reservation *array = new Reservation[100];
    int n_reservation = 0;

    FILE* fp = fopen(RESERVATION_FILE , "r");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        char name[80];
        int rn;
        time_t rt;
        time_t et;

        int i;
        for(i=0; !feof(fp); i++)
        {
            
             fscanf(fp , "customer Name : %s\n" , name);
             fscanf(fp , "room number : %d\n" , &rn);
             fscanf(fp , "Reservation date : %ld\n" , &rt);
             fscanf(fp , "Expiration date : %ld\n" , &et);

             array[n_reservation].setCustomerName(name);
             array[n_reservation].setRoomNumber(rn);
             array[n_reservation].setReservationDate(rt);
             array[n_reservation].setExpirationDate(et);
             n_reservation++;
        }

         //find username
        int index = -1;
        for(int i=0; i<n_reservation; i++)
        {
            if(array[i].getCustomerName() == this->getName())
            {
                index = i;
                break;
            }
            }

    while(1)
    {

    
    cout << "\t\t\tWELCOME TO CUSTOMER ACCOUNT\t\t\t\n";
    cout <<"\t\t*please enter your choice*:\n\n";

    cout << "1)Reservation"<<endl;
    cout << "2)Cancel Reservation"<<endl;
    cout << "3)Extend Reservation"<<endl;
    cout << "4)Order Food"<<endl;
    cout << "5)List Activities"<<endl;
    cout << "6)Pay Bills"<<endl;

    int choice;
    cin >> choice;
    cin.ignore();

    switch(choice)
    {
        case 1:
            reservation();
            break;
        case 2:
        {
            if(index != -1)
            {
                cancelReservation(array ,index , n_reservation);
                cout << "Reservation Cancelled\n";
            }
                
            else
                cout << "No made Reservation\n";
            break;
        }
            
        case 3:
        {
            if(index != -1)
            {
                int period;
                time_t new_date;
                cout << "Choose Period:\n";
                cout << "1) 1 Day\n";
                cout << "2) 3 Days\n";
                cout << "3) 1 Week\n";

                cin >> period;
                switch(period)
                {
                    case 1:
                       new_date =  array[index].getExpirationDate() + 86400;
                       break;
                    case 2:
                       new_date =  array[index].getExpirationDate() + (86400*3);
                       break;
                    case 3:
                       new_date =  array[index].getExpirationDate() + (86400*7);
                       break;
                }
                extendReservation(array ,index , n_reservation, new_date);
                cout << "Reservation extended\n";
            }
                
            else
                cout << "No made Reservation\n";
            break;
        }
        case 4:
            orderFood();
            break;
        case 5:
           listActivities();
           break;
        case 6:
            cout << "Your bill is : " << bill.getAmount();
            cout << "\nPress 1 to confirm\n";
            int action;
            cin >> action;
            if(action == 1)
            {
                bill.clear();
                cout << "Your bill have been paid\n";
            }
            else customerScreen();
            break;
    }
    }
}
}
void Customer::reservation()
{
    cout << "Choose Room Type : \n";
    cout << "1) Single\n";
    cout << "2) DOuble\n";

    int room_type;
    int free_rooms;
    int occupied_rooms;
    cin >> room_type;

    cout << "Choose Reservation Period : \n";
    cout << "1) 1 day\n";
    cout << "2) 3 days\n";
    cout << "3) 1 week\n";

    int period;
    cin >> period;
    time_t expirationDate;

    switch(period)
    {
        case 1:
            expirationDate = time(NULL) + 86400;
        case 2:
             expirationDate = time(NULL) + (86400 * 3); 
        case 3:
             expirationDate = time(NULL) + (86400 * 7);        
         
    }

    //read rooms

    FILE* fp = fopen(ROOM_FILE , "r");
    if(fp == NULL)
        cout << "Failed to open file\n";
    else
    {
        fscanf(fp , "free:%d\n" , &free_rooms);
        fscanf(fp , "occupied:%d" , &occupied_rooms);
        fclose(fp);
    }

    this->setRoomNumber(occupied_rooms+1);
    occupied_rooms++;
    free_rooms--;

    fp = fopen(ROOM_FILE , "w");
    fprintf(fp , "free:%d\n" , free_rooms);
    fprintf(fp , "occupied:%d" , occupied_rooms);
    fclose(fp);

    fp = fopen(RESERVATION_FILE , "a");

    Reservation r;
    r.setCustomerName(this->getName());
    r.setRoomNumber(occupied_rooms);
    r.setReservationDate(time(NULL));
    r.setExpirationDate(expirationDate);
    fprintf(fp , "customer Name: %s\n" , r.getCustomerName().c_str());
    fprintf(fp , "room number : %d\n" , r.getRoomNumber());
    fprintf(fp , "Reservation date : %ld\n" , r.getReservationDate());
    fprintf(fp , "Expiration date : %ld\n" , r.getExpirationDate());

    fclose(fp);

}
void Customer:: cancelReservation(Reservation* array , int index , int n)
{
    for(int i=index; i<n-1; i++)
    {
        array[i].setCustomerName(array[i+1].getCustomerName());
        array[i].setRoomNumber(array[i+1].getRoomNumber());
        array[i].setReservationDate(array[i+1].getReservationDate());
        array[i].setExpirationDate(array[i+1].getExpirationDate());
   }

    //write to file

    FILE* fp = fopen( RESERVATION_FILE , "w");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        for(int i=0; i<n-1; i++)
        {
            fprintf(fp , "customer Name: %s\n" , array[i].getCustomerName().c_str());
            fprintf(fp , "room number : %d\n" , array[i].getRoomNumber());
            fprintf(fp , "Reservation date : %ld\n" , array[i].getReservationDate());
            fprintf(fp , "Expiration date : %ld\n" , array[i].getExpirationDate());
        }    
    }
    fclose(fp);
}
void Customer:: extendReservation(Reservation* array ,int index ,int n ,time_t new_date)
{
     array[index].setExpirationDate(new_date);

//write to file

    FILE* fp = fopen( RESERVATION_FILE , "w");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        for(int i=0; i<n-1; i++)
        {
            fprintf(fp , "customer Name: %s\n" , array[i].getCustomerName().c_str());
            fprintf(fp , "room number : %d\n" , array[i].getRoomNumber());
            fprintf(fp , "Reservation date : %ld\n" , array[i].getReservationDate());
            fprintf(fp , "Expiration date : %ld\n" , array[i].getExpirationDate());

        }
    }
    fclose(fp);
}
void Customer:: orderFood()
{
            cout<< "Order Food\n";
            cout<<"\n\t\t\t please select your menu options ";
            cout<<"\n\n1) Paster: "<< 50<<"BDT"<<endl;
            cout<<"\n2) Burger: "<< 60<<"BDT"<<endl;
            cout<<"\n3) Noodles: "<< 40<<"BDT"<<endl;
            cout<<"\n4) chicken: "<< 30<<"BDT"<<endl;

            int price;
            int option;
            cin >> option;
            switch(option)
            {
                case 1:
                    price = 50;
                    break;
                case 2:
                    price = 60;  
                    break;  
                case 3:
                    price = 40;
                    break;
                case 4:
                    price = 30;
                    break;
            }
            bill.increase(price);
}
void Customer:: listActivities()
{   
     cout<<"\n\t\t\t please select your activities options ";
            cout<<"\n\n1)Swimming Pool: "<<30<<"BDT"<<endl;
            cout<<"\n2)Shopping: "<< 50<<"BDT"<<endl;
            cout<<"\n3)Laundry Service: "<< 20<<"BDT"<<endl;
            cout<<"\n4)Excursions: "<<60<<"BDT"<<endl;

            int price;
            int option;
            cin >> option;
            switch(option)
            {
                case 1:
                    price = 30;
                    break;
                case 2:
                    price = 50;  
                    break;  
                case 3:
                    price = 20;
                    break;
                case 4:
                    price = 60;
                    break;
            }
            bill.increase(price);

}


string Customer:: getName() const
{
    return name;
}
string Customer:: getNid() const
{
    return NID;
}
time_t Customer:: getDoj() const
{
    return dateOfJoin;
}
int Customer::getRoomNumber() const
{
    return roomNumber;
}
void Customer::setRoomNumber(int rn)
{
    roomNumber = rn;
}
void Customer :: setName(string n)
{ 
    name = n;
}
void Customer :: setNid(string n){
    NID = n;
}
void Customer :: setDoj(time_t d){
    dateOfJoin = d;
}


int Bill::getAmount() const
{
    return amount;
}
void Bill::setAmount(int amt)
{
    amount = amt;
}
template<typename T>
void Bill::increase(T amt)
{
    amount += amt;
}
void Bill::clear()
{
    amount = 0;
}

Staff:: Staff()
{

}

void Staff::staffScreen()   //staff
{
    clearScreen();
    while(1)
    {
    cout << "\t\t\tWELCOME TO STAFF ACCOUNT\t\t\t\n";
    cout <<"\t\t*please enter your choice*:\n\n";
    cout << "1)list room"<<endl;
    cout << "2)list customer and delete custumer"<<endl;
    cout << "3)search custumer"<<endl;

    int choice;
    cin >> choice;
    cin.ignore();

    switch(choice)
    {
        
        case 1:
            listroom();
            break;
        case 2:
            listcustumer();
            break;
        case 3:
            searchcustumer();
            break;
            case 4:
            staffScreen();
            break;
        
    }
    }
}

void Staff::listroom()
{
    //read reservations from file
    Reservation *array = new Reservation[100];
    int n_reservation = 0;

    FILE* fp = fopen(RESERVATION_FILE , "r");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        char name[80];
        int rn;
        time_t rt;
        time_t et;

        int i;
        for(i=0; !feof(fp); i++)
        {
            
             fscanf(fp , "customer Name : %s\n" , name);
             fscanf(fp , "room number : %d\n" , &rn);
             fscanf(fp , "Reservation date : %ld\n" , &rt);
             fscanf(fp , "Expiration date : %ld\n" , &et);

             array[n_reservation].setCustomerName(name);
             array[n_reservation].setRoomNumber(rn);
             array[n_reservation].setReservationDate(rt);
             array[n_reservation].setExpirationDate(et);
             n_reservation++;
        } 

        clearScreen();
        cout << "Name\t\tRoom Number\t\tReservation Date\n";
        for(int i=0; i<n_reservation; i++)
        {
            time_t resTime = array[i].getReservationDate();
            cout<<array[i].getCustomerName()<<"\t\t"<<array[i].getRoomNumber()<<"\t\t"<<ctime(&resTime)<<"\t\t"<<endl;
        }
        system("PAUSE");
    }
}
void Staff::listcustumer()
{
    Customer *customers = new Customer[100];
    int n_customers = 0;

    FILE* fp = fopen(CUSTOMER_FILE , "r");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        char name[80];
        char id[80];
        time_t doj;
        char dummy[80];
        char pass[100][80];

        int i;
        for(i=0; !feof(fp); i++)
        {
            
             fscanf(fp , "userName: %s\n" , name);
             fscanf(fp , "NID: %s\n" , id);
             fscanf(fp , "DOJ: %lld\n" , &doj);
             fscanf(fp , "pass: %s\n" , pass[n_customers]);
            

             customers[n_customers].setName(name);
             customers[n_customers].setNid(name);
             customers[n_customers].setDoj(doj);
             n_customers++;
        }
        fclose(fp);
        clearScreen();
        cout << "Name\t\t\tDate Of Join\n\n";
        for(int i=0; i<n_customers; i++)
        {
            time_t doj = customers[i].getDoj();
            cout <<customers[i].getName() << "\t\t" << ctime(&doj) << endl;
        
        }
        system("PAUSE");

        cout << "Press 2 to delete Customer\n";
        int action;
        cin >> action;
        if(action == 2)
        {
            cout << "Choose Customer to delete : \n";
            int choice;
            cin >> choice;

            deletecustumer(customers , pass , choice-1 , n_customers);
        }
        
    }

}

void Staff::deletecustumer(Customer* array, char pass[][80], int index , int n)
{
    for(int i=index; i<n-1; i++)
   {
        array[i].setName(array[i+1].getName());
        array[i].setNid(array[i+1].getNid());
        array[i].setDoj(array[i+1].getDoj());
        strcpy(pass[i] , pass[i+1]);
   }

    //write to file

    FILE* fp = fopen(  CUSTOMER_FILE , "w");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        for(int i=0; i<n-1; i++)
        {
            fprintf(fp , "userName: %s\n" , array[i].getName().c_str());
            fprintf(fp , "NID: %d\n" , array[i].getNid());
            fprintf(fp , "DOJ: %ld\n" ,array[i].getDoj());
            fprintf(fp , "pass: %s\n" , pass[i]);
        }    
    }
    fclose(fp);
}
void Staff::searchcustumer()
{
    //Read Customers from File
    Customer *customers = new Customer[100];
    int n_customers = 0;

    FILE* fp = fopen(CUSTOMER_FILE , "r");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        char name[80];
        char id[80];
        time_t doj;
        char dummy[80];
        char pass[100][80];

        int i;
        for(i=0; !feof(fp); i++)
        {
            
             fscanf(fp , "userName: %s\n" , name);
             fscanf(fp , "NID: %s\n" , id);
             fscanf(fp , "DOJ: %lld\n" , &doj);
             fscanf(fp , "pass: %s\n" , pass[n_customers]);
            

             customers[n_customers].setName(name);
             customers[n_customers].setNid(id);
             customers[n_customers].setDoj(doj);
             n_customers++;
        }
        fclose(fp);
    } 

    //read reservations from file
    Reservation *array = new Reservation[100];
    int n_reservation = 0;

    fp = fopen(RESERVATION_FILE , "r");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        char name[80];
        int rn;
        time_t rt;
        time_t et;

        int i;
        for(i=0; !feof(fp); i++)
        {
            
             fscanf(fp , "customer Name : %s\n" , name);
             fscanf(fp , "room number : %d\n" , &rn);
             fscanf(fp , "Reservation date : %ld\n" , &rt);
             fscanf(fp , "Expiration date : %ld\n" , &et);

             array[n_reservation].setCustomerName(name);
             array[n_reservation].setRoomNumber(rn);
             array[n_reservation].setReservationDate(rt);
             array[n_reservation].setExpirationDate(et);
             n_reservation++;
        } 


    cout << "1) Search By Name\n";
    cout << "2) Search By NID\n";

    int choice;
    cin >> choice;

    switch(choice)
    {
        case 1 : 
        {
            string target;
            bool customer_found = false;
            cout << "Enter Customer Name : ";
            cin >> target;
            clearScreen();
            for(int i=0; i<n_customers; i++)
            {
                if(customers[i].getName() == target)
                {
                    customer_found = true;
                    cout << "Name : " << customers[i].getName() << endl;
                    cout << "NID : " << customers[i].getNid() << endl;
                    cout << "Date Of Join : " << customers[i].getDoj() << endl;
                    break;
                }
                
            }
            if(!customer_found) throw NOT_FOUND();
            bool found = false;
            int index;
            for(int i=0; i<n_reservation; i++)
            {
                if(array[i].getCustomerName() == target)
                {
                    found = true;
                    index = i;
                }
            }
            if(found)
            {
                cout << "Room Number : " << array[index].getRoomNumber()<<endl;
                cout << "Reservation Date : " << array[index].getReservationDate() <<endl;
                cout << "Expiration Date : " << array[index].getExpirationDate() << endl;
            }
            else cout << "No Reservation for this Customer\n";
            break;
        }
        case 2:
        {
            string target;
            string target_name;
            bool customer_found = false;
            cout << "Enter Customer NID : ";
            cin >> target;
            
            for(int i=0; i<n_customers; i++)
            {
                if(customers[i].getNid() == target)
                {
                    clearScreen();
                    customer_found = true;
                    target_name = customers[i].getName();
                    cout << "Name : " << customers[i].getName() << endl;
                    cout << "NID : " << customers[i].getNid() << endl;
                    cout << "Date Of Join : " << customers[i].getDoj() << endl;
                    break;
                }
            }
            if(!customer_found) throw NOT_FOUND();

            bool reservation_found = false;
            int index;
            for(int i=0; i<n_reservation; i++)
            {
                if(array[i].getCustomerName() == target_name)
                {
                    reservation_found = true;
                    index = i;
                }
            }
            if(reservation_found)
            {
                cout << "Room Number : " << array[index].getRoomNumber()<<endl;
                cout << "Reservation Date : " << array[index].getReservationDate() <<endl;
                cout << "Expiration Date : " << array[index].getExpirationDate() << endl;
            }
            else cout << "No Reservation for this Customer\n";
            break;
        }
        clearScreen();        
    }
}
}
string Staff:: getName() const
{
    return Name;
}
string Staff:: getDOB() const
{
    return DOB;
}
string  Staff::getdesignation() const
{
    return designation;
}
string Staff::getemail() const
{
    return email;
}
int  Staff::getsalary() const
{
    return salary;
}
int  Staff::getID() const
{
    return ID;
}
void Staff:: setName(string n)
{
    Name = n;
}
void Staff :: setDOB(string d)
{
    DOB = d;
}
void Staff :: setdesignation(string ds)
{
    designation = ds;
}
void  Staff :: setemail(string em)
{
    email = em;
}
void Staff :: setsalary(int s)
{
    salary = s;
};
void Staff ::setID(int id)
{
    ID = id;
}


Manager:: Manager()
{

}
void Manager :: managerScreen() 
{
    clearScreen();
    while(1)
    {

    
    cout << "\t\t\tWELCOME TO MANAGER ACCOUNT\t\t\t\n";
    cout <<"\t\t*please enter your choice*:\n\n";
    cout << "1)add employees"<<endl;
    cout << "2)list employees"<<endl;
    cout << "3)list custumer"<<endl;
   


    int choice;
    cin >> choice;
    cin.ignore();

    switch(choice)
    {
        case 1:
            Manager::addemployee();
            break;
            
        case 2:
            Manager::listemployees();
            break;
        case 3:
            Manager::listcustumer();
            break;
      
    }
    }
}
void Manager::listcustumer()
{
     clearScreen();  
    Customer *customers = new Customer[100];
    int n_customers = 0;

    FILE* fp = fopen(CUSTOMER_FILE , "r");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        char name[80];
        char id[80];
        time_t doj;
        char dummy[80];

        int i;
        for(i=0; !feof(fp); i++)
        {
            
             fscanf(fp , "userName: %s\n" , name);
             fscanf(fp , "NID: %s\n" , id);
             fscanf(fp , "DOJ: %lld\n" , &doj);
             fscanf(fp , "pass: %s\n" , dummy);
            

             customers[n_customers].setName(name);
             customers[n_customers].setNid(name);
             customers[n_customers].setDoj(doj);
             n_customers++;
        }
        cout << "Name\t\t\tDate Of Join\n\n";
        for(int i=0; i<n_customers; i++)
        {
            time_t doj = customers[i].getDoj();
            cout<<"\n-----------------------------------------------------------------------\n";
            cout<<customers[i].getName() << "\t\t\tDate Of Join :" << ctime(&doj) << endl;
        
        } 
        
    }
        fclose(fp);
       system("PAUSE");
       
}

void Manager:: listemployees()
{
    Staff *staffs = new Staff[100];
    char password[100][80];
    int n_staffs = 0;

    FILE* fp = fopen(  STAFF_FILE , "r");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        char name[80];
        int id;
        int salary;
        char dob[80];
        char designation[80];
        char email[80];

        int i;
        for(i=0; !feof(fp); i++)
        {
            
             fscanf(fp , "userName: %s\n" , name);
             fscanf(fp , "DOB: %s\n" ,dob);
             fscanf(fp , "designation: %s\n" , designation);
             fscanf(fp , "email: %s\n" , email);
             fscanf(fp , "ID: %d\n" , &id);
             fscanf(fp , "salary: %d\n" , &salary);
             fscanf(fp , "pass: %s\n" , password[n_staffs]);

             staffs[n_staffs].setName(name);
             staffs[n_staffs].setID(id);
             staffs[n_staffs].setDOB(dob);
             staffs[n_staffs].setdesignation(designation);
             staffs[n_staffs].setemail(email);
             staffs[n_staffs].setsalary(salary);
             if(staffs[0].getName().length() > 3)n_staffs++;
        }
        clearScreen();
        for(int i=0; i<n_staffs; i++)
        {
            
            
            cout 
            <<i+1 << " )\n"
            << "Name : " << staffs[i].getName() <<"\n"
            << "Date Of birth : " << staffs[i].getDOB() <<"\n"
            << "Designation: " << staffs[i].getdesignation() << "\n"  
            << "Email: " << staffs[i].getemail() << "\n" 
            << "ID: " << staffs[i].getID() << "\n" 
            << "Salary: " << staffs[i].getsalary() << "\n\n" ;
        }
        
    }
     fclose(fp);

     if(n_staffs>0) cout << "Press 1 to delete an Employee \n";
     cout << "Press 2 to go back\n";
     int action;
     cin >> action;

     switch(action)
     {
        case 1:
        {
        cout << "Choose Employee to Delete : \n";
        int choice;
        cin >> choice;

        if (choice >= 1 && choice <= n_staffs) {
            deletemployee(staffs, password, choice - 1, n_staffs);
            cout << "Employee deleted successfully.\n";
        } else {
            cout << "Invalid choice.\n";
        }
        break;
        }
        case 2:
        {
            managerScreen();
            break;
        }
         
        
    }
    
}
void  Manager::addemployee()
{
     string n  , email , pass , dob, designation;
            int id,salary;
            cout << "Enter Name : ";
            getline(cin , n);
            cout << "Enter Date Of Birth : ";
            getline(cin , dob);
            cout << "Enter Designation : ";
            getline(cin , designation);
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


            Staff myEmp(n , dob , salary , designation , email , id);
            dbInsertStaff(myEmp , pass);
}

void Manager::deletemployee(Staff* array , char pass[][80], int index , int n)
{
   for(int i=index; i<n-1; i++)
   {
        array[i].setName(array[i+1].getName());
        array[i].setID(array[i+1].getID());
        array[i].setdesignation(array[i+1].getdesignation());
        array[i].setsalary(array[i+1].getsalary());
        array[i].setemail(array[i+1].getemail());
        array[i].setDOB(array[i+1].getDOB());
        strcpy(pass[i] , pass[i+1]);
   }

    //write to file

    FILE* fp = fopen(  STAFF_FILE , "w");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        for(int i=0; i<n-1; i++)
        {
            fprintf(fp , "userName: %s\n" , array[i].getName().c_str());
            fprintf(fp , "DOB: %s\n" ,array[i].getDOB().c_str());
            fprintf(fp , "designation: %s\n" , array[i].getdesignation().c_str());
            fprintf(fp , "email: %s\n" , array[i].getemail().c_str());
            fprintf(fp , "ID: %d\n" , array[i].getID());
            fprintf(fp , "salary: %d\n" , array[i].getsalary());
            fprintf(fp , "pass: %s\n" , pass[i]);
        } 
    }
    fclose(fp);
   
}
string Manager:: getName() const
{
    return Name;
}
string Manager:: getDOB() const
{
    return DOB;
}
string Manager::getemail() const
{
    return email;
}
int  Manager::getsalary() const
{
    return salary;
}
int  Manager::getID() const
{
    return ID;
}

void Room::setoccupation(bool occup)
{
    occupation = occup;
}
bool Room::getoccupation() const
{
    return occupation;
}
int Room::getroomid()const
{
    return roomid;
}
roomType Room:: getRoomtype()
{
    return type;
}
int Room:: getNumberOfRooms()
{
    return numberOfrooms;
}
int Room::numberOfrooms = 0;

void Reservation::setCustomerName(string name)
{
    customer_name = name;
}
void Reservation::setRoomNumber(int rn)
{
    room_number = rn;
}
void Reservation::setReservationDate(time_t date)
{
    reservation_date = date;
}
void Reservation::setExpirationDate(time_t date)
{
     expiration_date = date;
}

string Reservation::getCustomerName() const
{
     return customer_name;
}
int Reservation::getRoomNumber() const
{
    return room_number;
}
 time_t Reservation::getReservationDate() const
{
    return reservation_date;
}

time_t Reservation::getExpirationDate() const
{
    return expiration_date;
 }