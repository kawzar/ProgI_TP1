#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

using namespace sf;

class Game
{
public:
	Game();
	~Game();
	void Loop();

protected:
	RenderWindow *_window;
	Texture _txBackground;
	Sprite _background;
	Player* _player;

	void EventHandling();
	void Update();
	void Draw();
	void InitWindow();
	void InputHandling();
};

