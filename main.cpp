#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>

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

auto znajdzAdresataPoId(vector <Adresat> &adresaci, const int numerId) {
    for (auto itr = adresaci.begin(); itr != adresaci.end(); itr++) {
        if (itr->idAdresata == numerId)
            return itr;
    }
    return adresaci.end();
}

Adresat przypiszDaneAdresatowi(const string &odczytywanaLinia) {
    int licznikPionowychKresek = 0;
    Adresat wczytywanyAdresat;
    string daneUzytkownika = "";

    for(char znak : odczytywanaLinia) {
        if(znak != '|') {
            daneUzytkownika.push_back(znak);
        } else {
            licznikPionowychKresek++;
            switch(licznikPionowychKresek) {
                case 1:     wczytywanyAdresat.idAdresata = stoi(daneUzytkownika);                   break;
                case 2:     wczytywanyAdresat.idPrzypisanegoUzytkownika = stoi(daneUzytkownika);    break;
                case 3:     wczytywanyAdresat.imie = daneUzytkownika;                               break;
                case 4:     wczytywanyAdresat.nazwisko = daneUzytkownika;                           break;
                case 5:     wczytywanyAdresat.numerTelefonu = daneUzytkownika;                      break;
                case 6:     wczytywanyAdresat.adres = daneUzytkownika;                              break;
                case 7:     wczytywanyAdresat.email = daneUzytkownika;                              break;
                default:
                    cout << "Blad wczytywania. Dane Adresata nie moga zawierac znaku '|'. Ksiazka Adresowa zostanie zamknieta!" << endl;
                    wstrzymajProgram();
                    exit(1);
            }
            daneUzytkownika.clear();
        }
    }
    return wczytywanyAdresat;
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

bool zastapPlikTekstowy(const string &nazwaPlikuPrzedZmianami, const string &nazwaPlikuPoZmianach) {

    if (remove(nazwaPlikuPrzedZmianami.c_str()) == 0 && rename(nazwaPlikuPoZmianach.c_str(), nazwaPlikuPrzedZmianami.c_str()) == 0) {
        return true;
    } else {
        cout << "Blad podczas nadpisywania pliku tekstowego." << endl;
        return false;
    }
}

bool zaktualizujPlikZAdresatami(const Adresat &modyfikowanyAdresat, const string &kryterium) {
    string wczytanaLinia = "";
    fstream oryginalnyPlik, zaktualizowanyPlik;
    Adresat wczytanyAdresat;

    oryginalnyPlik.open("Adresaci.txt", ios::in);
    zaktualizowanyPlik.open("Adresaci_TYMCZASOWY.txt", ios::out | ios::app);

    if (oryginalnyPlik.good() && zaktualizowanyPlik.good()) {

        while(getline(oryginalnyPlik, wczytanaLinia)) {
            wczytanyAdresat = przypiszDaneAdresatowi(wczytanaLinia);

            if(wczytanyAdresat.idAdresata != modyfikowanyAdresat.idAdresata)
                zaktualizowanyPlik << wczytanaLinia << endl;
            else if(wczytanyAdresat.idAdresata == modyfikowanyAdresat.idAdresata && kryterium == "USUN")
                continue;

        }
        oryginalnyPlik.close();
        zaktualizowanyPlik.close();

        if(zastapPlikTekstowy("Adresaci.txt", "Adresaci_TYMCZASOWY.txt"))
            return true;
    }

    return false;
}

void usunWybranegoAdresata(vector <Adresat> &adresaci, const vector <Adresat> :: iterator &adresatDoUsuniecia) {
    char znak;
    Adresat adresataDoUsunieciaKopia;

    cout << "Czy napewno chcesz usunac wybranego Adresata?(t/n): ";
    while (true) {
        znak = wczytajZnak();
        switch(znak) {
            case 't':
                adresataDoUsunieciaKopia = *adresatDoUsuniecia;

                if(zaktualizujPlikZAdresatami(adresataDoUsunieciaKopia, "USUN")) {
                    adresaci.erase(adresatDoUsuniecia);
                    cout << endl << "Wybrany adresat zostal usuniety!" << endl;
                }
                return;
            case 'n':
                cout << endl << "Wybrany adresat NIE zostal usuniety!" << endl;
                return;
            default:
                cout << endl << "Wpisz t lub n!: ";
        }
    }
}

void usunAdresata(vector <Adresat> &adresaci) {
    system("cls");
    int numerId = 0;
    vector <Adresat> :: iterator adresatDoUsuniecia;

    cout << "\t< USUN ADRESATA >" << endl;
    cout << "---------------------------------" << endl << endl;

    if (!adresaci.empty()) {
        cout << "Wprowadz numer ID adresata do usuniecia:\t";
        numerId = wczytajLiczbe();

        adresatDoUsuniecia = znajdzAdresataPoId(adresaci, numerId);

        if(adresatDoUsuniecia != adresaci.end()) {
            cout << endl << "Wybrany adresat:" << endl;
            wyswietlDaneAdresata(adresatDoUsuniecia);

            usunWybranegoAdresata(adresaci, adresatDoUsuniecia);
        } else
            cout << endl << "Nie znaleziono adresata o takim numerze ID!" << endl;
    } else
        cout << "Ksiazka Adresowa jest pusta!" << endl << endl;

    wstrzymajProgram();
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
                usunAdresata(adresaci);
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
