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

void wyswietlDaneAdresata(const vector <Adresat> :: iterator &adresat) {
    cout << "Numer ID:\t\t"         << adresat->idAdresata                          << endl;
    cout << "Imie i Nazwisko:\t"    << adresat->imie << " " << adresat->nazwisko    << endl;
    cout << "nr. telefonu:\t\t"     << adresat->numerTelefonu                       << endl;
    cout << "Email:\t\t\t"          << adresat->email                               << endl;
    cout << "Adres:\t\t\t"          << adresat->adres                               << endl << endl;
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

void wyloguj()    {
}

int main() {
    vector <Adresat> adresaci;

cout << "Podaj ID: ";
int idZalogowanegoUzytkownika = 1;                      // podaj ID jakie bedzie docelowo podawal program

    while(true)    {
        wyswietlMenuUzytkownika();
        char wyborUzytkownika = wczytajLiczbe();

        switch (wyborUzytkownika) {
            case 1:
                dodajAdresata(adresaci, idZalogowanegoUzytkownika);
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
                wyloguj();
                break;
            default:
                cout << endl << "Nieprawidlowy wybor! Sprobuj ponownie." << endl;
                wstrzymajProgram();
        }
    }
    return 0;
}
