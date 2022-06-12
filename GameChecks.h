#pragma once
#include <iostream>
#include <fstream>   //za save&load
#include <windows.h> //za boje
#include <algorithm> //za for_each
#include "Output.h"  //za struct
using namespace std;

fstream save;

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

void CheckBellow(char grid[6][8], PlayerInfo ActivePlayer, int DropChoice)
{
    save.open("SaveResults.bin", ios::binary | ios::app | ios::out);
    int lgt = 5, t = 0;
    do {
        if (grid[lgt][DropChoice - 1] == ' ')
        {
            grid[lgt][DropChoice - 1] = ActivePlayer.ID;
            //spremanje žetona u polju
            save.write((char*) &grid[lgt][DropChoice - 1], sizeof(char));
            save.close();
            t = 1;
        }
        else
            --lgt;
    } while (t != 1);
  
}

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
            //if (i < 2 && j > 3)
                if (grid[i][j] == znak && grid[i + 1][j - 1] == znak && grid[i + 2][j - 2] == znak && grid[i + 3][j - 3] == znak)
                    win = 1;
            //if (j > 2)
                if (grid[i][j] == znak && grid[i][j - 1] == znak && grid[i][j - 2] == znak && grid[i][j - 3] == znak)
                    win = 1;
        }
    }
    return win;
}

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
        save.open("SaveResults.bin", ios::binary | ios::out | ios::app);
        save.write((char*)&player2.Name, sizeof(player2.Name));
        cout << "\033[32m" << endl << "Ime 2. igraca (" << player2.Name << ") uspjesno spremljeno. :)" << "\033[0m" << endl << endl;
        save.close();
        return false;
    }
}


