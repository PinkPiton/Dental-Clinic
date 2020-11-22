#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <map>
#include <string>
#include "Win10.h"
#include "menu.h"
#include "List.h"
#include "Queue.h"
#include "Table.h"
#include <conio.h> 
//#include "MenuFunc.h"
using namespace std;
#define MAX_POLE_HIGH 42
#define MAX_POLE_WIDTH 91
#define MAX_LADDER_WIDTH 5
#define MAX_LADDER_HIGH 13
#define RND(min,max) (rand()%((max)-(min)+1)+(min))
#define MAX_HIGH 3
#define MAX_WIDTH 4
#define MAX_LENGTH 20
#define CONTINUE_ID 2
#define SAVE_ID 5
Menu menu;
const char pe[MAX_POLE_HIGH][MAX_POLE_WIDTH] = {
	"                                                                                         *",
	"                                                                                         *",
	"                                                                                         *",
	"                                                                                         *",
	"                                                                                         *",
	"                                                                                         *",
	"                                                                                         *",
	"     $     |==|                                                                          *",
	"WWWWWWWWWWW|==|WWWWWWWWWWWWWWWWWWWW                                                      *",
	"           |==|++++++++++++++++++++++++++++++++++                                        *",
	"           |==|                                                                          *",
	"           |==|                                                                          *",
	"           |==|                                                                          *",
	"           |==|                                                $                |==|     *",
	"           |==|                        |==|     WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|==|WWWWW*",
	"           |==|              WWWWWWWWWW|==|                                     |==|     *",
	"           |==|              WWWWWWWWWW|==|                                     |==|     *",
	"           |==|              WWWWWWWWWW|==|                                     |==|     *",
	"           |==|              WWWWWWWWWW|==|                                     |==|     *",
	" |==|      |==|              WWWWWWWWWW|==|                  |==|               |==|     *",
	"W|==|WWWWWWWWWW              WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|==|WWWWWWWWWWWWWWWWWWWWWWWW*",
	" |==|                                                        |==|                        *",
	" |==|                                                        |==|                        *",
	" |==|                                                        |==|                        *",
	" |==|                                                        |==|                        *",
	" |==|                                                        |==|                        *",
	" |==|             |==|                                       |==|                        *",
	"WWWWWWWWWWWWWWWWWW|==|WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW|==|                        *",
	"                  |==|+++++++++++++++++++++++++++++++++++++++|==|                        *",
	"                  |==|                                       |==|                        *",
	"                  |==|                                       |==|                        *",
	"                  |==|                                       |==|                        *",
	"                  |==|                                       |==|                        *",
	"      |==|   $    |==|                                       |==|        $           |==|*",
	"      |==|WWWWWWWWWWWWWW                                WWWWWWWWWWWWWWWWWWWWWWWWWWWWW|==|*",
	"      |==|                                                                           |==|*",
	"      |==|                                                                           |==|*",
	"      |==|                                                                           |==|*",
	"      |==|                                                                           |==|*",
	"      |==|                                     $                                     |==|*",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW*",
	"##########################################################################################"

};
typedef char** Pole;
bool isStart = true;
bool isPlay = false;
const char enemyImage[4][MAX_HIGH][MAX_WIDTH + 1] = {
	{
		"  # ",
		"  |-",
		"  |&",
	},
	{
		" #  ",
		"^|  ",
		"?|  ",
	},
	{
		"|#| ",
		"^|^ ",
		"?|& ",
	},
	{
		"?|&",
		"^|^ ",
		"|#| ",
	}
};
const char defImage[4][MAX_HIGH][MAX_WIDTH + 1] = {
	{
		"  @ ",
		"  |-",
		"  |_",
	},
	{
		" @  ",
		"-|  ",
		"_|  ",
	},
	{
		"|@| ",
		"-|- ",
		"_|_ ",
	},
	{
		"-|-",
		"_|_ ",
		"|@| ",
	}
};
const char Ladder[MAX_LADDER_WIDTH] = { "|==|" };
const char rope[MAX_LENGTH] = { "+++++++++++++++++++" };
//int Stairs::X = 0, Stairs::Y = 0;
class Human {
public:
	enum DIRECTION {
		RIGHT = 0,
		LEFT,//1
		UP,//2
		DOWN,//3
		MAX_DIR//4
	};
protected:
	int X, Y;
	int speed;
	char Image[4][MAX_HIGH][MAX_WIDTH + 1];
	bool isAlive;
	DIRECTION direct;
	static int XSize, YSize;
	static int XStart, YStart;
public:
	Human() :speed(), isAlive(true), direct(), Y(25), X(80) {
		//points = 0;
		SetDefaultImage();
		//X = rand() % ((XSize - MAX_WIDTH-2) - (MAX_WIDTH-2) + 1) + (MAX_WIDTH - 1);
		//Y = rand() % ((YSize - MAX_HIGH-2) - (MAX_HIGH-2) + 1) + (MAX_HIGH - 1);
	}
	virtual void SetDefaultImage() {
		for (int i = 0; i < sizeof(Image) / sizeof(*Image); i++) {
			for (int j = 0; j < sizeof(*Image) / sizeof(*Image[0]); j++) {
				strcpy(Image[i][j], defImage[i][j]);
			}
		}
	}
	virtual void setXY(int x, int y) { X = x; Y = y; }
	virtual void Collision(Pole&pole, int e = 0) { return; }
	virtual void Draw(Pole&pole, int xSize, int ySize) {
		for (int i = 0; i < MAX_HIGH; i++) {
			for (int j = 0; j < MAX_WIDTH; j++) {
				if (Image[direct][i][j] == '@') {
					//SetColor(0x1);
					Image[direct][i][j] = char(1);
				}
				//if (Image[direct][i][j] == '|') {
				//	//SetColor(0x1);
				//	Image[direct][i][j] = char(24);
				//}
				if (Image[direct][i][j] == '#') {
					//SetColor(0x1);
					Image[direct][i][j] = char(2);
				}
				if (Image[direct][i][j] == '^') {
					//SetColor(0x1);
					Image[direct][i][j] = char(207);
				}
				if (Image[direct][i][j] == '&') {
					//SetColor(0x1);
					Image[direct][i][j] = char(191);
				}//218
				if (Image[direct][i][j] == '?') {
					//SetColor(0x1);
					Image[direct][i][j] = char(218);
				}
				pole[Y + i][X + j] = Image[direct][i][j];
				if(pole[Y + i][X + j + 1]!=' '&&pole[Y + i][X + j + 1] != 'W'&&pole[Y + i][X + j + 1] != '*')
					pole[Y + i][X + j + 1] = ' ';
				pole[Y + i][X - 1] = ' ';
				pole[Y + i + 1][X + j] = ' ';
				pole[Y - 1][X + j] = ' ';
				//
				/*pole[Y + i][X + 1] = ' ';
				pole[Y + i - 1][X + j] = ' ';
				pole[Y + 1][X + j] = ' ';*/
				//
				//pole[Y + MAX_HIGH][X + MAX_WIDTH] = ' ';
				/*pole[Y - MAX_HIGH][X + MAX_WIDTH] = ' ';
				pole[Y + MAX_HIGH][X - MAX_WIDTH] = ' ';
				pole[Y - MAX_HIGH][X - MAX_WIDTH] = ' ';*/
			}
		}
	}
	//   virtual void setpoints(int p) {
	   //	 //points = 0;
	   //		points += p;
	   //}
	   //
	static void SetSizeXY(int x, int y) { XSize = x, YSize = y; }
	static void SetStartXY(int x, int y) { XStart = x, YStart = y; }
	virtual void setisAlive(bool iA) { isAlive = iA; }
	static int getXSize() { return XSize; }
	static int getYSize() { return YSize; }
	static int getXStart() { return XStart; }
	static int getYStart() { return YStart; }
	virtual bool getisAlive()const { return isAlive; }
	virtual int getlives() const { return 0; }
	virtual bool isPlayer() { return false; }
	virtual void Displasement(Pole&pole,Human*hm) {
		// логика противника
		DIRECTION dir = (DIRECTION)(hm->X % DIRECTION::MAX_DIR);
		//DIRECTION dir = (DIRECTION)(hm->Y % DIRECTION::MAX_DIR);
		//int dir = dir1 + dir2;
		switch (dir)
		{
		case DIRECTION::LEFT: X = StepToLeft(X,pole); direct = DIRECTION::LEFT; break;
		case DIRECTION::RIGHT: X = StepToRight(X,pole); direct = DIRECTION::RIGHT; break;
		case DIRECTION::UP: Y = StepToUp(Y, pole); direct = DIRECTION::UP; break;
		case DIRECTION::DOWN: Y = StepToDown(Y, pole);  direct = DIRECTION::DOWN; break;
		}
		if (pole[Y + MAX_HIGH][X] != '#'&&pole[Y + MAX_HIGH][X] != '='&&pole[Y + MAX_HIGH + 1][X + MAX_WIDTH] != 'W'&&pole[Y + MAX_HIGH + 1][X - MAX_WIDTH] != 'W'&&
			Y < YSize - MAX_HIGH - 2 && pole[Y - 1][X + 2] != char(205)
			&& pole[Y - 1][X + 1] != char(205) && pole[Y + 3][X + 1] != '|'&& pole[Y + 3][X + 2] != '|'
			&& pole[Y + 3][X + 1] != '='&& pole[Y + 3][X + 2] != '='&&pole[Y + 3][X + 1] != '|'&& pole[Y + 3][X + 2] != '|'
			&& pole[Y + 3][X + 1] != '='&& pole[Y + 3][X + 2] != '=') {
			if (pole[Y][X + 1] != '='&&pole[Y][X + 1] != '|'&&pole[Y][X + 2] != '='&&pole[Y][X + 2] != '|') {

				Y++;
			}
		}
		if (pole[Y - 1][X] == char(205)) {
			direct = DIRECTION::UP;
		}
	}
	//virtual void StepToLeft(int& x) { if(x>0) x--; }
	virtual int StepToLeft(int x, Pole&pole,int xWidth = 4) {
		if(pole[Y + MAX_HIGH][X - 1] != 'W')
			if (x > 2) return x - 1;
		return x;
	}
	virtual int StepToRight(int x, Pole&pole, int xWidth = 4) {
		if (pole[Y + MAX_HIGH][X+MAX_WIDTH] != 'W')
			if (x < XSize - xWidth - 2) return x + 1;
		return x;
	}
	virtual int StepToUp(int y, Pole&pole, int yWidth = 3) {
		for (int i = 0; i < MAX_HIGH; i++) {
			for (int j = 0; j < MAX_WIDTH; j++) {
				if (pole[Y + i][X + j] == '|' || pole[Y + i][X + j] == '=') {
					if (pole[Y + i][X + j + 1] == '=')
						if (y > 2) return y - 1;
					//&&pole[Stairs::getY() + i][Stairs::getX() + j + 1] == '='
				}
			}
		}
		return y;
	}
	virtual int StepToDown(int y, Pole&pole, int yWidth = 3) {
		for (int i = 0; i < MAX_HIGH; i++) {
			for (int j = 0; j < MAX_WIDTH; j++) {
				if (pole[Y - i + MAX_HIGH][X + j] == '|' || pole[Y - i + MAX_HIGH][X + j+1] == '=') {
					if (pole[Y - i + MAX_HIGH][X + j + 1] == '=') {
						if(pole[Y + MAX_HIGH+1][X+j] != 'W')
							if (y < YSize - yWidth - 2) return y + 1;
					}
						
					//&&pole[Stairs::getY() + i][Stairs::getX() + j + 1] == '='
				}
			}
		}
		return y;
	}
	virtual int getpoints() { return 1; };
	virtual void setpoints(int p) {}
	virtual void setlives(int l) {}
	virtual int getX() { return X; }
	virtual int getY() { return Y; }
};
int Human::XSize = 0, Human::YSize = 0;
int Human::XStart = 0, Human::YStart = 0;
//int Human::points = 0;
class Enemy :virtual public Human {
public:
	virtual void SetDefaultImage() {
		for (int i = 0; i < sizeof(Image) / sizeof(*Image); i++) {
			for (int j = 0; j < sizeof(*Image) / sizeof(*Image[0]); j++) {
				strcpy(Image[i][j], enemyImage[i][j]);
			}
		}
	}
	//virtual void setpoints(int p) {
	//	//points = 0;
	//	points += 0;
	//}
	virtual void Displasement(Pole&pole, Human*hm) {
		Human::Displasement(pole,hm);

	}
	virtual int getpoints() { return 1; }
	Enemy() :Human() {
		SetDefaultImage();
		/*	Image[0][0][2] = '#';
			Image[0][1][3] = '^';
			Image[0][2][3] = '&';

			Image[1][0][1] = '#';
			Image[1][1][0] = '^';
			Image[1][2][0] = '&';

			Image[2][0][1] = '#';
			Image[3][2][1] = '#';*/
	}
};
class Player :virtual public Human {
public:
	int lives;
	int points;
public:
	void set() {
		lives = 3;
		//	points=0;
			//speed = 0, isAlive = true, direct = RIGHT, Y = 10, X = 15;
			//SetDefaultImage();
	}
	Player() :lives(3), points(), Human() {
		setXY(70, 10);
		//setpoints(0);
	}
	virtual void setlives(int l) { lives = l; }
	virtual void setpoints(int p) {
		if (this->points < 0)
			this->points = 0;
		if (p)
			this->points += p;
		/*SetPos(80, 15);
		cout << Player::getpoints();*/
	}
	virtual int getpoints() { return this->points; }

	virtual void FrontDestruction(Pole&pole) {
		for (int j = 0; j < MAX_WIDTH; j++) {
			if (pole[Y + MAX_HIGH + 1][X + MAX_WIDTH + j] != ' ') {
				pole[Y + MAX_HIGH + 1][X + MAX_WIDTH + j] = ' ';
			}
		}
	}
	virtual void BackDestruction(Pole&pole) {
		for (int j = 0; j < MAX_WIDTH; j++) {
			if (pole[Y + MAX_HIGH + 1][X - MAX_WIDTH - j] != ' ') {
				pole[Y + MAX_HIGH + 1][X - MAX_WIDTH - j] = ' ';
			}
		}
	}
	virtual void Displasement(Pole&pole, Human*hm) {
		if (pole[Y + MAX_HIGH][X] != '#'&&pole[Y + MAX_HIGH][X] != '='&&pole[Y + MAX_HIGH+1][X+MAX_WIDTH] != 'W'&&pole[Y + MAX_HIGH + 1][X - MAX_WIDTH] != 'W'&&
			Y < YSize - MAX_HIGH - 2 && pole[Y - 1][X+2] != char(205)
			&& pole[Y - 1][X + 1] != char(205) && pole[Y + 3][X + 1] != '|'&& pole[Y + 3][X+2] != '|'
			&& pole[Y + 3][X + 1] != '='&& pole[Y+3][X + 2] != '='&&pole[Y + 3][X+1] != '|'&& pole[Y + 3][X + 2] != '|'
			&& pole[Y + 3][X+1] != '='&& pole[Y + 3][X + 2] != '=') {
			if (pole[Y][X + 1] != '='&&pole[Y][X + 1] != '|'&&pole[Y][X + 2] != '='&&pole[Y][X + 2] != '|') {
				Y++;
			}
		}
		if (_kbhit()) {
			int key = _getch();
			if (key == KEY::CURSOR1 || key == KEY::CURSOR2) {
				key = _getch();
			}
			while (_kbhit()) _getch();
			switch (key) {
			case KEY::LEFT:
				X = StepToLeft(X,pole);
				direct = DIRECTION::LEFT;
				break;
			case KEY::RIGHT:
				X = StepToRight(X,pole);
				direct = DIRECTION::RIGHT;
				break;
			case KEY::UP:
				Y = StepToUp(Y, pole);
				direct = DIRECTION::UP;
				break;
			case KEY::DOWN:
				Y = StepToDown(Y, pole);
				direct = DIRECTION::DOWN;
				break;
			case KEY::Z:
				FrontDestruction(pole);
				direct = DIRECTION::RIGHT; break;
			case KEY::X:
				BackDestruction(pole);
				direct = DIRECTION::LEFT; break;
			case KEY::ESC: {
				menu.Insert(CONTINUE_ID, "Continue", 0);
				menu.Insert(SAVE_ID, "Save game", 2);
				system("cls");
				isStart = false;
				break;
			}
			default:
				break;
			}
		}
		/*for (int i = 0; i < MAX_HIGH; i++) {
			for (int j = 0; j < MAX_WIDTH; j++) {

			}
		}*/
		//if ()Y--;
		if (pole[Y - 1][X] == char(205)) {
			direct = DIRECTION::UP;
		}
	}
	virtual void Collision(Pole&pole, int e = 0) {
		if (pole[Y][X + 2] != 'W'&&pole[Y][X + 2] != char(205) &&
			pole[Y][X + 2] == char(191) || pole[Y][X + 2] == char(218) || pole[Y][X + 2] == char(207)||
			pole[Y][X - 2] == char(191) || pole[Y][X -2] == char(218) || pole[Y][X -2] == char(207)||
			pole[Y][X + MAX_WIDTH] == char(191) || pole[Y][X + MAX_WIDTH] == char(218) || pole[Y][X + MAX_WIDTH] == char(207) ||
			pole[Y][X - MAX_WIDTH] == char(191) || pole[Y][X - MAX_WIDTH] == char(218) || pole[Y][X - MAX_WIDTH] == char(207)) {
			if (lives)
				lives--;
			isAlive = false;
		}
		/*if (pole[Y][X + MAX_WIDTH] != ' '&&pole[Y][X + MAX_WIDTH] != char(191) && pole[Y][X + MAX_WIDTH] != char(218) &&
			pole[Y][X + MAX_WIDTH] != char(205) &&pole[Y][X + MAX_WIDTH] != '$'&&pole[Y][X + MAX_WIDTH] != '*'&&pole[Y][X + MAX_WIDTH] != '+'&&
			pole[Y][X + MAX_WIDTH] != '='&&pole[Y][X + MAX_WIDTH] != 'W') {
			if (pole[Y + MAX_HIGH][X + MAX_WIDTH] != ' '&&pole[Y + MAX_HIGH][X + MAX_WIDTH] != char(218) && pole[Y + MAX_HIGH][X + MAX_WIDTH] != char(205) &&
				pole[Y + MAX_HIGH][X + MAX_WIDTH] != char(191) &&pole[Y + MAX_HIGH][X + MAX_WIDTH] != '$'&&pole[Y + MAX_HIGH][X + MAX_WIDTH] != '*'&&pole[Y + MAX_HIGH][X + 1] != '+'&&
				pole[Y + MAX_HIGH][X + MAX_WIDTH] != '='&&pole[Y + MAX_HIGH][X + MAX_WIDTH] != 'W') {

			}
		}*/

	}
	virtual int getlives()const { return lives; }
	virtual bool isPlayer() { return true; }
	virtual bool getisAlive()const { return isAlive; }
};

class Stairs {
private:
	int X, Y;
	char Image[MAX_LADDER_HIGH][MAX_LADDER_WIDTH];
	int high;
public:
	Stairs() :Y(),X(),high() {
		//X = rand() % ((70 - MAX_LADDER_WIDTH) - (MAX_LADDER_WIDTH)+1) + (MAX_LADDER_WIDTH);
		//Y = rand() % ((40 - MAX_LADDER_HIGH) - (MAX_LADDER_HIGH)+1) + (MAX_LADDER_HIGH);
		//high = RND(2, MAX_LADDER_HIGH);
		SetDefaultImage();
	}
	void SetDefaultImage() {
		for (int i = 0; i < high; i++) {
			for (int j = 0; j < MAX_LADDER_WIDTH; j++) {
				Image[i][j] = Ladder[j];
			}
		}
	}
	void Draw(Pole&pole) {
		for (int i = 0; i < high; i++) {
			for (int j = 0; j < MAX_LADDER_WIDTH - 1; j++) {
				pole[Y + i][X + j] = '=';
			}
		}
	}
	void setXY(int x, int y) { X = x; Y = y; }
	void sethigh(int h) { high = h; }
	int getY() { return Y; }
	int getX() { return X; }
};
//int q = 0;
class Points {
private:
	int X, Y;
	int points;
	bool isAlive;
public:
	Points() :isAlive(1), points(250),X(),Y() {
	//	X = rand() % ((MAX_POLE_WIDTH - MAX_LADDER_WIDTH) - (MAX_LADDER_WIDTH)+1) + (MAX_LADDER_WIDTH);
		//int re = RND(1, 36);
		//for (int i = 0; i < 100;i++) {
		//	switch (re)
		//	{
		//	case 6:	case 11:case 17:case 24:case 30:case 36:
		//		Y = re; break;
		//	default:
		//		re = RND(1, 36);
		//		break;
		//	}
		//}
	//	Y = RND();
		//Y = 36;
		//static int i = 0;
		//for (; i < MAX_POLE_HIGH; i++) {
		//	for (int j = 0; j < MAX_POLE_WIDTH; j++) {
		//		if (pe[i][j] == '$') {
		//			//pole[i][j] = '$';
		//			//pole[i][j] = ' ';
		//			Y = i-2;
		//			X = j; return;
		//		}
		//	}
		//}
	}

	void Draw(Pole&pole) {
		if (isAlive) {
			//Insert(pole);
			//pole[Y-1][X] = ' ';
			pole[Y][X] = '$';
			//if (pole[Y + 1][X] != '#'&&pole[Y+ 1][X] != 'W'&&Y < MAX_POLE_HIGH - 1 - 2) {
			//		//pole[Y][X] = '$';
			//		Y++;
			//}
			
		}
	}
	void SetXY(int x, int y) { X = x; Y = y; }
	//void Collision(Pole&pole,Player&pl) {
	void Collision(Pole&pole, Human * pl) {
		/*if (pole[Y][X - 1] == ' ' && pole[Y][X - 2] == '@') {
			pl.setpoints(points);
			isAlive = false;
		}*/
		if (pole[Y-1][X] != ' '&&pole[Y - 1][X] != char(191)&& pole[Y - 1][X] != char(218)&& pole[Y - 1][X] != char(207)) {
			{
				//if (pole[Y-1][X] == '-' || pole[Y-1][X + 1] == '|' || pole[Y-1][X + 1] == '_') {
					//if(pole[Y][X])
					//pl.set();
					//pl.getisAlive();
					//points = 250;
					//if(pole[Y][X + 1] != ' ')
					//pl.setpoints(points);
					pl->setpoints(points);
					//pl.points += this->points;
					isAlive = false;
				//}

			}
		}
		/*else if(pole[Y][X + 1] != '_' || pole[Y][X - 1] != '_' ||
			pole[Y][X + 1] != '-' || pole[Y][X - 1] != '-' ||
			pole[Y][X + 1] != '@' || pole[Y][X - 1] != '@') {
			isAlive = false;
		}*/
	}
	inline bool getisAlive()const { return isAlive; }
	inline int getX()const { return X; }
	inline int getY()const { return Y; }
};
class Rope {
private:
	int X, Y;
	char Image[MAX_LENGTH];
	size_t width;
public:
	Rope() :Y(), X(),width() {
		//X = rand() % ((70 - MAX_LENGTH) - (MAX_LENGTH)+1) + (MAX_LENGTH);
		//Y = rand() % ((40 - MAX_LENGTH) - (MAX_LENGTH)+1) + (MAX_LENGTH);
		//width = RND(5, MAX_LENGTH);
		SetDefaultImage();
	}
	virtual void SetDefaultImage() {
		for (size_t i = 0; i < width; i++) {
			Image[i] = rope[i];
		}
	}
	virtual void Draw(Pole&pole) {
		for (size_t i = 0; i < width; i++) {
			if (Image[i] == '+') {
				//SetColor(0x1);
				Image[i] = char(205);
			}
			pole[Y][X + i] = Image[i];
		}
	}
	inline void setwidth(size_t w) { width = w; }
	inline void setXY(int x, int y) { if (x)X = x; if (y) Y = y; }
	inline int getX()const { return X; }
	inline int getY()const { return Y; }
	inline size_t getwidth()const { return width; }
};

class Game {
	vector<Human*> people;
	vector<Stairs*> ladders;
	vector<Points*> points;
	vector<Rope*> ropes;
	Table tp;
	int cntPlayer;
	int cntEnemy;
	int cntladders;
	int cntpoints;
	int cntropes;
	Pole pole;// размеры игрового поля
	int XSize, YSize;   // координаты левого
	int XStart, YStart;	// верхнего угла поля
	void defSetup() {}
public:
	Game() : pole() {
		// параметры по умолчанию
		cntPlayer = 1;
		cntEnemy = 1;//1
		cntladders = 65;//3
		cntpoints = 5;
		cntropes = 55;
		XSize = MAX_POLE_WIDTH, YSize = MAX_POLE_HIGH;   // размеры игрового поля
		XStart = 4, YStart = 2;   // координаты левого
		//pole = nullptr;
	}
	void Start() {
		if (isPlay&&isStart)
			Play();
		if (isStart) {
			// + установка особых параметров
			people.clear(); // очистка массива от старых данных
			ladders.clear();
			points.clear();
			ropes.clear();
			
			Human::SetSizeXY(XSize, YSize);
			Human::SetStartXY(XStart, YStart);
			for (int i = 0; i < cntladders; i++) {
				Stairs*st = new Stairs;
				ladders.push_back(st);
			}
			for (int i = 0; i < cntpoints; i++) {
				Points*pt = new Points;
				points.push_back(pt);
			}
			for (int i = 0; i < cntropes; i++) {
				Rope*rp = new Rope;
				ropes.push_back(rp);
			}
			// создание игроков-людей
			for (int i = 0; i < cntPlayer; i++) {
				Human * p = new Player;
				people.push_back(p);
				
			}
			// создание игроков-ботов
			for (int i = 0; i < cntEnemy; i++) {
				Human * p = new Enemy;
				people.push_back(p);
			}
			CreatePole_char(this->pole);

			// начало игры
			Play();
		}
	}
	void CreatePole_char(char ** &pole) {
		// поле типа char **
		// удаление старого поля
		if (pole) {
			for (int i = 0; i < YSize; i++) { delete[] pole[i]; }
			delete[]pole;
		}
		// создание поля
		pole = new char*[YSize];
		for (int i = 0; i < YSize; i++) {
			pole[i] = new char[XSize + 1];
		}
		// заролнение поля
		// пока бордюром и пробелами
		for (int i = 0; i < XSize; i++) {
			pole[0][i] = '#';       // шапка поля
			pole[YSize - 1][i] = '#'; // пятка поля
		}
		pole[0][XSize] = pole[YSize - 1][XSize] = '\0'; // !!!!
		// границы спарава и слева
		for (int i = 1; i < YSize - 1; i++) {
			pole[i][0] = pole[i][XSize - 1] = '*';
			for (int j = 1; j < XSize - 1; j++) {
				pole[i][j] = ' ';
			}
			pole[i][XSize] = '\0';
		}
		for (int i = 1; i < YSize - 1; i++) {
			for (int j = 1; j < XSize - 1; j++) {
				pole[i][j] = pe[i][j];
			}
		}
		//for ( = 0; ii < cntpoints;) {
		Replace();
	}
	virtual void Replace() {
		int ii = -1;
		int i = 0;
		while (ii != cntpoints - 1) {
			for (; i < YSize; i++) {
				for (int j = 0; j < XSize; j++) {
					if (pe[i][j] == '$') {
						if (ii < cntpoints - 1)
							ii++;
						points[ii]->SetXY(j, i);

					}
				}
			}
		}
		int ld = -1;
		int he = 1;
		i = 0;
		while (ld != cntladders - 1) {
			for ( ; i < YSize; i++) {
				for (int j = 0; j < XSize - 1; j++) {
					if (pe[i][j] == '|'&&pe[i][j + 1] == '=') {//|| pe[i][j] == '|'&&pe[i][j - 1] == '='
						if (ld < cntladders - 1)
							ld++;
						ladders[ld]->setXY(j, i);
						for (int jj = 1; jj < MAX_LADDER_HIGH; jj++) {
							if (pe[i + jj][j] == '|'&&pe[i + jj][j + 1] == '=') {
								// ||pe[i - jj][j] == '|'&&pe[i - jj][j - 1] == '='
								//pe[i - jj][j] == '|'&&pe[i - jj][j + 1] == '=' || pe[i + jj][j] == '|'&&pe[i + jj][j + 1] == '='||
								he++;
							}
						}
						ladders[ld]->sethigh(he);
						he = 1;
					}
				}
			}
		}

		int re = -1;
		size_t we = 1;
		i = 0;
		while (re != cntropes - 1) {
			for ( ; i < YSize; i++) {
				for (int j = 0; j < XSize - 1; j++) {
					if (pe[i][j] == '+') {
						if (re < cntropes - 1)
							re++;
						ropes[re]->setXY(j, i);
						for (int jj = 1; jj < MAX_LENGTH; jj++) {
							if (pe[i][j + jj] == '+') {
								we++;
							}
						}
						ropes[re]->setwidth(we);
						we = 1;
					}
				}
			}
		}
	}

	virtual void Show() {
		if (isStart) {
			
			for (size_t i = 0; i < people.size(); i++) {
				people[i]->Draw(this->pole, XSize, YSize);
			}
			for (size_t i = 0; i < ladders.size(); i++) {
				ladders[i]->Draw(this->pole);
			}
			for (size_t i = 0; i < ropes.size(); i++) {
				ropes[i]->Draw(this->pole);
			}
			for (size_t i = 0; i < points.size(); i++) {
				points[i]->Draw(this->pole);
				if (points[i]->getisAlive()) {
					//Human * h = people.operator[](i);// [i] ;
					//Player* p1 = reinterpret_cast<Player*>(people[i]);
					//Player& p = *reinterpret_cast<Player*>(people[i]);
					//points[i]->Collision(this->pole, p);
					points[i]->Collision(this->pole, people[0]);
				}

			}
			SetPos(100, YStart);
			cout << "Points: " << people[0]->getpoints() << endl;
			SetPos(100, YStart + 1);
			cout << " Lives:  " << people[0]->getlives() << endl;
			// прорисовка поля на экран
			SetPos(XStart, YStart);
			for (int i = 0; i < YSize; i++) {
				SetPos(XStart, YStart + i);
				cout << this->pole[i];
			}
		}
	}
	virtual void RunStep() {
		static int g = 0;
		if (isStart) {
			for (size_t i = 0; i < people.size(); i++) {
				if (g%100==0) {
					people[1]->Displasement(pole,(Human*)people[0]);
				/*	for (int j = 0; j <= 10000000; j++) {
						if (j == 10000000) {
							for (int e = 0; e <= 10000000; e++) {
								if (e == 10000000)
									
							}
							
						}
					}*/
				}
				g++;
				if (people[0]->getisAlive()) {
					people[0]->Displasement(pole, (Human*)people[0]);
					people[0]->Collision(pole);
				}
				else {
					for (int j = 0; j < cntPlayer; j++) {
						if (people[j]->getlives() > 0) {
							system("cls");
							SetPos(XStart, YStart);
							cout << "You have left " << people[0]->getlives() << " live(-s)" << endl;
							cin.get();
							CreatePole_char(pole);
							people[j]->setisAlive(true);
							people[j]->setXY(10, 3);
							system("cls"); 
						}
						else {
							system("cls");
							SetPos(XStart, YStart);
							cout << "Game over!";
							cin.get();
							system("cls");
							cout << "Input player name: ";
							string str;
							getline(cin, str);
							tp.NickName = str;
							tp.point = people[0]->getpoints();
							Add(tp);
							//CreatePole_char(pole);
							Print();
							//e++;
							/*for (int i = 0; i < YSize; i++) {
								SetPos(XStart, YStart + i);
								cout << this->pole[i];
							}*/
							isStart = false;
							isPlay = false;
							cin.get();

						}
					}
				}
				
			}
		}
	}
	void Play() {
		system("cls");
		isPlay = true;
		while (isStart) {
			Show();
			RunStep();
		}
	}
	virtual void SaveGame() {
		system("cls");
		string fileName;
		SetPos(10, 7);
		cout << "Input file Name:";
		getline(cin, fileName);
		ofstream ofile(fileName);
		if (ofile.is_open()) {
			//cout<<"This file already "
			for (int i = 0; i < people.size(); i++) {
				ofile<< people[i]->getpoints() << endl
					<< people[i]->getlives() << endl
					<< people[i]->getX() << endl
					<< people[i]->getY() << endl;
			}
		}
		else {
			cout << "Error!\n";
		}
	}
	virtual void LoadGame() {
		system("cls");
		cout << "Input load file: ";
		string fileName;
		getline(cin,fileName);
		ifstream ifile(fileName);
		char buf[100];
		if (ifile.is_open()) {
			//Start();
			int i = -1;
			people.clear();
			for (int i = 0; i < cntPlayer; i++) {
				Human * p = new Player;
				people.push_back(p);

			}
			for (int i = 0; i < cntEnemy; i++) {
				Human * p = new Enemy;
				people.push_back(p);
			}
			while (!ifile.eof()) {
				i++;
				ifile.getline(buf, sizeof(buf) / sizeof(*buf));
				if (!strlen(buf))continue;
				int temp = atoi(buf);

				people[i]->setpoints(temp);
				ifile.getline(buf, sizeof(buf) / sizeof(*buf));
				temp = atoi(buf);
				people[i]->setlives(temp);
				//
				ifile.getline(buf, sizeof(buf) / sizeof(*buf));
				temp = atoi(buf);
				ifile.getline(buf, sizeof(buf) / sizeof(*buf));
				int t = atoi(buf);
				people[i]->setXY(temp,t);
			}
			ladders.clear();
			points.clear();
			ropes.clear();

			Human::SetSizeXY(XSize, YSize);
			Human::SetStartXY(XStart, YStart);
			for (int i = 0; i < cntladders; i++) {
				Stairs*st = new Stairs;
				ladders.push_back(st);
			}
			for (int i = 0; i < cntpoints; i++) {
				Points*pt = new Points;
				points.push_back(pt);
			}
			for (int i = 0; i < cntropes; i++) {
				Rope*rp = new Rope;
				ropes.push_back(rp);
			}
			CreatePole_char(pole);
			Play();
			//int temp[4];
			//int c = 0;
			//for (int s = 0; s < sizeof(buf); s++) {
			//	if (buf[s] != '\n') {
			//		temp[c] = buf[s]; c++;
			//	}
			//}
			//for (int i = 0; i < people.size(); i++) {
			//	people[i]->setXY(buf);
			//}
		}
	}
};
