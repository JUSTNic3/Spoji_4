#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;



void show_grid(char grid[6][8])
{
   
    for (int i = 0; i < 6; i++)
    {
        cout << "\t";
        for (int j = 0; j < 8; j++)
        {
            cout << "|  " << grid[i][j];
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
    datoteka << "-Trebate skupiti 4 �etona iste boje u nizu: okomito, vodoravno ili dijagonalno." << endl;
    datoteka << "-Mo�ete baciti samo jedan �eton po okretu." << endl;
    datoteka << "-Prvi igra� koji spoji 4 jednobojna �etona pobje�uje." << endl;
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
            datoteka.open("Pravila.txt", ios::app);
            string pravila;
            getline(datoteka, pravila);
            datoteka << pravila << endl;
            datoteka.close();
        }
        else if (izbor == 2){
            system("cls");
            cout << "\t\t    CONNECT 4!" << endl;
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
    
    cout << "Drop a red disk at column (0�6): ";
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
 
    cout << "Drop a yellow disk at column (0�6): ";
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
-su�elje sa odabirom po�etka igre,pravila,imena igra�a rije�eno
-21 �eton za pojedinog igra�a
-max 2 igra�a
-znakovi na plo�i
-2d polje
-igra�a plo�a
-funkcija za provjeru 4 iste boje paralelno,okomito i dijagonalno
-spremanje rezultata u bin file (dodatna mogu�nost:sortiranje rezultata prema broju pobjeda ili kronolo�ki)

*ultra izazov(dodatan +):mogu�nost prestanka igre u bilo kojem trenutku te spremanje svega u bin file za kasniji nastavak

*/