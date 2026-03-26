#ifndef conio_h
#define conio_h

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