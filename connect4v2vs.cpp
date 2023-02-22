#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <windows.h>
#include <stdlib.h>
using namespace std;
//TODO: no global ints

int arr[6][7] = { 0 }, x, win = 0, turn = 1; //usually 1-Red, 2-Yellow

void displayboard() {    //prints the board

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "|1234567|\n|-------|\n"; //show possibilities

    for (int ii = 0; ii < 6;ii++) {

        for (int iii = 0; iii < 7;iii++) {

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //setting colour white
            if (iii == 0) { cout << "|"; }

            if (arr[ii][iii] == 0) {            //colors for clarity on which's turn it is now
                if (turn == 0) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); } //dark gray (end screen)
                if (turn == 1) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); } //red (dark red)
                if (turn == 2) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); } //brown (dark yellow)
                cout << ".";
            }
            else if (arr[ii][iii] == 1) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //light red
                cout << "0";
            }
            else if (arr[ii][iii] == 2) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); //yellow
                cout << "0";
            }


            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); //so the code after wont be mistakenly coloured
            if (iii == 6) {
                if (ii*iii == 30) {
                    cout << "|\n|-------|\n|1234567|\n\n";      //show possibilities at the end for extra clarity
                }
                else cout << "|\n";
            }
        }
    }
}

void checkturn(int check) {      //check turn validity
    
    check--;
    while (arr[0][check] != 0 || check < 0 || check>6) {   //check if row is full; check if its 1-7; prints out full rows
        cout << "\n\nPlease choose from 1 to 7";
        for (int I = 0, exc = 0; I < 7; I++) {
            if (arr[0][I] != 0) {
                if (exc == 0) {    //first time row is full prints out "except"
                    cout << ", except "<< I + 1;
                }
                else {
                    cout << ", " << I + 1;
                }
                exc++;
            }
        }
        cout << "\n";
        cin >> check;
        check--;
    }
    x = check;
    x++;    //?

}

void setpiece(int X) {   //sets piece in place
    X--;
    for (int j = 5; j > -1; j--) {
        if (arr[j][X] == 0) { 
            arr[j][X] = turn; 
            break; 
        }
    }
    cout << "\n\n";
}

void checkwin() {        //checks for each way to win, could be optimized for speed
    
    for (int i = 0; i < 6;i++) {        //horizontal
        for (int ii = 0;ii < 4;ii++) {     
            if (arr[i][ii] == turn && arr[i][1 + ii] == turn && arr[i][2 + ii] == turn && arr[i][3 + ii] == turn) {
                win = turn;
            }
        }
    }

    for (int i = 0; i < 7;i++) {        //vertical
        for (int ii = 0;ii < 3;ii++) {
            if (arr[ii][i] == turn && arr[1 + ii][i] == turn && arr[2 + ii][i] == turn && arr[3 + ii][i] == turn) {
                win = turn;
            }
        }
    }

    for (int i = 0;i < 3;i++) {     //diagonally falling
        for (int ii = 0;ii < 4;ii++) {
            if (arr[i][ii] == turn && arr[i + 1][ii + 1] == turn && arr[i + 2][ii + 2] == turn && arr[i + 3][ii + 3] == turn) {
                win = turn;
            }
        }
    }

    for (int i = 3;i < 6;i++) {     //diagonally rising
        for (int ii = 0;ii < 4;ii++) {
            if (arr[i][ii] == turn && arr[i - 1][ii + 1] == turn && arr[i - 2][ii + 2] == turn && arr[i - 3][ii + 3] == turn) {
                win = turn;
            }
        }
    }
}

void checkdraw() {      //checks if all rows full (and no one won) = a draw
    int tmp = 0;
    for (int i = 0;i < 7;i++) {
        if (arr[0][i] != 0) {
            tmp++;
        }
    }
    if (tmp == 7) { win = 3; }
}

void trophy() {     //trophy in ascii
    cout << "  ___________\n '._==_==_=_.'\n .-\\:      /-.\n| (|:.     |) |\n '-|:.     |-'\n   \\::.    /\n    '::. .'\n      ) (\n    _.' '._\n   `\"\"\"\"\"\"\"`\n\n";
}

void draw() {       //text "draw" in ascii
    cout << "It's a\n     888\n     888\n     888\n .d88888888d888 8888b. 888  888  888\nd88\" 888888P\"      \"88b888  888  888\n888  888888    .d888888888  888  888\nY88b 888888    888  888Y88b 888 d88P\n \"Y88888888    \"Y888888 \"Y8888888P\"\n\n";
}


int main()
{
    while (win == 0) {

        turn = 1;
        displayboard();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "Red players turn\nWrite from 1 to 7 to place your piece:\n\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cin >> x;
        checkturn(x);
        setpiece(x);
        checkwin();
        checkdraw();

        if (win != 0) {break;}

        turn = 2;
        displayboard();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "Yellow players turn\nWrite from 1 to 7 to place your piece:\n\n";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cin >> x;
        checkturn(x);
        setpiece(x);
        checkwin();
        checkdraw();
    }

    turn = 0;
    displayboard();

    switch (win) {
    case 1:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout << "Red won!\n";
        trophy();
        break;
    case 2:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "Yellow won!\n";
        trophy();
        break;
    case 3:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
        draw();
        break;
    default:
        cout << "Error code 1\n\n";
        break;
    }

    return 0;
}
