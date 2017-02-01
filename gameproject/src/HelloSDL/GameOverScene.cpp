
#include "GUI.h"
#include "System.h"
#include "Logger.h"
#include "MenuScene.h"
#include "GameOverScene.h"
#include "RankingScene.h"

using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

GameOverScene::GameOverScene(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::GO };
}

GameOverScene::~GameOverScene(void) {
}

void GameOverScene::OnEntry(void) {
}

void GameOverScene::OnExit(void) {
}

void GameOverScene::Update(void) {
	SDL_Delay(2000); //esperar un rato
	SM.SetCurScene<RankingScene>(); //ir al ranking scene
}

void GameOverScene::Draw(void) {
	m_background.Draw(); // Render background
	GUI::DrawTextShaded<FontID::ARIAL>("Game Over",
	{ W.GetWidth() >> 2, int(W.GetHeight()*.4f), 4, 3 },
	{ 390, 0, 0 }, { 0, 0, 0 });

}
