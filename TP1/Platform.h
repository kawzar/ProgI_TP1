#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Platform
{
public:
	Platform(Vector2f position);
	~Platform();

	void draw(RenderWindow * window);
	void update();

	bool intersects(FloatRect rect);

protected:
	Texture _tx;
	Sprite _sprite;

	float x = 0;
	float y = 0;
};

