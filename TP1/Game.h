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

private:
	RenderWindow *_window;
	Texture _txBackground;
	Sprite _background;
	Player* _player;
	Clock _clock;
	Time _time;
	Text _txtTime;
	Text _txtGameOver;
	Font _font;
	Platform* platformArray[10];

	int values[10];
	int lastCorrectIndex = 0;
	bool isPlayerColliding;
	bool gameOver;
	bool playerWon;

	const int amountOfBlocks = 10;

	void EventHandling();
	void Update();
	void Draw();
	void InitWindow();
	void InputHandling();
	void CheckCollisions();
	void InitArrays();
	void AddToArray(int index);
	void MarkBlockAsCorrect(Platform* platform);
	void MarkBlockAsIncorrect();
	void UpdateClock();
	void InitClock();
	void ShowGameOverScreen();
	void CheckWinCondition();
	void Quicksort(int arr[], int inf, int sup);
};

