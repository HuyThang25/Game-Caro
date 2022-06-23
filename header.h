#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>
#include <pthread.h>
#define MAX 25
#define XDAU 9
#define YDAU 4
#define true 1
#define false 0
typedef struct node{
    char data[30];
    struct node* next;
} node;
int endGame,thoat,quit,stop,start,pt;
int stepX=0, stepO=0, win1=0, win2=0,d;
char player1[30], player2[30],tenFileNhap[30],tenFileLuu[30],p1='X',p2='O';
node* first;
int top=0,ok=0;
void xoaDanhSach(node* first)
{
    while (first!=NULL){
        node* pNode=first;
        first=first->next;
        free(pNode);
    }
    top=0;
}
node* taoNode(char tmp[])
{
    node* pNode= (node*)malloc(sizeof(node));
    strcpy(pNode->data,tmp);
    pNode->next=NULL;
    return pNode;
}
void xoaNodeCuoi()
{
    node* i;
    for (i=first; i->next->next!=NULL; i=i->next);
    node*pNode=i->next;
    free(pNode);
    i->next=NULL;
    top--;
}
node* themNodeVaoDau(char tmp[],node* first)
{
    if (first==NULL) first=taoNode(tmp);
    else
    {
        if (top==30)
        {
            xoaNodeCuoi();
        }
        node* pNode=first;
        first=taoNode(tmp);
        first->next=pNode;
    }
    return first;
}
void  layDanhSach()
{
    first==NULL;
    FILE* f= fopen("listFile.c","r");
    if (f!=NULL)
    {
        char tmp[30];
        while (!feof(f))
        {
            if(fscanf(f,"%s",tmp)>0)
            {
                first=themNodeVaoDau(tmp,first);
                top++;
            }

        }
    }
    fclose(f);
}
char chuHoa(char c)
{
    if (c>='a' && c<='z') return c-32;
    else return c;
}
void keDong()
{
    printf("\t");
    for (int i=0; i<MAX*4+1; i++)
    {
        if (i%4==0) printf("+");
        else printf("-");
    }
    printf("\n");
}
void veMotO(char c)
{
    if (c!='X' && c!='O') c=' ';
    printf("| %c ",c);
}
void keBang(char a[][MAX])
{
    printf("\n\n\n");
    for (int i=0; i<MAX; i++){
        keDong();
        printf("\t");
        for (int j=0; j<MAX; j++){
            veMotO(a[j][i]);
        }
        printf("|\n");
    }
    keDong();
}
void set_color ( int code )
{
    HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute( color , code );
}
void gotoxy(int x, int y)
{
    static HANDLE h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h,c);
}
char chuyenDoiXO(int n)
{
    if (n==0) return 'X';
    else return 'O';
}
int checkWinner(char a[][MAX], int i, int j)
{
    int d = 0, k = i, h;
    // kiểm tra hàng
    while (a[k][j] == a[i][j]) {
        d++;
        k++;
    }
    k = i - 1;
    while (a[k][j] == a[i][j]) {
        d++;
        k--;
    }
    if (d > 4)
    {
        if (a[i][j]=='X') set_color(6);
            else set_color(4);
        for (int l=1; l<=5; l++)
        {
           gotoxy((k+l)*4+XDAU,j*2+YDAU);
           printf(" %c ",a[k+l][j]);
        }
        set_color(7);
        return 1;
    }
    d = 0; h = j;
    // kiểm tra cột
    while(a[i][h] == a[i][j]) {
        d++;
        h++;
    }
    h = j - 1;
    while(a[i][h] == a[i][j]) {
        d++;
        h--;
    }
    if (d > 4)
    {
        if (a[i][j]=='X') set_color(6);
            else set_color(4);
        for (int l=1; l<=5; l++)
        {
           gotoxy(i*4+XDAU,(h+l)*2+YDAU);
           printf(" %c ",a[i][h+l]);
        }
        set_color(7);
        return 1;
    }
    // kiểm tra đường chéo 1
    h = i; k = j; d = 0;
    while (a[i][j] == a[h][k]) {
        d++;
        h++;
        k++;
    }
    h = i - 1; k = j - 1;
    while (a[i][j] == a[h][k]) {
        d++;
        h--;
        k--;
    }
    if (d > 4)
    {
        if (a[i][j]=='X') set_color(6);
            else set_color(4);
        for (int l=1; l<=5; l++)
        {
           gotoxy((h+l)*4+XDAU,(k+l)*2+YDAU);
           printf(" %c ",a[h+l][k+l]);
        }
        set_color(7);
        return 1;
    }
    // kiểm tra đường chéo 2
    h = i; k = j; d = 0;
    while (a[i][j] == a[h][k]) {
        d++;
        h++;
        k--;
    }
    h = i - 1; k = j + 1;
    while (a[i][j] == a[h][k]) {
        d++;
        h--;
        k++;
    }
    if (d > 4)
    {
        if (a[i][j]==p1) set_color(6);
            else set_color(4);
        for (int l=1; l<=5; l++)
        {
           gotoxy((h+l)*4+XDAU,(k-l)*2+YDAU);
           printf(" %c ",a[h+l][k-l]);
        }
        set_color(7);
        return 1;
    }
    // nếu không đương chéo nào thỏa mãn thì trả về 0.
    return 0;
}
void resetBang(char a[][MAX])
{
    for (int i=0; i<MAX ; i++)
    {
        for (int j=0; j<MAX; j++)
        {
            a[i][j]=0;
        }
    }
    stepX=0; stepO=0;d=0;
}
void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;

    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;

    SetConsoleCursorInfo(handle, &ConCurInf);
}
void sua(char a[][MAX],int x,int y)
{
    gotoxy(x,y);
    set_color(7);
    if(a[(x-XDAU)/4][(y-YDAU)/2]==0)
        printf("   ",a[(x-XDAU)/4][(y-YDAU)/2]);
    else
        printf(" %c ",a[(x-XDAU)/4][(y-YDAU)/2]);

}
void ghi(char a[][MAX],int x,int y,int mau)
{
    gotoxy(x,y);
    set_color(mau);
    if(a[(x-XDAU)/4][(y-YDAU)/2]==0)
        printf("   ",a[(x-XDAU)/4][(y-YDAU)/2]);
    else
        printf(" %c ",a[(x-XDAU)/4][(y-YDAU)/2]);
    set_color(7);
}
void hienThiLuu(char a[][MAX])
{
    system("cls");
    SetScreenBufferSize(200,200);
    gotoxy(100,10);
    printf("Bạn có muốn lưu trân đấu lại không?");
    gotoxy(100,12);
    printf("Có");
    gotoxy(120,12);
    printf("Không");
    int x=100;
    gotoxy(x,12);
    set_color(2);
    printf("Có");
    set_color(7);
    while (true )
    {
        ok=0;
        char bam;
        fflush(stdin);
        bam=getch();
        if (bam==-32)
        {
            bam=getch();
        }
        else ok=1;
        switch (chuHoa(bam))
        {
        case 75:
            {
                if (ok==0)
                {
                    x-=20;
                    if (x==100)
                    {
                        gotoxy(120,12);
                        printf("Không");
                        gotoxy(100,12);
                        set_color(2);
                        printf("Có");
                        set_color(7);
                    }
                    else x+=20;
                }
                break;
            }
        case 77:
            {
                if (ok==0)
                {
                    x+=20;
                    if (x==120)
                    {
                        gotoxy(100,12);
                        printf("Có");
                        gotoxy(120,12);
                        set_color(2);
                        printf("Không");
                        set_color(7);
                    }
                    else x-=20;
                }
                break;
            }
        case 13:
            {
                if (ok)
                {
                    if (x==120) return 0;
                    else if (x==100)
                    {
                        while (true)
                        {
                            system("cls");
                            SetScreenBufferSize(200,200);
                            gotoxy(100,10);
                            printf("Nhập tên trận đấu: ");
                            gotoxy(120,10);
                            printf("                              ");
                            gotoxy(120,10);
                            ShowCur(1);
                            fflush(stdin);
                            tenFileLuu[0]='\n';
                            gets(tenFileLuu);
                            ShowCur(0);
                            if (strlen(tenFileLuu)<=0)
                            {
                                gotoxy(100,13);
                                printf("Vui lòng nhập tên trận đấu");
                                sleep(1);
                                gotoxy(100,48);
                                printf("                           ");
                            }
                            else if(tonTaiTenFile(tenFileLuu))
                            {
                                gotoxy(100,13);
                                printf("Trận đấy đã tồn tại. Vui lòng nhập tên khác");
                                sleep(1);
                                gotoxy(100,48);
                                printf("                                             ");
                            }
                            else
                            {
                                first=themNodeVaoDau(tenFileLuu,first);
                                top++;
                                taiSoLieuLenFile(a,tenFileLuu);
                                return 0;
                            }
                        }
                    }
                }
                break;
            }
        }
    }
}
void taiSoLieuLenFile(char a[][MAX], char tenFile[])
{
    char name[40];
    strcpy(name,tenFile);
    strcat(name,".c");
    FILE* f=fopen(name,"w");
    for (int i=0; i<MAX; i++)
    {
        for (int j=0; j<MAX; j++)
        {
            fprintf(f,"%d ",a[i][j]);
        }
    }
    fprintf(f,"%d %d %d %d %d %d %c %c",win1, win2, stepX, stepO, d,  pt, p1, p2);
    fprintf(f,player1);
    fprintf(f,player2);
    fclose(f);
}
void laySoLieu(char a[][MAX], char tenFile[])
{
    char name[40];
    strcpy(name,tenFile);
    strcat(name,".c");
    FILE* f=fopen(name,"r");
    for (int i=0; i<MAX; i++)
    {
        for (int j=0; j<MAX; j++)
        {
            fscanf(f,"%d ",&a[i][j]);
        }
    }
    fscanf(f,"%d %d %d %d %d %d %c %c",&win1, &win2, &stepX, &stepO, &d,  &pt, &p1, &p2);
    fgets(player1,30,f);
    fgets(player2,30,f);
    fclose(f);
}
void diChuyenVaDanh2Nguoi(char a[][MAX])
{
    ShowCur(0);
    int xX,yX,xO,yO;
    xX=XDAU+11*4;yX=YDAU+12*2;
    ghi(a,xX,yX,97);
    xO=xX+8;yO=yX;
    ghi(a,xO,yO,64);
    gotoxy(160,20);
    if (chuyenDoiXO(d%2)==p1) set_color(6);
    else set_color(4);
    printf("Lượt của %c",chuyenDoiXO(d%2));
    set_color(7);
    while (true)
    {
        ok=0;
        char bam;
        fflush(stdin);
        bam=getch();
        if (bam ==27)
        {
            hienThiLuu(a);
            stop=1;
            break;
        }
        else if(bam==-32)
        {
            ok=1;
            bam=getch();
        }
        switch (chuHoa(bam))
        {
        case 'W':
            {
                if(ok==0)
                {
                    yX-=2;
                    if (yX>=YDAU)
                    {
                        if (xX==xO && yX+2==yO)
                            ghi(a,xO,yO,64);
                        else
                            sua(a,xX,yX+2);
                        ghi(a,xX,yX,97);
                    }
                    else yX+=2;
                }
                break;
            }
        case 'A':
            {
                if(ok==0)
                {
                    xX-=4;
                    if (xX>=XDAU)
                    {
                        if (xX+4==xO && yX==yO)
                            ghi(a,xO,yO,64);
                        else
                            sua(a,xX+4,yX);
                        ghi(a,xX,yX,97);
                    }
                    else xX+=4;
                }
                break;
            }
        case 'S':
            {
                if(ok==0)
                {
                    yX+=2;
                    if (yX<MAX*2+YDAU)
                    {
                        if (xX==xO && yX-2==yO)
                            ghi(a,xO,yO,64);
                        else
                            sua(a,xX,yX-2);
                        ghi(a,xX,yX,97);
                    }
                    else yX-=2;
                }
                break;
            }
        case 'D':
            {
                if (ok==0)
                {
                    xX+=4;
                if (xX<MAX*4+XDAU)
                {
                    if (xX-4==xO && yX==yO)
                        ghi(a,xO,yO,64);
                    else
                        sua(a,xX-4,yX);
                    ghi(a,xX,yX,97);
                }
                else xX-=4;
                }
                break;
            }
        case 72:
            {
                if(ok)
                {
                    yO-=2;
                    if (yO>=YDAU)
                    {
                        if (xX==xO && yX==yO+2)
                            ghi(a,xX,yX,97);
                        else
                            sua(a,xO,yO+2);
                        ghi(a,xO,yO,64);
                    }
                    else yO+=2;
                }
                break;
            }
        case 75:
            {
                if(ok)
                {
                    xO-=4;
                    if (xO>=XDAU)
                    {
                        if (xX==xO+4 && yX==yO)
                            ghi(a,xX,yX,97);
                        else
                            sua(a,xO+4,yO);
                        ghi(a,xO,yO,64);
                    }
                    else xO+=4;
                }
                break;
            }
        case 80:
            {
                if(ok)
                {
                    yO+=2;
                    if (yO<MAX*2)
                    {
                        if (xX==xO && yX==yO-2)
                            ghi(a,xX,yX,97);
                        else
                            sua(a,xO,yO-2);
                        ghi(a,xO,yO,64);
                    }
                    else yO-=2;
                }
                break;
            }
        case 77:
            {
                if(ok)
                {
                    xO+=4;
                    if (xO<MAX*4+XDAU)
                    {
                        if (xX==xO-4 && yX==yO)
                            ghi(a,xX,yX,97);
                        else
                            sua(a,xO-4,yO);
                        ghi(a,xO,yO,64);
                    }
                    else xO-=4;
                }
                break;
            }
        case ' ':
            {
                if(ok==0)
                {
                    if (chuyenDoiXO(d%2)==p1)
                    {
                        int tung =(xX-XDAU)/4;
                        int hoanh=(yX-YDAU)/2;
                        if (a[tung][hoanh]!=0) break;
                        else
                        {
                            a[tung][hoanh]=p1;
                            ghi(a,xX,yX,97);
                            endGame=0;
                            stepX++;
                            gotoxy(163,9);
                            printf("%d",stepX);
                            gotoxy(160,20);
                            set_color(4);
                            printf("Lượt của %c",p2);
                            set_color(7);
                            d++;
                            if (checkWinner(a,tung,hoanh))
                            {
                                gotoxy(155,20);
                                if(a[tung][hoanh]==p1)
                                {
                                    printf("Người chơi %s đã thắng.",player1);
                                    win1++;
                                }
                                else
                                {
                                    printf("Người chơi %s đã thắng.",player2);
                                    win2++;
                                }
                                return ;
                            }
                            if(d==(MAX*MAX))
                            {
                                gotoxy(155,20);
                                printf("Trận đấu hoà");
                                return ;
                            }
                        }
                    }
                }
                break;
            }
        case 13:
            {
                if(ok==0)
                {
                    if (chuyenDoiXO(d%2)==p2)
                    {
                        int tung =(xO-XDAU)/4;
                        int hoanh=(yO-YDAU)/2;
                        if (a[tung][hoanh]!=0) break;
                        else
                        {
                            a[tung][hoanh]=p2;
                            ghi(a,xO,yO,64);
                            endGame=0;
                            stepO++;
                            gotoxy(163,34);
                            printf("%d",stepO);
                            gotoxy(160,20);
                            set_color(6);
                            printf("Lượt của %c",p1);
                            set_color(7);
                            d++;
                            if (checkWinner(a,tung,hoanh))
                            {

                                gotoxy(155,20);
                                if(a[tung][hoanh]==p1)
                                {
                                    printf("Người chơi %s đã thắng.",player1);
                                    win1++;
                                }
                                else
                                {
                                    printf("Người chơi %s đã thắng.",player2);
                                    win2++;
                                }
                                return ;
                            }
                            if(d==(MAX*MAX))
                            {
                                gotoxy(155,20);
                                printf("Trận đấu hoà");
                                return ;
                            }
                        }
                    }
                }
                break;
            }
        default: break;
        }
        if (xX==xO && yX==yO)
            ghi(a,xX,yX,192);
    }
}
void diChuyenVaDanh1Nguoi(char a[][MAX])
{
    ShowCur(0);
    int x,y;
    x=XDAU+12*4;y=YDAU+12*2;
    gotoxy(x,y);
    ghi(a,x,y,192);
    gotoxy(160,20);
    if (chuyenDoiXO(d%2)=='X') set_color(6);
    else set_color(4);
    printf("Lượt của %c",chuyenDoiXO(d%2));
    set_color(7);
    while (true)
    {
        ok=0;
        char bam;
        fflush(stdin);
        bam=getch();

        if (bam==27)
        {
            hienThiLuu(a);
            stop=1;
            break;
        }
        else if (bam==-32)
        {
            bam=getch();
        }
        else ok=1;
        switch (chuHoa(bam))
        {
        case 72:
            {
                if (ok==0)
                {
                    y-=2;
                    if (y>=YDAU)
                    {
                        sua(a,x,y+2);
                        ghi(a,x,y,192);
                    }
                    else y+=2;
                }
                break;
            }
        case 75:
            {
                if(ok==0)
                {
                    x-=4;
                    if (x>=XDAU)
                    {
                        sua(a,x+4,y);
                        ghi(a,x,y,192);
                    }
                    else x+=4;
                }
                break;
            }
        case 80:
            {
                if(ok==0)
                {
                    y+=2;
                    if (y<MAX*2+YDAU)
                    {

                        sua(a,x,y-2);
                        ghi(a,x,y,192);
                    }
                    else y-=2;
                }
                break;
            }
        case 77:
            {
                if(ok==0)
                {
                    x+=4;
                    if (x<MAX*4+XDAU)
                    {
                        sua(a,x-4,y);
                        ghi(a,x,y,192);
                    }
                    else x-=4;
                }
                break;
            }
        case 13:
            {
              if(ok)
              {
                  int tung=(x-XDAU)/4,hoanh=(y-YDAU)/2;
                  if (a[tung][hoanh]=='X' || a[tung][hoanh]=='O')
                        break;
                  else
                  {
                      a[tung][hoanh]=chuyenDoiXO(d%2);
                      ghi(a,x,y,192);
                      if (a[tung][hoanh]=='X')
                      {
                          stepX++;
                          gotoxy(163,9);
                          printf("%d",stepX);
                          gotoxy(160,20);
                          set_color(4);
                          printf("Lượt của O");
                          set_color(7);
                          gotoxy(x,y);
                          d++;
                      }
                      else
                      {
                          stepO++;
                          gotoxy(163,34);
                          printf("%d",stepO);
                          gotoxy(160,20);
                          set_color(6);
                          printf("Lượt của X");
                          set_color(7);
                          gotoxy(x,y);
                          d++;
                      }
                      endGame=0;
                      if (checkWinner(a,tung,hoanh)) {
                            char winner[30];
                            if(a[tung][hoanh]=='X') { win1++; strcpy(winner,player1);}
                            else { win2++; strcpy(winner,player2);}
                            gotoxy(155,20);
                            printf("Người chơi %s đã thắng.",winner);
                            return ;
                      }
                      if(d==(MAX*MAX))
                      {
                            gotoxy(155,20);
                            printf("Trận đấu hoà");
                            endGame=1;
                            return ;
                      }
                  }
              }
              break;
            }
        default: break;
        }
    }
}

int tonTaiTenFile(char tenFile[])
{
    for (node* i=first; i!=NULL; i=i->next)
    {
        if (strcmp(i->data,tenFile)==0) return 1;
    }
    return 0;
}
void suaLai(int x, int y)
{
    gotoxy(x,y);
    if (y==17) printf("Chơi tiếp");
    if (y==18) printf("Ván mới");
    if (y==19) printf("Hướng dẫn");
    if (y==20) printf("Thoát Game");
}
void ghiLai(int x, int y)
{
    set_color(2);
    gotoxy(x,y);
    if (y==17) printf("Chơi tiếp");
    if (y==18) printf("Ván mới");
    if (y==19) printf("Hướng dẫn");
    if (y==20) printf("Thoát Game");
    set_color(7);
}
void diChuyenMenu(char a[][MAX])
{
    ShowCur(0);
    stop=0;
    int x,y;
    x=112   ;y=17;
    gotoxy(x,y);
    ghiLai(x,y);
    while (true)
    {
        ok=0;
        ShowCur(0);
        char bam;
        fflush(stdin);
        bam=getch();
        if (bam==-32)
        {
            bam=getch();
        }
        else ok=1;
        switch (chuHoa(bam))
        {
        case 72:
            {
                if (ok==0)
                {
                    y--;
                    if (y>=17 && y<=20)
                    {
                        ShowCur(0);
                        suaLai(x,y+1);
                        ghiLai(x,y);
                    }
                    else y++;
                }
                break;
            }
        case 80:
            {
                if(ok==0)
                {
                    y++;
                    if (y>=17 && y<=20)
                    {
                        ShowCur(0);
                        suaLai(x,y-1);
                        ghiLai(x,y);
                    }
                    else y--;
                }
                break;
            }
        case 13:
            {
              if (ok)
              {
                  if (y==18)
                  {     //Ván mới
                        endGame=0;
                        system("cls");
                        SetScreenBufferSize(200,200);
                        p1='X'; p2='O';
                        player1[1]='\n';
                        player2[1]='\n';
                        hienThiNhapTen();
                        if (nhapTen()==0) return 0;
                        ShowCur(0);
                        hienThiPhuongThucDanh();
                        pt=chonPhuongThuc();
                        win1=0; win2=0;
                        while (true)
                        {
                            system("cls");
                            SetScreenBufferSize(200,200);
                            resetBang(a);
                            keBang(a);
                            hienThiThongTinNguoiChoi(player1,p1,stepX,win1,150,5);
                            hienThiThongTinNguoiChoi(player2,p2,stepO,win2,150,30);
                            gotoxy(160,27);
                            set_color(1);
                            printf("Bấm ESC để về menu");
                            if (pt==1) diChuyenVaDanh1Nguoi(a);
                            else diChuyenVaDanh2Nguoi(a);
                            if (stop) return 0;
                            if (choiLai()==0)
                            {
                                endGame=1;
                                hienThiLuu(a);
                            }
                            else
                            {
                                if (doiLuot())
                                {
                                    char c=p1;
                                    p1=p2;
                                    p2=c;
                                }
                            }
                            if (endGame) return 0;
                        }
                        break;
                  }
                  if (y==17)
                  {     //choi tiep
                        tenFileNhap[0]='\n';
                        if(hienThiDanhSachFile()==0) return 0;
                        else
                        {
                            laySoLieu(a,tenFileNhap);
                            system("cls");
                            SetScreenBufferSize(200,200);
                            keBang(a);
                            hienThiThongTinNguoiChoi(player1,p1,stepX,win1,150,5);
                            hienThiThongTinNguoiChoi(player2,p2,stepO,win2,150,30);
                            gotoxy(160,27);
                            set_color(1);
                            printf("Bấm ESC để về menu");
                            if (pt==1) diChuyenVaDanh1Nguoi(a);
                            else diChuyenVaDanh2Nguoi(a);
                            if (stop) return 0;
                            else
                            {
                                if (doiLuot())
                                {
                                    char c=p1;
                                    p1=p2;
                                    p2=c;
                                }
                            }
                            if (endGame) return 0;
                            while (true)
                            {
                                system("cls");
                                SetScreenBufferSize(200,200);
                                resetBang(a);
                                keBang(a);
                                hienThiThongTinNguoiChoi(player1,p1,stepX,win1,150,5);
                                hienThiThongTinNguoiChoi(player2,p2,stepO,win2,150,30);
                                gotoxy(160,27);
                                set_color(1);
                                printf("Bấm ESC để về menu");
                                if (pt==1) diChuyenVaDanh1Nguoi(a);
                                else diChuyenVaDanh2Nguoi(a);
                                if (stop) return 0;
                                if (choiLai()==0)
                                {
                                    endGame=1;
                                    hienThiLuu(a);
                                }
                                else
                                {
                                    if (doiLuot())
                                    {
                                        char c=p1;
                                        p1=p2;
                                        p2=c;
                                    }
                                }
                            }
                            if (endGame) return 0;
                            break;
                        }
                  }
                  if (y==19)
                  {
                        hienThiHuongDan();
                        return 0;
                  }
                  if (y==20)
                  {     //thoat Game
                        quit=1;
                        return 0;
                  }
                  break;

                }
            }
        default: break;
        }
    }
}

void hienThiThongTinNguoiChoi(char hoTen(), char player, int step, int win, int x, int y)
{
    gotoxy(x,y);
    printf("+");
    for (int i=0; i<40; i++)
        printf("-");
    printf("+");
    gotoxy(x,y+1);
    for (int i=1; i<=6; i++)
        {
            printf("|%41c|");
            gotoxy(x,y+i+1);
        }
    printf("+");
    for (int i=0; i<40; i++)
        printf("-");
    printf("+");
    gotoxy(x+1,y+3);
    printf("\tNgười chơi %c: %s",player,hoTen);
    gotoxy(x+1,y+4);
    printf("\tSố quân %c: %d",player,step);
    gotoxy(x+1,y+5);
    printf("\tSố trận đã thắng: %d", win);
}
void hienThiNhapTen()
{
    system("cls");
    SetScreenBufferSize(200,200);
    gotoxy(120-15,5);
    printf("    <<  Ván mới  >>   ");
    gotoxy(120-15,10);
    printf("Nhập tên người chơi ");
    gotoxy(115-15,12);
    printf("Tên người chơi X: ");
    gotoxy(115-15,13);
    printf("Tên người chơi O: ");
    gotoxy(110-15,14);
    printf("Quay lại");
    gotoxy(140-15,14);
    printf("Bắt đầu chơi");
}
void ghiNhapTen(int x,int y, int mau)
{
    //ShowCur(0);
    set_color(mau);
    if (y==14)
    {
        if (x==110-15)
        {
            printf("Quay lại");
        }
        if (x==140-15)
        {
            printf("Bắt đầu chơi");
        }
    }
    if (y==12)
    {
        printf("Tên người chơi X:");
    }
    if (y==13)
    {
        printf("Tên người chơi O:");
    }
    set_color(7);
}
int nhapTen()
{
    ShowCur(0);
    int x=115-15, y=12;
    gotoxy(x,y);
    ghiNhapTen(x,y,2);
    x=110-15; y=12;
    while (true)
    {
        ok=0;
        char bam;
        fflush(stdin);
        bam=getch();
        if (bam==-32) bam=getch();
        else ok=1;
        switch(chuHoa(bam))
        {
        case 72:
            {
                if (ok==0)
                {
                    y-=1;
                    if (y>=12)
                    {

                        if (y==12)
                        {
                            gotoxy(115-15,y+1);
                            ghiNhapTen(115-15,y+1,7);
                            gotoxy(115-15,y);
                            ghiNhapTen(115-15,y,2);

                        }
                        if (y==13)
                        {
                            gotoxy(x,y+1);
                            ghiNhapTen(x,y+1,7);
                            gotoxy(115-15,y);
                            ghiNhapTen(115-15,y,2);
                        }
                    }
                    else y+=1;
                }
                break;
            }

        case 80:
            {
                if (ok==0)
                {
                    y+=1;
                    if (y<=14)
                    {
                        if (y==14)
                        {
                            ShowCur(0);
                            gotoxy(115-15,y-1);
                            ghiNhapTen(115-15,y-1,7);
                            gotoxy(110-15,y);
                            ghiNhapTen(110-15,y,2);
                            x=110-15;
                        }
                        if (y==13)
                        {
                            gotoxy(115-15,y-1);
                            ghiNhapTen(115-15,y-1,7);
                            gotoxy(115-15,y);
                            ghiNhapTen(115-15,y,2);

                        }
                    }
                    else y-=1;
                }
                break;
            }
        case 75:
            {
                if (ok==0)
                {
                    if (y==14)
                    {
                        ShowCur(0);
                        x-=30;
                        if (x==(110-15))
                        {
                            gotoxy(x+30,y);
                            ghiNhapTen(140-15,y,7);
                            gotoxy(x,y);
                            ghiNhapTen(x,y,2);

                        }
                        else x+=30;
                    }
                }
                break;
            }
        case 77:
            {
                if (ok==0)
                {
                    if (y==14)
                    {
                        ShowCur(0);
                        x+=30;
                        if (x==(140-15))
                        {
                            gotoxy(x-30,y);
                            ghiNhapTen(110-15,y,7);
                            gotoxy(x,y);
                            ghiNhapTen(x,y,2);

                        }
                        else x-=30;
                    }
                }
                break;
            }
        case 13:
            {
                if (ok)
                {
                    if (y==14)
                    {
                        if (x==(110-15)) return 0;
                        if (x==(140-15))
                        {
                            if (strlen(player1)<=0 || strlen(player2)<=0)
                            {
                                gotoxy(109-15,16);
                                printf("Vui lòng nhập đủ tên của hai người chơi");
                                sleep(2);
                                gotoxy(109-15,16);
                                printf("                                         ");
                            }
                            else return 1;
                        }
                    }
                    else if (y==12)
                    {
                        gotoxy(135-15,12);
                        printf("                                  ");
                        gotoxy(135-15,12);
                        fflush(stdin);
                        ShowCur(1);
                        player1[0]='\n';
                        gets(player1);
                        gotoxy(135-15+strlen(player1),12);
                        ShowCur(0);
                    }
                    else if (y==13)
                    {
                        gotoxy(135-15,13);
                        printf("                                  ");
                        gotoxy(135-15,13);
                        fflush(stdin);
                        player2[0]='\n';
                        ShowCur(1);
                        gets(player2);
                        gotoxy(135-15+strlen(player2),13);
                        ShowCur(0);
                    }
                }
                break;
            }
        default: break;
        }
    }
}
void hienThiPhuongThucDanh()
{
    system("cls");
    SetScreenBufferSize(200,200);
    gotoxy(120-15,5);
    printf("    <<  Ván mới  >>   ");
    gotoxy(120-15,10);
    printf("Chọn phương thức di chuyển: ");
    gotoxy(115-15,12);
    printf("Di chuyển bằng 1 bên trên bàn phím");
    gotoxy(115-15,13);
    printf("Di chuyển bằng 2 bên trên bàn phím");
}
void ghiPhuongThuc(int y, int mau)
{
    set_color(mau);
    if (y==12)
    {
        printf("Di chuyển bằng 1 bên trên bàn phím");
    }
    if (y==13)
    {
        printf("Di chuyển bằng 2 bên trên bàn phím");
    }
    set_color(7);
}
int chonPhuongThuc()
{
    ShowCur(0);
    int x=115-15, y=12;
    gotoxy(x,y);
    ghiPhuongThuc(y,2);
    while (true)
    {
        ok=0;
        char bam;
        fflush(stdin);
        bam=getch();
        if (bam==-32) bam=getch();
        else ok=1;
        switch (chuHoa(bam))
        {
        case 72:
            {
                if (ok==0)
                {
                    y-=1;
                    if (y==12)
                    {
                        gotoxy(x,y+1);
                        ghiPhuongThuc(y+1,7);
                        gotoxy(x,y);
                        ghiPhuongThuc(y,2);
                    }
                    else y+=1;
                }
                break;
            }
        case 80:
            {
                if(ok==0)
                {
                    y+=1;
                    if (y==13)
                    {
                        gotoxy(x,y-1);
                        ghiPhuongThuc(y-1,7);
                        gotoxy(x,y);
                        ghiPhuongThuc(y,2);
                    }
                    else y-=1;
                }
                break;
            }
        case 13:
            {
                if (ok)
                {
                    if (y==12) return 1;
                    else return 2;
                }
            }

        }
    }
}
void ghiChoiLai(int x, int mau)
{
    set_color(mau);
    if (x==150) printf("Chơi lại");
    else printf("Về menu");
    set_color(7);
}
int choiLai()
{
    gotoxy(150,22);
    printf("Chơi lại");
    gotoxy(180,22);
    printf("Về menu");
    int x=150, y=22;
    gotoxy(x,y);
    ghiChoiLai(x,2);
    gotoxy(x,y);
    while (true)
    {
        ok=0;
        char bam;
        fflush(stdin);
        bam=getch();
        if (bam==-32) bam=getch();
        else ok=1;
        switch (chuHoa(bam))
        {
        case 75:
            {
                if (ok==0)
                {
                    x-=30;
                    if (x==150)
                    {
                        gotoxy(180,y);
                        ghiChoiLai(180,7);
                        gotoxy(x,y);
                        ghiChoiLai(x,2);
                    }
                    else x+=30;
                }
                break;
            }
        case 77:
            {
                if (ok==0)
                {
                    x+=30;
                    if (x==180)
                    {
                        gotoxy(150,y);
                        ghiChoiLai(150,7);
                        gotoxy(x,y);
                        ghiChoiLai(x,2);
                    }
                    else x-=30;
                }
                break;
            }
        case 13:
            {
                if(ok)
                {
                    if (x==150) return 1;
                    else return 0;
                }
            }
        }
    }

}
void ghiDoiLuot(int x, int mau)
{
    set_color(mau);
    if (x==150) printf("Có");
    else printf("Không");
    set_color(7);
}
int doiLuot()
{
    gotoxy(155,20);
    printf("Bạn có muốn đổi lượt không?");
    gotoxy(150,22);
    printf("Có           ");
    gotoxy(180,22);
    printf("Không        ");
    int x=150,y=22;
    gotoxy(x,y);
    ghiDoiLuot(x,2);
    while (true)
    {
        ok=0;
        char bam;
        fflush(stdin);
        bam=getch();
        if (bam==-32) bam=getch();
        else ok=1;
        switch (chuHoa(bam))
        {
        case 75:
            {
                if (ok==0)
                {
                    x-=30;
                    if (x==150)
                    {
                        gotoxy(180,y);
                        ghiDoiLuot(180,7);
                        gotoxy(x,y);
                        ghiDoiLuot(x,2);
                    }
                    else x+=30;
                }
                break;
            }
        case 77:
            {
                if (ok==0)
                {
                    x+=30;
                    if (x==180)
                    {
                        gotoxy(150,y);
                        ghiDoiLuot(150,7);
                        gotoxy(x,y);
                        ghiDoiLuot(x,2);
                    }
                    else x-=30;
                }
                break;
            }
        case 13:
            {
                if (ok)
                {
                    if (x==150 ) return 1;
                    else return 0;
                }
            }
        }
    }
}
void hienThiHuongDan()
{
    system("cls");
    SetScreenBufferSize(200,200);
    gotoxy(105,5);
    printf("  <<  Hướng dẫn  >>  ");
    gotoxy(110,10);
    printf("Luật chơi:");
    gotoxy(80,12);
    printf("- Bàn cờ gồm có 25x25 ô vuông.");
    gotoxy(80,13);
    printf("- Sử dụng cách thức di chuyển và đánh như hướng dẫn bên dưới.");
    gotoxy(80,14);
    printf("- Người chơi nào đánh đánh dấu được ít nhất 5 quân cờ của mình liên tiếp theo hàng thẳng (ngang, dọc , chéo) trước thì dành chiến thắng.");
    gotoxy(80,15);
    printf("- Người chơi có quân cờ X được đi trước và hai người sẽ đánh xen kẽ nhau.");
    gotoxy(107,17);
    printf("Cách di chuyển:");
    gotoxy(80,19);
    printf("Chế độ 2 người:");
    gotoxy(85,20);
    printf("Người chơi 1:");
    gotoxy(90,21);
    printf("W : Lên");
    gotoxy(90,22);
    printf("S : Xuống");
    gotoxy(90,23);
    printf("A : Sang trái");
    gotoxy(90,24);
    printf("D : Sang phải");
    gotoxy(90,25);
    printf("Space : đánh dấu quân cờ");
    gotoxy(135,20);
    printf("Người chơi 2:");
    gotoxy(140,21);
    printf("Sử dụng các nút điều hướng để di chuyển.");
    gotoxy(140,22);
    printf("Enter : đánh dấu quân cờ");
    gotoxy(80,27);
    printf("Chế độ 1 người: di chuyển và đánh như người chới 2 bên trên");
    gotoxy(110,29);
    set_color(1);
    printf("Bấm nút ESC để về menu");
    set_color(7);
    while (true)
    {
        char bam;
        fflush(stdin);
        bam=getch();
        if (bam==27) return 0;
    }
}
void hienThiMenu()
{
    ShowCur(0);
    set_color(3);
    gotoxy(97,5);
    printf(" $$$$$$\\   ");
    Sleep(50);
    gotoxy(97,6);
    printf("$$  __$$\\  ");
    Sleep(100);
    gotoxy(97,7);
    printf("$$ /  \\__|");
    Sleep(50);
    gotoxy(97,8);
    printf("$$ |        ");
    Sleep(50);
    gotoxy(97,9);
    printf("$$ |        ");
    Sleep(50);
    gotoxy(97,10);
    printf("$$ |  $$\\  ");
    Sleep(50);
    gotoxy(97,11);
    printf("\\$$$$$$  | ");
    Sleep(50);
    gotoxy(97,12);
    printf(" \\______/  ");
    Sleep(50);
    set_color(4);
    gotoxy(107,7);
    printf(" $$$$$$\\  ");
    Sleep(50);
    gotoxy(107,8);
    printf(" \\____$$\\");
    Sleep(50);
    gotoxy(107,9);
    printf(" $$$$$$$ | ");
    Sleep(50);
    gotoxy(107,10);
    printf("$$  __$$ | ");
    Sleep(50);
    gotoxy(107,11);
    printf("\\$$$$$$$ |");
    Sleep(50);
    gotoxy(107,12);
    printf(" \\_______|");
    Sleep(50);
    set_color(1);
    gotoxy(117,7);
    printf(" $$$$$$\\  ");
    Sleep(50);
    gotoxy(117,8);
    printf("$$  __$$\\ ");
    Sleep(50);
    gotoxy(117,9);
    printf("$$ |  \\__|");
    Sleep(50);
    gotoxy(117,10);
    printf("$$ |       ");
    Sleep(50);
    gotoxy(117,11);
    printf("$$ |       ");
    Sleep(50);
    gotoxy(117,12);
    printf("\\__|      ");
    Sleep(50);
    set_color(6);
    gotoxy(127,7);
    printf(" $$$$$$\\   ");
    Sleep(50);
    gotoxy(127,8);
    printf("$$  __$$\\  ");
    Sleep(50);
    gotoxy(127,9);
    printf("$$ /  $$ |  ");
    Sleep(50);
    gotoxy(127,10);
    printf("$$ |  $$ |  ");
    Sleep(50);
    gotoxy(127,11);
    printf("\\$$$$$$  | ");
    Sleep(50);
    gotoxy(127,12);
    printf(" \\______/  ");
    Sleep(100);
    set_color(7);
    gotoxy(112,17);
    printf("Chơi tiếp");
    Sleep(100);
    gotoxy(112,18);
    printf("Ván mới");
    Sleep(100);
    gotoxy(112,19);
    printf("Hướng dẫn");
    Sleep(100);
    gotoxy(112,20);
    printf("Thoát Game");
    gotoxy(90,25);
    set_color(8);
    printf("(Dùng các nút điều hướng để di chuyển. Bấm Enter để chọn.)");
    set_color(7);
}
void hienThiTamBiet()
{
    printf("\t\t\t\t\t\t\t\t\t\t ________  ______   __       __        _______   ______  ________  ________    \n");
    printf("\t\t\t\t\t\t\t\t\t\t/        |/      \\ /  \\     /  |      /       \\ /      |/        |/        |   \n");
    printf("\t\t\t\t\t\t\t\t\t\t$$$$$$$$//$$$$$$  |$$  \\   /$$ |      $$$$$$$  |$$$$$$/ $$$$$$$$/ $$$$$$$$/    \n");
    printf("\t\t\t\t\t\t\t\t\t\t   $$ |  $$ |__$$ |$$$  \\ /$$$ |      $$ |__$$ |  $$ |  $$ |__       $$ |      \n");
    printf("\t\t\t\t\t\t\t\t\t\t   $$ |  $$    $$ |$$$$  /$$$$ |      $$    $$<   $$ |  $$    |      $$ |      \n");
    printf("\t\t\t\t\t\t\t\t\t\t   $$ |  $$$$$$$$ |$$ $$ $$/$$ |      $$$$$$$  |  $$ |  $$$$$/       $$ |      \n");
    printf("\t\t\t\t\t\t\t\t\t\t   $$ |  $$ |  $$ |$$ |$$$/ $$ |      $$ |__$$ | _$$ |_ $$ |_____    $$ |      \n");
    printf("\t\t\t\t\t\t\t\t\t\t   $$ |  $$ |  $$ |$$ | $/  $$ |      $$    $$/ / $$   |$$       |   $$ |      \n");
    printf("\t\t\t\t\t\t\t\t\t\t   $$/   $$/   $$/ $$/      $$/       $$$$$$$/  $$$$$$/ $$$$$$$$/    $$/       \n");
}
void ghiChonFile(int x, int y, int mau)
{
    set_color(mau);
    if (y==44) printf("Nhập tên ván đấu: ");
    if (y==46)
    {
        if (x==90) printf("Về menu");
        if (x==130) printf("Bắt đầu chơi");
    }
    set_color(7);
}
void hienThiList()
{
    int x=90,y=13,d=0;
    for (node*i=first; i!=NULL; i=i->next)
    {
        gotoxy(x,y+(d%15));
        printf("%2d. %-30s",d+1,i->data);
        d++;
        if(d==15) x+=40;
    }
}
int hienThiDanhSachFile()
{
    system("cls");
    SetScreenBufferSize(200,200);
    ShowCur(0);
    gotoxy(105,5);
    printf("    <<  Chơi tiếp  >>   ");
    gotoxy(100,10);
    printf("Danh sách các trận đấu đã lưu: ");
    char tmp[30];
    if (first==NULL)
    {
        gotoxy(100,15);
        printf("Hiện tại không có trận đấu nào.");
        gotoxy(102,17);
        set_color(2);
        printf("Bấm nút bất kỳ để về menu");
        set_color(7);
        getch();
        return 0;
    }
    hienThiList();
    gotoxy(100,44);
    printf("Nhập tên ván đấu: ");
    gotoxy(90,46);
    printf("Về menu");
    gotoxy(130,46);
    printf("Bắt đầu chơi");
    int x=100, y=44;
    gotoxy(100,44);
    ghiChonFile(100,44,2);
    while (true)
    {
        ok=0;
        char bam;
        fflush(stdin);
        bam=getch();
        if(bam==-32) bam=getch();
        else ok=1;
        switch (chuHoa(bam))
        {
        case 72:
            {
                if (ok==0)
                {
                    y-=2;
                    if (y==44)
                    {
                        gotoxy(x,46);
                        ghiChonFile(x,46,7);
                        gotoxy(100,44);
                        ghiChonFile(100,44,2);
                        x=100;
                    }
                    else y+=2;
                }
                break;
            }
        case 80:
            {
                if (ok==0)
                {
                    y+=2;
                    if (y==46)
                    {
                        gotoxy(100,44);
                        ghiChonFile(100,44,7);
                        gotoxy(130,46);
                        ghiChonFile(130,46,2);
                        x=130;
                    }
                    else y-=2;
                }
                break;
            }
        case 75:
            {
                if (ok==0)
                {
                    if (y==46)
                    {
                        x-=40;
                        if (x==90)
                        {
                            gotoxy(130,46);
                            ghiChonFile(130,46,7);
                            gotoxy(90,46);
                            ghiChonFile(90,46,2);
                            x=90;
                        }
                    else x+=40;
                    }
                }
                break;
            }
        case 77:
            {
                if (ok==0)
                {
                    if (y==46)
                    {
                        x+=40;
                        if (x==130)
                        {
                            gotoxy(90,46);
                            ghiChonFile(90,46,7);
                            gotoxy(130,46);
                            ghiChonFile(130,46,2);
                            x=130;
                        }
                        else x-=40;
                    }
                }
                break;
            }
        case 13:
            {
                if (ok)
                {
                    if (y==44)
                    {
                        tenFileNhap[0]='\n';
                        fflush(stdin);
                        ShowCur(1);
                        gotoxy(120,44);
                        printf("                                       ");
                        gotoxy(120,44);
                        gets(tenFileNhap);
                        gotoxy(120+strlen(tenFileNhap),44);
                        ShowCur(0);
                    }
                    if (y==46)
                    {
                        if (x==90) return 0;
                        if (x==130)
                        {
                            if (strlen(tenFileNhap)<=0)
                            {
                                gotoxy(100,48);
                                printf("Vui lòng nhập tên File");
                                sleep(2);
                                gotoxy(100,48);
                                printf("                           ");
                            }
                            else
                            {
                                if (tonTaiTenFile(tenFileNhap)==0)
                                {
                                    gotoxy(95,48);
                                    printf("Vui lòng nhập đúng một trong những tên trên danh sách.");
                                    sleep(2);
                                    gotoxy(100,48);
                                    printf("                                                      ");
                                }
                                else
                                {
                                    xoaTenFile(tenFileNhap);
                                    return 1;
                                }
                            }
                        }
                    }
                }
                break;
            }
            default: break;
        }
    }
}
void  xoaTenFile(char tenFile[])
{
    if (strcmp(first->data,tenFile)==0)
    {
        node* pNode=first;
        first=first->next;
        free(pNode);
    }
    else
    {
        node* i;
        for (i=first; i->next!=NULL; i=i->next)
        {
            if (strcmp(i->next->data,tenFile)==0) break;
        }
        if (i->next!=NULL)
        {
            node* pNode=i->next;
            i->next=i->next->next;
            free(pNode);
        }
    }
    top--;
}
void SetWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;

    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}
void SetScreenBufferSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD NewSize;
    NewSize.X = width;
    NewSize.Y = height;

    SetConsoleScreenBufferSize(hStdout, NewSize);
}
void taiDanhSach()
{
    FILE* f=fopen("listFile.c","w");
    node* pNode=NULL;
    for (node* i=first; i!=NULL; i=i->next)
    {
        pNode=themNodeVaoDau(i->data,pNode);
    }
    for(node* i=pNode; i!=NULL; i=i->next)
    {
        fprintf(f,"%s ",i->data);
    }
    fclose(f);
}
void choi()
{
    SetScreenBufferSize(200,200);
    SetConsoleOutputCP(65001);
    endGame=1;
    quit=0;
    start=1;
    first=NULL;
    char a[MAX][MAX]={0};
    FILE *f=fopen("listFile.c","a");
    fclose(f);
    layDanhSach();
    while (true)
    {
        ShowCur(0);
        system("cls");
        SetScreenBufferSize(200,200);
        hienThiMenu();
        diChuyenMenu(a);
        if (quit)
        {
            system("cls");
            SetScreenBufferSize(200,200);
            hienThiTamBiet();
            break;
        }
    }
    taiDanhSach();
    xoaDanhSach(first);
}

