#include <stdbool.h>

typedef struct {
    int id;
    double balance;
    int pin;
    bool isStudentCard;
    bool isPupilCard;
    char cardHolderName;
} TBC;

typedef struct {
    int id;
    double balance;
    int pin;
    bool isStudentCard;
    bool isPupilCard;
    char cardHolderName;
} BOG;

typedef struct {
    int id;
    bool isActive;
    bool isCancelled;
    bool isBOG;
    bool isTBC;
    BOG *bankOfGeorgia;
    TBC *Tbc;
} card;