#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int instancja[2][1000];
int zadania[50][2];

void generatorInstancji(){
    ///zerowanie
    for (int i=0; i<1000; i++){
       instancja [0][i]=-10;
       instancja [1][i]=-10;
    }

    srand(time(0));
    int iloscPrzerw = 0;
    int poczatek, dlugosc;
    while (iloscPrzerw < 20){
        poczatek = rand()%400+1;
        dlugosc = rand()%15+1;
        int test = 1;
        for (int j = poczatek-1; j<poczatek+dlugosc+1; j++){
            if (instancja[0][j] != -10){
                test = 0;
            }
        }
        if (test){
            for (int i=poczatek; i<poczatek+dlugosc; i++){
                instancja[0][i] = -1;
            }
            iloscPrzerw++;
        }
    }
    //dla 2 procesora to samo
    iloscPrzerw = 0;
    while (iloscPrzerw < 20){
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
        zadania[i][0] = rand()%10+1;
        zadania[i][1] = rand()%10+1;
    }
}




int main(){
    generatorInstancji();
    return 0;
}
