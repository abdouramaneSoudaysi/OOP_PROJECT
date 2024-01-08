#include<string>
#pragma once
#include<ctime>

using namespace std;

enum roomType{single , dbl};
class Reservation;

class Bill{
    public:
    double amount;
    int getAmount() const;
    void setAmount(int amt);
    template<typename T>
    void increase(T amt);
    void clear();
};

class Customer
{
    private:
        string name;
        string NID;
        time_t dateOfJoin;
        int roomNumber;
        Bill bill;

    public:
        Customer();
        Customer(string _name , string _NID , time_t  _doj) : name(_name) , NID(_NID) , dateOfJoin(_doj){};
        void customerScreen();
        void reservation();
        void cancelReservation(Reservation* array , int index , int n);
        void extendReservation(Reservation*array ,int index ,int n, time_t new_date);
        void orderFood();
        void listActivities();
        string getName() const;
        string getNid() const;
        time_t getDoj() const;
        int getRoomNumber() const;
        void setRoomNumber(int rn);
        void setName(string n);
        void setNid(string n);
        void setDoj(time_t d);
        

    
};
class Employees
{
    virtual string getName() const = 0;
    virtual string getDOB() const = 0;
    virtual string getemail() const = 0;
    virtual int getID() const = 0; 
    
};
class Staff:public Employees
{   
    private:
    string Name;
    string DOB;
    string designation;
    string email;
    int  ID;
    int salary;

    class NOT_FOUND //exception class
    {
        public:
        NOT_FOUND()
        {
            cout << "Customer Not Found\n";
        }
    };
    public:
    Staff();
    Staff(string _Name, string _DOB, int salary, string design, string email,int _ID )
    : Name(_Name), DOB(_DOB), salary(salary), designation(design), email(email),ID(_ID){}
    

    void staffScreen();
    void listroom();
    void listcustumer();
    //void addnewcustumer();
    void deletecustumer(Customer* ,char pass[][80] , int index , int n);
    void searchcustumer();

   string getName() const;
   string getDOB() const;
   string getdesignation() const;
   string getemail() const;
   int getsalary() const;
   int getID() const; 
   void setName(string n);
   void setDOB(string d);
   void setdesignation(string ds);
   void setemail(string em);
   void setsalary(int s);
   void setID(int id);
};
class Manager : public Employees
{
    private:
    string Name;
    string DOB;
    string email;
    int  ID;
    int salary;

    public:
    Manager();
    Manager(string _Name, string _DOB, string _email,int _ID,int _salary)
    : Name(_Name), DOB(_DOB), email(_email),ID(_ID),salary(_salary) {}

    void managerScreen();
    void listcustumer();
    void listemployees();
    void addemployee();
    void deletemployee(Staff* array ,char pass[][80], int index , int n);
    //void viewreport();

    string getName() const;
    string getDOB() const;
    string getdesignation() const;
    string getemail() const;
    int getsalary() const;
    int getID() const;

    void setName(string n) const;
    void setDOB(string d) const;
    void setdesignation(string ds) const;
    void setemail(string e) const;
    void setsalary(int s) const;
    void setID(int id) const;
};

class Room
{
    private:
    int roomid;
    bool occupation;
    roomType type;
    static int numberOfrooms;
    
    public:
    Room()
    {
        occupation = false;
        roomid = numberOfrooms++;
    }
    Room(roomType roomtype):  type(roomtype){
        occupation = false;
        roomid = numberOfrooms++;
    }
    void setoccupation(bool occup);
    void setRoomType(roomType r);
    bool getoccupation()const;
    int getroomid() const;
    roomType getRoomtype();
    static int getNumberOfRooms();


};

class Reservation
{
    string customer_name;
    int room_number;
    time_t reservation_date;
    time_t expiration_date;

    public:
    Reservation(){}
    void setCustomerName(string name);
    void setRoomNumber(int rn);
    void setReservationDate(time_t date);
    void setExpirationDate(time_t date);
    
    string getCustomerName() const;
    int getRoomNumber() const;
    time_t getReservationDate() const;
    time_t getExpirationDate() const;
    
};
