# ifndef TSPPUNTO_H
# define TSPPUNTO_H

    # include <cmath>
    
    using namespace std;
    
    /**
    * @brief Clase que representa un punto en el plano que se utilizará como coordenadas de una ciudad dada para el TSP.
    */
    
    class TSPPunto{
        private:
                                        /* DATOS MIEMBRO */
            /*
            * @brief Dato miembro que representa la abscisa de un punto.
            */
            double x;
            
            /*
            * @brief Dato miembro que representa la ordenada de un punto.
            */
            double y;
        
        public:
                                        /* MÉTODOS PÚBLICOS */
            /**
            * @brief Método público que cambia la abscisa del punto.
            * @param x Nuevo valor double para la abscisa.
            */
            void setX(double x);
            
            /**
            * @brief Método público que cambia la ordenada del punto.
            * @param y Nuevo valor double para la ordenada.
            */
            void setY(double y);
        
            /**
            * @brief Método público que cambia las coordenadas del punto.
            * @param x Nuevo valor double para la abscisa.
            * @param y Nuevo valor double para la ordenada.
            */
            void setCoordenadas(double x, double y);
        
            /**
            * @brief Método público que devuelve la abscisa del punto.
            * @return Abscisa del punto (dato miembro x).
            */
            inline double getX() const{
                return x;
            }
            
            /**
            * @brief Método público que devuelve la ordenada del punto.
            * @return Ordenada del punto (dato miembro y).
            */
            inline double getY() const{
                return y;
            }
            
            /**
            * @brief Método público que calcula la distancia del punto a otro punto dado.
            * @param punto Objeto de la clase TSPPunto.
            * @return Distancia entre los dos puntos.
            */
            int distanciaHasta(const TSPPunto punto) const;
    };

# endif