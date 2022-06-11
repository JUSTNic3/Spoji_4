#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <algorithm>
using namespace std;

struct PlayerInfo {
    string Name;
    char ID{' '};
};

void Headline()
{
    cout << "\t\t ___   ___   ___     " << endl;
    cout << "\t\t|     |   | |   |     |  |         /|" << endl;
    cout << "\t\t|___  |___| |   |     |  |        / |" << endl;
    cout << "\t\t    | |     |   |     |  |       /__|_" << endl;
    cout << "\t\t ___| |     |___|  |__|  |          |" << endl;
    cout << "        ____________________________________________________" << endl;
    cout << endl;
    cout << "\t           ";
}

void ShowGrid(char grid[6][8])
{
    Headline();
    for (int i = 0; i < 7; i++)
    {
        cout << i + 1 << "   ";
    }
    cout << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "\t          ";
        for (int j = 0; j < 7; j++)
        {
            cout << "[" << grid[i][j] << "] ";
        }
        cout << endl;
    }
}

//checks
int PlayerDrop(char grid[6][8], PlayerInfo ActivePlayer)
{
    int DropChoice = 0;
    do
    {
        cout << endl << ActivePlayer.Name << "(" << "\033[32m" << ActivePlayer.ID << "\033[0m" << ")" << ", tvoj red. ";
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
            cout << "\033[31m" << "Krivi stupac! Pokusajte ponovno." << "\033[0m" << endl;
    } while (DropChoice < 1 || DropChoice > 8);
    return DropChoice;
}
//checks
void CheckBellow(char grid[6][8], PlayerInfo ActivePlayer, int DropChoice)
{
    fstream saveGrid;
    saveGrid.open("grid.bin", ios::binary | ios::out | ios::app);
    int lgt = 5, t = 0;
    do {
        if (grid[lgt][DropChoice - 1] == ' ')
        {
            grid[lgt][DropChoice - 1] = ActivePlayer.ID;
            //spremanje žetona u polju
            saveGrid.write((char*)&grid[lgt][DropChoice-1], sizeof(char));
            t = 1;
        }
        else

            --lgt;
    } while (t != 1);
    saveGrid.close();
}
//checks
int Check4(char grid[5][8], PlayerInfo ActivePlayer, int win)
{
    char znak = ActivePlayer.ID;
    win = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (grid[i][j] == znak && grid[i + 1][j + 1] == znak && grid[i + 2][j + 2] == znak && grid[i + 3][j + 3] == znak)
                win = 1;
            if (grid[i][j] == znak && grid[i][j + 1] == znak && grid[i][j + 2] == znak && grid[i][j + 3] == znak)
                win = 1;
            if (grid[i][j] == znak && grid[i + 1][j] == znak && grid[i + 2][j] == znak && grid[i + 3][j] == znak)
                win = 1;
            if(i < 2 && j > 3)
                if (grid[i][j] == znak && grid[i + 1][j - 1] == znak && grid[i + 2][j - 2] == znak && grid[i + 3][j - 3] == znak)
                    win = 1;
            if(j > 2)
                if (grid[i][j] == znak && grid[i][j - 1] == znak && grid[i][j - 2] == znak && grid[i][j - 3] == znak)
                    win = 1;
        }
    }
    return win;
}

//checks
int Restart(char grid[6][8])
{
    int restart = 0;
    do {
        cout << "Zelite li zaigrati ponovno? Da(1) Ne(2)" << endl;
        cin >> restart;
        if (restart == 1)
        {
            system("cls");
            Headline();
            for (int i = 0; i < 7; i++)
            {
                cout << i + 1 << "   ";
            }
            cout << endl;
            for (int i = 0; i < 5; i++)
            {
                cout << "\t          ";
                for (int j = 0; j < 7; j++)
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
//chekcs
int FullGrid(char grid[6][8])
{
    int full = 0;
    for (int i = 0; i < 7; ++i)
    {
        if (grid[1][i] != ' ')
            ++full;
    }
    return full;
}

void PlayerWin(PlayerInfo ActivePlayer)
{
    cout << endl << "\033[32m" << ActivePlayer.Name << ", pobijedio si!" << "\033[0m" << endl;
}

//checks
bool NameCheck(PlayerInfo player1, PlayerInfo player2)
{

    player1.Name.erase(remove(player1.Name.begin(), player1.Name.end(), ' '), player1.Name.end());
    player2.Name.erase(remove(player2.Name.begin(), player2.Name.end(), ' '), player2.Name.end());

    for_each(player1.Name.begin(), player1.Name.end(), [](char& c) {c = tolower(c); });
    for_each(player2.Name.begin(), player2.Name.end(), [](char& c) {c = tolower(c); });
    if (player1.Name == player2.Name) {
        cout << "\033[31m" << "Ime je vec upotrebljeno! Pokusajte ponovmo!" << "\033[0m" << endl;
        return true;
    }
    else {
        cout << "\033[32m" << endl << "Ime 2. igraca (" << player2.Name << ") uspjesno dodano. :)" << "\033[0m" << endl << endl;
        return false;
    }
}



int main()
{
    string text[5];
    text[0] = "\t\t Pravila";
    text[1] = "-Svaki igrac ima po 21 zeton (ukupno 42).";
    text[2] = "-Trebate skupiti 4 zetona iste boje u nizu: okomito, vodoravno ili dijagonalno.";
    text[3] = "-Mozete baciti samo jedan zeton po okretu.";
    text[4] = "-Prvi igrac koji spoji 4 jednobojna zetona pobjeduje.";
    fstream file("Rules.bin", ios::binary | ios::out);
    for(int i=0;i<5;i++)
        file.write((char*)&text[i], sizeof(text[i]));
    file.close();
    while (1)
    {
        system("cls");
        cout << "Dobrodosli u Spoji 4" << endl << endl;
        cout << "1. ispis pravila igre" << endl;
        cout << "2. pocetak igre" << endl;
        cout << "3. ispis rezultata" << endl;
        cout << "4. izlaz iz programa" << endl << endl;
        cout << "Vas odabir: ";
        string choice;
        cin >> choice;
        cin.ignore();
        if (choice == "1") {

            system("cls");
            file.open("Rules.bin", ios::binary | ios::in);
            if (file.is_open())
            {
                for (int i = 0; i < 4; i++)
                {
                    file.read((char*)&text[i], sizeof(text[i]));
                    cout << text[i] << endl;
                }
                file.close();
                cout << endl;
            }
            else
                cout << "Greska pri otvaranju datoteke!" << endl;
        }
        else if (choice == "2") {

            fstream saveGrid("grid.bin", ios::binary | ios::out);
            fstream savePlayers("players.bin", ios::binary | ios::out);
            PlayerInfo player1, player2;
            system("cls");

            cout << "ODABIR IMENA IGRACA" << endl << endl;
	        do {
		        cout << "Unesite ime 1. igraca: ";
		        getline(cin, player1.Name);
		        if(player1.Name.empty())
			        cout << "\033[31m" << "Niste unijeli ime igraca! Pokusajte ponovno!" << "\033[0m" << endl;
	        } while (player1.Name.empty());
            //spremanje 1. igraca
            savePlayers.write((char*) &player1.Name,sizeof(player1.Name));
	        cout << "\033[32m" << endl << "Ime 1. igraca (" << player1.Name << ") uspjesno dodano. :)" << "\033[0m" << endl << endl;
	        do
	        {
		        do {
			        cout << "Unesite ime 2. igraca: ";
			        getline(cin, player2.Name);
			        if(player2.Name.empty())
				        cout << "\033[31m" << "Niste unijeli ime igraca! Pokusajte ponovno!" << "\033[0m" << endl;
		        } while (player2.Name.empty());
	
	        } while (NameCheck(player1, player2));
            //spremanje 2. igraca
            savePlayers.write((char*)&player2.Name, sizeof(player2.Name));

            player1.ID = 'X';
            player2.ID = 'O';
            //spremanje žetona;
            savePlayers.write((char*)&player1.ID, sizeof(char));
            savePlayers.write((char*)&player2.ID, sizeof(char));
            savePlayers.close();
            cout << endl << "Zeton 1. igraca ce biti: " << "\033[32m" << player1.ID << "\033[0m" << endl;
            cout << "Zeton 2. igraca ce biti: " << "\033[32m" << player2.ID << "\033[0m" << endl << endl;

            system("pause");
            system("cls");
            char grid[6][8];
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 7; j++) 
                {
                    grid[i][j] = ' ';
                    saveGrid.write((char*)&grid[i][j], sizeof(char));
                }
            }
            ShowGrid(grid);
            //spremanje polja,za svaki slučaj
            
            int DropChoice, full = 0,again=0,win=0;
            //početak igre
            do
            {
                DropChoice = PlayerDrop(grid, player1);
                CheckBellow(grid, player1, DropChoice);  //spremanje mjesta ako je slobodno,mjesto je spoejno sa igračem
                win = Check4(grid, player1, win);
                system("cls");
                ShowGrid(grid);
                if(win == 1)
                {
                    PlayerWin(player1);
                    again = Restart(grid);
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
                    again = Restart(grid);
                    if (again == 2)
                        break;
                }

                full=FullGrid(grid);
                if(full == 8)
                {
                    cout << endl << "\033[32m" << "Ploca je puna, rezultat je izjednacen!" << "\033[0m" << endl;
                    again = Restart(grid);
                }
            } while (again != 2);

        }
        else if (choice == "3") {

            fstream results("grid.bin", ios::binary | ios::out);

        }
        else if (choice == "4") {

            cout << "Dovidjenja!";
            break;
        }
        else {
            cout << "Krivi unos!" << endl;
        }

        system("pause");
    }
}

//još samo save & load :(
//https://www.thiscodeworks.com/game-connect-four-connect-four-is-a-two-player-board-game-in-which-the-players-alternately-drop-colored-disks-into-a/5ffdf8a20c8c140014566a1c
//https://gist.github.com/MichaelEstes/7836988