#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>

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
    if (x <= 0 || y <= 0) {
        return;
    }

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

void deline(){
    printf("\033[M");
}
void insline(){
    printf("\033[L");
}
void highvideo(){
    printf("\033[1m");
}

void lowvideo(){
    printf("\033[2m");
}

int getch() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int getche() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt.c_lflag &= ~ICANON;   
    newt.c_lflag |= ECHO;      
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch; 
}

int kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}


void resetcolor() {printf("\033[0m");}

int putch(int ch) {
    return putchar(ch);
}

int cputs(const char *str) {
    if (!str) {
        return EOF;
    }

    return fputs(str, stdout);
}

int cprintf(const char *fmt, ...) {
    va_list args; //variable argument list
    int result;

    if (!fmt) {
        return EOF;
    }

    va_start(args, fmt);
    result = vprintf(fmt, args);   // vprintf returns number of characters printed
    va_end(args);

    return result;
}
