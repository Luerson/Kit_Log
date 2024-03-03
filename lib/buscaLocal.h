#ifndef BUSCALOCAL_H
#define BUSCALOCAL_H

#include <bits/stdc++.h>
#include "solucao.h"
#include "../src/Data.h"

void buscaLocal(Solution &, Data &);
bool bestImprovementSwap(Solution &, Data &);
bool bestImprovement20pt(Solution &, Data &);
bool bestImprovement0r0pt(Solution &, Data &, int);

#endif