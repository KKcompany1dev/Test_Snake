#ifndef SCORE_H
#define SCORE_H

#include "Snake.h"
#include "Fruct.h"

class Score
{
private:
	// Variables
	/// Score settings
	int score, length, vel, life;
	/// Text
	int charSize, xPos, yPos;
	sf::Font font;
	sf::Text textScore, textLength, textVel, textLife;
	/// Fruct data for counting score
	Fruct* fruct;
	/// Snake data for counting length
	Snake *snake;

	// Initialization
	void initVariables();
	void initText();

	// Functions
	void updateScore();
	void updateLength();
	void updateVelocity();
	void updateLife();
public:
	// Constructors and destructors
	Score(Snake& snake, Fruct& fruct);
	virtual ~Score();
	
	// Functions
	void update(const float& dt);
	void render(sf::RenderTarget *target);
};

#endif
