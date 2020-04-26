#ifndef SNAKE_H
#define SNAKE_H

#include "Arena.h"
#include "Sounds.h"


// Segment DATA
struct SnakeSegment
{
	SnakeSegment(float x0, float y0)
		: x0(x0), y0(y0) {}
	float x0, y0, xC, yC, xD, yD, length, vel;
};


// Snake data
class Snake
{
private:
	// Variables
	/// Snake settings
	unsigned int size;
	int lives;
	float v; /// velocity
	const float DELTA = 0.0001f;
	
	/// Limit x, limit y
	float xLimit, yLimit;

	/// Segment
	sf::CircleShape *segment;

	/// Snake (vector of segments)
	std::vector<SnakeSegment> s;
	int dir, prevDir;

	/// Sound
	Sounds *sounds;

	// Initialization
	void initVariables(Arena &arena);
	void initSegment();
	void initBody();

	// Functions
	/// Directions
	void changeDir();
	bool checkChangeDir();

	/// Gameplay
	void reset();

	/// Mechanics
	void interactionWithSegments();
	void border();
	void collision();
	
	/// Move
	void stopSnake();
	void move2destination(const float& dt);
	void moveSnake(const float& dt);
public:
	// Constructors and destructors
	Snake(Arena &arena, Sounds &sounds);
	virtual ~Snake();

	// Functions
	void update(const float& dt);
	void render(sf::RenderTarget *target);

	// Accessors
	/// Getters
	std::vector<SnakeSegment>& getSnakeSegments();
	int getLength();
	int getVelocity();
	int getLives();
	/// Setters
	void setAddVelocity(float deltaVel);
	void setAddLength();
};

#endif // !SNAKE_H

