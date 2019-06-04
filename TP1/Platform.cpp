#include "pch.h"
#include "Platform.h"
#include <iostream>;

using namespace std;


Platform::Platform(Vector2f position, int value)
{
	_tx.loadFromFile("Images/bloque_pared.png");
	_sprite.setTexture(_tx);
	_sprite.setOrigin(_tx.getSize().x / 2, _tx.getSize().y);

	x = position.x;
	y = position.y;
	_value = value;

	if (!font.loadFromFile("Less.otf"))
	{
		cout << "Couldn't load font";
	}

	_text = Text(std::to_string(_value), font, 24);
	_text.setFillColor(sf::Color::Yellow);
	_text.setOrigin(_sprite.getOrigin());
}


Platform::~Platform()
{
}

void Platform::draw(RenderWindow * window) {
	window->draw(_sprite);
	window->draw(_text);
}

void Platform::update() {
	_sprite.setPosition(x, y);
	_text.setPosition(x, y);
}

bool Platform::intersects(FloatRect rect) {
	return _sprite.getGlobalBounds().intersects(rect);
}

bool Platform::intersects(Vector2f point) {
	return _sprite.getGlobalBounds().contains(point);
}

int Platform::getValue() {
	return _value;
}