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

#define BOARD_TYPES 4

void pong();

unsigned char keyUp = 'A';
unsigned char keyDown = 'Z';
unsigned char boardType = 0;
unsigned char sounds = 1;
unsigned char waitFactor = 0;
unsigned char color = 7;

unsigned char xPlayer1, xPlayer2, yPlayer1, yPlayer2, xOldPlayer1, xOldPlayer2, yOldPlayer1, yOldPlayer2, i, scorePlayer1, scorePlayer2, xBall, yBall, realBallX, realBallY;
char dbx, dby, bgBall = 32;
char key1;

unsigned char engineRunning = 1;

int multi40[200] = {0, 40, 80, 120, 160, 200, 240, 280, 320, 360, 400, 440, 480, 520, 560, 600, 640, 680, 720, 760, 800, 840, 880, 920, 960, 1000, 1040, 1080, 1120, 1160, 1200, 1240, 1280, 1320, 1360, 1400, 1440, 1480, 1520, 1560, 1600, 1640, 1680, 1720, 1760, 1800, 1840, 1880, 1920, 1960, 2000, 2040, 2080, 2120, 2160, 2200, 2240, 2280, 2320, 2360, 2400, 2440, 2480, 2520, 2560, 2600, 2640, 2680, 2720, 2760, 2800, 2840, 2880, 2920, 2960, 3000, 3040, 3080, 3120, 3160, 3200, 3240, 3280, 3320, 3360, 3400, 3440, 3480, 3520, 3560, 3600, 3640, 3680, 3720, 3760, 3800, 3840, 3880, 3920, 3960, 4000, 4040, 4080, 4120, 4160, 4200, 4240, 4280, 4320, 4360, 4400, 4440, 4480, 4520, 4560, 4600, 4640, 4680, 4720, 4760, 4800, 4840, 4880, 4920, 4960, 5000, 5040, 5080, 5120, 5160, 5200, 5240, 5280, 5320, 5360, 5400, 5440, 5480, 5520, 5560, 5600, 5640, 5680, 5720, 5760, 5800, 5840, 5880, 5920, 5960, 6000, 6040, 6080, 6120, 6160, 6200, 6240, 6280, 6320, 6360, 6400, 6440, 6480, 6520, 6560, 6600, 6640, 6680, 6720, 6760, 6800, 6840, 6880, 6920, 6960, 7000, 7040, 7080, 7120, 7160, 7200, 7240, 7280, 7320, 7360, 7400, 7440, 7480, 7520, 7560, 7600, 7640, 7680, 7720, 7760, 7800, 7840, 7880, 7920, 7960};

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
unsigned char charset[] = {
		0,0,0,0,0,0,0,0,
	   8,8,8,8,8,0,8,0,
	   20,20,20,0,0,0,0,0,
	   20,20,62,20,62,20,20,0,
	   8,30,40,28,10,60,8,0,
	   48,50,4,8,16,38,6,0,
	   16,40,40,16,42,36,26,0,
	   8,8,8,0,0,0,0,0,
	   8,16,32,32,32,16,8,0,
	   8,4,2,2,2,4,8,0,
	   8,42,28,8,28,42,8,0,
	   0,8,8,62,8,8,0,0,
	   0,0,0,0,0,8,8,16,
	   0,0,0,62,0,0,0,0,
	   0,0,0,0,0,4,0,0,
	   0,2,4,8,16,32,0,0,
	   62,34,42,42,42,34,62,0,
	   8,8,8,8,8,8,8,0,
	   62,2,2,62,32,32,62,0,
	   62,2,2,30,2,2,62,0,
	   0,34,34,34,62,2,2,0,
	   0,62,32,62,2,2,62,0,
	   62,32,32,62,34,34,62,0,
	   62,2,2,2,2,2,2,0,
	   62,34,34,62,34,34,62,0,
	   62,34,34,62,2,2,62,0,
	   0,0,8,0,0,8,0,0,
	   0,0,8,0,0,8,8,16,
	   4,8,16,32,16,8,4,0,
	   0,0,62,0,62,0,0,0,
	   16,8,4,2,4,8,16,0,
	   28,34,4,8,8,0,8,0,
	   62,34,42,42,46,32,62,0,
	   62,34,34,62,34,34,34,0,
	   62,34,34,60,34,34,62,0,
	   62,34,32,32,32,34,62,0,
	   60,34,34,34,34,34,60,0,
	   62,32,32,62,32,32,62,0,
	   62,32,32,62,32,32,32,0,
	   62,32,32,46,34,34,62,0,
	   34,34,34,62,34,34,34,0,
	   8,8,8,8,8,8,8,0,
	   2,2,2,2,2,34,62,0,
	   34,34,34,62,36,36,36,0,
	   32,32,32,32,32,32,62,0,
	   62,42,42,42,42,42,42,0,
	   62,34,34,34,34,34,34,0,
	   62,34,34,34,34,34,62,0,
	   62,34,34,62,32,32,32,0,
	   62,34,34,34,42,36,58,0,
	   62,34,34,62,40,46,34,0,
	   62,32,32,62,2,2,62,0,
	   62,8,8,8,8,8,8,0,
	   34,34,34,34,34,34,62,0,
	   34,34,34,34,54,28,8,0,
	   34,34,34,42,42,42,62,0,
	   34,34,34,28,34,34,34,0,
	   34,34,34,62,8,8,8,0,
	   62,2,2,28,32,32,62,0,
	   30,16,16,16,16,16,30,0,
	   0,32,16,8,4,2,0,0,
	   60,4,4,4,4,4,60,0,
	   8,20,42,8,8,8,8,0,
	   14,16,16,16,60,16,62,0,
	   12,18,45,41,41,45,18,12,
	   0,0,62,2,62,34,62,0,
	   32,32,62,34,34,34,62,0,
	   0,0,62,32,32,32,62,0,
	   2,2,62,34,34,34,62,0,
	   0,0,62,34,62,32,62,0,
	   0,0,62,32,62,32,32,0,
	   0,0,62,34,34,62,2,62,
	   32,32,62,34,34,34,34,0,
	   8,0,8,8,8,8,8,0,
	   4,0,4,4,4,4,4,12,
	   32,32,62,34,62,40,46,0,
	   8,8,8,8,8,8,8,0,
	   0,0,62,42,42,42,42,0,
	   0,0,62,34,34,34,34,0,
	   0,0,62,34,34,34,62,0,
	   0,0,62,34,34,62,32,32,
	   0,0,62,34,34,62,2,2,
	   0,0,62,32,32,32,32,0,
	   0,0,62,32,62,2,62,0,
	   32,32,62,32,32,32,62,0,
	   0,0,34,34,34,34,62,0,
	   0,0,34,34,54,62,8,0,
	   0,0,34,34,42,42,62,0,
	   0,0,34,34,28,34,34,0,
	   0,0,34,34,34,62,2,62,
	   0,0,62,2,62,32,62,0,
	   14,24,24,48,24,24,14,0,
	   8,8,8,8,8,8,8,8,
	   56,12,12,6,12,12,56,0,
	   42,21,42,21,42,21,42,21,
	   63,63,63,63,63,63,63,63
};

unsigned char playSoundPong[] = {238,2,0,0,0,0,0,62,16,0,0,208,7,0};


unsigned char scoreFont[] = {63, 63, 63, 63, 63, 63, 63, 63};
unsigned char scoreFont2[] = {0,30,30,30,30,30,30,0};
unsigned char scoreFont3[] = {0,20,10,20,10,20,10,0};
unsigned char scoreFont4[] = {0,0,10,0,10,0,0,0};

unsigned char netFont[] = {8, 8, 8, 0, 0, 0, 0, 0};
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


	while (key1!='!')
	{
		init();
		title();
		get();

		cls2();
		init();
		get();
	
		engine();
	}

	cls2();
    poke(0x26A, CURSOR_END);
	poke(0x24e, 24);
    poke(0x24f, 4);
}

void font()
{
    memcpy((void *) (0xb500 ), charset, sizeof(charset));
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

        wait(5 - waitFactor);
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
    xOldPlayer1 = xPlayer1;
	yOldPlayer1 = yPlayer1;
			
    key1 = key();

    if (key1 == keyUp && yPlayer1 > 0) yPlayer1--;
    if (key1 == keyDown && yPlayer1 < 23) yPlayer1++;
	if (key1 == 'S') {sounds = 1-sounds;wait(10);key();}
	if (key1 == 'R') {wait(10);key();engineRunning = 0;}
    if (key1 == 'T')
    {
        boardType++;
        boardType = boardType > BOARD_TYPES ? 0 : boardType;
        board();
		wait(10);
		key();
    }
    if (key1 == 'C') changeColor();
    if (key1 == 'P') get();
    if (key1 == '!') engineRunning = 0;

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

	xOldPlayer2 = xPlayer2;
    yOldPlayer2 = yPlayer2;

    if (realBallX > 25 - scorePlayer1 / 5 && yPlayer2 + (STICK_HEIGHT / 2) > yBall / BALL_DELIMITER && yPlayer2 > 0) (yPlayer2--);

    if (realBallX > 25 - scorePlayer1 / 5 && yPlayer2 + (STICK_HEIGHT / 2) < yBall / BALL_DELIMITER && yPlayer2 < 23) (yPlayer2++);

    if (yOldPlayer2 != yPlayer2)
    {
        eraseStick(xOldPlayer2, yOldPlayer2);
        printStick(xPlayer2, yPlayer2);
    }
}

void changeColor()
{
	color++;
	if (color==8) color = 1;
	ink (color);
	poke(0xbb80,color);
	wait(10);
	key();
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
			
		case 2:
            memcpy((void *) (0xb400 + CHAR_SCORE * 8), scoreFont2, 8);
            break;
			
		case 3:
            memcpy((void *) (0xb400 + CHAR_SCORE * 8), scoreFont3, 8);
            break;
			
		case 4:
            memcpy((void *) (0xb400 + CHAR_SCORE * 8), scoreFont4, 8);
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

    if ((realBallX - 1 == xPlayer1 || realBallX  == xPlayer1) && realBallY >= yPlayer1 && realBallY < yPlayer1 + STICK_HEIGHT)
    {
        tmp = (realBallY - yPlayer1)-(STICK_HEIGHT / 2);
        dbx = (rand() % BALL_DELIMITER / 2 + 3);
        dby = tmp == 0 ? dby : tmp;
		playSound(1);
    }

    if (realBallX < 1)
    {
		playSound(3);
        dbx = 3;
        xBall += 3;
        scorePlayer2++;
        printScore();
    }

    if (realBallX + 1 == xPlayer2 && realBallY >= yPlayer2 && realBallY < yPlayer2 + STICK_HEIGHT)
    {
        dbx = -(rand() % BALL_DELIMITER / 2 + 3);
		tmp = (realBallY - yPlayer2)-(STICK_HEIGHT / 2);
		dby = tmp == 0 ? dby : tmp;
		playSound(1);
    }

    if (realBallX > 38)
    {
		playSound(3);
        dbx = -3;
        xBall -= 3;
        scorePlayer1++;
        printScore();
		waitFactor = scorePlayer1 / 20;
    }

    if (realBallY < 1) {dby = -dby;		playSound(2);}
    if (realBallY > 26) {dby = -dby;	playSound(2);}

	// print bg
    poke(0xbb80 + realBallX + (multi40[realBallY]), bgBall);

    xBall = xBall + dbx;
    yBall = yBall + dby;

    realBallX = xBall / BALL_DELIMITER;
    realBallY = yBall / BALL_DELIMITER;

    modBall();
	
	// get bg
	bgBall = peek(0xbb80 + realBallX + (multi40[realBallY]));
	
	// print ball
    poke(0xbb80 + realBallX + (multi40[realBallY]), CHAR_BALL);

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

void playSound(unsigned char type)
{
	if (!sounds) return;
	
	switch (type){
		case 1: kbdclick2(); break;
		case 2: kbdclick2(); break;
		case 3: pong(); break;
		
	}
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
    printf("                               `      ");
    printf("                                      ");
    printf("                                      ");
    printf("    _____  _____  _   _  _____        ");
    printf("    _   _  _   _  __  _  _            ");
    printf("    _____  _   _  _ _ _  _ ___        ");
    printf("    _      _   _  _  __  _   _        ");
    printf("    _      _____  _   _  _____        ");
    printf("                                      ");
    printf("      Keys:         P - Pause         ");
    printf("                    T - Score type    ");
    printf("      A - Up        S - Sounds On/Off ");
    printf("      Z - Down      R - Restart       ");
    printf("                    C - Color         ");
    printf("                    ! - Exit          ");
	printf("                                      ");
    printf("                  \033L Press any key!    ");
    printf("                                      ");


    init();
}
