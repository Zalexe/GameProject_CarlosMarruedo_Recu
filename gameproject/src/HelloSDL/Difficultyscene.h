#pragma once
#include "Sprite.h"
#include "Scene.h"

// MenuScene class with the main gameplay mode
class DifficultyScene : public Scene {
public:
	explicit DifficultyScene();
	~DifficultyScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background;
	Sprite s_head;
	Sprite s_body;
	Sprite s_tail;
	Sprite s_food;
	Sprite m_empty;
	int tiempo;
};