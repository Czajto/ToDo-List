#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <cstdlib>  // dla system()
using namespace std;
namespace fs = filesystem;

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

    cout << "\nTwoje zadania:" << endl;
    for (size_t i = 0; i < lista.size(); i++)
    {
        cout << i + 1 << ". " << lista[i] << ".\n";
    }
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
    cout << "Usunieto zadanie: " << "\"" << lista[index - 1] << "\"!" << endl;
    lista.erase(lista.begin() + index - 1);
}

void zapiszDoPliku(const vector<string>& lista, string& nazwa) {
    string sciezka = "C:\\Users\\rogal\\Desktop\\To-Do Listy\\" + nazwa + ".txt";

    ofstream plik(sciezka);

    if (!plik)
    {
        cout << "Otwieranie pliku nie powiodlo sie" << endl;
        return;
    }

    for (const string& zadanie : lista) {
        plik << zadanie << endl;
    }

    plik.close();
    cout << "Zadania zostaly zapisane do pliku" << endl;
}

void wyswietlaniePlikow(const string& sciezka) {
    cout << "Pliki w folderze: " << sciezka << endl;

    for (const auto& plik : fs::directory_iterator(sciezka)) {
        cout << " - " << plik.path().filename() << endl;
    }
}

int main() {
    string nazwaPliku;
    vector<string> listaZadan;
    string folder = "C:\\Users\\rogal\\Desktop\\To-Do Listy";  // Ustaw ścieżkę folderu

    while (true) {

        int mainWybor = wybor();
        switch (mainWybor) {
        case 1: // DODAWANIE ZADAN
            czyscEkran();  // Wyczyszczenie ekranu tylko przed pokazaniem zadań
            dodajZadanie(listaZadan);
            break;
        case 2: // POKAZYWANIE ZADAN
            czyscEkran();  
            pokazywanieZadania(listaZadan);
            break;
        case 3: // USUWANIE ZADAN
            czyscEkran();  
            pokazywanieZadania(listaZadan);
            usuwanieZadania(listaZadan);
            break;
        case 4: // ZAPISYWANIE ZADAN W PLIKU
            // Wyświetlanie dostępnych plików przed zapisaniem
            wyswietlaniePlikow(folder);

            cout << "Podaj nazwe pliku do ktorego chcesz zapisac zadania: ";
            cin >> nazwaPliku;
            zapiszDoPliku(listaZadan, nazwaPliku);
            break;
        case 5: // WCZYTYWANIE Z PLIKU
            cout << "Piec" << endl;
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
