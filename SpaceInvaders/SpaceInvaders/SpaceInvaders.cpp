#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

int map[20][20];
int playerx = 10;
int playery = 18;
int shot = 0;
int baza = 20;;
int oponentx[10];
int oponenty[10];
clock_t start;


void sh0t(int *shotx, int *shoty, int g);
void oponent(int *oponentx, int *oponenty, int i);
void gameover(clock_t start, int g);
void controls(int g);
void menu(int g);


int main()
{
	int shotx[1000];
	int shoty[1000];
	char move;
	int g = -1;


	//Otwarcie menu
	system("cls");
	cout << "WITAJ W MOJEJ GRZE!" << endl;
	Sleep(2000);
	menu(g);

	//Generowanie pocz¹tkowej pozycji przeciwników 
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		oponenty[i] = rand() % 10 - 11;
		oponentx[i] = rand() % 18 + 1;
	}

	//Licznik inicjacja 
	start = clock();

	//G³ówna pêtla
	for (int i = 0; i <= 1; i--)
	{
		system("cls");
		//Load
		for (int y = 19; y >= 0; y--)
		{
			for (int x = 19; x >= 0; x--)
			{
				if (x == 0 || x == 19 || y == 0 || y == 19) map[x][y] = 1;
				else if (x == playerx && y == playery) map[x][y] = 2;
				else map[x][y] = 0;

				for (int j = 0; j < 1000; j++)
				{
					if (x == shotx[j] && y == shoty[j]) map[x][y] = 3;
				}

				for (int j = 0; j < 10; j++)
				{
					if (x == oponentx[j] && y == oponenty[j]) map[x][y] = 4;
				}
			}
		}

		//Render
		for (int y = 19; y >= 0; y--)
		{
			for (int x = 19; x >= 0; x--)
			{
				if (map[x][y] == 0) cout << " ";
				else if (map[x][y] == 1) cout << "X";
				else if (map[x][y] == 2) cout << "O";
				else if (map[x][y] == 3) cout << "!";
				else if (map[x][y] == 4) cout << "H";
			}
			cout << endl;
		}
		cout << "Zycie bazy: " << baza << endl;
		cout << "Czas gry: " << (clock() - start) / (int)CLOCKS_PER_SEC << "s";

		//Data
		if (_kbhit())
		{
			//Move
			move = _getch();

			switch (move)
			{
				//case 'w': playery++;     break;
				//case 's': playery--;     break;
			case 'A':
			case 'a': playerx++;     break;
			case 'D':
			case 'd': playerx--;     break;
			case 'E':
			case 'e': shot++; g++;   break;//shot - inicjaci  strza³u, g - licznik strza³ów wykonanych
			}

			//Border
			if (playerx == 0) playerx = 1;
			else if (playerx == 19) playerx = 18;
			else if (playery == 0) playery = 1;
			else if (playery == 19) playery = 18;
		}

		//Shot
		if (shot != 0)
		{
			shotx[g] = playerx;
			shoty[g] = playery;
		}
		sh0t(shotx, shoty, g);

		//Hitboxy
		if (g >= 0)
		{
			for (int j = 0; j < 1000; j++)
			{
				for (int y = 0; y < 10; y++)
				{
					if (shotx[j] == oponentx[y] && (shoty[j] == oponenty[y] + 1 || shoty[j] == oponenty[y]))//shotx[j] == oponentx[y] && shoty[j] == oponenty[y])
					{
						shoty[j] = -20;
						oponenty[y] = -2; //Losowanie miejsca y
						oponentx[y] = rand() % 18 + 1;  //Losowanie miejsca x	
					}
				}
			}
		}

		//Oponent
		//if (i % 1 == 0)
		//{
		oponent(oponentx, oponenty, i);
		//}

		//Gameover
		if (baza <= 0) gameover(start, g);

		Sleep(17);
	}

	system("pause");
	return 0;
}

void sh0t(int *shotx, int *shoty, int g)
{
	for (int j = 0; j <= g; j++)
	{
		if (shoty[j] > 1) shoty[j]--; //zmiana pozycji strza³u o 1
		else shoty[j] = -20; //ustalenie standardowej pozycji strza³u
	}

	shot = 0; //koniec inicjacji strza³u 
}

void oponent(int *oponentx, int *oponenty, int i)
{
	if (i % 15 == 0)
	{
		for (int i = 0; i < 10; i++)
		{
			//Ruch przeciwnika
			if (oponenty[i] < 18)
			{
				oponenty[i]++;
			}
			//Jak dojdzie do koñca
			else if (oponenty[i] == 18)
			{
				baza--; //Baza traci ¿ycie
				oponenty[i] = -2; //Losowanie miejsca y
				oponentx[i] = rand() % 18 + 1;  //Losowanie miejsca x
			}
			if (oponenty[i] == 0) oponenty[i]++;
		}
	}
}

void gameover(clock_t star, int g)
{
	int what_to_do = 0;
	double czas;
	czas = (clock() - star) / (double)CLOCKS_PER_SEC;

	system("cls");
	cout << "PRZEGRALES/AS!" << endl << endl << "Udalo ci sie przetrwac " << czas << "sekund";
	Sleep(5000);
	cout << endl << endl << "Co chcesz zrobic?\n1. Graj ponownie\n2. Sterowanie\n3. Wyjdz\nTwoja odpowiedz: ";
	cin >> what_to_do;

	if (what_to_do > 3 || what_to_do < 1)
	{
		cout << "Podales bledna liczbe! \nSprobuj ponownie!";
		Sleep(1500);
		gameover(star, g);
	}

	switch (what_to_do)
	{
	case 1:
		playerx = 10;
		playery = 18;
		shot = 0;
		baza = 20;
		g = -1;
		start = clock();
		for (int y = 0; y < 10; y++)
		{
			oponenty[y] = rand() % 10 - 11;
			oponentx[y] = rand() % 18 + 1;
		}
		break;
	case 2:
		controls(g);
		break;
	case 3:
		exit(0);
		break;
	}
}

void controls(int g)
{
	int exit;

	system("cls");

	cout << "---------------ZASADY GRY---------------" << endl;
	cout << "Celem gry jest przetrwac jak najwiecej czasu." << endl;
	cout << "Przeciwnicy atakuja twoja baze, jezeli nie zestrzelisz ich przed tym jak dotra do niej uszkodza ja" << endl;
	cout << "Jezeli zycie twojej bazy spadnie do zera przegrywasz!" << endl;
	cout << "POWODZENIA!" << endl;

	cout << endl << "---------------STEROWANIE---------------" << endl;
	cout << "A - ruch w lewo" << endl;
	cout << "D - ruch w prawo" << endl;
	cout << "E - strzal" << endl << endl;

	cout << "Jezeli chcesz wrocic wybierz 1: ";
	cin >> exit;
	if (exit != 1)
	{
		cout << "Podales bledna liczbe! \nSprobuj ponownie!";
		Sleep(1500);
		controls(g);
	}
	else
	{
		menu(g);
	}
}

void menu(int g)
{
	int what_to_do = 0;

	system("cls");

	cout << "---------------MENU---------------" << endl;
	cout << "1. GRAJ" << endl;
	cout << "2. Zasady i sterowanie" << endl;
	cout << "3. Wyjdz" << endl;


	what_to_do = 0;
	cin >> what_to_do;
	if (what_to_do > 3 || what_to_do < 1)
	{
		cout << "Podales bledna liczbe! \nSprobuj ponownie!";
		Sleep(1500);
		menu(g);
	}

	switch (what_to_do)
	{
	case 1:
		playerx = 10;
		playery = 18;
		shot = 0;
		baza = 20;
		g = -1;
		start = clock();
		for (int y = 0; y < 10; y++)
		{
			oponenty[y] = rand() % 10 - 11;
			oponentx[y] = rand() % 18 + 1;
		}
		break;
	case 2:
		controls(g);
		break;
	case 3:
		system("cls");

		cout << "Ale czy aby na pewno?";
		cin >> what_to_do;
		system("cls");
		cout << "Jestes w 100% pewny/a?";
		cin >> what_to_do;
		system("cls");
		cout << "Zastanow sie poki jeszcze mozesz";
		cin >> what_to_do;
		system("cls");
		cout << "Potem nie bedzie odwrotu!";
		cin >> what_to_do;
		system("cls");
		cout << "MASZ TY ROZUM I GODNOSC CZLOWIEKA?!";
		cin >> what_to_do;
		system("cls");
		cout << "Jak nie, to nie. Zegnaj graczu!";
		for (int i = 10; i >= 0; i--)
		{
			system("cls");
			cout << i;
			Sleep(1000);
		}
		exit(0);
		break;
	}
}