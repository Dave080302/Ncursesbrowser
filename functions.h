typedef struct
{
    char url[50],title[50],*continut;
    int nrac,checksum,colour,background;
}site;
enum colours {red=1,blue,green,white,yellow,defaultcolour};
int verificare(char[],char[]);
int filtrare2(site *,site *, char [][100],int,int );
int comp2(site, site);
int filtrare3(site *,site *, char [][30],char [][30],char [][30],int,int,int,int);
int comp3(site , site);
void swap(site *,site *);
void sortare(site *,site *,int,int (*comp)(site site1, site site2));
void printsite(site);
void foundsites(site *,int,char []);
void simplesearch(site *,char [],int);
void meniucautare(site *,char [],int);
