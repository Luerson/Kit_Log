#ifndef INSTANCES_H
#define INSTANCES_H

#define INFINITE 99999999

#include <bits/stdc++.h>

using namespace std;

typedef struct
{
    pair<int, int> window;
    int demand;
    int serviceTime;
} Node;

typedef struct
{
    vector<Node> nodes;
    vector<vector<double>> dists;
    int totalVehicles;
    int capacity;
} Instance;

#endif