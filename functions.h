#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int validateCard(card *c){

    if(!c||c==NULL)return 1;

    FILE *file;
    file = fopen("cards.txt","r");
    
    bool wasFoundInCards=false;
    bool wasInCancelled=false;

    char str[100];
    while(fgets(str,100,file)){
        if(str[0] == c->id){
            wasFoundInCards = true;
            break;
        }
    }

    fclose(file);

    file = fopen("cancelled.txt","r");
    while(fgets(str,100,file)){
        if(str[0] == c->id){
            wasInCancelled=true;
            return 1;
        }
    }

    return 0;
}

int deposit(double amount,card *c){
    int isValid = validateCard(c);

    if(isValid == 1){
        printf("Invalid/Cancelled card.");
        return 1;
    }

    
}
int withdraw(double amount, card *c);

card createCard(char bogOrTBC,int age,int pin);

void activateCard(int id);
void deactivateCard(int id);

void changePin(card *c,int oldPin,int newPin);

void cancelCard(card *c);