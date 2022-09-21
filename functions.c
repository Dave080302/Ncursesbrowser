#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <unistd.h>
#include "functions.h"
int verificare(char sir[],char cuv[])
{
    char *p,copiesir[1000],listcuv[100][100];
    int n=0;
    strcpy(copiesir,sir);
    p=strtok(copiesir,"  \n");
    while(p)
    {
        strcpy(listcuv[n],p);
        n++;
        p=strtok(NULL,"  \n");
    }
    for(int i=0; i<n; i++)
        if(strcmp(listcuv[i],cuv)==0)
            return 1;
    return 0;

}
int filtrare2(site *filtr,site *sites, char cuv[][100],int n,int nrcuv)
{
    cuv[nrcuv-1][strlen(cuv[nrcuv-1])-1]=0;
    int i,j,k=0;
    for(i=0; i<n; i++)
    {
        int check=0;
        for(j=0; j<nrcuv; j++)
        {
            if(verificare(sites[i].continut,cuv[j])==1)
                check=1;
        }
        if(check==1)
        {
            filtr[k]=sites[i];
            k++;
        }
    }
    return k;
}
int comp2(site site1, site site2)
{
    if(strcmp(site1.continut,site2.continut)>0)
        return 1;

    else if(strcmp(site1.continut,site2.continut)<0)
        return -1;
    else
    {
        if(site1.nrac<site2.nrac)
            return 1;
        else return -1;
    }
    return 0;
}
int filtrare3(site *filtr,site *sites, char cuv[][30],char secv[][30],char neg[][30],int n,int nrsecv,int nrneg,int nrcuv)
{
    int i,j;
    int k=0;
    for(i=0; i<n; i++)
    {
        int ok=0;
        for(j=0; j<nrsecv; j++)
            if(strstr(sites[i].continut,secv[j])!=0)
                ok=1;
        for(j=0; j<nrcuv; j++)
            if(verificare(sites[i].continut,cuv[j])==1)
                ok=1;
        for(j=0; j<nrneg; j++)
            if(verificare(sites[i].continut,neg[j])==1)
                ok=0;

        if(ok==1)
        {
            filtr[k]=sites[i];
            k++;
        }
    }
    return k;
}


int comp3(site site1, site site2)
{
        if(site1.nrac<site2.nrac)
            return 1;
        if(site1.nrac>site2.nrac)
            return -1;
    return 0;
}
void swap(site *site1,site *site2)
{
    site aux= *site1;
    *site1=*site2;
    *site2=aux;
}
void sortare(site *sort,site *filtr,int n,int (*comp)(site site1, site site2))
{
    int i;
    int sortat=0;
    while(sortat==0)
    {
        sortat=1;
        for(i=0; i<n-1; i++)
            if(comp(filtr[i],filtr[i+1])>0)
            {
                swap(&filtr[i],&filtr[i+1]);
                sortat=0;
            }

    }
    for(i=0; i<n; i++)
        sort[i]=filtr[i];
    
}
void printsite(site s)
{
    if(has_colors()==FALSE)
    {
        endwin();
        exit(1);
    }
    start_color();
    int cont=0;
    switch(s.colour)
    {
        
        case red:
            switch(s.background)
                {
                    case red: init_pair(1,COLOR_RED,COLOR_RED);cont=1;break;
                    case blue: init_pair(2,COLOR_RED,COLOR_BLUE);cont=2;break;
                    case green: init_pair(3,COLOR_RED,COLOR_GREEN);cont=3;break;
                    case white: init_pair(4,COLOR_RED,COLOR_WHITE);cont=4;break;
                    case yellow: init_pair(5,COLOR_RED,COLOR_YELLOW);cont=5;break;
                    default: init_pair(6,COLOR_RED,COLOR_BLACK);cont=6;break;
                }
         break;
        case blue:
            switch(s.background)
                {
                    case red: init_pair(7,COLOR_BLUE,COLOR_RED);cont=7;break;
                    case blue: init_pair(8,COLOR_BLUE,COLOR_BLUE);cont=8;break;
                    case green: init_pair(9,COLOR_BLUE,COLOR_GREEN);cont=9;break;
                    case white: init_pair(10,COLOR_BLUE,COLOR_WHITE);cont=10;break;
                    case yellow: init_pair(11,COLOR_BLUE,COLOR_YELLOW);cont=11;break;
                    default: init_pair(12,COLOR_BLUE,COLOR_BLACK);cont=12;break;
                }
            break;
        case green:
         switch(s.background)
                {
                    case red: init_pair(13,COLOR_GREEN,COLOR_RED);cont=13;break;
                    case blue: init_pair(14,COLOR_GREEN,COLOR_BLUE);cont=14;break;
                    case green: init_pair(15,COLOR_GREEN,COLOR_GREEN);cont=15;break;
                    case white: init_pair(16,COLOR_GREEN,COLOR_WHITE);cont=16;break;
                    case yellow: init_pair(17,COLOR_GREEN,COLOR_YELLOW);cont=17;break;
                    default: init_pair(18,COLOR_GREEN,COLOR_BLACK);cont=18;break;
                }
         break;
        case white:
         switch(s.background)
                {
                    case red: init_pair(19,COLOR_WHITE,COLOR_RED);cont=19;break;
                    case blue: init_pair(20,COLOR_WHITE,COLOR_BLUE);cont=20;break;
                    case green: init_pair(21,COLOR_WHITE,COLOR_GREEN);cont=21;break;
                    case white: init_pair(22,COLOR_WHITE,COLOR_WHITE);cont=22;break;
                    case yellow: init_pair(23,COLOR_WHITE,COLOR_YELLOW);cont=23;break;
                    default: init_pair(24,COLOR_WHITE,COLOR_BLACK);cont=24;break;
                }
         break;
        case yellow:
         switch(s.background)
                {
                    case red: init_pair(25,COLOR_YELLOW,COLOR_RED);cont=25;break;
                    case blue: init_pair(26,COLOR_YELLOW,COLOR_BLUE);cont=26;break;
                    case green: init_pair(27,COLOR_YELLOW,COLOR_GREEN);cont=27;break;
                    case white: init_pair(28,COLOR_YELLOW,COLOR_WHITE);cont=28;break;
                    case yellow: init_pair(29,COLOR_YELLOW,COLOR_YELLOW);cont=29;break;
                    default: init_pair(30,COLOR_YELLOW,COLOR_BLACK);cont=30;break;
                }
         break;
        default:switch(s.background)
                {
                    case red: init_pair(31,COLOR_WHITE,COLOR_RED);cont=31;break;
                    case blue: init_pair(32,COLOR_WHITE,COLOR_BLUE);cont=32;break;
                    case green: init_pair(33,COLOR_WHITE,COLOR_GREEN);cont=33;break;
                    case white: init_pair(34,COLOR_WHITE,COLOR_WHITE);cont=34;break;
                    case yellow: init_pair(35,COLOR_WHITE,COLOR_YELLOW);cont=35;break;
                    default: init_pair(36,COLOR_WHITE,COLOR_BLACK);cont=36;break;
                }break;
    };
    
    if(cont!=0)    
    {

        clear();
        attron(A_BOLD);
        mvprintw(0,28,s.title);
        attroff(A_BOLD);
        attron(COLOR_PAIR(cont));
        mvprintw(1,0,s.continut);
        attroff(COLOR_PAIR(cont));
        attron(COLOR_PAIR(36));
        attroff(COLOR_PAIR(36));
        mvprintw(20,35,"Legenda");
        mvprintw(21,10,"B: Reveniti la pagina cu rezultatele");
        refresh();
        int letter;
        while(1)
        {
            letter=getch();
            if(letter=='b')
            break;
        }
        
    }
    else
    {
        clear();
        attron(A_BOLD);
        mvprintw(0,28,s.title);
        attroff(A_BOLD);
        mvprintw(1,0,s.continut);
        mvprintw(20,35,"Legenda");
        mvprintw(21,10,"B: Reveniti la pagina cu rezultatele");
        int letter;
        while(1)
        {
            letter=getch();
            if(letter=='b')
            break;
        }
        refresh();
    }
}
void foundsites(site *sort,int n,char input[])
{
    if(n==0)
    {
        clear();
        mvprintw(0,20,"Sorry, no options available,press B to return.");
        refresh();
        int letter1=0;
        while(1)
            {
                letter1=getch();
                if(letter1=='b')
                    break;
            }


    }
    else{
        clear();
        int i=0;
        mvprintw(0,20,"Sites containing ");
        mvprintw(0,38,input);
        mvprintw(0,38+strlen(input),":");
        for(i=0;i<n;i++)
                {
                    mvprintw((i+1)*3,10,sort[i].url);
                    mvprintw((i+1)*3,11+strlen(sort[i].url),sort[i].title);
                }
        mvprintw(3,7,"->");
        move(3,9);
        mvprintw(20,35,"Legenda:");
        mvprintw(21,10,"B: Reveniti la pagina de cautare");
        mvprintw(22,10,"Enter: Selectati site-ul din dreptul cursorului");
        mvprintw(23,10,"Up,down pentru navigarea printre site-uri");
        refresh();
        int currentsite=0;
        int letter=0;
        while(1)
        {
            letter=getch();
            if(letter=='b')
                break;
            if(letter== KEY_UP)
                {
                    if(currentsite>0)
                    currentsite--;
                else
                    currentsite=n-1;
                }
            if(letter== KEY_DOWN)
                currentsite=(currentsite+1)%n;
            if(letter=='\n')
            {
                printsite(sort[currentsite]);
                clear();
                mvprintw(0,20,"Sites containing ");
                mvprintw(0,38,input);
                mvprintw(0,38+strlen(input),":");
                for(i=0;i<n;i++)
                {
                    mvprintw((i+1)*3,10,sort[i].url);
                    mvprintw((i+1)*3,11+strlen(sort[i].url),sort[i].title);
                }
                mvprintw(3*(currentsite+1),7,"->");
                mvprintw(20,35,"Legenda:");
                mvprintw(21,10,"B: Reveniti la pagina de cautare");
                mvprintw(22,10,"Enter: Selectati site-ul din dreptul cursorului");
                mvprintw(23,10,"Up,down pentru navigarea printre site-uri");
                refresh();
            }
            for(i=0;i<n;i++)
                mvprintw(3*(i+1),7,"  ");
            mvprintw(3*(currentsite+1),7,"->");
            refresh();
    }
    }
}
void simplesearch(site *sites,char input[],int n)
{
    char cuvinte[100][100],cpinput[40];
    strcpy(cpinput,input);
    char *p=strtok(cpinput," ");
    int j=0;
    while(p != NULL)
    {
        strcpy(cuvinte[j],p);
        j++;
        p=strtok(NULL," ");
    }
    site *filtr;
    filtr=malloc(n*sizeof(site));
    int k=0;
    k=filtrare2(filtr,sites,cuvinte,n,j);
    site *sorted;
    sorted=malloc(k*sizeof(site));
    int (*cmp2)(site,site)=comp2;
    sortare(sorted,filtr,k,cmp2);
    foundsites(sorted,k,input);
    free(sorted);
    free(filtr);

}
        
void advancedsearch(site *sites, char input[],int n)
{
        char cuvinte[30][30],secv[30][30],neg[30][30];
    int nrcuv=0,nrsecv=0,nrneg=0;
    char cpinput[40];
    strcpy(cpinput,input);
    char *p=strtok(cpinput," ");
    while(p != NULL)
    {
        char aux[30];
        strcpy(aux,p);
        if(aux[0]=='-')
            strcpy(neg[nrneg++],p+1);
        else if(aux[0]=='"')
        {
            secv[nrsecv][0]=0;
            strcat(secv[nrsecv],p+1);
            while(aux[strlen(aux)-1]!='"')
            {
                p=strtok(NULL," ");
                strcpy(aux,p);
                if(aux[strlen(aux)-1]!='"')
                    strcat(secv[nrsecv],aux);
                strcat(secv[nrsecv]," ");
            }
            aux[strlen(aux)-1]='\0';
            strcat(secv[nrsecv],aux);
            nrsecv++;
        }
        else strcpy(cuvinte[nrcuv++],aux);
        p=strtok(NULL," ");
    }
    site *filtr;
    filtr=malloc(n*sizeof(site));
    int k=0;
    k=filtrare3(filtr,sites,cuvinte,secv,neg,n,nrsecv,nrneg,nrcuv);
    site *sorted;
    sorted=malloc(k*sizeof(site));
    int (*cmp3)(site,site)=comp3;
    sortare(sorted,filtr,k,cmp3);
    foundsites(sorted,k,input);
    free(sorted);
    free(filtr);
}
void meniucautare(site *sites,char input[],int n)
{
    int letter=0;
    clear();
    mvprintw(1,20,"Browser-ul lui Biju");
     mvprintw(20,35,"Legenda:");
     mvprintw(21,10,"S: Lansati o cautare simpla");
     mvprintw(22,10,"A: Lansati o cautare avansata");
    refresh();
    while(1)
    {
        letter=getch();
        if(letter=='s')
            {
                simplesearch(sites,input,n);
                break;
            }
        else if(letter='a')
            {
                advancedsearch(sites,input,n);
                break;
            }
        else
        {
            clear();
            mvprintw(1,20,"Browser-ul lui Biju");
            mvprintw(20,35,"Legenda:");
            mvprintw(21,10,"S: Lansati o cautare simpla");
            mvprintw(22,10,"A: Lansati o cautare avansata");
            refresh();
        }

    }
}