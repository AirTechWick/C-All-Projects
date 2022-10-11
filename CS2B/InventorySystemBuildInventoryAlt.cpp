//  ----------------------------------------------------------------------
// File Name: InventoryManagementSystem.cpp

// Version 1.0

// Date: 05-15-2020

// An inventory management system for an electronics store. The inventory system should have the following functionalities:
// BuildInventory: read a text file containing electronics products information and dynamically store them in an array of pointers.
// ShowInventory: display all inventory items.
// UpdateInventory: ask for item id and quantity. If found display cost and update Product object info (reduce Product's quantity and potentially update restocking flag).
// Terminate: save current inventory to a text file.

//  CS 2B Assignment #1 - Erik Rodriguez

//  ----------------------------------------------------------------------


#include <iostream> 
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std;

// global variables

const int g_kMaxArraySize = 512;

// class declarations

class InventoryItem
{
    protected:
        int item_id_;
        bool restocking_;

    public:
        // constructor/destructor

        InventoryItem();
        InventoryItem(bool restocking);
        ~InventoryItem();

        // accessor/mutator

        bool get_restocking() const;
        int get_item_id() const;
        void set_restocking(bool restocking);
        void set_item_id(int item_id);        

        // behavioral functions

        void Display() const;
        int GenerateItemID(int min, int max);
};


class InventorySystem
{
    private:
        string store_name_;
        int store_id_;
        InventoryItem * p_item_list_[g_kMaxArraySize];
        int item_count_;

        // Private member function

        InventoryItem * FindInventoryItem(int item_id);
    
    public:

        // constructors/destructor

        InventorySystem();
        InventorySystem(string store_name, int store_id);
        ~InventorySystem();

        // accessor/mutator

        string get_store_name() const;
        int get_store_id() const;
        int get_item_count() const;

        void set_store_name();
        void set_store_id();
        void set_item_count();

        // behavioral functions

        void BuildInventory();
        void ShowInventory() const;
        void UpdateInventory();
        void Terminate() const;

};


class Product : public InventoryItem
{
    private:
        string name_;
        int quantity_;
        double price_;
    
    public:

        // constructors/destructor

        Product();
        Product(bool restocking, string name, int quantity, double price);
        ~Product();

        // accessor/mutator

        string get_name() const;
        int get_quantity() const;
        double get_price() const;

        void set_name(string name);
        void set_quantity(int quantity);
        void set_price(double price);

        // behavioral functions

        void Display() const;
        double Cost(int quantity) const;   
};

// implementation & testing

int main()
{

/*
// testing inventory system class 
InventorySystem * p_valley_fair_system = nullptr;

p_valley_fair_system = new InventorySystem("Valley Fair", 19876);

cout << "Store ID: " << p_valley_fair_system->get_store_id() << endl;

p_valley_fair_system->BuildInventory();

delete p_valley_fair_system;*/


/*
// testing inventory items and display function
InventoryItem * p_inventory_item = nullptr;

p_inventory_item = new InventoryItem(true);

cout << p_inventory_item->get_item_id() << endl;

p_inventory_item->Display();
*/



/* 
// testing if random IDs are being created for each product, and is inheriting the item_id member from its base class
Product * p_valley_product = nullptr;
Product * p_valley_product2 = nullptr;


p_valley_product = new Product();
p_valley_product2 = new Product();


cout << "Product ID: " << p_valley_product->get_item_id() << endl;
cout << "Product ID: " << p_valley_product2->get_item_id() << endl;
*/



/*
// testing all the members that Product class contains 
Product * p_valley_product = nullptr;
p_valley_product = new Product();

// this is also the order in which all of the members are declared
cout << "int ProductID: " << p_valley_product->get_item_id() << " bool Restocking: " << p_valley_product->get_restocking() <<  " string Name: " << p_valley_product->get_name() << " int Quantity: " << p_valley_product->get_quantity() << " double Price: " << p_valley_product->get_price() << endl;
*/


return 0;
}

//----------------------------------
// InventoryItem definitions
//----------------------------------


// constructors/destructor definitions

InventoryItem::InventoryItem():  restocking_(false), item_id_(GenerateItemID(1,9999)){}

InventoryItem::InventoryItem(bool restocking): restocking_(restocking), item_id_(GenerateItemID(1,9999)){}

InventoryItem::~InventoryItem()
{
    cout << "InventoryItem " << item_id_ << " with " << restocking_ << " restocking destroyed..." << endl;
}

// behavioral function definitions

int InventoryItem::GenerateItemID(int min, int max)
{
    int id = 0;

    id = min + rand ( ) % (max - min + 1); // generate a number between min-max inclusively

    return id;
}

void InventoryItem::Display() const
{
    cout << "Item ID: " << setw(4) << setfill('0') << item_id_ << endl;

    cout << "Restocking: " << restocking_ << endl;
}

// accessor/mutator

bool InventoryItem::get_restocking() const
{
    return restocking_;
}

int InventoryItem::get_item_id() const
{
    return item_id_;
}

void InventoryItem::set_restocking(bool restocking)
{
    restocking_ = restocking;
}

void InventoryItem::set_item_id(int item_id)
{
    item_id_ = item_id;
}      



//----------------------------------
// InventorySystem definitions
//----------------------------------


// constructors/destructor definitions

InventorySystem::InventorySystem(): store_name_("N/A"), store_id_(0)
{
    for (int i = 0; i < g_kMaxArraySize; i++)
    {
        p_item_list_[i] = nullptr;

        p_item_list_[i] = new InventoryItem();

        cout << p_item_list_ << endl;
    }
    srand(time(NULL));
}

InventorySystem::InventorySystem(string store_name, int store_id) : store_name_(store_name), store_id_(store_id)
{

    for (int i = 0; i < g_kMaxArraySize; i++)
        {
            p_item_list_[i] = nullptr;

            p_item_list_[i] = new InventoryItem();
        }        
}

InventorySystem::~InventorySystem()
{
    for(int i=0; i < g_kMaxArraySize; i++)
    {
        delete p_item_list_[i];
    }
}

// private member function 

InventoryItem * InventorySystem::FindInventoryItem(int item_id)
{
    bool found = false;

    int count = 0;

    InventoryItem * p_item_inside_list = nullptr; 

    p_item_inside_list = p_item_list_[0];

    int item_id_inside_list = p_item_inside_list->get_item_id();

    cout << "Item ID inside the list: " << item_id_inside_list << endl; 

    while(found == false)
    {

        if(item_id == item_id_inside_list)
        {
            found = true;

            return p_item_inside_list;
        }

        if(count == g_kMaxArraySize)
        {
            return nullptr;
        }

        count++;

        p_item_inside_list++;

    }

    return nullptr;
    
}

// behavioral function definitions

void InventorySystem::BuildInventory()
{
    ifstream fin("ProductRecords.txt");

    Product * p_product_in_record;

    //local variables
    bool restock = 0;
    string name = "";
    int quantity = 0;
    double price = 0.00;

    int size = 0;

    if(!fin)
    {
        cout << "Error: Failed to open input file." << endl;
        exit(-1);
    }

    while( (fin >> restock >> name >> quantity >> price) && (size < g_kMaxArraySize))
    {
        p_product_in_record = new Product(restock, name, quantity, price);
        
        cout << "Product loaded into array: " << p_product_in_record->get_name() << endl;

        p_item_list_[size] = p_product_in_record;

        ++size;

        item_count_++;
    }

    fin.close();

    // size contains how many Products are loaded into the array
    // now the array can be proccessed if needed

    cout << "Item Count: " << item_count_ << endl;
}

void InventorySystem::ShowInventory() const
{
    for(int i = 0; i < item_count_; i++)
    {
        InventoryItem * p_item_in_list = nullptr; 

        p_item_in_list = p_item_list_[0];

        //p_item_in_list->
        // finish working on display functions



    }
}


// accessor/mutator

int InventorySystem::get_store_id() const
{
    return store_id_;
}



//----------------------------------
// Product definitions
//----------------------------------

// constructors/destructor definitions

Product::Product(): InventoryItem(), name_("N/A"), quantity_(0), price_(0.00){}

Product::Product(bool restocking, string name, int quantity, double price): InventoryItem(restocking), name_(name), quantity_(quantity), price_(price){}

Product::~Product()
{
    cout << "Product: " << item_id_ << " Name: " << name_ << " Quantity: " << quantity_ << " Price: " << price_ << " Restocking: " << restocking_ << " destroyed..." << endl;
}

// accessors/mutators

string Product::get_name() const
{
    return name_;
}

int Product::get_quantity() const 
{
    return quantity_;
} 

double Product::get_price() const 
{
    return price_;
}

void Product::set_name(string name)
{
    name_ = name;
} 

void Product::set_quantity(int quantity)
{
    quantity_ = quantity;
}

void Product::set_price(double price)
{
    price_ = price;
}
