#include <iostream>
#include <fstream>
#include <string>
#include "GameChecks.h"
#include "Output.h"
using namespace std;


int main()
{
    fstream file("rules.bin", ios::binary | ios::out);
    string text = "\t\t Pravila\n- Svaki igrac ima po 21 zeton (ukupno 42)."
        " \n- Trebate skupiti 4 zetona iste boje u nizu : okomito, vodoravno ili dijagonalno."
        "\n- Mozete baciti samo jedan zeton po okretu."
        "\n- Prvi igrac koji spoji 4 jednobojna zetona pobjeduje.";
    file.write((char*)&text, sizeof(text));
    file.close();

    string* player = new string[2];
    char* id = new char[2]{ 'X','O' };
    char grid[6][8]={{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '}};
    ofstream saveGrid("saveGrid.bin", ios::binary | ios::out);
    saveGrid.write((char*)&grid, sizeof(grid));
    saveGrid.close();
    while (1)
    {
        system("cls");
        cout << "Dobrodosli u Spoji 4" << endl << endl;
        cout << "1. ispis pravila igre" << endl;
        cout << "2. pocetak igre" << endl;
        cout << "3. ispis rezultata" << endl;
        cout << "4. izlaz iz programa" << endl << endl;
        cout << "Vas odabir: ";
        string choiceMenu;
        cin >> choiceMenu;
        cin.ignore();
        if (choiceMenu == "1") {

            system("cls");
            file.open("rules.bin", ios::binary | ios::in);
            if (file.is_open())
            {
                file.read((char*)&text, sizeof(text));
                cout << text << endl;
                file.close();
                cout << endl;
            }
            else
                cout << "Greska pri otvaranju datoteke!" << endl;
        }
        else if (choiceMenu == "2") {


            system("cls");
            cout << "ODABIR IMENA IGRACA" << endl << endl;
            cout << "Igraci se spremaju napon sto se oba igraca unesu." << endl 
                 << "Imena igraca moraju imati maksimalno 32 znaka, u suprotonome se string skracuje" << endl << endl;

            do {
                cout << "Unesite ime 1.igraca: ";
                getline(cin, player[0]);
                if (player[0].empty())
                    cout << "\033[31m" << "Niste unijeli ime igraca! Pokusajte ponovno!" << "\033[0m" << endl;
            } while (player[0].empty());
            cout << "\033[32m" << endl << "Ime 1. igraca (" << player[0] << ") uspjesno spremljeno. :)" << "\033[0m" << endl << endl;
            do
            {
                do {
                    cout << "Unesite ime 2. igraca: ";
                    getline(cin, player[1]);
                    if (player[1].empty())
                        cout << "\033[31m" << "Niste unijeli ime igraca! Pokusajte ponovno!" << "\033[0m" << endl;
                } while (player[1].empty());

            } while (NameCheck(player[0], player[1]));

            ofstream save("save.bin", ios::binary | ios::out);
            player[0].resize(32);
            player[1].resize(32);

            for (int i = 0; i < 2; i++)
            {
                save.write((char*)&player[i][0], 32);
            }
            save.close();
            for (int i = 0; i < 2; i++)
                cout << "Zeton " << i + 1 << ". igraca ce biti: " << "\033[32m" << id[i] << "\033[0m" << endl;
            system("pause");
            system("cls");

            //spremanje polja,za svaki slučaj


            ShowGrid(grid);
            //početak igre
            int DropChoice, full = 0, again = 0, win = 0;
            do
            {
                for (int i = 0; i < 2; i++)
                {
                    DropChoice = PlayerDrop(grid, player[i], id[i]);
                    CheckBellow(grid, id[i], DropChoice);
                    system("cls");
                    ShowGrid(grid);
                    win = Check4(grid, id[i], win);
                    if (win == 1)
                    {
                        PlayerWin(player[i]);
                        again = Restart(grid);
                        if (again == 2)
                            break;
                    }
                }
                full = FullGrid(grid);
                if (full == 8)
                {
                    cout << endl << "\033[32m" << "Ploca je puna, rezultat je izjednacen!" << "\033[0m" << endl;
                    again = Restart(grid);
                }
            } while (again != 2);

        }
        else if (choiceMenu == "3") {
            ifstream save("save.bin", ios::binary | ios::in);
            //string* player_nigga = new string[2];
            player[0].resize(32);
            player[1].resize(32);


            for (int i = 0; i < 2; i++)
            {
                //cout << sizeof(player[i]) << endl;
                //cout << sizeof(id[i]);
                save.read((char*)&player[i][0], 32);
                cout << player[i]<< endl;
                // save.read((char*)&id[i], 1);
                // cout << p[i] << endl;
            }
            save.close();

            ifstream saveGrid("saveGrid.bin", ios::binary | ios::in);
            save.read((char*)&grid, sizeof(grid));
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    cout << grid[i][j] << " ";
                }
                cout << endl;
            }
            saveGrid.close();

        }
        else if (choiceMenu == "4") {

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