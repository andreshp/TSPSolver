#ifndef CRONO_H
#define CRONO_H

    # include <ctime>
    # include <iostream>
    # include <stdlib.h>
    
    /**
    * @brief Clase que permite evaluar el tiempo que tarda en ejecutarse un algoritmo.
    */
    
    class Cronometro{

    private:
        /* DATOS MIEMBRO */

        /**
         * @brief Valor que guarda el instante inicial para poder medir el tiempo.
         */
    	time_t inicio;

        /**
         * @brief Valor que guarda el instante final para el que se desea medir el tiempo.
         */
    	time_t fin;

        /**
         * @brief Dato miembro que indica si el cronómetro está en marcha o no.
         */
    	bool activado;
    
    public:

        /**
         * @brief Constructor de la clase. Inicializa el cronómetro con valores correctos.
         */
    	Cronometro();

        /* MÉTODOS PÚBLICOS */

        /**
         * @brief Inicia el cronómetro.
         */
    	void start();

        /**
         * @brief Detiene el cronómetro.
         */
    	void stop();

        /**
         * @brief Devuelve el tiempo en segundos transcurrido desde que se inició el cronómetro.
         * @return Segundos.
         */	
    	double get_time() const;

        /**
         * @brief Indica si el cronómetro está en marcha.
         * @return Valor booleano que será verdadero solo cuando esté activado.
         */
    	inline bool enMarcha() const{
            return this->activado;
        }

        /**
         * @brief Imprime un mensaje con el tiempo transcurrido.
         */
        void message() const;
    };

#endif												
