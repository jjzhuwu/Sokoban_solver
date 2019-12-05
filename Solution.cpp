#include "Solution.h"

//# Wall . Free P Player  B Boxes G Goal Q Player+Goal C Boxes+Goal
Solution::Solution(vector<vector<string> >& agrid) {

    n = agrid.size();
    m = agrid[0].size();

    int player = 0;
    int num_boxes = 0;

    string s = "";

    for (int i = 0; i < n; i++){
        for (int j = 0; j < m; j++){

            if (agrid[i][j] == "W"){
                s += "W";
            } else if (agrid[i][j] == "."){
                s += ".";
            } else if (agrid[i][j] == "P"){
                player = i*m+j;
                s += ".";
            } else if (agrid[i][j] == "B"){
                s += "B";
                num_boxes++;
            } else if (agrid[i][j] == "G"){
                goals.push_back(i*m+j);
                s += ".";
            } else if (agrid[i][j] == "Q"){
                player = i*m+j;
                goals.push_back(i*m+j);
                s += ".";
            } else if (agrid[i][j] == "C"){
                goals.push_back(i*m+j);
                s += "B";
                num_boxes++;
            } else {
                s += ".";
            }
        }
    }

    assert(goals.size() == num_boxes);

    //identity positions that boxes can not be pushed to
    for (int i = 0; i < s.size(); i++){
        if ((s[i] == '.') && !goals_find(i)){
            if ((((i >= m)&&(s[i-m] == 'W'))||((i < (n-1)*m)&&(s[i+m] == 'W')))
                &&(((i % m >= 1)&&(s[i-1] == 'W'))||((i % m < m-1)&&(s[i+1] == 'W')))){
                    s[i] = 'I';
                }
        }
    }



    vector<char> t;

    s += player_loc_to_string(player);
    hist[s] = t;

    states.push(s);
}

bool Solution::goals_find(int i){

    int a = 0;
    int b = goals.size()-1;
    while (b-a > 1){
        int c = (a+b)/2;
        if (goals[c] > i){
            b = c;
        } else if (goals[c] < i){
            a = c;
        } else {
            return true;
        }
    }
    return ((goals[a] == i) || (goals[b] == i));
}

string Solution::player_loc_to_string(int p){

    stringstream ss;
    ss << p;
    string ret = ss.str();
    while (ret.size() < 3){
        ret = "0"+ ret;
    }
    return ret;
}

//also print solution, uses first one in the ss queue
bool Solution::solution_found(){

    string current_s = states.front();
    cout << current_s;
  //  cout << current_s[3] << endl;
    for (int i = 0; i < goals.size(); i++){
        if (current_s[goals[i]] != 'B'){
            return false;
        }
    }

    vector<char> to_print(hist[current_s]);

    cout << "Solution Found!";
    for (int i = 0; i < to_print.size(); i++){

        if (i % 10 == 5){
            cout << "    " ;
        } else if (i % 10 == 0){
            cout << endl << endl;
        }
        cout << to_print[i] << " ";
    }

    return true;
}


void Solution::move_up(string s, int loc){
    if ((loc >= m) && ((s[loc-m] == '.')||(s[loc-m] == 'I'))){
        vector<char> h_move (hist[s]);
        cout << " " << h_move.size();
        s.replace(s.size()-3, 3, player_loc_to_string(loc-m));

        if (hist.find(s) == hist.end()){
            h_move.push_back('U');
            hist[s] = h_move;
            states.push(s);
        }
    }
}

void Solution::push_up(string s, int loc){
    if ((loc >= 2*m) && (s[loc-m] == 'B') && (s[loc-2*m] == '.')){
        vector<char> h_move (hist[s]);
         cout << " " << h_move.size();
        s.replace(s.size()-3, 3, player_loc_to_string(loc-m));
        s[loc-m] = '.';
        s[loc-2*m] = 'B';

        if (hist.find(s) == hist.end()){
            h_move.push_back('U');
            hist[s] = h_move;
            states.push(s);
        }
    }
}

void Solution::move_left(string s, int loc){
    if ((loc % m >= 1) && ((s[loc-1] == '.')||(s[loc-1] == 'I'))){
        vector<char> h_move (hist[s]);
         cout << " " << h_move.size();
        s.replace(s.size()-3, 3, player_loc_to_string(loc-1));

        if (hist.find(s) == hist.end()){
            h_move.push_back('L');
            hist[s] = h_move;
            states.push(s);
        }
    }
}

void Solution::push_left(string s, int loc){
    if ((loc % m >= 2) && (s[loc-1] == 'B') && (s[loc-2] == '.')){
        vector<char> h_move (hist[s]);
         cout << " " << h_move.size();
        s.replace(s.size()-3, 3, player_loc_to_string(loc-1));
        s[loc-1] = '.';
        s[loc-2] = 'B';

        if (hist.find(s) == hist.end()){
            h_move.push_back('L');
            hist[s] = h_move;
            states.push(s);
        }
    }
}

void Solution::move_right(string s, int loc){
    if ((loc % m < m-1) && ((s[loc+1] == '.')||(s[loc+1] == 'I'))){
        vector<char> h_move (hist[s]);
         cout << " " << h_move.size();
        s.replace(s.size()-3, 3, player_loc_to_string(loc+1));

        if (hist.find(s) == hist.end()){
            h_move.push_back('R');
            hist[s] = h_move;
            states.push(s);
        }
    }
}

void Solution::push_right(string s, int loc){
    if ((loc % m < m-2) && (s[loc+1] == 'B') && (s[loc+2] == '.')){
        vector<char> h_move (hist[s]);
         cout << " " << h_move.size();
        s.replace(s.size()-3, 3, player_loc_to_string(loc+1));
        s[loc+1] = '.';
        s[loc+2] = 'B';

        if (hist.find(s) == hist.end()){
            h_move.push_back('R');
            hist[s] = h_move;
            states.push(s);
        }
    }
}

void Solution::move_down(string s, int loc){
    if ((loc < (n-1)*m) && ((s[loc+m] == '.') || (s[loc+m] == 'I'))){
        vector<char> h_move (hist[s]);
         cout << " " << h_move.size();
        s.replace(s.size()-3, 3, player_loc_to_string(loc+m));

        if (hist.find(s) == hist.end()){
            h_move.push_back('D');
            hist[s] = h_move;
            states.push(s);
        }
    }
}

void Solution::push_down(string s, int loc){
    if ((loc < (n-2)*m) && (s[loc+m] == 'B') && (s[loc+2*m] == '.')){
        vector<char> h_move (hist[s]);
         cout << " " << h_move.size();
        s.replace(s.size()-3, 3, player_loc_to_string(loc+m));
        s[loc+m] = '.';
        s[loc+2*m] = 'B';

        if (hist.find(s) == hist.end()){
            h_move.push_back('D');
            hist[s] = h_move;
            states.push(s);
        }
    }
}


void Solution::BFS(){
    while (!states.empty()){
        if (solution_found()){
            break;
        } else {
            string s = states.front();
            states.pop();

            int player_loc = stoi(s.substr(s.size()-3));

            move_up(s, player_loc);
            push_up(s, player_loc);

            move_left(s, player_loc);
            push_left(s, player_loc);

            move_right(s, player_loc);
            push_right(s, player_loc);

            move_down(s, player_loc);
            push_down(s, player_loc);
            cout << endl;
        }
    }
}
