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

	s = BB(cost, data.getDimension());

	hungarian_problem_t p;
	int mode = HUNGARIAN_MODE_MINIMIZE_COST;
	hungarian_init(&p, cost, data.getDimension(), data.getDimension(), mode); // Carregando o problema

	double obj_value = hungarian_solve(&p);
	cout << "Obj. value: " << obj_value << endl;

	cout << "Assignment" << endl;
	hungarian_print_assignment(&p);

	hungarian_free(&p);
	for (int i = 0; i < data.getDimension(); i++)
		delete[] cost[i];
	delete[] cost;

	return 0;
}
