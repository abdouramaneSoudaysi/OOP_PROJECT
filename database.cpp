#include<iostream>
#include<cstdio>
#include"class.h"
#include"database.h"


void dbInsertCustomer(Customer& c , string pass)
{
    FILE* fp = fopen(CUSTOMER_FILE , "a");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        fprintf(fp , "userName: %s\nNID:%s\nDOJ:%lld\npass:%s\n" , c.getName().c_str() , c.getNid().c_str() , c.getDoj() , pass.c_str());
        cout << "Customer Added Succesfully\n";
    }


    fclose(fp);
    system("PAUSE");
 
}
  
void dbInsertStaff(Staff& s , string pass)
{
    FILE* fp = fopen(STAFF_FILE , "a");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        fprintf(fp , "userName: %s\nDOB: %s\ndesignation: %s\nemail: %s\nID: %d\nsalary: %d\npass: %s\n" , s.getName().c_str() , s.getDOB().c_str() , s.getdesignation().c_str() ,s.getemail().c_str() ,s.getID() , s.getsalary() , pass.c_str());
        cout << "Staff Added Succesfully\n";
    }


    fclose(fp);
    system("PAUSE");
}
void dbInsertManager(Manager& m , string pass)
{
    FILE* fp = fopen(MANAGER_FILE , "a");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        fprintf(fp , "userName:%s\nDOB:%s\nemail:%s\nID:%d\nsalary:%d\npass:%s\n" , m.getName().c_str() , m.getDOB().c_str() , m.getemail().c_str() ,m.getID() , m.getsalary() , pass.c_str());
        cout << "Manager Added Succesfully\n";
    }


    fclose(fp);
    system("PAUSE");
    
}

 
Credentials dbRetreiveCustomerCredentials(string _name)
{
    FILE* fp = fopen(CUSTOMER_FILE , "r");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        char dummy[80];
        char name[80];
        char pass[80];
        time_t dmy;
        
        Credentials *accounts = new Credentials[100];
        int i;
        for(i=0; !feof(fp); i++)
        {
             fscanf(fp , "userName: %s\n" , name);
             fscanf(fp , "NID: %s\n" , dummy);
             fscanf(fp , "DOJ: %lld\n" , &dmy);
             fscanf(fp , "pass: %s\n" , pass);
            
             accounts[i].user_name = name;
             accounts[i].user_pass = pass;
        }
        int n_accounts = i;
        for(int i=0; i<n_accounts; i++)
        {
            if(accounts[i].user_name == _name) return accounts[i];
        }
        
    }
        fclose(fp);
        Credentials not_found;
        not_found.user_name = "not found";
        return not_found;

}
Credentials dbRetreiveStaffCredentials(string _name)
{
    FILE* fp = fopen( STAFF_FILE, "r");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        char dummy[80];
        char name[80];
        char pass[80];
        int d;
        
        
        Credentials *accounts = new Credentials[100];
        int i;
        for(i=0; !feof(fp); i++)
        {
             fscanf(fp , "userName: %s\n" , name);
             cout << name << endl;
             fscanf(fp , "DOB: %s\n" , dummy);
             cout << dummy << endl;
             fscanf(fp , "designation: %s\n" , dummy);
             cout << dummy << endl;
             fscanf(fp , "email: %s\n" , dummy);
             cout << dummy << endl;
             fscanf(fp , "ID: %d\n" , &d);
             cout << d << endl;
             fscanf(fp , "salary: %d\n" , &d);
             cout << d << endl;
             fscanf(fp , "pass: %s\n" , pass);
             cout << pass << endl;
             accounts[i].user_name = name;
             accounts[i].user_pass = pass;
        }
        int n_accounts = i;
        for(int i=0; i<n_accounts; i++)
        {
            if(accounts[i].user_name == _name)
            cout << "Account found\n";
            return accounts[i];
        }
        
    }

        fclose(fp);
        Credentials not_found;
        not_found.user_name = "not found";
        return not_found;

}
Credentials dbRetreiveManagerCredentials(string _name)
{
    FILE* fp = fopen( MANAGER_FILE, "r");
    if(fp == NULL)
        cout << "Failed to open FIle\n";
    else
    {
        char dummy[80];
        char name[80];
        char pass[80];
        
        
        Credentials *accounts = new Credentials[100];
        int i;
        for(i=0; !feof(fp); i++)
        {
             fscanf(fp , "userName: %s\n" , name);
             fscanf(fp , "DOB: %s\n" , dummy);
             fscanf(fp , "email: %s\n" , dummy);
             fscanf(fp , "ID: %s\n" , dummy);
             fscanf(fp , "salary: %s\n" , dummy);
             fscanf(fp , "pass: %s\n" , pass);

             accounts[i].user_name = name;
             accounts[i].user_pass = pass;
        }
        int n_accounts = i;
        for(int i=0; i<n_accounts; i++)
        {
            if(accounts[i].user_name == _name) return accounts[i];
        }
        
    }

        fclose(fp);
        Credentials not_found;
        not_found.user_name = "not found";
        return not_found;

}
