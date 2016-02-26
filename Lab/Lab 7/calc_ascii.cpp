#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

const int KEY       = 42;
const int RANGE     = 256;
const int SPLASH    = 13;

void output(const string& str)
{
    int key = str == "cipher" ? KEY : 0;
    if (str != "plain" && ! key)
    {
        cerr << "String input error" << endl;
        exit(1);
    }
    cout << str << "=\"";
    for (int i = 0; i < RANGE; i++)
    {
        cout << "\\";
        cout << oct << (i ^ key);
        if (i && i % SPLASH == 0)
            cout << "\\" << endl;
    }
    cout << "\"" << endl;
}

int main()
{
    output(string("cipher"));
    output(string("plain"));
}
