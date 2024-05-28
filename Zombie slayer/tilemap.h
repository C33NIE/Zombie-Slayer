#pragma once
#include "Tile.h"

class tilemap
{
private:
	std::vector<std::vector<Tile*>> tiles;

public:
	tilemap();
	virtual ~tilemap();

	//Functions
	void addTile(unsigned x, unsigned y);
	void removeTile(unsigned x, unsigned y);

	void update();
	void render();
};

