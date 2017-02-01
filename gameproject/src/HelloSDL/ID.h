
#pragma once
#include <iostream>

// Enum ID used to identify each Game Object in the Game
enum class ObjectID : int {
	SNAKE_HEAD, SNAKE_HEAD_RIGHT, SNAKE_HEAD_DOWN, SNAKE_HEAD_LEFT, //head sprites
	SNAKE_BODY, SNAKE_BODY_LEFT, SNAKE_BODY_RIGHT, SNAKE_BODY_DOWN, //body sprites
	SNAKE_TAIL, SNAKE_TAIL_RIGHT, SNAKE_TAIL_LEFT, SNAKE_TAIL_DOWN, //tail sprites
	FOOD, //sprites IDs
	CELL_EMPTY, // Cell IDs
	BG_00,// Background IDs
	WALL, //wall sprite
	GO,  //game over sprite
	SCORE, //Score scene background
	EasyLvl,
	NormalLvl,
	HardLvl,
	TIMER
};
inline std::ostream &operator<<(std::ostream &os, const ObjectID &id) { return os << int(id); };
inline std::istream &operator>>(std::istream &is, ObjectID &id) { return is >> reinterpret_cast<int&>(id); };
// Enum ID used to store each true type font for text rendering
enum class FontID : int {
	ARIAL,
	
	MAX
};

