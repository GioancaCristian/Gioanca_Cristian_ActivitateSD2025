#include<stdio.h>
#include<stdlib.h>

struct Masina {
	int id;
	int anFabricatie;
	char* sofer;
	float kilometriParcursi;
	char initialaProducator;
};

struct Masina initializare(int id, int anFabricatie, const char* sofer, float kilometriParcursi, char initialaProducator) {
	struct Masina m;
	m.id = id;
	m.anFabricatie = anFabricatie;
	m.sofer = (char*)malloc(strlen(sofer) + 1); //(char*) cast explicit , transforma void* in char*
	strcpy_s(m.sofer, strlen(sofer) + 1, sofer);
	m.kilometriParcursi = kilometriParcursi;
	m.initialaProducator = initialaProducator;
	//initializare structura 
	return m;
}

void afisare(struct Masina m) {
	printf("Id: %d \n", m.id);
	printf("An fabricatie: %d \n", m.anFabricatie);//functie cu numar variabil de parametri
	printf("SOfer: %s \n", m.sofer);
	printf("Kilometri parcursi: %f \n", m.kilometriParcursi);
	printf("Initiala producator %c \n", m.initialaProducator);
	//afisarea tuturor atributelor.
}

void modifica_Sofer(struct Masina* m, const char* nouSofer) {
	if (strlen(nouSofer) > 2) {
		if (m->sofer != NULL) {
			free(m->sofer);
		}
		m->sofer = (char*)malloc(strlen(nouSofer) + 1);
		strcpy_s(m->sofer, strlen(nouSofer) + 1, nouSofer);
	}
	//modificarea unui atribut
}

void dezalocare(struct Masina* m) {
	if (m->sofer != NULL) {
		free(m->sofer);
		m->sofer = NULL;
	}
	//dezalocare campuri alocate dinamic
}

int main() {
	struct Masina masina;
	masina = initializare(1, 2004, "Robert", 2000, 'P'); //"p" este un sir(2 octeti) 'P' este un singur caracter(1 octet)
	afisare(masina);
	modifica_Sofer(&masina, "Alex");
	afisare(masina);
	dezalocare(&masina);
	afisare(masina);
	return 0;
}