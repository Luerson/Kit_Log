#include "BB.h"

void solveHungarian(Node &root, double **cost, int dimension)
{
    vector<double> forbidden_values;
    for (int i = 0; i < root.forbidden_arcs.size(); i++)
    {
        int forbidden_i = root.forbidden_arcs[i].first;
        int forbidden_j = root.forbidden_arcs[i].second;

        forbidden_values.push_back(cost[forbidden_i][forbidden_j]);
        cost[forbidden_i][forbidden_j] = INFINITE;
    }

    hungarian_problem_t p;
    int mode = HUNGARIAN_MODE_MINIMIZE_COST;
    hungarian_init(&p, cost, dimension, dimension, mode); // Carregando o problema

    getAtributes(p, root, dimension);

    hungarian_free(&p);

    for (int i = 0; i < root.forbidden_arcs.size(); i++)
    {
        int forbidden_i = root.forbidden_arcs[i].first;
        int forbidden_j = root.forbidden_arcs[i].second;

        cost[forbidden_i][forbidden_j] = forbidden_values[i];
    }
}

Node branchingStrategy(list<Node> &tree, priority_queue<Node> &LB, int strategy)
{
    Node newNode;

    if (strategy == 1)
    {
        newNode = tree.back();
        tree.pop_back();
    }
    else if (strategy == 2)
    {
        newNode = tree.front();
        tree.pop_front();
    }
    else if (strategy == 3)
    {
        newNode = LB.top();
        LB.pop();
    }

    return newNode;
}

void getAtributes(hungarian_problem_t &p, Node &node, int dimension)
{
    vector<vector<int>> resp;
    vector<bool> visitados(dimension, false);

    node.lower_bound = hungarian_solve(&p);

    for (int i = 0; i < dimension; i++)
    {
        if (!visitados[i])
        {
            vector<int> subtour;
            visitados[i] = true;
            subtour.push_back(i);
            for (int j = 0; j < dimension; j++)
            {
                int cur = subtour.back();

                if (p.assignment[cur][j] == 1)
                {
                    if (!visitados[j])
                    {
                        visitados[j] = true;
                        subtour.push_back(j);
                        cur = j;
                        j = -1;
                    }
                    else
                    {
                        subtour.push_back(j);
                        break;
                    }
                }
            }
            resp.push_back(subtour);
        }
    }

    node.subtours = resp;
    node.feasible = (resp.size() == 1);
    node.chosen = 0;

    // Escolher melhor subtour
    for (int i = 1; i < resp.size(); i++)
    {
        if (resp[i].size() < resp[node.chosen].size() && resp[i].size() > 1)
        {
            node.chosen = i;
        }
        else if (resp[node.chosen].size() < 2)
        {
            node.chosen = i;
        }
    }
    return;
}

Solution BB(double **cost, int dimension, int strategy)
{
    Solution s;

    Node root;

    list<Node> tree;
    priority_queue<Node> LB;

    if (strategy < 3)
    {
        tree.push_back(root);
    }
    else
    {
        LB.push(root);
    }

    double upper_bound = numeric_limits<double>::infinity();

    while (!tree.empty() || !LB.empty())
    {
        auto node = branchingStrategy(tree, LB, strategy);
        solveHungarian(node, cost, dimension);
        vector<vector<int>> subtour = node.subtours;

        // cout << node.feasible << endl;
        // cout << node.lower_bound << endl;

        if (node.feasible && upper_bound > node.lower_bound)
        {
            upper_bound = min(node.lower_bound, upper_bound);
            s.sequencia = subtour[0];
            s.odj_value = upper_bound;

            // cout << s.odj_value << endl;
        }
        else if (upper_bound > node.lower_bound)
        {
            // cout << "chegou aqui" << endl;
            // cout << node.subtours[0].size() << endl;
            for (int i = 0; i < node.subtours[node.chosen].size() - 1; i++)
            {
                Node n;
                n.forbidden_arcs = node.forbidden_arcs;

                // cout << n.forbidden_arcs.size() << endl;

                pair<int, int>
                    forbidden_arc = {
                        node.subtours[node.chosen][i],
                        node.subtours[node.chosen][i + 1]};

                n.forbidden_arcs.push_back(forbidden_arc);

                // cout << n.forbidden_arcs.size() << endl;

                n.lower_bound = node.lower_bound;

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
    }

    return s;
}