#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <ctime>
#include "game.h"

using namespace std;

void sh0t(int *shotx, int *shoty, int g)
{
	for (int j = 0; j <= g; j++)
	{
		if (shoty[j] > 1) shoty[j]--; //zmiana pozycji strza�u o 1
		else shoty[j] = -20; //ustalenie standardowej pozycji strza�u
	}

	shot = 0; //koniec inicjacji strza�u 
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
			//Jak dojdzie do ko�ca
			else if (oponenty[i] == 18)
			{
				baza--; //Baza traci �ycie
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