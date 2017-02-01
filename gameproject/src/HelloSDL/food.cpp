#include "food.h"
#include "snake.h"
#include "InputManager.h"
#include <iostream>
#include <conio.h>
#include "EasyScene.h"
#include "Window.h"
#include <time.h>
using namespace std; 

bool food::isCollision(snake::COORD pos) {
	if ((position_x == pos.x || (position_x < pos.x + 20 && position_x > pos.x - 20))
		&& (position_y == pos.y || (position_y < pos.y + 20 && position_y > pos.y - 20))) {

		return true;
	}
	else return false;
}

void food::FoodSpawn() {
	srand(time(NULL));//inicializar en posicion random en el limite del escenario
	position_x = rand()%820 +100;
	position_y = rand()%520+100;
} 