#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Platform
{
public:
	Platform(Vector2f position, int value);
	~Platform();

	void draw(RenderWindow * window);
	void update();
	bool intersects(FloatRect rect);
	int getValue();

protected:
	Texture _tx;
	Sprite _sprite;
	Text _text;
	Font font;

	float x = 0;
	float y = 0;
	int _value;
};

