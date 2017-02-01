
#include "GUI.h"
#include "System.h"
#include "Logger.h"
#include "MenuScene.h"
#include "Difficultyscene.h"
#include "HardScene.h"
#include "NormalScene.h"
#include "EasyScene.h"
#include <XML/rapidxml_utils.hpp>


using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

DifficultyScene::DifficultyScene(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 };
}

DifficultyScene::~DifficultyScene(void) {
}

void DifficultyScene::OnEntry(void) {

	

}

void DifficultyScene::OnExit(void) {
}

void DifficultyScene::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	
	//easy
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>() && IM.GetMouseCoords().x > 456 && IM.GetMouseCoords().x < 567 && IM.GetMouseCoords().y > 130 && IM.GetMouseCoords().y < 175) {  //Apretar el boto de play
		SM.SetCurScene <EasyScene>();
	


		
		mouseCoords = IM.GetMouseCoords();
	}
	//normal
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>() && IM.GetMouseCoords().x > 436 && IM.GetMouseCoords().x < 567 && IM.GetMouseCoords().y > 210 && IM.GetMouseCoords().y < 250) {  //Apretar el boto de play
		SM.SetCurScene <NormalScene>();
	


		
		mouseCoords = IM.GetMouseCoords();
	}
	//hard
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>() && IM.GetMouseCoords().x > 456 && IM.GetMouseCoords().x < 567 && IM.GetMouseCoords().y > 268 && IM.GetMouseCoords().y < 344) {  //Apretar el boto de play
		SM.SetCurScene <HardScene>();
	
		mouseCoords = IM.GetMouseCoords();
	}
	//back
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>() && IM.GetMouseCoords().x > 463 && IM.GetMouseCoords().x < 559 && IM.GetMouseCoords().y > 421 && IM.GetMouseCoords().y < 498) {  //Apretar el boto de exit
		SM.SetCurScene <MenuScene>();
		mouseCoords = IM.GetMouseCoords();
	}



}

void DifficultyScene::Draw(void) {
	m_background.Draw(); // Render background
	GUI::DrawTextSolid<FontID::ARIAL>("Choose difficulty",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
	{ 60, 60, 230 });

	//juego en facil
	GUI::DrawTextShaded<FontID::ARIAL>("Easy",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.2f), 1, 1 },
	{ 60, 60, 190 }, { 160, 180, 120 });

	//en dificultad normal
	GUI::DrawTextShaded<FontID::ARIAL>("Normal",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.3f), 1, 1 },
	{ 60, 60, 190 }, { 160, 180, 120 }); 

	//en dificultad dificil
	GUI::DrawTextShaded<FontID::ARIAL>("Hard",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
	{ 60, 60, 190 }, { 160, 180, 120 }); 

	//volver al menu
	GUI::DrawTextShaded<FontID::ARIAL>("Back",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 },
	{ 60, 60, 190 }, { 160, 180, 120 });
}
