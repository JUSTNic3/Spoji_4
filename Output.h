#pragma once
#include <iostream>
#include <windows.h>
using namespace std;

struct PlayerInfo {
    string Name;
    char ID;
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

void PlayerWin(PlayerInfo ActivePlayer)
{
    cout << endl << "\033[32m" << ActivePlayer.Name << ", pobijedio si!" << "\033[0m" << endl;
}
