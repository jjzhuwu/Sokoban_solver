#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <utility>
#include <assert.h>
#include <string>

using namespace std;

class Solution {

private:

    int n; // <= 30;
    int m; // <= 30;

    vector<int> goals;
    map<string, vector<char> > hist;

    queue<string> states; //string: board+player_loc

public:
    //# Wall . Free P Player  B Boxes G Goal Q Player+Goal C Boxes+Goal
    Solution(vector<vector<string> > & agrid);

    bool goals_find(int i);

    string player_loc_to_string(int p);

    //also print solution, uses first one in the ss queue

    void prune_board(string & s);

    bool solution_found();

    void BFS();

    void move_up(string s, int loc);

    void push_up(string s, int loc);

    void move_left(string s, int loc);

    void push_left(string s, int loc);

    void move_right(string s, int loc);

    void push_right(string s, int loc);

    void move_down(string s, int loc);

    void push_down(string s, int loc);

};

#endif // SOLUTION_H_INCLUDED
