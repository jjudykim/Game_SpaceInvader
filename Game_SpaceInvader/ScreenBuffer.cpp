#include "ScreenBuffer.h"
ScreenBuffer::ScreenBuffer()
{
	//initialize buffers
	for (int y = 0; y < SCR_HEIGHT; y++)
	{
		for (int x = 0; x < SCR_WIDTH; x++)
		{
			front_buffer[y][x] = 0;
			back_buffer[y][x] = 0;
		}
	}
	//커서를 안보이도록 설정
	CONSOLE_CURSOR_INFO cur_info;
	cur_info.dwSize = 1; //커서의 높이를 셀 높이의 1%로 설정
	cur_info.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cur_info);
}
void ScreenBuffer::render()
{
	//re-draw changed parts
	for (int y = 0; y < SCR_HEIGHT; y++)
	{
		for (int x = 0; x < SCR_WIDTH; x++)
		{
			if (x == 0 || y == 0 || x == 59 || y == 29 || y == 2)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ (short)x,
				(short)y });
				cout << back_buffer[y][x];
			}
			if (x >= loc.X && x <= loc.X + 4)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ (short)x,
				(short)y });
				cout << back_buffer[y][x];
			}
			if (y == 1 && x >= 15 && x <= 35)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ (short)x,
				(short)y });
				cout << back_buffer[y][x];
			}
			if (back_buffer[y][x] != front_buffer[y][x])
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COORD{ (short)x,
				(short)y });
				if (back_buffer[y][x] == 0)
					cout << ' ';
				else
					cout << back_buffer[y][x];
			}
		}
	}
	for (int y = 0; y < SCR_HEIGHT; y++)
	{
		for (int x = 0; x < SCR_WIDTH; x++) {
			front_buffer[y][x] = back_buffer[y][x];
			back_buffer[y][x] = 0;
		}
	}
}
void ScreenBuffer::playerLoc(COORD loc)
{
	this->loc = loc;
}
void ScreenBuffer::drawToBackBuffer(const int x, const int y, const char image)
{
	back_buffer[y][x] = image;
}
void ScreenBuffer::drawToBackBuffer(const int x, const int y, const string image)
{
	for (int index = 0; image[index] != 0; index++)
	{
		back_buffer[y][x + index] = image[index];
	}
}