#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <windows.h>
using namespace std;

struct PlayerInfo {
    string PlayerName;
    char PlayerID{' '};
};

void ShowGrid(char grid[6][8])
{
    cout << "\t\t ___   ___   ___     " << endl;
    cout << "\t\t|     |   | |   |     |  |         /|" << endl;
    cout << "\t\t|___  |___| |   |     |  |        / |" << endl;
    cout << "\t\t    | |     |   |     |  |       /__|_" << endl;
    cout << "\t\t ___| |     |___|  |__|  |          |" << endl;
    cout << "        ____________________________________________________" << endl;
    cout << endl;
    cout << "\t           ";
    for (int i = 0; i < 8; i++)
    {
        cout << i + 1 << "   ";
    }
    cout << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << "\t          ";
        for (int j = 0; j < 8; j++)
        {
            cout << "[" << grid[i][j] << "] ";
        }
        cout << endl;
    }
}

int PlayerDrop(char grid[6][8], PlayerInfo ActivePlayer)
{
    int DropChoice = 0;
    do
    {
        cout << endl << ActivePlayer.PlayerName << "(" << "\033[32m" << ActivePlayer.PlayerID << "\033[0m" << ")" << ", tvoj red. ";
        cout << "Molim unesite broj stupac izmedu 1 i 8: ";
        cin >> DropChoice;
        if (DropChoice > 0 && DropChoice < 9)
        {
            while (grid[0][DropChoice - 1] != ' ') 
            {
                cout << "Taj redak je pun , molim unesite novi redak: ";
                cin >> DropChoice;
            }
        }
        else
            cout << "\033[31m" <<  "Krivi stupac! Pokusajte ponovno." <<  "\033[0m" << endl;
    } while (DropChoice < 1 || DropChoice > 8);
    return DropChoice; 
}

void CheckBellow(char grid[6][8], PlayerInfo ActivePlayer, int DropChoice)
{
    int lgt = 5, t = 0;
    do {
        if (grid[lgt][DropChoice-1] == ' ')
        {
            grid[lgt][DropChoice-1] = ActivePlayer.PlayerID;
            t = 1;
        }
        else
        
            --lgt;
    } while (t != 1);
}

int FullGrid(char grid[6][8])
{
    int full = 0;
    for (int i = 0; i < 8; ++i)
    {
        if (grid[1][i] != ' ')
            ++full;
    }
    return full;
}

int Check4(char grid[6][8], PlayerInfo ActivePlayer, int win)
{
    char znak = ActivePlayer.PlayerID;
    win = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (grid[i][j] == znak && grid[i + 1][j + 1] == znak && grid[i + 2][j + 2] == znak && grid[i + 3][j + 3] == znak)
                win = 1;
            if (grid[i][j] == znak && grid[i][j + 1] == znak && grid[i][j + 2] == znak && grid[i][j + 3] == znak)
                win = 1;
            if (grid[i][j] == znak && grid[i + 1][j] == znak && grid[i + 2][j] == znak && grid[i + 3][j] == znak)
                win = 1;
            if (grid[i][j] == znak && grid[i + 1][j - 1] == znak && grid[i + 2][j - 2] == znak && grid[i + 3][j - 3] == znak)
                win = 1;
            if (grid[i][j] == znak && grid[i][j - 1] == znak && grid[i][j - 2] == znak && grid[i][j - 3] == znak)
                win = 1;
        }
    }
    return win;
}

void PlayerWin(PlayerInfo ActivePlayer)
{
    cout << endl << "\033[32m" << ActivePlayer.PlayerName << ", pobijedio si!"  << "\033[0m" << endl;
}

int restart(char grid[6][8])
{
    int restart = 0;
    do{
        cout << "Zelite li zaigrati ponovno? Da(1) Ne(2)" << endl;
        cin >> restart;
        if (restart == 1)
        {
            system("cls");
            cout << "\t ___   ___   ___     " << endl;
            cout << "\t|     |   | |   |     |  |         /|" << endl;
            cout << "\t|___  |___| |   |     |  |        / |" << endl;
            cout << "\t    | |     |   |     |  |       /__|_" << endl;
            cout << "\t ___| |     |___|  |__|  |          |" << endl;
            cout << "        ____________________________________________________" << endl;
            cout << endl;
            cout << "\t           ";
            for (int i = 0; i < 8; i++)
            {
                cout << i + 1 << "   ";
            }
            cout << endl;
            for (int i = 0; i < 6; i++)
            {
                cout << "\t          ";
                for (int j = 0; j < 8; j++)
                {
                    cout << "[" << ' ' << "] ";
                    grid[i][j] = ' ';
                }
                cout << endl;
            }
        }
        else if (restart != 1 && restart != 2)
            cout << "\033[31m" << "Krivi unos! Molimo upisite valjani broj." << "\033[0m" << endl;
        else
            cout << "\033[32m" << endl << "Igra je gotova!" << "\033[0m" << endl;
    } while (restart != 1 && restart != 2);
    return restart;
}

bool nameCheck(PlayerInfo player1, PlayerInfo player2)
{
	
	player1.PlayerName.erase(remove(player1.PlayerName.begin(), player1.PlayerName.end(), ' '), player1.PlayerName.end());
	player2.PlayerName.erase(remove(player2.PlayerName.begin(), player2.PlayerName.end(), ' '), player2.PlayerName.end());

    for_each(player1.PlayerName.begin(), player1.PlayerName.end(), [](char& c) {c = tolower(c); });
	for_each(player2.PlayerName.begin(), player2.PlayerName.end(), [](char& c) {c = tolower(c); });
	if (player1.PlayerName == player2.PlayerName) {
		cout << "\033[31m" <<"Ime je vec upotrebljeno! Pokusajte ponovmo!" << "\033[0m" << endl;
		return true;
	}
	else {
		cout << "\033[32m" << endl << "Ime 2. igraca (" << player2.PlayerName << ") uspjesno dodano. :)" << "\033[0m" << endl << endl;
		return false;
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
        string izbor;
        cin >> izbor;
        cin.ignore();
        if (izbor == "1") {
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
        else if (izbor == "2") {
            PlayerInfo player1, player2;
            system("cls");

            cout << "ODABIR IMENA IGRACA" << endl << endl;
	        do {
		        cout << "Unesite ime 1. igraca: ";
		        getline(cin, player1.PlayerName);
		        if(player1.PlayerName.empty())
			        cout << "\033[31m" << "Niste unijeli ime igraca! Pokusajte ponovno!" << "\033[0m" << endl;
	        } while (player1.PlayerName.empty());
	        cout << "\033[32m" << endl << "Ime 1. igraca (" << player1.PlayerName << ") uspjesno dodano. :)" << "\033[0m" << endl << endl;
	        do
	        {
		        do {
			        cout << "Unesite ime 2. igraca: ";
			        getline(cin, player2.PlayerName);
			        if(player2.PlayerName.empty())
				        cout << "\033[31m" << "Niste unijeli ime igraca! Pokusajte ponovno!" << "\033[0m" << endl;
		        } while (player2.PlayerName.empty());
	
	        } while (nameCheck(player1, player2));

            player1.PlayerID = 'X';
            player2.PlayerID = 'O';
            cout << endl << "Zeton 1. igraca ce biti: " << "\033[32m" << player1.PlayerID << "\033[0m" << endl;
            cout << "Zeton 2. igraca ce biti: " << "\033[32m" << player2.PlayerID << "\033[0m" << endl << endl;

            system("pause");
            system("cls");
            char grid[6][8]{' '};
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 8; j++)
                    grid[i][j] = ' ';
            }
            ShowGrid(grid);
            
            int DropChoice, full = 0,again=0,win=0;

            do
            {
                DropChoice = PlayerDrop(grid, player1);
                CheckBellow(grid, player1, DropChoice);
                win = Check4(grid, player1, win);
                system("cls");
                ShowGrid(grid);
                if(win == 1)
                {
                    PlayerWin(player1);
                    again = restart(grid);
                    if (again == 2)
                        break;
                }
                system("cls");

                ShowGrid(grid);
                DropChoice = PlayerDrop(grid, player2);
                CheckBellow(grid, player2, DropChoice);
                system("cls");
                ShowGrid(grid);
                win = Check4(grid, player2, win);
                if(win == 1)
                {
                    PlayerWin(player2);
                    again = restart(grid);
                    if (again == 2)
                        break;
                }

                full=FullGrid(grid);
                if(full == 8)
                {
                    cout << endl << "\033[32m" << "Ploca je puna, rezultat je izjednacen!" << "\033[0m" << endl;
                    again = restart(grid);
                }
            } while (again != 2);

        }
        else if (izbor == "3") {
            fstream results("rezultati.bin", ios::binary | ios::in);

        }
        else if (izbor == "4") {
            cout << "Dovidjenja!";
            break;
        }
        else {
            cout << "Krivi unos!" << endl;
        }

        system("pause");
    }
}


//https://www.thiscodeworks.com/game-connect-four-connect-four-is-a-two-player-board-game-in-which-the-players-alternately-drop-colored-disks-into-a/5ffdf8a20c8c140014566a1c
//https://gist.github.com/MichaelEstes/7836988
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
-spremanje rezultata u bin file (dodatna moguænost:sortiranje rezultata prema broju pobjeda ili kronološki)*/