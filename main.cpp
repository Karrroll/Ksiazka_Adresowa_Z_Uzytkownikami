#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string wczytajTekst() {
    string tekst = "";

    while(true) {
        getline(cin, tekst);
        if(tekst.empty())
            cout << "Pole nie moze byc puste!" << endl;
        else
            return tekst;
    }
}

char wczytajZnak() {
    char wczytanyZnak = '0';
    string wejscie = "";

    while(true) {
        wejscie = wczytajTekst();

        if(wejscie.length() == 1) {
            wczytanyZnak = wejscie[0];
            return wczytanyZnak;
        } else
            cout << endl << "To nie jest pojedynczy znak! Wpisz ponownie: ";
    }
}

int wczytajLiczbe() {
    int liczba = 0;
    string wejscie = "";

    while(true)    {
        wejscie = wczytajTekst();
        stringstream mojStrumien(wejscie);

        if(mojStrumien >> liczba)
            return liczba;
        else
            cout << "To nie jest liczba. Wpisz ponownie!: ";
    }
}

void wstrzymajProgram() {
    cout << "Wcisnij Enter, aby kontynuowac...";
    cin.get();
}

void wyswietlMenuUzytkownika() {
    system("cls");
    cout << "\t< MENU UZYTKOWNIKA >"                                << endl;
    cout << "------------------------------------"                  << endl;
    cout << "1. Dodaj adresata do ksiazki adresowej"                << endl;
    cout << "2. Wyszukaj adresata po imieniu"                       << endl;
    cout << "3. Wyszukaj adresata po nazwisku"                      << endl;
    cout << "4. Wyswietl wszystkich adresatow z ksiazki adresowej"  << endl;
    cout << "5. Edytuj wybranego adresata"                          << endl;
    cout << "6. Usun wybranego adresata"                            << endl;
    cout << "------------------------------------"                  << endl;
    cout << "8. Zmien haslo"                                        << endl;
    cout << "9. Wyloguj"                                            << endl;
    cout << "------------------------------------"                  << endl;
    cout << "Wybierz jedna z opcji:\t";
}

void dodajAdresata()    {
}

void wyszukajAdresataPoImieniu()    {
}

void wyszukajAdresataPoNazwisku()    {
}

void wyswietlWszystkichAdresatow()    {
}

void edytujAdresata()    {
}

void usunAdresata()    {
}

void zmienHaslo()    {
}

void wyloguj(int &idZalogowanegoUzytkownika) {
    idZalogowanegoUzytkownika = 0;

    cout << endl << "Zostales wylogowany!" << endl;
    wstrzymajProgram();
}

int main() {
    cout << "Podaj ID: ";
    int idZalogowanegoUzytkownika = 1;                      // Podaj Id ktore docolowo bedzie podawala aplikacja

    while(true)    {
        wyswietlMenuUzytkownika();
        char wyborUzytkownika = wczytajLiczbe();

        switch (wyborUzytkownika) {
            case 1:
                dodajAdresata();
                break;
            case 2:
                wyszukajAdresataPoImieniu();
                break;
            case 3:
                wyszukajAdresataPoNazwisku();
                break;
            case 4:
                wyswietlWszystkichAdresatow();
                break;
            case 5:
                edytujAdresata();
                break;
            case 6:
                usunAdresata();
                break;
            case 8:
                zmienHaslo();
                break;
            case 9:
                wyloguj(idZalogowanegoUzytkownika);
                break;
            default:
                cout << endl << "Nieprawidlowy wybor! Sprobuj ponownie." << endl;
                wstrzymajProgram();
        }
    }
    return 0;
}
