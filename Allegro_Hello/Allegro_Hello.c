#pragma warning (disable:4996)
#include <errno.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
//#define _CRT_SECURE_NO_WARNINGS

#include <allegro5/allegro.h>

#include <allegro5/allegro_font.h>

#include <allegro5/allegro_primitives.h>

#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_native_dialog.h> //dodajemy wszystkie potrzebne biblioteki do korzystania z allegro

double wynik = 0;

enum move { left, right, down, up, none };

enum game_status{play, ranking};


struct color
{
    int value;
    ALLEGRO_COLOR color;
};


typedef struct gameScore //Struktura wyniku gry
{
    int wynik;
    int gameTimeMin;
    int gameTimeSec;
};


struct button //struktura przycisku
{
    int x1;
    int y1;
    int x2;
    int y2;
    ALLEGRO_COLOR color;
};



void must_init(bool test, const char* description)
{
    if (test) return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

void fill(int t[4][4]) //tworzenie tablicy
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            t[i][j] = 0;
        }
    }

}


void print(int t[4][4])  //wypisz tablice
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%d  ", t[i][j]);
        }
        printf("\n");

    }printf("\n");
}

void random_2(int t[4][4]) //losuje 2 wspolrzedne i wstawia w nie '2'
{
    srand(time(0));
    int r1 = 0;
    int r2 = 0;
    int r3 = 0;
    int r4 = 0;

    r1 = rand() % 4;
    r2 = rand() % 4;
    r3 = rand() % 4;
    r4 = rand() % 4;

    while (t[r1][r2] != 0) //wczesniej wylosowaly sie te same wspolrzedne wiec losujemy kolejne dopoki nie beda rozne
    {
        r1 = rand() % 4;
        r2 = rand() % 4;
    }

    while (t[r3][r4] != 0) //wczesniej wylosowaly sie te same wspolrzedne wiec losujemy kolejne dopoki nie beda rozne
    {
        r3 = rand() % 4;
        r4 = rand() % 4;
    }







    while ((r1 == r3) && (r2 == r4)) //wczesniej wylosowaly sie te same wspolrzedne wiec losujemy kolejne dopoki nie beda rozne
    {
        r3 = rand() % 4;
        r4 = rand() % 4;
    }


    t[r1][r2] = 2;
    t[r3][r4] = 2;



}




void random_1(int t[4][4]) //losuje 2 wspolrzedne i wstawia w nie '2'
{
    srand(time(0));
    int r1 = 0;
    int r2 = 0;

    r1 = rand() % 4;
    r2 = rand() % 4;

    while (t[r1][r2] != 0) //wczesniej wylosowaly sie te same wspolrzedne wiec losujemy kolejne dopoki nie beda rozne
    {
        r1 = rand() % 4;
        r2 = rand() % 4;
    }

    t[r1][r2] = 2;

}



void compress(int t[4][4], bool* changed)
{
    int tempTab[4][4] =
    { 0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    0,0,0,0 };

    for (int i = 0; i < 4; i++)
    {
        int pos = 0;
        for (int j = 0; j < 4; j++)
        {
            if (t[i][j] != 0)
            {
                tempTab[i][pos] = t[i][j];
                pos += 1;
                //printf("test");
                //print(tempTab);
            }
        }
    }
    //printf("test 2\n");
    //print(tempTab);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (t[i][j] != tempTab[i][j])
            {
                t[i][j] = tempTab[i][j];
                *changed = true;
            }

        }
    }


    //printf("test 2.1\n");

    //print(t);


}


int merge(int t[4][4], bool* changed, int* localScore)
{
    int wynik2 = 0;
    int tempTab[4][4] = { 0,0,0,0,
                        0,0,0,0,
                        0,0,0,0,
                        0,0,0,0 };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {

            if (t[i][j] == t[i][j + 1] && t[i][j] != 0) {
                *localScore += t[i][j];
                t[i][j] += t[i][j];
                t[i][j + 1] = 0;
                *changed = true;
            }

        }
    }


}

void transpose(int t[4][4])
{
    int tempTab[4][4] = { 0,0,0,0,
                        0,0,0,0,
                        0,0,0,0,
                        0,0,0,0 };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {

            tempTab[i][j] = t[j][i];


        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            t[i][j] = tempTab[i][j];
        }
    }

}


void reverse(int t[4][4])
{
    int tempTab[4][4] = { 0,0,0,0,
                        0,0,0,0,
                        0,0,0,0,
                        0,0,0,0 };

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tempTab[i][j] = t[i][3 - j];
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            t[i][j] = tempTab[i][j];
        }
    }
}




bool left2(int t[4][4], int* localScore)
{
    bool changed = false;

    // printf("Lmain test 2.1\n");
    // print(t);
    compress(t, &changed);
    //printf("Lmain test 2.2\n");
   // print(t);
    merge(t, &changed, *&localScore);

    // printf("Lmain test 2.3\n");
    // print(t);
    compress(t, &changed);
    // printf("Lmain test 2.4\n");
    // print(t);
    if (changed == true) {
        //random_1(t);
        return true;
    }
    return false;
}



bool right2(int t[4][4], int* localScore)
{
    bool changed = false;

    reverse(t);
    //printf("Rmain test 2.1\n");
    //print(t);
    compress(t, &changed);
    // printf("Rmain test 2.2\n");
     //print(t);
    merge(t, &changed, *&localScore);

    //printf("Rmain test 2.3\n");
    //print(t);
    compress(t, &changed);
    //printf("Rmain test 2.4\n");
    //print(t);
    reverse(t);
    if (changed == true) {
        //random_1(t);
        return true;
    }
    return false;
}




bool down2(int t[4][4], int* localScore)
{
    bool changed = false;

    transpose(t);
    //printf("main test transpose\n");
    //print(t);
    reverse(t);
    // printf("main test reverse\n");
     //print(t);
    compress(t, &changed);
    // printf("main test compress\n");
    // print(t);
    merge(t, &changed, *&localScore);

    // printf("main test merge\n");
    // print(t);

    compress(t, &changed);
    // printf("main test compress\n");
     //print(t);
     //printf("main test 2.4\n");
     //print(t);
    reverse(t);
    transpose(t);
    //printf("changed? %d", changed);
    if (changed == true) {
        //random_1(t);
        return true;
    }
    return false;


}

bool up2(int t[4][4], int* localScore)
{
    bool changed = false;

    transpose(t);
    //printf("Umain test 2.1\n");
    //print(t);
    compress(t, &changed);
    //printf("Umain test 2.2\n");
    //print(t);
    merge(t, &changed, *&localScore);

    // printf("Umain test 2.3\n");
     //print(t);
    compress(t, &changed);
    // printf("Umain test 2.4\n");
     //print(t);
    transpose(t);
    if (changed == true) {
        //random_1(t);
        return true;
    }
    return false;
}

bool isMoveValid(bool** operation(int*))
{
    if (*operation == true)
        return true;
    return false;

}


void move(int t[4][4], bool** operation(int*, int*))
{
    int score = 0;
    if (operation(t, &score) == true) {
        random_1(t);
        wynik += score;

    }


}

void resetBoard(int t[4][4], struct gameScore *score)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            t[i][j] = 0;
        }
    }
    score->gameTimeMin = 0;
    score->gameTimeSec = 0;
    score->wynik = 0;
    wynik = 0;
    random_1(t);
    random_1(t);
}

bool wygrana(int t[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (t[i][j] == 2048)
                return true;

        }
    }
    return false;


}



bool isGameLost(int t[4][4])
{
    int tempTab[4][4] = { 0,0,0,0,
                        0,0,0,0,
                        0,0,0,0,
                        0,0,0,0 };
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tempTab[i][j] = t[i][j];
        }
    }
    //puts("\\\n  test  \\\\n");
    int wynik2 = 0;
    if (isMoveValid(right2(tempTab, &wynik2)) == false) {
        if (isMoveValid(left2(tempTab, &wynik2)) == false) {
            if (isMoveValid(up2(tempTab, &wynik2)) == false) {
                if (isMoveValid(down2(tempTab, wynik2)) == false) {
                    return true;

                }
            }
        }
    }
    return false;

}


void writeFile(struct gameScore gameScoreArray[10])
{
    FILE* fp;
    errno_t err;
    int localScore = 0, localGameTimeSec = 0, localGameTimeMin = 0;
    err = fopen_s(&fp, "Ranking.txt", "w+");
    if (err != 0)
    {
        printf("The file 'Ranking.txt' was not opened");
        return;

    }

    if (fp == NULL)
    {
        printf("The pointer 'fp' doesnt exist");
        return;

    }
    for (int i = 0; i < 10; i++)
    {
        fprintf_s(fp, "SCORE: %d\t TIMER: %d min %d sec\n", gameScoreArray[i].wynik, gameScoreArray[i].gameTimeMin, gameScoreArray[i].gameTimeSec);
    }
    fclose(fp);


}


void readeFile(struct gameScore gameScoreArray[10])
{
    FILE* fp;
    errno_t err;
    int localScore = 0, localGameTimeSec = 0, localGameTimeMin = 0;
    err = fopen_s(&fp, "Ranking.txt", "r");
    if (err != 0)
    {
        printf("The file 'Ranking.txt' was not opened");
        return;

    }

    if (fp == NULL)
    {
        printf("The pointer 'fp' doesnt exist");
        return;

    }
    for (int i = 0; i < 10; i++)
    {
        fscanf_s(fp, "SCORE: %d\t TIMER: %d min %d sec\n", &gameScoreArray[i].wynik, &gameScoreArray[i].gameTimeMin, &gameScoreArray[i].gameTimeSec);
    }
    fclose(fp);


}

void sortRankingArray(struct gameScore gameScoreArray[10])
{


    for (int i = 0; i < 9; i++)
    {
        int min = i;
        for (int j = i + 1; j < 10; j++)
        {
            if (gameScoreArray[j].wynik < gameScoreArray[min].wynik)
            {
                min = j;
            }
        }
        if (min != i)
        {
            struct gameScore temp;
            temp = gameScoreArray[min];
            gameScoreArray[min] = gameScoreArray[i];
            gameScoreArray[i] = temp;
        }
    }



}

void updateRankingArray(struct gameScore gameScoreArray[10], struct gameScore localScore)
{
    struct gameScore temp = { 0,0,0 };
    for (int i = 0; i < 10; i++)
    {
        if (localScore.wynik > gameScoreArray[i].wynik)
        {
            printf("i: %d wynik localScore %d", i, gameScoreArray[i].wynik);

            puts("1");
            temp = gameScoreArray[i];
            gameScoreArray[i] = localScore;
            localScore = temp;
            printf("i: %d wynik localScore %d", i, localScore.wynik);
        }
        else if (localScore.wynik == gameScoreArray[i].wynik)
        {
            puts("2");

            if (localScore.gameTimeMin < gameScoreArray[i].gameTimeMin)
            {
                puts("3");

                temp = gameScoreArray[i];
                gameScoreArray[i] = localScore;
                localScore = temp;
            }
            else if (localScore.gameTimeMin == gameScoreArray[i].gameTimeMin && localScore.gameTimeSec < gameScoreArray[i].gameTimeSec)
            {
                puts("4");

                temp = gameScoreArray[i];
                gameScoreArray[i] = localScore;
                localScore = temp;
            }

        }
    }
}


void resetRanking(struct gameScore gameScoreArray[10])
{
    for (int i = 0; i < 10; i++)
    {
        gameScoreArray[i].wynik = 0;
        gameScoreArray[i].gameTimeMin = 0;
        gameScoreArray[i].gameTimeSec = 0;
    }

    writeFile(gameScoreArray);
}


int BothPointsInRect(int rect_x1, int rect_y1, int rect_x2, int rect_y2, int p1x, int p1y,int p2x, int p2y )
{
    printf("\nRECTANGLE: X1: %d X2: %d, Y1: %d Y2 %d\n", rect_x1, rect_x2, rect_y1, rect_y2);
    if (p1x >= rect_x1 && p1x <= rect_x2 && p1y >= rect_y1 && p1y <= rect_y2&& p2x >= rect_x1 && p2x <= rect_x2 && p2y >= rect_y1 && p2y <= rect_y2)
        return 1;
    else
        return 0;
}
int StartingPointsInRect(int rect_x1, int rect_y1, int rect_x2, int rect_y2, int p1x, int p1y)
{
    printf("\nRECTANGLE: X1: %d X2: %d, Y1: %d Y2 %d\n", rect_x1, rect_x2, rect_y1, rect_y2);
    if (p1x >= rect_x1 && p1x <= rect_x2 && p1y >= rect_y1 && p1y <= rect_y2 )
        return 1;
    else
        return 0;
}






ALLEGRO_COLOR getColor(int value)
{
    switch (value)
    {
    case 2:
        return al_map_rgb(238, 228, 218);
    case 4:
        return al_map_rgb(238, 225, 201);
    case 8:
        return al_map_rgb(243, 178, 122);
    case 16:
        return al_map_rgb(246, 150, 100);
    case 32:
        return al_map_rgb(247, 124, 95);
    case 64:
        return al_map_rgb(246, 93, 59);
    case 128:
        return al_map_rgb(238, 206, 113);
    case 256:
        return al_map_rgb(237, 204, 100);
    case 512:
        return al_map_rgb(236, 200, 79);
    case 1024:
        return al_map_rgb(236, 195, 62);
    case 2048:
        return al_map_rgb(236, 194, 44);

    default:
        return al_map_rgb(205, 193, 180);
    }
}



void drawGameBoard(ALLEGRO_DISPLAY* display, ALLEGRO_MONITOR_INFO info, ALLEGRO_FONT* font, int t[4][4], struct gameScore localScore, struct button resetButton)
{
    al_get_monitor_info(0, &info);
    int res_x_comp = info.x2 - info.x1;
    int res_y_comp = info.y2 - info.y1;
    float game_height = (float)(res_y_comp / 2);
    float game_width = (float)(res_x_comp / 4);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            al_draw_filled_rectangle(j * game_width / 4, i * game_width / 4, (j + 1) * game_width / 4, (i + 1) * game_width / 4, getColor(t[i][j]));
        }
    }
    al_draw_line(3, 0, 3, game_width, al_map_rgb(0, 0, 0), 4); //rysujemy ramke
    al_draw_line(game_width / 4, 0, game_width / 4, game_width, al_map_rgb(0, 0, 0), 3);
    al_draw_line(game_width / 2, 0, game_width / 2, game_width, al_map_rgb(0, 0, 0), 3);
    al_draw_line((game_width * 3 / 4), 0, game_width * 3 / 4, game_width, al_map_rgb(0, 0, 0), 3);
    al_draw_line(game_width - 3, 0, game_width - 3, game_width, al_map_rgb(0, 0, 0), 4);




    al_draw_line(3, 0, game_width - 3, 0, al_map_rgb(0, 0, 0), 6); //rysujemy ramke
    al_draw_line(3, game_width / 4, game_width - 3, game_width / 4, al_map_rgb(0, 0, 0), 3); //rysujemy ramke
    al_draw_line(3, game_width * 3 / 4, game_width - 3, game_width * 3 / 4, al_map_rgb(0, 0, 0), 3); //rysujemy ramke
    al_draw_line(3, game_width / 2, game_width - 3, game_width / 2, al_map_rgb(0, 0, 0), 3); //rysujemy ramke
    al_draw_line(3, game_width, game_width - 3, game_width, al_map_rgb(0, 0, 0), 3); //rysujemy ramke

    

    al_draw_text(font, al_map_rgb(0, 0, 0), 2, game_width + game_height / 20, 0, "WYNIK:"); //wyswietla napis 'WYNIK'
                //printf("Actual Time: %d min: %d sec",minutesPassed, secondsPassed);
    al_draw_text(font, al_map_rgb(0, 0, 0), 2, game_width + game_height / 12, 0, "TIMER:"); //wyswietla napis 'TIMER'




    al_draw_textf(font, al_map_rgb(0, 0, 0), 140, game_width + game_height / 20, 0, "%d", localScore.wynik); //wyswietla wartość wyniku
    al_draw_textf(font, al_map_rgb(0, 0, 0), 140, game_width + game_height / 12, 0, "%d min %d sec", localScore.gameTimeMin, localScore.gameTimeSec); //wyswietla aktualny czas gry


   // al_draw_filled_rectangle(280, 20, 350, 80, al_map_rgb(0, 0, 0));
    if (t[0][0] != 0) al_draw_textf(font, al_map_rgb(0, 0, 0), game_width / 8, game_width / 8, 0, "%d", t[0][0]); //wyswietla wartosci tablicy 
    if (t[0][1] != 0)al_draw_textf(font, al_map_rgb(0, 0, 0), game_width * 3 / 8, game_width / 8, 0, "%d", t[0][1]);
    if (t[0][2] != 0) al_draw_textf(font, al_map_rgb(0, 0, 0), game_width * 5 / 8, game_width / 8, 0, "%d", t[0][2]);
    if (t[0][3] != 0)al_draw_textf(font, al_map_rgb(0, 0, 0), game_width * 7 / 8, game_width / 8, 0, "%d", t[0][3]);

    if (t[1][0] != 0)al_draw_textf(font, al_map_rgb(0, 0, 0), game_width / 8, game_width * 3 / 8, 0, "%d", t[1][0]);
    if (t[1][1] != 0)al_draw_textf(font, al_map_rgb(0, 0, 0), game_width * 3 / 8, game_width * 3 / 8, 0, "%d", t[1][1]);
    if (t[1][2] != 0)al_draw_textf(font, al_map_rgb(0, 0, 0), game_width * 5 / 8, game_width * 3 / 8, 0, "%d", t[1][2]);
    if (t[1][3] != 0)al_draw_textf(font, al_map_rgb(0, 0, 0), game_width * 7 / 8, game_width * 3 / 8, 0, "%d", t[1][3]);

    if (t[2][0] != 0)al_draw_textf(font, al_map_rgb(0, 0, 0), game_width / 8, game_width * 5 / 8, 0, "%d", t[2][0]);
    if (t[2][1] != 0)al_draw_textf(font, al_map_rgb(0, 0, 0), game_width * 3 / 8, game_width * 5 / 8, 0, "%d", t[2][1]);
    if (t[2][2] != 0)al_draw_textf(font, al_map_rgb(0, 0, 0), game_width * 5 / 8, game_width * 5 / 8, 0, "%d", t[2][2]);
    if (t[2][3] != 0) al_draw_textf(font, al_map_rgb(0, 0, 0), game_width * 7 / 8, game_width * 5 / 8, 0, "%d", t[2][3]);

    if (t[3][0] != 0)al_draw_textf(font, al_map_rgb(0, 0, 0), game_width / 8, game_width * 7 / 8, 0, "%d", t[3][0]);
    if (t[3][1] != 0)al_draw_textf(font, al_map_rgb(0, 0, 0), game_width * 3 / 8, game_width * 7 / 8, 0, "%d", t[3][1]);
    if (t[3][2] != 0)al_draw_textf(font, al_map_rgb(0, 0, 0), game_width * 5 / 8, game_width * 7 / 8, 0, "%d", t[3][2]);
    if (t[3][3] != 0) al_draw_textf(font, al_map_rgb(0, 0, 0), game_width * 7 / 8, game_width * 7 / 8, 0, "%d", t[3][3]);

    al_draw_filled_rectangle(game_width * 3 / 4, game_width + game_height / 40, game_width * 3 / 4 + game_width * 1 / 5, game_height - game_height / 40, resetButton.color);
    al_draw_text(font, al_map_rgb(0, 0, 0), (game_width * 3 / 4 + game_width * 3 / 4 + game_width * 1 / 5) / 2, (game_width + game_height / 80 + game_height - game_height / 40) / 2, ALLEGRO_ALIGN_CENTER, "RESET");

}









int main()
{
    int t[4][4];

    fill(t);
    random_2(t);
    bool first_redraw_ranking = true;
    bool first_redraw_game = true;
    // print(t);


    bool redraw = true;

    int first_pos_x = 0;
    int first_pos_y = 0;



    if (!al_init()) //inicjalizujemy biblioteke allegro
    {
        fprintf(stderr, "Failed to initialize allegro!\n");
        return -1;
    }

    al_init_font_addon(); //inicjalizujemy czcionki 
    al_init_ttf_addon(); //inicjalizujemy czcionki true type 
    int timePassed = 0;
    int secondsPassed = 0;
    int minutesPassed = 0;


    struct gameScore gameScores[10];
    readeFile(gameScores);
    struct gameScore localScore = { 0,0,0 };

    writeFile(gameScores);

    ALLEGRO_TIMER* timer = al_create_timer(1.0);
    //must_init(timer, "timer");

    al_start_timer(timer);

    printf(" seconds passed : %d", secondsPassed);
    bool done = false;

    bool changeRankingFile = true;

    int res_x_comp = 0;
    int res_y_comp = 0;
    ALLEGRO_DISPLAY* display = NULL; //wskaznik do okna
    ALLEGRO_DISPLAY* finishDisplay = NULL; //wskaznik do okna konca gry
    ALLEGRO_FONT* fontWYNIK = al_create_builtin_font(); //wskaznik do czcionki 'WYNIK'
    ALLEGRO_FONT* fontWART_WYNIK = al_create_builtin_font();  //wskaznik do czcionki 'WARTOSC WYNIKU'
    ALLEGRO_FONT* score_board_font = al_create_builtin_font();  //wskaznik do czcionki 'WARTOSC WYNIKU'
    ALLEGRO_MONITOR_INFO info;
    al_get_monitor_info(0, &info);
    res_x_comp = info.x2 - info.x1;
    res_y_comp = info.y2 - info.y1;
    float game_height = (float)(res_y_comp / 2);
    float game_width = (float)(res_x_comp / 4);
    printf("resolution %d %d", res_x_comp, res_y_comp);


    ALLEGRO_FONT* F1 = al_create_builtin_font(); //wskaznik do czcionki pierwszego elementu tablicy
    ALLEGRO_FONT* F2 = al_create_builtin_font();
    ALLEGRO_FONT* F3 = al_create_builtin_font();
    ALLEGRO_FONT* F4 = al_create_builtin_font();
    ALLEGRO_FONT* F5 = al_create_builtin_font();
    ALLEGRO_FONT* F6 = al_create_builtin_font();
    ALLEGRO_FONT* F7 = al_create_builtin_font();
    ALLEGRO_FONT* F8 = al_create_builtin_font();
    ALLEGRO_FONT* F9 = al_create_builtin_font();
    ALLEGRO_FONT* F10 = al_create_builtin_font();
    ALLEGRO_FONT* F11 = al_create_builtin_font();
    ALLEGRO_FONT* F12 = al_create_builtin_font();
    ALLEGRO_FONT* F13 = al_create_builtin_font();
    ALLEGRO_FONT* F14 = al_create_builtin_font();
    ALLEGRO_FONT* F15 = al_create_builtin_font();
    ALLEGRO_FONT* F16 = al_create_builtin_font();



    if (!al_init_primitives_addon()) //inicjalizujemy rysowanie ksztaltow
    {
        fprintf(stderr, "Couldn't initialize primitives addon!\n");
        return -1;
    }

    al_install_keyboard();


    //ALLEGRO_KEYBOARD_STATE klawiatura;



    display = al_create_display(game_width, game_height); //tworzymy okno
    if (!display)
    {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }

    must_init(al_install_keyboard(), "keyboard");
    must_init(al_install_mouse(), "mouse");

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    //ALLEGRO_EVENT_QUEUE* event_display_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());
    // timePassed = (int)al_get_timer_count(timer);
    int actualTime = al_current_time(timer);
    int pos_x = 0, pos_y = 0;

    enum game_status GAME_MODE = play;
    struct button resetGameboard;
    resetGameboard.x1 = (int)(game_width * 3 / 4);
    resetGameboard.y1 = (int)(game_width + game_height / 40);
    resetGameboard.x2 = (int)(game_width * 3 / 4 + game_width * 1 / 5);
    resetGameboard.y2 = (int)(game_height - game_height / 40);
    resetGameboard.color = getColor(2);

    struct button resetScoreboard;

    resetScoreboard.x1 = (int)(game_width * 3 / 4);
    resetScoreboard.y1 = (int)(game_width + game_height / 40);
    resetScoreboard.x2 = (int)(game_width * 3 / 4 + game_width * 1 / 5);
    resetScoreboard.y2 = (int)(game_height - game_height / 40 + 15);
    resetScoreboard.color = getColor(2);
    

    while (!done)
    {

        enum move key = none;

        //printf("Actual Time: %d min: %d sec",minutesPassed, secondsPassed);
        ALLEGRO_EVENT events;
        // ALLEGRO_EVENT events2;
        al_wait_for_event(event_queue, &events);
       
        //redraw = true;

        if (GAME_MODE == play)


        {
            

            

            
           
            bool changeTime = false;
            if (actualTime != (int)al_current_time(timer)) {
                actualTime = (int)al_current_time(timer);
                changeTime = true;
            }

            if (changeTime == true) {
                timePassed += 1;
                redraw = true;
                //printf("%d", timePassed % 60);
                if ((int)timePassed % 60 == 0)
                {


                    localScore.gameTimeMin += 1;

                    localScore.gameTimeSec = 0;

                }

                else
                {

                    localScore.gameTimeSec += 1;
                }
            }
            if (events.type == ALLEGRO_EVENT_MOUSE_AXES)
            {
                pos_x = events.mouse.x;
                pos_y = events.mouse.y;

                //printf("POSITION: x:%d  y:%d  \n", pos_x, pos_y);
                // if (events2.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
                     //puts("1");
                  //al_draw_filled_rectangle(game_width * 3 / 4, game_width + game_height / 40, game_width * 3 / 4 + game_width * 1 / 5, game_height - game_height / 40, getColor(2));
                  //al_draw_text(fontWYNIK, al_map_rgb(0, 0, 0), (game_width * 3 / 4 + game_width * 3 / 4 + game_width * 1 / 5) / 2, (game_width + game_height / 80 + game_height - game_height / 40) / 2, ALLEGRO_ALIGN_CENTER, "RBBBBB");
                  //al_flip_display();
               // al_flush_event_queue(event_queue); //against buffer overload

            }
            else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                redraw = true;
                //change = true;
                //printf("\nCLICK DOWN  X:%d Y:%d ", pos_x, pos_y);
                if (events.mouse.button & 1)
                {
                    first_pos_x = pos_x;
                     first_pos_y = pos_y;
                     if (StartingPointsInRect(resetGameboard.x1, resetGameboard.y1, resetGameboard.x2, resetGameboard.y2, first_pos_x, first_pos_y) == 1)
                        resetGameboard.color = getColor(4);
                    printf("\nCLICK DOWN  X:%d Y:%d ", first_pos_x, first_pos_y);
                   // puts("1");
                   
                    
                        
                }
                     puts("1");
                /*
                 if (events2.mouse.button & 1)
                 {
                     puts("2");

                     int pos_x_first = events2.mouse.x;
                     int pos_y_first =events2.mouse.y;
                     //printf("First x:%f First y:%f  ", pos_x_first, pos_y_first);


                     printf("First x:%d First y:%d  ", pos_x_first, pos_y_first);
                     if (BothPointsInRect(game_width * 3 / 4, game_width + game_height / 40, game_width * 3 / 4 + game_width * 1 / 5, game_height - game_height / 40, pos_x_first, pos_y_first)==1);
                         puts("damn it works");






                 //}
                 */

             }
            else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                redraw = true;
                //change = true;
                //printf("\nCLICK UP X:%d Y:%d ", pos_x, pos_y);
                if (events.mouse.button & 1)
                {
                    resetGameboard.color = getColor(2);
                    int second_pos_x = pos_x;
                    int second_pos_y = pos_y;
                    printf("\nCLICK UP  X:%d Y:%d ", second_pos_x, second_pos_y);

                    if (BothPointsInRect(resetGameboard.x1, resetGameboard.y1, resetGameboard.x2, resetGameboard.y2, first_pos_x, first_pos_y, second_pos_x, second_pos_y) == 1)
                    {

                        puts("\ndamn it works\n");
                        resetBoard(t, &localScore);
                    }

                }
            }

            if (events.type == ALLEGRO_EVENT_KEY_DOWN)
            {

                switch (events.keyboard.keycode)
                {
                case ALLEGRO_KEY_DOWN:
                    key = down;
                    redraw = true;

                    // move(t,down2);

                    break;
                case ALLEGRO_KEY_UP:
                    key = up;
                    redraw = true;

                    // move(t, up2);

                    break;
                case ALLEGRO_KEY_RIGHT:
                    key = right;
                    redraw = true;

                    //move(t, right2);

                    break;
                case ALLEGRO_KEY_LEFT:
                    key = left;
                    //move(t, left2);
                    redraw = true;
                    break;
                case ALLEGRO_KEY_ESCAPE:
                    
                    //saveScoreBoard(wynik, minutesPassed, secondsPassed);

                   
                    printf("SCORE %d TIME %d %d ", localScore.wynik, localScore.gameTimeMin, localScore.gameTimeSec);



                    al_clear_to_color(getColor(0));
                    al_draw_text(score_board_font, al_map_rgb_f(0, 0, 0), game_width / 2, game_height / 2, ALLEGRO_ALIGN_CENTER, "G A M E  O V E R");
                    printf("SCORE %d TIME %d %d ", localScore.wynik, localScore.gameTimeMin, localScore.gameTimeSec);

                    al_draw_textf(score_board_font, al_map_rgb_f(0, 0, 0), game_width / 2, game_height / 2 + game_height / 20, ALLEGRO_ALIGN_CENTER, "SCORE: %d TIMER: %d min %.2d sec", localScore.wynik, localScore.gameTimeMin, localScore.gameTimeSec);
                    al_flip_display();
                    updateRankingArray(gameScores, localScore);
                    writeFile(gameScores);
                    redraw = false;
                    al_rest(3.0);
                    al_clear_to_color(getColor(0));

                    GAME_MODE = ranking;
                    //redraw = true;



                    
                    break;

                default:

                    break;
                }

            }
            else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                done = true;
                redraw = false;

                break;
            }
            if (redraw == true || first_redraw_game == true)

            {
                redraw = false;
                first_redraw_game = false;

                if (key == left)
                    move(t, left2);
                else if (key == right)
                    move(t, right2);

                else if (key == down)
                    move(t, down2);
                else if (key == up)
                    move(t, up2);
                localScore.wynik = wynik;
                drawGameBoard(display, info, fontWYNIK, t, localScore, resetGameboard);

                if (key == up || key == down || key == right || key == left)
                {
                    if (wygrana(t) == true)
                    {
                        //saveScoreBoard(wynik, minutesPassed, secondsPassed);
                        al_clear_to_color(al_map_rgb(213, 196, 161));

                        al_draw_text(score_board_font, al_map_rgb_f(0, 0, 0), game_width / 2, game_height / 2, ALLEGRO_ALIGN_CENTER, "Y O U  W O N");
                        printf("SCORE %d TIME %d %d ", localScore.wynik, localScore.gameTimeMin, localScore.gameTimeSec);

                        al_draw_textf(score_board_font, al_map_rgb_f(0, 0, 0), game_width / 2, game_height / 2 + game_height / 20, ALLEGRO_ALIGN_CENTER, "SCORE: %d TIMER: %d min %.2d sec", localScore.wynik, localScore.gameTimeMin, localScore.gameTimeSec);
                        al_flip_display();
                        updateRankingArray(gameScores, localScore);
                        writeFile(gameScores);

                        al_rest(3.0);
                        GAME_MODE = ranking;




                    }
                    if (isGameLost(t) == true)
                    {
                        //saveScoreBoard(wynik, minutesPassed, secondsPassed);
                        al_clear_to_color(al_map_rgb(213, 196, 161));

                        al_draw_text(score_board_font, al_map_rgb_f(0, 0, 0), game_width / 2, game_height / 2, ALLEGRO_ALIGN_CENTER, "G A M E  O V E R");
                        printf("SCORE %d TIME %d %d ", localScore.wynik, localScore.gameTimeMin, localScore.gameTimeSec);

                        al_draw_textf(score_board_font, al_map_rgb_f(0, 0, 0), game_width / 2, game_height / 2 + game_height / 20, ALLEGRO_ALIGN_CENTER, "SCORE: %d TIMER: %d min %.2d sec", localScore.wynik, localScore.gameTimeMin, localScore.gameTimeSec);
                        al_flip_display();
                        updateRankingArray(gameScores, localScore);
                        writeFile(gameScores);

                        al_rest(3.0);
                        GAME_MODE = ranking;





                    }



                }


               
                al_flip_display();
                al_clear_to_color(al_map_rgb(213, 196, 161));

                
            }
            


            
            /* al_draw_line(6, 0, 6, 406, al_map_rgb(0, 0, 0), 3); //rysujemy ramke
             al_draw_line(106, 0, 106, 406, al_map_rgb(0, 0, 0), 3);
             al_draw_line(206, 0, 206, 406, al_map_rgb(0, 0, 0), 3);
             al_draw_line(306, 0, 306, 406, al_map_rgb(0, 0, 0), 3);
             al_draw_line(406, 0, 406, 406, al_map_rgb(0, 0, 0), 3);
             */
           

            /*
            al_draw_line(6, 0, 406, 0, al_map_rgb(0, 0, 0), 3);
            al_draw_line(6, 106, 406, 106, al_map_rgb(0, 0, 0), 3);
            al_draw_line(6, 206, 406, 206, al_map_rgb(0, 0, 0), 3);
            al_draw_line(6, 306, 406, 306, al_map_rgb(0, 0, 0), 3);
            al_draw_line(6, 406, 406, 406, al_map_rgb(0, 0, 0), 3);
            */





           
            //print(t);








        }

        else if (GAME_MODE == ranking)
        {

           

              
        
            if (events.type == ALLEGRO_EVENT_MOUSE_AXES)
            {
                pos_x = events.mouse.x;
                pos_y = events.mouse.y;

               

            }
            
            


            else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
            {
                redraw = true;
                 

               
                if (events.mouse.button & 1)
                {
                    first_pos_x = pos_x;
                    first_pos_y = pos_y;
                    if (StartingPointsInRect(resetScoreboard.x1, resetScoreboard.y1, resetScoreboard.x2, resetScoreboard.y2, first_pos_x, first_pos_y) == 1)
                        resetScoreboard.color = getColor(4);




                }
               

            }
            else if (events.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                redraw = true;
                
                
                if (events.mouse.button & 1)
                {
                    resetScoreboard.color = getColor(2);

                    int second_pos_x = pos_x;
                    int second_pos_y = pos_y;
                   
                    printf("\nCLICK UP  X:%d Y:%d ", second_pos_x, second_pos_y);

                    if (BothPointsInRect(resetScoreboard.x1, resetScoreboard.y1, resetScoreboard.x2, resetScoreboard.y2, first_pos_x, first_pos_y, second_pos_x, second_pos_y) == 1)
                    {
                        resetRanking(gameScores);
                        writeFile(gameScores);
                        changeRankingFile = true;

                       
                    }

                }
            }
            if (events.type == ALLEGRO_EVENT_KEY_DOWN)
            {

                switch (events.keyboard.keycode)
                {
                case ALLEGRO_KEY_ESCAPE:
                    done = true;
                    break;
                case ALLEGRO_KEY_R:
                    resetRanking(gameScores);
                    writeFile(gameScores);
                    changeRankingFile = true;
                    redraw = true;
                    break;

                default:
                    break;


                }
            }
            else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                done = true;

            if (redraw == true||first_redraw_ranking==true)
            {
                redraw = false;
                first_redraw_ranking = false;
                if (changeRankingFile)
                {
                    readeFile(gameScores);
                    changeRankingFile = false;
                    
                }
                al_draw_textf(score_board_font, al_map_rgb(0, 0, 0), game_width / 2, 0, ALLEGRO_ALIGN_CENTER, "LEADERBOARD");

                for (int i = 0; i < 10; i++)
                    al_draw_textf(score_board_font, al_map_rgb(0, 0, 0), game_width / 2, (i + 1) * game_height / 10 - game_height / 20, ALLEGRO_ALIGN_CENTER, "SCORE: %d TIMER: %d min %.2d sec", gameScores[i].wynik, gameScores[i].gameTimeMin, gameScores[i].gameTimeSec);
                    
                
                al_draw_filled_rectangle(resetScoreboard.x1, resetScoreboard.y1, resetScoreboard.x2, resetScoreboard.y2,resetScoreboard.color);
                al_draw_text(F1, al_map_rgb(0, 0, 0), (resetScoreboard.x1 + resetScoreboard.x2) / 2, (resetScoreboard.y1 + resetScoreboard.y2) / 2-5, ALLEGRO_ALIGN_CENTER, "RESET");
                al_draw_text(F1, al_map_rgb(0, 0, 0), (resetScoreboard.x1 + resetScoreboard.x2) / 2, (resetScoreboard.y1 + resetScoreboard.y2) / 2+5, ALLEGRO_ALIGN_CENTER, "SCOREBOARD");

                al_flip_display();


                al_clear_to_color(al_map_rgb(213, 196, 161));


            }
             
        
        

        



        }

       
       
    }
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);


    return 0;

}

