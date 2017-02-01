#include "GUI.h"
#include "System.h"
#include "Logger.h"
#include "MenuScene.h"
#include "DifficultyScene.h"
#include "RankingScene.h"
#include "Player.h"

extern int scores;

using namespace std;
using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

RankingScene::RankingScene(void) {
	ranking[0] = p1;
	ranking[1] = p2;
	ranking[2] = p3;
	ranking[3] = p4;
	ranking[4] = p5;
	ranking[5] = p6;
	ranking[6] = p7;
	ranking[7] = p8;
	ranking[8] = p9;
	ranking[9] = p10;
	

	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::SCORE };
}

RankingScene::~RankingScene(void) {
}
void RankingScene::LeerBinario() {//leer archivos binarios
	
	ifstream fentrada("ranking.dat", ios::in | ios::binary);//abrir el archivo binario

	
	
		fentrada.read(reinterpret_cast<char *>(&ranking), sizeof(ranking));//interpretar los factores dentro del archivo
	
	fentrada.close();//cerrar el archivo

}

void RankingScene::EscribirBinario() {

	ofstream fsalida("ranking.dat", ios::out | ios::binary);//ir al archivo binario
	
		fsalida.write(reinterpret_cast<char *>(&ranking), sizeof(ranking));//escribir en el archivo
	

	fsalida.close();//cerrar el archivo

}

void RankingScene::OnEntry(void) {
	
	RankingScene::Player aPlayer;//iniciar player

	RankingScene::Player temporal;//iniciar player archivo temporal

	RankingScene::Player temporal2;//iniciar player archivo temporal



	cout << "Enter your name: " << endl;

	cin >> aPlayer.Name;//introducir el nombre del jugador

	//EscribirBinario();
	
	LeerBinario(); //leer el archivo binario
	
		aPlayer.score = scores;
	

	bool found = false;//bool para el ranking

	for (int i = 0; i < 10; i++) {

		if (ranking[i].score<aPlayer.score && !found) {//insertar en el ranking si es mayor que otro de el ranking

			temporal = ranking[i];

			ranking[i] = aPlayer;

			i++;

			found = true;

		}

		else if (found) {//poner los temporales en los sitios que no son mayores
			
				temporal2 = ranking[i];

				ranking[i] = temporal;

				temporal = temporal2;
			
		}

	}

	EscribirBinario();

	cout << "Top 10 player" << endl;

	for (int i = 0; i < 10; i++) {

		cout << ranking[i].Name << "--------->";

		cout << ranking[i].score << endl;

	}
	scores = 0;
}

void RankingScene::OnExit(void) {
	
}

void RankingScene::Update(void) {
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

void RankingScene::Draw(void) {
	m_background.Draw(); // Render background
	GUI::DrawTextSolid<FontID::ARIAL>("Ranking on the console",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.2f),1, 1 },
	{ 0, 0, 0 });
	GUI::DrawTextShaded<FontID::ARIAL>("Play Again",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.4f), 1, 1 },
	{ 60, 60, 190 }, { 160, 180, 120 });
	GUI::DrawTextShaded<FontID::ARIAL>("Exit",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.6f), 1, 1 },
	{ 60, 60, 190 }, { 160, 180, 120 });
}
