#include "Snake.h"
#include "Arena.h"

const float speedAfterDeath = 375.f;

// Initialization
void Snake::initVariables(Arena &arena)
{
	this->xLimit = arena.getArenaWidth() * tileSize;
	this->yLimit = arena.getArenaHeight() * tileSize;

	this->size = 0;
	this->prevDir = -1;
	this->dir = Dir::UP;
	this->v = speedAfterDeath;

	this->lives = 3;
}

void Snake::initSegment()
{
	this->segment = new sf::CircleShape(tileSize / 1.0f);
	this->segment->setFillColor(sf::Color(87, 166, 74));
	this->segment->setOutlineColor(sf::Color(0, 0, 0));
	this->segment->setOutlineThickness(1);
}

void Snake::initBody()
{
	/// Start position
	this->s.push_back(SnakeSegment(12 * tileSize, 14 * tileSize));
	this->s.push_back(SnakeSegment(12 * tileSize, 15 * tileSize));
	this->s.push_back(SnakeSegment(12 * tileSize, 16 * tileSize));

	/// Start size
	this->size = this->s.size();

	/// Initialization settings of segments for direction = UP
	for (auto it = this->s.begin(); it != this->s.end(); ++it)
	{
		it->xC = it->x0; it->yC = it->y0;
		it->xD = it->x0; it->yD = it->y0;
		it->length = tileSize;
		it->vel = this->v;
	}
}


// Functions
/// Directions
void Snake::changeDir()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && this->dir != Dir::RIGHT)
		 this->dir = Dir::LEFT;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && this->dir != Dir::DOWN)
		this->dir = Dir::UP;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && this->dir != Dir::UP)
		this->dir = Dir::DOWN;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && this->dir != Dir::LEFT)
		this->dir = Dir::RIGHT;
}

bool Snake::checkChangeDir()
{
	if (this->dir != this->prevDir)
	{
		this->prevDir = this->dir;
		return true;
	}
	return false;
}


/// Gameplay
void Snake::reset()
{
	if (this->lives > 1)
	{
		this->lives--;
		this->s.clear();

		this->dir = Dir::UP;
		this->v = speedAfterDeath;
		this->initBody();

		this->sounds->playDamage();
	}
	else
	{
		this->lives = 0;
		this->v = 0;
	}
}


/// Mechanics
void Snake::interactionWithSegments()
{
	/// Setting head position
	sf::Vector2f
		headPos(this->s[0].xC + tileSize, this->s[0].yC + tileSize),
		segmentPos;

	for (auto it = this->s.begin() + 1; it != this->s.end(); ++it)
	{
		/// Setting segment position
		segmentPos.x = it->xC + tileSize;
		segmentPos.y = it->yC + tileSize;

		/// Condition for stop
		if (abs(headPos.x - segmentPos.x) < tileSize / 3.f &&
			abs(headPos.y - segmentPos.y) < tileSize / 3.f)
		{
			this->v = 0;
		}
	}
}

void Snake::border()
{
	if (this->s[0].yC < tileSize)
	{
		this->stopSnake();
	}
	else if (this->s[0].yC > this->yLimit - 3 * tileSize)
	{
		this->stopSnake();
	}
	else if (this->s[0].xC < tileSize)
	{
		this->stopSnake();
	}
	else if (this->s[0].xC > this->yLimit - 3 * tileSize)
	{
		this->stopSnake();
	}
}

void Snake::collision()
{
	/// For avoiding collision effect

	/// set center for head
	float x0Center = this->s[0].xC + tileSize / 2.f;
	float y0Center = this->s[0].yC + tileSize / 2.f;

	/// set center for next element
	float x1Center, y1Center;
	float delta;

	for (auto it = this->s.begin(); it != this->s.end(); ++it)
	{
		/// set center for next element
		x1Center = it->xC - tileSize / 2.f;
		y1Center = it->yC - tileSize / 2.f;

		/// delta
		delta = sqrt(pow(abs(x0Center - x1Center), 2) + pow(abs(y0Center - y1Center), 2));
		if (delta < (tileSize* sqrt(2) / 2.f))
		{
			/// stop segment
			it->vel -= 0.1*this->v;
		}
		else
		{
			it->vel = this->v;
		}
		/// setting new x0Center and y0Center for next iteration
		x0Center = x1Center;
		y0Center = y1Center;
	}
}


/// Move
void Snake::stopSnake()
{
	for (auto it = this->s.begin(); it != this->s.end(); ++it)
		it->vel = 0;
	this->v = 0;
}

void Snake::move2destination(const float& dt)
{
	/// If direction was changed
	if (this->checkChangeDir())
	{
		/// Updating x0 / y0
		for (auto it = s.begin(); it != s.end(); ++it)
		{
			it->x0 = it->xC; 
			it->y0 = it->yC;
		}
		/// Updating destinations and setting lengths
		this->s[0].length = tileSize;
		for (auto it = s.begin() + 1; it != s.end(); ++it)
		{
			it->xD = (it - 1)->xC;
			it->yD = (it - 1)->yC;
			it->length = sqrt(pow(abs(it->yC - it->yD), 2) + pow(abs(it->xC - it->xD), 2));
		}
		/// Direction for head for different directions
		if (this->dir == Dir::UP)
		{
			this->s[0].xD = this->s[0].xC;
			this->s[0].yD = this->s[0].yC - tileSize;
		}
		else if (this->dir == Dir::DOWN)
		{
			this->s[0].xD = this->s[0].xC;
			this->s[0].yD = this->s[0].yC + tileSize;
		}
		else if (this->dir == Dir::LEFT)
		{
			this->s[0].xD = this->s[0].xC - tileSize;
			this->s[0].yD = this->s[0].yC;
		}
		else if (this->dir == Dir::RIGHT)
		{
			this->s[0].xD = this->s[0].xC + tileSize;
			this->s[0].yD = this->s[0].yC;
		}
	}

	/// For head
	if (this->dir == Dir::UP)
	{
		this->s[0].yC -= (this->s[0].vel * dt);
		this->s[0].length -= (this->s[0].vel * dt);
		if (this->s[0].length < this->DELTA)
		{
			this->s[0].length = 0.f;
			this->s[0].yC = this->s[0].yD;
			this->s[0].y0 = this->s[0].yC;
		}
	}
	else if (this->dir == Dir::DOWN)
	{
		this->s[0].yC += (this->s[0].vel * dt);
		this->s[0].length -= (this->s[0].vel * dt);
		if (this->s[0].length < this->DELTA)
		{
			this->s[0].length = 0.f;
			this->s[0].yC = this->s[0].yD;
			this->s[0].y0 = this->s[0].yC;
		}
	}
	else if (this->dir == Dir::LEFT)
	{
		this->s[0].xC -= (this->s[0].vel * dt);
		this->s[0].length -= (this->s[0].vel * dt);
		if (this->s[0].length < this->DELTA)
		{
			this->s[0].length = 0.f;
			this->s[0].xC = this->s[0].xD;
			this->s[0].x0 = this->s[0].xC;
		}
	}
	else if (this->dir == Dir::RIGHT)
	{
		this->s[0].xC += (this->s[0].vel * dt);
		this->s[0].length -= (this->s[0].vel * dt);
		if (this->s[0].length < this->DELTA)
		{
			this->s[0].length = 0.f;
			this->s[0].xC = this->s[0].xD;
			this->s[0].x0 = this->s[0].xC;
		}
	}

	/// For other segments
	for (auto it = s.begin() + 1; it != s.end(); ++it)
	{
		if (it->yD < it->yC)	/// UP
		{
			it->yC -= it->vel*dt;
			it->length -= it->vel*dt;
			if (it->length < this->DELTA)
			{
				it->length = 0.f;
				it->yC = it->yD;
				it->y0 = it->yC;
			}
		}
		if (it->yD >it->yC)	/// DOWN
		{
			it->yC += it->vel*dt;
			it->length -= it->vel*dt;
			if (it->length < this->DELTA)
			{
				it->length = 0.f;
				it->yC = it->yD;
				it->y0 = it->yC;
			}
		}
		if (it->xD < it->xC)	/// LEFT
		{
			it->xC -= it->vel*dt;
			it->length -= it->vel*dt;
			if (it->length < this->DELTA)
			{
				it->length = 0.f;
				it->xC = it->xD;
				it->x0 = it->xC;
			}
		}
		if (it->xD > it->xC)	/// RIGHT
		{
			it->xC += it->vel*dt;
			it->length -= it->vel*dt;
			if (it->length < this->DELTA)
			{
				it->length = 0.f;
				it->xC = it->xD;
				it->x0 = it->xC;
			}
		}
	}
}

void Snake::moveSnake(const float & dt)
{
	/// If snake has not reached the destination
	if (this->s[0].xC != this->s[0].xD || this->s[0].yC != this->s[0].yD)
		this->move2destination(dt);

	/// If snake has reached the destination then set destinations
	if (this->s[0].xC == this->s[0].xD && this->s[0].yC == this->s[0].yD)
	{
		/// Head settings is a main settings, other segments will repeat all the settings of the head
		if (this->dir == Dir::UP)
		{
			this->s[0].yD -= tileSize;
			this->s[0].length = tileSize;
		}
		else if (this->dir == Dir::DOWN)
		{
			this->s[0].yD += tileSize;
			this->s[0].length = tileSize;
		}
		else if (this->dir == Dir::LEFT)
		{
			this->s[0].xD -= tileSize;
			this->s[0].length = tileSize;
		}
		else if (this->dir == Dir::RIGHT)
		{
			this->s[0].xD += tileSize;
			this->s[0].length = tileSize;
		}
		/// Segments. Setting destinations
		for (auto it = s.begin() + 1; it != s.end(); ++it)
		{
			it->yD = (it - 1)->yC;
			it->xD = (it - 1)->xC;
			it->length = sqrt(pow(abs(it->yC - it->yD), 2) + pow(abs(it->xC - it->xD), 2));
		}
	}

	/// Collision effect
	this->collision();

	/// Border effect
	this->border();
	
	/// Interaction with segments
	this->interactionWithSegments();
}


// Constructors and destructors
Snake::Snake(Arena &arena, Sounds &sounds)
	: sounds(&sounds)
{
	this->initVariables(arena);
	this->initSegment();
	this->initBody();
}

Snake::~Snake()
{
	delete this->segment;
}


// Functions
void Snake::update(const float & dt)
{
	this->changeDir();
	this->moveSnake(dt); 

	if (this->v == 0)
		this->reset();
}

void Snake::render(sf::RenderTarget * target)
{
	for (auto it = begin(this->s); it != end(this->s); ++it)
	{
		if (it == begin(this->s))
			this->segment->setFillColor(sf::Color::Yellow);
		else
			this->segment->setFillColor(sf::Color(87, 166, 74));

		this->segment->setPosition(it->xC, it->yC);
		target->draw(*this->segment);
	}
}


// Accessors
/// Getters
std::vector<SnakeSegment>& Snake::getSnakeSegments()
{
	return this->s;
}

int Snake::getLength()
{
	return this->size;
}

int Snake::getVelocity()
{
	return this->v;
}

int Snake::getLives()
{
	return this->lives;
}


/// Setters
void Snake::setAddVelocity(float deltaVel)
{
	for (auto &el : this->s)
	{
		el.vel += deltaVel;
	}
	this->v += deltaVel;
}

void Snake::setAddLength()
{
	this->size++;
	auto tale = this->s.end() - 1;

	/// Creating a new segment
	this->s.push_back(SnakeSegment(tale->xC, tale->yC));
	auto newtale = this->s.end() - 1;
	auto oldtale = this->s.end() - 2;
	/// Setting position of a new tale
	newtale->xC = oldtale->xC; newtale->yC = oldtale->yC;
	newtale->xD = oldtale->x0; newtale->yD = oldtale->y0;
	newtale->length = tileSize;
	newtale->vel = oldtale->vel;
}

