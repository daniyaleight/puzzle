#include <iostream>
#include <fstream>

using namespace std;

//Functions
void LoadShapes();
void PrintShape(int);
void RotateShape(int);
void PrintSolution();
void FragmentSize(int, int, int &);
bool BoardhasAppropriateFragment();
bool CanPush(int, int, int);
void PushShape(int, int, int);
void PopShape(int, int, int);
void Findsolution(int, int, int);

//ASCII Charachters
char td = 179;
char tr = 192;
char trd = 195;
char tl = 217;
char tld = 180;
char tlr = 193;
char lr = 196;
char rd = 218;
char ld = 191;
char lrd = 194;
char tlrd = 197;
char s = 32;

//Board
char board[6][10] = {0};

//Global Variables
char shapes[12][5][5];
int shapeRotationCount[12];
bool usedShapes[12] = {false};
int answerCount = 0;

int main(int argc, char const *argv[])
{
    LoadShapes();

    Findsolution(0, 0, 0);

    cout << answerCount;

    return 0;
}

void LoadShapes()
{
    int asc = 96;
    int x;

    ifstream fin;

    fin.open("Shapes.txt");

    for (int shapeNo = 0; shapeNo < 12; shapeNo++)
    {
        asc++;

        fin >> shapeRotationCount[shapeNo];

        for (int col = 0; col < 5; col++)
        {
            for (int row = 0; row < 5; row++)
            {
                fin >> x;
                if (x == 1)
                    shapes[shapeNo][col][row] = (char)asc;
                else
                {
                    // shapes[shapeNo][col][row] = '0';
                }
            }
        }
    }
    fin.close();
}

void RotateShape(int shapeNo)
{
    char temp[5][5] = {0};
    int x;

    //Rotate shape and Copy to temp
    for (int row = 0; row < 5; row++)
        for (int col = 0; col < 5; col++)
        {
            temp[5 - 1 - col][row] = shapes[shapeNo][row][col];
        }
    //Shift temp Up
    x = 0;
    for (int col = 0; col < 5; col++)
    {
        x |= temp[0][col];
    }
    while (!x)
    {
        for (int row = 0; row < (5 - 1); row++)
            for (int col = 0; col < 5; col++)
            {
                temp[row][col] = temp[row + 1][col];
            }
        for (int col = 0; col < 5; col++)
        {
            temp[5 - 1][col] = 0;
        }
        x = 0;
        for (int col = 0; col < 5; col++)
        {
            x |= temp[0][col];
        }
    }

    //Shift temp Left
    x = 0;
    for (int row = 0; row < 5; row++)
    {
        x |= temp[row][0];
    }
    while (!x)
    {
        for (int row = 0; row < 5; row++)
            for (int col = 0; col < (5 - 1); col++)
            {
                temp[row][col] = temp[row][col + 1];
            }
        for (int row = 0; row < 5; row++)
        {
            temp[row][5 - 1] = 0;
        }
        x = 0;
        for (int row = 0; row < 5; row++)
        {
            x |= temp[row][0];
        }
    }

    //Copy temp To shapes
    for (int row = 0; row < 5; row++)
        for (int col = 0; col < 5; col++)
        {
            shapes[shapeNo][row][col] = temp[row][col];
        }
}

void PrintSolution()
{

    cout << endl;

    //PRINT FIRST ROW
    cout << rd << lr;
    for (int col = 1; col < 10; col++)
    {
        if (board[0][col] == board[0][col - 1])
        {
            cout << lr << lr;
        }
        else
        {
            cout << lrd << lr;
        }
    }
    cout << ld << endl;

    //PRINT INNER ROWS
    for (int row = 1; row < 6; row++)
    {
        if (board[row][0] == board[row - 1][0])
        {
            cout << td << s;
        }
        else
        {
            cout << trd << lr;
        }

        for (int col = 1; col < 10; col++)
        {
            if (board[row][col] == board[row][col - 1])
            {
                if (board[row][col] == board[row - 1][col])
                {
                    if (board[row - 1][col] == board[row - 1][col - 1])
                    {
                        cout << s << s;
                    }
                    else
                    {
                        cout << tl << s;
                    }
                }
                else
                {
                    if (board[row - 1][col] == board[row - 1][col - 1])
                    {
                        cout << lr << lr;
                    }
                    else
                    {
                        if (board[row][col - 1] != board[row - 1][col - 1])
                        {
                            cout << tlr << lr;
                        }
                    }
                    if (board[row][col - 1] == board[row - 1][col - 1])
                    {
                        cout << tr << lr;
                    }
                }
            }
            else
            {
                if (board[row][col] == board[row - 1][col])
                {
                    if (board[row - 1][col] == board[row - 1][col - 1])
                    {
                        cout << ld << s;
                    }
                    else
                    {
                        if (board[row][col - 1] != board[row - 1][col - 1])
                        {
                            cout << tld << s;
                        }
                    }
                    if (board[row][col - 1] == board[row - 1][col - 1])
                    {
                        cout << td << s;
                    }
                }
                else
                {
                    if (board[row - 1][col] == board[row - 1][col - 1])
                    {
                        if (board[row][col - 1] == board[row - 1][col - 1])
                        {
                            cout << rd << lr;
                        }
                        else
                        {
                            cout << lrd << lr;
                        }
                    }
                    else
                    {
                        if (board[row][col - 1] != board[row - 1][col - 1])
                        {
                            cout << tlrd << lr;
                        }
                    }
                    if (board[row][col - 1] == board[row - 1][col - 1])
                    {
                        if (board[row - 1][col] != board[row - 1][col - 1])
                        {
                            cout << trd << lr;
                        }
                    }
                }
            }
        }

        if (board[row][9] == board[row - 1][9])
        {
            cout << td;
        }
        else
        {
            cout << tld;
        }
        cout << endl;
    }

    //PRINT LAST ROW
    cout << tr << lr;
    for (int col = 1; col < 10; col++)
    {
        if (board[5][col] == board[5][col - 1])
        {
            cout << lr << lr;
        }
        else
        {
            cout << tlr << lr;
        }
    }
    cout << tl << endl;

    return;
}

void FragmentSize(int row, int col, int &fz)
{

    if (row < 0 || col < 0 || row > 5 || col > 9)
    {
        return;
    }

    if (board[row][col] == '0')
    {
        board[row][col] = -1;
        fz += 1;
    }
    else
    {
        return;
    }

    FragmentSize(row - 1, col, fz);
    FragmentSize(row + 1, col, fz);
    FragmentSize(row, col - 1, fz);
    FragmentSize(row, col + 1, fz);
}

bool BoardhasAppropriateFragment()
{
    bool hasFragment = false;
    int fz;

    for (int r = 0; r < 6; r++)
    {
        for (int c = 0; c < 10; c++)
            if (board[r][c] == 0)
            {
                fz = 0;
                FragmentSize(r, c, fz);

                if (fz % 5)
                {
                    hasFragment = true;
                    break;
                }
            }
        if (hasFragment)
        {
            break;
        }
    }

    for (int r = 0; r < 6; r++)
    {
        for (int c = 0; c < 10; c++)
        {
            if (board[r][c] == -1)
            {
                board[r][c] = 0;
            }
        }
    }
    return hasFragment;
}


bool CanPush(int shapeNo, int row, int col)
{
    int r, c;
    int bias = 0;

    while (shapes[shapeNo][0][bias] == 0)
        bias++;

    if (bias > col)
        return false;

    for (r = 0; r < 5; r++)
        for (c = 0; c < 5; c++)
            if (shapes[shapeNo][r][c] > 0)
            {
                if ((row + r) > (6 - 1) || (col + c - bias) > (10 - 1))
                    return false;

                if (board[row + r][col + c - bias] > 0)
                    return false;
            }
    return true;
}


void PushShape(int shapeNo, int row, int col)
{
    int r, c;
    int bias = 0;

    while (shapes[shapeNo][0][bias] == 0)
        bias++;

    for (r = 0; r < 5; r++)
        for (c = 0; c < 5; c++)
            if (shapes[shapeNo][r][c] > 0)
                board[row + r][col + c - bias] = shapes[shapeNo][r][c];
}


void PopShape(int shapeNo, int row, int col)
{
    int r, c;
    int bias = 0;

    while (shapes[shapeNo][0][bias] == 0)
        bias++;

    for (r = 0; r < 5; r++)
        for (c = 0; c < 5; c++)
            if (shapes[shapeNo][r][c])
                board[row + r][col + c - bias] = 0;
}


void Findsolution(int shapeCounter, int row, int col)
{
    int shapeNo, rotate;

    if (shapeCounter == 12)
    {
        PrintSolution();
        cout << "Press Enter To Continue...";
        answerCount++;
        cin.get();
        cout << "Please wait..." << endl;
        return;
    }

    if (BoardhasAppropriateFragment())
        return;

    while (board[row][col] != 0)
    {
        if (col > (10 - 2))
        {
            row++;
            col = 0;
        }
        else
        {
            col++;
        }
    }

    for (shapeNo = 0; shapeNo < 12; shapeNo++)
    {
        if (!usedShapes[shapeNo])
        {
            usedShapes[shapeNo] = true;
            for (rotate = 0; rotate < shapeRotationCount[shapeNo]; rotate++)
            {
                RotateShape(shapeNo);
                if (CanPush(shapeNo, row, col))
                {
                    PushShape(shapeNo, row, col);
                    // shapeOrder[shapeCounter]=shapeNo+1;
                    Findsolution(shapeCounter + 1, row, col);
                    // shapeOrder[shapeCounter]=0;
                    PopShape(shapeNo, row, col);
                }
            }
            usedShapes[shapeNo] = false;
        }
    }
}
