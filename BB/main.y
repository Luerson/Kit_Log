#include <iostream>
using namespace std;

#include "data.h"
#include "hungarian.h"
#include "solucao.h"
#include "lib/BB.h"

int main(int argc, char **argv)
{

	Solution s;
	Data data = Data(argc, argv[1]);
	data.readData();

	double **cost = new double *[data.getDimension()];
	for (int i = 0; i < data.getDimension(); i++)
	{
		cost[i] = new double[data.getDimension()];
		for (int j = 0; j < data.getDimension(); j++)
		{
			cost[i][j] = data.getDistance(i, j);
		}
	}

	while (1)
	{
		int strategy;
		cout << "1 - DFS" << endl;
		cout << "2 - BFS" << endl;
		cout << "3 - LB" << endl;
		cout << "0 - encerrar" << endl;

		cin >> strategy;

		if (strategy == 0)
		{
			break;
		}
		if (strategy < 0 && strategy > 3)
		{
			cout << "estrateia invalida" << endl;
		}
		s = BB(cost, data.getDimension(), strategy);
		cout << s.odj_value << endl;
	}

	for (int i = 0; i < data.getDimension(); i++)
		delete[] cost[i];
	delete[] cost;

	return 0;
}
