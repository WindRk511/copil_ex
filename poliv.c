#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//verification de parametre
char* veprm(int n, char** a, char* p )
{
	puts(a[1]);
	if (n == 2) {
	      	if ( strcmp(a[1],"--aide") == 0) {
			strcpy(p,"--aide");
        	        return p;
		}
		else if (a[1][0] == '-') {
			printf("Erreur de syntaxe\n");
			exit (1);
		}
        }

	 if(n != 3) {
                printf("argument insuffisant ou paramètre incorrecte\n ");
                exit (1);
        }

        if ( strcmp(a[1],"-p") == 0) {
		strcpy(p,"-p");
                return p;
        }
        else if ( strcmp(a[1],"-v") == 0) {
		strcpy(p,"-v");
                return p;
        }
        else if ( strncmp(a[1],"-pv",3) == 0 || strncmp(a[1],"-vp",3)) {
		strcpy(p,"-pv");
                return p;
        }
	else{
       		printf("Parametre incorrect\n");
		strcpy(p,"--aide");
                return p;
        }


}

//petit aide
int aide(char* p) {
	if(strcmp(p,"--aide") != 0) {
		return (-1);
	}
	printf("Syntaxe : fica [option] [argument] \n");
	printf("L'argument est le chemin vers le fichier.\n");
	printf("Option : \n");
	printf("-p		pour analyser les points virgule\n");
	printf("-v		pour analyser les variables \n");
	printf("--aide		page d'aide\n");
	exit (0);
}


//lecture integrale de fichier
void lectureif(char* src,FILE *ptf)
{
        char text[300];
        int lc = 0;     //ligne courant

        ptf=fopen(src,"r");
        if (ptf == NULL) {
                printf("Fichier introuvable\n");
                exit (1);
        }

        while ( feof(ptf) == 0) {
                lc = lc + 1;
                fgets(text,sizeof(text),ptf);
                printf("%s",text);
        }
	fclose(ptf);
}

//fontion pour negliger les commentaires en reduire la longueur de chaine considerer
void supcom(char** text, int l,int* r,int n, int* ec)	//detection de commentaire
{
	int i;
	char chaine[400];
	for (i = 0; i < l; i ++) {
		if (text[0][i] == '/' && text[0][i + 1] == '/') {
			if (*ec == 1) {
				continue;
			}
			*r = i + 1;
			return;
		}
		else if (text[0][i] == '/' && text[0][i + 1] == '*') {
			if (*ec == 1) {
				continue;
			}
			*ec = 1;
			*r = i + 1;
			return;
		}
		else if (text[0][i] == '*' && text[0][i + 1] == '/') {	//****En traint de l'amelioration
			if (*ec == 0) {
			       printf("Ligne %d position %d :\e[31mErreur de la fermeture de commentaire; Commentaire pas de debut\e[0m\n",n,i);
			return;
			}
			*ec = 0;
			*r = i + 1;
	 		return;
		}
		else if (text[0][i] == '\n') {
			return;
		}
		*r = i + 1;
	}
}

//detection des espaces blancs avant tout les instructions
int blanca (char** text) 	//detect espace blanc avant les instruction
{
	int i = 0;
	while (text[0][i] == ' ' || text[0][i] == '\t') {
		i = i + 1;
	}
	return i;
}

//detect des types de variables au debut de l'instruction
char* typef(char** text, int l) 
{
	int c = blanca(text);
	char* t=malloc(10);
	char* p;
	int i = 1;

		if (text[0][0] == '\n') {
			return NULL;
		}

	while (text[0][c] != ' ' || text[0][c] != '\t') {
		p = &text[0][c];

				
//		printf("t:%s lingne %d\n",t[0],l);
		if (strncmp(p,"int,",3) == 0) {
			strcpy(t,"int");
			return t;
		}
		else if ( strncmp(p,"void",4) == 0) {
			strcpy(t,"void");
			return t;
		}
		else if ( strncmp(p,"char",4) == 0) {
			strcpy(t,"char");
			return t;
		}
		else if ( strncmp(p,"float",5) == 0) {
			strcpy(t,"float");
			return t;
		}
		else if ( strncmp(p,"double",6) == 0) {
			strcpy(t,"double");
			return t;
		}
		else if ( strncmp(p,"long",4) == 0) {
			strcpy(t,"long");
			return t;
		}
		i = i + 1;
		c = c + 1;
//		text[0][i] = '\0';
		if (i == 10) {
			break;
		}		
	}
	return NULL;
}

//dermine s'il s'agit un instruction de controle dans une ligne
char* icltcheck(char** text, int r)
{	
	char* t = NULL;
	char* p;
	int i = 0;

		if (text[0][0] == '\n') {
			return NULL;
		}

	for(i = 0; i < r; i++) {
		p = &text[0][i];
		if (strncmp(p,"for",3) == 0) {
			t = malloc(4);
			strcpy(t,"for");
			return t;
		}
		else if ( strncmp(p,"while",5) == 0) {
			t = malloc(6);
			strcpy(t,"while");
			return t;
		}
		else if ( strncmp(p,"do",2) == 0) {
			t = malloc(3);
			strcpy(t,"do");
			return t;
		}
		else if ( strncmp(p,"if",2) == 0) {
			t = malloc(3);
			strcpy(t,"if");
			return t;
		}
		else if ( strncmp(p,"goto",4) == 0) {
			t = malloc(5);
			strcpy(t,"goto");
			return t;
		}
		else {
			p = NULL;
			t = NULL;
		}
	}
	return t;
}

char* typedet(char** text, int r) {
	char* t = NULL;
	char* p;
	int i = 1;

		if (text[0][0] == '\n') {
			return NULL;
		}

	for(i = 0; i < r; i++) {
		p = &text[0][i];
		if (strncmp(p,"int",3) == 0) {
			if(text[0][i+3] != ' ') {
				continue;
			}
			t = malloc(4);
			strcpy(t,"int");
			return t;
		}
		else if ( strncmp(p,"void",4) == 0) {
			if(text[0][i+4] != ' ') {
				continue;
			}
			t = malloc(5);
			strcpy(t,"void");
			return t;
		}
		else if ( strncmp(p,"char",4) == 0) {
			if(text[0][i+4] != ' ') {
				continue;
			}
			t = malloc(5);
			strcpy(t,"char");
			return t;
		}
		else if ( strncmp(p,"float",5) == 0) {
			if(text[0][i+5] != ' ') {
				continue;
			}
			t = malloc(6);
			strcpy(t,"float");
			return t;
		}
		else if ( strncmp(p,"double",6) == 0) {
			if(text[0][i+6] != ' ') {
				continue;
			}
			t = malloc(7);
			strcpy(t,"double");
			return t;
		}
		else if ( strncmp(p,"long",4) == 0) {
			if(text[0][i+4] != ' ') {
				continue;
			}
			t = malloc(5);
			strcpy(t,"long");
			return t;
		}
		i = i + 1;
	}
	return NULL;
}

