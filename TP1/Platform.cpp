#include "pch.h"
#include "Platform.h"



Platform::Platform(Vector2f position)
{
	_tx.loadFromFile("Images/bloque_pared.png");
	_sprite.setTexture(_tx);
	_sprite.setOrigin(_tx.getSize().x / 2, _tx.getSize().y);

	x = position.x;
	y = position.y;
}


Platform::~Platform()
{
}

void Platform::draw(RenderWindow * window) {
	window->draw(_sprite);
}

void Platform::update() {
	_sprite.setPosition(x, y);

}

bool Platform::intersects(FloatRect rect) {
	return _sprite.getGlobalBounds().intersects(rect);
}