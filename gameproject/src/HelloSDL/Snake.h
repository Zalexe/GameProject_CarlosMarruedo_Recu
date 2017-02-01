#include "Scene.h"
#include "GUI.h"
#include "Player.h"
#include "System.h"
#include "Logger.h"

#include <conio.h>

#include <iostream>
#include <list>

using namespace std;
#pragma once



// Scene class that serves as part of the Model
enum Direction { UP, RIGHT, DOWN,  LEFT};
class snake {
private:
	
	
	

public:
	int v ; //inicializar velocidad
	int dir = UP; //direccion de la serpiente
	


	int lifes; //inicializar vidas

	int alimentosObt = 0; //inicializar lista de alimentos comidos
	struct COORD //Crear el struct de coordenadas
	{
		int x;
		int y;
		 
	};
	COORD head, body, tail, aux, aux2; //inicializar variables de coordenadas
	list<COORD> segments; //inicializar lista
 

	void init_list(); //funcion para inicializar los elementos de la lista

	int getint(int x); //para facilitar la obtencion de variables de la lista o coordenadas
	
	
	void getKey(); //inicializar funcion para el cambio de direcciones segun la tecla q pulses
	void girarIzq(); //inicializar funcion de girar izquierda (en funcion de donde mire)
	void girarDer();//inicializar funcion de girar derecha


	void eat(); //inicializar funcion de comer
	void move(); //inicializar funcion de movimiento
	bool Collision(COORD headnow);//funcion de colision con el cuerpo
	
};
