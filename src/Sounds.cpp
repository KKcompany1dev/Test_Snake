#include "Sounds.h"


void Sounds::initVariables()
{
	this->isStop = false;
	this->offsetStop = 0;
	this->musicPitch = 1.5f;
}

// Initialization
void Sounds::initMusic()
{
	if (!this->music.openFromFile("Audio/bg-music.wav"))
	{
		throw "Error! ::Sounds:: could not open Audio/bg-music.wav";
	}
	/// Settings
	this->music.setPitch(this->musicPitch);
	this->music.setPlayingOffset(sf::seconds(0.f));
	this->music.setVolume(20.f);
	this->music.setLoop(true);
}

void Sounds::initEatSound()
{
	if (!this->eatBuf.loadFromFile("Audio/eat.wav"))
	{
		throw "Error! ::Sounds:: could not open Audio/eat.wav";
	}
	/// Settings
	this->eatSound.setBuffer(this->eatBuf);
	this->eatSound.setVolume(50.f);
}

void Sounds::initDmgSound()
{
	if (!this->dmgBuf.loadFromFile("Audio/damage.wav"))
	{
		throw "Error! ::Sounds:: could not open Audio/damage.wav";
	}
	/// Settings
	this->dmgSound.setBuffer(this->dmgBuf);
	this->dmgSound.setVolume(50.f);
}


// Constructors and destructors
Sounds::Sounds()
{
	this->initVariables();
	this->initMusic();
	this->initEatSound();
	this->initDmgSound();
}

Sounds::~Sounds()
{

}


// Functions
/// Music
void Sounds::playMusic()
{
	this->music.play();
}

void Sounds::stopMusic(const float &dt)
{
	if (this->offsetStop < 3.f && !this->isStop)
	{
		this->musicPitch -= 0.001f;
		this->music.setPitch(this->musicPitch);
		this->offsetStop += dt;
	}
	else if (this->isStop)
	{
		this->music.stop();
	}
	else
	{
		this->isStop = true;
	}
}


/// Eat
void Sounds::playEat()
{
	this->eatSound.play();
}


/// Damage
void Sounds::playDamage()
{
	this->dmgSound.play();
}
