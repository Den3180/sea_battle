#include"sea_battle.h"

int main()
{
	system("chcp 1251>null");
	srand(time(NULL));
	char answer;

	FieldGame field_player, field_comp;

	ShowTotal(field_player, field_comp);
	field_comp.NavyRandom();
	cout << "\n\nВыберите способ расстановки флота игрока: "
		<< "1-случайная, 2-ручная \n";
	cout << "Ваш выбор...";
	do
	{
		cin >> answer;
		switch (answer)
		{
		case '1':
			field_player.NavyRandom();
			system("cls");
			break;
		case '2':
			field_player.NavyManual();
			system("cls");
			break;
		default:
			cout << "\nНеверный ввод! Повторите выбор...";
			break;
		}
	} while (answer != '1' && answer != '2');

	ShowTotal(field_player, field_comp);
	
	//Основной игровой блок. 
	do
	{
		while (field_comp.BattlePlayer() && FieldGame::count_ship_comp != 0)
		{
			Sleep(2000);
			system("cls");
			ShowTotal(field_player, field_comp);
		}
		Sleep(2000);
		system("cls");
		ShowTotal(field_player, field_comp);

	if (FieldGame:: count_ship_comp == 0)
	{
		cout << "\nФлот противника потоплен, адмирал! Победа!\n";
		break;
	}
		while (field_player.BattleComp() && FieldGame::count_ship_player!=0)
		{
			Sleep(2000);
			system("cls");
			ShowTotal(field_player, field_comp);
		}
		Sleep(2000);
		system("cls");
		ShowTotal(field_player, field_comp);

	    if(FieldGame::count_ship_player==0)
	    {
			cout << "\nВаш флот потоплен, адмирал! Вам крышка!\n";
			break;
	    }

	} while (true);

	return 0;
}


