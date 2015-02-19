# include "TSPPunto.h"

                 /* MÉTODOS PÚBLICOS */

// Método público que cambia la abscisa del punto:
void TSPPunto::setX(double x){
    this -> x = x;
}

// Método público que cambia la ordenada del punto:
void TSPPunto::setY(double y){
    this -> y = y;
}

// Método público que cambia las coordenadas del punto:
void TSPPunto::setCoordenadas(double x, double y){
    setX(x);
    setY(y);
}


// Método público que calcula la distancia del punto a otro punto dado:
double TSPPunto::distanciaHasta(const TSPPunto punto) const{
    
    double x2 = punto.getX();
    double y2 = punto.getY();

    return sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
}