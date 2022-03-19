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
//������ �������.
const int n = 10;
const int m = 10;
//����� �������� ���� � �������� ����.
class FieldGame;
//������� ��������.
enum Navy
{
	//�����.
	boat = 1,
	//�������.
	destroyer,
	//�������.
	cruiser,
	//������.
	battleship
};

//���������� ���� ����. ������������ � ���������� �������� ����.
enum Letter_Code
{
	letter_code_A = 65,
	letter_code_J = 74,
	letter_code_a = 97,
	letter_code_j = 106
};

//����� �������� ����.
void Line1();
//��������� ��� �������� ����.
void LineLetter();
//����� ���������� ��� �������� �����.
void InterFace_1(FieldGame&, Navy&);

//����� �������� ����.
class FieldGame
{
private:
	//������ �������� ���� - ��������� ������.
	vector<vector<string>> field;
public:
	//����������� ����������. ������ ����� �������.
	static int i_static;
	//����������� ����������. ������ �������� �������.
	static int j_static;
	//������� �������� ������(����� ���������� ������ ��������).
	static size_t count_ship_player;
	//������� �������� ����������(����� ���������� ������ ��������).
	static size_t count_ship_comp;
	//������ ���������� ������� �� ����(�����������, �������������,����������).
	static string orientation_ship;
	//�����������.
	FieldGame();
	//����������.
	~FieldGame();
	//����������� ���� ������. ������������ ��� ������ ����������� ��������.
	void ShowFieldPlayer();
	//��������� ����������� ��������.
	void NavyRandom();
	//���������� ��������.
	bool BuildShip(int, int, Navy, int position = 2, int flag = 0);
	//������ ����������� ��������.
	void NavyManual();
	//�������� �� ������������ ����������� ��������.
	bool CheckShip(int, int);
	//�������� �� ������������ ������ ������ ��� ����� ����������.
	bool CheckCell();
	//����� ������.
	bool BattlePlayer();
	//����� ����������.
	bool BattleComp();
	//������ ����� ����������.
	bool GotorNotgot();
	//����������� ����� ������ � ����������.
	friend void ShowTotal(const FieldGame&, const FieldGame&);
};

