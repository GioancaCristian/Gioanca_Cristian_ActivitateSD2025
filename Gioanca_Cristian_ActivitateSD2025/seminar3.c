#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

void afisareMasina(Masina masina) {
	printf("ID : %d \n Nr Usi: %d \n Pret: %.2f \n Model: %s \n Nume Sofer: %s \n Serie : %c", masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);
	printf("\n");
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	if (masini != NULL && nrMasini > 0)
	{
		for (int i = 0; i < nrMasini; i++)
		{
			afisareMasina(masini[i]);
		}
	}
}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
	Masina* aux = (Masina*)malloc(sizeof(Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < (*nrMasini); i++)
	{
		aux[i] = (*masini)[i];
	}
	aux[(*nrMasini)] = masinaNoua;
	free((*masini));
	(*masini) = aux;
	(*nrMasini)++;
}

Masina citireMasinaFisier(FILE* file) {
	Masina m;
	char buffer[100];
	char delim[4] = ",;\n";
	fgets(buffer, 100, file);
	char* aux;
	aux = strtok(buffer, delim);
	m.id = atoi(aux);
	m.nrUsi = atoi(strtok(NULL,delim));
	m.pret = atof(strtok(NULL, delim));
	aux = strtok(NULL, delim);
	m.model = malloc(strlen(aux) + 1);
	strcpy_s(m.model, strlen(aux) + 1, aux);
	aux = strtok(NULL, delim);
	m.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m.numeSofer, strlen(aux) + 1, aux);
	m.serie = strtok(NULL, delim)[0];
	return m;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	FILE* f = fopen(numeFisier, "r");
	Masina* masini = NULL;
	while (!feof(f))
	{
		Masina mas = citireMasinaFisier(f);
		adaugaMasinaInVector((&masini), nrMasiniCitite, mas);
	}
	fclose(f);
	return masini;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	for (int i = 0; i < (*nrMasini); i++)
	{
		free((*vector)[i].model);
		free((*vector)[i].numeSofer);
	}
	free(*vector);
	(*vector) = NULL;
	(*nrMasini) = 0;
}

int main() {
	
	Masina* masini = NULL;
	int nrMasini = 0;
	masini = citireVectorMasiniFisier("masini.txt", &nrMasini);

	afisareVectorMasini(masini, nrMasini);

	return 0;
}