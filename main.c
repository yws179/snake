/***********************************************************
    > File Name:     Snakev4.0
    > Author:        YWS
    > Mail:          563098030@qq.com
    > ADI:           Codeblocks
    > Created Time:  2015年10月30日 23:58:50
************************************************************/

#include <F:\外部头文件\pcc32.h>
#define FALSE 0
#define TRUE 1
#define HEAD 2
#define FOOD 3
#define BODY 4

int len=2,key=JK_RIGHT,tempKey,a=FALSE,delay=500,b=0;
char degree='1';
struct Snake
{
    int x;
    int y;
}snake[100];

struct Food
{
    int x;
    int y;
}food;

int option();
void pOption(int b);
void enterOption(int b);
void game();
void initialise();
void start();
void printScreen();
void getFood();
int getLongerSnake();
void upDate();
void drawFood();
void getKey();
void drawSnake();
void drawData();
int dead();
void gameWin();
void gameOver();
void help();
void about();

int main()
{
    initialise();
    option();
    return 0;
}

int option()
{
    int i=0;
    for(;i<15;i++)
    {
        pccGotoPos(0,i);
        putchar('|');
        pccGotoPos(49,i);
        putchar('|');
    }
    pOption(b);
    while(1)
    {
        if(pccHasKey())
        {
            switch(pccGetKey())
            {
                case JK_UP:
                    if(b>0)b--;
                    pOption(b);
                    break;
                case JK_DOWN:
                    if(b<3)b++;
                    pOption(b);
                    break;
                case JK_ENTER:
                    system("cls");
                    enterOption(b);
                default:break;
            }
        }
        if(i>=14)i=0;
        pccGotoPos(49,i);
        putchar('*');
        pccGotoPos(0,i);
        putchar('*');
        Sleep(100);
        pccGotoPos(49,i);
        putchar('|');
        pccGotoPos(0,i);
        putchar('|');
        i++;
    }
}

void enterOption(int b)
{
    switch(b)
    {
        case 0:
            start();
            system("cls");
            game();
            break;
        case 1:
            help();
            break;
        case 2:
            about();
            break;
        case 3:
            exit(0);
        default:break;
    }
}

void pOption(int b)
{
    pccGotoPos(0,1);
    pccSetTextColor(YELLOW);
    printf("      ***   **    *      *      *   *  * * * \n");
	printf("     *      * *   *     * *     *  *   *      \n");
	printf("       *    *  *  *    * * *    * *    * * * \n");
	printf("        *   *   * *   *     *   *  *   *      \n");
	printf("     ***    *    **  *       *  *   *  * * * \n");
    pccGotoPos(18,10);
    pccSetTextColor(WHITE);
    switch(b)
    {
        case 0:
            printf("> start game <");
            pccGotoPos(24,9);
            putchar(' ');
            pccGotoPos(24,11);
            putchar(31);
            break;
        case 1:
            printf(">    help    <");
            pccGotoPos(24,9);
            putchar(30);
            break;
        case 2:
            printf(">    about   <");
            pccGotoPos(24,11);
            putchar(31);
            break;
        case 3:
            printf(">    exit    <");
            pccGotoPos(24,11);
            putchar(' ');
        default:break;
    }
}

void start()
{
    printf("\n              请选择游戏难度：\n");
    printf("\n                 1.easy\n");
    printf("\n                 2.normal\n");
    printf("\n                 3.hard\n");
    printf("\n                 4.hell\n");
    printf("\n                 5.god's game");
    do
    {
        degree=getch();
        switch(degree)
        {
            case '1':delay=500;break;
            case '2':delay=250;break;
            case '3':delay=100;break;
            case '4':delay=50;break;
            case '5':delay=1;break;
        }
    }while(degree!='1'&&degree!='2'&&degree!='3'&&degree!='4'&&degree!='5');
}

void game()
{
    printScreen();
    while(1)
    {

        getFood();
        drawSnake();
        drawFood();
        getKey();
        upDate();
        drawData();
        if(dead())gameOver();
        Sleep(delay);
    }
}

void initialise()
{
    pccFixSize(50, 15);
    pccShowCursor(0);
    srand(time(NULL));
    snake[0].x=10;
    snake[0].y=10;
}

void printScreen()
{
    int i;
    for(i=0;i<15;i++)
    {
        pccGotoPos(31,i);
        putchar('|');
    }
    pccGotoPos(34,1);
    printf("Degree:");
    pccGotoPos(34,3);
    printf("Length:");
    pccGotoPos(34,5);
    printf("Score:");
    pccGotoPos(33,14);
    printf("Press P to pause");
}

void getFood()
{
    if(a==FALSE)
    {
        while(1)
        {
            food.x=rand()%30;
            food.y=rand()%15;
            break;
        }
        a=TRUE;
    }
}

void getKey()
{
    if(kbhit())
    {
        tempKey=pccGetKey();
        switch(tempKey)
        {
            case JK_UP:
                if(snake[0].x!=snake[1].x||snake[0].y+1!=snake[1].y)
                    key=tempKey;
                break;
            case JK_DOWN:
                if(snake[0].x!=snake[1].x||snake[0].y-1!=snake[1].y)
                    key=tempKey;
                break;
            case JK_LEFT:
                if(snake[0].x-1!=snake[1].x||snake[0].y!=snake[1].y)
                    key=tempKey;
                break;
            case JK_RIGHT:
                if(snake[0].x+1!=snake[1].x||snake[0].y!=snake[1].y)
                    key=tempKey;
                break;
            case 'p':
            case 'P':
                pccPause();
                break;
        }
    }
}

int getLongerSnake()
{
    if(len<99)
    {
        snake[len+1]=snake[len];
        len++;
        return TRUE;
    }
    return FALSE;
}

void upDate()
{
    int i;
    for(i=len;i>=0;i--)
    {
        if(i==0)
        {
            switch(key)
            {
                case JK_UP:snake[0].y-=1;break;
                case JK_DOWN:snake[0].y+=1;break;
                case JK_LEFT:snake[0].x-=1;break;
                case JK_RIGHT:snake[0].x+=1;break;
            }
        }
        else
        {
            snake[i]=snake[i-1];
        }
        if(snake[0].x==food.x&&snake[0].y==food.y)
        {
            if(getLongerSnake()==FALSE)gameWin();
            a=FALSE;
        }
    }
}

void drawFood()
{
    pccSetTextColor(RED);
    pccGotoPos(food.x,food.y);
    putchar(FOOD);
    pccSetTextColor(WHITE);
}

void drawSnake()
{
    int i;
    pccSetTextColor(GREEN);
    for(i=0;i<=len;i++)
    {
        pccGotoPos(snake[i].x,snake[i].y);
        if(i==0)
            putchar(HEAD);
        else if(i==len)
            putchar(' ');
        else
            putchar(BODY);
    }
    pccSetTextColor(WHITE);
}

void drawData()
{
    pccGotoPos(41,1);
    printf("%5c",degree);
    pccGotoPos(41,3);
    printf("%5d",len);
    pccGotoPos(41,5);
    printf("%5d",len-2);
}

int dead()
{
    int j;
    for(j=1;j<len;j++)
    {
        if((snake[0].x==snake[j].x&&snake[0].y==snake[j].y)
            ||snake[0].x<0||snake[0].x>30||snake[0].y<0||snake[0].y>14)
        {
            return TRUE;
        }
    }
    return FALSE;
}

void gameWin()
{
    system("cls");
    printf("GOOD!!!WIN!!!");
    Sleep(3000);
    exit(0);
}

void gameOver()
{
    system("cls");
    printf("DEAD!!!GAME OVER!!!YOUR SCORE:%d",len-2);
    Sleep(3000);
    exit(0);
}

void help()
{
    printf("游戏规则：\n");
    printf("控制：键盘↑ ↓ ← →控制蛇移动，\"p\"键暂停游戏，在不撞到墙和蛇身的情况下尽可能的吃食物%c\n",FOOD);
    printf("胜利：分数达到100分\n");
    printf("\n\n\n按ESC键返回");
    while(1)
    {
        if(pccGetKey()==JK_ESC)
        {
            system("cls");
            option();
        }
    }
}

void about()
{
    printf("\n\n    > Game Name: Snake\n");
    printf("    > Author: YWS\n");
    printf("    > Mail: 563098030@qq.com\n");
    printf("\n\n\n按ESC键返回");
    while(1)
    {
        if(pccGetKey()==JK_ESC)
        {
            system("cls");
            option();
        }
    }
}
