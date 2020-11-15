#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;


bool gameOver;
const int width = 20; // ширина поля
const int height = 20; // высота поля
int x, y; // координаты оси передвижения змейки
int fruitX, fruitY; //фрукты на оси 
int score;// общий счет игры
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
//Создание функций для выполнения логики в игре

// Старт игры

void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2 - 1; //начальное положение змейки по оси Х    
    y = height / 2 - 1; // начальное положение змейки по оси У
    fruitX = rand() % width;// расположение фрукта на оси Х
    fruitY = rand() % height;
    score = 0;// начальный счет
}



//Карта
void Draw() {
    //верхняя граница карты
    system("cls"); //system("clear");
    for (int i = 0; i < width; i++)
        cout << "#";
    cout << endl;
    //боковые границы карты
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width;j++) {
            if (j == 0 || j == width - 1)
                cout << "#";
            if (i == y && j == x)
            {
                cout << "0";
                Sleep(33);
                
            }
            else if (i == fruitY && j == fruitX)
                {
                cout << "F";
                Sleep(33);
                }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        print = true;

                        cout << "o";
                        Sleep(100);
                    }
                }
                
                if(!print)
                cout << " ";
            }
        }
        cout << endl;
    }
    // нижняя граница карты
    for (int i = 0; i < width; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;

}




//Отслеживание нажатий
void Input() {

    if (_kbhit())
    {
        switch (_getch())
        {
        case'a':
            dir = LEFT;
            break;
        case'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;

        }
     }
}



//snake speed (Sleep(33);)
//Логика для игры
void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
}
    //if (x > width || x < 0 || y > height || y < 0)
      // gameOver = true;
    if (x >= width - 1)
        x = 0;
    else if (x < 0)
        x = width - 2;
    if (y >= height)
        y = 0;
    else if (y < 0)
        y = height - 1;
    for (int i = 0; i < nTail;i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    }
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
        
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
    }

    return 0;
}