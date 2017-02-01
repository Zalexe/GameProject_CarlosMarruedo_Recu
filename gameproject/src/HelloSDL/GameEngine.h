#pragma once
#include "System.h"

#pragma region GAME_SCENES
#include "MenuScene.h"
#include "DifficultyScene.h"
#include "EasyScene.h"
#include "HardScene.h"
#include "NormalScene.h"
#include "GameOverScene.h"
#include "RankingScene.h"

#include "RankingScene.h"

#pragma endregion TODO

//! Initializes game needs and controls the game loop
namespace GameEngine {
	//! Loads main resources such as game images and fonts
	void LoadMedia(void) {
		R.LoadFont<FontID::ARIAL>("fnt/arial.ttf", 40);
		R.LoadTexture<ObjectID::CELL_EMPTY>("empty.png");
		R.LoadTexture<ObjectID::SNAKE_HEAD>("head.png");
		R.LoadTexture<ObjectID::SNAKE_HEAD_RIGHT>("head_right.png");
		R.LoadTexture<ObjectID::SNAKE_HEAD_LEFT>("head_left.png");
		R.LoadTexture<ObjectID::SNAKE_HEAD_DOWN>("head_down.png");
		R.LoadTexture<ObjectID::SNAKE_BODY>("body.png");
		R.LoadTexture<ObjectID::SNAKE_BODY_LEFT>("body_left.png");
		R.LoadTexture<ObjectID::SNAKE_BODY_RIGHT>("body_right.png");
		R.LoadTexture<ObjectID::SNAKE_BODY_DOWN>("body_down.png");
		R.LoadTexture<ObjectID::SNAKE_TAIL>("tail.png");
		R.LoadTexture<ObjectID::SNAKE_TAIL_LEFT>("tail_left.png");
		R.LoadTexture<ObjectID::SNAKE_TAIL_RIGHT>("tail_right.png");
		R.LoadTexture<ObjectID::SNAKE_TAIL_DOWN>("tail_down.png");
		R.LoadTexture<ObjectID::FOOD>("food.png");
		R.LoadTexture<ObjectID::BG_00>("bg.jpg");
		R.LoadTexture<ObjectID::WALL>("wall_rock.jpg");
		R.LoadTexture<ObjectID::GO>("Game_Over.jpg");
		R.LoadTexture<ObjectID::SCORE>("bg_score.jpg");
		R.LoadTexture<ObjectID::TIMER>("timer.jpg");
	}
	//! Adds the game scenes into the Scene Manager and decides which is the first screen
	void AddScenes(void) {
		SM.AddScene<MenuScene>();
		SM.AddScene<DifficultyScene>();
		SM.AddScene<HardScene>();
		SM.AddScene<EasyScene>();
		SM.AddScene<NormalScene>();
		SM.AddScene<GameOverScene>();
		SM.AddScene<RankingScene>();
		SM.SetCurScene<MenuScene>();
	}
	/**
	* Runs the game specifying the window's name and dimensions
	* @tparam screenWidth Determines the window's width
	* @tparam screenHeight Determines the window's height
	* @param name Determines the window's title
	*/
	template<int screenWidth, int screenHeight>
	void Run(std::string &&name) {
		Window::Instance(std::move(name), screenWidth, screenHeight); // Initialize window Singleton instance for the first time
		LoadMedia(); // Loads the resource assets
		AddScenes(); // Loads the scenes
		bool m_isRunning{ true }; // Decides if the game loop is running
		Scene *&m_curScene(SM.GetCurScene()); // Defines a reference to a pointer that points to the current scene pointer (mindblown)
		while (!IM.HasQuit() && m_isRunning) { // Checks while game's still playable
#pragma region GAME_UPDATE
			TM.Update([&] {
				switch (m_curScene->GetState()) { // Check for the state of the screen
				case SceneState::RUNNING:	IM.Update(); m_curScene->Update(); break; // Updates the InputManager and the current scene
				case SceneState::EXIT:	m_isRunning = false; break; // Triggers an end of the game looping
				case SceneState::PAUSE: default:;
				}});
#pragma endregion
#pragma region GAME_DRAW
			if (m_curScene->CheckState<SceneState::RUNNING>()) { // If screen object exists and its state is running
				R.Clear();	// Clear the screen buffer
				m_curScene->Draw(); // Call the draw method of the scene
				R.Render();	// Update the screen buffer with all sprites that were pushed
			}
#pragma endregion
		}
	}
}