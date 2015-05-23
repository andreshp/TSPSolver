#include "TSPBacktracking.h"

TSPBacktracking::TSPBacktracking(TSPProblema *problema)
:problema(problema),nombre_algoritmo("Backtracking"),solucion(NULL)
{}

pair <long long, long long> TSPBacktracking::resolver(){
    
    TSPSolucion *greedy = TSPVecinoMasCercano(problema).obtenerSolucion();
    int mejor_sol = greedy->distanciaTotal();

    //Initialize solution with greedy algorithm.
    TSPSolucion *sol_backtracking = new TSPSolucion(problema,&nombre_algoritmo);
    set<int> candidatos;

    //Initialize candidates and root solution.
    for(int i = 1; i < problema->numeroCiudades(); i++)
        candidatos.insert(i);

    sol_backtracking->pushCiudad(0);

    //Call to recursive function.
    pair<long long, long long> rec = resolver(candidatos,sol_backtracking,mejor_sol);

/*    if(solucion->distanciaTotal() == mejor_sol){
        delete sol_backtracking;
        solucion = new TSPSolucion(solucion);
    }
    else solucion = sol_backtracking;*/
    if(solucion == NULL) solucion = new TSPSolucion(*greedy);

    return rec;
}

pair <long long, long long> TSPBacktracking::resolver(set<int> & candidatos, TSPSolucion *sol_backtracking, int mejor_sol){
    pair <long, long> rec(0,0);
    //When we are in a leaf
    if(candidatos.empty()){
        rec.second++;
        if(sol_backtracking->distanciaTotal() < mejor_sol){
            mejor_sol = sol_backtracking->distanciaTotal();
            if(solucion != NULL) delete solucion;
            solucion = new TSPSolucion(*sol_backtracking);
            rec.first++;
        }
    }
    //Else we visit sons if needed
    for(set<int>::iterator i = candidatos.begin(); i != candidatos.end(); ++i){
        int ciudad = *i;
        sol_backtracking->pushCiudad(ciudad);
        candidatos.erase(i);

        rec.first++;
        
        if(sol_backtracking->distanciaTotal() < mejor_sol){
            pair <long,long> rrec = resolver(candidatos,sol_backtracking, mejor_sol);
            rec.first += rrec.first; rec.second += rrec.second;
        }
        
        i = candidatos.insert(sol_backtracking->popCiudad()).first;
    }
    return rec;
}
