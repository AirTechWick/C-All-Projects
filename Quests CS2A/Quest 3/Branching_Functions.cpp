//  Student ID:​ 12345678

//  branching-functions.cpp
//  2a-Lab-03

#include <iostream>
using namespace std;

// This function returns the mean the three numbers passed
// in as parameters. Note that the mean may not be a round
// number. So you must use the double datatype for it.
double mean_of_3(int n1, int n2, int n3) {
    // TODO - YOUR CODE HERE
    n1 = 2;
    n2 = 9;
    n3 = 5;

    double mean_calculation = ((double) n1 + n2 + n3) / 3;
    cout << mean_calculation << endl;
    return 0;
    
}