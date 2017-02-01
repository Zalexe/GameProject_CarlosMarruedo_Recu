#pragma once
#include "Sprite.h"
#include "Scene.h"
#include <iostream>
#include <fstream>

using namespace std;

// MenuScene class with the main gameplay mode
class RankingScene : public Scene {
public:
	explicit RankingScene();
	~RankingScene() override;
	void OnEntry(void) override;
	void OnExit(void) override;
	void Update(void) override;
	void Draw(void) override;
	void RankingScene::LeerBinario();
	void RankingScene::EscribirBinario();
private:
	struct Player {
		string Name;
		int score;
	}; //nombre del jugador
	 //score del jugador
	Player ranking[10];
	Sprite m_background;

	Player p1{"---",0};
	Player p2{ "---",0 };
	Player p3{ "---",0 };
	Player p4{ "---",0 };
	Player p5{ "---",0 };
	Player p6{ "---",0 };
	Player p7{ "---",0 };
	Player p8{ "---",0 };
	Player p9{ "---",0 };
	Player p10{ "---",0 };


};