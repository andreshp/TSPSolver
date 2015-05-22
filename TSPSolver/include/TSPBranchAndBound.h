#ifndef TSPBYB_H
#define TSPBYB_H

    # include "TSPProblema.h"
    # include "TSPSolucion.h"
    # include "TSPVecinoMasCercano.h"
    # include <queue>
    # include <set> 

    struct Nodo{
    private:
        TSPSolucion *parcial;
        TSPProblema *problema;
        double estimacion;

    public:
        inline bool operator<(const Nodo & otro) const{
            return this->estimacion < otro.estimacion;
        }

        void estimar();

        Nodo(TSPProblema *problema, TSPSolucion *solucion){
            problema = problema;
            parcial = solucion;
            estimar();
        }

        ~Nodo(){
            delete parcial;
        }

        double getEstimacion() const{
            return estimacion;
        }

        TSPSolucion getSolucion() const{
            return *parcial;
        }

        set<int> getHijos() const;


    };
    class TSPBranchAndBound{
    private:
        TSPProblema *problema;
        TSPSolucion *solucion;
        const string nombre_algoritmo;

    public:
        TSPBranchAndBound(TSPProblema *problema);

        void resolver(vector <int> & candidatos,priority_queue <int> min_coste);
        void resolver();

        inline TSPSolucion *obtenerSolucion(){
            return solucion;
        }
        
    };

#endif