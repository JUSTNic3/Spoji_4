#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;



void show_grid(char ploca[6][8])
{
   
    for (int i = 0; i < 6; i++)
    {
        cout << "\t\t";
        for (int j = 0; j < 8; j++)
        {
            cout << "|  " << ploca[i][j];
        }
        cout << "|" << endl;
    }
}

int main()
{
    fstream datoteka("Pravila.txt");
    if(!datoteka.is_open())
        datoteka.open("Pravila.txt", ios::app);
    datoteka << "\t" << "Pravila igre" << "\t" << endl;
    datoteka << "-Svaki igrac ima po 21 zeton (ukupno 42)." << endl;
    datoteka << "-Trebate skupiti 4 zetona iste boje u nizu: okomito, vodoravno ili dijagonalno." << endl;
    datoteka << "-Mozete baciti samo jedan zeton po okretu." << endl;
    datoteka << "-Prvi igrac koji spoji 4 jednobojna zetona pobjeduje." << endl;
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
        if (izbor == 1){
            datoteka.open("Pravila.txt");
            string redak;
            while (!datoteka.eof()) {
                getline(datoteka, redak);
                cout << redak << endl;
                if (datoteka.eof())break;
            }
            datoteka.close();
            datoteka.open("Pravila.txt", ios::app);
            string pravila;
            getline(cin, pravila);
            datoteka << pravila << endl;
            datoteka.close();
        }
        else if (izbor == 2){
            system("cls");
            cout << "\t ___   ___                 ___  ___ _____" << endl;
            cout << "\t|     |   | |'   | |'   | |    |      |           /|" << endl;
            cout << "\t|     |   | | '  | | '  | |__  |      |          / |" << endl;
            cout << "\t|     |   | |  ' | |  ' | |    |      |         /__|_" << endl;
            cout << "\t|___  |___| |   '| |   '| |___ |___   |           |" << endl;
            cout << "___________________________________________________________________" << endl;
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
- poseban bin file ili odabir korisnika za pravila igre
-suèelje sa odabirom poèetka igre,pravila,imena igraèa riješeno
-21 žeton za pojedinog igraèa
-max 2 igraèa
-znakovi na ploèi
-2d polje
-igraèa ploèa
-funkcija za provjeru 4 iste boje paralelno,okomito i dijagonalno
-spremanje rezultata u bin file (dodatna moguænost:sortiranje rezultata prema broju pobjeda ili kronološki)

*ultra izazov(dodatan +):moguænost prestanka igre u bilo kojem trenutku te spremanje svega u bin file za kasniji nastavak

*/