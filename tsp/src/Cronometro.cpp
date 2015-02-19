#include "Cronometro.h"

using namespace std;

//Constructor por defecto para inicializar el cronómetro.
Cronometro::Cronometro(){
	inicio = 0;
	fin = 0;
	activado = false;
	srand(time(NULL));
}

//Método para poner en marcha el cronómetro.
void Cronometro::start(){
	if(!activado){
		activado = true;
	}
	inicio = clock();
}

//Método para detener el cronómetro.
void Cronometro::stop(){
	if(activado){
		activado = false;
		fin = clock();
	}
}

//Método que devuelve el tiempo transcurrido en segundos.
double Cronometro::get_time() const{
	if(activado){
		return (clock() - inicio)/ (double)CLOCKS_PER_SEC;
	}
	else{
		return (fin - inicio)/ (double)CLOCKS_PER_SEC;
	}
}

//Método que imprime el tiempo transcurrido desde que se inició el cronómetro.
void Cronometro::message() const{
	cout << "Se ha tardado " << get_time() << " segundos.\n";
}



