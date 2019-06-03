#include "pch.h"
#include "Player.h"
#include <stdio.h>
#include <iostream>

using namespace std;


Player::Player()
{
	_tx.loadFromFile("Images/jumper.png");
	_sprite.setTexture(_tx);
	_sprite.setOrigin(_tx.getSize().x / 2, _tx.getSize().y);
	x = 160;
	y = 525;
	faceLeft = true;
}


Player::~Player()
{
}

void Player::draw(RenderWindow * window) {
	window->draw(_sprite);
}

void Player::update() {
	updateMovement();

	if (velocityX > 0.0f && faceLeft)
	{
		_sprite.setScale(-1.f, 1.f);
		faceLeft = false;		
	}
	else if (velocityX < 0.0f && !faceLeft)
	{
		_sprite.setScale(1.f, 1.f);
		faceLeft = true;
	}

	_sprite.setPosition(x, y);

}

void Player::move(float velocity) {
	velocityX = velocity;
}

void Player::jump() {
	if (isGrounded) {
		isGrounded = false;
		velocityY = -15.0f;
	}
}

void Player::updateMovement() {

	if (!isGrounded)
	{
		velocityY += gravity;
	}
	
	velocityX += accelerationX;
	velocityY += accelerationY;

	x += velocityX;
	y += velocityY;

	isGrounded = y >= 525;

	if (y > 525) {
		y = 525;
	}
}

FloatRect Player::getBounds() {
	return _sprite.getGlobalBounds();
}