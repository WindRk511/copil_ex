#include<stdio.h>

int majmin(char c);
int chiffre(char c);
int carv(char c);
int vtype(const char *m);
void ajoutvar(char *var, char** list_var, int* nb_var );
int vardec(char *var, char** list_var, int nb_var);
void libremem(char** list_var, int *nb_var);
void ideclar(char *text, char** list_var, int* nb_var);
int detvar(char* parametre, char* src, FILE* pf);

