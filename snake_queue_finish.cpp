#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define DIRECTION 224
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define HEIGHT 10
#define WIDTH 35
#define SLEEP_TIME 150

using namespace std;

void HideCursor();
class set;
class SnakeBody;
class egg;
void gotoxy(int, int);

void HideCursor(){
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void gotoxy(int x, int y){
    COORD loc;
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    loc.X = x;
    loc.Y = y;
    SetConsoleCursorPosition(hOutput, loc);
}

class Object{
protected:
    static int maps[4];
    static egg* Egg;

public:
    virtual void be_eaten() = 0;
    static void setEgg(egg* e) {
        Egg = e;
    }
    static egg* getEgg() {
        return Egg;
    }
};



class set {
private:
    int i;

public:
    set() {
        for (i = 0; i < WIDTH; i++) {
            gotoxy(i, 0);
            cout << "*";
        }
        for (i = 0; i < HEIGHT; i++) {
            gotoxy(0, i);
            cout << "*";
        }
        for (i = 0; i < WIDTH; i++) {
            gotoxy(i, HEIGHT);
            cout << "*";
        }
        for (i = 0; i < HEIGHT; i++) {
            gotoxy(WIDTH, i);
            cout << "*";
        }
    }
};

class egg : public Object {
private:
    int locatex;
    int locatey;

public:
    egg() {
        srand(time(NULL));
        locatex = rand() % WIDTH + 1;
        locatey = rand() % HEIGHT + 1;

        while (locatex == 0 || locatex == WIDTH) {
            locatex = rand() % WIDTH + 1;
        }

        while (locatey == 0 || locatey == HEIGHT) {
            locatey = rand() % HEIGHT + 1;
        }

        maps[0] = locatex;
        maps[1] = locatey;
        gotoxy(locatex, locatey);
        cout << "E";
        Object::setEgg(this);
    }

    void be_eaten() {
        delete this; 
    }

    ~egg() {
        egg* newEgg = new egg();
        Object::setEgg(newEgg);
    }

    int egg_locate_x();
    int egg_locate_y();
};

int egg::egg_locate_x() {
    return locatex;
}

int egg::egg_locate_y() {
    return locatey;
}

class SnakeBody : public Object {
private:
    int x[100];
    int y[100];
    int Forward_x;
    int Forward_y;
    int direction;
    char shape;
    int length;

public:
    SnakeBody() {
        x[0] = 1;
        y[0] = 1;
        direction = RIGHT;
        ChangeShape('~');
        gotoxy(x[0], y[0]);
        cout << shape;
        length = 1;
    }

    int locate_x();
    int locate_y();
    void ChangeShape(char skin);
    void Move();
    void Forward();
    void be_eaten();
    void change();

    void bodyEaten();
};

int SnakeBody::locate_x() {
    return x[0];
}

int SnakeBody::locate_y() {
    return y[0];
}

void SnakeBody::ChangeShape(char skin) {
    shape = skin;
}

void SnakeBody::Move() {
    unsigned char key;

    if (kbhit()) {
        key = getch();

        switch (key) {
            case DIRECTION:
                switch (key = getch()) {
                    case UP:
                        direction = UP;
                        break;
                    case DOWN:
                        direction = DOWN;
                        break;
                    case LEFT:
                        direction = LEFT;
                        break;
                    case RIGHT:
                        direction = RIGHT;
                        break;
                }
        }
    }
    Forward();
    Sleep(SLEEP_TIME);
}

void SnakeBody::Forward() {
    Forward_x = x[0];
    Forward_y = y[0];

    switch (direction) {
        case UP:
            Forward_y--;
            break;
        case DOWN:
            Forward_y++;
            break;
        case LEFT:
            Forward_x--;
            break;
        case RIGHT:
            Forward_x++;
            break;
    }
    bodyEaten();
    if (Forward_x == 0 || Forward_x == WIDTH || Forward_y == 0 || Forward_y == HEIGHT) {
        cout << "Game Over!" << endl;
        exit(0);
    }

    if (Forward_x == maps[0] && Forward_y == maps[1]) {
        be_eaten();
    }
    else {
        gotoxy(x[length - 1], y[length - 1]);
        cout << ' ';
    }

    for (int i = length - 1; i > 0; i--) {
        x[i] = x[i - 1];
        y[i] = y[i - 1];
    }

    x[0] = Forward_x;
    y[0] = Forward_y;

    gotoxy(x[0], y[0]);
    cout << shape;
}

void SnakeBody::bodyEaten() {
    for (int i = 1; i < length; ++i) {
        if (x[i] == Forward_x && y[i] == Forward_y) {
            cout << "Game Over!" << endl;
            exit(0);
        }
    }
}

void SnakeBody::change() {
    srand(time(NULL));
    Forward_x = rand() % WIDTH + 1;
    Forward_y = rand() % HEIGHT + 1;
    while (Forward_x == 0 || Forward_x == WIDTH) {
        Forward_x = rand() % WIDTH + 1;
    }
    while (Forward_y == 0 || Forward_y == HEIGHT) {
        Forward_y = rand() % HEIGHT + 1;
    }
}

void SnakeBody::be_eaten() {
    if (length == 5) {
        cout << "You Win!" << endl;
        exit(0);
    }
    egg* Egg = Object::getEgg();
    Egg->be_eaten();
    length++;
}

int Object::maps[4] = {0};
egg* Object::Egg = NULL;

int main() {
    HideCursor();
    SnakeBody* snake = new SnakeBody;
    egg* initialEgg = new egg;
    set* Set = new set;

    while (1) {
        snake->Move();
    }
    return 0;
}

