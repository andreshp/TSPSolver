#include "TSPBranchAndBound.h"
#include <limits>

    void Nodo::estimar(){
        estimacion = parcial->distanciaTotal() - problema->elementoMatrizDistancias(parcial->ciudadVisitada(0), parcial->ciudadVisitada(parcial->getNumVisitadas()-1));
        if(parcial->getNumVisitadas() < problema->numeroCiudades()){
            int min_0, min_N; min_0 = min_N = std::numeric_limits<int>::max();
            for(int i = 0; i < problema->numeroCiudades(); i++){
                if(!parcial->visitada(i)){
                    //Add min distances to first city
                    if(problema->elementoMatrizDistancias(i,parcial->ciudadVisitada(0)) < min_0)
                        min_0 = problema->elementoMatrizDistancias(i,parcial->ciudadVisitada(0));
                    //Add min distances to last city
                    if(problema->elementoMatrizDistancias(i,parcial->ciudadVisitada(parcial->getNumVisitadas()-1)) < min_N)
                        min_N = problema->elementoMatrizDistancias(i,parcial->ciudadVisitada(parcial->getNumVisitadas()-1));

                    if (parcial->getNumVisitadas() < problema->numeroCiudades()-1){
                        //Add min distances between non-visited
                        int min = std::numeric_limits<int>::max();
                        for(int j = 0; j < problema->numeroCiudades(); j++){
                            if(j != i && !parcial->visitada(j) && problema->elementoMatrizDistancias(i,j) < min)
                                min = problema->elementoMatrizDistancias(i,j);
                        }
                        estimacion += min;
                    }
                }
            }
            estimacion += (min_0 + min_N);
//            cout << "Estimacion: " << estimacion << " Coste: " << parcial->distanciaTotal() << " min_0: " << min_0 << " min_N: " << min_N << endl;
        }
        //if(parcial->getNumVisitadas() == problema->numeroCiudades())
        //    estimacion  = -1;
        //else{
        //    int ciudad = parcial->ciudadVisitada(parcial->getNumVisitadas()-1);
        //    estimacion = (1.0)/(0.0);
        //    for(int i = 0; i < parcial->getNumCiudades();i++){
        //        if(!parcial->visitada(i) && ciudad != i && problema->elementoMatrizDistancias(ciudad,i) < estimacion)
        //            estimacion = problema->elementoMatrizDistancias(ciudad,i);
        //    }
        //}
    }

    TSPBranchAndBound::TSPBranchAndBound(TSPProblema *problema)
    :nombre_algoritmo("Branch and Bound"),problema(problema)
    {}

    
/*    set<int> Nodo::getHijos() const{
        set <int> hijos;
        for(int i = 0; i < problema->numeroCiudades(); i++){
            if(!parcial->visitada(i))
                hijos.insert(i);
        }
        return hijos;
    }*/

    vector <Nodo> Nodo::getHijos() const{
        vector <Nodo> hijos;
        //if(estimacion != -1)
        for(int i = 0; i < problema->numeroCiudades(); i++){
            if(!parcial->visitada(i)){
                TSPSolucion *newparcial = new TSPSolucion(*parcial);
                newparcial->pushCiudad(i);
                hijos.push_back(Nodo(problema,newparcial));
            }
        }
        return hijos;
    }


    pair<long long, long long> TSPBranchAndBound::resolver(){
        long long count_nodes = 1;
        long long count_solutions = 1;
        //Initialize queue pushing root node.
        priority_queue<Nodo> queue;
        TSPSolucion *sol_root = new TSPSolucion(problema,&nombre_algoritmo);
        sol_root->pushCiudad(0);
        Nodo root(problema,sol_root);
        queue.push(root);
        
        //Initialize best solution at the moment with greedy algorithm
        solucion = TSPVecinoMasCercano(problema).obtenerSolucion();
        int mejor_sol = solucion->distanciaTotal();

        while(!queue.empty() && queue.top().getEstimacion() < mejor_sol){
            Nodo n = queue.top();
            queue.pop();
            count_nodes++;
            
            //Add to queue son nodes
            vector <Nodo> hijos = n.getHijos();
            for(int i = 0; i < hijos.size(); i++){
                hijos[i].estimar();
                if(hijos[i].getEstimacion() < mejor_sol){
                    queue.push(hijos[i]);
                }
            }

            //Update best solution if needed.
            if(n.getSolucion()->getNumVisitadas() == problema->numeroCiudades()){
                count_solutions++;
                if(n.getSolucion()->distanciaTotal() < mejor_sol){
                    delete solucion;
                    solucion = n.getSolucion();
                    mejor_sol = solucion->distanciaTotal();
                }
                else n.eraseNode();
            }
        }
        return pair<long long, long long>(count_nodes, count_solutions);
    }
