#include <iostream>
#include <fstream>
#include <string>
#include "GameChecks.h"
#include "Output.h"
using namespace std;

struct info;

int main()
{

    string text = "\t\t Pravila\n- Svaki igrac ima po 21 zeton (ukupno 42)."
        " \n- Trebate skupiti 4 zetona iste boje u nizu : okomito, vodoravno ili dijagonalno."
        "\n- Mozete baciti samo jedan zeton po okretu."
        "\n- Prvi igrac koji spoji 4 jednobojna zetona pobjeduje.";
    fstream file("Rules.bin", ios::binary | ios::out);
    file.write((char*)&text, sizeof(text));
    file.close();

    char grid[6][8] = { {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '} };

    string* player = new string[2];
    char* id = new char[2]{ 'X','O' };

    info flag;
    int DropChoice, again = 0;
    while (1)
    {
        system("cls");
        cout << "Dobrodosli u Spoji 4" << endl << endl;
        cout << "1. ispis pravila igre" << endl;
        cout << "2. pocetak nove igre" << endl;
        cout << "3. ucitavanje prosle igre" << endl;
        cout << "4. izlaz iz programa" << endl << endl;
        cout << "Vas odabir: ";
        string choiceMenu;
        cin >> choiceMenu;
        cin.ignore();
        if (choiceMenu == "1") {

            system("cls");
            file.open("Rules.bin", ios::binary | ios::in);
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


            ofstream save("savePlayers.bin", ios::binary | ios::out);
            player[0].resize(32);
            player[1].resize(32);
            for (int i = 0; i < 2; i++)
                save.write((char*)&player[i][0], 32);
            save.close();


            for (int i = 0; i < 2; i++)
                cout << "Zeton " << i + 1 << ". igraca ce biti: " << "\033[32m" << id[i] << "\033[0m" << endl;
            system("pause");
            system("cls");


            ShowGrid(grid);
            //int DropChoice, again = 0;
        game:
            /*ifstream saveGrid("saveGrid.bin", ios::binary | ios::in);
            saveGrid.read((char*)&grid, sizeof(grid));
            saveGrid.close();*/
            do
            {
                for (int x = 0; x < 2; x++)
                {
                    DropChoice = PlayerDrop(grid, player[x], id[x]);
                    CheckBellow(grid, id[x], DropChoice);
                    //sejvanje ploče
                    ofstream saveGrid("saveGrid.bin", ios::binary | ios::out);
                    saveGrid.write((char*)&grid, sizeof(grid));
                    saveGrid.close();
                    system("cls");
                    ShowGrid(grid);
                    flag.win[x] = Check4(grid, id[x], flag, x);
                    if (flag.win[x] == 1)
                    {
                        PlayerWin(player[x]);
                        flag.lastPlayer = x;
                        again = Restart(grid);
                        if (again == 2) {

                            break;
                        }


                    }
                    flag.full = FullGrid(grid, flag);
                    if (flag.full == 8)
                    {
                        cout << endl << "\033[32m" << "Ploca je puna, rezultat je izjednacen!" << "\033[0m" << endl;
                        again = Restart(grid);
                        if (again == 2) {
                            //spremanje zastavica

                            break;
                        }
                    }
                }

            } while (again != 2);
        }
        else if (choiceMenu == "3") {

            ifstream saveGrid("saveGrid.bin", ios::binary | ios::in);
            saveGrid.read((char*)&grid, sizeof(grid));
            saveGrid.close();
            system("cls");
            //ShowGrid(grid);

            ifstream saveFlags("saveFlag.bin", ios::binary | ios::in);
            saveFlags.read((char*)&flag, sizeof(info));
            saveFlags.close();

            if (flag.full == 1) {
                ShowGrid(grid);
                cout << endl << "\033[32m" << "Rezultat je nerijesen." << "\033[0m" << endl;
            }
            //ShowGrid(grid);
            ifstream savePlayers("savePlayers.bin", ios::binary | ios::in);
            player[0].resize(32);
            player[1].resize(32);
            for (int i = 0; i < 2; i++) {
                savePlayers.read((char*)&player[i][0], 32);
                cout << player[i] << endl;
            }
            savePlayers.close();
            //ShowGrid(grid);

            for (int i = 0; i < 2; i++)
            {
                if (flag.win[i] == 1) {
                    ShowGrid(grid);
                    PlayerWin(player[i]);
                    again = Restart(grid);
                }
            }

            //ShowGrid(grid);
            cout << flag.lastPlayer << endl;
            cout << flag.full << endl;







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
