#include <iostream>
#include <fstream>
#include <vector>
#include "implements.h"

using namespace std;

// Struct para representar um cliente
struct Cliente
{
    int cust_no;
    double xcoord;
    double ycoord;
    int demand;
    int ready_time;
    int due_date;
    int service_time;
};

// Struct para representar um veículo
struct Veiculo
{
    int number;
    int capacity;
};

// Função para ler os dados do arquivo
void lerDadosArquivo(const string &nome_arquivo, Veiculo &veiculo, vector<Cliente> &clientes)
{
    ifstream arquivo(nome_arquivo);

    if (!arquivo.is_open())
    {
        cerr << "Erro ao abrir o arquivo." << endl;
        return;
    }

    // Descartar a primeira linha
    string linha;
    getline(arquivo, linha);
    getline(arquivo, linha);
    getline(arquivo, linha);
    getline(arquivo, linha);

    // Ler os dados do veículo
    arquivo >> veiculo.number >> veiculo.capacity;

    // Descartar as próximas duas linhas
    getline(arquivo, linha);
    getline(arquivo, linha);
    getline(arquivo, linha);
    getline(arquivo, linha);

    // Ler os dados dos clientes
    Cliente cliente;
    while (arquivo >> cliente.cust_no >> cliente.xcoord >> cliente.ycoord >> cliente.demand >> cliente.ready_time >> cliente.due_date >> cliente.service_time)
    {
        clientes.push_back(cliente);
    }

    arquivo.close();
}

// Função para imprimir os dados lidos
void imprimirDados(const Veiculo &veiculo, const vector<Cliente> &clientes)
{
    cout << "Veículo:" << endl;
    cout << "Número: " << veiculo.number << endl;
    cout << "Capacidade: " << veiculo.capacity << endl;

    cout << "\nClientes:" << endl;
    for (const auto &cliente : clientes)
    {
        cout << "CUST NO.: " << cliente.cust_no << " XCOORD.: " << cliente.xcoord << " YCOORD.: " << cliente.ycoord
             << " DEMAND: " << cliente.demand << " READY TIME: " << cliente.ready_time << " DUE DATE: " << cliente.due_date
             << " SERVICE TIME: " << cliente.service_time << endl;
    }
}

void executaVRPTW(Instance &instance, vector<Cliente> &clientes, Veiculo &veiculo)
{
    Solution s;

    instance.capacity = veiculo.capacity;
    instance.totalVehicles = veiculo.number;

    int size = clientes.size();

    instance.size = size;
    instance.nodes.resize(size);
    instance.dists.resize(size);

    for (int i = 0; i < size; i++)
    {
        instance.nodes[i].demand = clientes[i].demand;
        instance.nodes[i].serviceTime = clientes[i].service_time;
        instance.nodes[i].window = make_pair(clientes[i].ready_time, clientes[i].due_date);
    }

    for (int i = 0; i < size; i++)
    {
        instance.dists[i].resize(size);
    }

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                instance.dists[i][j] = INFINITE;
            }
            else
            {
                double dist = hypot(clientes[i].xcoord - clientes[j].xcoord, clientes[i].ycoord - clientes[j].ycoord);
                instance.dists[i][j] = dist;
                instance.dists[j][i] = dist;
            }
        }
    }

    s = ILS(1, 1, instance);

    exibirSolucao(s);
}

int main()
{
    Veiculo veiculo;
    vector<Cliente> clientes;

    // Nome do arquivo de entrada
    string nome_arquivo = "../instances/c101.txt";

    // Ler os dados do arquivo
    lerDadosArquivo(nome_arquivo, veiculo, clientes);

    Instance instance;

    executaVRPTW(instance, clientes, veiculo);

    // Imprimir os dados lidos
    // imprimirDados(veiculo, clientes);

    return 0;
}
