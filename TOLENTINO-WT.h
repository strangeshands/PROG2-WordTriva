// PROPERTY OF HEPHZI-BAH TOLENTINO //

#include <stdio.h>
#include <string.h>

#include <stdlib.h> //to use srand() and rand()
#include <time.h> //to use srand() and generate different random numbers each run

#define LEN20 21
#define LEN30 31
#define LEN100 101
#define MAX 150
#define MAX10 10
#define MAXTABLE 150
#define MAX5 5
#define MAX500 500

typedef char WORD[LEN20];
typedef char TRIVIA[LEN30];
typedef char SCAN[LEN100];
typedef char String30[LEN30];

typedef struct TriviaTag {
    TRIVIA          Relation;
    TRIVIA          RelValue;
} TriviaDetail;

typedef struct WordContentTag {
    WORD            Answer;
    char            firstLetter;
    TriviaDetail    Trivia[MAX10]; 
    int             RelCtr;
} WordDetail;

typedef struct letterTag{
    char            letter;
    int             count;
} letterDetail;

typedef struct accountTag {
    String30        username;
    String30        password;
} accountDetail;

typedef struct categoryTag {
    String30        catName;
    String30        catFile;
} categoryDetail;
