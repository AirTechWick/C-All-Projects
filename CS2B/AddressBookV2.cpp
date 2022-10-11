//  ----------------------------------------------------------------------
// File Name: AddressBook.cpp

// Version 1.0

// Date: 06-07-2020

// This program is to build a simplified console version of Address Book 
// App. The Address Book will allow employees or contractors 
// working for a company to search contact information of their peers. 
// The program should allow users to:
//   View all employees/contractors contact information
//   Search by name
//   Insert new contact

//  CS 2B Assignment #3 - Erik Rodriguez

//  ----------------------------------------------------------------------

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

//--------------------
// class declarations
//--------------------
class Name 
{
    private:
        string first_name_;
        string last_name_;
    public:
    // constructors / destructors
        Name():first_name_("N/A"), last_name_("N/A"){};
        Name(string first_name, string last_name):first_name_(first_name), last_name_(last_name){};
        ~Name(){};
    // behavioral functions
        bool operator==(const Name & left) const;
    // accessors/mutators
        string get_first_last_name() const;
};

class Contact // abstract class is classified by having one or more pure virtual functions
{
    protected:
        Name contact_name_;
        string business_phone_;
        string email_;
        int location_;

    private:
        Contact * p_next;

    public:
    // constructors / destructors
        Contact();
        Contact(string first_name, string last_name, string phone_number, string email, int location);
        virtual ~Contact();
    // behavioral functions
        virtual void ShowContact() const = 0; // implementing a pure virtual function
    // accessors/mutators 
        Name get_contact_name() const;
        string get_business_phone() const;
        string get_email() const;
        int get_location() const;
        Contact * get_next() const;
        
        void set_contact_name(string first, string last);
        void set_business_phone(string b_phone);
        void set_email(string email);
        void set_location(int location);
        void set_next(Contact * next);

};

class EmployeeContact : public Contact
{
    private:
        string title_;
        string department_;
    public:
    // constructors / destructors
        EmployeeContact();
        EmployeeContact(string first_name, string last_name, string phone_number, string email, int location, string title, string department);
        virtual ~EmployeeContact();
    // behavioral functions
        virtual void ShowContact() const;
    // accessors/mutators 
        string get_title() const;
        string get_department() const;
        
        void set_title(string title);
        void set_department(string department);
};

class ContractorContact : public Contact
{
    private:
        string company_;
        int assignment_duration_;
    public:
    // constructors / destructors
        ContractorContact();
        ContractorContact(string first_name, string last_name, string phone_number, string email, int location, string company, int assignment_duration);
        virtual ~ContractorContact();
    // behavioral functions
        virtual void ShowContact() const;
    // accessors/mutators 
        string get_company() const;
        int get_assignment_duration() const;

        void set_company(string company);
        void set_assignment_duration(int duration);
        
};

class ContactList
{
    private:
        Contact * p_head; 
    // behavioral functions
        Contact * FindContact(const Name & name);
        void Insert(Contact * contact_object);

    public:
    // constructors / destructors
        ContactList();
        virtual ~ContactList();
    // behavioral functions
        void Init();
        void ShowAllContacts();
        void SearchByName(const Name & name); //displays contact info
        void SearchByDepartment(string department); //displays contact info

};

class AddressBook
{
    private:
        string company_name_;
        ContactList list_of_contacts_;
    // behavioral functions
        void Menu();
        int GetUserOption();
        void ShowAllContacts();
        void SearchByName();
        void SearchByDepartment();
        void Quit();
    public:
    // constructors/destructors
        AddressBook();
        AddressBook(string company_name);
        virtual ~AddressBook();
    // behavioral functions        
        void Init();
        void Run();
};


//--------------------------
// implementation & testing
//--------------------------
main()
{
    AddressBook * ErikCoAddressBook = nullptr;

    ErikCoAddressBook = new AddressBook("Erik Co.");

    ErikCoAddressBook->Init();

    ErikCoAddressBook->Run();

    delete ErikCoAddressBook;

    return 0;
}

//------------------------
// Name definitions
//------------------------
bool Name::operator==(const Name & right) const
{
    string left_first_and_last = this->first_name_ + this->last_name_;
    string right_first_and_last = right.first_name_ + right.last_name_;

    // Converting strings to lowercase
    transform(left_first_and_last.begin(), left_first_and_last.end(), left_first_and_last.begin(), ::tolower);

    transform(right_first_and_last.begin(), right_first_and_last.end(), right_first_and_last.begin(), ::tolower);
    
    return (left_first_and_last == right_first_and_last);
}

string Name::get_first_last_name() const
{
    return this->first_name_ + " " + this->last_name_;
}

//------------------------------------
// Contact definitions
//------------------------------------

Contact::Contact(): contact_name_(Name()), business_phone_("1-408-790-0000"), email_("xyz@tpcommunications.com"), location_(0) , p_next(nullptr){}

Contact::Contact(string first_name, string last_name, string phone_number, string email, int location): business_phone_(phone_number), email_(email), location_(location), p_next(nullptr){ contact_name_ = Name(first_name, last_name); }

Contact::~Contact()
{

    cout << contact_name_.get_first_last_name() << " has gone home...\n";
}

// Contact accessors / mutators definitions

Name Contact::get_contact_name() const
{
    return contact_name_;
}

string Contact::get_business_phone() const
{ 
    return business_phone_;
}

string Contact::get_email() const
{ 
    return email_;
}

int Contact::get_location() const
{ 
    return location_;
}

Contact * Contact::get_next() const
{ 
    return p_next;
}

void Contact::set_contact_name(string first, string last)
{
    contact_name_ = Name(first,last);
}

void Contact::set_business_phone(string b_phone)
{
    business_phone_ = b_phone;
}

void Contact::set_email(string email)
{
    email_ = email;
}

void Contact::set_location(int location)
{
    location_ = location;
}

void Contact::set_next(Contact * next)
{
    p_next = next;
}

//-----------------------------
// EmployeeContact definitions
//-----------------------------

EmployeeContact::EmployeeContact(): Contact(), title_("New Hire"), department_("New Hire"){}

EmployeeContact::EmployeeContact(string first_name, string last_name, string phone_number, string email, int location, string title, string department): Contact(first_name, last_name, phone_number, email, location), title_(title), department_(department){}

EmployeeContact::~EmployeeContact(){}

void EmployeeContact::ShowContact() const
{
    // Header of Table
    cout << left << setw(20*1.2) << "Name";
    cout << left << setw(15*1.2) << "Title";
    cout << left << setw(25*1.2) << "Department";
    cout << left << setw(15*1.2) << "Location";
    cout << left << setw(20*1.2) << "Phone";
    cout << "Email\n";
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
    
    // Employee Contact Info
    cout << left << setw(20*1.2) << contact_name_.get_first_last_name();
    cout << left << setw(15*1.2) << title_; 
    cout << left << setw(25*1.2) << department_;  
    cout << "Room " << location_; 
    cout << left << setw(10*1.2) << " ";
    cout << left << setw(20*1.2) << business_phone_; 
    cout << email_ << "\n\n"; 
}

// Contact accessors / mutators definitions

string EmployeeContact::get_title() const
{
    return title_;
}

string EmployeeContact::get_department() const
{
    return department_;
}

//-------------------------------
// ContractorContact definitions
//-------------------------------

ContractorContact::ContractorContact():Contact(), company_("ABC Wireless"), assignment_duration_(3){}
ContractorContact::ContractorContact(string first_name, string last_name, string phone_number, string email, int location, string company, int assignment_duration): Contact(first_name,last_name, phone_number, email, location), company_(company), assignment_duration_(assignment_duration){}

ContractorContact::~ContractorContact(){}

void ContractorContact::ShowContact() const
{
    // Header of Table
    cout << left << setw(20*1.2) << "Name";
    cout << left << setw(23*1.2) << "Duration";
    cout << left << setw(15*1.2) << "Company";
    cout << left << setw(14*1.2) << "Location";
    cout << left << setw(20*1.2) << "Phone";
    cout << "Email\n";
    cout << "-------------------------------------------------------------------------------------------------------------------------------------------------" << endl;

    // Contractor Contact Info
    cout << left << setw(20*1.2) << contact_name_.get_first_last_name();
    cout << left << setw(2*1.2) << assignment_duration_;
    cout << " months(contractor)";
    cout << left << setw(5*1.2) << " ";
    cout << left << setw(15*1.2) << company_;
    cout <<  "Room ";
    cout << left << setw(10*1.2) << location_; 
    cout << left << setw(19*1.2) << business_phone_; 
    cout << email_ << "\n\n"; 
}

// ContractorContact accessors / mutators definitions

string ContractorContact::get_company() const
{
    return company_;
}

int ContractorContact::get_assignment_duration() const
{
    return assignment_duration_;
}

void ContractorContact::set_company(string company)
{
    company_ = company;
}

void ContractorContact::set_assignment_duration(int duration)
{
    assignment_duration_ = duration;
}

//-------------------------
// ContactList definitions
//-------------------------

ContactList::ContactList(): p_head(nullptr){}

ContactList::~ContactList()
{
    Contact * p_current_node = p_head;

    Contact * next_node = nullptr;

    while(p_current_node != nullptr)
    {   
        next_node = p_current_node->get_next();

        delete p_current_node;

        p_current_node = next_node;
    }
}

Contact * ContactList::FindContact(const Name & name)
{
    Contact * p_current_node = p_head;
    
    while(p_current_node != nullptr)
    {
        if(p_current_node->get_contact_name() == name)
        {
            return p_current_node;
        }
        p_current_node = p_current_node->get_next();
    }
    return nullptr;
}

void ContactList::Insert(Contact * p_contact_object)
{
    p_contact_object->set_next(p_head);

    p_head = p_contact_object;
}

void ContactList::Init()
{
    Insert (new EmployeeContact ("David", "Summer", "1-408-790-1682", "davids@tpcommuniations", 23,  "Software Engineer",  "Manufacturer"));

    Insert (new EmployeeContact ("Jennifer", "Hans", "1-408-790-2381", "jenniferh@tpcommuniations", 17,  "HR Representative",  "Finance"));

    Insert (new ContractorContact ( "Cindy", "Morgan", "1-408-790-3953", "cindym@tpcommuniations", 43, "TK Consultings", 12));

    Insert (new EmployeeContact ("Jordan", "Nguyen", "1-408-790-2793", "jordan@tpcommuniations", 23,  "App Engineer",  "Marketing"));

    Insert (new EmployeeContact ("Steven", "Mendoza", "1-408-790-3804", "steven@tpcommuniations", 17,  "Mech Engineer",  "Marketing"));

    Insert (new ContractorContact ( "Andy", "Rodriguez", "1-408-790-4915", "andy@tpcommuniations", 43, "TK Consultings", 12));

    Insert (new EmployeeContact ("Issac", "Federico", "1-408-790-5026", "issac@tpcommuniations", 23,  "Manager",  "IT"));

    Insert (new EmployeeContact ("Jacob", "Flam", "1-408-790-6137", "jacob@tpcommuniations", 17,  "Product Support",  "Sales"));

    Insert (new ContractorContact ( "Alex", "Truth", "1-408-790-7248", "alex@tpcommuniations", 43, "TK Consultings", 12));

    Insert (new EmployeeContact ("Anthony", "Kia", "1-408-790-8359", "anthony@tpcommuniations", 23,  "Test Technician",  "Marketing"));

    Insert (new EmployeeContact ("Jenn", "River", "1-408-790-9460", "jenn@tpcommuniations", 17,  "Software Engineer",  "Manufacturer"));

    Insert (new ContractorContact ( "Chris", "Liop", "1-408-790-4571", "chris@tpcommuniations", 43, "TK Consultings", 12));

    Insert (new EmployeeContact ("Jose", "Yu", "1-408-790-1682", "jose@tpcommuniations", 23,  "Business Analyst",  "IT"));

    Insert (new EmployeeContact ("Sean", "Hana", "1-408-790-5692", "sean@tpcommuniations", 17,  "Admin Assistant",  "Human Resources"));

    Insert (new ContractorContact ( "Sheri", "Kerry", "1-408-790-6703", "sheri@tpcommuniations", 43, "TK Consultings", 12));

    Insert (new EmployeeContact ("Karen", "Truman", "1-408-790-8914", "karen@tpcommuniations", 17,  "Director",  "Human Resources"));
}


void ContactList::ShowAllContacts()
{
    Contact * p_current_node = p_head;

    while(p_current_node != nullptr)
    {
        p_current_node->ShowContact();

        p_current_node = p_current_node->get_next();
    }
}

void ContactList::SearchByName(const Name & name)
{
    Contact * p_found_contact = FindContact(name);

    if(p_found_contact != nullptr)
    {
        p_found_contact->ShowContact(); 
    }
    else
    {
        cout << "\nError: name not found\n\n";
    }
}

void ContactList::SearchByDepartment(string department)
{
    Contact * p_current_node = p_head;

    EmployeeContact * p_employee_current_node = dynamic_cast<EmployeeContact*>(p_current_node);

    int count = 0;

    while(p_current_node != nullptr)
    {
        if(p_employee_current_node != nullptr && p_employee_current_node->get_department() == department)
        {
            count++;

            p_current_node->ShowContact();
        }
        p_current_node = p_current_node->get_next();
        
        p_employee_current_node = dynamic_cast<EmployeeContact*>(p_current_node); 
    }

    if(count == 0)
    {
        cout << "\nNo employees found in department." << endl;
    }
}

//-------------------------
// AddressBook definitions
//-------------------------

AddressBook::AddressBook(): company_name_("ABC Wireless"){}

AddressBook::AddressBook(string company_name): company_name_(company_name){}

AddressBook::~AddressBook(){}

void AddressBook::Init()
{
    list_of_contacts_.Init();
}

void AddressBook::Run()
{
    int user_input;

    do 
    {
        Menu();
        user_input = GetUserOption();

        switch(user_input)
        {
            case 1:
                ShowAllContacts();
                break;
            case 2:
                SearchByName();
                break;
            case 3:
                SearchByDepartment();
                break;
        }
    } while(user_input != 4);

    if(user_input == 4)
    {
        Quit();
    }
}


void AddressBook::Menu()
{
    cout << endl << company_name_ << " Address Book Menu\n";
    cout << "1. View all Contacts\n";
    cout << "2. Searh by Name\n";
    cout << "3. Search by Department\n";
    cout << "4. Quit\n\n";
}

int AddressBook::GetUserOption()
{
    string s_user_response;
    int user_response;

    cout << "Select an option by inserting a number: ";
    getline(cin, s_user_response);

    istringstream (s_user_response) >> user_response;

    return user_response;
}

void AddressBook::ShowAllContacts()
{
    list_of_contacts_.ShowAllContacts();
}

void AddressBook::SearchByName()
{
    string user_first_name;
    string user_last_name;

    cout << "Insert a First Name: ";
    getline(cin, user_first_name);

    cout << "Insert a Last Name: ";
    getline(cin, user_last_name);

    Name user_name = Name(user_first_name, user_last_name);

    list_of_contacts_.SearchByName(user_name);
}

void AddressBook::SearchByDepartment()
{
    string user_department;

    cout << "Enter a Department: ";
    getline(cin, user_department);

    list_of_contacts_.SearchByDepartment(user_department);
}

void AddressBook::Quit()
{
    cout << "Goodbye\n";
}