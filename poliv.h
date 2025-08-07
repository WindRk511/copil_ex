#include<stdio.h>

char* veprm(int nbr_arg, char** val_arg, char* parametre );
int aide(char* parametre);
void lectureif(char* src,FILE *ptf);
void supcom(char** text, int longueur_t,int* longueur_c, int n_ligne, int* etat_commentaire);
int blanca (char** text);
char* typef(char** text, int l);
char* icltcheck(char** text, int r);
char* typedet(char** text, int long_text);



