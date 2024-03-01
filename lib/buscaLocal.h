#ifndef BUSCALOCAL_H
#define BUSCALOCAL_H

#include <bits/stdc++.h>
#include "solucao.h"
#include "../src/Data.h"

void buscaLocal(Solution &, Graph &);
bool bestImprovementSwap(Solution &, Graph &);
bool bestImprovement20pt(Solution &, Graph &);
bool bestImprovement0r0pt(Solution &, Graph &, int);

#endif