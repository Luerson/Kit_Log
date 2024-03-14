#include "BB.h"

void solveHungarian(Node &root, double **cost)
{
}

Solution BB(double **cost, int dimension, int strategy)
{
    Solution s;

    Node root;
    int smallestSub;
    solveHungarian(root, cost);

    list<Node> tree;
    priority_queue<Node> LB;

    tree.push_back(root);

    double upper_bound = numeric_limits<double>::infinity();

    while (!tree.empty())
    {
        auto node = branchingStrategy(strategy);
        vector<vector<int>> subtour = getSubtourHung(node, smallestSub);

        if (node.feasible && upper_bound > node.lower_bound)
        {
            upper_bound = min(node.lower_bound, upper_bound);
            s.sequencia = subtour[0];
            s.odj_value = upper_bound;
        }
        else if (upper_bound > node.lower_bound)
        {
            for (int i = 0; i < node.subtours[smallestSub].size() - 1; i++)
            {
                Node n;
                n.forbidden_arcs = node.forbidden_arcs;

                pair<int, int> forbidden_arc = {
                    node.subtours[smallestSub][i],
                    node.subtours[smallestSub][i + 1]};

                n.forbidden_arcs.push_back(forbidden_arc);
                if (strategy < 3)
                {
                    tree.push_back(n);
                }
                else
                {
                    LB.push(n);
                }
            }
        }

        if (strategy == 1)
        {
            tree.pop_back();
        }
        else if (strategy == 2)
        {
            tree.pop_front();
        }
        else if (strategy == 3)
        {
            LB.pop();
        }
    }

    return s;
}