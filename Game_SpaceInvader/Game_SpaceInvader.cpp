#include"GameObject.h"
#include"GameHandler.h"
int main()
{
	GameObject player(">-0-<", { 26, 26 });
	vector<GameObject> enemy;
	vector<GameObject> bullets;
	GameHandler gameHandler;
	bool isGameOver = false;
	gameHandler.initGameField();
	gameHandler.initEnemy(enemy);
	while (true)
	{
		gameHandler.gameTiming();
		gameHandler.controlPlay(player, enemy, bullets);
		gameHandler.drawAll(player, enemy, bullets);
	}
}