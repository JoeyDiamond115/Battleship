#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int boardRows = 6;
const int boardColumns = 6;
int board[boardRows][boardColumns];
const int maxShips = 4;
int attemptedGuesses;

void Create_Board()
{
    for (int r = 0; r < boardRows; r++)
    {
        for (int c = 0; c < boardColumns; c++)
        {
            board[r][c] = 0;
        }
    }
}

void Show_Board()
{
    for (int r = 0; r < boardRows; r++)
    {
        for (int c = 0; c < boardColumns; c++)
        {
            if (board[r][c] == 1)
            {
                cout << "0 ";
            }
            else
            {
                cout << board[r][c] << " ";
            }
        }
        cout << endl;
    }
}

void Randomize_Ships()
{
    int shipsPlaced = 0;
    while (shipsPlaced < maxShips)
    {
        srand(time(0));
        int x = rand() % boardRows;
        int y = rand() % boardColumns;
        if (board[x][y] != 1)
        {
            shipsPlaced++;
            board[x][y] = 1;
        }
    }
}

void Setup_Game()
{
    Create_Board();
    Show_Board();
    Randomize_Ships();
}

bool Check_Left(int x, int y)
{
    if (board[x - 1][y] == 1)
    {
        board[x][y] = 3;
        cout << "Near Miss. You're one coordinate away from a hit!" << endl;
        return true;
    }
    return false;
}

bool Check_Right(int x, int y)
{
    if (board[x + 1][y] == 1)
    {
        board[x][y] = 3;
        cout << "Near Miss. You're one coordinate away from a hit!" << endl;
        return true;
    }
    return false;
}

bool Check_Up(int x, int y)
{
    if (board[x][y + 1] == 1)
    {
        board[x][y] = 3;
        cout << "Near Miss. You're one coordinate away from a hit!" << endl;
        return true;
    }
    return false;
}

bool Check_Down(int x, int y)
{
    if (board[x][y - 1] == 1)
    {
        board[x][y] = 3;
        cout << "Just nearly missed. You're one coordinate away from a hit!" << endl;
        return true;
    }
    return false;
}

bool Attack_Coordinate(int x, int y)
{
    attemptedGuesses++;
    if (board[x][y] == 1) 
    {
        board[x][y] = 5;
        cout << "HIT! YOU SUNK A SHIP :)" << endl;
        return true;
    }
    else if (Check_Down(x, y) || Check_Up(x, y) || Check_Left(x, y) || Check_Right(x, y))
    {
        return false;
    }
    else
    {
        board[x][y] = 0;
        cout << "Missed and hit nothing :(" << endl;
        return false;
    }
}

void Guess_Coordnite()
{
    int posx;
    int posy;
    cout << "Enter a coordinate to launch a missle (Row, Column): "; cin >> posx >> posy;
    Attack_Coordinate(posx - 1, posy - 1);
}

int Ships_Left()
{
    int s = 0;
    for (int r = 0; r < boardRows; r++)
    {
        for (int c = 0; c < boardColumns; c++)
        {
            if (board[r][c] == 1)
            {
                s++;
            }
        }
    }
    return s;
}

void Run_Game() {
    Guess_Coordnite();
    Show_Board();
    cout << "Ships remaining: " << Ships_Left() << endl;
    cout << "---------------------" << endl;
    if (Ships_Left() > 0)
    {
        Run_Game();
    }
    else if (Ships_Left() <= 0)
    {
        cout << "You sunk every ship!!!" << endl;
        cout << "You guessed " << attemptedGuesses << " times throughout the game." << endl;
    }
}

int main()
{   
    Setup_Game();
    Run_Game();
    return 0;
}
