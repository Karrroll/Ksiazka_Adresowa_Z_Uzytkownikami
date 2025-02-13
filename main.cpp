#include <iostream>
#include <string>
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

string wczytajTekstDozwoloneZnaki(const string &komentarz) {
    string tekst = "";

    while(true) {
        cout << komentarz;
        tekst = wczytajTekst();

        if(tekst.find("|") != string::npos)
            cout << endl << "Nie mozna uzywac znaku '|'. Sprobuj ponownie!" << endl;
        else if((tekst.front() == ' ') || (tekst.back() == ' '))
            cout << endl << "Pierwszy oraz ostatni znak nie moga byc spacja" << endl;
        else
            return tekst;
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

auto znajdzUzytkownikaPoId(vector <Uzytkownik> &uzytkownicy, const int numerId) {
    for (auto itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++) {
        if(itr->idUzytkownika == numerId)
            return itr;
    }
    return uzytkownicy.end();
}

Uzytkownik przypiszDaneUzytkownikowi(const string &odczytywanaLinia) {
    int licznikPionowychKresek = 0;
    string daneUzytkownika = "";
    Uzytkownik wczytywanyUzytkownik;

    for(char znak : odczytywanaLinia) {
        if(znak != '|') {
            daneUzytkownika.push_back(znak);
        } else {
            licznikPionowychKresek++;
            switch(licznikPionowychKresek) {
                case 1: wczytywanyUzytkownik.idUzytkownika = stoi(daneUzytkownika);     break;
                case 2: wczytywanyUzytkownik.loginUzytkownika = daneUzytkownika;        break;
                case 3: wczytywanyUzytkownik.hasloUzytkownika = daneUzytkownika;        break;
                default:
                cout << "Blad wczytywania. Dane Uzytkownika nie moga zawierac znaku '|'. Ksiazka Adresowa zostanie zamknieta!" << endl;
                wstrzymajProgram();
                exit(1);
            }
            daneUzytkownika.clear();
        }
    }
    return wczytywanyUzytkownik;
}

string zamienDaneUzytkownikaNaTekst(const Uzytkownik &wskazanyUzytkownik) {
    string daneUzytkownika = "";

    daneUzytkownika += (to_string(wskazanyUzytkownik.idUzytkownika) + "|");
    daneUzytkownika += (wskazanyUzytkownik.loginUzytkownika + "|");
    daneUzytkownika += (wskazanyUzytkownik.hasloUzytkownika + "|");

    return daneUzytkownika;
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

bool zastapPlikTekstowy(const string &nazwaPlikuPrzedZmianami, const string &nazwaPlikuPoZmianach) {

    if (remove(nazwaPlikuPrzedZmianami.c_str()) == 0 && rename(nazwaPlikuPoZmianach.c_str(), nazwaPlikuPrzedZmianami.c_str()) == 0) {
        return true;
    } else {
        cout << "Blad podczas nadpisywania pliku tekstowego." << endl;
        return false;
    }
}

bool zaktualizujPlikZUzytkownikami(const Uzytkownik &modyfikowanyUzytkownik) {
    string wczytanaLinia = "", daneUzytkownikaJednaLinia = "";
    fstream oryginalnyPlik, zaktualizowanyPlik;
    Uzytkownik wczytanyUzytkownik;

    oryginalnyPlik.open("Uzytkownicy.txt", ios::in);
    zaktualizowanyPlik.open("Uzytkownicy_TYMCZASOWY.txt", ios::out | ios::app);

    if(oryginalnyPlik.good() && zaktualizowanyPlik.good()) {

        while(getline(oryginalnyPlik, wczytanaLinia)) {
            wczytanyUzytkownik = przypiszDaneUzytkownikowi(wczytanaLinia);

            if(modyfikowanyUzytkownik.idUzytkownika != wczytanyUzytkownik.idUzytkownika)
                zaktualizowanyPlik << wczytanaLinia << endl;
            else {
                daneUzytkownikaJednaLinia = zamienDaneUzytkownikaNaTekst(modyfikowanyUzytkownik);
                zaktualizowanyPlik << daneUzytkownikaJednaLinia << endl;
            }

        }
        oryginalnyPlik.close();
        zaktualizowanyPlik.close();

        if(zastapPlikTekstowy("Uzytkownicy.txt", "Uzytkownicy_TYMCZASOWY.txt"))
            return true;
    }

    return false;
}

string wprowadzNoweHaslo(const string &stareHaslo) {
    string noweHaslo = "", potwierdzNoweHaslo = "";

    while(true) {
        system("cls");
        noweHaslo = wczytajTekstDozwoloneZnaki("Wpisz nowe haslo: ");

        if(noweHaslo != stareHaslo) {
            cout << "Potwierdz nowe haslo: ";
            potwierdzNoweHaslo = wczytajTekst();

            if(noweHaslo == potwierdzNoweHaslo)
                return noweHaslo;
            else
                cout << endl<< "Wpisane hasla roznia sie! Sprobuj ponownie!" << endl;

        } else
            cout << endl<< "Wpisane haslo jest takie samo!" << endl;

        wstrzymajProgram();
    }
}

void zmienHaslo(vector <Uzytkownik> &uzytkownicy, const int idUzytkownikaZmieniajacegoHaslo) {
    system("cls");
    int liczbaProbLogowania = 3;
    string haslo;
    vector <Uzytkownik> :: iterator uzytkownikZmieniajacyHaslo;
    Uzytkownik uzytkownikZmieniajacyHasloKopia;

    cout << "\t< ZMIEN HASLO >" << endl;
    cout << "-------------------------------" << endl << endl;

    uzytkownikZmieniajacyHaslo = znajdzUzytkownikaPoId(uzytkownicy, idUzytkownikaZmieniajacegoHaslo);

    if(uzytkownikZmieniajacyHaslo != uzytkownicy.end()) {
        uzytkownikZmieniajacyHasloKopia = *uzytkownikZmieniajacyHaslo;

        while(liczbaProbLogowania > 0) {
            cout << "Wpisz aktualne haslo: ";
            haslo = wczytajTekst();

            if(haslo == uzytkownikZmieniajacyHasloKopia.hasloUzytkownika) {
                uzytkownikZmieniajacyHasloKopia.hasloUzytkownika = wprowadzNoweHaslo(haslo);

                if(zaktualizujPlikZUzytkownikami(uzytkownikZmieniajacyHasloKopia)) {
                    *uzytkownikZmieniajacyHaslo = uzytkownikZmieniajacyHasloKopia;
                    cout << endl << "Haslo zostalo zmienione!" << endl;
                    break;
                } else
                    break;

            } else
                cout << "Nieprawidlowe haslo! Pozostalo prob: " << --liczbaProbLogowania << endl << endl;
        }
    } else
        cout << endl << "Nie znaleziono uzytkownika!" << endl;

    wstrzymajProgram();
}

void wyloguj()    {
}

int main() {
    cout << "Podaj ID: ";
    int idZalogowanegoUzytkownika = 1;                                      // Podaj ID ktore docelowo bedzie podawala aplikacja
    vector <Uzytkownik> uzytkownicy;

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
                zmienHaslo(uzytkownicy, idZalogowanegoUzytkownika);
                break;
            case 9:
                wyloguj();
                break;
            default:
                cout << endl << "Nieprawidlowy wybor! Sprobuj ponownie." << endl;
                wstrzymajProgram();
        }
    }
    return 0;
}
