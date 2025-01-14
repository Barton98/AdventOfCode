#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

int main() {
    // Dane wejściowe
    string nazwaPliku = "daneD3.txt";
    ifstream plik(nazwaPliku);

    //trzeba sprawdzić czy plik jest dobrze otwarty
    if(!plik.is_open()) {
        cerr << "Nie można otworzyć pliku z danymi!: " << nazwaPliku << endl;
        return 1;
    }

    // Wczytuje cały plik do jednego ciągu
    string ciag((istreambuf_iterator<char>(plik)), istreambuf_iterator<char>());
    plik.close();

    // Regex do dopasowania mul(...) i do()/don't()
    regex wzorzec(R"(mul\(([0-9]+),([0-9]+)\)|do\(\)|don't\(\))");

    // Zmienna do przechowywania sumy
    int suma = 0;
    bool aktywne = true; // Domyślnie włączone

    // Przeszukiwanie ciągu za pomocą iteratorów
    auto poczatek = ciag.cbegin();
    smatch dopasowanie;

    while (regex_search(poczatek, ciag.cend(), dopasowanie, wzorzec)) {
        string znaleziony = dopasowanie.str();

        if (znaleziony == "do()") {
            aktywne = true;
        } else if (znaleziony == "don't()") {
            aktywne = false;
        } else if (znaleziony.rfind("mul(", 0) == 0 && aktywne) {
            // Parsowanie wartości w mul(...)
            int x = stoi(dopasowanie[1].str());
            int y = stoi(dopasowanie[2].str());
            suma += x * y;
        }

        // Przesuwamy iterator na koniec bieżącego dopasowania
        poczatek = dopasowanie.suffix().first;
    }

    cout << "Suma wyników: " << suma << endl;

    return 0;
}