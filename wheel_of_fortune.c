#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



typedef struct node* link;
struct node{
  int data;
  link previous, next;
};
link head = NULL;
link t = NULL;

void printList();                          //function for printing the list
void put(int data);                        //insert data 
void qInit();                              //create new node
void make();                               //create the weel
int words();                               //return an integer that maps to a word 
void game();                               //initialize the game


int main(){

  srand(time(NULL));
  game();

  return 0;
}

void printList(){
  link tmp = (link)malloc(sizeof(link));
  tmp = head->next;
  while (tmp != head){
    if(tmp->data == 0)
      printf("Bankruptcy (you also lose your turn).\n");
    else if(tmp->data == 4)
      printf("You lose your turn.\n");
    else if(tmp->data == 15)
      printf("You take the next player's money.\n");
    else if(tmp->data == 17)
      printf("You have one more chance to choose a letter (if you guess wrong you do not lose your turn, but you earn no money).\n");
    else if(tmp->data == 19)
      printf("You lose your turn. All players lose half their money.\n");
    else
      printf("%d\n", tmp->data);

    tmp = tmp->next;
  }
}

void put(int data){
  link new = (link)malloc(sizeof(link));
  new->next = head;
  new->previous = head->previous;
  head->previous = new;
  new->previous->next = new;
  new->data = data;
}

void qInit(){
  head = (link)malloc(sizeof(link));
  head->next = head;
  head->previous = head;
}

void make(){
  int i = 0;
  qInit();
  int testValue = 10;
  for(i = 0; i < 24; i++){

    if(i == 0 || i == 11)                     //if i = 0 or i = 11  we have bankruptcy
      put(0);
    else if(i == 4)                           //if i = 4 rule 1
      put(4);
    else if(i == 15)                          //if i = 15 rule 3
      put(15);
    else if(i == 17)                          //if i = 17 rule 4
      put(17);
    else if(i == 19)
      put(19);
    else{
      put(testValue);
      testValue += 10;
    }
  }
}

int words(){
  int k = 0, m = 0;
  printf("Choose a number from 1 to 3 for the word to be chosen: ");
  while(m == 0){
    scanf("%d", &k);
    if(k < 1 || k > 3)
      printf("Choose again: ");
    else{
      printf("\nWord has been chosen.");
      m = 1;
    }
  }
  printf("\n");
  return k;
}


void game(){

  make();

  struct player{
    int money;
    char* name;
  };
  struct player players[3];

  int firstPlayer = 0, pos = 0;                                 //for the player who starts first, for the position on the wheel
  int direction = 0;                                            //wheel direction
  int i = 0, k = 0;                                             
  int w = 0, x = 0;
  int count;
  char *word, tmpChar, *wholeWord;                              //pointer for word, for temporary letter, for the completed word




  for (i = 0; i < 3; i++)                                       //money init;
    players[i].money = 0;

  players[0].name = "Me";
  players[1].name = "You";
  players[2].name = "They";

  printf("Welcome to the 'Wheel of Fortune'!!! \n");
  printf("Here comes the weel: \n");
  printList();
  printf("\n");

  w = words();
  if (w == 1)
    word = "apple";
  else if (w == 2)
    word = "ostrich";
  else
    word = "ecorp";

  char tmpWord[strlen(word)];
  for (i = 0; i < strlen(word); i++)                              //init for the empty string, representing the word
    tmpWord[i] = '_';

  firstPlayer = rand() % 3;                                       //for which player is going to start first

  if(firstPlayer == 0)
    printf("Your turn: Me \n");
  else if(firstPlayer == 1)
    printf("Your turn: You \n");
  else if(firstPlayer == 2)
    printf("Your turn: They \n");

  pos = rand() % 24;                                              //to find where the pointer is going to point on the wheel in the beginning

  t = (link)malloc(sizeof(link));
  t = head;
  for (i = 0; i <= pos; i++)                                      //the wheel is pointing at a random position
    t = t->next;



  while(k == 0){
    printf("Below is the word you have to guess: ");
    for(i = 0; i < strlen(tmpWord); i++){
      if(i == strlen(tmpWord) - 1)
        printf("%c \n", tmpWord[i]);
      else
        printf("%c ", tmpWord[i]);
    }

    pos = rand() % 24;

    printf("Choose between 'clockwise' and 'counterclockwise'. \n");
    printf("For 'clockwise' type '0', for 'counterclockwise' type '1'. \n");
    scanf("%d", &direction);
    while(1){
      if(direction != 0 && direction != 1){
        printf("Choose again... \n");
        scanf("%d", &direction);
      }
      else{
        if(direction == 0){

          for(i = 0; i <= pos; i++)
            t = t->previous;

          if(t->data == 0)
            printf("Bankruptcy (you also lose your turn).\n");
          else if(t->data == 4)
            printf("You lose your turn.\n");
          else if(t->data == 15)
            printf("You take the next player's money.\n");
          else if(t->data == 17)
            printf("You have one more chance to choose a letter (if you guess wrong you do not lose your turn, but you earn no money).\n");
          else if(t->data == 19)
            printf("You lose your turn. All players lose half their money.\n");
          else
            printf("%d\n", t->data);

          break;
        }
        else { 

          for(i = 0; i <= pos; i++)
            t = t->next;

          if(t->data == 0)
            printf("Bankruptcy (you also lose your turn).\n");
          else if(t->data == 4)
            printf("You lose your turn.\n");
          else if(t->data == 15)
            printf("You take the next player's money.\n");
          else if(t->data == 17)
            printf("You have one more chance to choose a letter (if you guess wrong you do not lose your turn, but you earn no money).\n");
          else if(t->data == 19)
            printf("You lose your turn. All players lose half their money.\n");
          else
            printf("%d\n", t->data);

          break;
        }
      }
    }
    count = 0;

    if(t->data != 0 && t->data != 4 && t->data != 15 && t->data != 19){

      if(t->data == 17){                                                                         //if the player is at this node
        printf("You can chose any letter you want. ");                                      	 //we have the rule 4
        printf("If you guess wrong you do not lose your turn, but you earn no money.\n");
      }

      if(t->data != 17){
        players[firstPlayer].money += t->data;
      }
      printf("You have: %d¥ \n", players[firstPlayer].money);
      getchar();
      printf("Choose a letter (only consonant). \n");
      scanf("%c", &tmpChar);
      getchar();

      for(i = 0; i < strlen(word); i++){
        if(word[i] == tmpChar){
          tmpWord[i] = tmpChar;
          count++;
        }
      }

      if(count > 0){
        for(i = 0; i < strlen(tmpWord); i++){
          if(i == strlen(tmpWord) - 1)
            printf("%c\n", tmpWord[i]);
          else
            printf("%c ", tmpWord[i]);
        }
      }

      if(count > 0){
        printf("Choose a vowel too.\n");
        scanf("%c", &tmpChar);
        for(i = 0; i < strlen(word); i++){
          if(word[i] == tmpChar){
            tmpWord[i] = tmpChar;
            count = -5;
          }
        }
        if(count != -5){
          if(firstPlayer == 0){
            firstPlayer++;
            printf("It's their turn: You\n");
          }
          else if(firstPlayer == 1){
            firstPlayer++;
            printf("It's their turn: They\n");
          }
          else{
            firstPlayer = 0;
            printf("It's their turn: Me\n");
          }
        }
      }
      else if(count == 0 && t->data != 17){
        if(firstPlayer == 0){
          firstPlayer++;
          printf("It's their turn: You\n");
        }
        else if(firstPlayer == 1){
          firstPlayer++;
          printf("It's their turn: They\n");
        }
        else{
          firstPlayer = 0;
          printf("It's their turn: Me\n");
        }
      }

      if(count > 0 || count == -5){
        for(i = 0; i < strlen(tmpWord); i++){
          if(i == strlen(tmpWord) - 1)
            printf("%c\n", tmpWord[i]);
          else
            printf("%c ", tmpWord[i]);
        }
      }

      if(count == -5){
        printf("Do you want to guess the whole word or play again?\n");
        printf("Type '1' for guessing and '2' for playing...\n");
        scanf("%d", &x);
        while(1){
          if(x != 1 && x != 2){
            printf("Type again...\n");
            scanf("%d", &x);
          }
          else{
            if(x == 1){
              printf("Guess the word: ");
              wholeWord = (char *)malloc(sizeof(char)*strlen(word));
              getchar();
              fgets(wholeWord,strlen(word) + 1,stdin);
              printf("%s\n",wholeWord);

              if(strcmp(word, wholeWord) == 0){
                printf("Congratulations, you guessed it! You won: %d¥ \n", players[firstPlayer].money);
                k = 1;
              }
              else{
                if(firstPlayer == 0){
                  firstPlayer++;
                  printf("It's their turn: Me\n");
                }
                else if(firstPlayer == 1){
                  firstPlayer++;
                  printf("It's their turn: They\n");
                }
                else{
                  firstPlayer = 0;
                  printf("It's their turn: You\n");
                }
              }
            }
            else
              printf("Keep going... \n");

            break;
          }
        }
      }
    }
    else if(t->data == 0){                                                      //o kanonas ths xreokopoias
      printf("The wheel decided bankruptcy. ");
      printf("You lose all your money... \n");
      players[firstPlayer].money = 0;

      if(firstPlayer == 0){
        firstPlayer++;
        printf("It's their turn: You\n");
      }
      else if(firstPlayer == 1){
        firstPlayer++;
        printf("It's their turn: They\n");
      }
      else{
        firstPlayer = 0;
        printf("It's their turn: Me\n");
      }
    }
    else if(t->data == 4){
      printf("You lose your turn, but you keep your money.\n");
      if(firstPlayer == 0){
        firstPlayer++;
        printf("It's their turn: You\n");
      }
      else if(firstPlayer == 1){
        firstPlayer++;
        printf("It's their turn: They\n");
      }
      else{
        firstPlayer = 0;
        printf("It's their turn: Me\n");
      }
    }
    else if(t->data == 15){
      printf("Next player's money is yours.\n");
      if(firstPlayer == 0)
        players[firstPlayer].money += players[1].money;
      else if(firstPlayer == 1)
        players[firstPlayer].money += players[2].money;
      else
        players[firstPlayer].money += players[0].money;
    }
    else if(t->data == 19){                                                                  //if the player is at this node
      printf("You lose your turn. All players lose half their money.\n");        			 //the player loses its turn
      for(i = 0; i < 3; i++){                                                                //and all players lose half their money
        players[i].money = players[i].money * 0.5;
      }
      if(firstPlayer == 0){
        firstPlayer++;
        printf("It's their turn: You\n");
      }
      else if(firstPlayer == 1){
        firstPlayer++;
        printf("It's their turn: They\n");
      }
      else{
        firstPlayer = 0;
        printf("Σειρά του παίκτη: Egw \n");
      }
    }
  }
}
