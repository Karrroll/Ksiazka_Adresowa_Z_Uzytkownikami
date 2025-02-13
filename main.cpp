#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Adresat {
    int idAdresata, idPrzypisanegoUzytkownika;
    string imie, nazwisko, numerTelefonu, adres, email;

    Adresat(int idAdresata = 0, int idUzytkownika = 0, string imie = "", string nazwisko = "", string telefon = "", string adres = "", string email = "")
        : idAdresata(idAdresata), idPrzypisanegoUzytkownika(idUzytkownika), imie(imie), nazwisko(nazwisko), numerTelefonu(telefon), adres(adres), email(email) {}
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

string ignorujWilkoscLiter(string &tekst) {
    transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
    return tekst;
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

void wyswietlDaneAdresata(const vector <Adresat> :: iterator &adresat) {
    cout << "Numer ID:\t\t"         << adresat->idAdresata                          << endl;
    cout << "Imie i Nazwisko:\t"    << adresat->imie << " " << adresat->nazwisko    << endl;
    cout << "nr. telefonu:\t\t"     << adresat->numerTelefonu                       << endl;
    cout << "Email:\t\t\t"          << adresat->email                               << endl;
    cout << "Adres:\t\t\t"          << adresat->adres                               << endl << endl;
}

void dodajAdresata()    {
}

void wypiszAdresatowWedlugKryterium(vector <Adresat> adresaci, string &szukanaWartosc, const string &kryterium) {
    bool znalezionyAdresat = false;
    string wartoscPorownywana = "";

    for(auto itr = adresaci.begin(); itr != adresaci.end(); itr++) {
        if(kryterium == "IMIE")
            wartoscPorownywana = itr->imie;
        else if(kryterium == "NAZWISKO")
            wartoscPorownywana = itr->nazwisko;

        if(ignorujWilkoscLiter(wartoscPorownywana) == ignorujWilkoscLiter(szukanaWartosc)) {
            wyswietlDaneAdresata(itr);
            znalezionyAdresat = true;
        }
    }
    if (znalezionyAdresat == false)
        cout << "Nie znaleziono adresata!" << endl;
}

void wyszukajAdresataPoImieniu(const vector <Adresat> &adresaci) {
    system("cls");
    string imieDoWyszukania = "";

    cout << "\t< WYSZUKAJ PO IMIENIU >" << endl;
    cout << "---------------------------------------" << endl;

    if (!adresaci.empty()) {
        cout << endl << "Wprowadz imie:\t\t";
        imieDoWyszukania = wczytajTekst();
        cout << endl;
        wypiszAdresatowWedlugKryterium(adresaci, imieDoWyszukania, "IMIE");
    } else {
        cout << endl << "Ksiazka Adresowa jest pusta!" << endl;
    }
    wstrzymajProgram();
}

void wyszukajAdresataPoNazwisku(const vector <Adresat> &adresaci) {
    system("cls");
    string nazwiskoDoWyszukania = "";

    cout << "\t< WYSZUKAJ PO NAZWISKU >" << endl;
    cout << "----------------------------------------" << endl;
    if (!adresaci.empty()) {
        cout << "Wprowadz nazwisko:\t\t";
        nazwiskoDoWyszukania = wczytajTekst();
        cout << endl;
        wypiszAdresatowWedlugKryterium(adresaci, nazwiskoDoWyszukania, "NAZWISKO");
    } else {
        cout << endl << "Ksiazka Adresowa jest pusta!" << endl;
    }
    wstrzymajProgram();
}

void wyswietlWszystkichAdresatow()    {
}

void edytujAdresata()    {
}

void usunAdresata()    {
}

void zmienHaslo()    {
}

void wyloguj()    {
}

int main() {
    vector <Adresat> adresaci;

    while(true)    {
        wyswietlMenuUzytkownika();
        char wyborUzytkownika = wczytajLiczbe();

        switch (wyborUzytkownika) {
            case 1:
                dodajAdresata();
                break;
            case 2:
                wyszukajAdresataPoImieniu(adresaci);
                break;
            case 3:
                wyszukajAdresataPoNazwisku(adresaci);
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
                wyloguj();
                break;
            default:
                cout << endl << "Nieprawidlowy wybor! Sprobuj ponownie." << endl;
                wstrzymajProgram();
        }
    }
    return 0;
}
