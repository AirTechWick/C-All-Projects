//  ----------------------------------------------------------------------
// File Name: MovieSystem.cpp

// Version 1.0

// Date: 04-28-2020

// This program is for a movie ticket master system. 
// The movie system should do the following: View all movies, Search a movie, Purchase a Movie Ticket. 

//  CS 2B Assignment #1 - Erik Rodriguez

//  ----------------------------------------------------------------------


#include <iostream> 
#include <string>
#include <sstream>

using namespace std;

// forward class declarations

class Movie;
class MovieTicketMaster;

// class declarations

class Movie 
{

    private: 

        string movie_name_;
        int seats_available_;
        double ticket_price_;

    public:

        // constructor/destructor

        Movie();
        Movie(string movie_name, int seats_available, double ticket_price);
        ~Movie(); // display “Movie <movie name> object is no longer showing …”

        // accessor/mutator

        string get_movie_name() const;
        int get_seats_available() const;
        double get_ticket_price() const;

        void set_movie_name( string movie_name );
        void set_seats_available( int seats_available );
        void set_ticket_price( double ticket_price );

        // behavioral functions
        
        double Purchase_Ticket(int number_of_tickets); // take an integer (number of tickets requested) and return total cost. If the requested number of tickets are more than seats available return -1. Otherwise compute the total cost (function return value) and deduct the seats by number of requested tickets.
        void Display(); // display all information about the movie. Nicely format your output.

};


class MovieTicketMaster 
{

    private:

        string theater_name_;
        string location_;
        int movie_count_;
        Movie movie_objects_[32];

        // helper functions

        void Menu();
        void ViewMovies();
        void SearchMovies();
        void PurchaseTicket();
        Movie * FindMovie(string movie_name);

    public: 
        
        // constructor/destructor

        MovieTicketMaster();
        MovieTicketMaster(string theater_name, string location, int movie_count);
        ~MovieTicketMaster(); // Create a definition for it that says “Theater <theater name> at <theater location> is currently closed.”

        // accessor/mutator

        string get_theater_name() const;
        string get_location() const;
        int get_movie_count() const;

        void set_theater_name();
        void set_location();
        void set_movie_count();

        // behavioral functions

        void Init(); // This function is to initialize the array of Movie objects
        void Run();

};

// implementation & testing

int main() 
{

    MovieTicketMaster * p_Object = nullptr;

    p_Object = new MovieTicketMaster("Digital Films Theater","Los Altos Hills",0);

    p_Object->Init();

    p_Object->Run();

    delete p_Object;

    return 0;

}

//----------------------------------
// Movie Ticket Master definitions
//----------------------------------

// constructors/destructor definitions


MovieTicketMaster::MovieTicketMaster(): movie_count_(0) {}

MovieTicketMaster::MovieTicketMaster(string theater_name, string location, int movie_count) :
theater_name_(theater_name), location_(location), movie_count_(movie_count) {}

MovieTicketMaster::~MovieTicketMaster() 
{

    cout << "Theater " << get_theater_name() << " at " << get_location() << " is currently closed. ";

}

// behavioral function definitions

void MovieTicketMaster::Init() 
{

    string movie_names[8] = 
    {

        "Interstellar",

        "My Hero Academia the Movie",

        "SpongeBob the Movie",

        "Sharknado",

        "Matrix",

        "John Wick",

        "Parasite",

        "Ice Age"

    };

    int seats_available[8] = { 1, 2, 3, 4, 5, 6, 7, 8};

    double ticket_price[8] = { 1.99, 2.99, 3.51, 5.25, 6.31, 9.22, 10.25, 16.01 };

    Movie * p_movie_object = nullptr;

    p_movie_object = &movie_objects_[0];

    string * p_movie_name = &movie_names[0];

    int * p_seats_available = &seats_available[0];

    double * p_ticket_price = &ticket_price[0];

    // use a loop to set movie name, seats and price for each Movie element in array of  Movie List as shown below.

    movie_count_ = 8;
    
    for (int i = 0; i < movie_count_; i++) 
    {
        p_movie_object->set_movie_name(*p_movie_name);

        p_movie_object->set_seats_available(*p_seats_available);

        p_movie_object->set_ticket_price(*p_ticket_price);

        p_movie_object++;

        p_movie_name++;

        p_seats_available++;

        p_ticket_price++;

    }

}

void MovieTicketMaster::Run()
{

    int user_response;
    string s_user_response;

    do 
    {
        Menu();
        cout << "Select an option by inserting a number: ";
        getline(cin, s_user_response);

        istringstream (s_user_response) >> user_response; // istringstream requires string argument and feeds it to an int varaible

        switch(user_response)
        {
            case 1:
                ViewMovies();
                break;
            case 2:
                SearchMovies();
                break;
            case 3:
                PurchaseTicket();
                break;
        }
        
    } while(user_response != 4);

}

// accessor/mutator

string MovieTicketMaster::get_theater_name() const 
{

return theater_name_;

}

string MovieTicketMaster::get_location() const 
{

return location_;

}

int MovieTicketMaster::get_movie_count() const 
{

return movie_count_;

}

// helper functions

void MovieTicketMaster::Menu()
{
    cout << "\n\nMOVIE TICKET MASTER\nTheater: " << get_theater_name() << " at " << get_location()<< endl;
    cout << "{}====================================={}\n";
    cout << "||                                     ||\n";
    cout << "||      Showing the Best Movies        ||\n";
    cout << "||          In the Wild West           ||\n";
    cout << "||       In a Theater Near You         ||\n";
    cout << "||                                     ||\n";
    cout << "{}====================================={}\n";
    cout << "1. View all movies";
    cout << "\n2. Search for a movie";
    cout << "\n3. Purchase a ticket";
    cout << "\n4. Quit\n\n";
}

void MovieTicketMaster::ViewMovies()
{
    Movie * p_view_movies = nullptr;

    p_view_movies = &movie_objects_[0];
    
    for (int i = 0; i < 8; i++)
    {
        p_view_movies->Display();

        p_view_movies++;
    } 


}

void MovieTicketMaster::SearchMovies()
{

    string user_response;
    
    cout << "Search: ";

    getline(cin, user_response);

    Movie * p_found_movie = FindMovie(user_response);

    if (p_found_movie == nullptr)
    {
        cout << "\nError: No movie found.\n";
    }
    else
    {
        p_found_movie->Display();
    }


}
        
Movie * MovieTicketMaster::FindMovie(string movie_name)
{

    Movie * p_movie_object = nullptr;

    p_movie_object = &movie_objects_[0];


    for(int i = 0; i < movie_count_; i++)
    {
        if (movie_name != p_movie_object->get_movie_name())
        {
            p_movie_object++;
        }
        
        else
        {
            return p_movie_object;
        }
    }

    p_movie_object = nullptr;

    return p_movie_object;    

}

void MovieTicketMaster::PurchaseTicket()
{

    string s_user_response_name;
    string s_user_response_tickets;
    int i_user_response;

    cout << "Enter a movie name: ";

    getline(cin, s_user_response_name);

    cout << "Enter the number of tickets: ";

    getline(cin, s_user_response_tickets); // first get string input for int

    istringstream(s_user_response_tickets) >> i_user_response; // convert string to int

    Movie * found_movie = FindMovie(s_user_response_name);
    
    if (found_movie == nullptr)
    {
        cout <<  "No movie found.";

    }

    else if (found_movie)
    {
        double total_cost = found_movie->Purchase_Ticket(i_user_response);

        if (total_cost == -1)
        {
            cout <<  "The show has been sold out or not enough tickets available per your request!";
        }
        
        else
        {
            cout << "Total cost: " << total_cost;
        }
    
    }
}

//--------------------
// Movie definitions
//--------------------

// constructors/ destructor definitions

Movie::Movie() : seats_available_(0), ticket_price_(0.0) {}

Movie::Movie(string movie_name, int seats_available, double ticket_price) :
movie_name_(movie_name), seats_available_(seats_available), ticket_price_(ticket_price) {}

Movie::~Movie() 
{

    cout << "Movie " << get_movie_name() << " object is no longer showing. ";

}

// behavioral function definitions

double Movie::Purchase_Ticket(int number_of_tickets) 
{

    if (number_of_tickets > seats_available_)
    {
        return -1;
    }

    else
    {
        double total = number_of_tickets * ticket_price_;

        seats_available_ -= number_of_tickets;

        return total;
    }

}

void Movie::Display() 
{

    cout << "\nMovie: "<< get_movie_name() << endl;
    
    cout << "Seats Available: " << get_seats_available() << endl;

    cout << "Ticket Price: " << get_ticket_price() << "\n";

}

// accessor/mutator

string Movie::get_movie_name() const 
{
    
    return movie_name_;

}

int Movie::get_seats_available() const 
{

    return seats_available_;

}

double Movie::get_ticket_price() const 
{
    return ticket_price_;
}

void Movie::set_movie_name( string movie_name )
{

    movie_name_ = movie_name;

}

void Movie::set_seats_available( int seats_available )
{
    seats_available_= seats_available;
}

void Movie::set_ticket_price( double ticket_price )
{
    ticket_price_ = ticket_price;
}
