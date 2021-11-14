#include"GameHandler.h"
GameHandler::GameHandler()
{
	scoreNum = 0;
	moveCount = 0;
	BeforePressed = false;
	Pressed = false;
}

void GameHandler::initGameField()
{
	gameField = new char[feildWidth * feildHeigth];
	for (int x = 0; x < feildWidth; x++)
	{
		for (int y = 0; y < feildHeigth; y++)
		{
			if (x == 0)
			{
				if (y == 0) gameField[y * feildWidth + x] = 1;
				else if (y == feildHeigth - 1) gameField[y * feildWidth + x] = 3;
				else gameField[y * feildWidth + x] = 5;
			}
			else if (x == feildWidth - 1)
			{
				if (y == 0) gameField[y * feildWidth + x] = 2;
				else if (y == feildHeigth - 1) gameField[y * feildWidth + x] = 4;
				else gameField[y * feildWidth + x] = 5;
			}
			else if (y == 2) gameField[y * feildWidth + x] = 6;
			else
			{
				if (y == 0 || y == feildHeigth - 1) gameField[y * feildWidth + x] = 6;
				else gameField[y * feildWidth + x] = 0;
			}
		}
	}
}

void GameHandler::initEnemy(vector<GameObject>& enemy)
{
	COORD Ctemp = { 17, 5 };
	int count = 0;
	for (int i = 0; i < 8; i++)
	{
		GameObject temp("[XOX]", Ctemp);
		enemy.push_back(temp);
		if (count == 3)
		{
			Ctemp = { 15, 7 };
		}
		Ctemp.X += 8;
		count++;
	}
}

void GameHandler::gameTiming()
{
	Sleep(10);
	moveCount++;
}

COORD GameHandler::moveEnemy(int i, vector<GameObject>& enemy)
{
	COORD temp = enemy.at(i).getLoc();
	if (moveCount < 13) temp.X--;
	else if (moveCount == 13)
	{
		temp.Y++;
		temp.X++;
	}
	else if (moveCount < 25) temp.X++;
	else if (moveCount == 25) temp.Y++;
	return temp;
}

COORD GameHandler::movePlayer(GameObject& player, vector<GameObject>& bullets)
{
	COORD temp = player.getLoc();
	if (GetAsyncKeyState(VK_LEFT) & (1 << 15))
	{
		if (1 < temp.X) temp.X--;
	}
	if (GetAsyncKeyState(VK_RIGHT) & (1 << 15))
	{
		if (temp.X < 59 - player.getImage().length()) temp.X++;
	}
	if (GetAsyncKeyState(VK_UP) & (1 << 15))
	{
		if (3 < temp.Y) temp.Y--;
	}
	if (GetAsyncKeyState(VK_DOWN) & (1 << 15))
	{
		if (temp.Y < 28) temp.Y++;
	}
	if (GetAsyncKeyState(VK_SPACE))
	{
		Pressed = true;
		if (BeforePressed == false)
		{
			GameObject temp("!", { player.getLoc().X + 2, player.getLoc().Y - 1 });
			bullets.push_back(temp);
		}
	}
	BeforePressed = Pressed;
	Pressed = false;
	return temp;
}

COORD GameHandler::moveBullets(int i, vector<GameObject>& bullets)
{
	COORD temp = bullets.at(i).getLoc(); if (temp.Y > 2) temp.Y--;
	return temp;
}

void GameHandler::crashCheck(vector<GameObject>& enemy, vector<GameObject>& bullets)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		for (int j = 0; j < enemy.size(); j++)
		{
			if (bullets.at(i).getLoc().Y == enemy.at(j).getLoc().Y)
			{
				if (enemy.at(j).getLoc().X <= bullets.at(i).getLoc().X &&
					bullets.at(i).getLoc().X <= enemy.at(j).getLoc().X + 4)
				{
					bullets.erase(bullets.begin() + i);
					enemy.erase(enemy.begin() + j);
					scoreNum++;
					break;
				}
			}
		}
	}
}

void GameHandler::controlPlay(GameObject& player, vector<GameObject>& enemy, vector<GameObject>& bullets)
{
	player.setLoc(movePlayer(player, bullets));
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets.at(i).setLoc(moveBullets(i, bullets));
		if (bullets.at(i).getLoc().Y == 2) bullets.erase(bullets.begin() + i);
	}
	for (int i = 0; i < enemy.size(); i++)
	{
		enemy.at(i).setLoc(moveEnemy(i, enemy));
		if (enemy.at(i).getLoc().Y == 28) gameOver(player, enemy, bullets);
	}
	crashCheck(enemy, bullets);
	if (moveCount == 26) moveCount = 0;
	if (scoreNum == 8) gameOver(player, enemy, bullets);
}

void GameHandler::gameOver(GameObject& player, vector<GameObject>& enemy, vector<GameObject>& bullets)
{
	char retry;
	system("cls");
	if (scoreNum == 8) cout << "YOU WIN!!" << endl << endl;
	else cout << "YOU LOOSE!!" << endl << endl;
	cout << "Score: " << scoreNum << endl << endl;
	cout << "Play Agian? (y/n) : ";
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	cin >> retry; if (retry == 'y' || retry == 'Y')
	{
		player.setLoc({ 26, 26 });
		enemy.clear();
		bullets.clear();
		initEnemy(enemy);
		scoreNum = 0;
		moveCount = 0;
	}
	else if (retry == 'n' || retry == 'N') exit(0);
}

void GameHandler::drawAll(GameObject& player, vector<GameObject>& enemy, vector<GameObject>& bullets)
{
	system("cls");
	for (int x = 0; x < feildWidth; x++)
	{
		for (int y = 0; y < feildHeigth; y++)
		{
			screenBuffer.drawToBackBuffer(x, y, gameField[y * feildWidth + x]);
		}
	}
	screenBuffer.playerLoc(player.getLoc());
	screenBuffer.drawToBackBuffer(player.getLoc().X, player.getLoc().Y, player.getImage());
	for (auto i : bullets)
	{
		screenBuffer.drawToBackBuffer(i.getLoc().X, i.getLoc().Y, i.getImage());
	}
	for (auto i : enemy)
	{
		screenBuffer.drawToBackBuffer(i.getLoc().X, i.getLoc().Y, i.getImage());
	}
	char scoreText[20];
	sprintf_s(scoreText, "SCORE: %8d", scoreNum);
	screenBuffer.drawToBackBuffer(15, 1, scoreText);
	screenBuffer.render();
}