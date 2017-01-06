#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define key 30 // Klucz IPC
#define sem1 0
#define sem2 1

int memory;
int semafors;
int plansza[9] = {0,0,0,0,0,0,0,0,0}; // 0-8 stan planszy, 9 to wynik rundy: 0(pusto), 1(Gracz1), 2(Gracz2), 3(remis)
char *playername;
int Gracz1 = 1;
int Gracz2 = 2;
int *shm; // shm = shared memory

struct sembuf Gracz1_lock = {sem2,-1,0};  // Zablokuj P1
struct sembuf Gracz1_unlock = {sem1,1,0}; // Odblokuj P1
struct sembuf Gracz2_lock = {sem1,-1,0};  // Zablokuj P2
struct sembuf Gracz2_unlock = {sem2,1,0}; // Odblokuj P2


void intro(){
    system("clear");
    printf("\t Kółko i Krzyżyk \n");
}

int ruch(int player){
    int pole;
    int status = 1;
    while(status == 1){
        printf("\nPodaj numer pola od 1 do 9: ");
        scanf("%d",&pole);
        if(pole < 10 && pole > 0 ){
            if(plansza[pole-1] == 0){
                plansza[pole-1] = player;
                status = 0;
                return 0;
            }
            else{
                printf("\n\nTo pole jest akurat zajete.\n");
                status = 1;
            }
        }
        else{
            printf("\n\nZly numer pola.\n");
            status = 1;
        }
    }
}

void posprzataj(){
    semctl(semafors,0,IPC_RMID,0);
    shmdt(shm);
    shmctl(memory,IPC_RMID,0);
    exit(0);
}

int czy_juz(){
    int i = 0;
    if(plansza[0] == 0 && plansza[1] == 0 && plansza[2] == 0 && plansza[3] == 0 && plansza[4] == 0 && plansza[5] == 0 && plansza[6] == 0 && plansza[7] == 0 && plansza[8] == 0){
        return 1;
    }
    else{
        return 0;
    }
}

void kopiuj_do_pamieci(){
    int counter = 0;
    for(counter; counter<10; counter++) shm[counter] = plansza[counter];
}

void kopiuj_z_pamieci(){
    int counter = 0;
    for(counter;counter<10;counter++) plansza[counter] = shm[counter];
}

void rysuj_plansze(){
    int i = 0;
    int k = 0;
    printf("\n");
    while(k<9){
        for(i;i<3;i++){
            int j = 0;
            for(j;j<3;j++){
                if(plansza[k] == 0) printf("  "); // jesli 0, to pole jest puste
                if(plansza[k] == 1) printf(" O"); // jesli 1, to wstaw O - zawsze Gracz1
                if(plansza[k] == 2) printf(" X"); // jesli 2, to wstaw X - zawsze Gracz2
                if(j==0 || j==1) printf(" |");
                k++;
            }
            if(i==0 || i==1) printf("\n-----------\n");
        }
    }
    printf("\n\n");
}

void sprawdz_plansze(int player){
    if(plansza[0] != 0 && plansza[1] != 0 && plansza[2] != 0 && plansza[3] != 0 && plansza[4] != 0 && plansza[5] != 0 && plansza[6] != 0 && plansza[7] != 0 && plansza[8] != 0){
        plansza[9] = 3; // 3 - remis, brak wolnych pol
    }
    else{
        if(plansza[0] == player && plansza[1] == player && plansza[2] == player) plansza[9] = player; // poziomo 1
        else if(plansza[3] == player && plansza[4] == player && plansza[5] == player) plansza[9] = player; // poziomo 2
        else if(plansza[6] == player && plansza[7] == player && plansza[8] == player) plansza[9] = player; // poziomo 3
        else if(plansza[0] == player && plansza[3] == player && plansza[6] == player) plansza[9] = player; // pion 1
        else if(plansza[1] == player && plansza[4] == player && plansza[7] == player) plansza[9] = player; // pion 2
        else if(plansza[2] == player && plansza[5] == player && plansza[8] == player) plansza[9] = player; // pion 3
        else if(plansza[0] == player && plansza[4] == player && plansza[8] == player) plansza[9] = player; // skos 1
        else if(plansza[2] == player && plansza[4] == player && plansza[6] == player) plansza[9] = player; // skos 2
        }
}

void sprawdz_wynik(){
    if(plansza[9] == 1 && strcmp(playername,"Gracz1") == 0){
        printf("\n\n Wybrales!! \n\n");
        posprzataj();
    }
    else if(plansza[9] == 1 && strcmp(playername,"Gracz2") == 0){
        printf("\n\n Przegrales!! Wygral Gracz 1 \n\n");
        posprzataj();
    }
    else if(plansza[9] == 2 && strcmp(playername,"Gracz2") == 0){
        printf("\n\n Wybrales!! \n\n");
        posprzataj();
    }
    else if(plansza[9] == 2 && strcmp(playername,"Gracz1") == 0){
        printf("\n\n Przegrales!! Wygral Gracz 1 \n\n");
        posprzataj();
    }
    else if(plansza[9] == 3){
        printf("\n\n Remis!! \n\n");
        posprzataj();
    }
}
int main()
{
    intro();

    if((memory = shmget(key,sizeof(int)*10,IPC_CREAT|IPC_EXCL|0777)) == -1){
        if((memory = shmget(key,sizeof(int)*10,0)) == -1){
            printf("\nNie mozna polaczyc z gra - blad pamieci wspoldzielonej!\n");
            exit(1);
        }
        else{
            printf("\nTwoja nazwa gracza: ");
        }
    }
    else{
        printf("\nTowja nazwa gracza: ");
    }

    semafors = semget(key,2,0777|IPC_CREAT|IPC_EXCL);

    if(semafors == -1){
        semafors = semget(key,2,0);
        playername = "Gracz2";
        printf("Gracz2 - 'X'\n");
    }
    else{
        playername = "Gracz1";
        printf("Gracz1 - 'O'\n");
    }

    shm = shmat(memory,0,0);
    kopiuj_do_pamieci();

    if(strcmp(playername,"Gracz1") == 0){
        semctl(semafors,sem1,SETVAL,0);
        semctl(semafors,sem2,SETVAL,1);
        if(ruch(Gracz1) == 0){
            system("clear");
            kopiuj_do_pamieci();
            rysuj_plansze();
            while(1){
                printf("\nOczekiwanie na ruch Gracza2\n");
                semop(semafors,&Gracz2_lock,1);
                system("clear");
                kopiuj_z_pamieci();
                rysuj_plansze();
                sprawdz_wynik();
                if(ruch(Gracz1) == 0){
                    system("clear");
                    sprawdz_plansze(Gracz1);
                    kopiuj_do_pamieci();
                    rysuj_plansze();
                    sprawdz_wynik();
                }
                semop(semafors,&Gracz2_unlock,1);
            }
        }
    }
    else{
        printf("\nOczekiwanie na ruch Gracza1 \n");
        while(1){
            kopiuj_z_pamieci();
            if(czy_juz() == 0){
                while(1){
                    printf("\nOczekiwanie na ruch Gracza1\n");
                    semop(semafors,&Gracz1_lock,1);
                    system("clear");
                    kopiuj_z_pamieci();
                    rysuj_plansze();
                    sprawdz_wynik();
                    if(ruch(Gracz2) == 0){
                        system("clear");
                        sprawdz_plansze(Gracz2);
                        kopiuj_do_pamieci();
                        rysuj_plansze();
                        sprawdz_wynik();
                    }
                    semop(semafors,&Gracz1_unlock,1);
                }
            }
        }
    }

   return 0;
}
