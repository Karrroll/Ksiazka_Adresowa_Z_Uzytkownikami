#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Uzytkownik {
    int idUzytkownika;
    string loginUzytkownika, hasloUzytkownika;

    Uzytkownik(int id = 0, string login = "", string haslo = "")
        : idUzytkownika(id), loginUzytkownika(login), hasloUzytkownika(haslo) {}
};

string wczytajTekst() {
    string tekst = "";

    cin.sync();
    getline(cin, tekst);

    return tekst;
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

void wyswietlMenuGlowne() {
    system("cls");
    cout << "\t< MENU GLOWNE >"                 << endl;
    cout << "-----------------------------"     << endl;
    cout << "1.LOGOWANIE"                       << endl;
    cout << "2.REJESTRACJA"                     << endl;
    cout << "3.ZAMKNIJ KSIAZKE ADRESOWA"        << endl;
    cout << "-----------------------------"     << endl;
    cout << "Wybierz jedna z opcji:\t";
}

void zalogujUzytkownika()    {

}

void zarejestrujNowegoUzytkownika() {

}

int main() {

    while(1)    {
        int wyborUzytkownika = 0;

        wyswietlMenuGlowne();
        wyborUzytkownika = wczytajLiczbe();

        switch(wyborUzytkownika) {
            case 1: zalogujUzytkownika();                break;
            case 2: zarejestrujNowegoUzytkownika();      break;
            case 3: exit(0);
            default:
                cout << endl << "Nieprawidlowy wybor!" << endl;
                wstrzymajProgram();
        }
    }
    return 0;
}
