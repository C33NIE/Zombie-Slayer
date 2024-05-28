#pragma once
#include "stdafx.h"
#include "Samurai.h"
#include "Zombie.h"

class Game
{
private:
	sf::RenderWindow window;
	sf::Event gameEvent;
	sf::Texture worldBackgroundTexture;
	sf::Sprite worldBackground;

	//resources

	Samurai* player; //player variable
	Zombie* enemies; //Zombie variable


	void initwindow(); //window creation
	void initplayer(); // player creation
	void initworld();//background
	void initzombie(); //zombie creation

public:
	//functions

	Game();
	virtual ~Game();

	//start position
	bool touchGround = false;
	sf::Clock collisiontimer;

	//Functions
	void updateSam(); //Character changes 
	void updatezom();
	void updateCollision(); //collision with window 
	void update(); // update game all together
	void renderPlayer(); //character display
	void render(); //game display
	void renderWorldbackground(); // background display
	void renderZombie(); //Zombie display
	void combat();
	const sf::RenderWindow& getWindow() const;
};

