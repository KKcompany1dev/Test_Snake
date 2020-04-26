#include "Game.h"

// Initialization
void Game::initVariables()
{
	this->gameOver = false;
	this->dt = 0.f;
}

void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(windowWidth*1.5, windowHeight*1.5), "Snake_v2.0");
}

void Game::initArena()
{
	this->arena = new Arena(36.f, 36.f);
}

void Game::initSnake()
{
	this->snake = new Snake(*this->arena, *this->sounds);
}

void Game::initFruct()
{
	this->fruct = new Fruct(*this->arena, *this->snake, *this->sounds);
}

void Game::initScore()
{
	this->score = new Score(*this->snake,*this->fruct);
}

void Game::initGameOver()
{
	/// Block
	this->gameOverRect.setPosition(windowWidth / 2.f, windowHeight / 2.f);
	this->gameOverRect.setSize(sf::Vector2f(400.f, 180.f));
	this->gameOverRect.setFillColor(sf::Color(0, 11, 99));
	this->gameOverRect.setOutlineColor(sf::Color(252, 6, 2));
	this->gameOverRect.setOutlineThickness(10);

	/// Text
	if (!this->font.loadFromFile("Fonts/19104.ttf"))
	{
		throw "Error! ::Score::initText could not load fonts from file";
	}
	else
	{
		this->textGameOver.setPosition(windowWidth / 2.f + 30, windowHeight / 2.f + 50);
		this->textGameOver.setFont(this->font);
		this->textGameOver.setString("Game over");
		this->textGameOver.setCharacterSize(64);
		this->textGameOver.setFillColor(sf::Color(252, 6, 2));
	}
}

void Game::initSounds()
{
	this->sounds = new Sounds;
	this->sounds->playMusic();
}


// Functions
/// Gameplay
void Game::isGameOver()
{
	this->gameOver = true;
}

/// System
void Game::updateEvent()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::updateDt()
{
	this->dt = clock.restart().asSeconds();
}

void Game::update()
{
	this->updateEvent();
	this->updateDt();

	this->arena->update(this->dt);
	this->snake->update(this->dt);
	this->fruct->update(*this->snake, this->dt);
	this->score->update(this->dt);

	/// Game over
	if (!this->snake->getLives() && !this->gameOver) this->isGameOver();
}

void Game::render()
{
	this->window->clear(sf::Color(43, 36, 42));

	///////////////////
	/// Drawing section
	this->arena->render(this->window);
	this->fruct->render(this->window);
	this->snake->render(this->window);
	this->score->render(this->window);

	/// GameOver
	if (!this->snake->getLives()) {
		this->window->draw(this->gameOverRect);
		this->window->draw(this->textGameOver);
		this->sounds->stopMusic(this->dt);
	}
	///////////////////
	this->window->display();
}


// Constructors and destructors
Game::Game()
{
	this->initSounds();

	this->initVariables();
	this->initWindow();
	this->initArena();
	this->initSnake();
	this->initFruct();
	this->initScore();
	this->initGameOver();
}

Game::~Game()
{
	delete this->window;
	delete this->arena;
	delete this->snake;
	delete this->fruct;
	delete this->score;

	delete this->sounds;
}


// Run
void Game::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}

