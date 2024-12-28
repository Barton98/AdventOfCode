#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    //skąd będą brane dane, zaciągane do kodu
    string nazwaPliku = "daneD3.txt";
    ifstream plik(nazwaPliku);

    //trzeba sprawdzić czy plik jest dobrze otwarty
    if(!plik.is_open()) {
        cerr << "Nie można otworzyć pliku z danymi!: " << nazwaPliku << endl;
        return 1;
    }

    //wczytuje cały plik do jendego ciagu
    string ciag((istreambuf_iterator<char>(plik)), istreambuf_iterator<char>());

    plik.close();

    //regex do wyciągania poprawnych sekwencji mul(X,Y)
    regex wzorzec(R"(mul\(([0-9]{1,3}),([0-9]{1,3})\))");
    smatch dopasowanie;

    //wektor do przechowywania wyników
    //vector<string> wyniki;

    //zmienna dla sumy
    int suma = 0;

    //sprawdzanie ciagu i sekwencji w nim
    auto poczatek = ciag.cbegin();
    while (regex_search(poczatek, ciag.cend(), dopasowanie, wzorzec)) {

        //pobieranie liczb x i y z dopasowania
        int x = stoi(dopasowanie[1].str());
        int y = stoi(dopasowanie[2].str());

        //mnożenie i sumowanie liczb w poprawnych sekwencjach do wyniku
        suma += x * y; //dodanie wyniku do sumy

        poczatek = dopasowanie.suffix().first; //przejscie do reszty ciagu
    }

    //wyświetlanie wyników sumy
    cout << "Suma wyników: " << suma << endl;

    return 0;
}