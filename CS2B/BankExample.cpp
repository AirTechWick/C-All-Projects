//---------------------------------------------------------------------------------------------------------------------------

//  File name:  Banking.cpp

//  Version 1.0

//   Date: 04-09-2018

//  Program purpose: This program is to process Bank accounts.

//  Disclaimer: If this program is working it's written by the author below. If it is not I don't know who wrote it.

//  Revision history:

//   Date                  Programmer             Change ID   Description

//   04/09/18           TP @CS Dept.            1273            Initial implementation

//   04/15/18           TP @CS Dept.            1273           Revise for performance consideration
 //--------------------------------------------------------------------------------------------------------------------------------

 

#include <iostream>

#include <iomanip>

#include <string>

 

using namespace std;

 

// forward class declarations

class BankAccount;

// global function declarations

BankAccount *  SearchAccount ( string to_account);

 

// class declarations

class BankAccount {

    // Member data and static data (should be made private) - do not initialize them here.

   // It's always a good programming practice to do it in constructors instead.

     private:

           string   account_number_;

           double  balance_;

           int  years_ ;

           static  string routing_number_ ;

           double *p_test; 

        public:

             // constructors  -- it's desirable to provide both default constructor

             // and non-default constructor. They should be made public.

              BankAccount ( );

              BankAccount (string account_number, double balance, int years);

             // always define destructor even though it does nothing.

              ~BankAccount ( );

 

               // accessor/mutator functions (should be made public)

               int get_balance ( ) const  ;

               void  set_balance (double balance)  ;

               // public static function - getter of private static data

               static  string get_routing_number ( )  ;

                // behavioral member functions (mostly public - some private for internal usage)

                void Deposit (double amount);

                bool  TransferFund  (string to_account, double amount);

                void testBankFunction ();

 };

//-------------------------------------------------------------------------------------------------------------------

// define static data

string BankAccount::routing_number_  = "0012183892" ;

 

//-------------------------------------------------------------------------------------------------------------------

// entry point of your program

int main (  ) {

    BankAccount  bank_account ("Jane", 12345, 500.00);

    BankAccount Erik;

    BankAccount Bob ("123456", 2031, 3);

    BankAccount testBankFunction();

    return 0;

}

//--------------------------------------------------------------------------------------------------------------------

// Bank Account definitions

BankAccount::BankAccount ( ) :  balance_ (0.0), years_(0)  { }

BankAccount::BankAccount  (string account_number, double balance, int years)  :

account_number_ (account_number), balance_(balance), years_ (years)  { }

BankAccount::~BankAccount ( )  { }

//-------------------------------------------------------------------------------------------------------------------

int  BankAccount::get_balance ( ) const  { return  balance_; }

void  BankAccount::set_balance (double balance)   { balance_ = balance; }

string BankAccount::get_routing_number ( )  { return routing_number_ ; }  // why this function can't be declared as a const function as it's a getter itself. Please post your opinion in the public Forum.

//-------------------------------------------------------------------------------------------------------------------

void  BankAccount::Deposit (double amount) {

     if  (amount > 0)  {      

               balance_ += amount;

     }

     // or   balance +=  (amount > 0) ? amount : 0 ;

}

//-------------------------------------------------------------------------------------------------------------------

bool  BankAccount::TransferFund  (string to_account, double amount)  {

         BankAccount *  p_account = SearchAccount (to_account);  // pointer is used here. It will be covered in more details next.

         if ( (amount > 0) && (balance_ >= amount) ) {

                p_account->Deposit (amount);

                balance_  += amount;

                return true;


         }
         return false;

}
//-------------------------------------------------------------------------------------------------------------------


void BankAccount::testBankFunction () {
  


}



//-------------------------------------------------------------------------------------------------------------------

// global function definitions

BankAccount *  SearchAccount ( string to_account)  {

          // searching account from bank data base

          // return a pointer to the account (we will discuss pointer soon.

        BankAccount *found_account; // Have to use BankAccount when creating new objects

        return found_account;

}

//--------------------------------------------------------------------------------------------------------------