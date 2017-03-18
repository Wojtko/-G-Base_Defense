#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <ctime>
#include "game.h"

using namespace std;

int map[20][20];
int playerx = 10;
int playery = 18;
int shot = 0;
int baza = 20;;
int oponentx[10];
int oponenty[10];
clock_t start;

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

	//Generowanie początkowej pozycji przeciwników 
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		oponenty[i] = rand() % 10 - 11;
		oponentx[i] = rand() % 18 + 1;
	}

	//Licznik inicjacja 
	start = clock();

	//Główna pêtla
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
			case 'e': shot++; g++;   break;//shot - inicjacia  strzału, g - licznik strzałów wykonanych
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
					if (shotx[j] == oponentx[y] && (shoty[j] == oponenty[y] + 1 || shoty[j] == oponenty[y]))
					{
						shoty[j] = -20;
						oponenty[y] = -2; //Losowanie miejsca y
						oponentx[y] = rand() % 18 + 1;  //Losowanie miejsca x	
					}
				}
			}
		}
		//Oponent
		oponent(oponentx, oponenty, i);

		//Gameover
		if (baza <= 0) gameover(start, g);

		Sleep(17);
	}

	system("pause");
	return 0;
}