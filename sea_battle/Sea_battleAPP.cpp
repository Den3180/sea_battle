#include"sea_battle.h"
//-------------------------------------------------------//
int FieldGame::i_static = -1;
int FieldGame::j_static = -1;
//Сумма клеток всех кораблей.
size_t FieldGame::count_ship_player = 20;
//Сумма клеток всех кораблей.
size_t FieldGame::count_ship_comp = 20;
//Положение корабля на поле(вертик./гориз.). 
//Используется при атаке компьютера. Определяет положение подбитых кораблей.
string FieldGame::orientation_ship = "unknow";

//Линии игрового поля.
void Line1()
{
	cout.setf(ios::right);
	cout.width(3);
	cout << "+";

	for (int i = 0; i < n; i++)
		cout << "---+";
	cout.unsetf(ios::right);
}
//Буквенный ряд игрового поля.
void LineLetter()
{
	cout.setf(ios::left);

	for (int i = 0; i < m; i++)
	{
		cout.width(4);
		cout << static_cast<char>(letter_code_A + i);
	}
}

//Шапка интерфейса при неверном вводе.
void InterFace_1(FieldGame& obj, Navy& type_ship)
{
	cout << "\nНеверный ввод!\n";
	system("pause");
	system("cls");
	cout << "\t\tСоздание флота\n";
	obj.ShowFieldPlayer();
	switch (type_ship)
	{
	case battleship:
		cout << "\t\tЛинкор(1 корабл, 4 клетки)\n";
		break;
	case cruiser:
		cout << "\t\tЭсминец(2 корабля по 3 клетки)\n";
		break;
	case destroyer:
		cout << "\t\tКорвет(3 корабля по 2 клетки)\n";
		break;
	case boat:
		cout << "\t\tКатер(4 корабля по 1 клетке)\n";
		break;

	}
}
//Анализ атаки компьютера.
bool FieldGame::GotorNotgot()
{
	if (field[i_static][j_static] == "0")
	{
		field[i_static][j_static] = "X";
		cout << "\nБолванка в борт ударила, адмирал!\n";
		count_ship_player--;
		return true;
	}
	else if (field[i_static][j_static] == " ")
	{
		field[i_static][j_static] = "*";
		cout << "\nПротивник дал нам шанс, адмирал!\n";
		return false;
	}
}

//Проверка на корректность расстановке кораблей.
bool
FieldGame::CheckShip(int i, int j)
{
	for (int ii = -1; ii <= 1; ii++)
	{
		//Проверка пересечения границы поля.
		if (i + ii > m - 1 || i + ii < 0)
			continue;
		for (int jj = -1; jj <= 1; jj++)
		{
			//Проверка пересечения границы поля.
			if (j + jj > m - 1 || j + jj < 0)
				continue;
			//Анализ клетки на присутствии там корабля. Не позволяет построить корабли в притирку друг к другу.
			if (field[i + ii][j + jj] == "0")
			{
				return false;
			}
		}
	}
	return true;
}
//Проверка на корректность выбора клетки при атаке компьютера.
bool FieldGame::CheckCell()
{
	for (int ii = -1; ii <= 1; ii++)
	{
		//Проверка пересечения границы поля. 
		if (i_static + ii > m - 1 || i_static + ii < 0)
			continue;
		for (int jj = -1; jj <= 1; jj++)
		{
			//Проверка пересечения границы поля. 
			if (j_static + jj > m - 1 || j_static + jj < 0)
				continue;
			//Проверка на повторное попадание в одну и туже клетку.
			if (field[i_static + ii][j_static + jj] == "X" || field[i_static][j_static]=="*")
			{
				return false;
			}
		}
	}
	return true;
}

//Конструктор поля.

FieldGame::FieldGame()
{
	for (int i = 0; i < n; i++)
	{
		vector<string> temp;
		for (int j = 0; j < m; j++)
		{
			temp.push_back(" ");
		}
		field.push_back(temp);
	}
}
//Деструктор.

FieldGame::~FieldGame()
{
	//cout << "\nДеструктор\n";
}

//Отображение поля игрока. Используется при ручной расстановки кораблей.
void
FieldGame::ShowFieldPlayer()
{
	cout << "\n\t\tПоле игрока\n\n";
	cout << " ";
	cout.setf(ios::right);
	LineLetter();
	cout << "\n";
	Line1();
	cout << "\n";
	for (int i = 0; i < n; i++)
	{
		cout.setf(ios::left);
		cout.width(2);
		cout << i + 1;

		for (int j = 0; j < m; j++)
		{
			cout << "| " << field[i][j] << " ";
		}
		cout << "|\n";
		Line1();
		cout << "\n";
	}
}
//Отображение полей игрока и компьютера.
void ShowTotal(const FieldGame& player, const FieldGame& comp)
{
	cout << "\n\t\t\t\t\tМорской бой\n\n";
	cout << "\n\t\tПоле игрока\t\t\t\t";
	cout << "\tПоле компьютера\n\n    ";
	LineLetter();
	cout << "\t    ";
	LineLetter();
	cout << "\n";
	Line1();
	cout << "\t";
	Line1();
	cout << "\n";

	for (int i = 0; i < n; i++)
	{
		cout.setf(ios::left);
		cout.width(2);
		cout << i + 1;

		for (int j = 0; j < m; j++)
		{
			cout << "| " << player.field[i][j] << " ";
		}
		cout << "|\t";

		cout.setf(ios::left);
		cout.width(2);
		cout << i + 1;
		for (int j = 0; j < m; j++)
		{
			if (comp.field[i][j] == "0")
				cout << "| " << "  ";
			else
				cout << "| " << comp.field[i][j] << " ";
		}
		cout << "|\n";
		Line1();
		cout << "\t";
		Line1();
		cout << "\n";
	}

}
//Построение кораблей.
bool FieldGame::BuildShip(int i, int j, Navy type, int position, int flag)
{
	//Счетчик клеток корабля.
	int count = 0;
	//Условие того, что корабль строится рандомно и его положение, вертикально или горизантально,
	////определяется случайным способом.
	if (position == 2)
	{
		position = rand() % 2;
		flag = rand() % 2;
	}

	switch (position)
	{
		//Корабль строится вертикально.
	case 0:
		//Направление построения корабля. 0-вниз.
		if (flag == 0)
		{
			//Цикл работает пока счетчик клеток не совпадет с типом корабля.
			while (count < type)
			{
				//Проверка пространства для построения корабля.
				if ((i + count) < n && CheckShip(i + count, j) != false)
				{
					count++;
				}
				//Сброс, если проверка не пройдена.
				else
				{
					count = 0;
					//Смена направления построения корабля. 1-вверх.
					flag = 1;
					break;
				}
			}
			//Если есть совпадение с счетчика клеток с типом корабля.
			if (count == type)
			{
				//Выполнеине построение корабля.
				do
				{
					field[i++][j] = "0";
					count--;
				} while (count > 0);
				return true;
			}
		}

		//Если корабль строится вертикально вверх.
		if (flag == 1)
		{
			while (count < type)
			{
				//Проверка пространства для построения корабля.
				if (i - count > 0 && CheckShip(i - count, j) != false)
					count++;
				//Сброс, если проверка не пройдена.
				else
				{
					count = 0;
					//Смена направления построения корабля. 1-вниз.
					flag = 0;
					break;
				}
			}
			//Если есть совпадение с счетчика клеток с типом корябля.
			if (count == type)
			{
				//Выполнеине построение корабля.
				do
				{
					field[i--][j] = "0";
					count--;
				} while (count > 0);
				return true;
			}
		}
		break;

		//Корабль строится горизонтально.
	case 1:
		//Направление построения корабля. 0-вправо.
		if (flag == 0)
		{
			//Цикл работает пока счетчик клеток не совпадет с типом корабля.
			while (count < type)
			{
				//Проверка пространства для построения корабля.
				if ((j + count) < m && CheckShip(i, j + count) != false)
				{
					count++;
				}
				//Сброс, если проверка не пройдена.
				else
				{
					count = 0;
					flag = 1;
					break;
				}
			}
			//Если есть совпадение с счетчика клеток с типом корябля.
			if (count == type)
			{
				//Выполнение построение корабля.
				do
				{
					field[i][j++] = "0";
					count--;
				} while (count > 0);
				return true;
			}
		}
		//Направление построения корабля. 0-влево.
		if (flag == 1)
		{
			//Цикл работает пока счетчик клеток не совпадет с типом корабля.
			while (count < type)
			{
				//Проверка пространства для построения корабля.
				if (j - count > 0 && CheckShip(i, j - count) != false)
					count++;
				//Сброс, если проверка не пройдена.
				else
				{
					count = 0;
					flag = 0;
					break;
				}
			}
			//Если есть совпадение с счетчика клеток с типом корябля.
			if (count == type)
			{
				//Выполнение построение корабля.
				do
				{
					field[i][j--] = "0";
					count--;
				} while (count > 0);
				return true;
			}
		}
		break;
	}
	return false;
}
//Случайная расстановка кораблей.
void FieldGame::NavyRandom()
{
	//Линкор---------------------------//
	 //Количество кораблей данного типа.
	int countship = 1;
	int i = 0;
	int j = 0;
	while (countship > 0)
	{
		i = rand() % 9;
		j = rand() % 9;
		if (BuildShip(i, j, battleship) != false)
			countship--;
	}
	//------------Крейсер---------------------------//
	 //Количество кораблей данного типа.
	countship = 2;
	while (countship > 0)
	{
		i = rand() % 9;
		j = rand() % 9;
		if (BuildShip(i, j, cruiser) != false)
			countship--;
	}
	//------------Эсминец---------------------------//
	 //Количество кораблей данного типа.
	countship = 3;
	while (countship > 0)
	{
		i = rand() % 9;
		j = rand() % 9;
		if (BuildShip(i, j, destroyer) != false)
			countship--;
	}
	//------------Катер---------------------------//
	 //Количество кораблей данного типа.
	countship = 4;
	while (countship > 0)
	{
		i = rand() % 9;
		j = rand() % 9;
		if (BuildShip(i, j, boat) != false)
			countship--;
	}
}
//Ручная расстановка кораблей.
void
FieldGame::NavyManual()
{
	char position_letter = '\0';
	int i = 0, j = 0, flag = 0, count_ship = 10;
	int position = 0;
	Navy type_ship;
	system("cls");

	do
	{

		cout << "\t\tСоздание флота\n";
		ShowFieldPlayer();

		switch (count_ship)
		{
		case 10:
			type_ship = battleship;
			cout << "\t\tЛинкор(1 корабль, 4 клетки)\n";
			break;
		case 9:
		case 8:
			type_ship = cruiser;
			cout << "\t\tЭсминец(2 корабля по 3 клетки)\n";
			break;
		case 7:
		case 6:
		case 5:
			type_ship = destroyer;
			cout << "\t\tКорвет(3 корабля по 2 клетки)\n";
			break;
		case 4:
		case 3:
		case 2:
		case 1:
			type_ship = boat;
			cout << "\t\tКатер(4 корабля по 1 клетке)\n";
			break;
		}
		cout << "Введите координаты клетки.\n";
		while (true)
		{

			cout << "Координата по горизонтали (буквы от A до J (без учета регистра)): ";
			cin >> position_letter;
			//Перевод символьной переменной в десятичный код.
			j = static_cast<int>(position_letter);
			//Проверка на соответствие кодам букв игрового поля.
			if (j >= letter_code_a && j <= letter_code_j)
			{
				j = j - (letter_code_a - letter_code_A) - letter_code_A;
				break;
			}
			//Проверка на соответствие кодам букв игрового поля.
			else if (j >= letter_code_A && j <= letter_code_J)
			{
				j = j - letter_code_A;
				break;
			}
			InterFace_1(*this, type_ship);
		}

		while (true)
		{
			cout << "Координата по вертикали (цифра от 1 до 10): ";
			cin >> i;
			i--;

			//Проверка на выход за границы поля.
			if (i<0 || i>m - 1)
			{
				InterFace_1(*this, type_ship);
			}
			else
				break;
		}

		while (true && type_ship != boat)
		{
			cout << "\nОреинтация корабля на поле: 0-вертикально, 1-горизонтально \n";
			cout << "Ваш выбор: ";
			cin >> position;
			//Проверка выбора позиционирования корабля.
			if (position != 0 && position != 1)
			{
				InterFace_1(*this, type_ship);
			}
			else
				break;
		}

		while (true && type_ship != boat)
		{
			cout << "\nНаправление корабля на поле : 0-вниз/вправо, 1-вверх/влево\n";
			cout << "Ваш выбор: ";
			cin >> flag;
			//Проверка выбора направления построения корабля.
			if (flag != 0 && flag != 1)
			{
				InterFace_1(*this, type_ship);
			}
			else
				break;
		}
		if (BuildShip(i, j, type_ship, position, flag) == false)
		{
			cout << "\nНаложение кораблей или выход за границы поля!\n"
				<< "Попробуйте еще раз...\n";
			system("pause");
		}
		else
			count_ship--;
		system("cls");
	} while (count_ship > 0);
}
//Атака игрока.
bool
FieldGame::BattlePlayer()
{
	int i, j;
	char position_letter = '\0';

	cout << "\nВаш ход!\n";

	while (true)
	{

		cout << "Координата по горизонтали (буквы от A до J (без учета регистра)): ";
		cin >> position_letter;
		j = static_cast<int>(position_letter);
		//Проверка на соответствие кодам букв игрового поля.
		if (j >= letter_code_a && j <= letter_code_j)
		{
			j = j - (letter_code_a - letter_code_A) - letter_code_A;
			break;
		}
		//Проверка на соответствие кодам букв игрового поля.
		else if (j >= letter_code_A && j <= letter_code_J)
		{
			j = j - letter_code_A;
			break;
		}
		cout << "\nКоордината за пределами поля. Повторите ввод!\n";

	}

	while (true)
	{
		cout << "Координата по вертикали (цифра от 1 до 10): ";
		cin >> i;
		i--;

		if (i<0 || i>m - 1)
		{
			cout << "\nКоордината за пределами поля. Повторите ввод!\n";
		}
		else
			break;
	}

	if (field[i][j] == "0")
	{
		field[i][j] = "X";
		cout << "\nЕсть попадание!\n";
		count_ship_comp--;
		return true;
	}
	else if (field[i][j] == " ")
	{
		field[i][j] = "*";
		cout << "\nПромах!\n";
	}
	//Проверка на повтороное попадание в клетку.
	else if (field[i][j] == "*" || field[i][j] == "X")
	{
		cout << "\nПротри свой глаз, адмирал! В этом квадрате ты побывал!\n";
	}

	return false;
}
//Атака компьютера.
bool
FieldGame::BattleComp()
{
	cout << "\nХод компьютера...\n";
	Sleep(2000);
	//Первый выстрел.
	if (i_static == -1)
	{
		i_static = rand() % 9;
		j_static = rand() % 9;
	}
	//Последующие выстрелы при условие, что предыдущий выстрел был мимо.
	else if (field[i_static][j_static] == "*" && orientation_ship=="unknow")
	{
		//Проверка ячейки атаки.
		while (!CheckCell())
		{
			i_static = rand() % 9;
			j_static = rand() % 9;
		}
	}
	//Если есть первое попадание (неизвестен ни тип ни направление корабля).
	if (field[i_static][j_static] == "X" && orientation_ship == "unknow")
	{
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				if (i + j != -1 && i + j != 1)
				{
					if (i == 1 && j == 1)
					{
						while (!CheckCell())
						{
							i_static = rand() % 9;
							j_static = rand() % 9;
						}
					}
					//Проверка ячеек только по горизонтали и вертикали. Диагональные игнорируются.
					continue;
				}
				//Проверка границ поля.
				if (i_static + i < 0 || i_static + i > m || j_static + j < 0 || j_static + j > n)
				{
					continue;
				}
				//Проверка клетки на предыдущие попадания.
				if (field[i_static + i][j_static + j] == "X" || field[i_static + i][j_static + j] == "*")
				{
					continue;
				}
				//Если промах.
				if (field[i_static + i][j_static + j] == " ")
				{
					field[i_static + i][j_static + j] = "*";
					cout << "\nПротивник дал нам шанс, адмирал!\n";
					return false;
				}
				//Если попадание.
				if (field[i_static + i][j_static + j] == "0")
				{
					//Определение положения подбитого корабля.
					if (i_static + i == i_static)
						orientation_ship = "horizontal";
					else
						orientation_ship = "vertical";

					i_static = i_static + i;
					j_static = j_static + j;
					return GotorNotgot();
				}
			}
		}
	}
	//Блок управления атакой компьютера, если частично подбитый корабль в положении горизонтально.
	if (orientation_ship == "horizontal")
	{
		while (field[i_static][j_static] == "X" && j_static != 0)
			j_static--;
		if (field[i_static][j_static] == " " || field[i_static][j_static] == "0")
		{
			return GotorNotgot();
		}
		else if (field[i_static][j_static] == "*")
		{
			j_static++;
		}

			while (field[i_static][j_static] == "X" && j_static!=n-1)
				j_static++;
			if (field[i_static][j_static] == "0" || field[i_static][j_static] == " ")
			{
				if(field[i_static][j_static] == " ")
				orientation_ship = "unknow";
				return GotorNotgot();
			}
			if (field[i_static][j_static] == "*" || field[i_static][j_static] == "X")
			{
				orientation_ship = "unknow";
			while (true)
			{
				i_static = rand() % 9;
				j_static = rand() % 9;
				if (field[i_static][j_static] != "*" && field[i_static][j_static] != "X")
					break;
			}
			}
			return GotorNotgot();
	}
	//Блок управления атакой компьютера, если частично подбитый корабль в положении вертикально.
    if (orientation_ship == "vertical")
	{
	 while (field[i_static][j_static] == "X" && i_static != 0)
		i_static--;
	if (field[i_static][j_static] == " " || field[i_static][j_static] == "0")
	{
		return GotorNotgot();
	}
	else if (field[i_static][j_static] == "*")
	{
		i_static++;
	}

	while (field[i_static][j_static] == "X" && i_static != n - 1)
		i_static++;
	if (field[i_static][j_static] == "0" || field[i_static][j_static] == " ")
	{
		if (field[i_static][j_static] == " ")
			orientation_ship = "unknow";
		return GotorNotgot();
	}
	if (field[i_static][j_static] == "*" || field[i_static][j_static] == "X")
	{
		orientation_ship = "unknow";
		while (true)
		{
			i_static = rand() % 9;
			j_static = rand() % 9;
			if (field[i_static][j_static] != "*" && field[i_static][j_static] != "X")
				break;
		}
	}
	return GotorNotgot();
    }
	return GotorNotgot();
}