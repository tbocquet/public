#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "base.h"
#include "calculs_base.h"
#include "determinant.h"
#include "inversion.h"
#include "comatrice.h"
#include "gauss-jordan.h"

#define T_MAT_MULT 3
#define T_MAT_DET 3
#define T_MAT_INVERSE 3

void choix_nbl_nbc(int * nbl, int * nbc)
{
	printf("Nombre de lignes : ");
	scanf("%d",nbl);
	printf("Nombre de colonnes : ");
	scanf("%d",nbc);
}
matrice_s * creation_matrice()
{
	matrice_s * m;
	int nbl, nbc;
	int choix = 0;
	printf("Création d'une matrice, \033[31m-- choix de la dimension\033[00m\n");
	choix_nbl_nbc(&nbl, &nbc);
	printf(	"Choix 1 : remplissage aléatoire de la matrice\n"
			"Choix 2 : remplir soi-même\n");
	scanf("%d",&choix);
	switch(choix)
	{
		case 1 : m = random_matrix(nbl, nbc); break;
		case 2 : m = read_matrix(nbl, nbc); break;
		default : break;
	}
	return m;
}

void test_determinant_comatrice_transposee()
{
	matrice_s *m, *co, *tr;

	printf(	"\033[32mdéterminant - comatrice - transposée \033[00m\n"
			"\033[31m-- création d'une matrice\033[00m\n");
	m = creation_matrice();

	printf("Matrice créée :\n");
	display_matrix(m);
	printf("Déterminant de la matrice : %.2f\n",det_nxn(m));

	co = comatrice(m);
	tr = transposee_matrix(m);

	printf("Sa comatrice : \n");
	display_matrix(co);

	printf("Sa transposée : \n");
	display_matrix(tr);

	free_matrix(m);
	free_matrix(co);
	free_matrix(tr);
}
void test_multiplication()
{
	printf("\033[31mtest de la multiplication : création de 2 matrices\033[00m\n");
	matrice_s *m1, *m2, *mult;
	m1 = creation_matrice();
	m2 = creation_matrice();

	printf("Les 2 matrices crées : \n");
	display_matrix(m1);
	display_matrix(m2);

	printf("Multiplication de ces 2 matrices : \n");
	mult = multiplication_matrices(m1,m2);
	display_matrix(mult);

	free_matrix(m1);
	free_matrix(m2);
	free_matrix(mult);
}
void test_addition_matrices()
{
	printf("test addition de matrices \033[31m -- création de 2 matrices \033[00m\n");
	matrice_s * m1, *m2, *m3;
	m1 = creation_matrice();
	m2 = creation_matrice();

	printf("Affichage des matrices créées : \n");
	display_matrix(m1);
	display_matrix(m2);

	printf("L'addition des 2 matrices précédentes : \n");
	m3 = add_matrix(m1,m2);
	display_matrix(m3);

	free_matrix(m1);
	free_matrix(m2);
	free_matrix(m3);
}

void test_inversion()
{
	matrice_s *m, *inverseco, *inversegauss;
	printf(	"\033[32minversion de matrice\033[00m"
			"\033[31m-- création d'une matrice\033[00m\n");
	m = creation_matrice();

	printf("La matrice créee : \n");
	display_matrix(m);

	printf("Déterminant de la matrice : %2.2f\n",det_nxn(m));
	printf("Via la méthode de \033[032mcomatrice :\033[00m \n");
	inverseco = inversion_comatrices(m);
	if(inverseco != NULL)
		display_matrix(inverseco);
	else
		printf("Déterminant == 0 donc on ne fait pas d'inversion car impossible\n");

	printf("Via la méthode du \033[32mpivot de Gauss :\033[00m \n");
	inversegauss = inversion_gauss_jordan(m);
	if(inversegauss != NULL)
		display_matrix(inversegauss);
	else
		printf("impossible via le pivot de gauss\n");

	free_matrix(m);
	free_matrix(inverseco);
	free_matrix(inversegauss);
}

void test_addition_lignes()
{
	printf("\033[31mAddition de 2 lignes\033[00m\n");
	matrice_s * m = random_matrix(T_MAT_MULT,T_MAT_MULT);
	display_matrix(m);

	printf("Addition de 2 lignes : l1 += l0 * 2\n\n");
	addition_lignes(m,0, 1, 2);
	display_matrix(m);
	printf("Inversion de 2 lignes : la 2 et la 3\n\n");
	inversion_lignes(m, 2,3);
	display_matrix(m);
	
}
void tests_divers()
{
	printf("Matrice identitée de %d \n", T_MAT_MULT);
	matrice_s * identitee;
	identitee = matrice_identitee(T_MAT_MULT);
	display_matrix(identitee);

	matrice_s * autre = matrice_identitee(T_MAT_MULT);

	printf("Test fonction 'identiques' → si 2 matrices sont identiques\n");
	printf("Seconde matrice pour le test : \n");
	autre->matrice[0][0] = 2; 
	display_matrix(autre);

	if(identiques(autre,identitee) == 0)
		printf("Les 2 matrices sont identiques -- erreur\n");
	else
		printf("Les 2 matrices sont différentes -- fonction 'identiques' OK\n");

	int ligne, colonne;
	ligne = 1; colonne = 2;
	printf( "\n\033[31mTest du pivot\033[00m \n"
			"On prend la matrice identitée pour ce test\n"
			"On se place en ligne %d et en colonne %d" 
			": où est le prochain pivot ?\n",
			ligne, colonne);
	ligne = recherche_ligne_pivot_suivant(identitee, ligne, &colonne);
	printf("ligne trouvée : %d ::::: colonne : %d \n", ligne, colonne);
}
void test_systeme_gauss()
{
	matrice_s *m, *valeur;

	printf("\033[31mTest de calcul de l'valeur de la matrice - GAUSS\033[00m\n");
	printf("Création d'une matrice %dx%d\n",T_MAT_INVERSE,T_MAT_INVERSE);

	m = read_matrix(T_MAT_INVERSE,T_MAT_INVERSE);

	display_matrix(m);
	printf("Création d'une matrice %dx1\n",T_MAT_INVERSE);
	valeur = read_matrix(T_MAT_INVERSE,1);

	printf("Résolution du système via le pivot de Gauss :\n");

	if(systeme_gauss_jordan(m,valeur) == 0)
		display_matrix(valeur);
	else
		printf("impossible de résoudre ce système !\n");
	
	free_matrix(valeur);
	free_matrix(m);
}
void print_menu()
{
	printf(	"\n	\033[31mMENU\033[00m\n"
			" 1 : déterminant - comatrice - transposée\n"
			" 2 : addition de 2 matrices\n"
			" 3 : multiplications de 2 matrices\n"
			" 4 : inversion - via comatrice puis par pivot\n"
			"Votre choix : "
		  );
}
void menu()
{
	int choix;
	while(1)
	{
		choix = -1;
		print_menu();

		scanf("%d",&choix);
		switch(choix)
		{
			case 1 : test_determinant_comatrice_transposee(); break;
			case 2 : test_addition_matrices(); break;
			case 3 : test_multiplication(); break; // TODO
			case 4 : test_inversion(); break; // TODO
			default : 
				printf("\033[32mERREUR CHOIX\033[00m\n");
				break;

		}
	}

//	tests_divers(); 
//	test_systeme_gauss();

}
int main(int argc, char * argv[])
{
	menu();
	return EXIT_SUCCESS;
}
