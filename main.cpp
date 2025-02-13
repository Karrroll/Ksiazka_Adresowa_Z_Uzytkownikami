#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

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

string zamienDaneUzytkownikaNaTekst(const Uzytkownik &wskazanyUzytkownik) {
    string daneUzytkownika = "";

    daneUzytkownika += (to_string(wskazanyUzytkownik.idUzytkownika) + "|");
    daneUzytkownika += (wskazanyUzytkownik.loginUzytkownika + "|");
    daneUzytkownika += (wskazanyUzytkownik.hasloUzytkownika + "|");

    return daneUzytkownika;
}

bool dodajNowegoUzytkownikaDoPlikuTekstowego(const Uzytkownik &nowyUzytkownik) {
    string daneUzytkownikaJednaLinia = "";
    fstream plikListaUzytkownikow;

    plikListaUzytkownikow.open("Uzytkownicy.txt", ios::out | ios::app);

    if(plikListaUzytkownikow.good()) {
        daneUzytkownikaJednaLinia = zamienDaneUzytkownikaNaTekst(nowyUzytkownik);
        plikListaUzytkownikow << daneUzytkownikaJednaLinia << endl;

        cout << endl << "Uzytkownik " <<  nowyUzytkownik.loginUzytkownika << " zostal zarejestrowany pomyslnie" << endl;
        wstrzymajProgram();
        plikListaUzytkownikow.close();
        return true;
    } else {
        cout << "Rejestracja zakonczona niepowodzeniem!" << endl;
        wstrzymajProgram();
        return false;
    }
}

int wyznaczIdNowemuUzytkownikowi(const vector <Uzytkownik> &uzytkownicy) {
    if(uzytkownicy.empty())
        return 1;
    else
        return uzytkownicy.back().idUzytkownika + 1;
}

int pobierzIdUzytkownika(const vector <Uzytkownik> &uzytkownicy, const string &sprawdzanyLogin) {                               ///////// tttuuuutaj
    for(auto wczytanyUzytkownik : uzytkownicy) {
        if(wczytanyUzytkownik.loginUzytkownika == sprawdzanyLogin)
            return wczytanyUzytkownik.idUzytkownika;
    }
    return 0;
}

void zarejestrujNowegoUzytkownika(vector <Uzytkownik> &uzytkownicy) {
    system("cls");
    int idUzytkownika = 0;
    string loginNowegoUzytkownika = "";
    Uzytkownik nowyUzytkownik;

    cout << "REJESTRACJA" << endl;
    cout << "----------------------" << endl;

    cout << "Nazwa Uzytkownika: ";
    loginNowegoUzytkownika = wczytajTekst();

    idUzytkownika = pobierzIdUzytkownika(uzytkownicy, loginNowegoUzytkownika);

    if(idUzytkownika == 0) {
        nowyUzytkownik.idUzytkownika = wyznaczIdNowemuUzytkownikowi(uzytkownicy);
        nowyUzytkownik.loginUzytkownika = loginNowegoUzytkownika;

        cout << "Haslo: ";
        nowyUzytkownik.hasloUzytkownika = wczytajTekst();

        if(dodajNowegoUzytkownikaDoPlikuTekstowego(nowyUzytkownik))
            uzytkownicy.emplace_back(nowyUzytkownik);

    } else {
        cout << endl << "Nazwa Uzytkownika juz istnieje!" << endl;
        wstrzymajProgram();
    }
}

int main() {
    vector <Uzytkownik> uzytkownicy;

    while(1)    {
        int wyborUzytkownika = 0;

        wyswietlMenuGlowne();
        wyborUzytkownika = wczytajLiczbe();

        switch(wyborUzytkownika) {
            case 1: zalogujUzytkownika();                           break;
            case 2: zarejestrujNowegoUzytkownika(uzytkownicy);      break;
            case 3: exit(0);
            default:
                cout << endl << "Nieprawidlowy wybor!" << endl;
                wstrzymajProgram();
        }
    }
    return 0;
}
