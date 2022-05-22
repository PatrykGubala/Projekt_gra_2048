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

enum move{left, right, down, up, none};

struct color
{
    int value;
    ALLEGRO_COLOR color;
};


typedef struct gameScore
{
    int wynik;
    int gameTimeMin;
    int gameTimeSec;
};

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



void compress(int t[4][4], bool * changed )
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


int merge(int t[4][4], bool * changed,int *localScore )
{
    int wynik2 = 0;
    int tempTab[4][4] ={ 0,0,0,0,
                        0,0,0,0,
                        0,0,0,0,
                        0,0,0,0 };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {

            if (t[i][j] == t[i][j + 1] && t[i][j] != 0) {
                *localScore +=  t[i][j];
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




/*
void down(int t[4][4])
{
    for (int x = 0; x < 4; x++)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (t[i][j] != 0 && t[i + 1][j] == 0)
                {
                    t[i + 1][j] = t[i][j];
                    t[i][j] = 0;

                }
                if (t[i][j] != 0)
                {
                    if (t[i][j] == t[i + 1][j])
                    {
                        wynik = wynik + t[i][j];
                        t[i + 1][j] = t[i + 1][j] * 2;
                        t[i][j] = 0;


                    }
                }
            }
        }
    }


}
*/


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
   
    compress(t,&changed);
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

bool up2(int t[4][4], int * localScore)
{
    bool changed= false;
 
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


void move( int t[4][4],bool** operation(int *, int *))
{
    int score=0;
    if (operation(t, &score) == true) {
        random_1(t);
        wynik += score;

    }
        
       
}
/*
void up(int t[4][4])
{
    for (int x = 0; x < 4; x++)
    {
        for (int i = 3; i > 0; i--)
        {
            for (int j = 3; j >= 0; j--)
            {
                if (t[i][j] != 0 && t[i - 1][j] == 0)
                {
                    t[i - 1][j] = t[i][j];
                    t[i][j] = 0;

                }
                if (t[i][j] != 0)
                {
                    if (t[i][j] == t[i - 1][j])
                    {
                        wynik = wynik + t[i][j];
                        t[i - 1][j] = t[i - 1][j] * 2;
                        t[i][j] = 0;


                    }
                }
            }
        }
    }


}

*/
/*
void left(int t[4][4])
{
    for (int x = 0; x < 4; x++)
    {
        for (int i = 3; i >= 0; i--)
        {
            for (int j = 3; j > 0; j--)
            {
                if (t[i][j] != 0 && t[i][j - 1] == 0)
                {
                    t[i][j - 1] = t[i][j];
                    t[i][j] = 0;

                }
                if (t[i][j] != 0)
                {
                    if (t[i][j] == t[i][j - 1])
                    {
                        wynik = wynik + t[i][j];
                        t[i][j - 1] = t[i][j - 1] * 2;
                        t[i][j] = 0;


                    }
                }
            }
        }
    }


}



void right(int t[4][4])
{
    for (int x = 0; x < 4; x++)
    {
        for (int i = 0; i <= 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (t[i][j] != 0 && t[i][j + 1] == 0)
                {
                    t[i][j + 1] = t[i][j];
                    t[i][j] = 0;

                }
                if (t[i][j] != 0)
                {
                    if (t[i][j] == t[i][j + 1])
                    {
                        wynik = wynik + t[i][j];
                        t[i][j + 1] = t[i][j + 1] * 2;
                        t[i][j] = 0;



                    }
                }
            }
        }
    }


}

*/
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


bool przegrana(int t[4][4])
{
    int counter = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (t[i][j] != 0)
                counter++;

        }
    }
    if (counter == 16)
        return true;

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
            tempTab[i][j]= t[i][j] ;
        }
    }
    //puts("\\\n  test  \\\\n");
    int wynik2=0;
    if (isMoveValid(right2(tempTab,&wynik2)) == false) {
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
/*

void saveScoreBoard(int score, int gameTimeMin, int gameTimeSec)
{
    FILE* fp;
    errno_t err;
    int localScore = 0, localGameTimeSec = 0, localGameTimeMin = 0;
    err = fopen_s(&fp, "Ranking.txt", "w+");
    


    if (err!=0)
    {
        printf("The file 'Ranking.txt' was not opened");
        
    }
    
    else 
    {
        printf("The file 'Ranking.txt' was opened");

        if (fp)
            fseek(fp, 0L, SEEK_SET);
        printf("SCORE: %d\t TIMER: %d min %d sec\n", score, gameTimeMin, gameTimeSec);

        fprintf(fp, "SCORE: %d\t TIMER: %d min %d sec\n", 1, 11, 12);
        fprintf(fp, "SCORE: %d\t TIMER: %d min %d sec\n", 10, 11, 12);
        fprintf(fp, "SCORE: %d\t TIMER: %d min %d sec\n", 10, 11, 12);

        
        fseek(fp, 0L, SEEK_SET);
        /*while (!feof(fp))
        {  
           
           //fscanf_s(fp, "SCORE: %d\t TIMER: %d min %d sec\n", &localScore, &localGameTimeMin, &localGameTimeSec);
           fprintf(fp, "SCORE: %d\t TIMER: %d min %d sec\n", score, gameTimeMin, gameTimeSec);

            
           printf("SCORE: %d\t TIMER: %d min %d sec\n", localScore, localGameTimeMin, localGameTimeSec);
           //printf("Pointer %d\n", fp);
            if (score > localScore)
            {
                //fseek(fp, 0L, SEEK_CUR);
                //fprintf(fp, "SCORE: %d\t TIMER: %d min %d sec\n", score, gameTimeMin, gameTimeSec);

                //fscanf_s(fp, "SCORE: %d\t TIMER: %d min %d sec\n", &localScore, &localGameTimeMin, &localGameTimeSec);
                
                
                //printf("SCORE: %d\t TIMER: %d min %d sec\n", localScore, localGameTimeMin, localGameTimeSec);

            }

        }
        
        score = 15;
        gameTimeSec = 20;
        gameTimeMin = 15;
        for (int i = 0; i < 10; i++)
        {
            if (feof(fp)==0)
            {
                printf(" \nif 1 i: %d \n", i);
                fscanf_s(fp, "SCORE: %d\t TIMER: %d min %d sec\n", &localScore, &localGameTimeMin, &localGameTimeSec);
                printf("SCORE: %d\t TIMER: %d min %d sec\n", localScore, localGameTimeMin, localGameTimeSec);
                printf("GAME SCORE: %d\t GAME TIMER: %d min %d sec\n", score, gameTimeMin, gameTimeSec);

                if (score > localScore)
                {
                    printf(" \nif 2 i: %d \n", i);

                    fprintf(fp, "SCORE: %d\t TIMER: %d min %d sec\n", score, gameTimeMin, gameTimeSec);
                    score = localScore;
                    gameTimeMin = localGameTimeMin;
                    gameTimeSec = localGameTimeSec;
                }
                else
                {
                    printf(" \nel 2 i: %d \n", i);

                    fseek(fp, 0, SEEK_END);
                    fprintf(fp, "SCORE: %d\t TIMER: %d min %d sec\n", 0, 0, 0);
                }
                    //fprintf(fp, "SCORE: %d\t TIMER: %d min %d sec\n", localScore, localGameTimeMin, localGameTimeSec);
                    



            }
            else
            {
                printf(" \nel 1 i: %d \n", i);

                fseek(fp, 0, SEEK_END);
                fprintf(fp, "SCORE: 0\t TIMER: 0 min 0 sec\n");
            }
            //fprintf(fp, "SCORE: %d\t TIMER: %d min %d sec\n", score, gameTimeMin, gameTimeSec);
        }
       
    }
    if (fp)
      fclose(fp);
    



    

}


*/

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
        fprintf_s(fp,"SCORE: %d\t TIMER: %d min %d sec\n", gameScoreArray[i].wynik, gameScoreArray[i].gameTimeMin, gameScoreArray[i].gameTimeSec);
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
    

    for (int i = 0; i <9; i++)
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
    struct gameScore temp= {0,0,0};
    for (int i = 0; i < 10; i++)
    {
        if (localScore.wynik > gameScoreArray[i].wynik)
        {
            printf("i: %d wynik localScore %d", i, gameScoreArray[i].wynik);

            puts("1");
            temp = gameScoreArray[i];
            gameScoreArray[i] = localScore;
            localScore = temp;
            printf("i: %d wynik localScore %d", i , localScore.wynik);
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

int main()
{
    int t[4][4];

    fill(t);
    random_2(t);
   // print(t);





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
    float game_width =(float)(res_x_comp / 4);
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

    al_install_keyboard();

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    //ALLEGRO_EVENT_QUEUE* event_display_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
   // timePassed = (int)al_get_timer_count(timer);

    while (!done)
    {   
        

        //printf("Actual Time: %d min: %d sec",minutesPassed, secondsPassed);
        ALLEGRO_EVENT events;
       // ALLEGRO_EVENT events2;
        al_wait_for_event(event_queue, &events);
       // al_wait_for_event(event_display_queue, &events2);

        if (events.type == ALLEGRO_EVENT_TIMER) {
            timePassed += 1;
            if ((int)timePassed % 60 == 0 )
            {
                printf("%d", timePassed%60);
                minutesPassed += 1;
                localScore.gameTimeMin += 1;
                secondsPassed = 0;
            }
                
            else
            {
                secondsPassed += 1;
                localScore.gameTimeSec += 1;
            }
        }
       
        if (wygrana(t) == true)
        {
            //saveScoreBoard(wynik, minutesPassed, secondsPassed);
            updateRankingArray(gameScores, localScore);
            writeFile(gameScores);
            al_clear_to_color(getColor(0));
            for (int i = 0; i < 10; i++)
                al_draw_textf(F10, al_map_rgb(0, 0, 0), game_width / 2, i * game_width / 50, ALLEGRO_ALIGN_CENTER, "SCORE: %d TIMER: %d min %.2d sec", gameScores[i].wynik, gameScores[i].gameTimeMin, gameScores[i].gameTimeSec);
            al_flip_display();

            al_rest(10.0);
            al_destroy_display(display);
            al_destroy_event_queue(event_queue);

        }
        if (isGameLost(t) == true)
        {
            //saveScoreBoard(wynik, minutesPassed, secondsPassed);
            updateRankingArray(gameScores, localScore);
            writeFile(gameScores);
            al_clear_to_color(getColor(0));
            for (int i = 0; i < 10; i++)
                al_draw_textf(score_board_font, al_map_rgb(0, 0, 0), game_width / 2, i * game_width / 50, ALLEGRO_ALIGN_CENTER, "SCORE: %d TIMER: %d min %.2d sec", gameScores[i].wynik, gameScores[i].gameTimeMin, gameScores[i].gameTimeSec);
            al_flip_display();

            al_rest(10.0);
            done = true;
            al_destroy_display(display);
            al_destroy_event_queue(event_queue);

            

        }


        
        enum move key=none;

        if (events.type == ALLEGRO_EVENT_KEY_DOWN)
        {

            switch (events.keyboard.keycode)
            {
            case ALLEGRO_KEY_DOWN:
                key = down;
               // move(t,down2);

                break;
            case ALLEGRO_KEY_UP:
                key = up;
               // move(t, up2);

                break;
            case ALLEGRO_KEY_RIGHT:
                key = right;
                //move(t, right2);

                break;
            case ALLEGRO_KEY_LEFT:
                key = left;
                //move(t, left2);

                break;
            case ALLEGRO_KEY_ESCAPE:
                //saveScoreBoard(wynik, minutesPassed, secondsPassed);

                done = true;
                printf("SCORE %d TIME %d %d ", localScore.wynik, localScore.gameTimeMin, localScore.gameTimeSec);
                


                al_clear_to_color(getColor(0));
                al_draw_text(score_board_font,al_map_rgb_f(0, 0,0), game_width / 2, game_height / 2,ALLEGRO_ALIGN_CENTER,"G A M E  O V E R");
                printf("SCORE %d TIME %d %d ", localScore.wynik, localScore.gameTimeMin, localScore.gameTimeSec);

                al_draw_textf(score_board_font,al_map_rgb_f(0, 0,0), game_width / 2, game_height / 2+game_height/20,ALLEGRO_ALIGN_CENTER, "SCORE: %d TIMER: %d min %.2d sec", localScore.wynik, localScore.gameTimeMin, localScore.gameTimeSec);
                al_flip_display();
                updateRankingArray(gameScores, localScore);
                writeFile(gameScores);

                al_rest(3.0);
                al_clear_to_color(getColor(0));
                al_draw_textf(score_board_font, al_map_rgb(0, 0, 0), game_width / 2, 0, ALLEGRO_ALIGN_CENTER, "LEADERBOARD");

                for (int i=0; i<10;i++)
                    al_draw_textf(score_board_font, al_map_rgb(0, 0, 0),game_width/2, (i+1) * game_height / 10-game_height/20, ALLEGRO_ALIGN_CENTER, "SCORE: %d TIMER: %d min %.2d sec", gameScores[i].wynik, gameScores[i].gameTimeMin, gameScores[i].gameTimeSec);
                al_flip_display();
               
                al_rest(15.0);
                

                break;
               
            default:
                
                break;
            }

        }
        else if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        {
            done = true;

            break;
        }
       
        if (key == left)
            move(t, left2);      
        else if (key == right)       
            move(t, right2);
        
        else if (key == down)
            move(t, down2);
        else if (key == up)
            move(t, up2);


        localScore.wynik = wynik;


        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                al_draw_filled_rectangle(j * game_width/4 , i * game_width / 4, (j + 1) * game_width / 4, (i + 1) * game_width / 4, getColor(t[i][j]));
            }
        }
       /* al_draw_line(6, 0, 6, 406, al_map_rgb(0, 0, 0), 3); //rysujemy ramke
        al_draw_line(106, 0, 106, 406, al_map_rgb(0, 0, 0), 3);
        al_draw_line(206, 0, 206, 406, al_map_rgb(0, 0, 0), 3);
        al_draw_line(306, 0, 306, 406, al_map_rgb(0, 0, 0), 3);
        al_draw_line(406, 0, 406, 406, al_map_rgb(0, 0, 0), 3);
        */
        al_draw_line(3, 0, 3, game_width, al_map_rgb(0, 0, 0), 4); //rysujemy ramke
        al_draw_line(game_width / 4, 0, game_width / 4, game_width, al_map_rgb(0, 0, 0), 3);
        al_draw_line(game_width / 2, 0, game_width / 2, game_width, al_map_rgb(0, 0, 0), 3);
        al_draw_line((game_width * 3 / 4), 0, game_width * 3 / 4, game_width, al_map_rgb(0, 0, 0), 3);
        al_draw_line(game_width-3, 0, game_width-3, game_width, al_map_rgb(0, 0, 0),4);




        al_draw_line(3, 0, game_width-3, 0, al_map_rgb(0, 0, 0), 6); //rysujemy ramke
        al_draw_line(3, game_width/4, game_width-3, game_width / 4, al_map_rgb(0, 0, 0), 3); //rysujemy ramke
        al_draw_line(3, game_width*3/4,game_width - 3, game_width * 3 / 4, al_map_rgb(0, 0, 0), 3); //rysujemy ramke
        al_draw_line(3, game_width/2, game_width - 3, game_width / 2, al_map_rgb(0, 0, 0), 3); //rysujemy ramke
        al_draw_line(3, game_width, game_width - 3, game_width , al_map_rgb(0, 0, 0), 3); //rysujemy ramke
       

        /*
        al_draw_line(6, 0, 406, 0, al_map_rgb(0, 0, 0), 3);
        al_draw_line(6, 106, 406, 106, al_map_rgb(0, 0, 0), 3);
        al_draw_line(6, 206, 406, 206, al_map_rgb(0, 0, 0), 3);
        al_draw_line(6, 306, 406, 306, al_map_rgb(0, 0, 0), 3);
        al_draw_line(6, 406, 406, 406, al_map_rgb(0, 0, 0), 3);
        */

        al_draw_text(fontWYNIK, al_map_rgb(0, 0, 0), 2, game_width+game_height/20, 0, "WYNIK:"); //wyswietla napis 'WYNIK'
                //printf("Actual Time: %d min: %d sec",minutesPassed, secondsPassed);
        al_draw_text(fontWYNIK, al_map_rgb(0, 0, 0), 2, game_width + game_height / 12, 0, "TIMER:"); //wyswietla napis 'TIMER'


        al_draw_textf(fontWART_WYNIK, al_map_rgb(0, 0, 0), 140, game_width + game_height / 20, 0, "%.0f", wynik); //wyswietla wartość wyniku
        al_draw_textf(fontWART_WYNIK, al_map_rgb(0, 0, 0), 140, game_width + game_height / 12, 0, "%d min %d sec", minutesPassed, secondsPassed); //wyswietla aktualny czas gry


       // al_draw_filled_rectangle(280, 20, 350, 80, al_map_rgb(0, 0, 0));
        if (t[0][0] != 0) al_draw_textf(F1, al_map_rgb(0, 0, 0), game_width / 8, game_width / 8, 0, "%d", t[0][0]); //wyswietla wartosci tablicy 
        if (t[0][1] != 0)al_draw_textf(F2, al_map_rgb(0, 0, 0), game_width *3 / 8, game_width / 8, 0, "%d", t[0][1]);
        if (t[0][2] != 0) al_draw_textf(F3, al_map_rgb(0, 0, 0), game_width * 5 / 8, game_width / 8, 0, "%d", t[0][2]);
        if (t[0][3] != 0)al_draw_textf(F4, al_map_rgb(0, 0, 0), game_width * 7 / 8, game_width / 8, 0, "%d", t[0][3]);

        if (t[1][0] != 0)al_draw_textf(F5, al_map_rgb(0, 0, 0), game_width/8, game_width * 3 / 8, 0, "%d", t[1][0]);
        if (t[1][1] != 0)al_draw_textf(F6, al_map_rgb(0, 0, 0), game_width * 3 / 8, game_width * 3 / 8, 0, "%d", t[1][1]);
        if (t[1][2] != 0)al_draw_textf(F7, al_map_rgb(0, 0, 0), game_width * 5 / 8, game_width * 3 / 8, 0, "%d", t[1][2]);
        if (t[1][3] != 0)al_draw_textf(F8, al_map_rgb(0, 0, 0), game_width * 7 / 8, game_width * 3 / 8, 0, "%d", t[1][3]);

        if (t[2][0] != 0)al_draw_textf(F9, al_map_rgb(0, 0, 0), game_width / 8, game_width * 5 / 8, 0, "%d", t[2][0]);
        if (t[2][1] != 0)al_draw_textf(F10, al_map_rgb(0, 0, 0), game_width * 3 / 8, game_width * 5 / 8, 0, "%d", t[2][1]);
        if (t[2][2] != 0)al_draw_textf(F11, al_map_rgb(0, 0, 0), game_width * 5 / 8, game_width * 5 / 8, 0, "%d", t[2][2]);
        if (t[2][3] != 0) al_draw_textf(F12, al_map_rgb(0, 0, 0), game_width * 7 / 8, game_width * 5 / 8, 0, "%d", t[2][3]);

        if (t[3][0] != 0)al_draw_textf(F13, al_map_rgb(0, 0, 0), game_width / 8, game_width * 7 / 8, 0, "%d", t[3][0]);
        if (t[3][1] != 0)al_draw_textf(F14, al_map_rgb(0, 0, 0), game_width * 3 / 8, game_width * 7 / 8, 0, "%d", t[3][1]);
        if (t[3][2] != 0)al_draw_textf(F15, al_map_rgb(0, 0, 0), game_width * 5 / 8, game_width * 7 / 8, 0, "%d", t[3][2]);
        if (t[3][3] != 0) al_draw_textf(F16, al_map_rgb(0, 0, 0), game_width * 7 / 8, game_width * 7 / 8, 0, "%d", t[3][3]);

        al_flip_display();
        al_clear_to_color(al_map_rgb(213, 196, 161));
        //print(t);
    }
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);


    return 0;

}

