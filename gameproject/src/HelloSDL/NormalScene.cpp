
#include "GUI.h"
#include "Player.h"
#include "System.h"
#include "Logger.h"
#include "NormalScene.h"
#include "DifficultyScene.h"
#include "Snake.h"
#include "food.h"
#include "GameOverScene.h"
#include "global.h"
#include <XML/rapidxml_utils.hpp>

#include <fstream>
#include <sstream> 
using namespace Logger;

using namespace std;
using namespace rapidxml;

snake snaki; //inicializar la serpiente
Player playerd;//inicializar el jugador
food appled;//inicializar la comida
extern int scores;

NormalScene::NormalScene(void) {
	//leer del XML
	NormalScene::ReadXML();

	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_00 }; //inicializar el background

	s_head = { { 0,0,30,30 },ObjectID::SNAKE_HEAD_RIGHT }; //inicializar sprites cabeza al empezar
	s_body = { { 0,0,30,30 },ObjectID::SNAKE_BODY };//inicializar sprites cuerpo al empezar
	s_tail = { { 0,0,30,30 },ObjectID::SNAKE_TAIL };//inicializar sprites cola al empezar
	s_food = { { appled.position_x,appled.position_y,30,30 },ObjectID::FOOD };//inicializar sprites cabeza al empezar
	m_empty = { { 0,0,30,30 },ObjectID::CELL_EMPTY };

	//no quedan del todo bien las variables del xml porq tambien se tiene que tener en cuenta el tamaño del sprite
	Wall1 = { { 20,(abajo_y - 50),abajo_x,50 },ObjectID::WALL };//abajo inclinado
	Wall2 = { { 20,50,arriba_x,(arriba_y - 70) },ObjectID::WALL };//arriba inclinado
	Wall3 = { { derecha_x,50,50,derecha_y },ObjectID::WALL };//derecha recto
	Wall4 = { { 20,50,izquierda_x,izquierda_y },ObjectID::WALL };//izquierda recto
	timer = { { 20,700,tiempo,20 },ObjectID::TIMER };//barra de tiempo
	nivel = 1;
	//initial y incremental son valores del XML
	alimentosPorObt = initial + incremental * nivel;
}

NormalScene::~NormalScene(void) {
}

void NormalScene::ReadXML() {


	string input_xml;
	string line;
	ifstream in("niveles.xml");

	// read file into input_xml
	while (getline(in, line))
		input_xml += line;

	vector<char> xml_copy(input_xml.begin(), input_xml.end());
	xml_copy.push_back('\0');


	xml_document<> doc;

	doc.parse<parse_declaration_node | parse_no_data_nodes>(&xml_copy[0]);



	xml_node<>* cur_node = doc.first_node("variables");



	cur_node = cur_node->first_node("easy");
	//va al normal
	cur_node = cur_node->next_sibling();
	
	//va hacia el primer atributo de easy, arriba_x
	cur_node = cur_node->first_node();
	string content = cur_node->value(); // if the node doesn't exist, this line will crash
	arriba_x = atoi(content.c_str());

	//va hacia arriba_y
	cur_node = cur_node->next_sibling();
	content = cur_node->value(); // if the node doesn't exist, this line will crash
	arriba_y = atoi(content.c_str());

	//va hacia  derecha_x
	cur_node = cur_node->next_sibling();
	content = cur_node->value(); // if the node doesn't exist, this line will crash
	derecha_x = atoi(content.c_str());

	//va hacia  derecha_y
	cur_node = cur_node->next_sibling();
	content = cur_node->value(); // if the node doesn't exist, this line will crash
	derecha_y = atoi(content.c_str());

	//va hacia abajo_x
	cur_node = cur_node->next_sibling();
	content = cur_node->value(); // if the node doesn't exist, this line will crash
	abajo_x = atoi(content.c_str());

	//va hacia abajo_y
	cur_node = cur_node->next_sibling();
	content = cur_node->value(); // if the node doesn't exist, this line will crash
	abajo_y = atoi(content.c_str());

	//va hacia izquierda_x
	cur_node = cur_node->next_sibling();
	content = cur_node->value(); // if the node doesn't exist, this line will crash
	izquierda_x = atoi(content.c_str());

	//va hacia izquierda_y
	cur_node = cur_node->next_sibling();
	content = cur_node->value(); // if the node doesn't exist, this line will crash
	izquierda_y = atoi(content.c_str());

	//va hacia time
	cur_node = cur_node->next_sibling();
	content = cur_node->value(); // if the node doesn't exist, this line will crash
	time = atoi(content.c_str());

	//va hacia speed
	cur_node = cur_node->next_sibling();
	content = cur_node->value(); // if the node doesn't exist, this line will crash
	speed = atoi(content.c_str());

	//va hacia initial
	cur_node = cur_node->next_sibling();
	content = cur_node->value(); // if the node doesn't exist, this line will crash
	initial = atoi(content.c_str());

	//va hacia incremental
	cur_node = cur_node->next_sibling();
	content = cur_node->value(); // if the node doesn't exist, this line will crash
	incremental = atoi(content.c_str());
}

void NormalScene::OnEntry(void) {
	snaki.lifes = 3; //inicializar vidas de la vida
	snaki.alimentosObt = 0;
	snaki.init_list(); //inicializar la lista de las posiciones del cuerpo de la serpiente
	appled.FoodSpawn();
	sizeChekpoint = 3;
	
	while (snaki.segments.size() > sizeChekpoint) {
		snaki.segments.pop_back();
	}

	while ((appled.position_x == snaki.head.x || (appled.position_x < snaki.head.x + 15 && appled.position_x > snaki.head.x - 15))
		|| (appled.position_y == snaki.head.y || (appled.position_y < snaki.head.y + 15 && appled.position_y > snaki.head.y - 15))) {
		appled.FoodSpawn();
	}
	//speed sacada del XML
	TM.n = speed;//para controlar el tiempo y a su vez la velocidad de la serpiente
	tiempomax = time;
	tiempo = tiempomax;
}

void NormalScene::OnExit(void) {
}

void NormalScene::Update(void) {

	snaki.getKey();//detecta los controles
	snaki.v = 30 + (playerd.score / 1000);//inicia la velocidad
	snaki.move();//activa la funcion de movimiento

	snake::COORD dead; //inicializa las cordenadas de una variable auxiliar para la muerte de la serpiente
	dead.x = 590; dead.y = 390; //  ^

	if ((arriba_x > snaki.head.x && 20<snaki.head.x) && (arriba_y>snaki.head.y && 30 < snaki.head.y)) {//collison pared arriba

		snaki.head.x = dead.x;//cambia las cordenadas de la cabeza al morir
		snaki.head.y = dead.y;
		snaki.lifes--; //resta el numero de vidas restantes
		while (snaki.segments.size() > sizeChekpoint) {
			snaki.segments.pop_back();
		}
	}
	if ((izquierda_x > snaki.head.x && 0<snaki.head.x) && (izquierda_y>snaki.head.y && 50 < snaki.head.y)) {//colision pared izquierda
		snaki.lifes--;
		snaki.head.x = dead.x;
		snaki.head.y = dead.y;
		while (snaki.segments.size() > sizeChekpoint) {
			snaki.segments.pop_back();
		}

	}
	if ((derecha_x > snaki.head.x && 920<snaki.head.x) && (derecha_y>snaki.head.y && 50 < snaki.head.y)) {//collision pared derecha
		snaki.lifes--;
		snaki.head.x = dead.x;
		snaki.head.y = dead.y;
		while (snaki.segments.size() > sizeChekpoint) {
			snaki.segments.pop_back();
		}
	}
	if ((abajo_x > snaki.head.x && 20<snaki.head.x) && (abajo_y>snaki.head.y && 650 < snaki.head.y)) {//collision pared abajo
		snaki.lifes--;
		snaki.head.x = dead.x;
		snaki.head.y = dead.y;
		while (snaki.segments.size() > sizeChekpoint) {
			snaki.segments.pop_back();
		}
	}
	if (snaki.Collision(dead)) {
		snaki.lifes--;
		snaki.head.x = dead.x;
		snaki.head.y = dead.y;
		while (snaki.segments.size() > sizeChekpoint) {
			snaki.segments.pop_back();
		}
	}

	playerd.score++;//incrementa la puntuacion del jugador constantemente

	scores = playerd.score;

	if (snaki.lifes == 0) { //detecta si el jugador ya ha perdido
		scores = playerd.score;
		playerd.score = 0;
		SM.SetCurScene <GameOverScene>(); //acaba el juego 
	}

	if (appled.isCollision(snaki.head)) {
		snaki.alimentosObt++;
		snaki.segments.push_front(snaki.head);
		appled.FoodSpawn();
		while ((appled.position_x == snaki.head.x || (appled.position_x < snaki.head.x + 5 && appled.position_x > snaki.head.x - 5))
			&& (appled.position_y == snaki.head.y || (appled.position_y < snaki.head.y + 5 && appled.position_y > snaki.head.y - 5))) {
			appled.FoodSpawn();
		}
	}
	if (snaki.alimentosObt == alimentosPorObt) {
		GUI::DrawTextShaded<FontID::ARIAL>("Has completado el nivel!",
		{ W.GetWidth() >> 2, int(W.GetHeight()*.4f), 4, 3 },
		{ 190, 150, 150 }, { 0, 0, 0 });
		
		sizeChekpoint = snaki.segments.size();


		nivel++;//aumenta el nivel
		snaki.lifes = 3;//restaura las vidas
		playerd.score += 1000;//suma el score
		snaki.alimentosObt = 0;//restaura el valor para el nuevo nivel
		alimentosPorObt = 3 + 2 * nivel;//aumenta la lista de alimentos por obtener
		printf("Nivel %d\n", nivel);
		tiempo += 150;
	}

	if (tiempo <= 20) {
		snaki.lifes = 0;
	}
	tiempo--;//pasas el tiempo
	//le pasas el score al static score de las escenas de ranking

	
	timer = { { 20,700,tiempo/2,20 },ObjectID::TIMER };//barra de tiempo
}


void NormalScene::Draw(void) {
	m_background.Draw(); // Render background
	snake::COORD pos; //inicializa cordenadas 
	pos = snaki.segments.front(); //se guarda la primera posicion de la lista


	if (snaki.dir == 1) { //comprueba la direccion
		s_head = { { snaki.getint(pos.x),snaki.getint(pos.y),30,30 },ObjectID::SNAKE_HEAD_DOWN }; //pinta en la posicion del primer elemento de la lista y cambia el sprite dependiendo de su direccion



	}
	else if (snaki.dir == 0) {
		s_head = { { snaki.getint(pos.x),snaki.getint(pos.y), 30, 30 },ObjectID::SNAKE_HEAD_RIGHT };

	}
	else if (snaki.dir == 2) {
		s_head = { { snaki.getint(pos.x),snaki.getint(pos.y),30,30 },ObjectID::SNAKE_HEAD_LEFT };

	}
	else if (snaki.dir == 3) {
		s_head = { { snaki.getint(pos.x),snaki.getint(pos.y),30,30 },ObjectID::SNAKE_HEAD };

	}
	s_head.Draw(); //pinta la cabeza
	list<snake::COORD>::iterator posi;  //inicializa otro iterador
	posi = snaki.segments.begin(); //guarda el iterador de la primera posicion de la lista
	posi++; //incrementas al siguiente iterador de la lista

	while (posi != --snaki.segments.end()) { //mientras el iterador no apunte a la ultima posicion

		snaki.aux2 = *posi; //guardamos la posicion en una variable auxiliar



		if (snaki.dir == 1) {
			s_body = { { snaki.getint(snaki.aux2.x),snaki.getint(snaki.aux2.y),30,30 },ObjectID::SNAKE_BODY_DOWN }; //pintamos el sprite dependiendo de la direccion y la posicion de ese segmento

		}
		else if (snaki.dir == 0) {
			s_body = { { snaki.getint(snaki.aux2.x),snaki.getint(snaki.aux2.y), 30, 30 },ObjectID::SNAKE_BODY_RIGHT };


		}
		else if (snaki.dir == 2) {
			s_body = { { snaki.getint(snaki.aux2.x),snaki.getint(snaki.aux2.y),30,30 },ObjectID::SNAKE_BODY_LEFT };

		}
		else if (snaki.dir == 3) {
			s_body = { { snaki.getint(snaki.aux2.x),snaki.getint(snaki.aux2.y),30,30 },ObjectID::SNAKE_BODY };
		}

		posi++;//pasamos al siguiente iterador de la lista
		s_body.Draw();//pintamos este segmento del cuerpo por cada iteracion
	}

	snaki.aux2 = snaki.segments.back(); //al acabar de recorrrer el cuerpo recogemos la ultima posicion de la lista



	if (snaki.dir == 1) { //pintamos la cola dependiendo de su direccion en la coordenada final de la lista
		s_tail = { { snaki.getint(snaki.aux2.x),snaki.getint(snaki.aux2.y),30,30 },ObjectID::SNAKE_TAIL_DOWN };

	}
	else if (snaki.dir == 0) {
		s_tail = { { snaki.getint(snaki.aux2.x),snaki.getint(snaki.aux2.y), 30, 30 },ObjectID::SNAKE_TAIL_RIGHT };

	}
	else if (snaki.dir == 2) {
		s_tail = { { snaki.getint(snaki.aux2.x),snaki.getint(snaki.aux2.y),30,30 },ObjectID::SNAKE_TAIL_LEFT };

	}
	else if (snaki.dir == 3) {
		s_tail = { { snaki.getint(snaki.aux2.x),snaki.getint(snaki.aux2.y),30,30 },ObjectID::SNAKE_TAIL };
	}
	s_food = { { appled.position_x,appled.position_y,30,30 },ObjectID::FOOD };




	s_tail.Draw(); //pintamos la cola
	s_food.Draw(); //pintamos la comida
	Wall1.Draw(); //pintamos las paredes
	Wall2.Draw();
	Wall3.Draw();
	Wall4.Draw();
	timer.Draw();
}