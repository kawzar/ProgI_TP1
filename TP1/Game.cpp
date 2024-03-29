#include "pch.h"
#include "Game.h"
#include <iostream>

using namespace std;


Game::Game()
{
	_player = new Player();

	InitWindow();
	InitArrays();
	InitClock();
	InitSound();
}


Game::~Game()
{
}

void Game::Loop()
{
	while (_window->isOpen())
	{
		if (!gameOver) {
			UpdateClock();
			EventHandling();
			InputHandling();
			Update();
			CheckCollisions();
			Draw();
			CheckWinCondition();
		}
		else {
			ShowGameOverScreen();
		}
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
		_jumpSound.play();
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
		}
	}
}

void Game::Update()
{
	_player->update();

	for (int i = 0; i < amountOfBlocks; i++) {
		platformArray[i]->update();
	}
}

void Game::CheckCollisions() {
	for (int i = 0; i < amountOfBlocks; i++) {
		if (!_player->isColliding()) {
			if (platformArray[i]->intersects(_player->getColliderPosition())) {
				_player->collide();

				if (platformArray[i]->getValue() == values[lastCorrectIndex]) {
					MarkBlockAsCorrect(platformArray[i]);
				}
				else if (!platformArray[i]->isAlreadyMarked()) {
					MarkBlockAsIncorrect();
				}

				isPlayerColliding = true;
			}
		}
	}
}

void Game::Draw()
{
	_window->clear();
	_window->draw(_background);
	_window->draw(_txtTime);

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
	
		xPos += 40;
		AddToArray(i);
		platformArray[i] = new Platform(Vector2f(xPos, 400), values[i]);
	}

	Quicksort(values, 0, amountOfBlocks - 1);

}

void Game::InitClock() {
	_time = sf::seconds(60.0f);
	int seconds = _time.asSeconds();

	if (!_font.loadFromFile("Less.otf"))
	{
		cout << "Couldn't load font";
	}

	_txtTime = Text(std::to_string(seconds), _font, 15);
	_txtTime.setFillColor(sf::Color::White);
	_txtTime.setPosition(15, 15);
}

void Game::InitSound()
{
	_jumpSb.loadFromFile("Sounds/smw_jump.wav");
	_correctSb.loadFromFile("Sounds/smw_coin.wav");
	_failSb.loadFromFile("Sounds/smw_stomp.wav");
	_clockSb.loadFromFile("Sounds/tick.wav");
	
	_jumpSound.setBuffer(_jumpSb);
	_correctSound.setBuffer(_correctSb);
	_failSound.setBuffer(_failSb);
	_clockSound.setBuffer(_clockSb);
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
	_correctSound.play();
}

void Game::MarkBlockAsIncorrect() {
	_time -= sf::seconds(10.0f);
	_failSound.play();
}


void Game::Quicksort(int arr[], int inf, int sup)
{
	int aux;
	int i = inf - 1;
	int j = sup;
	int flag = 1;
	int pivot = arr[sup];

	if (inf >= sup)
		return;

	while (flag)
	{
		while (arr[++i] < pivot);
		while (arr[--j] > pivot);
		if (i < j)
		{
			aux = arr[i];
			arr[i] = arr[j];
			arr[j] = aux;
		}
		else
			flag = 0;
	}

	aux = arr[i];
	arr[i] = arr[sup];
	arr[sup] = aux;

	Quicksort(arr, inf, i - 1);
	Quicksort(arr, i + 1, sup);
}

void Game::UpdateClock() {
	int previousSecond = _time.asSeconds();
	_time -= _clock.restart();

	int seconds = _time.asSeconds();
	_txtTime.setString(std::to_string(seconds));

	if (seconds != previousSecond) {
		_clockSound.play();
	}
}

void Game::ShowGameOverScreen() {
	if(playerWon){
		_txtGameOver = Text("You won! Your remaining time was: ", _font, 15);
		_txtGameOver.setFillColor(sf::Color::Green);
		_txtGameOver.setPosition(200, 250);

		_txtTime.setFillColor(sf::Color::Green);
		_txtTime.setPosition(200, 290);
		_window->draw(_txtTime);

	}
	else {
		_txtGameOver = Text("You Lost!", _font, 15);
		_txtGameOver.setFillColor(sf::Color::Red);
		_txtGameOver.setPosition(200, 250);
		_txtTime.setFillColor(Color::Black);
	}

	Event evt;
	while (_window->waitEvent(evt))
	{
		if (evt.type == Event::Closed) {
			_window->close();
		}

		_window->clear(Color::Black);
		_window->draw(_txtGameOver);
		_window->draw(_txtTime);
		_window->display();
	}
}

void Game::CheckWinCondition() {
	if (lastCorrectIndex == amountOfBlocks) {
		gameOver = true;
		playerWon = true;
	}

	if (_time <= sf::seconds(0.0f)) {
		gameOver = true;
		playerWon = false;
	}

}