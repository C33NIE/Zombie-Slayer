#include "stdafx.h"
#include "Samurai.h"

void Samurai::initvariables()
{
	this->animState = IDLE;
}

void Samurai::inittexture()
{
	if (!this->textureSheet.loadFromFile("Images/samurai_spritesheet.png"))
	{
		std::cout << "ERROR::PLAYER::couldnt load player sheet!" << "\n";
	}
}

void Samurai::initsprite()
{
	this->sam.setTexture(this->textureSheet);
	this->currentFrame = sf::IntRect(30, 90, 97, 80);
	this->sam.setTextureRect(this->currentFrame);
	this->sam.setScale(2.5f, 2.5f);
}

void Samurai::initanimations()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Samurai::initPhysics()
{
	this->maxv = 7.f;
	this->minv = 1.f;
	this->acceleration = 3.f;
	this->drag = 0.9f;
	this->gravity = 6.f;
	this->maxvY = 12.f;
	this->isjumping = false;
}

Samurai::Samurai()
{
	this->initvariables();
	this->inittexture();
	this->initsprite();
	this->initanimations();
	this->initPhysics();
}

Samurai::~Samurai()
{
}

const bool& Samurai::getAnimationSwitch()
{
	bool anim_switch = this->animationSwitch;

	if (this->animationSwitch)
		this->animationSwitch = false;

	return anim_switch;
}

const sf::Vector2f Samurai::getPosition() const
{
	return this->sam.getPosition();
}

const sf::FloatRect Samurai::getGlobalBounds() const
{
	return this->sam.getGlobalBounds();
}

const int& Samurai::getHp() const
{
	return this->hp;
}

void Samurai::setPosition(const float x, const float y)
{
	this->sam.setPosition(x, y);
}

void Samurai::resetVelocityY()
{
	this->velocity.y = 0.f;
}

void Samurai::resetAnimationTimer()
{
	this->animationTimer.restart();
	this->animationSwitch = true;
}

void Samurai::move(const float dir_x, const float dir_y)
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

void Samurai::updatePhysics()
{
	//Gravity
	this->velocity.y += 1.0f * this->gravity;

	if (std::abs(this->velocity.y) > this->maxvY)
	{
		//set Y speed to 
		this->velocity.y = this->maxvY * ((this->velocity.y < 0.f) ? 1.f : -1.f);
	}
	//Deceleration update
	this->velocity.x *= this->drag; //constant deceleration


	//Limit deceleration
	if (std::abs(this->velocity.y < this->minv))
		this->velocity.y = 0.f;

	if (sam.getPosition().y == 360) //is player on ground check.
		isjumping = false;

		this->sam.move(this->velocity);
}

void Samurai::updateMovement()
{
	this->animState = PLAYER_ANIMATION_STATES::IDLE;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //left movement
	{
		this->move(-1.f,0.f);
		this->animState = MOVING_LEFT;
		previousState = MOVING_LEFT;
		isattacking = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Right movement
	{
		this->move(1.f, 0.f);
		this->animState = MOVING_RIGHT;
		previousState = MOVING_RIGHT;
		isattacking = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) //Attack animation
	{
		this->animState = ATTACKING;
		isattacking = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isjumping==false) //Up movement
	{
		isjumping = true;
		isattacking = false;
		if (previousState == MOVING_RIGHT) // jump right
		{
			this->sam.move(100.f, -250.f);
			this->animState = JUMPING;
		}
		else if (previousState == MOVING_LEFT) //jump left
		{
			this->sam.move(-100.f, -250.f);
			this->animState = JUMPING;
		}

	}
	else
	{
		this->animState = IDLE;
		isattacking = false;
	}
	
}

void Samurai::updateAnimations()
{
	if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.2f || getAnimationSwitch())
		{
			this->currentFrame.top = 75.f; //cuts the sprite sheet
			this->currentFrame.left += 97.f; //flips the current frame throughout the sprite sheet
			if (this->currentFrame.left >= 97.f) // until the end of the animation
				this->currentFrame.left = 0;


			this->animationTimer.restart();
			this->sam.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_RIGHT)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || getAnimationSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 95.f;
			if (this->currentFrame.left > 200.f)
				this->currentFrame.left = 0;


			this->animationTimer.restart();
			this->sam.setTextureRect(this->currentFrame);
		}
		this->sam.setScale(2.5f, 2.5f);
		this->sam.setOrigin(0.f, 0.f);
	}
	else if (this->animState == PLAYER_ANIMATION_STATES::MOVING_LEFT) //Character moves left animation is just flipping sprite
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.1f || getAnimationSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 95.f;
			if (this->currentFrame.left > 200.f)
				this->currentFrame.left = 0;


			this->animationTimer.restart();
			this->sam.setTextureRect(this->currentFrame);
		}

		this->sam.setScale(-2.5f, 2.5f);
		this->sam.setOrigin(this->sam.getGlobalBounds().width / 2.5f, 0.f); //fixes the issues of flipping sprite
	}
	else if (this->animState == ATTACKING)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.08f || getAnimationSwitch())
		{
			this->currentFrame.top = 75.f;
			this->currentFrame.left += 97.f;
			if (this->currentFrame.left >= 200.f)
				this->currentFrame.left = 0;


			this->animationTimer.restart();
			this->sam.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == JUMPING)
	{
		if (this->animationTimer.getElapsedTime().asSeconds() >= 0.3f || getAnimationSwitch())
		{
			this->currentFrame.top = 0.f;
			this->currentFrame.left = 95.f;


			this->animationTimer.restart();
			this->sam.setTextureRect(this->currentFrame);
		}
	}
	else
		this->animationTimer.restart();
}

void Samurai::update()
{
	this->updateMovement();
	this->updateAnimations();
	this->updatePhysics();
}

void Samurai::render(sf::RenderTarget& target)
{
	target.draw(this->sam);
	sf::CircleShape circ;


	/*origin checker*/
	//circ.setFillColor(sf::Color::White);
	//circ.setRadius(2.f);
	//circ.setPosition(this->sam.getPosition());

	//target.draw(circ);
}
