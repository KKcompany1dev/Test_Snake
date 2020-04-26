#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Fruct.h"
#include "Score.h"
#include "Sounds.h"

class Game
{
private:
	// Variables
	/// Window
	sf::RenderWindow* window;
	sf::Event event;
	/// Time
	sf::Clock clock; float dt;
	/// Arena
	Arena* arena;
	/// Snake
	Snake* snake;
	/// Fruct
	Fruct *fruct;
	/// Score
	Score *score;
	/// Game over
	sf::RectangleShape gameOverRect;
	sf::Font font;
	sf::Text textGameOver;
	bool gameOver;
	
	// Sounds
	Sounds *sounds;

	// Initialization
	void initVariables();
	void initWindow();
	void initArena();
	void initSnake();
	void initFruct();
	void initScore();
	void initGameOver();
	void initSounds();

	// Functions
	/// Gameplay
	void isGameOver();
	/// System
	void updateEvent();
	void updateDt();
	void update();
	void render();
public:
	// Constructors and destructors
	Game();
	virtual ~Game();
	// Run
	void run();
};

#endif // !GAME_H
