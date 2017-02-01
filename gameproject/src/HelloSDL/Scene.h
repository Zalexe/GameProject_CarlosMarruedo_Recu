
#pragma once

// Enum state fot each Scene in the Game
enum class SceneState {
	EMPTY,		// Default empty state
	RUNNING,	// State of updating the current screen
	EXIT,		// State of leaving the current game
	PAUSE		// State of leaving scene stand by
};

// Scene class that serves as part of the Model
class Scene {
	friend class SceneManager;
public:
	explicit Scene() = default;
	virtual ~Scene() = default;
	int score;
	// funcion para cuando se entra en la escena
	virtual void OnEntry(void) = 0;
	// funcion para cuando se deja la escena
	virtual void OnExit(void) = 0;
	// update de la escena (mientras esta en ejecucion)
	virtual void Update(void) = 0;
	// funcion para pintar la escena mientras esta ejecutandose
	virtual void Draw(void) = 0;
	// modos de usar los estados
	//cambiar el estado
	template <SceneState state> inline void SetState(void) { currentState = state; };
	//funcion q devuelve el estado de un escenarion
	inline SceneState GetState(void) const { return currentState; };
	//funcion que comprueba/compara con que estado esta
	template <SceneState state> inline bool CheckState(void) const { return currentState == state; };
protected:
	//el estado de la escena
	SceneState currentState{ SceneState::EMPTY }; // Current state of the scene, NONE by default
};