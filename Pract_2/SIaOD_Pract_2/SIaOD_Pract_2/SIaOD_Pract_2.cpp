#include "pch.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <conio.h>

using namespace std;

#define ALF_CHAR 256



int main()
{

	string a;
	getline(cin, a);
	string t;
	getline(cin, t);
	
	int n = a.length();
	int m = t.length();

	int *pi = new int[n];
	pi[0] = 0;

	int y = 0;

	cout << "Case sensitive? (1 - yes ; 2 - no)" << endl;
	while ((y != 1) && (y != 2)) {
		cin >> y;
		if ((y != 1) && (y != 2)) {
			cout << "Chose '1' or '2'!" << endl;
		}
	}

	int counter[4];
	//Упражнение №1
	cout << "Knut-Morris-Pratt algorithm" << endl;

	int i = 1;
	int j = 0;
	int k = 0; //Символ строки
	int l = 0; //Символ образа

	switch (y) {
	case 1:
	{
		//Префикс-функция
		while (i <= n) {
			if (a[i] == a[j]) {
				pi[i] = j + 1;
				i++;
				j++;
			}
			else {
				if (j == 0) {
					pi[i] = 0;
					i++;
				}
				else {
					j = pi[j - 1];
				}
			}
			counter[0]++;
		}

		//Основная функция
		while ((k < m) && (l != n) && (k != m)) {
			if (t[k] == a[l]) {
				k++;
				l++;
				if (l == n) {
					cout << "Success!" << endl;
				}
				else if (k == m) {
					cout << "Failure!" << endl;
				}
			}
			else if ((t[k] != a[l]) && (l != 0)) {
				l = pi[l - 1];
			}
			else if ((t[k] != a[l]) && (l == 0)) {
				k++;
				if (k == m) {
					cout << "Failure!" << endl;
				}
			}
			counter[0]++;
		}
		break;
	}
	case 2:
	{
		{
			while (i <= n) {
				if (tolower(a[i]) == tolower(a[j])) {
					pi[i] = j + 1;
					i++;
					j++;
				}
				else {
					if (j == 0) {
						pi[i] = 0;
						i++;
					}
					else {
						j = pi[j - 1];
					}
				}
				counter[0]++;
			}

			//Основная функция
			while ((k < m) && (l != n) && (k != m)) {
				if (tolower(t[k]) == tolower(a[l])) {
					k++;
					l++;
					if (l == n) {
						cout << "Success!" << endl;
					}
					else if (k == m) {
						cout << "Failure!" << endl;
					}
				}
				else if ((tolower(t[k]) != tolower(a[l])) && (l != 0)) {
					l = pi[l - 1];
				}
				else if ((tolower(t[k]) != tolower(a[l])) && (l == 0)) {
					k++;
					if (k == m) {
						cout << "Failure!" << endl;
					}
				}
				counter[0]++;
			}
		}
		break;
	}
	}

	cout << endl;
	//Алгоритм прямого поиска
	cout << "Broutforce search" << endl;
	if (y == 2) { //Без учет регистра
		for (i = 0; i < n; i++) {
			a[i] = tolower(a[i]);
		}
		for (i = 0; i < m; i++) {
			t[i] = tolower(t[i]);
		}
	}

	k = 0; //Символ строки
	l = 0; //Символ образа
	int f = 0;

	//Основная часть
	while ((k < m) && (l != n) && (k != m)) {
		if (t[k] == a[l]) {
			k++;
			l++;
			if (l == n) {
				cout << "Success!" << endl;
			}
			else if (k == m) {
				cout << "Failure!" << endl;
			}
		}
		else if ((t[k] != a[l]) && (l != 0)) {
			l = 0;
			k = f;
			f++;
		}
		else if ((t[k] != a[l]) && (l == 0)) {
			k++;
			if (k == m) {
				cout << "Failure!" << endl;
			}
		}
		counter[1]++;
	}

	cout << endl;
	//Упражнение №2
	cout << "Boyer-Mur algorithm" << endl;
	//Алгоритм Бойера-Мура

	//Составление таблицы

	int char_ascii[ALF_CHAR];

	for (i = 0; i < ALF_CHAR; i++)
	{
		char_ascii[i] = n;
	}

	f = 1;
	for (i = n - 2; i >= 0; i--)
	{
		if (char_ascii[(int)a[i]] == n) {
			char_ascii[(int)a[i]] = f;
		}
		f++;
	}

	//Основная часть
	k = n - 1; //Символ строки
	l = n - 1; //Символ образа
	f = k;

	while ((k <= m) && (l >= 0)) {
		if (t[k] == a[l]) {
			f = k;
			k--;
			l--;
			if (l < 0) {
				cout << "Success!" << endl;
			}
		}
		else if ((t[k] != a[l]) && (l != n - 1)) {
			l = n - 1;
			k = f + char_ascii[(int)t[f]];
		}
		else if ((t[k] != a[l]) && (l == n - 1)) {
			k = k + char_ascii[(int)t[k]];
			if (k > m) {
				cout << "Failure!" << endl;
			}
		}
		counter[3]++;
	}

	cout << endl;
	//Упражнение №4 и №5
	cout << "Iteratins compare" << endl;

	int max;
	for (i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (counter[j] > counter[j + 1]) {
				max = counter[j];
			}
		}
	}

	if (max == counter[0]) {
		cout << "Brute Force is the fastest" << endl;
	}
	else if ((max == counter[1]) && (max == counter[3])) {
		cout << "Boyer-Mur and Knut-Morris-Pratt is the fastest" << endl;
	}
	else if (max == counter[3]) {
		cout << "Boyer-Mur is the fastest" << endl;
	}
	else if (max == counter[1]) {
		cout << "Knut-Morris-Pratt is the fastest" << endl;
	}

}