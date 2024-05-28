#include "stdafx.h"
#include "Zombie.h"

void Zombie::initvariables()
{
	this->animState = IDLES;
}

void Zombie::inittexture()
{
	if (!this->textureSheet.loadFromFile("Images/walk.png"))
	{
		std::cout << "ERROR::PLAYER::couldnt load player sheet!" << "\n";
	}
}

void Zombie::initsprite()
{
	this->zom.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(0, 0, 120, 102);
	this->zom.setTextureRect(this->currentFrame);
	this->zom.setScale(1.8f, 1.8f);
}

void Zombie::initanimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Zombie::initPhysics()
{
	this->maxv = 7.f;
	this->minv = 1.f;
	this->acceleration = 3.f;
	this->drag = 0.9f;
	this->gravity = 6.f;
	this->maxvY = 12.f;
	this->hp = 100;
}

Zombie::Zombie()
{
	this->initvariables();
	this->inittexture();
	this->initsprite();
	this->initanimations();
	this->initPhysics();
}

Zombie::~Zombie()
{
	
}

const bool& Zombie::getAnimationSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}

const sf::Vector2f Zombie::getPosition() const
{
	return this->zom.getPosition();
}


const sf::FloatRect Zombie::getGlobalBounds() const
{
	return this->zom.getGlobalBounds();
}


void Zombie::setPosition(const float x, const float y)
{
	this->zom.setPosition(x, y);
	if (isSpawned == false)
	{
		this->zom.setPosition(1500.f, 250.f);
		isSpawned = true;
	}
}

void Zombie::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Zombie::loseHp(const int value)
{
}

bool Zombie::rightgetcollision()
{
	return rightcollision = true;
}

bool Zombie::leftgetcollision()
{
	return rightcollision = false;
}

void Zombie::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Zombie::move(const float dir_x, const float dir_y)
{
	//Acceleration
	this->velocity.x += dir_x * this->acceleration;

	//Limit velocity
	if (std::abs(this->velocity.x) > this->maxv)
	{
		//in order to fix the flipping errors
		this->velocity.x = this->maxv * ((this->velocity.x <= 0.f) ? -1.f : 1.f);
	}

}

void Zombie::updatePhysics()
{
	//Gravity
	this->velocity.y += 1.0f * this->gravity;

	if (std::abs(this->velocity.y) > this->maxvY)
	{
		//limiting gravity
		this->velocity.y = this->maxvY * ((this->velocity.y < 0.f) ? 1.f : -1.f);
	}
	//Deceleration update
	this->velocity.x *= this->drag; //constant deceleration


	//Limit deceleration
	if (std::abs(this->velocity.y < this->minv))
		this->velocity.y = 0.f;

	this->zom.move(this->velocity);
}

void Zombie::updateMovement()
{
	if (rightcollision==true) //left movement
	{
		this->move(-.1f, 0.f);
		this->animState = MOVING_LEFTS;
	}
	else if (rightcollision==false) //Right movement
	{
		this->move(0.1f, 0.f);
		this->animState = MOVING_RIGHTS;
	}

}

void Zombie::updateAnimations()
{
	if (this->animState == PLAYER_ANIMATION_STATE::MOVING_RIGHTS)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || getAnimationSwitch())
		{
			this->currentFrame.top = 102.f;
			this->currentFrame.left += 96.f;
			if (this->currentFrame.left > 720.f)
				this->currentFrame.left = 0;


			this->animationTimer.restart();
			this->zom.setTextureRect(this->currentFrame);
		}
		this->zom.setScale(1.8f, 1.8f);
		this->zom.setOrigin(0.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATE::MOVING_LEFTS) //Character moves left animation is just flipping sprite
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || getAnimationSwitch())
		{
			this->currentFrame.top = 102.f;
			this->currentFrame.left += 96.f;
			if (this->currentFrame.left > 200.f)
				this->currentFrame.left = 0;


			this->animationTimer.restart();
			this->zom.setTextureRect(this->currentFrame);
		}

		this->zom.setScale(-1.8f, 1.8f);
		this->zom.setOrigin(this->zom.getGlobalBounds().width / 1.8f, 0.f); //fixes the issues of flipping sprite
	}
	else if (animState == ATTACKINGS)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.08f || getAnimationSwitch())
		{
			this->currentFrame.top = 204.f;
			this->currentFrame.left += 96.f;
			if (this->currentFrame.left >= 480.f)
				this->currentFrame.left = 0;


			this->animationTimer.restart();
			this->zom.setTextureRect(this->currentFrame);
		}
	}
	else
		this->animationTimer.restart();
}

int Zombie::isattacking()
{
	animState = ATTACKINGS; 

	return this->animState;
}

void Zombie::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
}

void Zombie::render(sf::RenderTarget& targets)
{
	targets.draw(this->zom);
	sf::CircleShape circ;


	/*origin checker*/
	//circ.setFillColor(sf::Color::White);
	//circ.setRadius(2.f);
	//circ.setPosition(this->zom.getPosition());

	//targets.draw(circ);
}