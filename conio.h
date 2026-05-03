#ifndef conio_h
#define conio_h

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

void textcolor(int color);
void textbackground(int color);
void clrscr();
void gotoxy(int x, int y);
void wherex();
void wherey();
void deline();
void insline();
void highvideo();
void lowvideo();
int getch();
int getche();
int kbhit();
void resetcolor();
int putch(int ch);
int cputs(const char *str);
int cprintf(const char *fmt, ...);

#endif /* conio_h */
