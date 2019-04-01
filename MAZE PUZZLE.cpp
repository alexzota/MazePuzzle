#include <iostream>

#include "Maze.h"
#include "Maze.cpp"

using namespace std;

int main()
{

    Maze m1;
    m1.start();

    char opt;
    cout <<"Vrei sa incepi un joc nou? (Y/N)\n";
    cin >>opt;
    while (opt == 'Y')
    {
        Maze m2;
        m2.start();
        cout <<"Vrei sa incepi un joc nou? (Y/N)\n";
        cin >>opt;
    }

    return 0;
}
