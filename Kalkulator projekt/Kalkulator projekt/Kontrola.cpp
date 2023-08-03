#include "Kontrola.h"
#include <fstream>
#include <iostream>
#include <stack>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

map<string, string> odczyt(string sciezka)          //zdefiniowanie kontenera i funkcji do odczytywania z pliku tekstowego
{
	map<string, string> zapis;						// kontener
	ifstream file;
	string data;
	string klucz;
	string wartosc;
	int x;

	file.open(sciezka);						//otwierania z pliku
	if (file.is_open())						// jeśli plik jest w folderze to go wyświetl
	{
		while (!file.eof())
		{
			getline(file, data);
			x = data.find(';');
			klucz = data.substr(0, x);
			data.erase(0, x + 1);
			wartosc = data;
			zapis[klucz] = wartosc;
		}
	}
	else
	{
		cout << "Nie udało się otworzyć" << endl;				//jesli nie ma podanego pliku to wyswietl komunikat
	}
	file.close();												// zamknij plik

	return zapis;												// zwroc wartosc do pliku
}

string usun_spacje(string a)									// usuwa spacje z rownania
{
	int i = 0;
	while (a.size() > i)			
	{
		if (a[i] == ' ') a.erase(i, 1);							// jesli napotka spacje to ją usuwa
		else i++;												// jeśli nie to program idzie dalej, przechodzi do następnego znaku,liczby itp.
	}

	return a;													// zwraca 
}

string zmien_litere(string s)									// zmienia małą litere na dużą
{
	for (int i = 0; i < s.size(); i++)
		if (s[i] >= 'a' && s[i] <= 'z') s[i] -= 32;				// jesli napotka małą litere od a do z w kodzie ASCII to zamienia to na dużą litere

	return s;
}

bool kontrola(string b)											// sprawdza poprawność zapisanych danych w zmiennej magazyn
{
	if (b.find('=') == -1)										// sprawdza poprawnosc czy =
	{
		cout << "Bledne dane, wprowadz dane typu M4=..." << endl;
		return true;
	}
	else
	{
		if (b[0] >= 'A' && b[0] <= 'Z')							// sprawdza poprawność zapisu (na pierwszym miejscu duża litera)
		{
			for (int i = 1; i < b.find('='); i++)
			{
				if (b[i] <= '0' || b[i] >= '9')					// sprawdza czy na miejscu przed = znajduje się liczba
				{
					cout << "Bledne dane, wprowadz dane typu M4=... " << endl;			//jesli nie to wyswietl komunikat
					return true;
				}
			}
		}
		else
		{
			cout << "Bledne dane, wprowadz dane typu M4=..." << endl;
			return true;
		}
	}

	return false;
}

bool podwojny(string c)
{
	for (int i = c.find('='); i < c.size(); i++)
		if (c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/' || c[i] == '^') return false;			// sprawdza dopuszczalne działania kalkulatora

	return true;
}

string pokaz(string& d)									
{
	string e;
	e = d.substr(0, d.find("="));
	d.erase(0, d.find('=') + 1);

	return e;
}

string podmien(string wyrazenie, map<string, string> dane)
{
	size_t pozycja;
	for (auto dane_ : dane)
	{
		pozycja = wyrazenie.find(dane_.first);
		if (pozycja != -1)
		{
			wyrazenie.erase(pozycja, 2);
			wyrazenie.insert(pozycja, dane_.second);
		}
	}

	return wyrazenie;
}

string przecinki(string f)					// jeśli uzytkownik wprowadza przecinek to go usuwa i wstawia kropke (notacja amerykańska, zabezpieczenie przy liczbach typu double)
{
	for (int i = 0; i < f.size(); i++)
	{
		if (f[i] == ',')
		{
			f.erase(i, 1);
			f.insert(i, ".");
		}
	}
	return f;
}

bool literki(string g)
{
	for (int i = 0; i < g.size(); i++)
	{
		if (g[i] >= 'A' && g[i] <= 'Z')
		{
			cout << "Brak wszystkich danych" << endl;
			return false;
		}
	}

	return true;
}

string nawiasy(string h)
{
	int i = 0;
	int pozycja;
	stack<int>poczatek_nawiasu;
	string c_kalkulator;
	while (h.size() > i)
	{
		if (h[i] == '(')
		{
			poczatek_nawiasu.push(i);
		}
		else if (h[i] == ')')
		{
			pozycja = poczatek_nawiasu.top();
			poczatek_nawiasu.pop();
			c_kalkulator = kalkulator(h.substr(pozycja + 1, i - pozycja - 1));
			//Czemu tu też musi być handler?
			if (c_kalkulator.find("error") != -1) return "error";
			h.erase(pozycja, i - pozycja + 1);
			h.insert(pozycja, c_kalkulator);
			i = pozycja + c_kalkulator.size() - 1;
		}
		i++;
	}
	if (!poczatek_nawiasu.empty()) {
		cout << "Nie wszystkie nawiasy zostaly domkniete" << endl;
		return "error";
	}
	return h;
}

bool sprawdzenie(string c)
{
	for (int i = 0; i < c.size(); i++)							// sprawdza czy w rownaniu zawarte są jedynie znaki działań, kropki, nawiasy i liczby
	{															// jeśli nie zwraca komunikat
		if (c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/' || c[i] == '^' || c[i] == '.') continue;
		if (c[i] == '(' || c[i] == ')' || c[i] == '[' || c[i] == ']') continue;
		if (c[i] >= '0' && c[i] <= '9') continue;
		cout << "Blad wprowadzenia danych - cos innego niz znaki i liczby lub brak zawartosci wszystkich wywolanych komorek " << endl;
		return true;
	}

	return false;
}

bool sprawdzenie_cyfra_przed_nawiasem(string c)
{
	if ((c[0] == '+' || c[0] == '-' || c[0] == '*' || c[0] == '/' || c[0] == '^'))
	{
		cout << "Wprowadzono dane w formie niedozwolonej np.: A4=-2 --> A4=[-2]" << endl;
		return true;
	}
	if ((c[c.size() - 1] == '+' || c[c.size() - 1] == '-' || c[c.size() - 1] == '*' || c[c.size() - 1] == '/' || c[c.size() - 1] == '^'))
	{
		cout << "Wprowadzono dane w formie niedozwolonej np.: A4=2- --> A4=2" << endl;
		return true;
	}
	for (int i = 1; i < c.size(); i++)
	{
		if (c[i] == '+' || c[i] == '-' || c[i] == '*' || c[i] == '/' || c[i] == '^')
		{
			if (c[i - 1] >= '0' && c[i - 1] <= '9') continue;
			if (c[i - 1] == ')' || c[i - 1] == ']') continue;
			if (c[i] == '-' && c[i - 1] == '[') continue;
			cout << "Wprowadzono dane w formie niedozwolonej np.: 7+(-2+2) --> 7+([-2]+2)" << endl;
			return true;
		}
	}

	return false;
}

bool sprawdzenie_z_nawiasami(string c)
{
	for (int i = 1; i < c.size(); i++)
	{
		if (c[i] == ')')
		{
			if (c[i - 1] == ')' || c[i - 1] <= ']') continue;
			if (c[i - 1] >= '0' && c[i - 1] <= '9') continue;
			cout << "Przed zamknieciem nawiasu znajduje sie niedozwolony znak np.: -)" << endl;
			return true;
		}
	}

	return false;
}

bool sprawdzenie_ujemna(string c)
{
	bool znak = false; //Przechowuje informacje o natrafieniu na '[' - czyli zapis liczby ujemnej
	for (int i = 1; i < c.size(); i++) {
		if (znak) {
			if (c[i] >= '0' && c[i] <= '9') continue;
			//Znowu brak obslugi zmiennoprzecinkowych
			if (c[i] == '.') continue;
			if (c[i] == ']')
			{
				znak = false;
				continue;
			}
			cout << "Nieprawidlowe wprowadzenie liczby ujemnej - w [] nie znajduje sie tylko liczba --> [-1]" << c[i] << endl;
			return true;
		}
		if (c[i] == '[') {
			znak = true;
			i++;
			if (c[i] == '-') continue;
			cout << "Nieprawidlowe wprowadzenie liczby ujemnej - nie wprowadzono '-' --> [-1]" << endl;
			return true;
		}
	}
	return false;
}

string kalkulator(string dzialanie)
{
	string dana = {};
	vector<string>licz, licz_2;
	vector<char>znaki, znaki_2;
	char znak = '0';
	//Wyłuskanie ze string wektora znaków i liczb
	for (int i = 0; i < dzialanie.size(); i++)
	{
		if (dzialanie[i] == '[')
		{
			i++;
			//Step by step - czyli co jeśli [-[-2]] --> --2
			//Handler:
			if (dana[0] == '-') {
				dana = {};
				continue;
			}
			dana += dzialanie[i];

		}
		else if (dzialanie[i] >= 48 && dzialanie[i] <= 57 || dzialanie[i] == '.')
		{
			dana += dzialanie[i];
		}
		else if (dzialanie[i] == '*' || dzialanie[i] == '+' || dzialanie[i] == '-' || dzialanie[i] == '/' || dzialanie[i] == '^')
		{
			znak = dzialanie[i];
			licz.push_back(dana);
			znaki.push_back(znak);
			dana = {};
			znak = '0';
		}
	}
	licz.push_back(dana);

	bool spr = true;
	bool spr_2 = false;

	//Exception handler - czyli co jak zostało nam po nawiasach np.: 5
	if (licz.size() == 1) return licz[0];
	//Kalkulator mnożenia, dzielenia i potęgowania
	for (int i = 0; i < licz.size() - 1; i++)
	{
		if (znaki[i] == '/' || znaki[i] == '*' || znaki[i] == '^')
		{
			if (spr == true)
			{
				dana = wynik(licz[i], licz[i + 1], znaki[i]);
				spr = false;
			}
			else
				dana = wynik(dana, licz[i + 1], znaki[i]);
			//Obsluga bledu dzielenia przez 0
			if (dana == "error") return "error";

			spr_2 = true;
		}
		else
		{
			if (spr_2 == true)
			{
				licz_2.push_back(dana);
				spr_2 = false;
			}
			else
				licz_2.push_back(licz[i]);

			znaki_2.push_back(znaki[i]);
			spr = true;
		}
	}

	if (spr_2 == true)
		licz_2.push_back(dana);
	else
		licz_2.push_back(licz[licz.size() - 1]);
	//Co jeśli jedynymi operacjami było mnożenie, dzielenie i potęgowanie? 
	//Handler:
	if (licz_2.size() == 1) return licz_2[0];
	dana = wynik(licz_2[0], licz_2[1], znaki_2[0]);
	for (int i = 1; i < licz_2.size() - 1; i++)
		dana = wynik(dana, licz_2[i + 1], znaki_2[i]);

	return (dana);
}

string wynik(string pl, string dl, char z)
{
	double pl_, dl_;
	pl_ = stod(pl);							// konwertuje ze string na double
	dl_ = stod(dl);
	if (z == '*') return to_string(pl_ * dl_);
	else if (z == '+') return to_string(pl_ + dl_);						// wypisuje wynik danego działania
	else if (z == '-') return to_string(pl_ - dl_);
	else if (z == '^') return to_string(pow(pl_, dl_));
	else {
		if (dl_ == 0) {
			cout << "Nie dzielimy przez 0" << endl;							// kontrola blędu przy dzieleniu przez 0
			return "error"; //Tu trzeba było zmienić kod błędu
		}
		return to_string(pl_ / dl_);
	}
}
void do_pliku(map<string, string>kontener, string sciezka)
{
	ofstream file;
	file.open(sciezka);
	if (file.is_open())
	{
		for (auto element : kontener) file << element.first << ";" << element.second << endl;
	}
	file.close();
	return;
}