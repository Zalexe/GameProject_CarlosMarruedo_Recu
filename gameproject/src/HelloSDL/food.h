#pragma once
#include "ID.h"
#include "Renderer.h"
#include "Transform.h"
#include "snake.h"


class food {

public:
	int position_y;
	int position_x;
	bool InScene;
	bool isCollision(snake::COORD po);
	void FoodSpawn();


};