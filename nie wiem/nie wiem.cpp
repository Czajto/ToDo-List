#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <limits>
#include <cstdlib>  // dla system()

/*

X = NIE ZROBIONE
✓ = ZROBIONE

RZECZY DO ZROBIENIA!!!!
##############################
MOZLIWOSC EDYTOWANIA PODANYCH ZADAN Z LISTY (X)
WSZYSTKO MA LADNIE SIE WYSWIETLAC (X)
DODANIE FUNKCJI OZNACZANIA W DANYM PLIKU RZECZY ZROBIONYCH I NIE (X)
FUNKCJA KTORA CZYSCI DANE ZADANIA Z PLIKU (X)
FUNKCJA KTORA USUWA PLIKI Z KOMPUTERA (X)


MOZLIWOSC CZYSCZENIA OBECNEJ LISTY Z FUNKCJA "CZY NA PEWNO?" (✓)
DODAWANIE A NIE NADPISYWANIE DO ISTNIEJACYCH PLIKOW Z ZADANIAMI (✓)
############################
*/

using namespace std;
namespace fs = filesystem;

// Deklaracja funkcji potwierdzenia
bool potwierdzenie(const string& komunikat);

void czyscEkran() {
    // Sprawdzenie systemu operacyjnego
#ifdef _WIN32
    system("cls");  // dla Windows
#else
    system("clear");  // dla Linux/macOS
#endif
}
int wybor() {
    int wybor;

    cout << "[1] Dodaj zadanie do listy" << endl;
    cout << "[2] Pokaz zadania z listy" << endl;
    cout << "[3] Usun zadanie z listy" << endl;
    cout << "[4] Zapisz do pliku" << endl;
    cout << "[5] Wczytaj z pliku" << endl;
    cout << "[6] Wyjscie" << endl;
    cin >> wybor;
    cin.ignore();
    return wybor;
}
void dodajZadanie(vector<string>& lista) {
    string zadanie;
    cout << "Podaj tresc zadania" << endl;
    getline(cin, zadanie);
    lista.push_back(zadanie);
    cout << "Dodano zadanie: " << "\"" << zadanie << "\"" << endl;
}
void pokazywanieZadania(const vector<string>& lista) {
    if (lista.empty())
    {
        cout << "Brak zadan na liscie!" << endl;
        return;
    }

    cout << "Twoje zadania:" << endl;

    // Iteruje po kolei kazde zadanie z listy i je wyswietla
    for (size_t i = 0; i < lista.size(); i++)
    {
        cout << i + 1 << ". " << lista[i] << ".\n";
    }
    cout << endl;
}
void usuwanieZadania(vector<string>& lista) {
    if (lista.empty())
    {
        cout << "Brak zadan na liscie!" << endl;
        return;
    }

    int index;
    cout << "Podaj numer zadanie do usuniecia: ";
    cin >> index;

    if (index < 1 || index > lista.size()) {
        cout << "Niepoprawny numer!" << endl;
        return;
    }

    // Usuwa podane zadanie w numerze odejmujac jeden dopasowujac do indexu listy np. zadanie nr 1 bedzie znajdowac sie w indexie 0 w array
    cout << "Usunieto zadanie: " << "\"" << lista[index - 1] << "\"!" << endl;
    lista.erase(lista.begin() + index - 1);
}
void zapiszDoPliku(const vector<string>& lista, string& nazwa) {
    string sciezka = "C:\\Users\\rogal\\Desktop\\To-Do Listy\\" + nazwa + ".txt";

    ofstream plik(sciezka, ios::app);

    if (!plik)
    {
        cout << "Otwieranie pliku nie powiodlo sie" << endl;
        return;
    }

    for (const string& zadanie : lista) {
        // Zapisuje zadania z array do pliku !CHWILOWO NADPISUJE WSZYSTKO CO JEST W PLIKU! !!!!! DO NAPRAWY !!!!!!!
        plik << zadanie << endl;
    }

    plik.close();
    cout << "Zadania zostaly zapisane do pliku" << endl;
}
void wczytywanieZpliku(vector<string> &lista, string &nazwa) {
    string sciezka = "C:\\Users\\rogal\\Desktop\\To-Do Listy\\" + nazwa + ".txt";

    ifstream plik(sciezka);

        if (!plik) {
            cout << "Brak pliku lub blad otwierania" << endl;
            return;
    }
        lista.clear();
        string zadanie;

        while (getline(plik, zadanie))
        {
            lista.push_back(zadanie);
        }

        plik.close();
        cout << "Zadania wczytane z pliku: " << "\"" << nazwa << ".txt\"" << endl;

}
void wyswietlaniePlikow(const string& sciezka) {
    cout << "Pliki w folderze: " << sciezka << endl;

    // PRZY UZYCIU BIBLIOTEKI FILESYSTEM ROBI ITERACJE W FOLDERZE WYSWIETLAJAC PRZY TYM WSZYSTKIE PLIKI BEZ ROZSZERZEŃ
    for (const auto& plik : fs::directory_iterator(sciezka)) {
        cout << " - " << plik.path().stem() << endl;
    }
}
void wyczyscCalaListe(vector<string>&lista) {
    if (lista.empty())
    {
        cout << "Brak zadan na liscie!" << endl;
        return;
    }

    if (potwierdzenie("Czy na pewno chcesz usunac wszystkie zadania z listy?: ")) {
        lista.clear();
        cout << "Wszystkie zadania zostaly usuniete. " << endl;
    }
    else {
        cout << "Anulowano operacje." << endl;
    }

    // Czyszczenie bufora wejścia dla pewności
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


}
bool potwierdzenie(const string& komunikat) {
    char decyzja;
    cout << komunikat << " (T/N): ";
    cin >> decyzja;

    //Konwersja do wielkiej litery, aby działało dla "t" i "T"
    decyzja = toupper(decyzja);

    return (decyzja == 'T');  // Zwraca true, jeśli użytkownik wpisał 'T'
}

int main() {
    string nazwaPliku;
    vector<string> listaZadan;
    string folder = "C:\\Users\\rogal\\Desktop\\To-Do Listy";  // Ustaw ścieżkę folderu
    int wyborUsuniecia;


    while (true) {

        int mainWybor = wybor();
        switch (mainWybor) {
        case 1:                             // DODAWANIE ZADAN
            czyscEkran();  // Wyczyszczenie ekranu tylko przed pokazaniem zadań


            dodajZadanie(listaZadan);

            break;
        case 2: // POKAZYWANIE ZADAN
            czyscEkran();  
            pokazywanieZadania(listaZadan);
            break;
        case 3:                             // USUWANIE ZADAN
            czyscEkran();  
            cout << "Co chcesz zrobic?" << endl;
            cout << "[1] Usunac wszystkie zadania z listy " << endl;
            cout << "[2] Usunac pojedyncze zadania z listy wybrane przez ciebie" << endl;
            cin >> wyborUsuniecia;
            if (wyborUsuniecia == 1) {
                wyczyscCalaListe(listaZadan);
            }
            else if (wyborUsuniecia == 2) {
                pokazywanieZadania(listaZadan);
                usuwanieZadania(listaZadan);

            }
            else {
                cout << "wybierz jedna z opcji";
                return 0;
            }

            break;
        case 4:                            // ZAPISYWANIE ZADAN W PLIKU
            // Wyświetlanie dostępnych plików przed zapisaniem
            wyswietlaniePlikow(folder);

            cout << "Podaj nazwe pliku do ktorego chcesz zapisac zadania: ";
            cin >> nazwaPliku;

            // Zapisuje zadania i tworzy dla nich pliki
            zapiszDoPliku(listaZadan, nazwaPliku);
            break;
        case 5:                             // WCZYTYWANIE Z PLIKU
            cout << "Z którego pliku chcesz zaladowac zadania?" << endl;

            wyswietlaniePlikow(folder);

            cin >> nazwaPliku;

            // Wczytuje z pliku
            wczytywanieZpliku(listaZadan, nazwaPliku);

            break;
        case 6:
            cout << "Zegnaj (czesc)" << endl;
            return 0;
        default:
            cout << "Prosze podac jedna z opcji" << endl;
        }
    }

    return 0;
}
