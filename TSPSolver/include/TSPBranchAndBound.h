#ifndef TSPBYB_H
#define TSPBYB_H

    # include "TSPProblema.h"
    # include "TSPSolucion.h"
    # include "TSPVecinoMasCercano.h"
    # include <queue>
    # include <set> 

    class Nodo{
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
            this->problema = problema;
            parcial = solucion;
            estimar();
        }

        double eraseNode(){
            delete parcial;
            estimacion = 0;
        }
        double getEstimacion() const{
            return estimacion;
        }

        TSPSolucion *getSolucion() const{
            return parcial;
        }

        vector <Nodo> getHijos() const;


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
            resolver();
            return solucion;
        }
        
    };

#endif