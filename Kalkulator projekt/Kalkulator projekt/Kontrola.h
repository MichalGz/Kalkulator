#include <map>
#include <string>
#ifndef KONTROLA_H
#define KONTROLA_H
using std::map;
using std::string;
map<string, string> odczyt(string sciezka);
string usun_spacje(string a);
string zmien_litere(string s);
bool kontrola(string b);
string pokaz(string& d);
string podmien(string wyrazenie, map<string, string>dane);
string przecinki(string f);
bool literki(string g);
string nawiasy(string h);
bool sprawdzenie(string c);
bool sprawdzenie_cyfra_przed_nawiasem(string c);
bool sprawdzenie_z_nawiasami(string c);
bool sprawdzenie_ujemna(string c);
string kalkulator(string c);
string wynik(string pl, string dl, char z);
void do_pliku(map<string, string> kontener, string sciezka);

#endif

