#include <iostream>
#include <vector>
#include <cmath>
#include "Solution.h"
#include "CSVReader.h"
#include <queue>

using namespace std;

int main(){

    //# Wall . Free P Player  B Boxes G Goal Q Player+Goal C Boxes+Goal
    CSVReader reader("input.csv");

    vector<vector<string> > grid = reader.getData();

    Solution solver(grid);

    solver.BFS();
}
