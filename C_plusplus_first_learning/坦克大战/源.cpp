#include <iostream>
#include <conio.h>
#include <windows.h>

const int width = 20;
const int height = 10;
int tankX, tankY;
int bulletX, bulletY;
bool bulletActive;

void Setup() {
    tankX = width / 2;
    tankY = height - 1;
    bulletActive = false;
}

void Draw() {
    system("cls");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == tankY && j == tankX)
                std::cout << "T";
            else if (bulletActive && i == bulletY && j == bulletX)
                std::cout << "|";
            else
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void Input() {
    if (_kbhit()) {
        char key = _getch();
        if (key == 'a' && tankX > 0)
            tankX--;
        if (key == 'd' && tankX < width - 1)
            tankX++;
        if (key == ' ' && !bulletActive) {
            bulletX = tankX;
            bulletY = tankY - 1;
            bulletActive = true;
        }
    }
}

void Logic() {
    if (bulletActive) {
        bulletY--;
        if (bulletY < 0)
            bulletActive = false;
    }
}

int main() {
    Setup();
    while (true) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
    return 0;
}