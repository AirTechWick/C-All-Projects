#include <iostream>
#include <sstream>

#include <vector>

#include "Pet_Store.h"

using namespace std;

Pet_Store::Pet_Store(size_t n) 
{
    // TODO - Your code here
    _pets.resize(n);
    _sort_order = NONE;
}

void Pet_Store::set_size(size_t n)
{
    // TODO - Your code here
}

size_t Pet_Store::get_size() const 
{
    // TODO - Your code here
    return sizeof(_pets);
}

void Pet_Store::clear()
{
    // TODO - Your code here
}

void Pet_Store::populate_with_n_random_pets(size_t n)
{
    // TODO - Your code here
}

// These two functions can be conveniently made anonymous "lambda" functions
// defined within the scope of the functions where they're used but only
// c++-11 on. For now we're just going to leave them here. It's straightforward
// to move them in. Just look up c++ lambda functions if you want. If you want
// to know but don't understand it, I'm happy to explain what they are. Ask me
// in the forums. It's not necessary to know about it to ace this course.
//
// You are free to experiment by hacking the functions below, but restore their
// correct functionalities before submitting your lab.
//
bool Pet_Store::_id_compare(const Pet& p1, const Pet& p2) 
{
    return p1.get_id() < p2.get_id();
}

bool Pet_Store::_name_compare(const Pet& p1, const Pet& p2)
{
    return p1.get_name() < p2.get_name();
}

void Pet_Store::_sort_pets_by_id()
{
    std::sort(_pets.begin(), _pets.end(), Pet_Store::_id_compare);
    _sort_order = BY_NAME;
}

bool Pet_Store::find_pet_by_id_lin(long id, Pet& pet)
{
    // TODO - Your code here
}

bool Pet_Store::find_pet_by_name_lin(string name, Pet& pet)
{
    // TODO - Your code here
}

// When this method starts, the _pets[] vector must be sorted in
// non-descending order by _id. If it is not already, then it will be resorted.

bool Pet_Store::find_pet_by_id_bin(long id, Pet& pet)
{
    // TODO - Your code here
}

// When this method is called, the _pets[] vector must be sorted in
// lexicographic non-descending order by _name. If it is not already.
// then it will be resorted

bool Pet_Store::find_pet_by_name_bin(string name, Pet& pet)
{
    // TODO - Your code here
}

// Return a string representation of the pets with indexes n1 through n2
// inclusive, exclusive of non-existent indices
// Each pet is on a line by itself. There is no newline after the last pet.

string Pet_Store::to_string(size_t n1, size_t n2)
{
    // TODO - Your code here
}
