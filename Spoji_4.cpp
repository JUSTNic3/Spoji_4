#include <iostream>
#include <fstream>
#include <string>
#include "GameChecks.h"
#include "Output.h"
using namespace std;

struct Flags {
    int deleting;
    int win = 0;
    int full = 0;
    int again = 0;
};


int main()
{
    fstream file("rules.bin", ios::binary | ios::out);
    string text="\t\t Pravila\n- Svaki igrac ima po 21 zeton (ukupno 42)."
                " \n- Trebate skupiti 4 zetona iste boje u nizu : okomito, vodoravno ili dijagonalno."
                "\n- Mozete baciti samo jedan zeton po okretu."
                 "\n- Prvi igrac koji spoji 4 jednobojna zetona pobjeduje.";
    file.write((char*)&text, sizeof(text));
    file.close();

    PlayerInfo player1, player2;
    Flags info;//je za zastavice koje ce nam pomoc pri loadanju igre prije gasenja programa
    char grid[6][8];

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

            fstream save;
            system("cls");

            cout << "ODABIR IMENA IGRACA" << endl << endl;
            cout << "Spremanje igraca i zetona ce se izvrsiti pojedinacno" << endl;
	        do {
		        cout << "Unesite ime 1. igraca: ";
		        getline(cin, player1.Name);
		        if(player1.Name.empty())
			        cout << "\033[31m" << "Niste unijeli ime igraca! Pokusajte ponovno!" << "\033[0m" << endl;
	        } while (player1.Name.empty());

            //spremanje 1. igraca
            save.open("SaveResults.bin",ios::binary | ios::app | ios::out);
            save.write((char*) &player1.Name,sizeof(player1.Name));
            save.close();
	        cout << "\033[32m" << endl << "Ime 1. igraca (" << player1.Name << ") uspjesno spremljeno. :)" << "\033[0m" << endl << endl;
	        do
	        {
		        do {
			        cout << "Unesite ime 2. igraca: ";
			        getline(cin, player2.Name);
			        if(player2.Name.empty())
				        cout << "\033[31m" << "Niste unijeli ime igraca! Pokusajte ponovno!" << "\033[0m" << endl;
		        } while (player2.Name.empty());
	
	        } while (NameCheck(player1, player2));
           

            player1.ID = 'X';
            player2.ID = 'O';
            //spremanje žetona;
            save.open("SaveResults.bin", ios::binary | ios::app | ios::out);
            save.write((char*)&player1.ID, sizeof(player1.ID));
            save.close();
            save.open("SaveResults.bin", ios::binary | ios::app | ios::out);
            save.write((char*)&player2.ID, sizeof(player2.ID));
            save.close();


            cout << endl << "Zeton 1. igraca ce biti: " << "\033[32m" << player1.ID << "\033[0m" << endl;
            cout << "Zeton 2. igraca ce biti: " << "\033[32m" << player2.ID << "\033[0m" << endl << endl;

            system("pause");
            system("cls");

            //spremanje polja,za svaki slučaj
            save.open("SaveResults.bin", ios::binary | ios::app | ios::out);
            for (int i = 0; i < 6; i++)
            {
                for (int j = 0; j < 8; j++) 
                {
                    grid[i][j] = ' ';
                    save.write((char*)&grid[i][j], sizeof(char));   //spremanje polja ak neko izađe iz igre
                }
            }
            save.close();
            ShowGrid(grid);
            
            
            int DropChoice, full = 0,again=0,win=0;
            //početak igre
            do
            {
                info.deleting = 0;
                save.write((char*)&info.deleting, sizeof(int));
                save.close();
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
        else if (choiceMenu == "3") {

            
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