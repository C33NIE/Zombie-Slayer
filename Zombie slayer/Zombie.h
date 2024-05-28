#pragma once

enum PLAYER_ANIMATION_STATE { IDLES = 0, MOVING_LEFTS, MOVING_RIGHTS, ATTACKINGS };

class Zombie
{
private:
	sf::Sprite zom;
	sf::Texture textureSheet;
	sf::Clock animationTimer;
	float positionx, positiony;
	int previousState;

	unsigned pointCount;
	int type;
	float speed;
	int hp;
	int hpMax;
	int damage;
	int points;

	bool rightcollision = false;

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

	//Character details
	void initvariables();
	void inittexture();
	void initsprite();
	void initanimations();
	void initPhysics();

public:
	Zombie();
	virtual ~Zombie();

	bool isalive = true;
	bool isSpawned = false;
	

	//Accesors
	const bool& getAnimationSwitch(); //BYPASSING TIMER 
	const sf::Vector2f getPosition() const;
	const sf::FloatRect getGlobalBounds() const;

	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;
	bool rightgetcollision();
	bool leftgetcollision();


	//Modifiers
	void setPosition(const float x, const float y);
	void resetVelocityY();
	void setHp(const int hp);
	void loseHp(const int value);

	//Functions
	void resetAnimationTimer();
	int isattacking();
	void move(const float dir_x, const float dir_y); //direction x and y
	void updatePhysics();
	void updateMovement();
	void updateAnimations();
	void updateAttack();
	void update();
	void render(sf::RenderTarget& targets);
};
