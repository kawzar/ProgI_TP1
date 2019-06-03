#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "imageManager.h"
#include <list>
#include "Platform.h"

using namespace sf;
using namespace std;

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
	imageManager* img_mgr;
	list<Platform*> platforms;
	list<Platform*>::iterator it;

	void EventHandling();
	void Update();
	void Draw();
	void InitWindow();
	void InputHandling();
	void CheckCollisions();
};

