#include "Score.h"


// Initialization
void Score::initVariables()
{
	this->life = this->snake->getLives();
	this->vel = this->snake->getVelocity();
	this->length = this->snake->getLength();
	this->score = 0;
	this->charSize = 32;
	this->xPos = 1.14 * windowWidth;
	this->yPos = 6;
}

void Score::initText()
{
	if (!this->font.loadFromFile("Fonts/19104.ttf"))
	{
		throw "Error! ::Score::initText could not load fonts from file";
	}
	else
	{
		/// Score
		this->textScore.setPosition(this->xPos, this->yPos);
		this->textScore.setFont(this->font);
		this->textScore.setString("Score: " + std::to_string(this->score));
		this->textScore.setCharacterSize(this->charSize);
		this->textScore.setFillColor(sf::Color(181, 241, 212));

		/// Length
		this->textLength.setPosition(this->xPos, this->yPos + this->charSize * 1.5f);
		this->textLength.setFont(this->font);
		this->textLength.setString("Length: " + std::to_string(this->length));
		this->textLength.setCharacterSize(this->charSize);
		this->textLength.setFillColor(sf::Color(181, 241, 212));

		/// Velocity
		this->textVel.setPosition(this->xPos, this->yPos + this->charSize * 3.f);
		this->textVel.setFont(this->font);
		this->textVel.setString("Velocity: " + std::to_string(this->vel));
		this->textVel.setCharacterSize(this->charSize);
		this->textVel.setFillColor(sf::Color(181, 241, 212));

		/// Life
		this->textLife.setPosition(this->xPos, this->yPos + this->charSize * 4.5f);
		this->textLife.setFont(this->font);
		this->textLife.setString("Life: " + std::to_string(this->life));
		this->textLife.setCharacterSize(this->charSize);
		this->textLife.setFillColor(sf::Color(181, 241, 212));
	}
}


// Functions
void Score::updateScore()
{
	this->score = this->fruct->getScore();
	this->textScore.setString("Score: " + std::to_string(this->score));
}

void Score::updateLength()
{
	this->length = this->snake->getLength();
	this->textLength.setString("Length: " + std::to_string(this->length));
}

void Score::updateVelocity()
{
	this->vel = this->snake->getVelocity();
	this->textVel.setString("Velocity: " + std::to_string(this->vel));
}

void Score::updateLife()
{
	this->life = this->snake->getLives();
	this->textLife.setString("Life: " + std::to_string(this->life));
}


// Constructors and destructors
Score::Score(Snake& snake, Fruct& fruct)
	: fruct(&fruct), snake(&snake)
{
	this->initVariables();
	this->initText();
}

Score::~Score()
{

}

void Score::update(const float & dt)
{
	this->updateScore();
	this->updateLength();
	this->updateVelocity();
	this->updateLife();
}

void Score::render(sf::RenderTarget * target)
{
	target->draw(this->textScore);
	target->draw(this->textLength);
	target->draw(this->textVel);
	target->draw(this->textLife);
}
