#include <stdio.h>
void clrscr(){
    printf("\033[2J\033[H");
}

void gotoxy(int x, int y){
    printf("\033[%d;%dH",y,x);
}


int main (){
    printf("\033[44;31m");
    printf("Hi!");
    printf("\033[0m\n");
    clrscr();
    gotoxy(20,10);
    printf("TestCase\n");
    return 0;
}
