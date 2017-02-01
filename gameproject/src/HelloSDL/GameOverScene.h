#pragma once
#include "Sprite.h"
#include "Scene.h"

// MenuScene class with the main gameplay mode
class GameOverScene : public Scene {
public:
	explicit GameOverScene();
	~GameOverScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
private:
	Sprite m_background;
};