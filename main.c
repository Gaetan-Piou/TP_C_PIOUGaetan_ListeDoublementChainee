#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct ELEMENT {
	int nombre;
	struct ELEMENT *precedent;
	struct ELEMENT *suivant;
} ELEMENT;

typedef struct LISTE {
	ELEMENT *premier;
	ELEMENT *dernier;
} LISTE;


void initialisation(LISTE *l);
void ajoutFin(LISTE *l, int val);
void ajoutDebut(LISTE *l, int val);
void ajoutMilieu(LISTE *l, int val, int rang);
int retraitFin(LISTE *l);
int retraitDebut(LISTE *l);
int retraitMilieu(LISTE *l, int rang);
int modifValeur(LISTE *l, int val, int rang);
void afficheListe(LISTE *l);

int main()
{
    LISTE maListe;
    initialisation(&maListe);

    ajoutDebut(&maListe,12);
    ajoutFin(&maListe,46);
    ajoutDebut(&maListe,69);
    ajoutDebut(&maListe,420);

    afficheListe(&maListe);

    printf("On ajoute 160 avant le 3e element\n");

    ajoutMilieu(&maListe,160,3);

    afficheListe(&maListe);

    printf("On enleve le premier element, c'est-a-dire %d\n",retraitDebut(&maListe));

    afficheListe(&maListe);

    printf("On enleve le deuxieme element, c'est-a-dire %d\n",retraitMilieu(&maListe,2));

    afficheListe(&maListe);

    printf("On modifie le deuxieme element, c'est-a-dire %d, on lui donne 120\n",modifValeur(&maListe, 120, 2));

    afficheListe(&maListe);


    return 0;
}

void initialisation(LISTE *l) {
	l->premier = NULL;
	l->dernier = NULL;
}


void ajoutFin(LISTE *l, int val) {
	ELEMENT *nouveau = malloc(sizeof(ELEMENT));
	if(!nouveau) {
		exit(EXIT_FAILURE);
	}

	nouveau->nombre = val;
	nouveau->precedent = l->dernier;
	nouveau->suivant = NULL;

	if(l->dernier) {
		l->dernier->suivant = nouveau;
	} else {
		l->premier = nouveau;
	}
	l->dernier = nouveau;
}


void ajoutDebut(LISTE *l, int val) {
	ELEMENT *nouveau = malloc(sizeof(ELEMENT));
	if(!nouveau) {
		exit(EXIT_FAILURE);
	}

	nouveau->nombre = val;
	nouveau->suivant = l->premier;
	nouveau->precedent = NULL;

	if(l->premier) {
		l->premier->precedent = nouveau;
	} else {
		l->dernier = nouveau;
	}
	l->premier = nouveau;
}


void ajoutMilieu(LISTE *l, int val, int rang) {
	ELEMENT *nouveau = malloc(sizeof(ELEMENT));
	ELEMENT *positionSuivant = l->premier;
	ELEMENT *positionPrecedent;
	int i = 1;
	if(!nouveau) {
		exit(EXIT_FAILURE);
	}

	nouveau->nombre = val;

	while(positionSuivant && (i<rang)) {
		positionSuivant = positionSuivant->suivant;
		i++;
	}

	if(positionSuivant) {
		positionPrecedent = positionSuivant->precedent;
		nouveau->precedent = positionPrecedent;
		nouveau->suivant = positionSuivant;
		positionPrecedent->suivant = nouveau;
		positionSuivant->precedent = nouveau;
	}
}


int retraitFin(LISTE *l) {
	int val;
	ELEMENT *tmp = l->dernier;

	if(!tmp) {
		return -1;
	}

	val = tmp->nombre;
	l->dernier = tmp->precedent;

	if(l->dernier) {
		l->dernier->suivant = NULL;
	} else {
		l->premier = NULL;
	}

	free(tmp);
	return val;
}


int retraitDebut(LISTE *l) {
	int val;
	ELEMENT *tmp = l->premier;

	if(!tmp) {
		return -1;
	}

	val = tmp->nombre;
	l->premier = tmp->suivant;

	if(l->premier) {
		l->premier->precedent = NULL;
	} else {
		l->dernier = NULL;
	}

	free(tmp);
	return val;
}


int retraitMilieu(LISTE *l, int rang) {
	int val;
	ELEMENT *tmp = l->premier;
	ELEMENT *precedent;
	int i = 1;

	if(!tmp) {
		return -1;
	}

	while(tmp && i<rang) {
		tmp = tmp->suivant;
		i++;
	}

	if(tmp) {
		val = tmp->nombre;
		tmp->precedent->suivant = tmp->suivant;
		tmp->suivant->precedent = tmp->precedent;
	} else {
		return -1;
	}

	free(tmp);
	return val;
}


int modifValeur(LISTE *l, int val, int rang) {
	ELEMENT *nouveau = l->premier;
	int exVal;
	int i = 1;

	while(nouveau && (i<rang)) {
		nouveau = nouveau->suivant;
		i++;
	}

	if(nouveau) {
		exVal = nouveau->nombre;
		nouveau->nombre = val;
		nouveau->suivant->precedent = nouveau;
		nouveau->precedent->suivant = nouveau;
	} else {
		return -1;
	}

	return exVal;

}


void afficheListe(LISTE *l) {
	ELEMENT *elementAffiche = l->premier;
	while(elementAffiche) {
		printf("%d",elementAffiche->nombre);
		elementAffiche = elementAffiche->suivant;
		if(elementAffiche) {
			printf(" -> ");
		}
	}
	printf("\n");
}
