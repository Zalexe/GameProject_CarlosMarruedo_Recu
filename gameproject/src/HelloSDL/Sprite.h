#pragma once
#include "ID.h"
#include "Renderer.h"
#include "Transform.h"

// Sprite class that serves as part of the Model
struct Sprite {
	Transform transform;
	ObjectID objectID;
	void Draw() { R.Push(objectID, transform); };
};