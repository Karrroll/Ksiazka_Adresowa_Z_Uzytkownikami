#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct Uzytkownik {
    int idUzytkownika;
    string loginUzytkownika, hasloUzytkownika;

    Uzytkownik(int id = 0, string login = "", string haslo = "")
        : idUzytkownika(id), loginUzytkownika(login), hasloUzytkownika(haslo) {}
};

struct Adresat {
    int idAdresata, idPrzypisanegoUzytkownika;
    string imie, nazwisko, numerTelefonu, adres, email;

    Adresat(int idAdresata = 0, int idUzytkownika = 0, string imie = "", string nazwisko = "", string telefon = "", string adres = "", string email = "")
        : idAdresata(idAdresata), idPrzypisanegoUzytkownika(idUzytkownika), imie(imie), nazwisko(nazwisko), numerTelefonu(telefon), adres(adres), email(email) {}

    bool operator == (const Adresat &porownaj) const {
        return (imie == porownaj.imie) && (nazwisko == porownaj.nazwisko) && (numerTelefonu == porownaj.numerTelefonu) && (adres == porownaj.adres) && (email == porownaj.email);
    }
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

string ignorujWilkoscLiter(string &tekst) {
    transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
    return tekst;
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

void wyswietlMenuEdycji() {
    cout << "Wybierz dane do edycji:\t"         << endl;
    cout << "1 - Imie"                          << endl;
    cout << "2 - Nazwisko"                      << endl;
    cout << "3 - Numer Telefonu"                << endl;
    cout << "4 - Email"                         << endl;
    cout << "5 - Adres"                         << endl;
    cout << "6 - Powrot do Menu Uzytkownika"    << endl << endl;
}

void wyswietlDaneAdresata(const vector <Adresat> :: iterator &adresat) {
    cout << "Numer ID:\t\t"         << adresat->idAdresata                          << endl;
    cout << "Imie i Nazwisko:\t"    << adresat->imie << " " << adresat->nazwisko    << endl;
    cout << "nr. telefonu:\t\t"     << adresat->numerTelefonu                       << endl;
    cout << "Email:\t\t\t"          << adresat->email                               << endl;
    cout << "Adres:\t\t\t"          << adresat->adres                               << endl << endl;
}

auto znajdzUzytkownikaPoId(vector <Uzytkownik> &uzytkownicy, const int numerId) {
    for (auto itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++) {
        if(itr->idUzytkownika == numerId)
            return itr;
    }
    return uzytkownicy.end();
}

auto znajdzAdresataPoId(vector <Adresat> &adresaci, const int numerId) {
    for (auto itr = adresaci.begin(); itr != adresaci.end(); itr++) {
        if (itr->idAdresata == numerId)
            return itr;
    }
    return adresaci.end();
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

void wczytajZarejestrowanychUzytkownikowDoWektora(vector <Uzytkownik> &uzytkownicy) {
    string wczytanaLinia = "";
    fstream plikListaUzytkownikow;
    Uzytkownik wczytanyUzytkownik;

    plikListaUzytkownikow.open("Uzytkownicy.txt", ios::in);

    if(plikListaUzytkownikow.good())    {
        while(getline(plikListaUzytkownikow, wczytanaLinia)) {
            wczytanyUzytkownik = przypiszDaneUzytkownikowi(wczytanaLinia);
            uzytkownicy.emplace_back(wczytanyUzytkownik);
        }
    }

    plikListaUzytkownikow.close();
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

void wczytajAdresatowUzytkownikaDoWektora(vector <Adresat> &adresaci, const int idUzytkownika) {
    string wczytanaLinia = "";
    fstream plikListaAdresatow;
    Adresat wczytanyAdresat;

    plikListaAdresatow.open("Adresaci.txt", ios::in);

    if (plikListaAdresatow.good()) {
        while (getline(plikListaAdresatow, wczytanaLinia)) {
            wczytanyAdresat = przypiszDaneAdresatowi(wczytanaLinia);

            if(idUzytkownika == wczytanyAdresat.idPrzypisanegoUzytkownika)
                adresaci.emplace_back(wczytanyAdresat);
        }
    }

    plikListaAdresatow.close();
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

int pobierzIdUzytkownika(const vector <Uzytkownik> &uzytkownicy, const string &sprawdzanyLogin) {                               ///////// tttuuuutaj
    for(auto wczytanyUzytkownik : uzytkownicy) {
        if(wczytanyUzytkownik.loginUzytkownika == sprawdzanyLogin)
            return wczytanyUzytkownik.idUzytkownika;
    }
    return 0;
}

int wyznaczIdNowemuUzytkownikowi(const vector <Uzytkownik> &uzytkownicy) {
    if(uzytkownicy.empty())
        return 1;
    else
        return uzytkownicy.back().idUzytkownika + 1;
}

void zarejestrujNowegoUzytkownika(vector <Uzytkownik> &uzytkownicy) {
    system("cls");
    int idUzytkownika = 0;
    string loginNowegoUzytkownika = "";
    Uzytkownik nowyUzytkownik;

    cout << "REJESTRACJA" << endl;
    cout << "----------------------" << endl;

    loginNowegoUzytkownika = wczytajTekstDozwoloneZnaki("Nazwa Uzytkownika: ");
    idUzytkownika = pobierzIdUzytkownika(uzytkownicy, loginNowegoUzytkownika);

    if(idUzytkownika == 0) {
        nowyUzytkownik.idUzytkownika = wyznaczIdNowemuUzytkownikowi(uzytkownicy);
        nowyUzytkownik.loginUzytkownika = loginNowegoUzytkownika;
        nowyUzytkownik.hasloUzytkownika = wczytajTekstDozwoloneZnaki("Haslo: ");

        if(dodajNowegoUzytkownikaDoPlikuTekstowego(nowyUzytkownik))
            uzytkownicy.emplace_back(nowyUzytkownik);

    } else {
        cout << endl << "Nazwa Uzytkownika juz istnieje!" << endl;
        wstrzymajProgram();
    }
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

bool czyAdresatJuzIstnieje(vector <Adresat> &adresaci, const Adresat &sprawdzanyAdresat) {

    for (vector <Adresat> :: iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
        if (itr->imie == sprawdzanyAdresat.imie && itr->nazwisko == sprawdzanyAdresat.nazwisko) {
            cout << endl << "Podany adresat juz istnieje!" << endl;
            wyswietlDaneAdresata(itr);
            wstrzymajProgram();
            return true;
        }
    }
    return false;
}

string daneAdresataJednaLinia(const Adresat &wybranyAdresat) {
    string daneAdresataTekst = "";

    daneAdresataTekst += (to_string(wybranyAdresat.idAdresata) + "|");
    daneAdresataTekst += (to_string(wybranyAdresat.idPrzypisanegoUzytkownika) + "|");
    daneAdresataTekst += (wybranyAdresat.imie + "|");
    daneAdresataTekst += (wybranyAdresat.nazwisko + "|");
    daneAdresataTekst += (wybranyAdresat.numerTelefonu + "|");
    daneAdresataTekst += (wybranyAdresat.email + "|");
    daneAdresataTekst += (wybranyAdresat.adres + "|");

    return daneAdresataTekst;
}

bool zapiszAdresataDoPlikuTekstowego(const Adresat &zapisywanyAdresat) {
    fstream plikListaAdresatow;

    plikListaAdresatow.open("Adresaci.txt", ios::out | ios::app);

    if (plikListaAdresatow.good()) {
        plikListaAdresatow << daneAdresataJednaLinia(zapisywanyAdresat) << endl;
        plikListaAdresatow.close();
        return true;
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        wstrzymajProgram();
        return false;
    }
}

Adresat wczytajDaneNowegoAdresata(const int idZalogowanegoUzytkownika, const int idOstatniegoAdresata) {
    system("cls");
    Adresat nowyAdresat;

    nowyAdresat.idAdresata = idOstatniegoAdresata + 1;
    nowyAdresat.idPrzypisanegoUzytkownika = idZalogowanegoUzytkownika;

    cout << "\t< DODAJ ADRESATA >" << endl;
    cout << "----------------------------------" << endl << endl;
    cout << "Numer ID adresata:\t\t" << nowyAdresat.idAdresata << endl;

    nowyAdresat.imie = wczytajTekstDozwoloneZnaki("Podaj imie:\t\t\t");
    nowyAdresat.nazwisko = wczytajTekstDozwoloneZnaki("Podaj nazwisko:\t\t\t");
    nowyAdresat.numerTelefonu = wczytajTekstDozwoloneZnaki("Podaj numer telefonu:\t\t");
    nowyAdresat.email = wczytajTekstDozwoloneZnaki("Podaj adres email:\t\t");
    nowyAdresat.adres = wczytajTekstDozwoloneZnaki("Podaj adres zamieszkania:\t\t");

    return nowyAdresat;
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

void wyswietlWszystkichAdresatow(vector <Adresat> &adresaci) {
    system("cls");
    cout << "\t< WSZYSCY ADRESACI >"                << endl;
    cout << "------------------------------------"  << endl;

    if (!adresaci.empty()) {
        cout << endl << "Liczba Adresatow: " << adresaci.size() << endl << endl;

        for (auto itr = adresaci.begin(); itr != adresaci.end(); itr++)
            wyswietlDaneAdresata(itr);

    } else {
        cout << endl << "Ksiazka adresowa jest pusta!" << endl;
    }
    wstrzymajProgram();
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
            else if(wczytanyAdresat.idAdresata == modyfikowanyAdresat.idAdresata && kryterium == "EDYTUJ")
                zaktualizowanyPlik << daneAdresataJednaLinia(modyfikowanyAdresat) << endl;
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

Adresat wprowadzZmianyEdycjaAdresata(const vector <Adresat> :: iterator oryginalnyAdresat, const int wybor) {
    string wprowadzanaZmiana = "";
    Adresat edytowanyAdresat = *oryginalnyAdresat;

    system("cls");
    wprowadzanaZmiana = wczytajTekstDozwoloneZnaki("Wprowadz zmiane:\t");

    switch (wybor) {
        case 1: edytowanyAdresat.imie = wprowadzanaZmiana;              break;
        case 2: edytowanyAdresat.nazwisko = wprowadzanaZmiana;          break;
        case 3: edytowanyAdresat.numerTelefonu = wprowadzanaZmiana;     break;
        case 4: edytowanyAdresat.email = wprowadzanaZmiana;             break;
        case 5: edytowanyAdresat.adres = wprowadzanaZmiana;             break;
    }

    return edytowanyAdresat;
}

Adresat edytujWybranegoAdresata(const vector <Adresat> :: iterator &oryginalnyAdresat) {
    int wyborUzytkownika = 0;
    Adresat edytowanyAdresat;

    cout << "Twoj wybor: ";
    wyborUzytkownika = wczytajLiczbe();

    while(true) {
        if(wyborUzytkownika == 6) {
            return *oryginalnyAdresat;
        } else if(wyborUzytkownika >= 0 && wyborUzytkownika <= 5) {
            edytowanyAdresat = wprowadzZmianyEdycjaAdresata(oryginalnyAdresat, wyborUzytkownika);

            if(edytowanyAdresat == *oryginalnyAdresat) {
                cout << endl << "Proponowana zmiana jest taka sama. Sprobuj ponownie." << endl;
                wstrzymajProgram();
            } else
                return edytowanyAdresat;

        } else
            cout << endl << "Niepoprawny wybor! Sprobuj ponownie." << endl;
    }
}

void edytujAdresata(vector <Adresat> &adresaci) {
    system("cls");
    int numerId = 0;
    vector <Adresat> :: iterator edytowanyAdresat;
    Adresat adresatPoEdycji;

    cout << "\t< EDYTUJ ADRESATA >" << endl;
    cout << "-----------------------------------" << endl << endl;

    if (!adresaci.empty()) {
        cout << "Wprowadz numer ID adresata do edycji:\t";
        numerId = wczytajLiczbe();

        edytowanyAdresat = znajdzAdresataPoId(adresaci, numerId);

        if(edytowanyAdresat != adresaci.end()) {
            cout << endl << "Wybrany adresat:" << endl;
            wyswietlDaneAdresata(edytowanyAdresat);

            wyswietlMenuEdycji();
            adresatPoEdycji = edytujWybranegoAdresata(edytowanyAdresat);

            if(adresatPoEdycji == *edytowanyAdresat) {
                return;
            } else {
                if(zaktualizujPlikZAdresatami(adresatPoEdycji, "EDYTUJ")) {
                    *edytowanyAdresat = adresatPoEdycji;
                    cout << endl << "Zapisano zmiany!" << endl;
                }
            }
        } else
            cout << endl << "Nie znaleziono adresata o takim numerze ID!" << endl;
    } else
        cout << "Ksiazka Adresowa jest pusta!" << endl;

    wstrzymajProgram();
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

void wyloguj(int &idZalogowanegoUzytkownika) {
    idZalogowanegoUzytkownika = 0;

    cout << endl << "Zostales wylogowany!" << endl;
    wstrzymajProgram();
}

int pobierzIdOstatniegoAdresata() {
    int idOstatniegoAdresata = 0;
    string wczytanaLinia = "", ostatniaLinia = "";
    fstream plikListaAdresatow;
    Adresat wczytanyAdresat;

    plikListaAdresatow.open("Adresaci.txt", ios::in);

    if (plikListaAdresatow.good()) {
        while (getline(plikListaAdresatow, wczytanaLinia)) {
            if(!wczytanaLinia.empty())
                ostatniaLinia = wczytanaLinia;
        }
        wczytanyAdresat = przypiszDaneAdresatowi(ostatniaLinia);
        idOstatniegoAdresata = wczytanyAdresat.idAdresata;
    }

    plikListaAdresatow.close();

    return idOstatniegoAdresata;
}

void dodajAdresata(vector <Adresat> &adresaci, const int idZalogowanegoUzytkownika) {
    int idOstatniegoAdresata = 0;
    Adresat nowyAdresat;

    idOstatniegoAdresata = pobierzIdOstatniegoAdresata();
    nowyAdresat = wczytajDaneNowegoAdresata(idZalogowanegoUzytkownika, idOstatniegoAdresata);

    if(!czyAdresatJuzIstnieje(adresaci, nowyAdresat)) {
        if(zapiszAdresataDoPlikuTekstowego(nowyAdresat)) {
            adresaci.emplace_back(nowyAdresat);
            cout << endl << "Adresat zostal dodany do listy kontaktow." << endl;
            wstrzymajProgram();
        }
    }
}

void przejdzDoMenuUzytkownika(vector <Uzytkownik> &uzytkownicy, vector <Adresat> &adresaci, int &idZalogowanegoUzytkownika) {
    int wyborUzytkownika = 0;

    wczytajAdresatowUzytkownikaDoWektora(adresaci, idZalogowanegoUzytkownika);

    while(idZalogowanegoUzytkownika != 0) {
        wyswietlMenuUzytkownika();
        wyborUzytkownika = wczytajLiczbe();

        switch (wyborUzytkownika) {
            case 1: dodajAdresata(adresaci, idZalogowanegoUzytkownika);     break;
            case 2: wyszukajAdresataPoImieniu(adresaci);                    break;
            case 3: wyszukajAdresataPoNazwisku(adresaci);                   break;
            case 4: wyswietlWszystkichAdresatow(adresaci);                  break;
            case 5: edytujAdresata(adresaci);                               break;
            case 6: usunAdresata(adresaci);                                 break;
            case 8: zmienHaslo(uzytkownicy, idZalogowanegoUzytkownika);     break;
            case 9: wyloguj(idZalogowanegoUzytkownika);                     break;
            default:
                cout << endl << "Nieprawidlowy wybor! Sprobuj ponownie." << endl;
                wstrzymajProgram();
        }
    }
}

void przejdzDoMenuGlownego(vector <Uzytkownik> &uzytkownicy, int &idZalogowanegoUzytkownika) {
    int wyborUzytkownika = 0;

    wyswietlMenuGlowne();
    wyborUzytkownika = wczytajLiczbe();

    switch(wyborUzytkownika) {
        case 1: idZalogowanegoUzytkownika = zalogujUzytkownika(uzytkownicy);    break;
        case 2: zarejestrujNowegoUzytkownika(uzytkownicy);                      break;
        case 3: exit(0);
        default:
            cout << endl << "Nieprawidlowy wybor!" << endl;
            wstrzymajProgram();
    }
}

int main() {
    int idZalogowanegoUzytkownika = 0;
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> adresaci;

    wczytajZarejestrowanychUzytkownikowDoWektora(uzytkownicy);

    while(true) {
        if(idZalogowanegoUzytkownika == 0) {
            przejdzDoMenuGlownego(uzytkownicy, idZalogowanegoUzytkownika);
        } else {
            przejdzDoMenuUzytkownika(uzytkownicy, adresaci, idZalogowanegoUzytkownika);
        }
    }
    return 0;
}

