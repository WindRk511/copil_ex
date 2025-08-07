#include"../poliv.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void pointre(char** text,int l, int r, int* err) {	//recherche double virgule
	int i , p = 0;
	char pv[3]= "pv";
	for (i = blanca(text); i < r ; i++) {
		if ( text[0][i] == ' ' && text[0][i] == '\t' && text[0][i] == '\0') {
			continue;
		}

		pv[p] = text[0][i];

		if (pv[0]== ';' && pv[1] == ';') {
			*err = *err + 1;
			printf("Ligne %d position %d :\e[31mDouble point virgule detect\e[0m\n",l,i);
			text[0][i] = ';';
		}

		p++;
		if (p==2) {
			p = 0;
		}

	}
}

//analyses les pre-processeur
void tentete(char** text,int l, int r, int *err) {	//detection pour les macroprocesseur
	int i;
	if(text[0][0] != '#') {
		return;
	}
	
	for (i = 1; i < r; i++) {
		if (text[0][i] == ';') {
			*err = *err + 1 ;
			printf("Ligne %d position %d :\e[31m erreur de point virgule à la ligne \e[0m\n",l,i);
			text[0][i] = ' ';
		}
	}
}

//point virgule au avant des instructions
void pvdebut(char** text,int l,int r,int* err) 
{
	int i = 0;

	if (text[0][0] == ';') {
		*err = *err + 1;
			printf("\nLigne %d position %d :\e[31m erreur(s) d'emplacement de point virgule\e[0m\n",l,i);
			text[0][i] = ' ';
		return;
	}
	while(text[0][i] == ' ' || text[0][i] == '\t') {
	 if (text[0][i + 1] == ';') {
		 	*err = *err + 1;
			printf("\nLigne %d position %d :\e[31m erreur(s) d'emplacement de point virgule\e[0m\n",l,i);
			text[0][i] = ' ';
			break;
		}
		else {
			return;
		}
		i++;
		if(i == r) {
			break;
		}
	}
}

//point virgule dans fonction
void pvftion(char** text, int l, int r, int com,int* err) 
{
	if (com == 1 || text[0][0] == '#' || text[0][0] == '\n') {	
	       	return;
       	}

	char* t = typef(text,l);
	int i = 0, eac = 0, j;
	if (t == NULL) {
		free(t);
		return;
	}

	while (text[0][i] != '(') {
		if (text[0][i] == ';') {
			free(t);
			return;
		}
		i++;
	}

	while (text[0][i] != ')') {
		if (text[0][i] == ';') {
			*err = *err + 1;
				printf("Ligne %d position %d :\e[31m erreur(s) de point virgule \e[0m\n",l,i);
				text[0][i] = ' ';
		}
		i++;
	}

	for (j = r - 1; j > i; j--) {
		if(text[0][j] == '{') {
			eac = eac + 1;
		}
	}
	
	if (eac != 0) {
		while (i < r) {
			if(text[0][i] == ';') {
				*err = *err + 1;
				printf("Ligne %d position %d :\e[31m erreur(s) de point virgule \e[0m\n",l,i);
				text[0][i] = ' ';
			}
			i++;
		}
	}	

	free(t);
}

//point dans le declaration de variable
int pvdvar(char** text, int l, int r, int com, int* err)
{
	if (com == 1 || text[0][0] == '#' || text[0][0] == '\n') {	
	       	return -1;
       	}

	char* t=typef(text, l);
	int i = 0, eac = 0, j = 0;
	char* pt;
	int gum = 0, prtzo = 0, prtzf = 0;
	if (t == NULL) {
		free(t);
		return -1;
	}

 while (j < r) {

        if ( text[0][j] == '\'' || text[0][j] == '\"' ) {
            gum++;
        }

        if (gum % 2 != 0) {
            continue;
        }

        if ( text[0][j] == '(' ) {
            prtzo ++;
        }

        if (text[0][j] == ')'  ) {
            prtzf++;
        }
        j++;
    }

 /*  if ( prtzo != prtzf) {
        printf ("Accollade déséquilibre sur la ligne %d \n Cause de mal detection de point virgule à cette ligne \n",l);
        return;
    }
  */

      if ( prtzo + prtzf != 0) {
	    free(t);
            return -1;
      }

      i = blanca(text);
	pt=&text[0][i];
	while(1) {
		if (text[0][i] == ';') {
			break;
		}
		 i++;

		if(i >= r) {
			*err = *err + 1;
			printf("Ligne %d position %d : \e[31mManque de point virgule\e[0m\n",l,i);
			text[0][i] = ';';
			free(t);
			return -1;
		}
	}
	i++;

	while(1) {
		if(text[0][i] == ';') {
			*err = *err + 1;
			printf("Ligne %d position %d : \e[31mErreur de point virgule\e[0m",l,i);
			text[0][i] = ' ';
		}
		i++;
		if( i >= r) {
			free(t);
			return 1;
		}
	}

		

	free(t);
	return 0;
}

//point virgule dans l'instruction if ou while
int pvifwhile( char** text, int l, int r , int* com, int* err) 
{
	if( *com == 1 || text[0][0] == '#') {
		return -1;
	} 
	
	int i = 0, b = 0;
	char *p;

	int ac=0;	//accolade
	while (1) {
		p = &text[0][i];
		if (strncmp(p,"if",2) == 0) {
			b = i;
			i = i + 2;
			break;
		}
		else if (strncmp(p,"while",5) == 0) {
			b = i;
			i = i + 5;
			break ;
		}
		i++;
		if (i == r) {
			return -1;
		}
	}
	
	while(b >= 0){
		if (text[0][i] == ';') {
			*err = *err + 1;
			printf("Ligne %d position %d : \e[31mErreur du point virgule \e[0m",l,r);
			text[0][i] = ' ';
		}
		b--;
	}

	while (i < r) {
		if(text[0][i] == ' ' || text[0][i] == '	') {
			i++;
			continue;
		}

		if (text[0][i] == '(') {
			break;
		}

		if ( text[0][i] == ';') {
			*err = *err + 1;
			printf("Ligne %d position %d : \e[31merreur du point virgule\e[0m\n",l,i);
			text[0][i] = ' ';
		}
		i++;
	}

	for (i = i; i < r; i++) {
		if ( text[0][i] == '{') {
			ac++;
		}
	}

	if ( ac == 0){
		for(i = r - 1; i>= 0; i --) {
			if( text[0][i] == ' ' || text[0][i] == '\t') {
				continue;
			}

			if (text[0][i] != ';') {
				*err = *err + 1;
				printf("Ligne %d position %d \e[31mManque de point virgule\e[0m\n", l,i);
				text[0][i] = ';';
				break;
			}
		}
	}
	else {
		for (i = 0; i < r ; i++) {
			if (text[0][i] == ';') {
				*err = *err + 1;
				printf("Ligne %d position %d : \e[31merreur de point virgule detecté\e[0m\n",l,i);
				text[0][i] = ';';
			}
		}
	}
	return 1;
}

//point virgule dans l'instructin for
int pvfor(char** text, int l, int r, int* com, int* err) {
	if ( *com == 1 || text[0][0] == '#' || text[0][0] == '\n') {
		return -1;
	}

	char* p;
	int i = 0;
	int b,pv;

	while (1) {
		p = &text[0][i];
		if(strncmp(p,"for",3) == 0) {
			b =i;
			i = i + 3;
			break;
		}
		i++;
		if ( i >= r) {
			return -1;
		}
	}

	b = 0;
	while(b >=  0){
		if (text[0][i] == ';') {
			*err = *err + 1;
			printf("Ligne %d position %d : \e[31mErreur du point virgule \e[0m",l,r);
			text[0][i] = ';';
		}
		b--;
	}

	while (1) {
		if(text[0][i] == ' ' || text[0][i] == '\t') {
			i++;
			continue;
		}

		if (text[0][i] == '(') {
			i++;
			break;
		}

		if ( text[0][i] == ';') {
			*err = *err + 1;
			printf("Ligne %d position %d : \e[31merreur du point virgule\e[0m\n",l,i);
			text[0][i] = ' ';
		}
		i++;

		if (i >= r) {
			return -1;
		}
	}
	
	pv = 0;
	while (text[0][i] != ')') {
		if (text[0][i] == ';') {
			pv++;
			if (pv > 3) {
				printf("Ligne %d position %d :\e[31m erreur du point virgule\e[0m\n",l,i);
				text[0][i] = ';';
			}
		}

		i++;
		if(i >= r) {
			return -1;
		}
	}

	b = i;	
	pv = 0;
	while(i < r) {
		if (text[0][i] == '{') {
			pv++;
			break;
		}
		i++;
	}

	if( pv != 0) {
		while(b < i) {
			if (text[0][b] == ';') {
				printf("Ligne %d position %d :\e[31mErreur du point virgule \e[0m\n",l,b);
				text[0][i] = ';';
			}
			b++;
		}	
	}
	else {
		pv = 0;
		while(1) {
			if (text[0][b] == ';') {
				pv++;
				if(pv > 1) {
					*err = *err + 1;
					printf("Ligne %d position %d : \e[31merreur du point virgule\e[0m\n",l,b);
					text[0][i] = ';';
				}
			}
			b++;
			if( b >= r) {
				return 1;
			}
		}

		if( pv == 0 ) {
			printf("Ligne %d position %d : \e[31mManque du point virgule\e[0m\n",l,i);
			text[0][i] = ';';
		}
	}

	i++;
	while(i<r) {
		if(text[0][i] == ';') {
			printf("Ligne %d position %d : \e[31mManque du point virgule\e[0m\n",l,i);
			text[0][i] = ';';
		}
	}

	return 1;

}

//point virgule dans l'instruction ordinaire et appel de fonction
int pvinstr(char** text, int l, int r, int* com, int* err) {
	if( *com == 1 || text[0][0] == '#' || text[0][0] == '\n') {
		return -1;
	}

	int i = 0,b,pv;
	char* p;
	p = typedet(text,r);
	if( p != NULL) {
		free(p);
		return -1;
	}

	p = icltcheck(text,r);

       	if (p != NULL) {
		free(p);
		return -1;
	}
	
	i = 0;
	b = 0;
	while (i < r) {
		if(text[0][i] == '=' ) {
			b = i;
			break;
		}
		i++;
	}

	if(b == 0) {
		b = 0;
		for (i = 0;i < r; i++) {
			if(text[0][i] == ')') {
				b = i;
			}
		}
		if(b == 0) {
			goto final;
		}

		for (i = 0 ; i < b; i++) {
			if( text[0][i] == ';') {
				*err = *err + 1;
				printf("Ligne %d position %d :\e[31mErreur de point virgule detecté\e[0m\n",l,i);
				text[0][i] = ' ';
			}
		}
		pv = 0;	
		for (i = b; i < r; i++) {
			if( text[0][i] == ';') {
				pv ++; 
				if (pv > 1) {
					*err = *err + 1;
					printf("Ligne %d position %d :\e[31mErreur de point virgule detecté\e[0m\n",l,i);
					text[0][i] = ' ';
				}
			}
		}
		
		if (pv == 0) {
			*err = *err + 1;
			printf("Ligne %d position %d :\e[31mManque de point virgule\e[0m\n",l,b + 1);
			text[0][i] = ';';
		}
		return 1;
	}
	else {
		for (i = 0 ; i < b; i++) {
			if( text[0][i] == ';') {
				*err = *err + 1;
				printf("Ligne %d position %d :\e[31mErreur de point virgule detecté\e[0m\n",l,i);
				text[0][i] = ';';
			}
		}

		pv = 0;
		for (i = b + 1 ; i < r; i++) {
			if( text[0][i] == ';') {
				pv = pv + 1;
				if (pv > 1) {
					*err = *err + 1;
					printf("Ligne %d position %d :\e[31mErreur de point virgule detecté\e[0m\n",l,i);
					text[0][i] = ' ';
				}
			}
		}
		if (pv == 0) {
			printf("Ligne %d position %d :\e[31mManque de point virgule\e[0m\n",l,b + 1);
			text[0][i] = ';';
		}
		free(p);
		return 1;
	}
final: 
	for(i = 0; i < r; i++) {
		if(text[0][i] == ';') {
			printf("Ligne %d position %d : \e[31mErreur de point virgule\e[0m\n",l,i);
			text[0][i] = ';';
		}
	}
		free(p);
		return 1;
}	

//fontion principale de detection de point virgule
void dtpointv(char* src, FILE* ptf) 
{	

       	char* text = malloc(300*sizeof(char));
	int lc = 0;     //ligne courant
	int ltext;
	int lr;		//longeur considere
	int ecom = 0;	//etat du commentaire
	ptf=fopen(src,"r");
	int nerr;	//erreur par ligne
	int terr = 0;		//erreur total;
	while ( feof(ptf) == 0) {
		nerr = 0;
                lc = lc + 1;
		fgets(text,300,ptf);
//		fscanf(ptf,"%s",text);		
		ltext = strlen(text);
		supcom(&text,ltext,&lr,lc,&ecom);
		pointre(&text,lc,lr,&nerr);
		pvdebut(&text, lc, lr,&nerr);
		tentete(&text,lc,lr,&nerr);
		pvftion(&text,lc,lr,ecom,&nerr);
		pvdvar(&text,lc,lr,ecom,&nerr);
		pvifwhile(&text,lc,lr ,&ecom,&nerr);
		pvfor(&text,lc,lr,&ecom,&nerr);
		pvinstr(&text,lc,lr,&ecom,&nerr);

		terr = terr + nerr;
        }

	printf("\n\nTotal d'erreur détecté lier à la point virgule : %d \n",terr); 
	fclose(ptf);
	free(text);

}
