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

int replaceText(char textToReplace[100],char towhat[100],char fileName[50]){
    FILE *originalFile;
    FILE *writingFile;

    originalFile = fopen(fileName,"r+");
    writingFile= fopen("temp.txt","w+");

    if(originalFile == NULL || writingFile==NULL){
        printf("Something went wrong. Try again Later.");
        return 1;
    }

    char str[100];
    while(fgets(str,100,originalFile)){
        if(str==textToReplace){
            fprintf(writingFile,"%s\n",towhat);
        }else{
            fprintf(writingFile,"%s\n",str);
        }
    }

    fclose(originalFile);
    fclose(writingFile);

    originalFile = fopen(fileName,"w+");
    writingFile= fopen("temp.txt","r+");

    char str[100];
    while(fgets(str,100,writingFile)){
        if(strcmp(str,textToReplace)==0){
            fprintf(originalFile,"%s\n",towhat);
        }else{
            fprintf(originalFile,"%s\n",str);
        }
    }

    fclose(originalFile);
    fclose(writingFile);
}

int deposit(double amount,card *c){
    int isValid = validateCard(c);
    if(isValid == 1||!isValid||isValid==NULL){
        printf("Invalid/Cancelled card.");
        return 1;
    }

    char BANK[5];
    FILE *file;
    if(c->isBOG==true){
        strcpy(BANK,"BOG");
        file=fopen("bog.txt","a");
    }else{
        strcpy(BANK,"TBC");
        file=fopen("tbc.txt","a");
    }


    if(!file || file==NULL){
        printf("Something went wrong.");
        return 1;
    }

    char str[100];
    if(strcmp(BANK,"BOG")==0){
        while(fgets(str,100,file)){
            if(str[0]==c->bankOfGeorgia->id){
                char oldLine[100],newLine[100];
                sprintf(oldLine,"%d. %s - %f$ | %d | status: ",c->bankOfGeorgia->id,c->bankOfGeorgia->cardHolderName,c->bankOfGeorgia->balance,c->bankOfGeorgia->pin,c->isActive);
                sprintf(newLine,"%d. %s - %f$ | %d | status: ",c->bankOfGeorgia->id,c->bankOfGeorgia->cardHolderName,c->bankOfGeorgia->balance+amount,c->bankOfGeorgia->pin,c->isActive);
                replaceText(oldLine,newLine,"bog.txt");
            }
        }
    }else{
        while(fgets(str,100,file)){
            if(str[0]==c->Tbc->id){
                char oldLine[100],newLine[100];
                sprintf(oldLine,"%d. %s - %f$ | %d | status: ",c->Tbc->id,c->Tbc->cardHolderName,c->Tbc->balance,c->Tbc->pin,c->isActive);
                sprintf(newLine,"%d. %s - %f$ | %d | status: ",c->Tbc->id,c->Tbc->cardHolderName,c->Tbc->balance+amount,c->Tbc->pin,c->isActive);
                replaceText(oldLine,newLine,"tbc.txt");
            }
        }
    }

    printf("Deposited successfully");
    fclose(file);
    return 0;
}
int withdraw(double amount, card *c);

card createCard(char bogOrTBC,int age,int pin);

void activateCard(int id);
void deactivateCard(int id);

void changePin(card *c,int oldPin,int newPin);

void cancelCard(card *c);