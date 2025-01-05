#include <bits/stdc++.h>
#include <iostream>
using namespace std;

#define RESET "\033[0m"
#define RED "\033[1m\033[31m"
#define GREEN "\033[1m\033[32m"
#define DEPTH 9  // how far the computer searches in the game
#define Infinity std::numeric_limits<double>::infinity() // Can replace this

int userid = 0;
int compid = 1;
int counter = 0;
int value;
int iter = 0; // Can comment this line
char gameboard[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

// someone please lmk in which order these variables 
// should be initalized to reduce amount of data used 
// via stack alignment

std::ostream& operator<<(std::ostream& stream, char& chr) // Operator overloading is just there for decorations :D
{
    if(chr == 'O')
    {
        stream << RED << 'O' << RESET;
        return stream;
    }
    else if(chr == 'X')
    {
        stream << GREEN << 'X' << RESET;
        return stream;
    }
    else
    {
        if(isdigit(chr))
        {
            stream << chr - '0';
            return stream;
        }
        else
        {
            stream << chr;
            return stream;
        }
    }
}

void DrawBoard()
{
    cout << 
    "    |     |    \n"
    " " << gameboard[0] << "  |  " << gameboard[1] << "  |  " << gameboard[2] << "\n"
    "    |     |    \n"
    "----+-----+------\n"
    "    |     |    \n"
    " " << gameboard[3] << "  |  " << gameboard[4] << "  |  " << gameboard[5] << "\n"
    "    |     |    \n"
    "----+-----+------\n"
    "    |     |    \n"
    " " << gameboard[6] << "  |  " << gameboard[7] << "  |  " << gameboard[8] << "\n"
    "    |     |    \n\n";
}
int CheckWin()
{
    if(gameboard[0] == gameboard[4] && gameboard[4] == gameboard[8] || gameboard[2] == gameboard[4] && gameboard[4] == gameboard[6])
    {
        if(gameboard[4] == 'X')
        {
            return 0;
        }
        else // if(gameboard[4] == 'O')
        {
            return 1;
        }
    }
    else if(gameboard[0] == gameboard[3] && gameboard[3] == gameboard[6] && gameboard[6] == 'X' || gameboard[1] == gameboard[4] && gameboard[4] == gameboard[7] && gameboard[7] == 'X' || gameboard[2] == gameboard[5] && gameboard[5] == gameboard[8] && gameboard[8] == 'X')
    {
        return 0;
    }
    else if(gameboard[0] == gameboard[3] && gameboard[3] == gameboard[6] && gameboard[6] == 'O' || gameboard[1] == gameboard[4] && gameboard[4] == gameboard[7] && gameboard[7] == 'O' || gameboard[2] == gameboard[5] && gameboard[5] == gameboard[8] && gameboard[8] == 'O')
    {
        return 1;
    }
    else if(gameboard[0] == gameboard[1] && gameboard[1] == gameboard[2] && gameboard[2] == 'X' || gameboard[3] == gameboard[4] && gameboard[4] == gameboard[5] && gameboard[5] == 'X' || gameboard[6] == gameboard[7] && gameboard[7] == gameboard[8] && gameboard[8] == 'X')
    {
        return 0;
    }
    else if(gameboard[0] == gameboard[1] && gameboard[1] == gameboard[2] && gameboard[2] == 'O' || gameboard[3] == gameboard[4] && gameboard[4] == gameboard[5] && gameboard[5] == 'O' || gameboard[6] == gameboard[7] && gameboard[7] == gameboard[8] && gameboard[8] == 'O')
    {
        return 1;
    }
    else
    {
        value = 2;
        for(int elem = 0; elem < 9; ++elem)
        {
            if(isdigit(gameboard[elem]))
            {
                value = 10;
                break;
            }
        }
        return value;
    }
    // 0 is player
    // 1 is computer
    // 2 is draw
    // 10 is keep going
    // gameboard[ROW][COL]
    // Please optimize Checkwin()
}
void IsGameOver()
{
    if(CheckWin() != 10)
    {
        if(CheckWin() == 0)
        {
            //system("clear");
            DrawBoard();
            cout << "Player has won!\n";
            exit(0);
        }
        else if(CheckWin() == 1)
        {
            //system("clear");
            DrawBoard();
            cout << "Computer has won!\n";
            exit(0);
        }
        else if(CheckWin() == 2)
        {
            //system("clear");
            DrawBoard();
            cout << "Draw!\n";
            exit(0);
        }
    }
}
void Player()
{
    int num;
    cout << "Enter a number 1-9: ";cin >> num;
    if(gameboard[num - 1] != 'X' && gameboard[num - 1] != 'O')
    {
        gameboard[num - 1] = 'X';
        ++counter;
        if(counter >= 5)
        {
            IsGameOver();
        }
    }
    else
    {
        cout << "Wrong move please try again!\n";
        Player();
    }
}
int Minimax(int depth, bool Maximizing)
{
    if(CheckWin() != 10 || depth == DEPTH)
    {
        ++iter;
        if(CheckWin() == 1)         // Computer
        {
            return 10 - depth;
        }
        else if(CheckWin() == 0)    // Player
        {
            return -10 + depth;
        }
        else                        // Draw
        {
            return 0;
        }
    }
    if(Maximizing)                // Computer simulation
    {
        int Best = -Infinity;
        for(int i = 0; i < 9; ++i)
        {
            if(isdigit(gameboard[i]))
            {
                gameboard[i] = 'O';
                Best = max(Best, Minimax(depth + 1, false));
                gameboard[i] = char('0' + (i + 1));
            }
        }
        return Best;
    }
    else                            // Player simulation
    {
        int Best = Infinity;
        for(int i = 0; i < 9; ++i)
        {
            if(isdigit(gameboard[i]))
            {
                gameboard[i] = 'X';
                Best = min(Best, Minimax(depth + 1, true));
                gameboard[i] = char('0' + (i + 1));
            }
        }
        return Best;
    }
}

int AlphaBetaPruning(int depth, bool Maximizing, int alpha, int beta)
{
    if(CheckWin() != 10 || depth == DEPTH)
    {
        ++iter;                     // Can comment this line
        if(CheckWin() == 1)         // Computer
        {
            return 10 - depth;
        }
        else if(CheckWin() == 0)    // Player
        {
            return -10 + depth;
        }
        else                        // Draw
        {
            return 0;
        }
    }
    if(Maximizing)                   // Computer simulation
    {
        int Best = -Infinity;
        for(int i = 0; i < 9; ++i)
        {
            if(isdigit(gameboard[i]))
            {
                gameboard[i] = 'O';
                Best = max(Best, AlphaBetaPruning(depth + 1, false, alpha, beta));
                gameboard[i] = char('0' + (i + 1));
                alpha = max(alpha, Best);
                if(beta <= alpha)
                {
                    break;
                }
            }
        }
        return Best;
    }
    else                               // Player simulation
    {
        int Best = Infinity;
        for(int i = 0; i < 9; ++i)
        {
            if(isdigit(gameboard[i]))
            {
                gameboard[i] = 'X';
                Best = min(Best, AlphaBetaPruning(depth + 1, true, alpha, beta));
                gameboard[i] = char('0' + (i + 1));
                beta = min(beta, Best);
                if (beta <= alpha)
                {
                    break;
                }
            }
        }
        return Best;
    }
}
void Computer()
{
    int MaxScore = -Infinity;
    int Index;
    for(int i = 0; i < 9; ++i)
    {
        if(isdigit(gameboard[i]))
        {
            gameboard[i] = 'O';
            //int Score = Minimax(0, false);
            int Score = AlphaBetaPruning(0, false, -Infinity, Infinity);
            gameboard[i] = char('0' + (i + 1));
            if(Score > MaxScore)
            {
                MaxScore = Score;
                Index = i;
            }
        }
    }
    /* CAN COMMENT THIS SECTION */
    cout << "\033[1m\033[33mCPU has searched " << "\033[1m\033[36m" << iter << "\033[0m" << " \033[1m\033[33mmoves total\033[0m" << "\n\n";
    iter = 0;
    /* CAN COMMENT THIS SECTION */
    gameboard[Index] = 'O';
    ++counter;
    if(counter >= 5)
    {
        IsGameOver();
    }
}
int main()
{
    char choice;
    cout << "Do you want to go first[Y/N]: ";cin >> choice;
    // change this into switch statements
    if(tolower(choice) == 'y')
    {
        while (true)
        {
            DrawBoard();
            Player();
            Computer();
        }
    }
    else if(tolower(choice) == 'n')
    {
        while (true)
        {
            Computer();
            DrawBoard();
            Player();
        }
    }
    else
    {
        cout << "[-] Error input please enter in a better input next time :D\n";
        exit(EXIT_FAILURE);
    }
}
