#ifndef TSPBACKTRACKING_H
#define TSPBACKTRACKING_H

#include "TSPProblema.h"
#include "TSPSolucion.h"
#include "TSPVecinoMasCercano.h"

#include <vector>
#include <set>
#include <stdlib.h>

using namespace std;

class TSPBacktracking{
private:
    TSPProblema *problema;
    TSPSolucion *solucion;
    const string nombre_algoritmo;

    pair <long long, long long> resolver(set<int> & candidatos, TSPSolucion *sol_backtracking, int & mejor_sol);

public:
    TSPBacktracking(TSPProblema *problema);
    pair <long long, long long> resolver();

    inline TSPSolucion *obtenerSolucion(){
        return solucion;
    }

    //~TSPBacktracking(){
    //    if(solucion != NULL) delete solucion;
    //}
};
#endif