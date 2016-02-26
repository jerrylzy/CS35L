#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

const int KEY       = 42;
const int LINE_SIZE = 16;
const int RANGE     = 256;
const int LETTER_A  = atoi("A");
const int NEW_LINE  = atoi("\n");

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cerr << "Wrong number of arguments." << endl;
        exit(1);
    }
    
    int lineNum = stoi(argv[1]);
    srand(static_cast<unsigned int>(time(nullptr)));
    for (int i = 0; i < lineNum; i++)
    {
        for (int j = 0, k = rand() % RANGE; j < LINE_SIZE; j++, k = rand() % RANGE)
        {
            k = k == NEW_LINE ? LETTER_A : k;
            cout << to_string(k ^ KEY);
        }
        cout << " ";
    }
}
