#include "pch.h"
#include "Game.h"
#include <iostream>

using namespace std;


Game::Game()
{
	_player = new Player();

	InitWindow();
	InitArrays();
}


Game::~Game()
{
	for (it = platforms.begin(); it != platforms.end(); it++) {
		delete *it;
	}
}

void Game::Loop()
{
	while (_window->isOpen())
	{
		EventHandling();
		InputHandling();
		Update();
		CheckCollisions();
		Draw();
	}

}

void Game::InputHandling() 
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_player->move(-10.0f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_player->move(10.0f);
	} 
	else
	{
		_player->move(0.0f);
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
	_player->jump();
	}

}


void Game::EventHandling()
{
	Event evt;
	while (_window->pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::Closed:
			_window->close();
			break;
		case Event::MouseButtonPressed:
			if (evt.mouseButton.button == Mouse::Button::Left)
			{
			}
		}
	}
}

void Game::Update()
{
	if (lastCorrectIndex == amountOfBlocks) {
		cout << "Game finished";
	}

	_player->update();
	for (int i = 0; i < amountOfBlocks; i++) {
		platformArray[i]->update();
	}
}

void Game::CheckCollisions() {
	for (int i = 0; i < amountOfBlocks; i++) {
		if (platformArray[i]->intersects(_player->getColliderPosition())) {
			if (platformArray[i]->getValue() == values[lastCorrectIndex]) {
				MarkBlockAsCorrect(platformArray[i]);
			}
			else {
				MarkBlockAsIncorrect();
			}
		}
	}
}

void Game::Draw()
{
	_window->clear();
	_window->draw(_background);

	for (int i = 0; i < amountOfBlocks; i++) {

		platformArray[i]->draw(_window);
	}
	
	_player->draw(_window);
	
	_window->display();
}


void Game::InitWindow()
{
	_window = new RenderWindow(VideoMode(800, 600), "TP1");
	_window->setMouseCursorVisible(true);
	_window->setFramerateLimit(60);
	_txBackground.loadFromFile("Images/mundo_fondo.jpg");
	_background.setTexture(_txBackground);
}

void Game::InitArrays() {
	float xPos = 200;
	for (int i = 0; i < amountOfBlocks; i++) {
	
		xPos += 41;
		AddToArray(i);
		platformArray[i] = new Platform(Vector2f(xPos, 400), values[i]);
	}

	bubbleSort(values, amountOfBlocks);
}

void Game::AddToArray(int index) {
	int number = 1 + (std::rand() % (999 - 1 + 1));
	bool exists = false;

	for (int i = 0; i < index && !exists; i++) {
		exists = number == values[i];
	}

	if (!exists) {
		values[index] = number;
	}
	else {
		AddToArray(index);
	}
}

void Game::MarkBlockAsCorrect(Platform* platform) {
	platform->markAsCorrect();
	lastCorrectIndex++;
}

void Game::MarkBlockAsIncorrect() {
	cout << "incorrect" << endl;
}



void Game::swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void Game::bubbleSort(int arr[], int n)
{
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
			}
		}
	}
}