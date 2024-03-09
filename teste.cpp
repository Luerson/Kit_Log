#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
    // Abre o arquivo de leitura
    ifstream inputFile("entrada.txt");
    if (!inputFile)
    {
        cerr << "Erro ao abrir o arquivo de entrada." << endl;
        return 1;
    }

    // Abre o arquivo de escrita
    ofstream outputFile("dados_saida.txt");
    if (!outputFile)
    {
        cerr << "Erro ao abrir o arquivo de saída." << endl;
        return 1;
    }

    string line;
    while (getline(inputFile, line))
    {
        // Usando stringstream para dividir a linha em palavras
        stringstream ss(line);
        string instance;
        double expectedTime, obtainedTime, expectedCost, obtainedCost;

        // Lê os valores de cada coluna
        ss >> instance >> expectedTime >> obtainedTime >> expectedCost >> obtainedCost;

        // Realiza alguma operação com os valores (por exemplo, soma)
        double per_time = ((obtainedTime - expectedTime) / obtainedTime) * 100.0;
        double per_cost = ((expectedCost - obtainedCost) / expectedCost) * 100.0;

        // Escreve os resultados no arquivo de saída
        outputFile << instance << " ";
        outputFile << fixed << setprecision(1) << per_time << " ";
        outputFile << fixed << setprecision(3) << per_cost << " ";
        outputFile << fixed << setprecision(3) << obtainedTime << " ";
        outputFile << fixed << setprecision(1) << expectedCost << " ";
        outputFile << fixed << setprecision(3) << expectedTime << " ";
        outputFile << fixed << setprecision(1) << obtainedCost << endl;
    }

    // Fecha os arquivos
    inputFile.close();
    outputFile.close();

    cout << "Operação concluída. Verifique o arquivo 'dados_saida.txt'." << endl;

    return 0;
}