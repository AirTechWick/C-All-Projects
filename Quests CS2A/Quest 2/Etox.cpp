// Student ID: 20342635
// 2a-Lab-01

#include <iostream>
#include <sstream>

#include <cmath>
#include <cstdlib>

using namespace std;

double etox_5_terms(double x) {
    return exp (x);
}

// e to the 2nd power is 7.38905609893

int main(int argc, char **argv) {
    string user_input;
    double x;

    cout << "Enter a value for x: ";
    getline(cin, user_input);
    istringstream(user_input) >> x;

    cout << etox_5_terms(x) << endl;

    return 0;

}