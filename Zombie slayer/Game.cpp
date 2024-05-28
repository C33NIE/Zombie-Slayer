#include "stdafx.h"
#include "Game.h"




void Game::initwindow()
{
	this->window.create(sf::VideoMode(1900, 560), "Zombie Slayer", sf::Style::Close | sf::Style::Titlebar); //create new window
	this->window.setFramerateLimit(60);
}


	//Player initialising
	void Game::initplayer()
	{
		this->player = new Samurai();
	}

	//Zombie initialising
	void Game::initzombie()
	{
		this->enemies = new Zombie();
	}

	//World initialisig
	void Game::initworld()
	{
		if (!this->worldBackgroundTexture.loadFromFile("Images/forest.bmp"))
		{
			std::cout << "ERROR::GAME::COULD_NOT_SHOW_MAP" << "\n";
		}

		this->worldBackground.setTexture(this->worldBackgroundTexture);
	}

	//constructor
	Game::Game()
	{
		this->initwindow();
		this->initplayer();
		this->initzombie();
		this->initworld();
	}

	//destructor
	Game::~Game()
	{
		delete this->player;

	}

	//updating events for samurai
	void Game::updateSam()
	{
		this->player->update();
	}

	//updating events for zombie
	void Game::updatezom()
	{
		if (enemies->isalive == true)
		{
			this->enemies->update();
		}
	}

	//updating world collision
	void Game::updateCollision()
	{
		//collision with the bottom
		if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
		{
			this->player->resetVelocityY(); //set Y velocity to 0
			this->player->setPosition(this->player->getPosition().x,
				this->window.getSize().y - this->player->getGlobalBounds().height);
		}

		//collision with the bottom
		if (this->enemies->getPosition().y + this->enemies->getGlobalBounds().height > this->window.getSize().y)
		{
			this->enemies->resetVelocityY(); //set Y velocity to 0
			this->enemies->setPosition(this->enemies->getPosition().x,
				this->window.getSize().y - this->enemies->getGlobalBounds().height);
		}

		//Left world collision
		if (this->player->getGlobalBounds().left < 0.f)
		{
			this->player->setPosition(0.f, this->player->getGlobalBounds().top);
		}
		//Right world collison
		else if (this->player->getGlobalBounds().left + this->player->getGlobalBounds().width >= this->window.getSize().x)
		{
			this->player->setPosition(this->window.getSize().x - this->player->getGlobalBounds().width, this->player->getGlobalBounds().top);
		}

		//Left world collision zombie
		if (this->enemies->getGlobalBounds().left < 0.f)
		{
			this->enemies->setPosition(0.f, this->enemies->getGlobalBounds().top);
			this->enemies->leftgetcollision();
		}
		//Right world collison zombie
		else if (this->enemies->getGlobalBounds().left + this->enemies->getGlobalBounds().width >= this->window.getSize().x)
		{
			this->enemies->setPosition(this->window.getSize().x - this->enemies->getGlobalBounds().width, this->enemies->getGlobalBounds().top);
			this->enemies->rightgetcollision();
		}
	}

	//updating combat
	void Game::combat()
	{
		/*if players position colliding with enemies position and player attacking then delete the enemy (std::abs cuz i want the negative values to work aswell)*/

		if (player->isattacking == true && std::abs(player->getPosition().x) / std::abs(enemies->getPosition().x) > 0.92f && enemies->isalive == true)
		{
			std::cout << std::abs(player->getPosition().x) / std::abs(enemies->getPosition().x);
			enemies->isalive = false;
		}

		//if enemy collides with user then user dies.
		else if (std::abs(player->getPosition().x) / std::abs(enemies->getPosition().x) > 1.f && !(std::abs(player->getPosition().x) / std::abs(enemies->getPosition().x) > 1.05f) && enemies->isalive == true)
		{
			window.close();

			/*sf::Text text;
			sf::Font fonto;

			if (!fonto.loadFromFile("Images/fontinho.ttf")) {
				std::cout << "cant load font" << std::endl;
			}

			text.setFillColor(sf::Color::Red);
			text.setString("GAME OVER");
			text.setCharacterSize(70);
			text.setPosition(850, 300);

			window.draw(text);

			sf::Clock time;
			if (time.getElapsedTime().asSeconds() == 3.f)
			{
				window.close();
			}*/
		}

	}

	//updating the window
	void Game::update()
	{
		//polling window events
		while (this->window.pollEvent(this->gameEvent))
		{
			if (this->gameEvent.type == sf::Event::Closed) //pressing the X on the window closes game
			{
				this->window.close();
			}
			else if (this->gameEvent.type == sf::Event::KeyPressed && this->gameEvent.key.code == sf::Keyboard::Escape)
			{
				this->window.close();
			}

			if (
				this->gameEvent.type == sf::Event::KeyReleased &&
				(
					this->gameEvent.key.code == sf::Keyboard::A ||
					this->gameEvent.key.code == sf::Keyboard::D ||
					this->gameEvent.key.code == sf::Keyboard::Space ||
					this->gameEvent.key.code == sf::Keyboard::E ||
					this->gameEvent.key.code == sf::Keyboard::S
					)
				)
			{
				this->player->resetAnimationTimer();
			}


		}
		this->updateSam(); //updates sam in game

		if (enemies->isalive == true)
		{
			this->updatezom();//updates enemy in game
		}
		this->updateCollision();

		this->combat();
	}

	//rendering player sprite
	void Game::renderPlayer()
	{
		this->player->render(this->window);
	}

	//rendering zombie sprite
	void Game::renderZombie()
	{
		if (enemies->isalive == true)
		{
			this->enemies->render(this->window);
		}
	}

	//rendering world background
	void Game::renderWorldbackground()
	{
		this->window.draw(this->worldBackground);
	}

	//rendering the window
	void Game::render()
	{
		this->window.clear();

		//Render Game
		this->renderWorldbackground();

		if (enemies->isalive == true)
		{
			this->renderZombie();
		}
		else if (enemies->isalive == false)
		{
			enemies->setPosition(1800, 250);
			enemies->isalive = true;
		}
		this->renderPlayer();

		this->window.display();
	}

	//getting window
	const sf::RenderWindow& Game::getWindow() const
	{
		// TODO: insert return statement here
		return this->window;
	}
