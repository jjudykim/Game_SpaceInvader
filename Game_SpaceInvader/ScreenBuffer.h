#pragma once

#include<iostream>
#include<Windows.h>
#include<string>
using namespace std;
#define SCR_WIDTH 60
#define SCR_HEIGHT 30
class ScreenBuffer
{
private:
	char front_buffer[SCR_HEIGHT][SCR_WIDTH]; //���� ȭ�鿡 �������� ��
	char back_buffer[SCR_HEIGHT][SCR_WIDTH]; //������ ������ ������ ������ ��
	COORD loc = { 0,0 };
public:
	ScreenBuffer();
	void playerLoc(COORD loc);
	void render();
	void drawToBackBuffer(const int x, const int y, const char image);
	void drawToBackBuffer(const int x, const int y, const string image);
};