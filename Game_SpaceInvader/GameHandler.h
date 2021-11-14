#pragma once
#include"GameObject.h"
#include"ScreenBuffer.h"

class GameHandler
{
private:
	const int feildWidth = 60;
	const int feildHeigth = 30;
	char* gameField = nullptr;
	int scoreNum;
	int moveCount;
	bool BeforePressed;
	bool Pressed;
	ScreenBuffer screenBuffer;
public:
	GameHandler();
	void initGameField();
	void initEnemy(vector<GameObject>& enemy);
	void gameTiming();
	COORD movePlayer(GameObject& player, vector<GameObject>& bullets);
	COORD moveEnemy(int i, vector<GameObject>& enemy);
	COORD moveBullets(int i, vector <GameObject>& bullets);
	void controlPlay(GameObject& player, vector<GameObject>& enemy, vector<GameObject>& bullets);
	void crashCheck(vector<GameObject>& enemy, vector<GameObject>& bullets);
	void drawAll(GameObject& player, vector<GameObject>& enemy, vector<GameObject>& bullets);
	void gameOver(GameObject& player, vector<GameObject>& enemy, vector<GameObject>& bullets);
};