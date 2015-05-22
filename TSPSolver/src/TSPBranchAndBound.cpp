#include "TSPBranchAndBound.h"

    void Nodo::estimar(){
        int ciudad = parcial->ciudadVisitada(parcial->getNumVisitadas()-1);
        estimacion = (1.0)/(0.0);
        for(int i = 0; i < parcial->getNumCiudades();i++){
            if(!parcial->visitada(i) && ciudad != i && problema->elementoMatrizDistancias(ciudad,i) < estimacion)
                estimacion = problema->elementoMatrizDistancias(ciudad,i);
        }
    }

    TSPBranchAndBound::TSPBranchAndBound(TSPProblema *problema)
    :nombre_algoritmo("Branch and Bound"),problema(problema)
    {}

    set<int> Nodo::getHijos() const{
        set <int> hijos;
        for(int i = 0; i < problema->numeroCiudades(); i++){
            if(!parcial->visitada(i))
                hijos.insert(i);
        }
        return hijos;
    }


    void TSPBranchAndBound::resolver(){
        set<int> candidatos;
        for(int i = 0; i < problema->numeroCiudades(); i++){
            candidatos.insert(i);
        }
        priority_queue<Nodo> queue;
        TSPSolucion sol(problema,&nombre_algoritmo);
        sol.pushCiudad(0);

        Nodo root(problema,&sol);
        solucion = TSPVecinoMasCercano(problema).obtenerSolucion();
        int mejor_sol = solucion->distanciaTotal();
        while(!queue.empty() && queue.top().getEstimacion() < mejor_sol){
            Nodo n = queue.top();
            queue.pop();
            set<int> candidatos = n.getHijos();
            for(set<int>::iterator i = candidatos.begin(); i != candidatos.end(); ++i){
                TSPSolucion solh(n.getSolucion());
                solh.pushCiudad(*i);
                Nodo hijo = Nodo(problema,&solh);
                hijo.estimar();
                if(hijo.getEstimacion() < mejor_sol){
                    queue.push(hijo);
                }
            }
            if(n.getSolucion().getNumVisitadas() == problema->numeroCiudades() && n.getSolucion().distanciaTotal() < mejor_sol){
                mejor_sol = n.getSolucion().distanciaTotal();
                *solucion = n.getSolucion();
            }

        }
    }


   //while not cola.empty && cola.top.estimación < mejor_sol:
   //nodo = cola.pop
   //hijos = nodo hijos
   //for h in hijos:
   //    h.estimar()
   //    if h.estimación < mejor_sol:
   //       cola.push(h)

