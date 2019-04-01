#include "Maze.h"
#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include <stack>
#define S 0
#define E 1
#define E 1
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::stack;
using std::pair;
using std::string;

Maze::Maze()
{
    srand (time(NULL));

    string welcome_text1 = "SALUT, VEI PARTICIPA LA UN JOC DE TIP LABIRINT, SCOPUL TAU ESTE SA GASESTI IESIREA ";
    string welcome_text2 = "INTRODU MARIMEA LABIRINTULUI ( PREFERABIL > 10 )";
    cout << "\n\n\n\n\n\n\n\n    \t\t\t";
    for (auto ch : welcome_text1)
    {
        cout << ch;
        Sleep(5);
    }
    cout << endl << endl;
    cout << "    \t\t\t\t  ";
    for (auto ch : welcome_text2)
    {
        cout << ch;
        Sleep(5);
    }
    int size;
    cin >> size;
    set_size(size);
    vector<vector<vector<int>>> neighbours(size, vector<vector<int>>(size, vector<int>(2)));
    set_neighbours(neighbours);
}

void Maze::start()
{
    generate_maze_matrix();

    cout <<"\n\n\n";
    string begin_text1 = "LAYOUT-UL  LABIRINTULUI, MULT NOROC";
    cout << "    \t\t\t\t  ";
    for (auto ch : begin_text1)
    {
        cout << ch;
        Sleep(10);
    }
    cout << "\n\n\n";
    vector< vector<int> > maze_matrix_curr = get_maze_matrix();
    for(int i = 0 ; i < maze_matrix_curr.size(); i++)
    {
        for(int j = 0; j < maze_matrix_curr[i].size(); j++)
        {
            cout << maze_matrix_curr[i][j] << " ";
        }
        cout << endl;
    }
    cout <<  "ya";

    int l = 0, c = 0;
    system("CLS");
    print_matrix(l, c);
    char in = _getch();

    while(l != get_size()-1 || c != get_size()-1 )
    {
        switch(in)
        {
        case 'a':
        {
            if ( c > 0 && neighbours[l][c-1][E])
            {
                c--;
                print_matrix( l, c);
            }
            break;
        }
        case 'w':
        {
            if ( l > 0 && neighbours[l-1][c][S])
            {
                l--;
                print_matrix( l, c);
            }
            break;
        }
        case 'd':
        {
            if ( c < get_size()-1 && neighbours[l][c][E])
            {
                c++;
                print_matrix( l, c);
            }
            break;
        }
        case 's':
        {
            if ( l < get_size()-1 && neighbours[l][c][S])
            {
                l++;
            }
            break;
        }
        }

        system("CLS");
        print_matrix( l, c);
        if (l == get_size()-1 && c== get_size()-1)
        {
            cout << "\nFELICITARI, AI INVINS LABIRINTUL\n";
        }
        in = _getch();
    }

}

void Maze::print_matrix(int l = 0, int c = 0)
{
    cout << "    ";
    int size = get_size();
    vector< vector< vector< int> > > neighbours = get_neighbours();

    for(int i = 1 ; i < size; i++)
        cout << "_ ";
    cout <<endl;
    for(int i = 0 ; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(j == 0)
                cout << "| ";

            if( j == c && i == l)
                cout << "X";
            if(neighbours[i][j][S]==0)
                cout << "_";
            else
                cout << " ";
            if(neighbours[i][j][E]==0)
                cout << "|";
            else
                cout << " ";
        }
        cout << endl;
    }
    cout << "A - stanga\nW - sus\nD - dreapta\nS - jos\nX - EXIT \n";
}

void Maze::available_neighbours(int l, int c, stack< pair<int,int> > &st, vector< vector< int> > vizitat)
{
    vector< vector< vector< int> > > neighbours = get_neighbours();
    int size = get_size();
    if (c == 0 && l == 0)
    {
        if( vizitat[l+1][c] && vizitat[l][c+1])
        {
            st.pop();
        }
    }
    else if (c == 0 && l == size-1)
    {
        if( vizitat[l-1][c] && vizitat[l][c+1])
        {
            st.pop();
        }
    }
    else if (c == 0)
    {
        if(  vizitat[l+1][c] && vizitat[l-1][c] && vizitat[l][c+1])
        {
            st.pop();
        }
    }
    else if (l == 0 && c == size-1)
    {
        if(  vizitat[l+1][c] && vizitat[l][c-1])
        {
            st.pop();
        }
    }
    else if (l == 0)
    {
        if( vizitat[l+1][c] && vizitat[l][c-1] && vizitat[l][c+1])
        {
            st.pop();
        }
    }
    else if (l == size-1 && c == size-1)
    {
        if( vizitat[l-1][c] && vizitat[l][c-1])
        {
            st.pop();
        }
    }
    else if (c == size-1)
    {
        if(  vizitat[l-1][c] && vizitat[l][c-1] && vizitat[l+1][c] )
        {
            st.pop();
        }
    }
    else if (l == size-1)
    {
        if(  vizitat[l-1][c] && vizitat[l][c-1] && vizitat[l][c+1] )
        {
            st.pop();
        }
    }
    else if ( c > 0 && l > 0 && c < size-1 && l < size-1 && vizitat[l][c-1] && vizitat[l-1][c] && vizitat[l][c+1]&& vizitat[l+1][c])
    {
        st.pop();
    }
}

void Maze::generate_maze_matrix()
{
    stack< pair<int,int> > st;
    st.push(std::make_pair(0,0));
    int size = get_size();
    vector< vector< int> > vizitat(size, vector<int>(size));
    vizitat[0][0] = 1;

    while(st.empty()== 0)
    {
        int random = rand()%4;
        pair<int,int> top = st.top();
        int l = top.first;
        int c = top.second;
        switch(random)
        {
        case 0:
        {
            if(c > 0 && vizitat[l][c-1] == 0)
            {
                st.push(std::make_pair(l, c-1));    // left
                vizitat[l][c-1] = 1;
                neighbours[l][c-1][E] = 1;
            }
            else
                available_neighbours(l,c,st,vizitat);
            cout << endl;
            break;
        }
        case 1:
        {
            if(l > 0 && vizitat[l-1][c] == 0)
            {
                st.push(std::make_pair(l-1, c));    // up
                vizitat[l-1][c]= 1;
                neighbours[l-1][c][S] = 1;
            }
            else
                available_neighbours(l,c,st,vizitat);
            cout << endl;
            break;
        }
        case 2:
        {
            if(c < size-1 && vizitat[l][c+1]==0)
            {
                st.push(std::make_pair(l, c+1));    // right
                vizitat[l][c+1]= 1;
                neighbours[l][c][E] = 1;
            }
            else
                available_neighbours(l,c,st,vizitat);
            cout << endl;
            break;
        }
        case 3:
        {
            if(l < size-1 && vizitat[l+1][c] == 0)
            {
                st.push(std::make_pair(l+1, c));    // down
                vizitat[l+1][c]= 1;
                neighbours[l][c][S] = 1;
            }
            else
                available_neighbours(l,c,st,vizitat);
            cout << endl;
            break;
        }
        }
    }
    neighbours[size-1][size-1][E] = 1;
}
