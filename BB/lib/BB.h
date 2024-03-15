#ifndef BB_H
#define BB_H

#include <bits/stdc++.h>
#include "../implements.h"

using namespace std;

struct Node
{
    vector<pair<int, int>> forbidden_arcs;
    vector<vector<int>> subtours;
    int **assignment;

    double lower_bound;
    int chosen;
    bool feasible;

    bool operator<(Node other) const
    {
        return lower_bound > other.lower_bound;
    }
};

Solution BB(double **, int, int);
Node branchingStrategy(list<Node> &, priority_queue<Node> &, int);
void solveHungarian(Node &, double **, int dimension);
void getAtributes(hungarian_problem_t &, Node &, int);

#endif