#include <iostream>

#include "log_n_vector.h"

using std::cout;
using std::endl;

int main() {
    LogNVector<int> v = {0, 11, 22, 33, 44, 55, 66, 77, 88, 99, 110, 121};
    //cout << v.size() << endl;
    LogNVector<int> apple = v;

   cout << "v[0] == " << v[0] << ",    &v[0] == " << &v[0] << endl;
    for (int j = 1; j < v.size(); ++j) {
        // All the elements in the same array should have sequential addresses.
        // For example, &v[2] == &v[1] + 1
        // However, there's no guarantee that &v[1] == &v[0] + 1.
        cout << "v[" << j << "] == " << v[j] << ",    "
             << "&v[" << j << "] - &v[" << j - 1 << "] == "
             << &v[j] - &v[j - 1] << endl;
    }


   cout << "\napple[0] == " << apple[0] << ",    &apple[0] == " << &apple[0] << endl;
    for (int j = 1; j < apple.size(); ++j) {
        // All the elements in the same array should have sequential addresses.
        // For example, &apple[2] == &apple[1] + 1
        // However, there's no guarantee that &apple[1] == &apple[0] + 1.
        cout << "apple[" << j << "] == " << apple[j] << ",    "
             << "&apple[" << j << "] - &apple[" << j - 1 << "] == "
             << &apple[j] - &apple[j - 1] << endl;
    }

    return 0;
}