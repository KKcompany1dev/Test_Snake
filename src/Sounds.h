#ifndef SOUNDS_H
#define SOUNDS_H

#include <SFML/Audio.hpp>
#include <iostream>

class Sounds
{
private:
	// Variables
	/// Music
	bool isStop;
	float offsetStop, musicPitch;
	sf::Music music;
	/// Jump
	sf::SoundBuffer eatBuf;
	sf::Sound eatSound;
	/// Damage
	sf::SoundBuffer dmgBuf;
	sf::Sound dmgSound;

	// Initialization
	void initVariables();
	void initMusic();
	void initEatSound();
	void initDmgSound();
public:
	// Constructors and destructors
	Sounds();
	virtual ~Sounds();
	// Functions
	/// Music
	void playMusic();
	void stopMusic(const float &dt);
	/// Eat
	void playEat();
	/// Damage
	void playDamage();
};

#endif