#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int instancja[2][1000];             //wzorzec instancji
int zadania[50][2];                 //tab z zadaniami

int rozwiazania1[50][1000];         //tablica z 50 rozwiazan dla 1 procka
int rozwiazaniaTmp1[150][1000];     //tab z 150 rozw (mutacje i krzyzowanie) dla 1 procka, one beda odrzucane
int rozwiazania2[50][1000];         //to samo dla 2
int rozwiazaniaTmp2[150][1000];

void generatorInstancji(){
    ///zerowanie
    for (int i=0; i<1000; i++){     //zeruje calosc
       instancja [0][i]=-10;
       instancja [1][i]=-10;
    }

    srand(time(0));
    int iloscPrzerw = 0;
    int poczatek, dlugosc;
    while (iloscPrzerw < 20){
        poczatek = rand()%500+1;        //losuje poczatek przerw konserwacyjnych
        dlugosc = rand()%15+1;
        int test = 1;
        for (int j = poczatek-1; j<poczatek+dlugosc+1; j++){
            if (instancja[0][j] != -10){
                test = 0;
            }                           //testuje czy miejsce jest wolne
        }
        if (test){
            for (int i=poczatek; i<poczatek+dlugosc; i++){
                instancja[0][i] = -1;
            }
            iloscPrzerw++;              //jesli tak to dodaje
        }
    }
    
    
    iloscPrzerw = 0;
    while (iloscPrzerw < 20){           //to samo dla 2 procka
        poczatek = rand()%400+1;
        dlugosc = rand()%15+1;
        int test = 1;
        for (int j = poczatek-1; j<poczatek+dlugosc+1; j++){
            if (instancja[1][j] != -10){
                test = 0;
            }
        }
        if (test){
            for (int i=poczatek; i<poczatek+dlugosc; i++){
                instancja[1][i] = -1;
            }
            iloscPrzerw++;
        }
    }
    /* SPRAWDZA CZY DOBRZE DODALO PRZERWY
    int licznik = 0;
    for (int i=i; i<1000; i++)
        if (instancja[1][i-1]<instancja[1][i])
            licznik++;
    cout<<licznik<<endl;*/
    for (int i=0; i<50; i++){
        zadania[i][0] = rand()%15+1;
        zadania[i][1] = rand()%15+1;        //randuje zadania
    }
                                            //kopiowanie instancji do rozwiazan
    for (int i=0; i<50; i++){
        for (int j=0; j<1000; j++){
            rozwiazania1[i][j]=instancja[0][j];
            rozwiazania2[i][j]=instancja[1][j];
        }
    }
    for (int i=0; i<150; i++){
        for (int j=0; j<1000; j++){
            rozwiazaniaTmp1[i][j]=instancja[0][j];
            rozwiazaniaTmp2[i][j]=instancja[1][j];
        }
    }
    
} //jesli -10 to nic nie ma, jesli -1 to jest przerwa

void testInstancji(){
    printf("INSTANCJA /////////////////");
    for (int i=0; i<1000; i++){
        printf("%d",instancja[1][i]);
    }
}//wypisuje instancje, generalnie useless ale patrzylem czy dziala

void generatorLosowych(){
    int tabZadan[50][2];            //pomocnicza
    for (int k=0; k<50; k++){       //dla 50 zadan
        for (int i=0; i<50; i++){
            tabZadan[i][0]=i;       //kazdy element do tablic
            tabZadan[i][1]=i;
        }
        int tmp, tmp1, tmp2;
        for (int i=0; i<50; i++){   //mieszam obie tablice, dla obu prockow, czyli defacto mieszam kolejnosc
            tmp1=rand()%50;         //50 razy zamieniam 2 randomowe elementy, wystarczy raczej
            tmp2=rand()%50;
            tmp = tabZadan[tmp1][0];
            tabZadan[tmp1][0]=tabZadan[tmp2][0];
            tabZadan[tmp2][0]=tmp;
            
            tmp1=rand()%50;
            tmp2=rand()%50;
            tmp = tabZadan[tmp1][1];
            tabZadan[tmp1][1]=tabZadan[tmp2][1];
            tabZadan[tmp2][1]=tmp;
        }
        /* //SPRAWDZANIE SUM
        int sum1, sum2;
        sum1=sum2=0;
        for (int i=0; i<50; i++){
            printf("%d\t%d\n", tabZadan[i][0],tabZadan[i][1]);
            sum1+=tabZadan[i][0];
            sum2+=tabZadan[i][1];
        }
        printf("%d\t%d\n", sum1, sum2);*/ //kolejne useless
        
        int wskaznik = 0, dlugosc, ktoreZadanie;        //i teraz dla kazdej z 50 tablic, 50 zadan dodaje
        for (int i=0; i<50; i++){
            dlugosc = 0;
            ktoreZadanie = tabZadan[i][0];
            dlugosc = zadania[ktoreZadanie][0];
            //printf("%d ",ktoreZadanie);
            //printf("%d\t",dlugosc);
            int test = 0;
            while (!test){                              //jade po kolei
                int czyWolne = 1;
                for (int j=wskaznik; j<wskaznik+dlugosc; j++){
                    if (instancja[0][j] != -10){
                        czyWolne = 0;
                        //printf("AAAAAAAAAAAA");
                    }
                }
                if (czyWolne){                          //patrze czy moge wrzucic zadanie
                    for (int j = wskaznik; j<wskaznik+dlugosc; j++){
                        rozwiazania1[k][j] = ktoreZadanie;
                    }
                    test=1;
                    //printf("%d\t", i);
                    wskaznik+=dlugosc;
                }
                else{
                    wskaznik++;
                }
            }
        }
    }
        
        
    //testy do losowych na 1 procku, zawsze ma wyjsc 1225, wychodzi
    /*
    int suma = 0;
    for(int k=0; k<50; k++){
        for (int i=0; i<999; i++){
            if (rozwiazania1[k][i]>=0 && (rozwiazania1[k][i]!=rozwiazania1[k][i+1]))
                suma+= rozwiazania1[k][i];
        }
        printf("%d\n",suma);
        suma=0;
    }
    
    suma=0;
    for (int i=0; i<50;i++){
        suma+=i;
    }
    printf("%d\n",suma);*/
    
    
    
}

void testLosowaniaDla1Procka(int ktore){
    int tab[50];
    for (int i = 0; i<999; i++){
        if (rozwiazania1[ktore][i]>=0 && rozwiazania1[ktore][i] != rozwiazania1[ktore][i+1])
            tab[rozwiazania1[ktore][i]] = 1;
    }
    int test = 1;
    for(int i=0; i<50; i++){
        if (tab[i] != 1){
            test = 0;
        }
    }
    if (test){
        printf ("zdane\n");
    }
    else {
        printf("NIEZDANEEEEEE\n");
    }
}    //sprawdza czy wszystkie procesy sa w rozwiazaniu, na procku 1
                                                //jesli wypisuje 50 wynikow testow


int main(){
    generatorInstancji();
    generatorLosowych();
    
    return 0;
}
