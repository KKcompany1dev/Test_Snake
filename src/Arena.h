#ifndef ARENA_H
#define ARENA_H

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <time.h>
#include <math.h>
#include <iostream>
#include <vector>

// Window settings
const int tileSize = 25;
const float windowWidth = tileSize * 32, windowHeight = tileSize * 24;

// Directions
enum Dir { LEFT = 1, RIGHT, UP, DOWN };


class Arena
{
private:
	// Variables
	/// Arena settings
	sf::RectangleShape border;
	sf::RectangleShape tile;
	float arenaWidth, arenaHeight;

	// Initialization
	void initVariables();
	void initBorder();
	void initTile();
public:
	// Constructors and destructors
	Arena(float arenaWidth, float arenaHeight);
	virtual ~Arena();
	
	// Functions
	void update(const float& dt);
	void render(sf::RenderTarget* target);

	/// Accessors
	float getArenaWidth();
	float getArenaHeight();
};

#endif // !ARENA_H
