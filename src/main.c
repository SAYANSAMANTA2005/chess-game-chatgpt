#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_SIZE 8

// Initialize the board with the starting positions
char board[BOARD_SIZE][BOARD_SIZE] = {
    {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
    {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
    {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
};

// Function to print the current state of the board
void printBoard() {
    printf("  a b c d e f g h\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", BOARD_SIZE - i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if a square is occupied by a white piece
int isWhitePiece(char piece) {
    return piece >= 'A' && piece <= 'Z';
}

// Function to check if a square is occupied by a black piece
int isBlackPiece(char piece) {
    return piece >= 'a' && piece <= 'z';
}

// Function to validate moves for White Pawn
int isValidWhitePawnMove(int x1, int y1, int x2, int y2) {
    char target = board[x2][y2];
    if (x2 == x1 - 1 && y2 == y1 && target == ' ') return 1; // Move forward
    if (x1 == 6 && x2 == x1 - 2 && y2 == y1 && target == ' ' && board[x1-1][y1] == ' ') return 1; // Double move
    if (x2 == x1 - 1 && abs(y2 - y1) == 1 && isBlackPiece(target)) return 1; // Capture
    return 0;
}

// Function to validate moves for White Knight
int isValidWhiteKnightMove(int x1, int y1, int x2, int y2) {
    char target = board[x2][y2];
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
        if (target == ' ' || isBlackPiece(target)) return 1;
    }
    return 0;
}

// Function to validate moves for White Rook
int isValidWhiteRookMove(int x1, int y1, int x2, int y2) {
    char target = board[x2][y2];
    if (x1 == x2) { // Horizontal move
        int step = (y2 > y1) ? 1 : -1;
        for (int y = y1 + step; y != y2; y += step) {
            if (board[x1][y] != ' ') return 0; // Path blocked
        }
        if (target == ' ' || isBlackPiece(target)) return 1;
    } else if (y1 == y2) { // Vertical move
        int step = (x2 > x1) ? 1 : -1;
        for (int x = x1 + step; x != x2; x += step) {
            if (board[x][y1] != ' ') return 0; // Path blocked
        }
        if (target == ' ' || isBlackPiece(target)) return 1;
    }
    return 0;
}

// Function to validate moves (currently only for pawns, knights, and rooks)
int isValidMove(int x1, int y1, int x2, int y2, int isWhiteTurn) {
    char piece = board[x1][y1];
    if (isWhiteTurn) {
        switch (piece) {
            case 'P': return isValidWhitePawnMove(x1, y1, x2, y2);
            case 'N': return isValidWhiteKnightMove(x1, y1, x2, y2);
            case 'R': return isValidWhiteRookMove(x1, y1, x2, y2);
        }
    } else {
        // Add validation for Black pieces here
    }
    return 0;
}

// Function to make a move
void makeMove(int x1, int y1, int x2, int y2) {
    board[x2][y2] = board[x1][y1];
    board[x1][y1] = ' ';
}

// Function to convert user input to board coordinates
void getInput(char *input, int *x1, int *y1, int *x2, int *y2) {
    *y1 = input[0] - 'a';
    *x1 = BOARD_SIZE - (input[1] - '0');
    *y2 = input[2] - 'a';
    *x2 = BOARD_SIZE - (input[3] - '0');
}

int main() {
    char input[5];
    int x1, y1, x2, y2;
    int isWhiteTurn = 1;

    while (1) {
        printBoard();
        printf("%s's move (e.g., e2e4): ", isWhiteTurn ? "White" : "Black");
        scanf("%s", input);
        getInput(input, &x1, &y1, &x2, &y2);

        if (isValidMove(x1, y1, x2, y2, isWhiteTurn)) {
            makeMove(x1, y1, x2, y2);
            isWhiteTurn = !isWhiteTurn; // Switch turn
        } else {
            printf("Invalid move! Try again.\n");
        }
    }

    return 0;
}