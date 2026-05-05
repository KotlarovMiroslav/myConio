#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/select.h>
#include "conio.h"

static int read_with_timeout(unsigned char *ch);

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

static int cursor_position(int *x, int *y)
{
    struct termios oldt, newt;
    char response[32];
    unsigned char ch;
    int i = 0;

    if (tcgetattr(STDIN_FILENO, &oldt) != 0) {
        return 0;
    }

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    printf("\033[6n");
    fflush(stdout);

    while (i < (int)sizeof(response) - 1 && read_with_timeout(&ch)) {
        response[i++] = (char)ch;

        if (ch == 'R') {
            break;
        }
    }

    response[i] = '\0';
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return sscanf(response, "\033[%d;%dR", y, x) == 2;
}

int wherex(){
    int x, y;

    if (cursor_position(&x, &y)) {
        return x;
    }

    return -1;
}

int wherey(){
    int x, y;

    if (cursor_position(&x, &y)) {
        return y;
    }

    return -1;
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

static int read_with_timeout(unsigned char *ch)
{
    fd_set set;
    struct timeval timeout;

    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);

    timeout.tv_sec = 0;
    timeout.tv_usec = 50000;

    if (select(STDIN_FILENO + 1, &set, NULL, NULL, &timeout) <= 0) {
        return 0;
    }

    return read(STDIN_FILENO, ch, 1) == 1;
}

static int csi_key_from_final(unsigned char final, int number)
{
    switch (final) {
        case 'A':
            return KEY_UP;
        case 'B':
            return KEY_DOWN;
        case 'C':
            return KEY_RIGHT;
        case 'D':
            return KEY_LEFT;
        case 'H':
            return KEY_HOME;
        case 'F':
            return KEY_END;
        case '~':
            switch (number) {
                case 1:
                case 7:
                    return KEY_HOME;
                case 2:
                    return KEY_INSERT;
                case 3:
                    return KEY_DELETE;
                case 4:
                case 8:
                    return KEY_END;
                case 5:
                    return KEY_PAGEUP;
                case 6:
                    return KEY_PAGEDOWN;
                case 11:
                    return KEY_F1;
                case 12:
                    return KEY_F2;
                case 13:
                    return KEY_F3;
                case 14:
                    return KEY_F4;
                case 15:
                    return KEY_F5;
                case 17:
                    return KEY_F6;
                case 18:
                    return KEY_F7;
                case 19:
                    return KEY_F8;
                case 20:
                    return KEY_F9;
                case 21:
                    return KEY_F10;
                case 23:
                    return KEY_F11;
                case 24:
                    return KEY_F12;
                default:
                    return 27;
            }
        default:
            return 27;
    }
}

static int ss3_key(unsigned char ch)
{
    switch (ch) {
        case 'A':
            return KEY_UP;
        case 'B':
            return KEY_DOWN;
        case 'C':
            return KEY_RIGHT;
        case 'D':
            return KEY_LEFT;
        case 'H':
            return KEY_HOME;
        case 'F':
            return KEY_END;
        case 'P':
            return KEY_F1;
        case 'Q':
            return KEY_F2;
        case 'R':
            return KEY_F3;
        case 'S':
            return KEY_F4;
        default:
            return 27;
    }
}

static int old_linux_console_key(unsigned char ch)
{
    switch (ch) {
        case 'A':
            return KEY_F1;
        case 'B':
            return KEY_F2;
        case 'C':
            return KEY_F3;
        case 'D':
            return KEY_F4;
        case 'E':
            return KEY_F5;
        default:
            return 27;
    }
}

static int csi_key(void)
{
    unsigned char ch;
    int number = 0;

    if (!read_with_timeout(&ch)) {
        return 27;
    }

    if (ch == '[') {
        if (!read_with_timeout(&ch)) {
            return 27;
        }

        return old_linux_console_key(ch);
    }

    if (ch < '0' || ch > '9') {
        return csi_key_from_final(ch, 0);
    }

    while (ch >= '0' && ch <= '9') {
        number = number * 10 + (ch - '0');

        if (!read_with_timeout(&ch)) {
            return 27;
        }
    }

    if (ch == ';') {
        do {
            if (!read_with_timeout(&ch)) {
                return 27;
            }
        } while ((ch >= '0' && ch <= '9') || ch == ';');
    }

    return csi_key_from_final(ch, number);
}

static int read_key(void)
{
    unsigned char ch;
    unsigned char second;

    if (read(STDIN_FILENO, &ch, 1) != 1) {
        return EOF;
    }

    if (ch != 27) {
        return ch;
    }

    if (!read_with_timeout(&second)) {
        return 27;
    }

    if (second == '[') {
        return csi_key();
    }

    if (second == 'O') {
        if (!read_with_timeout(&ch)) {
            return 27;
        }

        return ss3_key(ch);
    }

    return 27;
}

int getch() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = read_key();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int getche() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = read_key();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    if (ch >= 0 && ch < 256) {
        putchar(ch);
        fflush(stdout);
    }

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
