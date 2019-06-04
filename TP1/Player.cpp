#include "pch.h"
#include "Player.h"
#include <stdio.h>
#include <iostream>

using namespace std;


Player::Player()
{
	_tx.loadFromFile("Images/jumper.png");
	_sprite.setTexture(_tx);
	_sprite.setOrigin(_tx.getSize().x / 2, 0);
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

	isGrounded = y >= floor;

	if (y > floor) {
		y = floor;
		colliding = false;
	}

	if (y < maxJump) {
		y = maxJump;
	}
}

FloatRect Player::getBounds() {
	return _sprite.getGlobalBounds();
}

Vector2f Player::getColliderPosition() {
	return Vector2f(_sprite.getPosition());
}

void Player::collide() {
	colliding = true;
}

bool Player::isColliding() {
	return colliding;
}