/*#include <iostream>
using namespace std;

#include "data.h"
#include "hungarian.h"
#include "solucao.h"
#include "lib/BB.h"

void processarLinha(char *str, double tempoEsp, double custoEsp, ofstream &outputFile)
{
    Solution s;

    Data data = Data(2, str);
    data.readData();
    size_t n = data.getDimension();

    double **cost = new double *[data.getDimension()];
    for (int i = 0; i < data.getDimension(); i++)
    {
        cost[i] = new double[data.getDimension()];
        for (int j = 0; j < data.getDimension(); j++)
        {
            cost[i][j] = data.getDistance(i, j);
        }
    }

    double totalTimeDFS = 0.0;
    double totalTimeBFS = 0.0;
    double totalTimeLB = 0.0;
    double midTimeDFS = 0.0;
    double midTimeBFS = 0.0;
    double midTimeLB = 0.0;

    double solution;

    for (int i = 1; i <= 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            auto start = chrono::steady_clock::now();
            s = BB(cost, n, i);

            auto end = chrono::steady_clock::now();
            chrono::duration<double> elapsedTime = end - start;

            totalTimeDFS += (i == 1 ? elapsedTime.count() : 0);
            totalTimeBFS += (i == 2 ? elapsedTime.count() : 0);
            totalTimeLB += (i == 3 ? elapsedTime.count() : 0);
        }
    }

    midTimeDFS = totalTimeDFS / 4.0;
    midTimeBFS = totalTimeBFS / 4.0;
    midTimeLB = totalTimeLB / 4.0;

    if (!outputFile.is_open())
    {
        outputFile.open("resultados.tex", ios_base::app);
    }

    string nomeInstancia = str;
    nomeInstancia = nomeInstancia.substr(nomeInstancia.find_last_of("/") + 1);
    nomeInstancia.substr(0, nomeInstancia.size() - 4);

    outputFile << nomeInstancia << " & ";
    outputFile << fixed << setprecision(3) << midTimeDFS << " & ";
    outputFile << fixed << setprecision(3) << midTimeBFS << " & ";
    outputFile << fixed << setprecision(3) << midTimeLB << " & ";
    outputFile << fixed << setprecision(1) << s.odj_value << " \\\\" << endl;

    outputFile.close();
}

int main(int argc, char **argv)
{
    ifstream arquivo("instancias.txt");
    ofstream outputFile;

    if (arquivo.is_open())
    {
        string linha;
        while (getline(arquivo, linha))
        {
            char *linha_char = new char[linha.length() + 1];
            strcpy(linha_char, linha.c_str());

            char *str = strtok(linha_char, " ");
            double valor1 = atof(strtok(nullptr, " "));
            double valor2 = atof(strtok(nullptr, " "));

            processarLinha(str, valor1, valor2, outputFile);

            delete[] linha_char;
        }
    }
    else
    {
        cerr << "Erro ao abrir o arquivo!" << endl;
    }

    return 0;
}*/