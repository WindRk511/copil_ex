#include"var_indeclare.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 99


int majmin(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int chiffre(char c) {		//determine chiffre
    return (c >= '0' && c <= '9');
}

int carv(char c) {		//caractere validé
    return majmin(c) || chiffre(c) || c == '_';
}

int vtype(const char *m) {
    if (strcmp(m, "int") == 0 ) {
	    return 0;
    }
    else if(strcmp(m, "float") == 0) {
	    return 0;
    }
    else if (strcmp(m, "char") == 0 ) {
	    return 0;
    }
    else if (strcmp(m, "double") == 0) {
	    return 0;
    }
    return 1;
}

void ajoutvar(char *var, char** lvar, int* nvar ) {
    if (*nvar < M) {
	    *nvar = *nvar + 1;
	    lvar[*nvar] = malloc(sizeof(var));
	    strcpy(lvar[*nvar],var);
    }
}

int vardec(char *var, char**lvar, int nvar) {
    for (int i = 0; i < nvar; i++) {
        if (strcmp(lvar[i], var) == 0) {
		return 1;
	}
    }
    return 0;
}

void libremem(char** lvar, int *nvar) {
    for (int i = 0; i < *nvar; i++) {
        free(lvar[i]);
    }
    *nvar = 0;
}

void ideclar(char *text, char** lvar,int* nvar) {
    char m[300];
    int i = 0, j = 0;
    int d = 0;

    while (i < strlen(text)) {
        char c = text[i];
        if (majmin(c)) {
            if (j < 300 - 1) {
                m[j++] = c;
            }
        } else {
            if (j > 0) {
                m[j] = '\0';
                j = 0;

                if (vtype(m)) {
                    i = 1;
                } else if (i == 1) {
                    ajoutvar(m,lvar,nvar);
                    i = 0;
                } else {
                    if (vardec(m,lvar,*nvar) == 0) {
                        printf("Variable non déclarée : %s\n", m);
                    }
                }
            }
        }
        i++;
    }
}

int detvar(char* p,char* src, FILE* pf) 
{
	printf("tsia");
	if(strcmp(p,"-v") != 0) {
	       	if (strcmp(p,"-pv") != 0 || strcmp(p,"-vp") != 0) {
			return -1;
		}
	}

    pf = fopen(src, "r");
    if (pf == NULL) {
        printf("Erreur d'ouverture du fichier %s\n",src);
        return 1;
    }
	char *lvar[M];
	int nvar = 0;

    	char text[400];
	while (feof(pf) == 0) {
		fgets(text, sizeof(text), pf);
       		ideclar(text,lvar,&nvar);
    	}

    	fclose(pf);
    	libremem(lvar,&nvar);
}
