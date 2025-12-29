#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

#define DELAY   200

using namespace std;

void hidecursor();
void hidecursor(){
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

class Robot{
private:
    //data momber
    char shape;
    int x;
    int y;
    int targetX;
    int targetY;
    int chargingX;
    int chargingY;
    int power;
public:
    //method
    void gotoxy(int x, int y){
        COORD  loc;
        HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
        loc.X = x;
        loc.Y = y;
        SetConsoleCursorPosition(hOuput,loc);
    }
    void TargetLocation(int a, int b){
        targetX = a;
        targetY = b;
    }
    void ChargingLocation(int a, int b){
        chargingX = a;
        chargingY = b;
    }
    void Start(int a, int b){
        x = a;
        y = b;
    }
    void MoveTo(){
    	if(targetX == x && targetY == y) return;
    	gotoxy(x,y);
    	cout << ' ';
    	if(targetX>x){
    		x++;
    		
		}
    	else if(targetX<x){
    		x--;
    		
		}
		if(targetY>y){
    		y++;
    		
		}
    	else if(targetY<y){
    		y--;
    		
		}
		gotoxy(x,y);
    	cout << shape;
    	_sleep(1000);
    	MoveTo();
	}
    void SetShape(char s){
        shape = s;
    }
    void start(){
        int tX,tY;
        cout<<"Power on......"<<endl;
        SetShape('R');

        x=0;
        y=0;
        
        cout<<"Set start location (x,y): ";
        cin>>tX>>tY;
        Start(tX,tY);
		  
        cout<<"Set target location (x,y): "; 
        cin>>tX>>tY;
        TargetLocation(tX,tY);

        cout<<"Set charging stand location (x,y): ";
        cin>>tX>>tY;
        ChargingLocation(tX,tY);

        system("cls");
        gotoxy(x,y);
        cout<<'R';
        gotoxy(targetX,targetY);
        cout<<'T';
        gotoxy(chargingX,chargingY);
        cout<<'C';
        
    }
};


int main(){
    hidecursor();

    Robot exercise;

    exercise.start();
    exercise.MoveTo();

    return 0;
}
