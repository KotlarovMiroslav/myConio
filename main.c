#include <stdio.h>
#define BLACK         0
#define BLUE          1
#define GREEN         2
#define CYAN          3
#define RED           4
#define MAGENTA       5
#define BROWN         6
#define LIGHTGRAY     7
#define DARKGRAY      8
#define LIGHTBLUE     9
#define LIGHTGREEN   10
#define LIGHTCYAN    11
#define LIGHTRED     12
#define LIGHTMAGENTA 13
#define YELLOW       14
#define WHITE        15

void textcolor(int color) {
    static const int ansi_fg[16] = {
        30, 34, 32, 36, 31, 35, 33, 37,
        90, 94, 92, 96, 91, 95, 93, 97
    };

    if (color < 0 || color > 15) {
        return;
    }

    printf("\033[%dm", ansi_fg[color]);
}

void textbackground(int color) {
    static const int ansi_bg[16] = {
        40, 44, 42, 46, 41, 45, 43, 47,
        100, 104, 102, 106, 101, 105, 103, 107
    };

    if (color < 0 || color > 15) {
        return;
    }

    printf("\033[%dm", ansi_bg[color]);
}

void clrscr(){
    printf("\033[2J\033[H");
}

void gotoxy(int x, int y){
    printf("\033[%d;%dH",y,x);
}

void wherex(){
    int x, y;
    printf("\033[6n");
    scanf("\033[%d;%dR", &y, &x);
    printf("Current X: %d\n", x);
}
void wherey(){
    int x, y;
    printf("\033[6n");
    scanf("\033[%d;%dR", &y, &x);
    printf("Current Y: %d\n", y);
}

void deline(){ // TEST
    printf("\033[M");
}
void insline(){ // TEST
    printf("\033[L");
}

void resetcolor() {printf("\033[0m");}
int main (){
    printf("\033[44;31m");
    printf("Hi!");
    printf("\033[0m\n");
    clrscr();
    gotoxy(20,10);
    textcolor(BLACK);
    textbackground(WHITE);
    printf("TestCase\n");
    
    return 0;
}
