/********************************************
** File: Proj1.cpp
** Project: CMSC 202 Project 1, Spring 2020
** Author: Rooklyn Kline
** Date: 2/25/19
** Section: 23
** E-mail: rkline2@umbc.edu
**
** This program is based off of the game "fifteen"
** where the user will be manipulating a scrambled board.    
** The user must have the tiles in decending order from  
** the left-hand corner to the bottom right-hand corner. 
** The program will detect if the user has won the game or not
** as well as many other input validations.  
**
*********************************************/


#include <iostream>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
using namespace std;


const int MAXCHAR = 80; // maximum amount of characters 
const int MAXROW = 4; // maximum amount of rows 
const int MAXCOL = 4; // maximum amount of columns
const int MAXELMNT = 16; // heighest amount of elements in a array
const char WINNER = 'W'; // used to determine if the user has won
const char LOSER = 'L'; // used to determine if the user has lost
const char YES = 'y'; // user input responce
const char NO = 'n'; // user input responce
const char WRONGVAL = '!'; // indicates the user has entered a wrong value
const char TR_EDGE = '}'; // represents the user selecting the top right corner
const char TL_EDGE = '{'; // represents the user selecting the top left corner
const char BL_EDGE = '('; // represents the user selecting the bottom left corner 
const char BR_EDGE = ')'; // represents the user selecting the bottom right edge
const char T_SIDE = '^'; // represents the user selecting the top edge
const char B_SIDE = '_'; // represents the user selecting the bottom edge
const char L_SIDE = '['; // represents the user selecting the left edge
const char R_SIDE = ']'; // represents the user selecting the right edge
const char CENTER = '-'; // represents the user selecting a center piece
const int ZEROMKR = 0; // used to find the zero from the board
const int TENDIGIT = 10; // determins the number of digits from an element on the board 
const char SPACE = ' '; // used the space out the numbers on the board  
const char H_BAR = '|'; // used for decorating the board
const char B_BAR = '_'; // used for decorating the board
const char BAR = '-'; // used for decorating the board
const char PERIOD = '.'; // indicates the row and column numbers on the board
const int FIFTHELMT = 5; // used to print a special char one every five times

// startGame
// Given the default board, changes the board based on a .txt file 
void startGame(int board[MAXROW][MAXCOL]);

// selectTile
// Given the board, determines the correct coordinates the user has entered
void selectTile(int board[MAXROW][MAXCOL]);

// swapTile
// Given the board and the user's entered row and column, it will swap
// the tile with the 'zero' tile 
void swapTile(int board[MAXROW][MAXCOL], int usrRow, int usrCol);

// checkDirection
// Given the board and the user's entered row and column, it will dsetermine if
// the coordinates are valid
bool checkDirection(int board[MAXROW][MAXCOL], int usrRow, int usrCol);

// printBoard
// Given the board, prints out the current board
void printBoard(int board[MAXROW][MAXCOL]);

// getBoard
// Given the filename, maximum element and the board, 
// it will modify the board based on the values in the .txt file 
void getBoard(char fileName[], int size, int board[MAXROW][MAXCOL]);

// checkWinner
// Given board, ckecks to see if the user has won the game
char checkWinner(int board[MAXROW][MAXCOL]);

// playGame
// This function is the main foundation of the game
// it allows the user to play the game if they wish to do so 
void playGame();

// findLen
// Given an array of characters or a number, returns the 
// length of the word or the amount of digits in the number 
int findLen(char list[MAXELMNT]);
int findLen(int testNum);

// playAgain
// returns a value which determins if the user wants to play again
char playAgain();

// findLocation
// Given the entered row and columnn, returns 
// the location of the tile 
char findLocation(int usrRow, int usrCol);

// addSpaces
// Given an integer, prints the desired amount of spaces 
void addSpaces(int maxspace);

// createBar 
// given the length of the bar, symbor and/or the amount of spaces
// will print a line of the desired symbol for the board
void createBar(int barLim, char symbol);
void createBar(int barLim, char symbol, int numSpaces);


int main()
{
    char anotherGame = YES;
    while (anotherGame == YES) {
        playGame();
        anotherGame = playAgain();
    }
    return 0;
}


void playGame() {
    int board[MAXROW][MAXCOL] = { {1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,0,15} };
    startGame(board);
    char isWinner = checkWinner(board);
    while (isWinner == LOSER) {
        if (isWinner == LOSER) {
            cout << "Board is not complete" << endl;
        }
        selectTile(board);
        isWinner = checkWinner(board);
    }
    printBoard(board);
    cout << "Winner!" << endl;
}


void startGame(int board[MAXROW][MAXCOL]) {
    int selectBoard = 2;
    char fileName[MAXCHAR] = {};
    int count = 0;

    cout << "Welcome to the Fifteen Game" << endl;
    do {
        cout << "Would you like to load a board? \n"
            << "1. Yes \n" << "2. No \n";
        cin >> selectBoard;
    } while (selectBoard != 1 && selectBoard != 2);
    if (selectBoard == 1) {
        cout << "What is the file name? " << endl;
        cin >> fileName;
        getBoard(fileName, MAXELMNT, board);
    }
}

void getBoard(char fileName[], int size, int board[MAXROW][MAXCOL]) {
    int elmntCount = 0;
    int boardRow = 0;
    int boardCol = 0;

    ifstream inputStream;
    inputStream.open(fileName);
    while (elmntCount <= size) {
        if (boardCol < MAXCOL && boardRow < MAXROW) {
            inputStream >> board[boardRow][boardCol];
            boardCol++;
        }
        else if (boardCol >= MAXCOL && boardRow < MAXROW) {
            boardRow++;
            boardCol = 0;
            inputStream >> board[boardRow][boardCol];
            boardCol++;
        }
        elmntCount++;
    }
    inputStream.close();
}

void addSpaces(int maxspace) {
    for (int space = 1; space < maxspace; space++) {
        cout << SPACE;
    }
}

void createBar(int barLim, char symbol) {
    for (int bar = 1; bar <= barLim; bar++) {
        if (bar == barLim) {
            cout << symbol << endl;

        }
        else if (bar == 1) {
            cout << '\t' << symbol;
        }
        else {
            cout << symbol;
        }
    }
}

void createBar(int barLim, char symbol, int numSpaces) {
    cout << endl;
    addSpaces(MAXROW + 4);
    cout << H_BAR;
    for (int bar = 1; bar <= barLim; bar++) {
        if (bar == barLim) {
            cout << H_BAR << endl;

        }
        else if (bar % FIFTHELMT == 0) {
            cout << H_BAR;
        }
        else if (bar == 1) {
            addSpaces(numSpaces);
            cout << symbol;
        }
        else {
            cout << symbol;
        }
    }
}



void printBoard(int board[MAXROW][MAXCOL]) {
    int underBarLim = (MAXCOL * 3 + MAXCOL * 2);
    int twoDig = 1;
    int numSpace = 2;
    for (int i = 1; i <= MAXCOL; i++) {
        if (i == 1) {
            cout << '\t' << SPACE << i << PERIOD;
        }
        else if (i < MAXCOL && i > 1) {
            // add spaces here
            addSpaces(MAXCOL);
            cout << i << PERIOD;
        }
        else if (i == MAXCOL) {
            addSpaces(MAXCOL);
            cout << i << PERIOD << endl;
        }
    }

    createBar(underBarLim, B_BAR);

    for (int row = 0; row < MAXROW; row++) {
        addSpaces(MAXROW + 2);
        cout << row + 1 << PERIOD << H_BAR;
        for (int col = 0; col < MAXCOL; col++) {
            int checkLen = findLen(board[row][col]);
            if (checkLen == 1) {
                // changes here
                addSpaces(numSpace + 1);
                cout << board[row][col] << SPACE << H_BAR;
            }
            else {
                addSpaces(numSpace);
                cout << board[row][col] << SPACE << H_BAR;
            }
        }
        createBar(underBarLim, BAR, 0);
    }
}

int findLen(char list[MAXELMNT]) {
    int index = 0;
    while (list[index] != 0) {
        index++;
    }
    return index;
}

int findLen(int testNum) {
    int numdigit = 0;
    if (testNum == 0) {
        numdigit = 1;
    }
    while (testNum > 0) {
        testNum /= TENDIGIT;
        ++numdigit;
    }

    return numdigit;
}

char checkWinner(int board[MAXROW][MAXCOL]) {
    char isWinner = 'W';
    for (int row = 0; row < MAXROW; row++) {
        for (int col = 0; col < MAXCOL; col++) {
            if (col + 1 < MAXCOL && row != MAXROW - 1) {
                int testValue = board[row][col + 1];
                if ((testValue - board[row][col]) != 1) {
                    isWinner = 'L';
                }
            }
            else if (col == MAXCOL - 1 && row != MAXROW - 1) {
                int testValue = board[row + 1][0];
                if ((testValue - board[row][col]) != 1) {
                    isWinner = 'L';
                }
            }
            else if ((col == MAXCOL - 1 && row == MAXROW - 1) && (board[row][col] != 0)) {
                isWinner = 'L';
            }
        }
    }
    return isWinner;
}

void swapTile(int board[MAXROW][MAXCOL], int usrRow, int usrCol) {
    for (int row = 0; row < MAXROW; row++) {
        for (int col = 0; col < MAXCOL; col++) {
            if (board[row][col] == 0) {
                board[row][col] = board[usrRow][usrCol];
                board[usrRow][usrCol] = ZEROMKR;
            }

        }
    }
}



void selectTile(int board[MAXROW][MAXCOL]) {
    int usrRow = 0;
    int usrCol = 0;
    char checkVal = 'N';
    bool isValidCoord = true;
    do
    {
        printBoard(board);
        cout << "What is the row (left) and column (top) to slide?" << endl;
        cin >> usrRow;
        cin >> usrCol;
        cout << "Are you sure you want to enter these values? ('Y' or 'N'): ";
        cin >> checkVal;
        cout << endl;
        // input validation
        switch (checkVal)
        {
        case 'y':
        case 'Y':
            checkVal = 'Y';
            break;
        case 'n':
        case 'N':
            cout << "Okay" << endl;
            checkVal = 'N';
            break;
        default:
            cout << "Invald input" << endl;
            cin.clear();
            checkVal = 'N';
            break;
        }
        if (checkVal == 'Y') {
            usrRow--;
            usrCol--;
            isValidCoord = checkDirection(board, usrRow, usrCol);
            if (isValidCoord == false) {
                cout << "Coordinates are not valid" << endl;
            }
        }
    } while (checkVal != 'Y' || isValidCoord == false);

    cout << endl;
    // Swap the tiles
    swapTile(board, usrRow, usrCol);
}

bool checkDirection(int board[MAXROW][MAXCOL], int usrRow, int usrCol) {
    char location = findLocation(usrRow, usrCol);
    bool isValid = false;
    switch (location)
    {
    case WRONGVAL:
        break;
    case TR_EDGE:
        // Top right corner 
        if ((board[usrRow + 1][usrCol] == ZEROMKR) || (board[usrRow][usrCol - 1] == ZEROMKR)) {
            isValid = true;
        }
        break;
    case TL_EDGE:
        // Top left corner
        if ((board[usrRow + 1][usrCol] == ZEROMKR) || (board[usrRow][usrCol + 1] == ZEROMKR)) {
            isValid = true;
        }
        break;
    case BR_EDGE:
        // Bottom right corner
        if ((board[usrRow - 1][usrCol] == ZEROMKR) || (board[usrRow][usrCol - 1] == ZEROMKR)) {
            isValid = true;
        }
        break;
    case BL_EDGE:
        // Bottom left corner
        if ((board[usrRow - 1][usrCol] == ZEROMKR) || (board[usrRow][usrCol + 1] == ZEROMKR)) {
            isValid = true;
        }
        break;
    case T_SIDE:
        // Top edge
        if ((board[usrRow][usrCol + 1] == ZEROMKR) || (board[usrRow + 1][usrCol] == ZEROMKR)
            || (board[usrRow][usrCol - 1] == ZEROMKR)) {
            isValid = true;
        }
        break;
    case B_SIDE:
        // Bottom edge
        if ((board[usrRow][usrCol - 1] == ZEROMKR) || (board[usrRow - 1][usrCol] == ZEROMKR)
            || (board[usrRow][usrCol + 1] == ZEROMKR)) {
            isValid = true;
        }
        break;
    case R_SIDE:
        // Right edge
        if ((board[usrRow + 1][usrCol] == ZEROMKR) || (board[usrRow][usrCol - 1] == ZEROMKR)
            || (board[usrRow - 1][usrCol] == ZEROMKR)) {
            isValid = true;
        }
        break;
    case L_SIDE:
        // Left edge
        if ((board[usrRow - 1][usrCol] == ZEROMKR) || (board[usrRow][usrCol + 1] == ZEROMKR)
            || (board[usrRow + 1][usrCol] == ZEROMKR)) {
            isValid = true;
        }
        break;
    default:
        // Center
        if ((board[usrRow - 1][usrCol] == ZEROMKR) || (board[usrRow][usrCol + 1] == ZEROMKR)
            || (board[usrRow + 1][usrCol] == ZEROMKR) || (board[usrRow][usrCol - 1] == ZEROMKR)) {
            isValid = true;
        }
        break;
    }
    return isValid;
}


char findLocation(int usrRow, int usrCol) {
    char findSide = CENTER;

    // This locates the tile
    if ((usrRow < 0 || usrRow >= MAXROW) || (usrCol < 0 || usrCol >= MAXCOL)) {
        findSide = WRONGVAL;
    }
    // top left corner
    else if (usrRow == 0 && usrCol == 0) {
        findSide = TL_EDGE;
    }

    // top right corner
    else if (usrRow == 0 && usrCol == MAXCOL - 1) {
        findSide = TR_EDGE;
    }

    // bottom left corner
    else if (usrRow == MAXROW - 1 && usrCol == 0) {
        findSide = BL_EDGE;
    }

    // bottom right corner
    else if (usrRow == MAXROW - 1 && usrCol == MAXCOL - 1) {
        findSide = BR_EDGE;
    }

    // top edge
    else if (usrRow == 0) {
        findSide = T_SIDE;
    }

    // bottom edge
    else if (usrRow == MAXROW - 1) {
        findSide = B_SIDE;
    }

    // right edge
    else if (usrCol == MAXCOL - 1) {
        findSide = R_SIDE;
    }

    // left edge
    else if (usrCol == 0) {
        findSide = L_SIDE;
    }
    return findSide;
}

char playAgain() {
    char ans[MAXELMNT] = { WRONGVAL };
    while (ans[0] == WRONGVAL) {
        // asks if the user wants to play again
        cout << "Play again? (y/n): ";
        cin >> ans;
        int valLen = findLen(ans);
        if (valLen == 1) {
            switch (ans[0]) {
            case 'y':
            case 'Y':
                cout << endl;
                cout << "Loading a new game..." << endl;
                ans[0] = 'y';
                break;
            case 'n':
            case 'N':
                cout << endl;
                cout << "Thank you for playing the game of fifteen!" << endl;
                ans[0] = 'n';
                break;

            default:
                cin.clear();
                cout << "Incorrect responce please try again" << endl;
                ans[0] = WRONGVAL;
                break;
            }
        }
        else {
            cout << "Incorrect responce please try again" << endl;
            cin.clear();
            ans[0] = WRONGVAL;
        }

    }
    
    return ans[0];
}

