#pragma warning (disable:4996)

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#include <allegro5/allegro.h>

#include <allegro5/allegro_font.h>

#include <allegro5/allegro_primitives.h>

#include <allegro5/allegro_ttf.h>

#include <allegro5/allegro_native_dialog.h> //dodajemy wszystkie potrzebne biblioteki do korzystania z allegro

double wynik = 0;


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



void compress(int t[4][4])
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
                printf("test");
                print(tempTab);
            }
        }
    }
    printf("test 2\n");
    print(tempTab);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            t[i][j] = tempTab[i][j];
        }
    }


    printf("test 2.1\n");

    print(t);


}


void merge(int t[4][4])
{
    int tempTab[4][4] =
    { 0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    0,0,0,0 };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {

            if (t[i][j] == t[i][j + 1] && t[i][j] != 0) {
                t[i][j] += t[i][j];
                t[i][j + 1] = 0;
            }

        }
    }

}


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



struct color
{
    int value;
    ALLEGRO_COLOR color;
};

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
    print(t);





    if (!al_init()) //inicjalizujemy biblioteke allegro
    {
        fprintf(stderr, "Failed to initialize allegro!\n");
        return -1;
    }

    al_init_font_addon(); //inicjalizujemy czcionki 
    al_init_ttf_addon(); //inicjalizujemy czcionki true type 


    bool done = false;


    ALLEGRO_DISPLAY* display = NULL; //wskaznik do okna
    ALLEGRO_FONT* fontWYNIK = al_create_builtin_font(); //wskaznik do czcionki 'WYNIK'
    ALLEGRO_FONT* fontWART_WYNIK = al_create_builtin_font();  //wskaznik do czcionki 'WARTOSC WYNIKU'

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


    ALLEGRO_KEYBOARD_STATE klawiatura;



    display = al_create_display(410, 460); //tworzymy okno
    if (!display)
    {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }

    al_install_keyboard();

    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());


    while (!done)
    {
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);

        if (wygrana(t) == true)
        {
            al_destroy_display(display);
            al_destroy_event_queue(event_queue);

        }
        if (przegrana(t) == true)
        {
            al_destroy_display(display);
            al_destroy_event_queue(event_queue);

        }





        if (events.type == ALLEGRO_EVENT_KEY_DOWN)
        {

            switch (events.keyboard.keycode)
            {
            case ALLEGRO_KEY_DOWN:
                down(t);
                random_1(t);

                break;
            case ALLEGRO_KEY_UP:
                up(t);
                random_1(t);

                break;
            case ALLEGRO_KEY_RIGHT:
                right(t);
                random_1(t);

                break;
            case ALLEGRO_KEY_LEFT:
                printf("main test 2.1\n");
                print(t);
                compress(t);
                printf("main test 2.2\n");
                print(t);
                merge(t);
                printf("main test 2.3\n");
                print(t);
                compress(t);
                printf("main test 2.4\n");
                print(t);
                random_1(t);

                break;
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                random_1(t);
                break;
            }

        }
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                al_draw_filled_rectangle(j * 100 + 6, i * 100 + 6, (j + 1) * 100 + 6, (i + 1) * 100 + 6, getColor(t[i][j]));
            }
        }
        al_draw_line(6, 0, 6, 406, al_map_rgb(0, 0, 0), 3); //rysujemy ramke
        al_draw_line(106, 0, 106, 406, al_map_rgb(0, 0, 0), 3);
        al_draw_line(206, 0, 206, 406, al_map_rgb(0, 0, 0), 3);
        al_draw_line(306, 0, 306, 406, al_map_rgb(0, 0, 0), 3);
        al_draw_line(406, 0, 406, 406, al_map_rgb(0, 0, 0), 3);





        al_draw_line(6, 0, 406, 0, al_map_rgb(0, 0, 0), 3);
        al_draw_line(6, 106, 406, 106, al_map_rgb(0, 0, 0), 3);
        al_draw_line(6, 206, 406, 206, al_map_rgb(0, 0, 0), 3);
        al_draw_line(6, 306, 406, 306, al_map_rgb(0, 0, 0), 3);
        al_draw_line(6, 406, 406, 406, al_map_rgb(0, 0, 0), 3);

        al_draw_text(fontWYNIK, al_map_rgb(0, 0, 0), 2, 420, 0, "WYNIK:"); //wyswietla napis 'WYNIK'
        al_draw_textf(fontWART_WYNIK, al_map_rgb(0, 0, 0), 140, 420, 0, "%.0f", wynik); //wyswietla wartość wyniku

       // al_draw_filled_rectangle(280, 20, 350, 80, al_map_rgb(0, 0, 0));
        if (t[0][0] != 0) al_draw_textf(F1, al_map_rgb(0, 0, 0), 50, 50, 0, "%d", t[0][0]); //wyswietla wartosci tablicy 
        if (t[0][1] != 0)al_draw_textf(F2, al_map_rgb(0, 0, 0), 150, 50, 0, "%d", t[0][1]);
        if (t[0][2] != 0) al_draw_textf(F3, al_map_rgb(0, 0, 0), 250, 50, 0, "%d", t[0][2]);
        if (t[0][3] != 0)al_draw_textf(F4, al_map_rgb(0, 0, 0), 350, 50, 0, "%d", t[0][3]);

        if (t[1][0] != 0)al_draw_textf(F5, al_map_rgb(0, 0, 0), 50, 150, 0, "%d", t[1][0]);
        if (t[1][1] != 0)al_draw_textf(F6, al_map_rgb(0, 0, 0), 150, 150, 0, "%d", t[1][1]);
        if (t[1][2] != 0)al_draw_textf(F7, al_map_rgb(0, 0, 0), 250, 150, 0, "%d", t[1][2]);
        if (t[1][3] != 0)al_draw_textf(F8, al_map_rgb(0, 0, 0), 350, 150, 0, "%d", t[1][3]);

        if (t[2][0] != 0)al_draw_textf(F9, al_map_rgb(0, 0, 0), 50, 250, 0, "%d", t[2][0]);
        if (t[2][1] != 0)al_draw_textf(F10, al_map_rgb(0, 0, 0), 150, 250, 0, "%d", t[2][1]);
        if (t[2][2] != 0)al_draw_textf(F11, al_map_rgb(0, 0, 0), 250, 250, 0, "%d", t[2][2]);
        if (t[2][3] != 0) al_draw_textf(F12, al_map_rgb(0, 0, 0), 350, 250, 0, "%d", t[2][3]);

        if (t[3][0] != 0)al_draw_textf(F13, al_map_rgb(0, 0, 0), 50, 350, 0, "%d", t[3][0]);
        if (t[3][1] != 0)al_draw_textf(F14, al_map_rgb(0, 0, 0), 150, 350, 0, "%d", t[3][1]);
        if (t[3][2] != 0)al_draw_textf(F15, al_map_rgb(0, 0, 0), 250, 350, 0, "%d", t[3][2]);
        if (t[3][3] != 0) al_draw_textf(F16, al_map_rgb(0, 0, 0), 350, 350, 0, "%d", t[3][3]);

        al_flip_display();
        al_clear_to_color(al_map_rgb(213, 196, 161));
        print(t);
    }
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);


    return 0;

}

