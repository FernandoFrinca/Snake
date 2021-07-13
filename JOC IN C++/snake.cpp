#include<iostream>
#include<Windows.h>
#include<stdio.h>
#include<string>
#include<fstream>
#include<vector>
using namespace std;
fstream f2("final.txt",ios::in), f("first.txt",ios::in);
int inaltime,latime,k,score,next=2,c=1,cul=1,cull=1,special,special2;
char mapa[100][100]={   //matricea de caractere pentru 1 player
"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX   SCORE:",
"X                                                          X   HIGHSCORE:",
"X                                                          X",
"X           *                                              X   *= 1 punct",
"X                                                          X   O= 3 puncte",
"X                                                          X   X= DEATH",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};
char mapa2[100][100]={   //matricea de caractere pentru 2 players
"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX PLAYER1:RED&WHITE",
"X                                                          X PLAYER2:GREEN&WHITE",
"X                                                          X",
"X                             *                            X PLAYER1:W,A,S,D",
"X                                                          X PLAYER2:ARROWS",
"X                                                          X",
"X                                                          X X=DEATH",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"X                                                          X",
"XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
};
struct Snake{
int x,y;
};
struct punct
{
    char c[333];
}v[19];
void coordonate(int x, int y)
{
    COORD coord={x,y}; //definirea coordonatelor unui punct pe axele de coordonate xOy
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void MAPA(vector<Snake>snake)
{
    int i,j;
    inaltime=0;
    system("cls"); //clear screen
    for(i=0;mapa[i][0];i++)
    {
        if(i==1)
        cout<<score;
        if(i==2)
        {
            int h;
            fstream f3("highscore.txt",ios::in),f4("afisare.txt",ios::out);
            f3>>h;
            if(h>=score)
            {
                cout<<h;
            }
            if(h<score)
            {
                h=score;
                f4<<h;
                cout<<h;
                fstream f5("highscore.txt",ios::out),f6("afisare.txt",ios::in);
                f6>>h;
                f5<<h;
            }
        }
        latime=0;
        for(j=0;mapa[i][j];j++)
        {
            latime++;
            if(mapa[i][j]!=' ')
            {
                coordonate(j,i);
                cout<<mapa[i][j];
            }
        }
        inaltime++;
    }
    for(i=0;i<snake.size()/*returneaza nr. elementelor din vector*/;i++)
    {
        coordonate(snake[i].x,snake[i].y);
        cout<<char(219);// caracterul din care este compus sarpele
    }
}
void MAPA2(vector<Snake>snake)
{
    int i,j;
    inaltime=0;
    system("cls");//clear screen
    for(i=0;mapa2[i][0];i++)
    {
        latime=0;
        for(j=0;mapa2[i][j];j++)
        {
            latime++;
            if(mapa2[i][j]!=' ')
            {
                coordonate(j,i);
                cout<<mapa2[i][j];
            }
        }
        inaltime++;
    }
    for(i=0;i<snake.size();i++)
    {
        coordonate(snake[i].x,snake[i].y);
        cout<<char(219);
    }
}
bool sfarsit(int x, int y, vector<Snake>&snake)
{
    int i;
    if(mapa[y][x]=='X')
    return true;
    if(snake.size()>3)
    for(i=3;i<snake.size();i++)
    if(snake[i].x==x&&snake[i].y==y)
    return true;
    if(mapa[y][x]=='*')
    {
        score++;
        mapa[y][x]=' ';
        Snake newSnake;
        newSnake.x=snake[snake.size()-1].x;
        newSnake.y=snake[snake.size()-1].y;
        snake.push_back(newSnake);//adaugarea unui nou element la sfarsitul vectorului
        int z,zz;
        do{
            z=rand()%latime; //un numar random z de la 0 la latime
            zz=rand()%inaltime; //un numar random zz de la 0 la inaltime
        }while (sfarsit(z, zz,snake));
        mapa[zz][z]='*';
        special++;
        if(special%3==0)
        {
            z=rand()%latime;
            zz=rand()%inaltime;
            mapa[zz][z]='O';
        }
        special2++;
        if(special2==2)
        {
            z=rand()%latime+2;
            zz=rand()%inaltime+2;
            mapa[zz][z]='X';
            special2=0;
        }
        MAPA(snake);
    }
    if(mapa[y][x]=='O')
    {
        score=score+3;
        mapa[y][x]='   ';
        mapa[y][x]='X';special2=1;
        Snake newSnake;
        newSnake.x=snake[snake.size()-1].x;
        newSnake.y=snake[snake.size()-1].y;
        snake.push_back(newSnake);
        MAPA(snake);
    }
    return false;
}
bool sfarsit2(int x, int y, vector<Snake>&snake)
{
    int i;
    if(mapa2[y][x]=='X')
    return true;
    if(snake.size()>3)
    for(i=3;i<snake.size();i++)
    if(snake[i].x==x&&snake[i].y==y)
    return true;
    if(mapa2[y][x]=='*')
    {
        score++;
        mapa2[y][x]=' ';
        Snake newSnake;
        newSnake.x=snake[snake.size()-1].x;
        newSnake.y=snake[snake.size()-1].y;
        snake.push_back(newSnake);
        int z,zz;
        do{
            z=rand()%latime;
            zz=rand()%inaltime;
        }while (sfarsit(z, zz,snake));
        mapa2[zz][z]='*';
        special++;
        if(special%3==0)
        {
            z=rand()%latime;
            zz=rand()%inaltime;
            mapa2[zz][z]='O';
        }
        special2++;
        if(special2==2)
        {
            z=rand()%latime+2;
            zz=rand()%inaltime+2;
            mapa2[zz][z]='X';
            special2=0;
        }
        MAPA2(snake);
    }
    if(mapa2[y][x]=='O')
    {
        score=score+3;
        mapa2[y][x]='   ';
        mapa2[y][x]='X';
        special2=1;
        Snake newSnake;
        newSnake.x=snake[snake.size()-1].x;
        newSnake.y=snake[snake.size()-1].y;
        snake.push_back(newSnake);
        MAPA2(snake);
    }
    return false;
}
void initializare(int x,int y, vector<Snake> &snake)
{
    Snake newSnake;
    newSnake.x=x;
    newSnake.y=y;
    snake.push_back(newSnake);
}
bool miscare(vector<Snake>&snake, short d[2])
{
    int i,xx,yy,x,y;
    coordonate(snake[snake.size()-1].x,snake[snake.size()-1].y);
    cout<<" ";
    xx=snake[0].x;
    yy=snake[0].y;
    snake[0].x=snake[0].x+d[0];
    snake[0].y=snake[0].y+d[1];
    coordonate(snake[0].x,snake[0].y);
    if(snake.size()>1)
    {
        for(i=1;i<snake.size();i++)
        {
            x=snake[i].x;
            y=snake[i].y;
            snake[i].x=xx;
            snake[i].y=yy;
            xx=x;
            yy=y;
        }
    }
    if(k%2==0)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);//schimbarea culorii caracterelor in verde
        cout<<char(219);k++;
    }
    else
    {
        SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 15);//schimbarea culorii caracterelor in alb
        cout<<char(219);k++;
    }
    if(sfarsit(snake[0].x,snake[0].y,snake))
    return true;
    return false;
}
bool miscare2(vector<Snake>&snake, short d[2])
{
    int i,xx,yy,x,y;
    coordonate(snake[snake.size()-1].x,snake[snake.size()-1].y);
    cout<<" ";
    xx=snake[0].x;
    yy=snake[0].y;
    snake[0].x=snake[0].x+d[0];
    snake[0].y=snake[0].y+d[1];
    coordonate(snake[0].x,snake[0].y);
    if(snake.size()>1)
    {
        for(i=1;i<snake.size();i++)
        {
            x=snake[i].x;
            y=snake[i].y;
            snake[i].x=xx;
            snake[i].y=yy;
            xx=x;
            yy=y;
        }
    }
    if(k%2==0)
    {
        if(cull==1)
        {SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout<<char(219);cull=2;}
        else
        {SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 2);
        cout<<char(219);cull=1;}
        k++;
    }
    else
    {
        if(cul==1)
        {SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 12);
        cout<<char(219);cul=2;}
        else
        {SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 15);
        cout<<char(219);cul=1;}
        k++;
    }
    if(sfarsit2(snake[0].x,snake[0].y,snake))
    return true;
    return false;
}
int main()
{
    bool Merge=true;
    int viteza=110,q;
    short d[2]={0,1};
    short d2[2]={0,1};
    int jj,pp;
    for(jj=1;jj<=19;jj++)
    {
        f2.get(v[jj].c,1000);
        f2.get();
    }
    string meniu[4]={"  1PLAYER                                                                        ","2PLAYERS                                                                       ","MUSIC                                                                     ","      IESIRE JOC"};
    int tt=0,ii,xd=0;
    while(true)
    {
        MAIN_CASE:
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
        system("cls");//clear screen
        for(jj=1;jj<=19;jj++)
        {
            cout<<v[jj].c<<endl;//afisarea din fisier a desenului cu sarpe
        }
        for(ii=0;ii<4;ii++)
        {
            if (ii==tt)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                cout<<meniu[ii]<<" ";
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout<<meniu[ii]<<" ";
            }
        }
        while(true)
        {
            if(GetAsyncKeyState(VK_UP)!=0)// VK= virtual-key code
            {
                tt--;
                if(tt==-1)
                {
                    tt=3;
                }
                break;
            }
            else if(GetAsyncKeyState(VK_DOWN)!=0)// VK= virtual-key code
            {
                tt++;
                if(tt==4)
                {
                    tt=0;
                }
                break;
            }
            else if(GetAsyncKeyState(VK_RETURN)!=0)// VK= virtual-key code
            {
                switch(tt)
                {
                    case 0:
                    {

                system("cls");
                vector<Snake>snake;
                initializare(15,12,snake);
                MAPA(snake);
                cout<<" APASA ORICE TASTA PENTRU A INCEPE";
                system("pause > nul");
                MAPA(snake);
                while(Merge)
                {
                    if(GetAsyncKeyState(VK_UP))
                    {
                        if(d[1]==0)
                        {
                            d[1]=-1;
                            d[0]=0;
                        }
                    }
                    else if(GetAsyncKeyState(VK_DOWN))
                    {
                        if(d[1]==0)
                        {
                            d[1]=1;
                            d[0]=0;
                        }
                    }
                    else if(GetAsyncKeyState(VK_LEFT))
                    {
                        if(d[0]==0)
                        {
                            d[1]=0;
                            d[0]=-1;
                        }
                    }
                    else if(GetAsyncKeyState(VK_RIGHT))
                    {
                        if(d[0]==0)
                        {
                            d[1]=0;
                            d[0]=1;
                        }
                    }
                    if(miscare(snake,d))
                    {
                        PlaySound(TEXT("5.wav"), NULL, SND_SYNC);
                        system("cls");score=0;
                        fstream f("first.txt",ios::in);
                char a;int aa=49,k=1;
                while(f>>a)
                {
                    if(GetAsyncKeyState(VK_RETURN)!=0)
                    system("snake.exe");
                    aa++;
                    if(aa==50)
                    {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
                        aa=0;k++;
                    }
                    if(k==3)
                        k=1;
                    if(a=='1')
                        cout<<" ";
                    else
                    cout<<a;
                    Sleep(2);
                }system("snake.exe");

                        break;
                    }
                    Sleep(viteza);
                 }
                    }break;
                    case 1:
                    {
    system("cls");
    vector<Snake>snake;
    vector<Snake>snake2;
    initializare(12,12,snake);
    initializare(20,12,snake2);
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),2);
    MAPA2(snake);
    cout<<" Player2";
    system("pause > nul");
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),12);
    MAPA2(snake2);
    cout<<" Player1";
    system("pause > nul");
    MAPA2(snake2);
    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE),15);
    while(Merge)
    {
        if(GetAsyncKeyState(VK_UP))
        {
            if(d[1]==0)
            {
                d[1]=-1;
                d[0]=0;
            }
        }
        else if(GetAsyncKeyState(VK_DOWN))
        {
            if(d[1]==0)
            {
                d[1]=1;
                d[0]=0;
            }
        }
        else if(GetAsyncKeyState(VK_LEFT))
        {
            if(d[0]==0)
            {
                d[1]=0;
                d[0]=-1;
            }
        }
        else if(GetAsyncKeyState(VK_RIGHT))
        {
            if(d[0]==0)
            {
                d[1]=0;
                d[0]=1;
            }
        }
        if(GetAsyncKeyState(0x57))// valoarea hexazecimala pentru W
        {
            if(d2[1]==0)
            {
                d2[1]=-1;
                d2[0]=0;
            }
        }
        else if(GetAsyncKeyState(0x53))// valoarea hexazecimala pentru S
        {
            if(d2[1]==0)
            {
                d2[1]=1;
                d2[0]=0;
            }
        }
        else if(GetAsyncKeyState(0x41))// valoarea hexazecimala pentru A
        {
            if(d2[0]==0)
            {
                d2[1]=0;
                d2[0]=-1;
            }
        }
        else if(GetAsyncKeyState(0x44))// valoarea hexazecimala pentru D
        {
            if(d2[0]==0)
            {
                d2[1]=0;
                d2[0]=1;
            }
        }
        if(miscare2(snake,d))
        {
            PlaySound(TEXT("5.wav"), NULL, SND_SYNC);
            system("cls");
            PlaySound(TEXT("6.wav"), NULL, SND_LOOP | SND_ASYNC);
            fstream f5("player1.txt",ios::in);
                char a;int aa=49,k=1;
                while(f5>>a)
                {
                    if(GetAsyncKeyState(VK_RETURN)!=0)
                    {
                        PlaySound(NULL, NULL, 0);
                        system("snake.exe");
                    }
                    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 12);
                    if(a=='1')
                        cout<<" ";
                    else
                    cout<<a;
                    Sleep(4.5);
                }
                PlaySound(NULL, NULL, 0);
                system("snake.exe");
            break;
        }
        if(miscare2(snake2,d2))
        {
            PlaySound(TEXT("5.wav"), NULL, SND_SYNC);
            system("cls");
            PlaySound(TEXT("6.wav"), NULL, SND_LOOP | SND_ASYNC);
            fstream f5("player2.txt",ios::in);
                char a;int aa=49,k=1;
                while(f5>>a)
                {
                    if(GetAsyncKeyState(VK_RETURN)!=0)
                    {
                        PlaySound(NULL, NULL, 0);
                        system("snake.exe");
                    }
                    SetConsoleTextAttribute (GetStdHandle(STD_OUTPUT_HANDLE), 2);
                    if(a=='1')
                        cout<<" ";
                    else
                    cout<<a;
                    Sleep(4.5);
                }
                PlaySound(NULL, NULL, 0);
                system("snake.exe");
            break;
        }
        Sleep(viteza);
    }

                    }break;
                    case 2:
                    {
                            string meniu1[4]={"ON","OFF","NEXT","REVENIRE"};
                            int t=0,i;
                            while(true)
                            {
                                system("cls");
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                                for(i=0;i<4;i++)
                                {
                                    if (i==t)
                                    {
                                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                                        cout<<meniu1[i]<<" ";
                                    }
                                    else
                                    {
                                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                                        cout<<meniu1[i]<<" ";
                                    }
                                }
                                while(true)
                                {
                                    if(GetAsyncKeyState(VK_LEFT)!=0)
                                    {
                                        t--;
                                        if(t==-1)
                                        {
                                            t=3;
                                        }
                                        break;
                                    }
                                    else if(GetAsyncKeyState(VK_RIGHT)!=0)
                                    {
                                        t++;
                                        if(t==4)
                                        {
                                            t=0;
                                        }
                                        break;
                                    }
                                    else if(GetAsyncKeyState(VK_RETURN)!=0)
                                    {
                                         switch(t)
                                            {
                                                case 0:
                                                {
                                                    PlaySound(TEXT("1.wav"), NULL, SND_LOOP | SND_ASYNC);

                                                }break;
                                                case 1:
                                                {
                                                    PlaySound(NULL, NULL, 0);
                                                }break;
                                                case 2:
                                                {
                                                    if(next==1)
                                                    {
                                                        PlaySound(TEXT("1.wav"), NULL, SND_LOOP | SND_ASYNC);
                                                        next++;
                                                    }
                                                    else if(next==2)
                                                    {
                                                        PlaySound(TEXT("2.wav"), NULL, SND_LOOP | SND_ASYNC);
                                                        next++;
                                                    }
                                                    else if(next==3)
                                                    {
                                                        PlaySound(TEXT("3.wav"), NULL, SND_LOOP | SND_ASYNC);
                                                        next++;
                                                    }
                                                    else if(next==4)
                                                    {
                                                        PlaySound(TEXT("4.wav"), NULL, SND_LOOP | SND_ASYNC);
                                                        next++;
                                                    }
                                                    else
                                                    {
                                                        PlaySound(TEXT("1.wav"), NULL, SND_LOOP | SND_ASYNC);
                                                        next=2;
                                                    }
                                                }break;
                                                case 3:
                                                {

                                                      goto MAIN_CASE;

                                                }
                                            }break;
                                    }
                                }
                                Sleep(150);
                            }

                    }break;
                    case 3:
                    {
                            string meniu10[2]={"                            YES :(", "          NO :)"};
                            int t=0,i;
                            while(true)
                            {
                                system("cls");
                                cout<<endl;cout<<endl;cout<<endl;cout<<endl;cout<<endl;cout<<endl;cout<<endl;
                                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                                cout<<"                   DO YOU REALLY WANT TO EXIT THIS GAME?";
                                cout<<endl;cout<<endl;cout<<endl;cout<<endl;
                                for(i=0;i<2;i++)
                                {
                                    if (i==t)
                                    {
                                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
                                        cout<<meniu10[i]<<" ";
                                    }
                                    else
                                    {
                                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                                        cout<<meniu10[i]<<" ";
                                    }
                                }
                                while(true)
                                {
                                    if(GetAsyncKeyState(VK_LEFT)!=0)
                                    {
                                        t--;
                                        if(t==-1)
                                        {
                                            t=1;
                                        }
                                        break;
                                    }
                                    else if(GetAsyncKeyState(VK_RIGHT)!=0)
                                    {
                                        t++;
                                        if(t==2)
                                        {
                                            t=0;
                                        }
                                        break;
                                    }
                                    else if(GetAsyncKeyState(VK_RETURN)!=0)
                                    {
                                         switch(t)
                                            {
                                                case 0:
                                                {
                                                    system("cls");
                                                    cout<<"                                                                 PRESS THE RED X";
                                                }break;
                                                case 1:
                                                {
                                                    goto MAIN_CASE;
                                                }break;


                                    }
                                }
                                Sleep(180);
                            }
                    }
                    }break;
                }
            }
        }
        Sleep(180);
    }
}
