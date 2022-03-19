#pragma once
#define _SRT_SECURE__NO_WARNINGS
#include<iostream>
#include<vector>
#include<string>
#include<string.h>
#include<string.h>
#include<algorithm>
#include<stdlib.h>
#include<iomanip>
#include<time.h>
#include<windows.h>

using namespace std;
//Размер массива.
const int n = 10;
const int m = 10;
//Класс игрового поля с методами игры.
class FieldGame;
//Индексы кораблей.
enum Navy
{
	//Катер.
	boat = 1,
	//Эсминец.
	destroyer,
	//Крейсер.
	cruiser,
	//Линкор.
	battleship
};

//Десятичные коды букв. Используется в построении игрового поля.
enum Letter_Code
{
	letter_code_A = 65,
	letter_code_J = 74,
	letter_code_a = 97,
	letter_code_j = 106
};

//Линии игрового поля.
void Line1();
//Буквенный ряд игрового поля.
void LineLetter();
//Шапка интерфейса при неверном вводе.
void InterFace_1(FieldGame&, Navy&);

//Класс игрового поля.
class FieldGame
{
private:
	//Основа игрового поля - двумерный массив.
	vector<vector<string>> field;
public:
	//Статическая переменная. Индекс строк массива.
	static int i_static;
	//Статическая переменная. Индекс столбцов массива.
	static int j_static;
	//Счетчик кораблей игрока(общее количество клеток кораблей).
	static size_t count_ship_player;
	//Счетчик кораблей компьютера(общее количество клеток кораблей).
	static size_t count_ship_comp;
	//Маркер ориентации корабля на поле(вертикально, горизонтально,неизвестно).
	static string orientation_ship;
	//Конструктор.
	FieldGame();
	//Деструктор.
	~FieldGame();
	//Отображение поля игрока. Используется при ручной расстановки кораблей.
	void ShowFieldPlayer();
	//Случайная расстановка кораблей.
	void NavyRandom();
	//Построение кораблей.
	bool BuildShip(int, int, Navy, int position = 2, int flag = 0);
	//Ручная расстановка кораблей.
	void NavyManual();
	//Проверка на корректность расстановки кораблей.
	bool CheckShip(int, int);
	//Проверка на корректность выбора клетки при атаке компьютера.
	bool CheckCell();
	//Атака игрока.
	bool BattlePlayer();
	//Атака компьютера.
	bool BattleComp();
	//Анализ атаки компьютера.
	bool GotorNotgot();
	//Отображение полей игрока и компьютера.
	friend void ShowTotal(const FieldGame&, const FieldGame&);
};

