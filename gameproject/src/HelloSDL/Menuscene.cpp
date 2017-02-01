
#include "GUI.h"
#include "System.h"
#include "Logger.h"
#include "MenuScene.h"
#include "DifficultyScene.h"
using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

MenuScene::MenuScene(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 }; //inicializa el sprite del background
}

MenuScene::~MenuScene(void) {
}

void MenuScene::OnEntry(void) {
}

void MenuScene::OnExit(void) {
}

void MenuScene::Update(void) {
	static MouseCoords mouseCoords(0, 0); //inicializa la variable de las cordenadas de las mouse
	

	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>() && IM.GetMouseCoords().x > 456 && IM.GetMouseCoords().x < 567 && IM.GetMouseCoords().y > 268 && IM.GetMouseCoords().y < 344) {  //Apretar el boto de play
		SM.SetCurScene <DifficultyScene>(); //cambia de escena
		mouseCoords = IM.GetMouseCoords();//Detecta la posicion del mouse
	}

	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>() && IM.GetMouseCoords().x > 463 && IM.GetMouseCoords().x < 559 && IM.GetMouseCoords().y > 421 && IM.GetMouseCoords().y < 498) {  //Apretar el boto de exit
		IM.SetQuit(); //cerrar el juego
		mouseCoords = IM.GetMouseCoords();
	}



}

void MenuScene::Draw(void) {
	m_background.Draw(); // Render background
	GUI::DrawTextSolid<FontID::ARIAL>("The great Snake",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.2f), 1, 1 },
	{ 60, 60, 230 }); // Render score that will be different when updated
	GUI::DrawTextShaded<FontID::ARIAL>("Play",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
	{ 60, 60, 190 }, { 160, 180, 120 }); // Render score that will be different when updated
	GUI::DrawTextShaded<FontID::ARIAL>("Exit",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 },
	{ 60, 60, 190 }, { 160, 180, 120 }); // Render score that will be different when updated
}
