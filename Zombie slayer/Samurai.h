#pragma once

enum PLAYER_ANIMATION_STATES { IDLE = 0, MOVING_LEFT, MOVING_RIGHT, JUMPING, FALLING,ATTACKING };

class Samurai
{
private:
	sf::Sprite sam;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	float positionx, positiony;
	int previousState;

	int hp;
	int hpMax;

	//Animation
	short animState;
	sf::IntRect currentFrame;
	bool animationSwitch;

	//Physics
	sf::Vector2f velocity;
	float maxv;
	float minv;
	float acceleration;
	float drag;
	float gravity;
	float maxvY;
	bool isjumping;

	//Character details
	void initvariables();
	void inittexture();
	void initsprite();
	void initanimations();
	void initPhysics();

public:
	Samurai();
	virtual ~Samurai();

	bool isattacking = false;
	bool facedir;

	//Accesors
	const bool& getAnimationSwitch(); //BYPASSING TIMER 
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();
	void setHp(const int hp);
	void loseHp(const int value);

	//Functions
	const bool canAttack();
	void resetAnimationTimer();
	void move(const float dir_x, const float dir_y); //direction x and y
	void updatePhysics();
	void updateMovement();
	void updateAnimations();
	void updateAttack();
	void update();
	void render(sf::RenderTarget& target);
};

