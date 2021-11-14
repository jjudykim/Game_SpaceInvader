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
	char front_buffer[SCR_HEIGHT][SCR_WIDTH]; //현재 화면에 보여지는 곳
	char back_buffer[SCR_HEIGHT][SCR_WIDTH]; //앞으로 보여질 내용을 저장할 곳
	COORD loc = { 0,0 };
public:
	ScreenBuffer();
	void playerLoc(COORD loc);
	void render();
	void drawToBackBuffer(const int x, const int y, const char image);
	void drawToBackBuffer(const int x, const int y, const string image);
};