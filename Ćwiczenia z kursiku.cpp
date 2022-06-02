#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>
using namespace std;

class tools
{
protected:
    void napisy(string nazwa, bool printTop = true, bool printBottom = true);
public:
    string losuj_slowo(string sciezka);
};

class gra :public tools {
private:
    const string nazwa_gry = "WISIELEC by ...";
    const string dostepne_litery = "DOSTEPNE LITERY";
    const string napis_haslo = "HASLO:";
    const string wygrana = "WYGRANA";
    const string przegrana = "GAME OVER";
public:
    void wyswietlanie_nazwy_gry();
    void wywietlenie_nap_lit();
    void wywietlenie_nap_hasla();
    void wyswietlanie_wygrana();
    void wyswietlanie_przegrana();
    void rysowanie_wisielca();
    void wyswietlanie_liter(string input, char from, char to);
    void wyswietlanie_dostepnych_liter(string taken);
    bool wyswietlanie_slowa(string slowo, string zgadywane);
    int pozostale_proby;
    int proba = 0;
};

void tools::napisy(string nazwa, bool printTop, bool printBottom)
{
    if (printTop)
    {
        cout << "|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|" << endl;
        cout << "|";
    }
    else
    {
        cout << "|";
    }

    bool front = true;

    for (int i = nazwa.length(); i < 39; i++)
    {
        if (front) {
            nazwa = " " + nazwa;
        }
        else {
            nazwa = nazwa + " ";
        }
        front = !front;
    }
    cout << nazwa.c_str();

    if (printBottom)
    {
        cout << "|" << endl;
        cout << "|-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-|" << endl;
    }
    else
    {
        cout << "|" << endl;
    }
}
void gra::wyswietlanie_nazwy_gry()
{
    napisy(nazwa_gry);
}

void gra::wywietlenie_nap_lit()
{
    napisy(dostepne_litery, true, false);
    napisy(" ", false, false);
}

void gra::wyswietlanie_wygrana()
{
    napisy(wygrana);
}

void gra::wyswietlanie_przegrana()
{
    napisy(przegrana);
}

void gra::wywietlenie_nap_hasla()
{
    napisy(napis_haslo, false, false);
    napisy(" ", false, false);
}
void gra::rysowanie_wisielca()
{
    napisy("|", false, false);
    napisy("|", false, false);
    /*--------------------------------------*/
    if (proba >= 1)
        napisy("O", false, false);
    else
        napisy("", false, false);
    /*--------------------------------------*/
    if (proba == 2)
        napisy("+", false, false);

    /*--------------------------------------*/
    if (proba == 3)
        napisy("-+ ", false, false);

    /*--------------------------------------*/
    if (proba >= 4)
        napisy("-+-", false, false);
    /*--------------------------------------*/
    if (proba >= 5)
        napisy("|", false, false);
    else
        napisy("", false, false);
    /*--------------------------------------*/
    if (proba == 6)
        napisy("/  ", false, false);
    /*--------------------------------------*/
    if (proba >= 7)
        napisy("/ \\ ", false, false);

    napisy(" ", false, false);
    napisy("_______________", false, false);
    napisy("|             |", false, false);
    napisy("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", false, false);

}

void gra::wyswietlanie_liter(string input, char from, char to)
{

    string s;
    for (char i = from; i <= to; i++)
    {
        if (input.find(i) == string::npos)
        {
            s += i;
            s += " ";
        }
        else
            s += " ";
    }
    napisy(s, false, false);
}

void gra::wyswietlanie_dostepnych_liter(string taken)
{
    wyswietlanie_liter(taken, 'A', 'M');
    wyswietlanie_liter(taken, 'N', 'Z');
    napisy("", false, true);
}

bool gra::wyswietlanie_slowa(string slowo, string zgadywane)
{
    bool wygrana = true;
    string s;
    for (int i = 0; i < slowo.length(); i++)
    {
        if (zgadywane.find(slowo[i]) == string::npos)
        {
            wygrana = false;
            s += "_ ";
        }
        else
        {
            s += slowo[i];
            s += " ";
        }
    }
    napisy(s, false);
    return wygrana;
}
string tools::losuj_slowo(string sciezka)
{
    int lineCount = 0;
    string slowo;
    vector<string> v;
    ifstream reader(sciezka);
    if (reader.is_open())
    {
        while (getline(reader, slowo))
            v.push_back(slowo);

        int randomline = rand() % v.size();

        slowo = v.at(randomline);
        reader.close();
    }
    return slowo;
}

int pozostale_proby(string slowo, string zgadywane)
{
    int error = 0;
    for (int i = 0; i < zgadywane.length(); i++)
    {
        if (slowo.find(zgadywane[i]) == string::npos)
            error++;
    }
    return error;
}

int main()
{
    gra wisielec;
    srand(time(0));
    string slowo_zgad;
    string slowo_do_zgad;
    slowo_zgad = wisielec.losuj_slowo("C:\\Users\\lesiu\\source\\repos\\Ćwiczenia z kursiku\\chujdupacycki.txt");
    wisielec.proba;
    bool wygrana = false;
    do
    {
        system("cls");
        wisielec.wyswietlanie_nazwy_gry();
        wisielec.rysowanie_wisielca();
        wisielec.wywietlenie_nap_lit();
        wisielec.wyswietlanie_dostepnych_liter(slowo_do_zgad);
        wisielec.wywietlenie_nap_hasla();
        wygrana = wisielec.wyswietlanie_slowa(slowo_zgad, slowo_do_zgad);

        if (wygrana)
            break;

        char x;
        cout << ">";
        cin >> x;
        if (slowo_do_zgad.find(x) == string::npos)
            slowo_do_zgad += x;

        wisielec.proba = pozostale_proby(slowo_zgad, slowo_do_zgad);

    } while (wisielec.proba < 8);

    if (wygrana)
        wisielec.wyswietlanie_wygrana();
    else
        wisielec.wyswietlanie_przegrana();

    system("pause");
    getchar();
    return 0;

}