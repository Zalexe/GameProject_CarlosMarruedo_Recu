#pragma once
#include "Sprite.h"
#include "Scene.h"
#include "TimeManager.h"
// MenuScene class with the main gameplay mode
class NormalScene : public Scene {
public:
	explicit NormalScene();
	~NormalScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void NormalScene::ReadXML();
private:
	//iniciacion de los sprites que usaremos en el nivel
	Sprite m_background;
	Sprite s_head;
	Sprite s_body;
	Sprite s_tail;
	Sprite s_food;
	Sprite m_empty;
	Sprite Wall1;
	Sprite Wall2;
	Sprite Wall3;
	Sprite Wall4;
	Sprite timer;
	//tiempo limite
	int tiempo;
	int tiempomax;
	int sizeChekpoint;
	int nivel;

	//variables xml
	int arriba_x, arriba_y, derecha_x, derecha_y, abajo_x, abajo_y, izquierda_x, izquierda_y, time, speed, initial, incremental;

	int alimentosPorObt;

};