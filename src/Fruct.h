#ifndef FRUCT_H
#define FRUCT_H

#include "Arena.h"
#include "Snake.h"
#include "Sounds.h"

class Fruct
{
private:
	// Variables
	/// Settings
	float posX, posY, xMin, xMax, yMin, yMax, addSpeed;
	bool spawn;
	int inSegment, score;
	/// Fruct
	sf::RectangleShape fruct;
	bool isEaten;
	/// Sound
	Sounds *sound;


	// Functions
	/// Mechanics
	void eatenByHead(Snake &snake);

	/// Initialization
	void initVariables(Arena &arena);
	void initPosition(Snake &snake);
	void initFruct();
public:
	// Constructors and destructors
	Fruct(Arena &arena, Snake &snake, Sounds &sounds);
	virtual ~Fruct();

	// Functions
	void update(Snake& snake, const float& dt);
	void render(sf::RenderTarget *target);

	// Accessors
	int getScore();
};

#endif // !FRUCT_H
