#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const int R = 10;
const int C = 10;

int charToInt(int input){
     return input - '0';
}

int checkAvversario(char board[R][C], int riga, int colonna){

     if(board[riga][colonna] == '#'){
          return 1;
     }
     return 0;
}

int checkCasella(char board[R][C], int riga, int colonna){

     if(board[riga][colonna] == '#'){
          printf("Casella già occupata da una nave, Riprova!");
          return 1;
     }
     return 0;
}

int mossaColonna(char plancia[R][C]){

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

          if(conversione < 0 || conversione > 9){
               printf("Indice invalido! Riprova!\n\n");
               continue;
          }else{
               break;
          }
     }
     printf("Mossa fatta... \n");
     return conversione;
}


int mossaRiga(char board[R][C], char *nome){
     int conversione = 0;

     printf("Che mossa vuoi fare %s?\n", nome);

     while(1){
          printf("Riga == ");
          char inputR = getchar();
          while ((getchar()) != '\n');

          if(isalpha(inputR)){
               printf("Non puoi inserire caratteri! Riprova!\n\n");
               continue;
          }

          conversione = charToInt(inputR);

          if(conversione < 0 || conversione > 9){
               printf("Indice invalido! Riprova!\n\n");
               continue;
          }else{
               break;
          }
     }
     return conversione;
}

void printboard(char board[R][C], char* nome){

     printf("\n\n                 -----%s----\n\n", nome);
     printf("*  |   0   1   2   3   4   5   6   7   8   9\n");
     printf("---------------------------------------------\n\n");

     for(int i = 0; i<R; i++){
          printf("%d  |",i);
          for(int j = 0 ; j<C; j++){
               printf("%4c", board[i][j]);
          }
          printf("\n\n");
     }
}

int attack(char campoGuerra[R][C], char board[R][C], char *nome){

     int riga, colonna;
     int sbagliato = 0;
     int affondate = 0;
     int mosse = 1;

          while(mosse != 11){
               printboard(campoGuerra,nome);
               riga = mossaRiga(campoGuerra,nome);
               colonna = mossaColonna(campoGuerra);

               if(checkAvversario(board,riga,colonna)){
                    printf("PRESA!\n\n");
                    affondate++;
                    campoGuerra[riga][colonna] = '=';
               }else{
                    printf("SPLASH!\n\n");
                    campoGuerra[riga][colonna] = '0';
               }
               mosse++;
          }
     return affondate;
}


void setupBoard(char board[R][C], char *nome){

     int FineTurno = 1;
     int riga , colonna;

     printboard(board,nome);
     printf("\n\nFAI LE TUE MOSSE %s!\n\n", nome);

     while(FineTurno != 11){
          riga = mossaRiga(board,nome);
          colonna = mossaColonna(board);

          if(checkCasella(board,riga,colonna)){
               continue;
          }

          board[riga][colonna] = '#';

          printboard(board,nome);
          FineTurno++;
     }
}

void fillBoard(char board[R][C]){

     for(int i = 0; i < R; i++){
          for(int j = 0 ; j < C; j++){
               board[i][j] = '-';
          }
     }
}


void giocoNavale(){
     char board1[R][C], board2[R][C];
     char campoGuerra1[R][C],campoGuerra2[R][C];
     char Giocatore1[40], Giocatore2[40];

     printf("\n\n|---------------------------------------------------|\n\n");
     printf("|                BATTAGLIA NAVALE                   |\n\n");
     printf("|---------------------------------------------------|\n\n");

     printf("INSERITE I VOSTRI NOMI!\n");

     printf("Nome Giocatore1: ");
     fgets(Giocatore1, 40, stdin);
     (Giocatore1)[strlen(Giocatore1)-1] = '\0';

     printf("Nome Giocatore2: ");
     fgets(Giocatore2, 40, stdin);
     (Giocatore2)[strlen(Giocatore2)-1] = '\0';

     //SETUP BOARD
     fillBoard(board1);
     fillBoard(board2);
     fillBoard(campoGuerra1);
     fillBoard(campoGuerra2);

     setupBoard(board1, Giocatore1);
     setupBoard(board2, Giocatore2);

     //NAVI INTATTE
     int viteG1 = 10;
     int viteG2 = 10;

     //PARTE DI GIOCO DI ATTACCO
     printf("\n\nPROVA AD AFFONDARE LE NAVI AVVERSARIE\n\n");
     while(viteG1 > 0 && viteG2 > 0 ){
          viteG1 -= attack(campoGuerra1,board2,Giocatore1);
          viteG2 -= attack(campoGuerra2,board1,Giocatore2);
     }
     (viteG1) ? printf("Hai vinto %s", Giocatore1) :
                printf("hai vinto %s", Giocatore2);
}

int main(int argc, char const *argv[]) {

     giocoNavale();
     return 0;
}
