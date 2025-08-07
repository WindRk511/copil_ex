#include<stdio.h>

void pointre(char** text,int ligne, int long_text, int* n_err);
void tentete(char** text,int linge, int long_text, int* n_err);
void pvdebut(char** text,int ligne,int long_text,int* n_err);
void pvftion(char** text, int ligne, int long_text, int etat_com,int* n_err);
int pvdvar(char** text, int ligne, int long_text, int etat_com, int* n_err);
int pvifwhile( char** text, int ligne, int long_text , int* etat_com, int* n_err);
int pvfor(char** text, int ligne, int long_text, int* etat_com, int* n_err);
int pvinstr(char** text, int ligne, int long_text, int* etat_com, int* n_err);
void dtpointv(char* p, char* src, FILE* ptf);

