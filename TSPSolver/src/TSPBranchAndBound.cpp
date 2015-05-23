#include "TSPBranchAndBound.h"

    void Nodo::estimar(){
        if(parcial->getNumVisitadas() == problema->numeroCiudades())
            estimacion  = -1;
        else{
            int ciudad = parcial->ciudadVisitada(parcial->getNumVisitadas()-1);
            estimacion = (1.0)/(0.0);
            for(int i = 0; i < parcial->getNumCiudades();i++){
                if(!parcial->visitada(i) && ciudad != i && problema->elementoMatrizDistancias(ciudad,i) < estimacion)
                    estimacion = problema->elementoMatrizDistancias(ciudad,i);
            }
        }
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
        if(estimacion != -1)
            for(int i = 0; i < problema->numeroCiudades(); i++){
                if(!parcial->visitada(i)){
                    TSPSolucion *newparcial = new TSPSolucion(*parcial);
                    newparcial->pushCiudad(i);
                    hijos.push_back(Nodo(problema,newparcial));
                }
            }
        return hijos;
    }


    void TSPBranchAndBound::resolver(){
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
                if(n.getSolucion()->distanciaTotal() < mejor_sol){
                    delete solucion;
                    solucion = n.getSolucion();
                    mejor_sol = solucion->distanciaTotal();
                }
                else n.eraseNode();
            }
        }
    }
