
#pragma once

#include <string>

// Scene class that serves as part of the Model
class Player {
	
public:
	explicit Player() = default;
	virtual ~Player() = default;
	
	int score;//inicializar score
	std::string Name; //inicializar nombre
	int MaxScore; //inicializar max score


};