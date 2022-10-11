#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

int main () 
{
    ifstream fin("in.txt"); // can name ifstream object anything. (file_input, file_in, fin, etc.)

    // Make sure to have a .txt file in the projects folder already

    ofstream fout("out.txt");

    // creates a new one if one hasn't been created.

    string line;

    if(!fin)
    {
        cout << "ERROR: Failed to open input file. \n";

        exit(-1);
    }

    if(!fout)
    {
        cout << "ERROR: Failed to open output file. \n";

        exit(-2);
    }

    while (getline(fin, line))
    {
        fout << line << endl;
    }

    fin.close(); // must close file after done with it
    
    fout.close();

    return 0;

}