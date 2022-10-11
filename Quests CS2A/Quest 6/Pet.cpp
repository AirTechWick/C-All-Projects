//  Pet.cpp 
//  2a-Lab-06-Pets 
// 
#include <iostream> 
#include <sstream> 
//#include <time.h>
#include <vector> 
#include "Pet.h" 
 
using namespace std; 

/*int main(int argc, const char * argv[]) 
{ 
    Pet pet1;
    cout << pet1.get_name() << pet1.get_id() << pet1.get_num_limbs();
    return 0;
}*/

// This is a way to properly initialize (out-of-line) a static variable. 
size_t Pet::_population = 0; 

Pet::Pet(string name, long id, int num_limbs) {     
// TODO - Your code here MY DEFAULT VALUES
    _name = name;
    _id = id;
    _num_limbs = num_limbs;
    _population++;
} 

Pet::~Pet() {     
// TODO - Your code here 
    _population--;
} 

string Pet::get_name() const { return _name; }

long Pet::get_id() const {      
// TODO - Your code here 
    return _id;
} 

int Pet::get_num_limbs() const {      
// TODO - Your code here 
    return _num_limbs;
} 

bool Pet::set_name(string name) {     
// TODO - Your code here
    if (name == "")
        return false;
    else
        _name = name;
    return true;
} 

bool Pet::set_id(long id) {     
// TODO - Your code here 
    if (id < 0)
        return false;
    else
        _id = id;
    return true;
} 

bool Pet::set_num_limbs(int num_limbs) {     
// TODO - Your code here 
    if (num_limbs < 0)
        return false;
    else
        _num_limbs = num_limbs;
    return true;
        
} 

string Pet::to_string() const {     
// TODO - Your code here
    ostringstream cnvrt;
    cnvrt << _id;
    string stringID = cnvrt.str();

    ostringstream cnvrt2;
    cnvrt2 << _num_limbs;
    string stringNumLimbs = cnvrt2.str();

    string info = "(Name: " + _name + ", ID: " + stringID + ", Limb Count: " + stringNumLimbs + ")";
    return info;
} 

// Fill in the supplied pets vector with n pets whose 
// properties are chosen randomly. 
// Don't mess with this method more than necessary. 
void Pet::get_n_pets(size_t n, std::vector<Pet>& pets, int name_len) {     
	// TODO - Resize pets as necessary  
    pets.resize(n);  // vector pets starts out as empty vector and I resized the vector to the argument n
	long prev_id = 0;     
	for (size_t i = 0; i < n; i++) {         
		long id = prev_id + 1 + rand() % 10; // New random id is created in this iteration
		pets[i].set_id(id); // whatever place it is at i, set the id    
		pets[i].set_num_limbs(rand() % 9); // up to arachnids || whatever place it is at i, set the num_limbs

        //nothing has happened to prev_id so far

		// TODO - make and set a name of the requested length
        string newName = pets[i].make_a_name(name_len);
        pets[i].set_name(newName);
		// TODO - adjust prev_id as necessary
        prev_id = id; // AFTER the id has been set, prev id is equal to id so in the next iteration prev id is this value
	} 
}

string Pet::make_a_name(int len){
	// TODO - Your code here
    string vowels = "aeiou", consonants = "bcdfghjklmnpqrstvwxyz",
    manufacturedName = "", firstLetter = "";
    
    bool prevVowel; //if the previous character is a vowel this turns true otherwise if the prevVowel is a consonant this turns false

    int randNum = rand() % 2;

    if (len == 0)
    {
        return "";
    }

    else if (randNum == 0) // code for first letter
    {
        int randIndexCons = rand() % consonants.length();
        firstLetter = consonants[randIndexCons];
        prevVowel = false;
    }
    else
    {
        int randIndexVowel = rand() % vowels.length();
        firstLetter = vowels[randIndexVowel];
        prevVowel = true;
    }


    for (int i = 1; i < len; i++) // code for letters following first letter
    {

        if(prevVowel == false)
        {
            int randIndexVowel = rand() % vowels.length();
            manufacturedName += vowels[randIndexVowel];
            prevVowel = true;
        }
        else
        {
            int randIndexCons = rand() % consonants.length();
            manufacturedName += consonants[randIndexCons];
            prevVowel = false;
        }
    }   

    string newName = firstLetter + manufacturedName;
    return newName;
}


// Optional EC points
// Global helpers 
bool operator==(const Pet& pet1, const Pet& pet2) {     
// TODO - Your code here 
    return true;
} 

bool operator!=(const Pet& pet1, const Pet& pet2) {     
// TODO - Your code here 
    return true;
} 

ostream& operator<<(ostream& os, const Pet& pet) {     
// TODO - Your code here 
    return os;
}