#include "Fruct.h"
#include "Snake.h"


// Functions
/// Mechanics
void Fruct::eatenByHead(Snake & snake)
{
	/// LeftUp, RightDown points of snake head
	auto head = snake.getSnakeSegments().begin();
	sf::Vector2f 
		sLU(head->xC, head->yC),
		sRD(head->xC + 2 * tileSize, head->yC + 2 * tileSize);
	/// LeftUp, RightUp, LeftDown, RightDown points of fruct
	sf::Vector2f
		fLU(this->posX, this->posY),
		fRU(this->posX + tileSize, this->posY),
		fLD(this->posX, this->posY + tileSize),
		fRD(this->posX + tileSize, this->posY + tileSize);

	/// If one of the fruct's points inside the head
	if (!this->isEaten)
	{
		if (fLU.x > sLU.x && fLU.x < sRD.x && fLU.y > sLU.y && fLU.y < sRD.y ||
			fRU.x > sLU.x && fRU.x < sRD.x && fRU.y > sLU.y && fRU.y < sRD.y ||
			fLD.x > sLU.x && fLD.x < sRD.x && fLD.y > sLU.y && fLD.y < sRD.y ||
			fRD.x > sLU.x && fRD.x < sRD.x && fRD.y > sLU.y && fRD.y < sRD.y)
		{
			/// Increasing score and speed and adding a new segment
			snake.setAddLength();
			snake.setAddVelocity(addSpeed);
			this->score += 20;
			this->isEaten = true;

			this->sound->playEat();
		}
	}
	/// Else respawn the fruct
	else
	{
		this->isEaten = this->spawn = false;
		this->initPosition(snake);
	}
}

/// Initialization
void Fruct::initVariables(Arena &arena)
{
	this->xMin = this->yMin = tileSize;
	this->xMax = arena.getArenaWidth() * tileSize - 3 * tileSize;
	this->yMax = arena.getArenaHeight() * tileSize - 3 * tileSize;

	this->score = this->inSegment = 0;
	this->isEaten = this->spawn = false;

	this->addSpeed = 20.0f;
}

void Fruct::initPosition(Snake & snake)
{
	srand(time(NULL));
	/// LeftUp, RightDown points
	sf::Vector2f LU, RD;

	/// Spawning fruct
	while (!this->spawn)
	{
		this->posX = rand() % (int)(this->xMax - this->xMin) + xMin;
		this->posY = rand() % (int)(this->yMax - this->yMin) + yMin;

		/// Checking for not on snake
		for (auto it = snake.getSnakeSegments().begin(); it != snake.getSnakeSegments().end(); ++it)
		{
			LU = sf::Vector2f(it->xC - tileSize * 5 , it->yC - tileSize * 5);
			RD = sf::Vector2f(it->xC + tileSize * 5, it->yC + tileSize * 5);

			if (!(this->posX > LU.x && this->posX < RD.x &&
				this->posY > LU.y && this->posY < RD.y))
				this->inSegment++;			
		}
		if (this->inSegment >= snake.getSnakeSegments().size() - 1)
		{
			this->spawn = true;
			this->inSegment = 0;
		}
	}
}

void Fruct::initFruct()
{
	this->fruct.setSize(sf::Vector2f(tileSize, tileSize));
	this->fruct.setFillColor(sf::Color(239, 88, 89));
	this->fruct.setOutlineColor(sf::Color(0, 0, 0));
	this->fruct.setOutlineThickness(1);
}


// Constructors and destructors
Fruct::Fruct(Arena &arena, Snake &snake, Sounds &sounds)
	: sound(&sounds)
{
	this->initVariables(arena);
	this->initPosition(snake);
	this->initFruct();
}

Fruct::~Fruct()
{

}


// Functions
void Fruct::update(Snake &snake, const float & dt)
{
	this->eatenByHead(snake);
}

void Fruct::render(sf::RenderTarget * target)
{
	this->fruct.setPosition(posX, posY);
	target->draw(this->fruct);
}


// Accessors
int Fruct::getScore()
{
	return this->score;
}
