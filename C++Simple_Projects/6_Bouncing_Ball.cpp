#include <iostream>
#include <windows.h>
#include <conio.h>  // for kbhit() and getch()
#include <cstdlib>  // for rand()
#include <ctime>    // for time()
using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;
const int PADDLE_SIZE = 6;

int ballX, ballY;
int dirX = 1, dirY = -1;  // moving diagonally
int paddleX;
int score = 0;
bool gameOver = false;

/////////////////////////////////////////////// Boom (falling object)////////////////////////////////////////////////
int boomX, boomY;

void resetBoom() {
    boomX = rand() % WIDTH; // random X
    boomY = 0;              // start at top
}



///////////////////////////////////////////// Draw the game state using ASCII characters ///////////////////////////
void draw(){
    system("cls");

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == ballX && y == ballY) {
                cout << "O"; // Ball
            }
            else if(x == boomX && y ==boomY){
                cout<<"*"; // Boom
            }
            else if (y == HEIGHT - 1 && x >= paddleX && x < paddleX + PADDLE_SIZE) {
                cout << "="; // Paddle
            }
            else {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << "Score: " << score << endl;
}

///////////////////////// Handle the input before updating the game state /////////////////////////////////////
void input() {
    if (_kbhit()) {
        char ch = _getch();
        if (ch == 'a' || ch == 'A') {
            paddleX -= 2;
            if (paddleX < 0) paddleX = 0;
        }
        else if (ch == 'd' || ch == 'D') {
            paddleX += 2;
            if (paddleX > WIDTH - PADDLE_SIZE) paddleX = WIDTH - PADDLE_SIZE;
        }
    }
}

/////////////////////////////////////// Update the game state (ball and paddle positions)///////////////////////
int boomSpeed = 20;   // lower = faster, higher = slower
int frameCount = 0;

void logic() {
    // Ball update
    ballX += dirX;
    ballY += dirY;

    // Bounce off walls
    if (ballX <= 0 || ballX >= WIDTH - 1) dirX *= -1;
    if (ballY <= 0) dirY *= -1;

    // Bounce on paddle
    if (ballY == HEIGHT - 2 && ballX >= paddleX && ballX < paddleX + PADDLE_SIZE) {
        dirY *= -1;
        score++;
    }

    // Miss paddle -> Game Over
    if (ballY >= HEIGHT - 1) {
        gameOver = true;
    }

    // Boom update (slower)
    frameCount++;
    if (frameCount >= boomSpeed) {
        boomY++;
        frameCount = 0;
    }

    // If boom crosses bottom line
    if (boomY >= HEIGHT) {
        score += 5;
        resetBoom();
    }
}



///////////////////////////////// Main function ////////////////////////////////////////////////////////////////
int main() {
    srand(time(0)); // seed random

    // Initial positions
    ballX = WIDTH / 2;
    ballY = HEIGHT / 2;
    paddleX = WIDTH / 2 - PADDLE_SIZE / 2;
    resetBoom();

    while (!gameOver) {
        draw();
        input();
        logic();
        resetBoom();
        Sleep(60); // control speed
    }

    system("cls");
    cout << "GAME OVER!" << endl;
    cout << "Final Score: " << score << endl;
    return 0;
}
