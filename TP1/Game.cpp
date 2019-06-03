#include "pch.h"
#include "Game.h"


Game::Game()
{
	_player = new Player();

	InitWindow();
}


Game::~Game()
{
}

void Game::Loop()
{
	while (_window->isOpen())
	{
		EventHandling();
		InputHandling();
		Update();
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
	_player->update();
}

void Game::Draw()
{
	_window->clear();
	_window->draw(_background);
	_player->draw(_window);
	
	_window->display();
}


void Game::InitWindow()
{
	_window = new RenderWindow(VideoMode(900, 468), "TP1");
	_window->setMouseCursorVisible(true);
	_window->setFramerateLimit(60);
	_txBackground.loadFromFile("Images/background.png");
	_background.setTexture(_txBackground);
}
