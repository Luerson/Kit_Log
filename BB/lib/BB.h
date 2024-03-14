#ifndef BB_H
#define BB_H

#include <bits/stdc++.h>
#include "../implements.h"

using namespace std;

struct Node
{
    vector<pair<int, int>> forbidden_arcs;
    vector<vector<int>> subtours;

    double lower_bound;
    int chosen;
    bool feasible;

    bool operator<(Node other) const
    {
        return lower_bound < other.lower_bound;
    }
};

Solution BB(double **, int);
Node branchingStrategy(int);
void solveHungarian(Node &, double **);
vector<vector<int>> getSubtourHung(Node &, int &);

#endif BB_H