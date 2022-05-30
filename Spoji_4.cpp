#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <windows.h>
#include <conio.h>
#include <ctime>
using namespace std;

int printRandomToken(int index)
{
    for (int i = 0; i < 4; i++)
        index = rand() % 4;
    return index;
}

bool nameCheck(string player1, string player2)
{
    /*remove koristimo za micanje razmaka(problem je mnozenje zadnjih slova nakon micanja razmaka
    ,a to rjesavamo sa erase koji koristimo do kraja reda(inace imamo isti problem*/
    player1.erase(remove(player1.begin(), player1.end(), ' '), player1.end());
    player2.erase(remove(player2.begin(), player2.end(), ' '), player2.end());
    //smanjenje svih slova
    transform(player1.begin(), player1.end(), player1.begin(), tolower);
    transform(player2.begin(), player2.end(), player2.begin(), tolower);
    if (player1 == player2) {
        cout << "\033[31m" << "Ime je vec upotrebljeno! Pokusajte ponovmo!" << "\033[0m" << endl;
        return 1;
    }
    else {
        cout << "\033[32m" << endl << "Ime 2. igraca (" << player2 << ") uspjesno dodano. :)" << "\033[0m" << endl << endl;
        return 0;
    }
}

void show_grid(char ploca[6][8])
{
   
    for (int i = 0; i < 6; i++)
    {
        cout << "\t       ";
        for (int j = 0; j < 8; j++)
        {
            cout << "[  ]" << ploca[i][j];
        }
        cout << endl;
    }
}

int main()
{
    string p1, p2, p3, p4, p5;
    p1 = "\t\t Pravila";
    p2 = "-Svaki igrac ima po 21 zeton (ukupno 42).";
    p3 = "-Trebate skupiti 4 zetona iste boje u nizu: okomito, vodoravno ili dijagonalno.";
    p4 = "-Mozete baciti samo jedan zeton po okretu.";
    p5 = "-Prvi igrac koji spoji 4 jednobojna zetona pobjeduje.";
    fstream datoteka("Pravila.bin", ios::binary | ios::out);
    datoteka.write((char*)&p1, sizeof(p1));
    datoteka.write((char*)&p2, sizeof(p2));
    datoteka.write((char*)&p3, sizeof(p3));
    datoteka.write((char*)&p4, sizeof(p4));
    datoteka.write((char*)&p5, sizeof(p5));
    datoteka.close();
    while (1)
    {
        system("cls");
        cout << "Dobrodosli u Spoji 4" << endl << endl;
        cout << "1. ispis pravila igre" << endl;
        cout << "2. pocetak igre" << endl;
        cout << "3. ispis rezultata" << endl;
        cout << "4. izlaz iz programa" << endl << endl;
        cout << "Vas odabir: ";
        int izbor;
        cin >> izbor;
        cin.ignore();
        if (izbor == 1){
            datoteka.open("Pravila.bin", ios::binary | ios::in);
            datoteka.read((char*)&p1, sizeof(p1));
            cout << p1 << endl;
            datoteka.read((char*)&p2, sizeof(p2));
            cout << p2 << endl;
            datoteka.read((char*)&p3, sizeof(p3));
            cout << p3 << endl;
            datoteka.read((char*)&p4, sizeof(p4));
            cout << p4 << endl;
            datoteka.read((char*)&p5, sizeof(p5));
            cout << p5 << endl;
            datoteka.close(); 
        }
        else if (izbor == 2){
            system("cls");
            //unos imena igraca
            string player1, player2;
            char token1, token2;
            char tokens[4] = { 'X', 'O', 'I','H' };
            //upis imena i provjera je li string prazan
            cout << "ODABIR IMENA IGRACA" << endl << endl;
            do {
                cout << "Unesite ime 1. igraca: ";
                getline(cin, player1);
                if (player1.empty())
                    cout << "\033[31m" << "Niste unijeli ime igraca! Pokusajte ponovno!" << "\033[0m" << endl;
            } while (player1.empty());
            cout << "\033[32m" << endl << "Ime 1. igraca (" << player1 << ") uspjesno dodano. :)" << "\033[0m" << endl << endl;
            /*upis imena i provjera je li string prazan te jesu li imena ista neovisno
            o razamcima te velicini slova*/
            do
            {
                do {
                    cout << "Unesite ime 2. igraca: ";
                    getline(cin, player2);
                    if (player2.empty())
                        cout << "\033[31m" << "Niste unijeli ime igraca! Pokusajte ponovno!" << "\033[0m" << endl;
                } while (player2.empty());

            } while (nameCheck(player1, player2));
            cout << "ODABIR ZETONA" << endl << endl;
            cout << "Racunalo ce nasumicno izabrati zetone za svakog igraca" << endl;
            srand(time(0));
            int index = 0;
            token1 = tokens[printRandomToken(index)];
            cout << "Zeton 1. igraca ce biti: " << "\033[32m" << token1 << "\033[0m" << endl;
            do
            {
                token2 = tokens[printRandomToken(index)];
            } while (token1 == token2);
            cout << "Zeton 2. igraca ce biti: " << "\033[32m" << token2 << "\033[0m" << endl;
            //_getch();
            system("cls");
            cout << "\t ___   ___                 ___  ___ _____" << endl;
            cout << "\t|     |   | |'   | |'   | |    |      |          /|" << endl;
            cout << "\t|     |   | | '  | | '  | |__  |      |         / |" << endl;
            cout << "\t|     |   | |  ' | |  ' | |    |      |        /__|_" << endl;
            cout << "\t|___  |___| |   '| |   '| |___ |___   |           |" << endl;
            cout << "       _____________________________________________________" << endl;
            cout << endl;
            char grid[6][8];
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 8; j++)
                    grid[i][j] = ' ';
            }
            show_grid(grid);
        }
        else if (izbor == 3) {
            fstream rezults("rezultati.bin", ios::binary | ios::in);

        }
        else if(izbor == 4){
            cout << "Dovidjenja!";
            break;
        }
        else {
                cout << "Krivi unos!" << endl;
        }
        
       system("pause");
    }  
}

//https://www.tutorialspoint.com/cplusplus-program-to-check-if-input-is-an-integer-or-a-string
//https://www.thiscodeworks.com/game-connect-four-connect-four-is-a-two-player-board-game-in-which-the-players-alternately-drop-colored-disks-into-a/5ffdf8a20c8c140014566a1c
 
/*void player1(char grid[][7], int x, int y)
{
    show_grid(grid);
    
    cout << "Drop a red disk at column (0–6): ";
    cin >> y;
    if (grid[x][y] == ' ')
        grid[x][y] = 'R';
    else {
        //make sure not to target the same row
        while (grid[x][y] != ' ')x--;
        grid[x][y] = 'R';
    }
}
 
void player2(char grid[][7],int x,int y)
{
    show_grid(grid);
 
    cout << "Drop a yellow disk at column (0–6): ";
    cin >> y;
    if (grid[x][y] == ' ')
        grid[x][y] = 'Y';
    else {
        //make sure not to target the same row
        while (grid[x][y] != ' ')x--;
        grid[x][y] = 'Y';
    }
       
}*/
/* 


-21 žeton za pojedinog igraèa
-2d polje
-funkcija za provjeru 4 iste boje paralelno,okomito i dijagonalno
-spremanje rezultata u bin file (dodatna moguænost:sortiranje rezultata prema broju pobjeda ili kronološki)

*ultra izazov(dodatan +):moguænost prestanka igre u bilo kojem trenutku te spremanje svega u bin file za kasniji nastavak

*/