#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


const int R = 3;   //costante per le RIGHE
const int C = 3;   //costante per le COLONNE
const char VUOTO = '-';



int charToInt(int input){
     return input - '0';
}


int checkCasella(char plancia[R][C], int riga, int colonna, int turno){

     if(turno){
          if(plancia[riga][colonna] == 'O'){
               printf("Casella occupata!\n\n");
               return 0;
          }else{
               return 1;
          }
     }else{
          if(plancia[riga][colonna] == 'X'){
               printf("Casella occupata!\n\n");
               return 0;
          }else{
               return 1;
          }
     }
}


int checkWin(char plancia[R][C], int turno){

     int win = 0;

     if(turno == 0){
          if(((plancia[0][0] == 'X') &&
              (plancia[1][0] == 'X') &&
              (plancia[2][0] == 'X'))||

             ((plancia[0][1] == 'X') &&
              (plancia[1][1] == 'X') &&
              (plancia[2][1] == 'X')) ||

             ((plancia[0][2] == 'X') &&
              (plancia[1][2] == 'X') &&
              (plancia[2][2] == 'X')) ||

             ((plancia[0][0] == 'X') &&
              (plancia[0][1] == 'X') &&
              (plancia[0][2] == 'X')) ||

             ((plancia[1][0] == 'X') &&
              (plancia[1][1] == 'X') &&
              (plancia[1][2] == 'X'))||

             ((plancia[2][0] == 'X') &&
              (plancia[2][1] == 'X') &&
              (plancia[2][2] == 'X'))||

             ((plancia[0][0] == 'X') &&
              (plancia[1][1] == 'X') &&
              (plancia[2][2] == 'X'))||

             ((plancia[0][2] == 'X') &&
              (plancia[1][1] == 'X') &&
              (plancia[2][0] == 'X'))){
               win = 1;
          }
     }else{
                if(((plancia[0][0] == 'O') &&
                    (plancia[1][0] == 'O') &&
                    (plancia[2][0] == 'O'))||

                 ((plancia[0][1] == 'O') &&
                    (plancia[1][1] == 'O') &&
                    (plancia[2][1] == 'O')) ||

                 ((plancia[0][2] == 'O') &&
                    (plancia[1][2] == 'O') &&
                    (plancia[2][2] == 'O')) ||

                 ((plancia[0][0] == 'O') &&
                    (plancia[0][1] == 'O') &&
                    (plancia[0][2] == 'O')) ||

                 ((plancia[1][0] == 'O') &&
                    (plancia[1][1] == 'O') &&
                    (plancia[1][2] == 'O'))||

                 ((plancia[2][0] == 'O') &&
                    (plancia[2][1] == 'O') &&
                    (plancia[2][2] == 'O'))||

                 ((plancia[0][0] == 'O') &&
                    (plancia[1][1] == 'O') &&
                    (plancia[2][2] == 'O'))||

                 ((plancia[0][2] == 'O') &&
                    (plancia[1][1] == 'O' )&&
                    (plancia[2][0] == 'O'))){
                      win = 1;
               }
         }
         return win;
}


/*FUNZIONE CHE CONTROLLA SE NON SI È RIEMPITA LA PLANCIA*/
int checkGameOver(char plancia[R][C]){

     int check = 0;

     for(int i = 0 ; i < R; i++){
          for(int j = 0; j < C; j++){
               if(plancia[i][j] == VUOTO){
                    check = 1;
               }
          }
     }
     return check;
}

/*FUNZIONE CHE OTTIENE L'INDICE DELLE COLONNE*/
int mossaColonna(char plancia[R][C],char *Giocatore){

     int conversione = 0;

     while(1){
          printf("Colonna == ");
          char inputC = getchar();
          while ((getchar()) != '\n');

          if(isalpha(inputC)){
               printf("Non puoi inserire caratteri! Riprova!\n\n");
               continue;
          }

          conversione = charToInt(inputC);

          if(conversione < 1 || conversione > 3){
               printf("Indice invalido! Riprova!\n\n");
               continue;
          }else{
               break;
          }
     }
     printf("Mossa fatta... \n");
     return conversione - 1;
}

/*FUNZIONE CHE OTTIENE L'INDICE DELLE RIGHE*/
int mossaRiga(char plancia[R][C],char *Giocatore){

     int conversione = 0;

     printf("Che mossa vuoi fare %s?\n", Giocatore);

     while(1){
          printf("Riga == ");
          char inputR = getchar();
          while ((getchar()) != '\n');

          if(isalpha(inputR)){
               printf("Non puoi inserire caratteri! Riprova!\n\n");
               continue;
          }

          conversione = charToInt(inputR);

          if(conversione < 1 || conversione > 3){
               printf("Indice invalido! Riprova!\n\n");
               continue;
          }else{
               break;
          }
     }
     return conversione - 1;
}

/*FUNZIONE CHE RIEMPIE LA PLANCIA CON '-' */
void riempiPlancia(char plancia[R][C]){

     for(int i = 0 ; i < R; i++){
          for(int j = 0; j < C; j++){
               plancia[i][j] = VUOTO;
          }
     }
}

/*FUNZIONE CHE STAMPA LA PLANCIA CON IL NOME DI CHI HA FATTO LA MOSSA*/
void stampaPlancia(char plancia[R][C], char *Giocatore){

     printf("\n----%s----\n\n", Giocatore);
     printf("* |   1    2    3\n");
     printf("-----------------\n");
     for(int i = 0 ; i < R; i++){
          printf("%d |", i + 1);
          for(int j = 0; j < C; j++){
               printf("%4c ", plancia[i][j]) ;
          }
          printf("\n\n");
     }
}


/*FUNZIONE DOVE IL GIOCO INIZIA */
void giocoTris(){

     char plancia[R][C];                 //creazione plancia di gioco
     char Giocatore1[30],Giocatore2[30];
     int riga,colonna;
     int turno = 1;
     int Gameover = 0;

     printf("\n\n---------------------------\n");
     printf("|         TRIS            |\n");
     printf("---------------------------\n\n");

     printf("INSERITE I VOSTRI NOMI!\n");

     printf("Nome Giocatore1: ");
     fgets(Giocatore1, 30, stdin);
     (Giocatore1)[strlen(Giocatore1)-1] = '\0';

     printf("Nome Giocatore2: ");
     fgets(Giocatore2, 30, stdin);
     (Giocatore2)[strlen(Giocatore2)-1] = '\0';

     riempiPlancia(plancia);   //riempimento plancia (vuota)


     /*STAMPA PLANCIA DI GIOCO*/
     printf("\n* |   1    2    3\n");
     printf("-----------------\n");
     for(int i = 0 ; i < R; i++){
          printf("%d |", i + 1);
          for(int j = 0; j < C; j++){
               printf("%4c ", plancia[i][j]) ;
          }
          printf("\n\n");
     }

     /*IL LOOP DEL GIOCO */
     while(!Gameover){
          if(turno){
               if(checkGameOver(plancia)){
                    while(1){
                         riga = mossaRiga(plancia, Giocatore1);
                         colonna = mossaColonna(plancia, Giocatore1);

                         if(checkCasella(plancia, riga, colonna, turno)){
                              plancia[riga][colonna] = 'X';
                              break;
                         }
                    }

                    stampaPlancia(plancia,Giocatore1);
                    turno--;

                    if(checkWin(plancia,turno)){
                         printf("---Hai vinto %s---", Giocatore1);
                         break;
                    }
                    continue;
               }else{
                    printf("GAMEOVER PAREGGIO!");
                    Gameover = 1;
               }
          }else{
               if(checkGameOver(plancia)){
                    while(1){
                         riga = mossaRiga(plancia, Giocatore2);
                         colonna = mossaColonna(plancia, Giocatore2);

                         if(checkCasella(plancia, riga, colonna, turno)){
                              plancia[riga][colonna] = 'O';
                              break;
                         }
                    }

                    stampaPlancia(plancia,Giocatore2);
                    turno++;

                    if(checkWin(plancia,turno)){
                         printf("---Hai vinto %s---", Giocatore2);
                         break;
                    }
                    continue;
               }else{
                    printf("GAMEOVER PAREGGIO!");
                    Gameover = 1;
               }
          }
     }
}


/*FUNZIONE MAIN*/
int main(int argc, char const *argv[]) {
     giocoTris();
     return 0;
}
