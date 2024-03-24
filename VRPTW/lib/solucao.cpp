#include "solucao.h"

using namespace std;

void startADS(ADS &ads, int dimension, int totalVehicles)
{
    ads.arriveTime.resize(totalVehicles);
    ads.maxDecreaseTime.resize(totalVehicles);
    ads.maxIncreaseTime.resize(totalVehicles);
    ads.total_load.resize(totalVehicles);

    for (int i = 0; i < totalVehicles; i++)
    {
        ads.arriveTime[i].resize(dimension + 1);
        ads.maxDecreaseTime[i].resize(dimension + 1);
        ads.maxIncreaseTime[i].resize(dimension + 1);
    }
}

void fillTimeArrive(Solution &s, Instance &instance, ADS &ads, int i)
{
    double cur_time = 0;
    // cout << "i = " << i << endl;
    for (int j = 0; j < s.routes[i].size() - 1; j++)
    {
        // cout << "j = " << j << endl;
        ads.arriveTime[i][j] = cur_time;

        int cur_node_index = s.routes[i][j];
        int next_node_index = s.routes[i][j + 1];

        // cout << "j = " << j << endl;

        Node cur_node = instance.nodes[cur_node_index];

        // cout << "j = " << j << endl;

        cur_time += cur_node.serviceTime + instance.dists[cur_node_index][next_node_index];
        // cout << "j = " << j << endl;
    }

    ads.arriveTime[i].back() = cur_time;
}

void fillTotalLoad(Solution &s, Instance &instance, ADS &ads, int i)
{
    int cur_load = 0;

    for (int j = 0; j < s.routes[i].size(); j++)
    {
        int node_index = s.routes[i][j];

        cur_load += instance.nodes[node_index].demand;
    }

    ads.total_load[i] = cur_load;
}

void fillTimeChange(Solution &s, Instance &instance, ADS &ads, int i)
{
    double cur_max_decrease = INFINITE;
    double cur_max_increase = INFINITE;

    for (int j = s.routes[i].size() - 1; j >= 0; j--)
    {
        int cur_node_index = s.routes[i][j];
        Node cur_node = instance.nodes[cur_node_index];

        cur_max_decrease = min(cur_max_decrease, ads.arriveTime[i][j] - cur_node.window.first);
        cur_max_increase = min(cur_max_increase, cur_node.window.second - ads.arriveTime[i][j]);

        ads.maxDecreaseTime[i][j] = cur_max_decrease;
        ads.maxIncreaseTime[i][j] = cur_max_increase;
    }
}

void exibirSolucao(Solution &s)
{
    for (int i = 0; i < s.routes.size(); i++)
    {
        for (int j = 0; j < s.routes[i].size() - 1; j++)
        {
            cout << s.routes[i][j] << " -> ";
        }
        cout << s.routes[i].back() << endl;

        /*for (int j = 0; j < s.routes[i].size() - 1; j++)
        {
            cout << s.ads.arriveTime[i][j] << " -> ";
        }
        cout << s.ads.arriveTime[i].back() << endl;*/
    }

    cout << s.valorObj << endl;
}

void calcularValorObj(Solution &s, Instance &instance)
{
    s.valorObj = 0;
    for (int i = 0; i < s.routes.size(); i++)
    {
        double curr_route = 0;
        for (int j = 0; j < s.routes[i].size() - 1; j++)
        {
            int cur_node_index = s.routes[i][j];
            int next_node_index = s.routes[i][j + 1];

            curr_route += instance.dists[cur_node_index][next_node_index];
        }

        s.valorObj += curr_route;
    }
}