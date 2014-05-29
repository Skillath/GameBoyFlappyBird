#include <graphics.h>
#include <time.h>
#include <stdio.h>

void scrivi_punteggio(int score);
int disegna_bird(int x_pos, int y_pos);
void disegna_rettangoli(struct barra* rett, int n_rett);
int collisioni(struct barra* rett, int n_rett);
int conta_punti(struct barra* rett, int n_rett, int punti);

struct barra
{
    int x_rett;
    int altezza;
};

int main() 
{
    int x_pos=150;
    int y_pos=450;
    struct barra rett[3];
    int contatore;
    int esecuzione=0;
    int n_rett=0;
    int flag=0;
    int punti=0;
    srand(time(NULL));
    initwindow(640, 480, "Bounce v1.2.1", 0, 0, true, true);
    setbkcolor(3);
    for(contatore=0;contatore<3;contatore++)
        rett[contatore].x_rett=615;
    while(1) 
    {
        y_pos=disegna_bird(x_pos, y_pos);
        disegna_rettangoli(rett, n_rett);
        if(esecuzione>0) 
        {
            flag=collisioni(rett, n_rett);
            punti=conta_punti(rett, n_rett, punti);
        }
        if(flag==1) 
        {
            outtext("PUNTI:  ");
            bgiout << punti;
            outstream();
            outtextxy(0,20, "HAI PERSO");
            outtextxy(0,40, "PREMERE UN TASTO PER CONTINUARE");
            swapbuffers();
            break;
        }
        else 
        {
            for(contatore=0;contatore<n_rett;contatore++)
                rett[contatore].x_rett=rett[contatore].x_rett-5;
            if(esecuzione%40==0 && n_rett<3)
                n_rett++;
            esecuzione++;
            delay(40);
            outtext("PUNTI:  ");
            bgiout << punti;
            outstream();
            swapbuffers();
            cleardevice();
        }
    }
    scrivi_punteggio(punti);
    delay(200);
    getch();
    closegraph();
    return 0;
}

int disegna_bird(int x_pos, int y_pos) 
{
    if(ismouseclick(WM_MOUSEMOVE)) 
    {
        if(y_pos-16>0)
            y_pos=y_pos-20;
        readimagefile("bird.bmp", x_pos, y_pos, x_pos+40, y_pos+27);
    }
    else 
    {
        if(y_pos<450)
            y_pos=y_pos+5;
        readimagefile("bird.bmp", x_pos, y_pos, x_pos+40, y_pos+27);
    }
    clearmouseclick(WM_MOUSEMOVE);
    return y_pos;
}

void disegna_rettangoli(struct barra* rett, int n_rett) 
{
    int contatore;
    for(contatore=0;contatore<n_rett;contatore++) 
    {
        if(rett[contatore].x_rett==0)
            rett[contatore].x_rett=615;
        if(rett[contatore].x_rett==615)
            rett[contatore].altezza=rand()%(480-100)+1;
        rectangle(rett[contatore].x_rett, 0, rett[contatore].x_rett+25, rett[contatore].altezza);
        rectangle(rett[contatore].x_rett, rett[contatore].altezza+100, rett[contatore].x_rett+25, 480);
        setfillstyle(SOLID_FILL, GREEN);
        floodfill(rett[contatore].x_rett+1, 1, 15);
        floodfill(rett[contatore].x_rett+1, 479, 15);
    }
    return;
}

int collisioni(struct barra* rett, int n_rett) 
{
    int verifica=0, flag=0, contatore1, contatore;
    for(contatore1=0;contatore1<n_rett;contatore1++) 
    {
        if(rett[contatore1].x_rett>130) {
            for(contatore=0;contatore<rett[contatore1].altezza;contatore++) 
            {
                if(getpixel(rett[contatore1].x_rett-1, contatore)!=getbkcolor()) 
                {
                    verifica=1;
                    goto fine;
                }
            }
            for(contatore=rett[contatore1].altezza+100;contatore<480;contatore++) 
            {
                if(getpixel(rett[contatore1].x_rett-1, contatore)!=getbkcolor()) 
                {
                    verifica=1;
                    goto fine;
                }
            }
            for(contatore=rett[contatore1].x_rett;contatore<rett[contatore1].x_rett+15;contatore++) 
            {
                if(getpixel(contatore, rett[contatore1].altezza+1)!=getbkcolor()) 
                {
                    verifica=1;
                    goto fine;
                }
            }
            for(contatore=rett[contatore1].x_rett;contatore<rett[contatore1].x_rett+15;contatore++) 
            {
                if(getpixel(contatore, rett[contatore1].altezza+99)!=getbkcolor()) 
                {
                    verifica=1;
                    goto fine;
                }
            }
        }
    }
    fine:
    if(verifica==1) 
    {
        flag=1;
    }
    return flag;
}

int conta_punti(struct barra* rett, int n_rett, int punti) 
{
    int contatore1, contatore;
    for(contatore1=0;contatore1<n_rett;contatore1++) 
    {
        if(rett[contatore1].x_rett==120) 
        {
            for(contatore=rett[contatore1].altezza;contatore<rett[contatore1].altezza+100;contatore++) {
                if(getpixel(rett[contatore1].x_rett+32, contatore)!=getbkcolor()) 
                {
                    punti++;
                    break;
                }
            }
        }
    }
    return punti;
}


void scrivi_punteggio(int score) 
{
    FILE* file_punteggio;
    file_punteggio=fopen("punti.txt", "a");
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    fprintf(file_punteggio, "\n\n%s", asctime(timeinfo), "s");
    fprintf(file_punteggio, "Punteggio: ", "s");
    fprintf(file_punteggio, "%i", score, "i");
    fclose(file_punteggio);
    return;
}