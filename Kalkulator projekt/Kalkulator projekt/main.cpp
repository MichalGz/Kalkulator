#include <iostream> 
#include "Kontrola.h"

using namespace std;

int main(int argc, char* argv[])
{
    string magazyn;                             // przechowuje infromacje jak sie nazywa komórka do ktorej bedziemy pisac np. A5
    string rownanie;                            // przyjmujemy tu to co wpisze uzytkownik
    string path = argv[0];                      // sciezka do naszego pliku tekstowego
    map<string, string> program;                // przechowuje wartosci ktore sa zapisane w komorki
    if (int a = path.find("\\Debug\\Kalkulator_projekt.exe"))           // zmienia sciezke do pliku 
        path.erase(a + 1, path.size() - a);                             // 
    path += "Kalkulator.txt";                                           // dodanie pliku do sciezki (kalkulator plik tekstowy)
    program = odczyt(path);                         // do mapy program zapisuje wartosci komorek ktore zostaly zapisane w pliku tekstowym
    while (true)
    {
        cout << "Wprowadz dane: ";
        getline(cin, rownanie);
        if (rownanie == "exit") break;              // warunek wyjscia - podanie warunku exit konczy program
        rownanie = usun_spacje(rownanie);           // usuwanie spacje        
        rownanie = zmien_litere(rownanie);          // zmienia mala litere na duza
        if (kontrola(rownanie))  continue;          // sprawdza czy w pliku znajduja sie nieprzewidzane rzeczy (poprawnoœæ danych umieszczonych w zmiennej magazyn
        magazyn = rownanie.substr(0, 2);            // wyciaga nazwe komorki
        rownanie.erase(0, 3);                       // usuwa nazwe komorki i znak rownosci pozostawiajac samo rownanie
        rownanie = przecinki(rownanie);             // zamienia przecinki na kropki (notacja amerykanska) double nie odczytuje przecinka jako 11,5 zle 11.5 dobrze
        rownanie = podmien(rownanie, program);      // zmienia nazwy komorek na wartosci
        if (sprawdzenie(rownanie))  continue;       // sprawdza czy tylko dopuszczone operacje zosta³y umieszczone w programie
        if (sprawdzenie_cyfra_przed_nawiasem(rownanie))  continue;      // sprawdza poprawnosc zapisu np nie moze byc M3=2-
        if (sprawdzenie_z_nawiasami(rownanie)) continue;                // Przed zamknieciem nawiasu znajduje sie niedozwolony znak np.: -)
        if (sprawdzenie_ujemna(rownanie)) continue;                     // sprawdzenie poprawnosci zapisu liczby ujemnej [-2]
        rownanie = nawiasy(rownanie);                                   // rozwiazywanie rownania wewnatrz nawiasow
        if (rownanie == "error") continue;                              // kontrola bledu
        rownanie = kalkulator(rownanie);                                // rozwiazywanie calego rownania
        if (rownanie == "error") continue;                              // kontrola bledu
        //Ujemny wynik - handler
        if (rownanie[0] == '-') rownanie = '[' + rownanie + ']';        // jesli wynik jest ujemny to umieszcza go w []
        cout << magazyn << " = " <<  rownanie << endl;                  // wyswietlanie wyniku
        program[magazyn] = rownanie;                                    // umieszczanie wyniku w mapie
    }
    do_pliku(program, path);                                            // umieszczanie mapy w pliku
}