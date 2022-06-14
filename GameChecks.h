#pragma once
#include <iostream>
#include <typeinfo> //provjera vrste varijable
#include <fstream>   //za save&load
#include <windows.h> //za boje
#include <algorithm> //za for_each
#include "Output.h"  //za struct
using namespace std;

struct info {
    int full = 0;
    int win[2];
    int lastPlayer = 0;
};

int PlayerDrop(char grid[6][8], string player, char id)
{
    int DropChoice = 0;
    do
    {
        cout << endl << player << "(" << "\033[32m" << id << "\033[0m" << ")" << ", tvoj red. ";
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

void CheckBellow(char grid[6][8], char id, int DropChoice)
{
    int lgt = 5, t = 0;
    do {
        if (grid[lgt][DropChoice - 1] == ' ')
        {
            grid[lgt][DropChoice - 1] = id;
            t = 1;
        }
        else
            --lgt;
    } while (t != 1);
}

int Check4(char grid[6][8], char id, info flag, int x)
{
    char znak = id;
    flag.win[x] = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (grid[i][j] == znak && grid[i + 1][j + 1] == znak && grid[i + 2][j + 2] == znak && grid[i + 3][j + 3] == znak)
                flag.win[x] = 1;
            if (grid[i][j] == znak && grid[i][j + 1] == znak && grid[i][j + 2] == znak && grid[i][j + 3] == znak)
                flag.win[x] = 1;
            if (grid[i][j] == znak && grid[i + 1][j] == znak && grid[i + 2][j] == znak && grid[i + 3][j] == znak)
                flag.win[x] = 1;
            //if (i < 2 && j > 3)
            if (grid[i][j] == znak && grid[i + 1][j - 1] == znak && grid[i + 2][j - 2] == znak && grid[i + 3][j - 3] == znak)
                flag.win[x] = 1;
            //if (j > 2)
            if (grid[i][j] == znak && grid[i][j - 1] == znak && grid[i][j - 2] == znak && grid[i][j - 3] == znak)
                flag.win[x] = 1;
        }
    }
    return flag.win[x];
}

int Restart(char grid[6][8])
{
    int restart = 0;
    do {
        cout << "Zelite li zaigrati ponovno? Da(1) Ne(2) ";
        cin >> restart;
        if (restart == 1)
        {
            system("cls");
            Headline();
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

int FullGrid(char grid[6][8], info flag)
{
    flag.full = 0;
    for (int i = 0; i < 8; ++i)
    {
        if (grid[1][i] != ' ')
            ++flag.full;
    }
    return flag.full;
}

bool NameCheck(string player1, string player2)
{

    player1.erase(remove(player1.begin(), player1.end(), ' '), player1.end());
    player2.erase(remove(player2.begin(), player2.end(), ' '), player2.end());

    for_each(player1.begin(), player1.end(), [](char& c) {c = tolower(c); });
    for_each(player2.begin(), player2.end(), [](char& c) {c = tolower(c); });
    if (player1 == player2) {
        cout << "\033[31m" << "Ime je vec upotrebljeno! Pokusajte ponovmo!" << "\033[0m" << endl;
        return true;
    }
    else {

        cout << "\033[32m" << endl << "Ime 2. igraca (" << player2 << ") uspjesno spremljeno. :)" << "\033[0m" << endl << endl;

        return false;
    }
}
