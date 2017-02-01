
#include "Player.h"
#include "Snake.h"
#include "InputManager.h"
#include <iostream>
#include <conio.h>
#include "EasyScene.h"
#include "Window.h"

using namespace std; 



void snake::eat() {
	alimentosObt++;
	
}
void snake::init_list() {
		tail.x =530;
		tail.y = 330;
		segments.push_front(tail);//inicializar la cola en la posicion inicial
		body.x = 560;
		body.y = 360;
		segments.push_front(body);//inicializar el cuerpo en la posicion inicial
		head.x = 590;
		head.y = 390;
		segments.push_front(head);//inicializar la cabeza en la posicion inicial
		
	
	

};
void snake::move() {
	
	//list<COORD>::iterator pos; //inicializar el iterador
	//pos = segments.begin(); //hacer q el iterador apunte a la primera posicion
	

	switch (dir) {//comprobar que direccion esta

		case UP://si mira hacia delante

			head.x += v; //avanza
			

			break;
		case DOWN://si mira hacia atras


			head.x -= v; //retrocede
			

			break;
		case LEFT://si mira hacia arriba (su izquierda al inicializar)

			head.y -= v;//sube 
			break;
		case RIGHT://si mira hacia abajo (su derecha al inicializar)

			head.y += v;//baja
			
			break;
		default:
			break;
		}
	
	segments.pop_back(); //elimina el ultimo elemento
	segments.push_front(head); //añade el nuevo elemento con la nueva posicion
	
			}
			
		
	
void snake::getKey() {

	
		if (IM.IsKeyUp<KEY_BUTTON_LEFT>()) { //detecta si pulsas la flecha izquierda
			snake::girarIzq();
		}
		else if (IM.IsKeyUp<KEY_BUTTON_RIGHT>()) {//Detecta si pulsas la flecha derecha
			snake::girarDer();
		}
	}
	

void snake::girarIzq() {//cambia la direccion en el sentido contrario de las agujas del reloj
	dir--;
	if (dir < 0) { 
		dir = 3;
	}
	
}

void snake::girarDer() {//cambia la direccion en el sentido de las agujas del reloj
	dir++;
	if (dir > 3) {
		dir = 0;
	}
}

int snake::getint(int x) { return x; }//simple, lo cree por algunos errores que habia antes

bool snake::Collision(snake::COORD headNow) {
	list<snake::COORD>::iterator pos;
	pos = segments.begin();
	pos++;
	

	headNow = *pos;
	
	while (pos != segments.end()) {
		headNow = *pos;
		
		if ((headNow.x == head.x || (headNow.x < head.x + 15 && headNow.x > head.x - 15))
			&& (headNow.y == head.y || (headNow.y < head.y + 15 && headNow.y > head.y - 15))) {
			
			
			return true;

		}
		pos++;
		
		
	}
	return false;
}
