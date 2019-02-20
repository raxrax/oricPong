#include <lib.h>

#define CURSOR_START 10 // #26a,10
#define CURSOR_END 3 // #26a,3

#define SCREEN 0xbb80
#define STICK_HEIGHT 5
#define CHAR_BALL 96
#define CHAR_NET 124
#define CHAR_SCORE 95
#define CHAR_STICK 127

#define POS_SCORE_P1 10
#define POS_SCORE_P2 22

#define BALL_DELIMITER 4

unsigned char keyUp = 'A';
unsigned char keyDown = 'Z';
unsigned char boardType = 0;

unsigned char xPlayer1, xPlayer2, yPlayer1, yPlayer2, xOldPlayer1, xOldPlayer2, yOldPlayer1, yOldPlayer2, i, scorePlayer1, scorePlayer2, xBall, yBall, realBallX, realBallY;
char dbx, dby, bgBall = 32;

unsigned char engineRunning = 1;

int multi40[200] = {0, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440, 480, 520, 560, 600, 640, 680, 720, 760, 800, 840, 880, 920, 960, 1000, 1040, 1080, 1120, 1160, 1200, 1240, 1280, 1320, 1360, 1400, 1440, 1480, 1520, 1560, 1600, 1640, 1680, 1720, 1760, 1800, 1840, 1880, 1920, 1960, 2000, 2040, 2080, 2120, 2160, 2200, 2240, 2280, 2320, 2360, 2400, 2440, 2480, 2520, 2560, 2600, 2640, 2680, 2720, 2760, 2800, 2840, 2880, 2920, 2960, 3000, 3040, 3080, 3120, 3160, 3200, 3240, 3280, 3320, 3360, 3400, 3440, 3480, 3520, 3560, 3600, 3640, 3680, 3720, 3760, 3800, 3840, 3880, 3920, 3960, 4000, 4040, 4080, 4120, 4160, 4200, 4240, 4280, 4320, 4360, 4400, 4440, 4480, 4520, 4560, 4600, 4640, 4680, 4720, 4760, 4800, 4840, 4880, 4920, 4960, 5000, 5040, 5080, 5120, 5160, 5200, 5240, 5280, 5320, 5360, 5400, 5440, 5480, 5520, 5560, 5600, 5640, 5680, 5720, 5760, 5800, 5840, 5880, 5920, 5960, 6000, 6040, 6080, 6120, 6160, 6200, 6240, 6280, 6320, 6360, 6400, 6440, 6480, 6520, 6560, 6600, 6640, 6680, 6720, 6760, 6800, 6840, 6880, 6920, 6960, 7000, 7040, 7080, 7120, 7160, 7200, 7240, 7280, 7320, 7360, 7400, 7440, 7480, 7520, 7560, 7600, 7640, 7680, 7720, 7760, 7800, 7840, 7880, 7920, 7960};

/* unsigned char numbersData[] ={
           62,34,34,34,34,34,62,0,
           8,8,8,8,8,8,8,0,
           62,2,2,62,32,32,62,0,
           62,2,2,30,2,2,62,0,
           36,36,36,36,62,4,4,0,
           62,32,32,62,2,2,62,0,
           32,32,32,62,34,34,62,0,
           62,2,2,2,2,2,2,0,
           62,34,34,62,34,34,62,0,
           62,34,34,62,2,2,62,0,
}; */



char * numbersData[10][6] = {
    {
        "___",
        "_ _",
        "_ _",
        "_ _",
        "___"
    },
    {
        " _ ",
        " _ ",
        " _ ",
        " _ ",
        " _ ",
    },
    {
        "___",
        "  _",
        "___",
        "_  ",
        "___",
    },
    {
        "___",
        "  _",
        "___",
        "  _",
        "___",
    },

    {
        "_ _",
        "_ _",
        "___",
        "  _",
        "  _",
    },
    {
        "___",
        "_  ",
        "___",
        "  _",
        "___",
    },

    {
        "_  ",
        "_  ",
        "___",
        "_ _",
        "___",
    },

    {
        "___",
        "  _",
        "  _",
        "  _",
        "  _",
    },

    {
        "___",
        "_ _",
        "___",
        "_ _",
        "___",
    },

    {
        "___",
        "_ _",
        "___",
        "  _",
        "  _",
    }
};



unsigned char scoreFont[] = {63, 63, 63, 63, 63, 63, 63, 63};
unsigned char netFont[] = {8, 8, 0, 0, 0, 0, 0, 0};
unsigned char ballFont[] = {0, 0, 30, 30, 30, 30, 0, 0};

unsigned char ballTR[] = {15, 15, 15, 15, 0, 0, 0, 0};
unsigned char ballTL[] = {60, 60, 60, 60, 0, 0, 0, 0};
unsigned char ballDR[] = {0, 0, 0, 0, 15, 15, 15, 15};
unsigned char ballDL[] = {0, 0, 0, 0, 60, 60, 60, 60};

void main()
{
    text();

    font();
    poke(0x26A, CURSOR_START);
    poke(0x24e, 1);
    poke(0x24f, 1);
    cls2();


    init();
    title();
    get();

    cls2();
    init();
    get();

    engine();


    poke(0x26A, CURSOR_END);
}

void font()
{
    memcpy((void *) (0xb400 + CHAR_NET * 8), netFont, 8);
    memcpy((void *) (0xb400 + CHAR_SCORE * 8), scoreFont, 8);
    memcpy((void *) (0xb400 + CHAR_BALL * 8), ballFont, 8);

}

void engine()
{

    engineRunning = 1;

    init();

    while (engineRunning)
    {
        player();

        enemy();

        ball();

        wait(5);
    }
}

void init()
{

    xPlayer1 = 2;
    xPlayer2 = 37;
    yPlayer1 = 10;
    yPlayer2 = 10;

    xBall = 20 * 5;
    yBall = 10 * 5;
    dbx = -3;
    dby = -3;

    scorePlayer1 = 0;
    scorePlayer2 = 0;

    board();
    printScore();
    printStick(xPlayer1, yPlayer1);
    printStick(xPlayer2, yPlayer2);
}

void player()
{
    char key1;

    xOldPlayer1 = xPlayer1;
    xOldPlayer2 = xPlayer2;

    key1 = key();

    if (key1 == keyUp && yPlayer1 > 0) yPlayer1--;
    if (key1 == keyDown && yPlayer1 < 23) yPlayer1++;
    if (key1 == 'T')
    {
        boardType++;
        boardType = boardType > 1 ? 0 : boardType;
        board();
    }
    if (key1 == 'P') get();
    if (key1 == 'E') engineRunning = 0;

    if (yOldPlayer1 != yPlayer1)
    {
        eraseStick(xOldPlayer1, yOldPlayer1);
        printStick(xPlayer1, yPlayer1);
    }
}

void enemy()
{
    static count = 0;
    count++;
    if (count % 3 == 0) return;

    yOldPlayer1 = yPlayer1;
    yOldPlayer2 = yPlayer2;

    if (realBallX > 28 - scorePlayer1 / 5 && yPlayer2 + (STICK_HEIGHT / 2) > yBall / BALL_DELIMITER && yPlayer2 > 0) (yPlayer2--);

    if (realBallX > 28 - scorePlayer1 / 5 && yPlayer2 + (STICK_HEIGHT / 2) < yBall / BALL_DELIMITER && yPlayer2 < 23) (yPlayer2++);

    if (yOldPlayer2 != yPlayer2)
    {
        eraseStick(xOldPlayer2, yOldPlayer2);
        printStick(xPlayer2, yPlayer2);
    }
}

void board()
{

    paper(0);
    ink(7);

    switch (boardType)
    {
        case 0:
            memcpy((void *) (0xb400 + CHAR_SCORE * 8), scoreFont, 8);
            break;

        case 1:
            memcpy((void *) (0xb400 + CHAR_SCORE * 8), (void *) (0xb400 + 126 * 8), 8);
            break;
    }

    for (i = 0; i < 28; i++)
    {
        poke(0xbb80 + 19 + (i * 40), CHAR_NET);
    }
}

void ball()
{
    unsigned char tmp;
    realBallX = xBall / BALL_DELIMITER;
    realBallY = yBall / BALL_DELIMITER;

    if (realBallX - 1 == xPlayer1 && realBallY >= yPlayer1 && realBallY < yPlayer1 + STICK_HEIGHT)
    {
        tmp = (realBallY - yPlayer1)-(STICK_HEIGHT / 2);
        dbx = (rand() % BALL_DELIMITER / 2 + 3);
        //dby = tmp == 0 ?  dby : tmp+rand()%2;
        dby = tmp == 0 ? dby : tmp;
    }

    if (realBallX < 1)
    {
        dbx = 3;
        xBall += 3;
        scorePlayer2++;
        printScore();
    }

    if (realBallX + 1 == xPlayer2 && realBallY >= yPlayer2 && realBallY < yPlayer2 + STICK_HEIGHT)
    {
        dbx = -(rand() % BALL_DELIMITER / 2 + 3);
    }

    if (realBallX > 38)
    {
        dbx = -3;
        xBall -= 3;
        scorePlayer1++;
        printScore();
    }

    if (realBallY < 1) dby = -dby;
    if (realBallY > 26) dby = -dby;

    poke(0xbb80 + realBallX + (multi40[realBallY]), bgBall);

    xBall = xBall + dbx;
    yBall = yBall + dby;

    realBallX = xBall / BALL_DELIMITER;
    realBallY = yBall / BALL_DELIMITER;

    modBall();
    printBall();

}

void modBall()
{
    switch (xBall % BALL_DELIMITER)
    {
        case 0:
        case 1:
            switch (yBall % BALL_DELIMITER)
            {
                case 0:
                case 1:
                    memcpy((void *) (0xb400 + CHAR_BALL * 8), ballTL, 8);
                    break;

                default:
                    memcpy((void *) (0xb400 + CHAR_BALL * 8), ballDL, 8);
                    break;
            }

            break;

        default:
            switch (yBall % BALL_DELIMITER)
            {
                case 0:
                case 1:
                    memcpy((void *) (0xb400 + CHAR_BALL * 8), ballTR, 8);
                    break;

                default:
                    memcpy((void *) (0xb400 + CHAR_BALL * 8), ballDR, 8);
                    break;
            }
            break;
    }
}

void printBall()
{
    bgBall = peek(0xbb80 + realBallX + (multi40[realBallY]));
    poke(0xbb80 + realBallX + (multi40[realBallY]), CHAR_BALL);
}

void printStick(unsigned char x, unsigned char y)
{
    unsigned char h;
    unsigned int screenAddr;
    screenAddr = SCREEN + x;

    for (h = 0; h < STICK_HEIGHT; h++)
    {
        poke(screenAddr + (multi40[y + h]), CHAR_STICK);
    }
}

void eraseStick(unsigned char x, unsigned char y)
{
    unsigned char h;
    unsigned int screenAddr;
    screenAddr = SCREEN + x;

    for (h = 0; h < STICK_HEIGHT; h++)
    {
        poke(screenAddr + (multi40[y + h]), 32);
    }
}

void wait(unsigned int time)
{
    int now;
    now = deek(0x276);
    while (now - deek(0x276) < time)
    {
        ;
    }
    doke(0x276, 0);
}

void printScore()
{
    unsigned int srcCharAddr;
    unsigned curChar;

    if (scorePlayer1 > 99) scorePlayer1 = 99;
    if (scorePlayer2 > 99) scorePlayer2 = 99;

    curChar = scorePlayer1 % 10;
    printNumber(curChar, 0xbb80 + POS_SCORE_P1 + 4);

    curChar = scorePlayer1 / 10;
    printNumber(curChar, 0xbb80 + POS_SCORE_P1);


    curChar = scorePlayer2 % 10;
    printNumber(curChar, 0xbb80 + POS_SCORE_P2 + 4);

    curChar = scorePlayer2 / 10;
    printNumber(curChar, 0xbb80 + POS_SCORE_P2);

}

void printNumber(unsigned char num, unsigned int addr)
{
    for (i = 0; i < 5; i++)
    {
        sprintf((void *) (addr + multi40[i]), "%s", numbersData[num][i]);
    }
}

void cls2()
{
    memset((void *) 0xbb80, 32, 40);
    cls();
}

void title()
{
    cls2();

    printf("                                      ");
    printf("                                      ");
    printf("                                      ");
    printf("                                      ");
    printf("                                      ");
    printf("                                      ");
    printf("                                      ");
    printf("                                      ");
    printf("                                      ");
    printf("                              `       ");
    printf("                                      ");
    printf("                                      ");
    printf("                                      ");
    printf("                                      ");
    printf("                                      ");
    printf("                                      ");
    printf("    _____  _____  _   _  _____        ");
    printf("    _   _  _   _  __  _  _            ");
    printf("    _____  _   _  _ _ _  _ ___        ");
    printf("    _      _   _  _  __  _   _        ");
    printf("    _      _____  _   _  _____        ");
    printf("                                      ");
    printf("                                      ");
    printf("                                      ");
    printf("                                      ");

    init();
}