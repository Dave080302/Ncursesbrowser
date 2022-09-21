#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <unistd.h>
#include "functions.h"
int main()
{
       site *sites;
    sites=malloc(3*(sizeof(site)));
    FILE *master=fopen("master.txt","r");
    char nume[30];
    int i=0;
    while(fgets(nume,30,master))
    {
        char codhtml[1000];
        nume[strlen(nume)-1]=0;
        char *inct,*sft;
        char linie[100];
        int lg=0,lgt=0;
        if(i%3==0 && i!=0)
            sites=realloc(sites,(i+3)*sizeof(site));///adaugam inca 3 slot-uri de memorie dupa ce i a atins valoarea 3
        FILE *fisier=fopen(nume,"r");
        fscanf(fisier,"%s %d %d %d \n",sites[i].url,&lg,&sites[i].nrac,&sites[i].checksum);
        codhtml[0]=0;
        while(fgets(linie,100,fisier))
        {
            strcat(codhtml,linie);
        }
        inct=strstr(codhtml,"<title>")+7;///adaugam +7, pentru ca pointer-ul sa se afle pe pozitia de dupa ">"
        sft=strstr(codhtml,"</title>");
        lgt=sft-inct;
        strncpy(sites[i].title,inct,lgt);
        sites[i].title[lgt]=0;
        char *incc,*sfc;
        incc=strstr(codhtml,"<p")+2;
        while(incc[0]!='>')
            incc++;
        incc++;
        sfc=strstr(codhtml,"</p>");
        lg=sfc-incc;
        sites[i].continut=malloc((lg+1)*(sizeof(char)));
        strncpy(sites[i].continut,incc,lg);
        sites[i].continut[lg]=0;
        char *sc,*ec;
        if(strstr(codhtml,"color:")!=0)
        {
            sc=strchr(codhtml,'"')+7;
            ec=strchr(codhtml,';');
        }
        char culoare[100];
        int lgc=0;
        lgc=ec-sc;
        if(lgc<100);
        strncpy(culoare,sc,lgc);
        culoare[lgc]=0;
        if(strcmp(culoare,"red")==0)
            sites[i].colour=1;
        else if(strcmp(culoare,"blue")==0)
            sites[i].colour=2;
        else if(strcmp(culoare,"green")==0)
            sites[i].colour=3;
        else if(strcmp(culoare,"white")==0)
            sites[i].colour=4;
        else if(strcmp(culoare,"yellow")==0)
            sites[i].colour=5;
        else sites[i].colour=6;
        char background[100];
        background[0]=0;
        char *sb,*eb;
        if(strstr(codhtml,"background-color:")!=0)
        {
            sb=strstr(codhtml,"background-color:")+17;
            eb=strrchr(codhtml,';');
        }        
        int lgb=0;
        lgb=eb-sb;
        if(lgb<100);
        strncpy(background,sb,lgb);
        background[lgb]=0;
        if(strcmp(background,"red")==0)
            sites[i].background=1;
        else if(strcmp(background,"blue")==0)
            sites[i].background=2;
        else if(strcmp(background,"green")==0)
            sites[i].background=3;
        else if(strcmp(background,"white")==0)
            sites[i].background=4;
        else if(strcmp(background,"yellow")==0)
            sites[i].background=5;
        else sites[i].background=6;
        i++;
        
        fclose(fisier);
    }
    initscr();
    cbreak();
    noecho();
    keypad(stdscr,TRUE);
    int letter;
    char input[38];
    for(int j=0;j<40;j++)
        input[j]=0; 
    mvprintw(20,35,"Legenda:");
    mvprintw(21,10,"C: Incepeti o cautare");
    mvprintw(22,10,"Q: Inchideti programul");
    refresh();
    while(1)
    {
        letter=getch();
        if(letter == 'c')
        {
            clear();
            mvprintw(1,20,"Browser-ul lui Biju");
            mvprintw(5,20,"+-----------------------------------------+");
            mvprintw(8,20,"+-----------------------------------------+");
            mvprintw(6,20,"|");
            mvprintw(7,20,"|");
            mvprintw(6,62,"|");
            mvprintw(7,62,"|");
            mvprintw(20,35,"Legenda:");
            mvprintw(21,10,"Q: Inchideti programul");
            mvprintw(22,10,"Enter: Lansati cautarea dupa introducerea string-ului");
            move(6,21);
            refresh();
            break;
        }
        if(letter == 'q')
            break;
    }
    int inputlenght=0;
    while(1)
    {
        letter=getch();
        if(letter=='q')
            break;
        else if(letter=='\n')
        {
                meniucautare(sites,input,i);
                clear();
           
            mvprintw(1,20,"Browser-ul lui Biju");
            mvprintw(5,20,"+-----------------------------------------+");
            mvprintw(8,20,"+-----------------------------------------+");
            mvprintw(6,20,"|");
            mvprintw(7,20,"|");
            mvprintw(6,62,"|");
            mvprintw(7,62,"|");
            mvprintw(20,35,"Legenda:");
            mvprintw(21,10,"Q: Inchideti programul");
            mvprintw(22,10,"Enter: Lansati cautarea dupa introducerea string-ului");
            
            move(6,21);
            mvprintw(6,21,input);
            refresh();
        }
        else if(letter== KEY_BACKSPACE)
        {
              if(inputlenght>0);
                {
                    inputlenght--;
                    input[strlen(input)-1]=0;
                    mvprintw(6,21,"                                     ");
                    mvprintw(6,21,input);
                    refresh();
                }
            

        }
        else
        {
            if(inputlenght<37)
                input[inputlenght++]=letter;
        mvprintw(6,21,"                                        ");
        mvprintw(6,21,input);
        }
    }
    clear();
    endwin();
    for(int j=0;j<i;j++)
	free(sites[j].continut);
    free(sites);

}