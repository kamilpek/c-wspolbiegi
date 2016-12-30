#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define key 30 // Klucz IPC
#define sem1 0 // sem1 - semafor dla Player1
#define sem2 1 // sem2 - semafor dla Player2

/*########## ZMIENNE ##########*/
int memory;
int semafors;
int plansza[9] = {0,0,0,0,0,0,0,0,0}; // pola 0-8 to stan planszy, pole 9 to wynik rundy - moze miec warotsc: 0(pusto), 1(Player1), 2(Player2), 3(remis)
char *playername;
int player1 = 1; // identyfiaktor dla Player1
int player2 = 2; // identyfiaktor dla Player2
int *shm;        // shm = shared memory

/*########## OPERACJE NA SEMAFORACH ##########*/
struct sembuf player1_lock = {sem2,-1,0};  // Zablokuj Playera nr 1
struct sembuf player1_unlock = {sem1,1,0}; // Odblokuj Playera nr 1
struct sembuf player2_lock = {sem1,-1,0};  // Zablokuj Playera nr 2
struct sembuf player2_unlock = {sem2,1,0}; // Odblokuj Playera nr 2


/*########## FUNKCJA WYSWIETLAJACA INTRO ##########*/
void intro(){
    system("clear");
    printf("\n#######################################\n\n");
    printf("\t=== TIC TAC TOE ===\n");
    printf("\n#######################################\n\n");
}
/*########## FUNKCJA SPRAWDZAJĽCA POPRAWNOŚĆ RUCHU GRACZA ##########*/
int ruch(int player){
    int pole;
    int status = 1;
    while(status == 1){
        printf("\nEnter field number[1-9]: ");
        scanf("%d",&pole);
        if(pole < 10 && pole > 0 ){
            if(plansza[pole-1] == 0){
                plansza[pole-1] = player;
                status = 0;
                return 0;
            }
            else{
                printf("\n\n=== Field is already full!!! ===\n");
                status = 1;
            }
        }
        else{
            printf("\n\n=== Wrong field number!!! ===\n");
            status = 1;
        }
    }
}
/*########## FUNKCJA SPRZATAJĽCA PO ROZGRYWCE - USUWA PRZYDZIELONĽ PAMIĘĆ I SEMAFORY ##########*/
void posprzataj(){
    semctl(semafors,0,IPC_RMID,0);
    shmdt(shm);
    shmctl(memory,IPC_RMID,0);
    exit(0);
}
/*########## FUNKCJA SPRAWDZAJĽCA CZY PLAYER1 ZROBIL JUZ PIERWSZY RUCH ##########*/
int czy_juz(){
    int i = 0;
    if(plansza[0] == 0 && plansza[1] == 0 && plansza[2] == 0 && plansza[3] == 0 && plansza[4] == 0 && plansza[5] == 0 && plansza[6] == 0 && plansza[7] == 0 && plansza[8] == 0){
        return 1;
    }
    else{
        return 0;
    }
}
/*########## FUNKCJA KOPIUJĽCA STAN GRY DO PAMIĘCI ##########*/
void kopiuj_do_pamieci(){
    int counter = 0;
    for(counter;counter<10;counter++){
        shm[counter] = plansza[counter];
    }
}
/*########## FUNKCJA KOPIUJĽCA STAN GRY Z PAMIĘCI ##########*/
void kopiuj_z_pamieci(){
    int counter = 0;
    for(counter;counter<10;counter++){
        plansza[counter] = shm[counter];
    }
}
/*########## FUNKCJA RYSUJĽCA PLANSZE NA PODSTAWIE STANU GRY ##########*/
void rysuj_plansze(){
    int i = 0;
    int k = 0;
    printf("\n");
    while(k<9){
        for(i;i<3;i++){
            int j = 0;
            for(j;j<3;j++){
                if(plansza[k] == 0){ // jesli 0, to pole jest puste
                    printf("  ");
                }
                if(plansza[k] == 1){ // jesli 1, to wstaw O - zawsze Player1
                    printf(" O");
                }
                if(plansza[k] == 2){ // jesli 2, to wstaw X - zawsze Player2
                    printf(" X");
                }
                if(j==0 || j==1){
                    printf(" |");
                }
                k++;
            }
            if(i==0 || i==1){
                printf("\n-----------\n");
            }
        }
    }
    printf("\n\n");
}
/*########## FUNKCJA SPRAWDZAJĄCA PLANSZE, W POSZUKIWANIU WYGRANEJ LUB REMISU ##########*/
void sprawdz_plansze(int player){
    if(plansza[0] != 0 && plansza[1] != 0 && plansza[2] != 0 && plansza[3] != 0 && plansza[4] != 0 && plansza[5] != 0 && plansza[6] != 0 && plansza[7] != 0 && plansza[8] != 0){
        plansza[9] = 3; // 3 oznacza remis - brak wolnych pól i nikt nie wygrał
    }
    else{
        if(plansza[0] == player && plansza[1] == player && plansza[2] == player){        // poziom 1
            plansza[9] = player;
        }
        else if(plansza[3] == player && plansza[4] == player && plansza[5] == player){ // poziom 2
            plansza[9] = player;
        }
        else if(plansza[6] == player && plansza[7] == player && plansza[8] == player){ // poziom 3
            plansza[9] = player;
        }
        else if(plansza[0] == player && plansza[3] == player && plansza[6] == player){ // pion 1
            plansza[9] = player;
        }
        else if(plansza[1] == player && plansza[4] == player && plansza[7] == player){ // pion 2
            plansza[9] = player;
        }
        else if(plansza[2] == player && plansza[5] == player && plansza[8] == player){ // pion 3
            plansza[9] = player;
        }
        else if(plansza[0] == player && plansza[4] == player && plansza[8] == player){ // skos 1
            plansza[9] = player;
        }
        else if(plansza[2] == player && plansza[4] == player && plansza[6] == player){ // skos 2
            plansza[9] = player;
        }
    }
}
/*########## FUNKCJA PRZERYWAJĽCA ROZGRYWKE W PRZYPADKU WYGRANEJ LUB REMISU ##########*/
void sprawdz_wynik(){
    if(plansza[9] == 1 && strcmp(playername,"Player1") == 0){             // Jesli wygrał Player1, a my jesteśmy Player1
        printf("\n\n====== Congratulations!!! You win!! ======\n\n");
        posprzataj();
    }
    else if(plansza[9] == 1 && strcmp(playername,"Player2") == 0){        // Jesli wygrał Player1, a my jesteśmy Player2
        printf("\n\n====== You loose!! Player1 win!! ======\n\n");
        posprzataj();
    }
    else if(plansza[9] == 2 && strcmp(playername,"Player2") == 0){        // Jesli wygrał Player2, a my jesteśmy Player2
        printf("\n\n====== Congratulations!!! You win!! ======\n\n");
        posprzataj();
    }
    else if(plansza[9] == 2 && strcmp(playername,"Player1") == 0){        // Jesli wygrał Player2, a my jesteśmy Player1
        printf("\n\n====== You loose!! Player2 win!! ======\n\n");
        posprzataj();
    }
    else if(plansza[9] == 3){                                             // Jesli jest remis i nikt nie wygrał
        printf("\n\n====== Nobody win!! ======\n\n");
        posprzataj();
    }
}
int main()
{
    intro();

    /* Wydzielamy pamiec wspoldzielona */
    if((memory = shmget(key,sizeof(int)*10,IPC_CREAT|IPC_EXCL|0777)) == -1){ // Jeśli nie istnieje, próbujemy ją utowrzyć
        if((memory = shmget(key,sizeof(int)*10,0)) == -1){ // Jeśli pamięć juz istnieje i powyzsza funkcja zwróciła błąd, próbujemy sie od niej podłączyc
            printf("\nCan't connect to game - shared memory error!!!\n");
            exit(1);
        }
        else{
            printf("\n=== Your playername: ");
        }
    }
    else{
        printf("\n=== Your playername: ");
    }

    /* Tworzymy 2 semafory*/
    semafors = semget(key,2,0777|IPC_CREAT|IPC_EXCL);

    /* Jesli semafory istnieja, tzn. ze jestesmy Player2 */
    if(semafors == -1){
        semafors = semget(key,2,0); // Przyłaczamy sie do istniejacych semaforów jeli okzało sie, że jestemy Player2
        playername = "Player2";
        printf("Player2 - 'X' ===\n");
    }
    else{
        playername = "Player1";
        printf("Player1 - 'O' ===\n");
    }

    /* Łšczymy współdzielonš pamiec z programem */
    shm = shmat(memory,0,0);

   /* Kopiujemy pustš plansze do pamieci */
    kopiuj_do_pamieci();

   /* Sprawdzamy ktorym playerem jestesmy */
    if(strcmp(playername,"Player1") == 0){
        /* Jesli jestesmy Player1 inicjalizujemy semafory*/
        semctl(semafors,sem1,SETVAL,0); // Ustawiamy semafor dla Player1 na zamkniety
        semctl(semafors,sem2,SETVAL,1); // Ustawiamy semafor dla Player2 na otwarty
        /* Zaczynamy gre */
        if(ruch(player1) == 0){          // Robimy pierwszy ruch
            system("clear");                    // Systemowe wywołanie 'clear'
            kopiuj_do_pamieci();
            rysuj_plansze();
            while(1){
                printf("\nWaiting for Player2 move...\n");
                semop(semafors,&player2_lock,1);    // Otrzymujemy dostep do pamieci - blokujemy Player2
                system("clear");
                kopiuj_z_pamieci();
                rysuj_plansze();
                sprawdz_wynik();
                if(ruch(player1) == 0){
                    system("clear");
                    sprawdz_plansze(player1);
                    kopiuj_do_pamieci();
                    rysuj_plansze();
                    sprawdz_wynik();
                }
                semop(semafors,&player2_unlock,1);    // Wykonalismy ruch, zwalniamy dostep do pamieci - odblokowujemy Player2
            }
        }
    }
    else{
        /* Jesli jestesmy Player2 */
        printf("\nWaiting for Player1 move...\n");
        while(1){
            kopiuj_z_pamieci();
            if(czy_juz() == 0){                                 // Sprawdzamy funkcję czy_juz(), czy Player1 wykonał pierwszy ruch
                while(1){
                    printf("\nWaiting for Player1 move...\n");
                    semop(semafors,&player1_lock,1); // Otrzymujemy dostep do pamieci - blokujemy Player1
                    system("clear");
                    kopiuj_z_pamieci();
                    rysuj_plansze();
                    sprawdz_wynik();
                    if(ruch(player2) == 0){
                        system("clear");
                        sprawdz_plansze(player2);
                        kopiuj_do_pamieci();
                        rysuj_plansze();
                        sprawdz_wynik();
                    }
                    semop(semafors,&player1_unlock,1); // Wykonalismy ruch, zwalniamy dostep do pamieci - odblokowujemy Player1
                }
            }
        }
    }

   return 0;
} 
