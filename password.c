#include <stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>
#include<stdbool.h>
#include<string.h>
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
}
int main(){
    printf("Password: ");
    char c;
    char pw[20];
    int n=0;
    int x=10,y=0;
    while (1){
        c = getch();
        if (c== 13) break;
        if (c==-32) { getch();}
        else if (c==8) {
            if (n!=0)
            {
                pw[--n]='\0';
                x--;
                gotoxy(x,y);
                printf(" ");
                gotoxy(x,y);
            }
        }
        else{
            pw[n++]=c;
            pw[n]='\0';
            printf("*");
            x++;
        }
    }
    printf("Mat khau: %s\n",pw);
    return 0;
}
