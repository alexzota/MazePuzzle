#ifndef MAZE_H
#define MAZE_H
#include <iostream>
#include <vector>
#include <stack>
using std::vector;
using std::stack;
using std::pair;
class Maze
{
    public:
        Maze();


        void start();
        int get_size() { return size; }
        void set_size(int val) { size = val; }
        vector< vector<int> > get_maze_matrix() { return maze_matrix; }
        vector< vector<int> > set_maze_matrix(vector< vector<int> > aux) {  maze_matrix = aux; }
        void generate_maze_matrix();
        vector<vector<vector<int>>> get_neighbours() { return neighbours; }
        void set_neighbours(vector<vector<vector<int>>> val) { neighbours = val; };

        void available_neighbours(int l, int c,stack< pair<int,int> > &st,  vector< vector< int> > vizitat);
        void print_matrix(int l , int c );

    private:
        int size;
        vector< vector<int> > maze_matrix;
        vector<vector<vector<int>>> neighbours;
};

#endif // MAZE_H
