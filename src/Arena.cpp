#include "Arena.h"


// Initialization
void Arena::initVariables()
{
	
}

void Arena::initBorder()
{
	this->border.setSize(sf::Vector2f(tileSize, tileSize));
	this->border.setFillColor(sf::Color(222, 8, 1));
}

void Arena::initTile()
{
	this->tile.setSize(sf::Vector2f(tileSize, tileSize));
	this->tile.setFillColor(sf::Color(0, 0, 0));
}

// Constructors and destructors
Arena::Arena(float arenaWidth, float arenaHeight)
	:arenaWidth(arenaWidth), arenaHeight(arenaHeight)
{
	this->initVariables();
	this->initBorder();
	this->initTile();
}

Arena::~Arena()
{

}


// Functions
void Arena::update(const float & dt)
{

}

void Arena::render(sf::RenderTarget * target)
{
	for (size_t i = 0; i < this->arenaWidth; i++)
	{
		for (size_t j = 0; j < this->arenaHeight; j++)
		{
			if (i == 0 || i == this->arenaWidth - 1 || j == 0 || j == this->arenaHeight - 1)
			{
				this->border.setPosition(i*tileSize, j*tileSize);
				target->draw(this->border);
			}
			else
			{
				this->tile.setPosition(i*tileSize, j*tileSize);
				target->draw(this->tile);
			}
		}
	}
}


/// Accessors
float Arena::getArenaWidth()
{
	return this->arenaWidth;
}

float Arena::getArenaHeight()
{
	return this->arenaHeight;
}
