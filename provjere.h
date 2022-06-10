#pragma once
struct PlayerInfo {
    string PlayerName;
    char PlayerID{ ' ' };
};

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
            cout << "\033[31m" << "Krivi stupac! Pokusajte ponovno." << "\033[0m" << endl;
    } while (DropChoice < 1 || DropChoice > 8);
    return DropChoice;
}

void CheckBellow(char grid[6][8], PlayerInfo ActivePlayer, int DropChoice)
{
    int lgt = 5, t = 0;
    do {
        if (grid[lgt][DropChoice - 1] == ' ')
        {
            grid[lgt][DropChoice - 1] = ActivePlayer.PlayerID;
            t = 1;
        }
        else

            --lgt;
    } while (t != 1);
}

int Check4(char grid[5][8], PlayerInfo ActivePlayer, int win)
{
    char znak = ActivePlayer.PlayerID;
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
            if (grid[i][j] == znak && grid[i + 1][j - 1] == znak && grid[i + 2][j - 2] == znak && grid[i + 3][j - 3] == znak)
                win = 1;
            if (grid[i][j] == znak && grid[i][j - 1] == znak && grid[i][j - 2] == znak && grid[i][j - 3] == znak)
                win = 1;
        }
    }
    return win;
}

int restart(char grid[6][8])
{
    int restart = 0;
    do {
        cout << "Zelite li zaigrati ponovno? Da(1) Ne(2)" << endl;
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

bool nameCheck(PlayerInfo player1, PlayerInfo player2)
{

    player1.PlayerName.erase(remove(player1.PlayerName.begin(), player1.PlayerName.end(), ' '), player1.PlayerName.end());
    player2.PlayerName.erase(remove(player2.PlayerName.begin(), player2.PlayerName.end(), ' '), player2.PlayerName.end());

    for_each(player1.PlayerName.begin(), player1.PlayerName.end(), [](char& c) {c = tolower(c); });
    for_each(player2.PlayerName.begin(), player2.PlayerName.end(), [](char& c) {c = tolower(c); });
    if (player1.PlayerName == player2.PlayerName) {
        cout << "\033[31m" << "Ime je vec upotrebljeno! Pokusajte ponovmo!" << "\033[0m" << endl;
        return true;
    }
    else {
        cout << "\033[32m" << endl << "Ime 2. igraca (" << player2.PlayerName << ") uspjesno dodano. :)" << "\033[0m" << endl << endl;
        return false;
    }
}
