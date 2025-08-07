#include"poliv.h"
#include"point_virgule/point_virgule.h"
#include<stdio.h>

int main (int c, char** arg)
{
	FILE *pf;
	char prm[10];

	veprm(c,arg,prm);	//Verfication de l'argument
	aide(prm);		//Page d'aide
	lectureif(arg[2],pf);	//Affiche de contenu du tableau
	dtpointv(arg[2],pf);	//detection et correction de point virgule
}
