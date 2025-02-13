#include <iostream>
#include <string>
#include <sstream>
#include <vector>

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

auto znajdzUzytkownikaPoId(vector <Uzytkownik> &uzytkownicy, const int numerId) {
    for (auto itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++) {
        if(itr->idUzytkownika == numerId)
            return itr;
    }
    return uzytkownicy.end();
}

int pobierzIdUzytkownika(const vector <Uzytkownik> &uzytkownicy, const string &sprawdzanyLogin) {                               ///////// tttuuuutaj
    for(auto wczytanyUzytkownik : uzytkownicy) {
        if(wczytanyUzytkownik.loginUzytkownika == sprawdzanyLogin)
            return wczytanyUzytkownik.idUzytkownika;
    }
    return 0;
}

bool wprowadzHasloDlaUzytkownika(const vector <Uzytkownik> :: iterator &wybranyUzytkownik) {
    int iloscProbLogowania = 3;
    string haslo = "";

    do {
        cout << "Haslo: ";
        haslo = wczytajTekst();

        if(wybranyUzytkownik->hasloUzytkownika == haslo) {
            cout << endl << "Uzytkownik " << wybranyUzytkownik->loginUzytkownika << " zalogowany!" << endl;
            wstrzymajProgram();
            return true;
        } else {
            cout << endl << "Niepoprawne haslo! Pozostalo prob: " << --iloscProbLogowania << endl;
            wstrzymajProgram();
            cout << endl;
        }
    }while(iloscProbLogowania > 0);

    return false;
}

int zalogujUzytkownika(vector <Uzytkownik> &uzytkownicy) {
    system("cls");
    int idUzytkownika = 0;
    string login = "";
    vector <Uzytkownik> :: iterator znalezionyUzytkownik;

    cout << "LOGOWANIE" << endl;
    cout << "----------------------" << endl;

    cout << "Nazwa Uzytkownika: ";
    login = wczytajTekst();

    idUzytkownika = pobierzIdUzytkownika(uzytkownicy, login);

    if(idUzytkownika != 0) {
        znalezionyUzytkownik = znajdzUzytkownikaPoId(uzytkownicy, idUzytkownika);

        if(wprowadzHasloDlaUzytkownika(znalezionyUzytkownik))
            return idUzytkownika;
        else
            idUzytkownika = 0;

    } else {
        cout << endl << "Podany uzytkownik nie istnieje!" << endl;
        wstrzymajProgram();
    }
    return idUzytkownika;
}

void zarejestrujNowegoUzytkownika() {

}

int main() {
    int idZalogowanegoUzytkownika = 0;
    vector <Uzytkownik> uzytkownicy;
//Uzytkownik uzytkownik(5, "Karol", "Karol");               //TESTY
//uzytkownicy.push_back(uzytkownik);
    while(1) {
        int wyborUzytkownika = 0;

        wyswietlMenuGlowne();
        wyborUzytkownika = wczytajLiczbe();

        switch(wyborUzytkownika) {
            case 1: idZalogowanegoUzytkownika = zalogujUzytkownika(uzytkownicy);    break;
            case 2: zarejestrujNowegoUzytkownika();                                 break;
            case 3: exit(0);
            default:
                cout << endl << "Nieprawidlowy wybor!" << endl;
                wstrzymajProgram();
        }
//cout << idZalogowanegoUzytkownika << endl;                //TESTY
//wstrzymajProgram();
    }
    return 0;
}
