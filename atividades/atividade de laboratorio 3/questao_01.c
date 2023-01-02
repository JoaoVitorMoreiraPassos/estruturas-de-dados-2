#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct series Series;
typedef struct seasons Seasons;
typedef struct participants Participants;
void mostraArvore(Series* a, int b);
void imprimeNo(char *s, int b);


struct participants
{
    char *artist_name;
    char *caracter_name;
    char *caracter_description;
    Participants *left, *right;
};
struct seasons
{
    int number;
    char *title;
    int num_eps;
    int year;
    Participants *participant;
    Seasons *next;
};
struct series
{
    char cod[9];
    char *title;
    int num_seasons;
    Seasons *season;
    Series *left, *right;
};


Series *start()
{
    return NULL;
}

void insertSerie(Series **bt_series, char cod[9], char *title, int num_seasons)
{
    if((*bt_series) == NULL){
        (*bt_series) = (Series *) malloc(sizeof(Series));
        strcpy((*bt_series)->cod, cod);

        (*bt_series)->title = (char *) calloc(strlen(title),sizeof(char));

        strcpy((*bt_series)->title, title);
        (*bt_series)->num_seasons = num_seasons;

        (*bt_series)->season = NULL;
        (*bt_series)->left = NULL;
        (*bt_series)->right = NULL;
    }else if(strcmp((*bt_series)->cod, cod) == -1)
        insertSerie(&(*bt_series)->left, cod, title, num_seasons);
    else if(strcmp((*bt_series)->cod, cod) == 1)
        insertSerie(&(*bt_series)->right, cod, title, num_seasons );
}


void insertSeason(Series **bt,char serie_cod[9], int ssn, char *title, int num_eps, int year)
{
    if((*bt) != NULL){
        if(strcmp((*bt)->cod, serie_cod) == 0){
            Seasons *node = (Seasons*) malloc(sizeof(Seasons));
            node->number = ssn;
            node->title = (char *) malloc(sizeof(char) * strlen(title));
            strcpy(node->title, title);
            node->num_eps = num_eps;
            node->year = year;
            node->participant = NULL;
            node->next = (*bt)->season;
            (*bt)->season = node;

            Seasons *i, *j;
            for(i = (*bt)->season; i != NULL; i=i->next)
            {
                for(j = i->next; j != NULL; j = j->next)
                {
                    if(i->number > j->number){
                        int aux_i;
                        char *aux_c;
                        Participants *aux_p;
                        aux_i = i->number;
                        i->number = j->number;
                        j->number = aux_i;

                        aux_c = (char *) malloc(sizeof(char)*strlen(i->title));
                        strcpy(aux_c, i->title);
                        i->title = (char *) malloc(sizeof(char) * strlen(j->title));
                        strcpy(i->title, j->title);
                        j->title = (char *) malloc( sizeof(char) * strlen(aux_c));
                        strcpy(j->title, aux_c);

                        aux_i = i->num_eps;
                        i->num_eps = j->num_eps;
                        j->num_eps = aux_i;

                        aux_i = i->year;
                        i->year = j->year;
                        j->year = aux_i;

                        aux_p = i->participant;
                        i->participant = j->participant;
                        j->participant = aux_p;
                    }
                }
            }
        }
        else if(strcmp((*bt)->cod,serie_cod) == -1)
            insertSeason(&(*bt)->left,serie_cod, ssn, title, num_eps, year);
        else if(strcmp((*bt)->cod,serie_cod) == 1)
            insertSeason(&(*bt)->right,serie_cod, ssn ,title, num_eps, year);
    }
}
void auxParticipant(Participants **part, char *artist_name, char *caracter_name, char *caracter_description)
{
    if((*part) == NULL){
        (*part) = (Participants *) malloc(sizeof(Participants));
        (*part)->artist_name = (char *) malloc(sizeof(char)* strlen(artist_name));
        (*part)->caracter_name = (char *) malloc(sizeof(char)* strlen(caracter_name));
        (*part)->caracter_description = (char *) malloc(sizeof(char)* strlen(caracter_description));
        
        strcpy((*part)->artist_name, artist_name);
        strcpy((*part)->caracter_name, caracter_name);
        strcpy((*part)->caracter_description, caracter_description);
        (*part)->left = NULL;
        (*part)->right = NULL;
    }
    else if(strcmp((*part)->caracter_name, caracter_description) == -1)
        auxParticipant(&(*part)->left, artist_name, caracter_name, caracter_description);
    else if(strcmp((*part)->caracter_name, caracter_description) == 1)
        auxParticipant(&(*part)->right, artist_name, caracter_name, caracter_description);
}
void insertParticipant(Series **bt, char cod[9], int season, char *artist_name, char *caracter_name, char *caracter_description)
{
    if((*bt) != NULL)
    {
        if(strcmp((*bt)->cod, cod) == 0)
        {
            Seasons *i;
            for (i = (*bt)->season; i != NULL; i = i->next)
            {
                if(i->number == season)
                    auxParticipant(&i->participant, artist_name, caracter_name, caracter_description);
            }
        }
        else if(strcmp((*bt)->cod,cod) == -1)
            insertParticipant(&(*bt)->left,cod, season,artist_name, caracter_name, caracter_description);
        else if(strcmp((*bt)->cod, cod) == 1)
            insertParticipant(&(*bt)->right,cod, season ,artist_name, caracter_name, caracter_description);
    }
}

void letterA(Series *bt)
{
    if(bt != NULL)
    {
        letterA(bt->left);
        printf("Title: %s, %d Seasons\n",bt->title,bt->num_seasons);
        letterA(bt->right);
    }
}

void letterB(Series *bt, char cod[9])
{
    if(bt != NULL){
        letterB(bt->left, cod);
        letterB(bt->right, cod);
        if(strcmp(bt->cod, cod) == 0)
        {
        	Seasons *i;
            for( i = bt->season; i != NULL; i = i->next)
                printf("Season %d; Title: %s; Number of episodes: %d; Year: %d\n", i->number,i->title, i->num_eps, i->year);
        }
    }
}
void printCaracters(Participants *part)
{
    if(part != NULL)
    {
        printCaracters(part->left);
        printf("Artist name: %s, Caracter name: %s, Description: %s\n", part->artist_name, part->caracter_name, part->caracter_description);
        printCaracters(part->right);
    }
}
void letterC(Series *bt, char cod[9], int season)
{
    if(bt != NULL)
    {
        if(strcmp(bt->cod, cod) == 0)
        {   
            Seasons *i;
            for (i = bt->season; i != NULL; i = i->next)
            {
                if(i->number == season)
                    printCaracters(i->participant);
            }
        }
        else if(strcmp(bt->cod, cod) == -1)
            letterC(bt->left,cod, season);
        else if(strcmp(bt->cod, cod) == 1)
            letterC(bt->right,cod, season);
    }
}

void printArtirts(Participants *part, int s)
{
    if(part != NULL)
    {
        printArtirts(part->left, s);
        printf("%s as %s in season %d\n",part->artist_name, part->caracter_name, s);
        printArtirts(part->right, s);
    }
}
void letterD(Series *bt, char cod[9])
{
    if(bt != NULL)
    {
        if(strcmp(bt->cod, cod) == 0)
        {
            Seasons *i;
            for (i = bt->season; i != NULL; i = i->next)
                printArtirts(i->participant, i->number);
        }
        else if(strcmp(bt->cod, cod) == -1)
            letterD(bt->left,cod);
        else if(strcmp(bt->cod, cod) == 1)
            letterD(bt->right,cod);
    }
}

void main()
{
    Series *bt = start();

    insertSerie(&bt, "111111111", "DRAGON BALL Z", 4);
    insertSerie(&bt, "222222222", "TVD", 8);
    insertSerie(&bt, "333333333", "LEGACIES", 4);
    insertSerie(&bt, "444444444", "HOW I MET YOUR MOTHER", 9);
    
    insertSeason(&bt, "111111111", 1, "Saga dos sayajins",35,1989);
    insertSeason(&bt, "111111111", 2, "Saga de Fresza",71,1991);
    insertSeason(&bt, "111111111", 3, "Saga dos Androides",76,1993);
    insertSeason(&bt, "111111111", 4, "Saga de Majin Boo",91,1995);

    insertParticipant(&bt,"111111111",1,"Goku","Goku", "Protagonista");
    insertParticipant(&bt,"111111111",1,"Vegeta","Vegeta", "Principe dos sayajins");
    insertParticipant(&bt,"111111111",1,"Gohan","Gohan", "Filho de Goku");
    insertParticipant(&bt,"111111111",1,"Kuririn","Kuririn", "Amigo de Goku");
    
    letterA(bt);
    printf("----------------------------------\n");
    letterB(bt, "111111111");
    printf("----------------------------------\n");
    letterC(bt, "111111111", 1);
    printf("----------------------------------\n");
    letterD(bt, "111111111");
}
