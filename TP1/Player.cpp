#include "pch.h"
#include "Player.h"
#include <stdio.h>
#include <iostream>

using namespace std;


Player::Player()
{
	_tx.loadFromFile("Images/cat.png");
	_sprite.setTexture(_tx);
	_sprite.setOrigin(_tx.getSize().x / 2, _tx.getSize().y);
	x = 160;
	y = 390;
	faceRight = true;
}


Player::~Player()
{
}

void Player::draw(RenderWindow * window) {
	window->draw(_sprite);
}

void Player::update() {
	updateMovement();

	if (velocityX > 0.0f && !faceRight)
	{
		_sprite.setScale(1.f, 1.f);
		faceRight = true;		
	}
	else if (velocityX < 0.0f && faceRight)
	{
		_sprite.setScale(-1.f, 1.f);
		faceRight = false;
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

	isGrounded = y >= 400;

	if (y > 400) {
		y = 400;
	}
}