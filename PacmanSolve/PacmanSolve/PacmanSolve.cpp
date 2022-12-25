#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <vector>
#include <random>
#include <ctime>
#include <iostream>
const int W = 19;
const int H = 21;
const int ts = 25;
using namespace sf;
using namespace std;
unsigned long steps = 0;
unsigned int sqore = 0;
String TileMap[H] = {
"AAAAAAAAAAAAAAAAAAA",
"A        A        A",
"A AA AAA A AAA AA A",
"A        A        A",
"A AA A AAAAA A AA A",
"A    A   A   A    A",
"AAAA AAA A AAA AAAA",
"BBBA A       A ABBB",
"AAAA A AA AA A AAAA",
"ABBB   A213A   BBBA",
"AAAA A AAAAA A AAAA",
"BBBA A       A ABBB",
"AAAA A AAAAA A AAAA",
"A        A        A",
"A AA AAA A AAA AA A",
"A  A     C     A  A",
"AA A A AAAAA A A AA",
"A    A   A   A    A",
"A AAAAAA A AAAAAA A",
"A                 A",
"AAAAAAAAAAAAAAAAAAA",
};

enum Direction
{
    right_Dir = 1,
    left_Dir = 2,
    up_Dir = 3, down_Dir= 4
};
// menuTexture1 - Новая игра
// menuTexture2 - Выход
void menu(RenderWindow& window) {
    Texture menuTexture1, menuTexture2, pacmanTexture;
    menuTexture1.loadFromFile("111.png");
    menuTexture2.loadFromFile("333.png");

    Sprite menu1(menuTexture1), menu2(menuTexture2);
    bool isMenu = 1;
    int menuNum = 0;
    menu1.setPosition(100, 200);
    menu2.setPosition(100, 300);


    //////////////////////////////МЕНЮ///////////////////
    while (isMenu)
    {
        menu1.setColor(Color::White);
        menu2.setColor(Color::White);
        menuNum = 0;
        window.clear(Color::Black);
        if (IntRect(100, 200, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
        if (IntRect(100, 300, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
            
            if (menuNum == 2) { window.close(); isMenu = false; }

        }
        window.draw(menu1);
        window.draw(menu2);

        window.display();
    }
    ////////////////////////////////////////////////////
}
int randInt(int b)
{
    return rand() % (b + 1);
}

class Enemy
{
public:
    int positionY;
    int positionX;
    Direction direction;
    char enemychar;

    char wasChar;

    Enemy(int x, int y, char c)
    {
        direction = right_Dir;
        positionY = y;
        positionX = x;
        enemychar = c;
        wasChar = 'B';
    }
    vector<Direction> mayDir;   
    void move()
    {
        mayDir.clear();
        if (direction == right_Dir || direction == left_Dir)
        {
            if (TileMap[positionY + 1][positionX] != 'A' && TileMap[positionY + 2][positionX] != '1' && TileMap[positionY + 2][positionX] != '2' && TileMap[positionY + 2][positionX] != '3')
                mayDir.push_back(down_Dir);
            if (TileMap[positionY - 1][positionX] != 'A' && TileMap[positionY - 2][positionX] != '1' && TileMap[positionY - 2][positionX] != '2' && TileMap[positionY - 2][positionX] != '3')
                mayDir.push_back(up_Dir);
            if (direction == right_Dir && TileMap[positionY][positionX + 1] != 'A' && TileMap[positionY][positionX + 2] != '1' && TileMap[positionY][positionX + 2] != '2' && TileMap[positionY][positionX + 2] != '3')
                mayDir.push_back(right_Dir);
            if (direction == left_Dir && TileMap[positionY][positionX - 1] != 'A' && TileMap[positionY][positionX - 2] != '1' && TileMap[positionY][positionX - 2] != '2' && TileMap[positionY][positionX - 2] != '3')
                mayDir.push_back(left_Dir);
            
        }
        
        if (direction == right_Dir && TileMap[positionY - 1][positionX] == 'A' && TileMap[positionY + 1][positionX] == 'A' && TileMap[positionY][positionX + 1] == 'A')
            mayDir.push_back(left_Dir);
        if (direction == left_Dir && TileMap[positionY - 1][positionX] == 'A' && TileMap[positionY + 1][positionX] == 'A' && TileMap[positionY][positionX - 1] == 'A')
            mayDir.push_back(right_Dir);



        if (direction == down_Dir || direction == up_Dir)
        {
            if (TileMap[positionY][positionX + 1] != 'A' && TileMap[positionY][positionX + 2] != '1' && TileMap[positionY][positionX + 2] != '2' && TileMap[positionY][positionX + 2] != '3')
                mayDir.push_back(right_Dir);
            if (TileMap[positionY][positionX - 1] != 'A' && TileMap[positionY][positionX - 2] != '1' && TileMap[positionY][positionX - 2] != '2' && TileMap[positionY][positionX - 2] != '3')
                mayDir.push_back(left_Dir);
            if (direction == up_Dir && TileMap[positionY - 1][positionX] != 'A' && TileMap[positionY - 2][positionX] != '1' && TileMap[positionY - 2][positionX] != '2' && TileMap[positionY - 2][positionX] != '3')
                mayDir.push_back(up_Dir);
            if (direction == down_Dir && TileMap[positionY + 1][positionX] != 'A' && TileMap[positionY + 2][positionX] != '1' && TileMap[positionY + 2][positionX] != '2' && TileMap[positionY + 2][positionX] != '3')
                mayDir.push_back(down_Dir);
        }


        if (mayDir.size() == 0)
        {
            if (direction = right_Dir)
                mayDir.push_back(left_Dir);
            if (direction = left_Dir)
                mayDir.push_back(right_Dir);
            if (direction = up_Dir)
                mayDir.push_back(down_Dir);
            if (direction = down_Dir)
                mayDir.push_back(up_Dir);
        }

        
        srand(time(0));
        direction = mayDir[randInt(mayDir.size() - 1)];

        if (wasChar == 'B' || wasChar == ' ')
            TileMap[positionY][positionX] = wasChar;

        switch (direction)
        {
        case right_Dir:
            if (TileMap[positionY][positionX + 1] != 'A') {
                positionX = positionX + 1;
                positionY = positionY;
            } break;

        case down_Dir:
            if (TileMap[positionY + 1][positionX] != 'A') {
                positionX = positionX;
                positionY = positionY + 1;
            } break;
        case left_Dir:
            if (TileMap[positionY][positionX - 1] != 'A') {
                positionX = positionX - 1;
                positionY = positionY;
            } break;
        case up_Dir:
            if (TileMap[positionY - 1][positionX] != 'A') {
                positionX = positionX;
                positionY = positionY - 1;
            }break;
        }

        if (TileMap[positionY][positionX] == ' ' || TileMap[positionY][positionX] == 'B')
            wasChar = TileMap[positionY][positionX];

    }
};

bool isLose(int posX, int posY, char enemy)
{
    return (TileMap[posY + 1][posX] == enemy || TileMap[posY][posX + 1] == enemy
        || TileMap[posY - 1][posX] == enemy || TileMap[posY][posX - 1] == enemy || TileMap[posY][posX] == enemy);
}

class Pacman
{
public:
    int positionY = 15;
    int positionX = 9;
    Direction direction = right_Dir;
    float frame = 0;
    int sqore = 0;
    void update()
    {
        frame += 1;
        if (frame > 4)
            frame -= 4;
    }

    void move()
    {
        if (direction == right_Dir)
        {
            if (TileMap[positionY][positionX + 1] != 'A') {
                TileMap[positionY][positionX] = 'B';
                positionX = positionX + 1;
                positionY = positionY;
                if (TileMap[positionY][positionX] == ' ') sqore++;
                TileMap[positionY][positionX] = 'C';
            }
        }
        if (direction == down_Dir)
        {
            if (TileMap[positionY+1][positionX] != 'A') {
                TileMap[positionY][positionX] = 'B';
                positionX = positionX;
                positionY = positionY + 1;
                if (TileMap[positionY][positionX] == ' ') sqore++;
                TileMap[positionY][positionX] = 'C';
            }
        }
        if (direction == left_Dir)
        {
            if (TileMap[positionY][positionX - 1] != 'A') {
                TileMap[positionY][positionX] = 'B';
                positionX = positionX - 1;
                positionY = positionY;
                if (TileMap[positionY][positionX] == ' ') sqore++;
                TileMap[positionY][positionX] = 'C';
            }
        }
        if (direction == up_Dir)
        {
            if (TileMap[positionY-1][positionX] != 'A') {
                TileMap[positionY][positionX] = 'B';
                positionX = positionX;
                positionY = positionY - 1;
                if (TileMap[positionY][positionX] == ' ') sqore++;
                TileMap[positionY][positionX] = 'C';
            }
        }



    }

};

int main()
{
    sf::RenderWindow window(sf::VideoMode(W*ts, (H+2)*ts), "Packman!");
    Font font;
    menu(window);
    

    font.loadFromFile("21037.ttf");
    Text text("", font, 30);
    // text.setColor(Color::White);
    text.setStyle(Text::Bold);

    int lifes = 3;

    Texture t;
    t.loadFromFile("title.png");
    Sprite plat(t);
    Pacman pacman;
    Enemy enemy1(8, 9, '1');
    Enemy enemy2(9, 9, '2');
    Enemy enemy3(10, 9, '3');
    Direction nextDir = right_Dir;
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (event.key.code == Keyboard::Right)
            nextDir = right_Dir;
        if (event.key.code == Keyboard::Left)
            nextDir = left_Dir;
        if (event.key.code == Keyboard::Up)
            nextDir = up_Dir;
        if (event.key.code == Keyboard::Down)
            nextDir = down_Dir;


        if (nextDir == right_Dir)
            if (TileMap[pacman.positionY][pacman.positionX + 1] != 'A')
                pacman.direction = right_Dir;
        if (nextDir == left_Dir)
            if (TileMap[pacman.positionY][pacman.positionX - 1] != 'A')
                pacman.direction = left_Dir;
        if (nextDir == up_Dir)
            if (TileMap[pacman.positionY-1][pacman.positionX] != 'A')
                pacman.direction = up_Dir;
        if (nextDir == down_Dir)
            if (TileMap[pacman.positionY+1][pacman.positionX] != 'A')
                pacman.direction = down_Dir;


        if (!isLose(pacman.positionX, pacman.positionY, '1') &&
            !isLose(pacman.positionX, pacman.positionY, '2') &&
            !isLose(pacman.positionX, pacman.positionY, '3'))
        {
            steps++;
            Sleep(125);
            pacman.move();
            enemy1.move();
            if (steps > 30)
                enemy2.move();
            if (steps > 70)
                enemy3.move();
            pacman.update();
        }
        else
        {
            if (lifes == 1) {
                MessageBox(NULL, L"         Lost =(", L"You lose!", MB_DEFBUTTON1);
                return 0;
            }
            else
            {
                MessageBox(NULL, L"      You lost 1 life!", L"Oh!", MB_DEFBUTTON1);
                lifes--;


                TileMap[pacman.positionY][pacman.positionX] = 'B';
                pacman.positionX = 9;
                pacman.positionY = 15;
                TileMap[15][9] = 'C';

                TileMap[enemy1.positionY][enemy1.positionX] = enemy1.wasChar;
                enemy1.positionX = 8;
                enemy1.positionY = 9;
                enemy1.wasChar = 'B';
                enemy1.direction = right_Dir;

                TileMap[enemy2.positionY][enemy2.positionX] = enemy2.wasChar;
                enemy2.positionX = 9;
                enemy2.positionY = 9;
                enemy2.wasChar = 'B';
                enemy2.direction = right_Dir;

                TileMap[enemy3.positionY][enemy3.positionX] = enemy3.wasChar;
                enemy3.positionX = 10;
                enemy3.positionY = 9;
                enemy3.wasChar = 'B';
                enemy3.direction = right_Dir;

                steps = 0;
            }
        }

        text.setString("Earned sqore: " + to_string(pacman.sqore) +" Lifes: " + to_string(lifes));
        text.setPosition(5, (H)*ts);
        TileMap[enemy1.positionY][enemy1.positionX] = '1';
        TileMap[enemy2.positionY][enemy2.positionX] = '2';
        TileMap[enemy3.positionY][enemy3.positionX] = '3';
        window.clear(Color::Black);
        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                
                
                if (TileMap[i][j] == 'A')
                    plat.setTextureRect(IntRect(0, 0, ts, ts));
                else if (TileMap[i][j] == 'C')
                    plat.setTextureRect(IntRect(ts * int(pacman.frame), int(pacman.direction) * ts, ts, ts));
                else if (TileMap[i][j] == ' ')
                    plat.setTextureRect(IntRect(ts, 0, ts, ts));
                else if (TileMap[i][j] == 'B')
                    continue;
                else if (TileMap[i][j] == '1')
                        plat.setTextureRect(IntRect(ts * 5, ts * int(enemy1.direction), ts, ts));
                else if (TileMap[i][j] == '2')
                        plat.setTextureRect(IntRect(ts * 5, ts * int(enemy2.direction), ts, ts));
                else if (TileMap[i][j] == '3')
                    plat.setTextureRect(IntRect(ts * 5, ts * int(enemy3.direction), ts, ts));
               


                if (pacman.sqore == 176)
                {
                    MessageBox(NULL, L"         Winning condition", L"You won!", MB_DEFBUTTON1);
                    return 0;
                }
                plat.setPosition(j * ts, i * ts);
                window.draw(plat);
                window.draw(text);
            }
        }

        window.display();
    }

    return 0;
}