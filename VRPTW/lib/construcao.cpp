#include "construcao.h"

bool feasible(Node &node, Instance &instance, Solution &s, pair<int, int> edge, int route, int node_index)
{
    if (s.ads.total_load[route] + node.demand > instance.capacity)
    {
        return false;
    }

    double newDistLeft = instance.dists[s.routes[route][edge.first]][node_index];
    double newDistRight = instance.dists[node_index][s.routes[route][edge.second]];
    double previousDist = instance.dists[s.routes[route][edge.first]][s.routes[route][edge.second]];
    double delta = newDistLeft + newDistRight + node.serviceTime - previousDist;

    if (delta > s.ads.maxIncreaseTime[route][edge.second])
    {
        return false;
    }

    double last_node_arrive = s.ads.arriveTime[route][edge.first];
    double last_node_service = instance.nodes[s.routes[route][edge.first]].serviceTime;
    double time_travel = instance.dists[s.routes[route][edge.first]][node_index];

    if (last_node_arrive + last_node_service + time_travel < node.window.first || last_node_arrive + last_node_service + time_travel > node.window.second)
    {
        return false;
    }

    return true;
}

void preencherVazios(Instance &instancia, Solution &s, vector<int> &CL)
{
    int size = instancia.totalVehicles;

    for (int i = 0; i < size; i++)
    {
        s.routes[i].push_back(0);
        s.routes[i].push_back(0);

        fillTimeArrive(s, instancia, s.ads, i);
        fillTotalLoad(s, instancia, s.ads, i);
        fillTimeChange(s, instancia, s.ads, i);

        /*while (1)
        {
            int newIndex = rand() % CL.size();

            int t_arrive = instancia.dists[0][CL[newIndex]];
            Node node = instancia.nodes[CL[newIndex]];

            if (feasible(node, instancia, s, make_pair(0, 1), i, CL[newIndex]))
            {
                s.routes[i].insert(s.routes[i].begin() + 1, CL[newIndex]);
                CL.erase(CL.begin() + newIndex);
                fillTimeArrive(s, instancia, s.ads, i);
                fillTotalLoad(s, instancia, s.ads, i);
                fillTimeChange(s, instancia, s.ads, i);
                break;
            }
        }*/
    }
}

vector<int> iniciaCL(int dimension)
{
    vector<int> CL;

    for (int i = 1; i < dimension; i++)
    {
        CL.push_back(i);
    }

    return CL;
}

int menorCusto(vector<int> &CL, Solution &s, int route, double gama, InsertionInfo &custoInsercao, Instance &instance)
{
    int menorIndice = -1;
    double menorValor = INFINITE;

    for (int i = 0; i < CL.size(); i++)
    {
        int vertice = CL[i];

        for (int j = 0; j < s.routes[route].size() - 1; j++)
        {
            double custo_Atual;
            Node node = instance.nodes[vertice];
            InsertionInfo newInfo;

            int cur_node = s.routes[route][j];
            int next_node = s.routes[route][j + 1];

            if (gama < 0)
            {
                custo_Atual = instance.dists[cur_node][vertice];
            }
            else
            {
                custo_Atual = (instance.dists[cur_node][vertice] + instance.dists[vertice][next_node] - instance.dists[cur_node][next_node]);
                custo_Atual -= gama * (instance.dists[0][vertice] + instance.dists[vertice][0]);
            }

            if (custo_Atual < menorValor && feasible(node, instance, s, make_pair(j, j + 1), route, vertice))
            {
                newInfo.arestaRemovida = make_pair(j, j + 1);
                newInfo.correspond_rout = route;
                newInfo.custo = custo_Atual;
                newInfo.noInserido = vertice;

                menorIndice = i;
                menorValor = custo_Atual;

                custoInsercao = newInfo;
            }
        }
    }

    return menorIndice;
}

void inserirNaSolucao(Solution &s, InsertionInfo &insertion, Instance &instance)
{
    int node_number = insertion.noInserido;
    int insert_index = insertion.arestaRemovida.second;
    int route = insertion.correspond_rout;

    s.routes[route].insert(s.routes[route].begin() + insert_index, node_number);

    fillTimeArrive(s, instance, s.ads, route);
    fillTotalLoad(s, instance, s.ads, route);
    fillTimeChange(s, instance, s.ads, route);
}

bool estrategiaSequencial(Solution &s, Instance &instance, vector<int> &CL, INSERTION_CRITERIA criteria)
{
    double gama = -1;
    vector<vector<InsertionInfo>> candidates;

    if (criteria == CHEAPEST_INS)
    {
        gama = (rand() % 35) * 0.05;
    }

    while (!CL.empty())
    {
        bool oneInserted = false;
        for (int i = 0; i < s.routes.size(); i++)
        {
            if (CL.empty())
            {
                oneInserted = true;
                break;
            }

            InsertionInfo custoInsercao;
            int menorIndice = menorCusto(CL, s, i, gama, custoInsercao, instance);

            if (menorIndice < 0)
            {
                continue;
            }

            oneInserted = true;
            inserirNaSolucao(s, custoInsercao, instance);
            CL.erase(CL.begin() + menorIndice);
        }

        if (!oneInserted)
            return false;
        oneInserted = false;
    }

    return true;
}

bool estrategiaParalela(Solution &s, Instance &instance, vector<int> &CL, INSERTION_CRITERIA criteria)
{
    double gama = -1;
    vector<vector<InsertionInfo>> candidates;

    if (criteria == CHEAPEST_INS)
    {
        gama = (rand() % 35) * 0.05;
    }

    while (!CL.empty())
    {
        InsertionInfo custoInsercao;
        int menorIndex = -1;

        custoInsercao.custo = INFINITE;

        for (int i = 0; i < s.routes.size(); i++)
        {
            InsertionInfo cur_custoInsercao;
            cur_custoInsercao.custo = INFINITE;
            int curr_menor_index = menorCusto(CL, s, i, gama, cur_custoInsercao, instance);

            if (cur_custoInsercao.custo < custoInsercao.custo)
            {
                custoInsercao = cur_custoInsercao;
                menorIndex = curr_menor_index;
            }
        }

        if (menorIndex < 0)
        {
            return false;
        }

        inserirNaSolucao(s, custoInsercao, instance);
        CL.erase(CL.begin() + menorIndex);
    }

    return true;
}

Solution construcao(Instance &instancia)
{
    int dimension = instancia.size;

    int k = 0;

    while (1)
    {
        k++;
        Solution s;
        startADS(s.ads, dimension, instancia.totalVehicles);
        s.routes.resize(instancia.totalVehicles);

        vector<int> CL = iniciaCL(dimension);

        preencherVazios(instancia, s, CL);

        INSERTION_CRITERIA criterion = (rand() % 2 == 0 ? CHEAPEST_INS : NEAREST_NEIGH);
        INSERTION_STRATEGY strategy = (rand() % 2 == 0 ? SEQUENTIAL : PARALLEL);

        if (strategy == SEQUENTIAL)
        {
            s.feasible = estrategiaSequencial(s, instancia, CL, criterion);
        }
        else if (strategy == PARALLEL)
        {
            s.feasible = estrategiaParalela(s, instancia, CL, criterion);
        }

        if (s.feasible)
        {
            calcularValorObj(s, instancia);
            return s;
        }
    }
}