#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "base.h"
#include "calculs_base.h"
#include "determinant.h"
#include "inversion.h"
#include "comatrice.h"
#include "pivot-gauss.h"
#include "valeurs-propres.h"

#define T_MAT 3

// Pour afficher joliement si un polynôme est vide ou pas
void afficher_poly_vide_ou_pas(polynome_s * p)
{
	printf(" Le polynôme suivant est-il nul ?\n");
	display_polynome(p);
	if( 0 == polynome_vide(p))
		printf("\033[31m OUI \033[00m \n");
	else
		printf("\033[31m NON \033[00m \n");
}
void choix_nbl_nbc(int * nbl, int * nbc)
{
	printf("Nombre de lignes : ");
	scanf("%d",nbl);
	printf("Nombre de colonnes : ");
	scanf("%d",nbc);
}
// Pour créer joliement une matrice
matrice_s * creation_matrice()
{
	matrice_s * m;
	int nbl, nbc;
	int choix = 0;
	printf("Création d'une matrice, \033[31m-- choix de la dimension\033[00m\n");
	choix_nbl_nbc(&nbl, &nbc);
	while(choix == 0)
	{
		printf(	"Choix 1 : remplissage aléatoire de la matrice\n"
				"Choix 2 : remplir soi-même\nVotre choix : ");
		scanf("%d",&choix);
		switch(choix)
		{
			case 1 : m = random_matrix(nbl, nbc); break;
			case 2 : m = read_matrix(nbl, nbc); break;
			default : choix = 0; break;
		}
	}
	return m;
}
void test_determinant_comatrice_transposee()
{
	matrice_s *m, *co, *tr;

	printf(	"\033[32mdéterminant - comatrice - transposée \033[00m "
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
	printf("\033[32mmultiplication \033[00m"
			"\033[31m-- création de 2 matrices\033[00m\n");
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
	printf(	"\033[32maddition \033[00m"
			"\033[31m-- création de 2 matrices \033[00m\n");
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

	printf("La matrice créee : \n");
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
	matrice_s * m = random_matrix(T_MAT,T_MAT);
	display_matrix(m);

	printf("Addition de 2 lignes : l1 += l0 * 2\n\n");
	addition_lignes(m,0, 1, 2);
	display_matrix(m);
	printf("Inversion de 2 lignes : la 2 et la 3\n\n");
	inversion_lignes(m, 2,3);
	display_matrix(m);

	free_matrix(m);
	
}
void tests_divers()
{
	printf("Matrice identitée de %d \n", T_MAT);
	matrice_s * identitee;
	identitee = matrice_identitee(T_MAT);
	display_matrix(identitee);

	matrice_s * autre = matrice_identitee(T_MAT);

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

	free_matrix(identitee);
	free_matrix(autre);
}
void test_systeme_gauss()
{
	matrice_s *m, *valeur;
	int retour_fonction_pivot;
	printf("\033[32mRésolution de système via pivot de Gauss\033[00m ");
	printf("\033[31m-- création d'une matrice\033[00m\n");

	m = creation_matrice();

	printf("La matrice créée : \n");
	display_matrix(m);
	printf("Création d'une matrice %dx1\n",m->nbl);
	valeur = read_matrix(m->nbl,1);

	printf("Résolution du système via le pivot de Gauss :\n");

	if((retour_fonction_pivot = pivot_gauss_double_matrice(m,valeur)) >= 0)
	{
		display_matrix(valeur);
		if(retour_fonction_pivot != 0)
			printf("Une valeur s'exprime en fonction des autres : %d (numéro de ligne vide)\n", retour_fonction_pivot);
	}
	else
		printf("impossible de résoudre ce système !\n");
	
	free_matrix(valeur);
	free_matrix(m);
}
void test_polynomes()
{	
	polynome_s *p, *p2, *pmult;

	printf(	"\n\033[32mPolynômes\033[31m -- "
			"création et affichage d'un polynôme 10.35x^2 + 15.3x - 20 \033[00m\n");
	p = creation_poly_sec(10.35,15.3, -20.0);
	display_polynome(p);
	printf(	"		-- désallocation puis création d'un polynôme de premier degré : 2.2x + 5.3\n");
	free_polynome(p);
	p = creation_poly_prem(2.2,5.3);
	display_polynome(p);
	printf("		-- création d'un second polynôme 2x - 2 puis \033[31m multiplication \033[00m \n");
	p2 = creation_poly_prem(2,-2);
	pmult = multiplication_polynomes_prem(p,p2);
	display_polynome(pmult);
	free_polynome(p);
	free_polynome(p2);
	p = creation_poly_sec(1,-2,5);
	printf("		-- \033[31m  soustraction \033[00m de 1x^2 -2x +5 \n" );
	p2 = soustraction_polynomes_sec(pmult, p);
	display_polynome(p2);
	afficher_poly_vide_ou_pas(p2);
	free_polynome(p);
	p = creation_poly_sec(0,0,0);
	afficher_poly_vide_ou_pas(p);



	free_polynome(p);
	free_polynome(p2);
	free_polynome(pmult);
}
void test_pmatrices()
{
	pmatrice_s * pm;
	matrice_s * m = random_matrix(3,3);

	printf(	"\033[32mPmatrices \033[00m"
			"\033[31m-- création aléatoire d'une matrice 3x3\033[00m\n");
	display_matrix(m);
	printf(	"Création d'une pmatrice à partir de cette matrice (avec -delta sur la diagonale)\n");
	pm = create_matrix_poly(m);
	display_pmatrix(pm);

	printf(	"Inversion de 2 colonnes 1 et 2\n");
	pmatrice_inversion_colonnes(pm, 1,2);
	display_pmatrix(pm);

	printf(	"Inversion de 2 lignes 1 et 2\n");
	pmatrice_inversion_lignes(pm, 1,2);
	display_pmatrix(pm);

	printf(	"Ligne 0 += 3 * Ligne 2\n");
	pmatrice_addition_lignes(pm, 0, 2, 3);
	display_pmatrix(pm);

	
	free_matrix(m);
	free_pmatrice(pm);

}
void test_valeurs_propres()
{
	int i,j;
	matrice_s *vpropres, *vpropretmp, *m;
	pmatrice_s * pm;
	printf(	"\033[32mValeurs propres \033[00m"
			"\033[31m-- création d'une matrice 3x3\033[00m\n"
			"((( Rappel : il faut entrer une matrice qui a déjà deux zéro sur la même ligne ou colonne - la diagonale ne compte pas - )))\n"
			);

	printf(	"La matrice : \n\n");
	m = read_matrix(3,3);
	display_matrix(m);

	printf(	"Création de la pmatrice (matrice de polynômes avec -delta sur la diagonale) \n\n");
	pm = create_matrix_poly(m);
	display_pmatrix(pm);
	vpropres = valeurs_propres(pm);

	if( NULL != vpropres)
	{
		printf("\033[31m	Les valeurs propres calculées : \033[00m \n\n");
		display_matrix(vpropres);

		printf("On va calculer les valeurs des vecteurs propres via le pivot de Gauss: \n");
		printf("	-- pour rappel A = \n");
		display_matrix(m);
		
		for(i = 0 ; i < vpropres->nbl ; i++)
		{	
			printf("\n Résultat pivot de Gauss pour : \n(A) ( %3.3lf %3.3lf %3.3lf )  (vecteur colonne)\n", 
					vpropres->matrice[i][0], vpropres->matrice[i][0], vpropres->matrice[i][0]);
			vpropretmp = create_matrix(vpropres->nbl, 1);
			for(j = 0 ; j < vpropres->nbl ; j++)
				vpropretmp->matrice[j][0] = vpropres->matrice[i][0];
			if( 0 <= pivot_gauss_double_matrice(m, vpropretmp))
			{
				printf("Vecteur propre : \n");
				display_matrix(vpropretmp);
			}
			else
				printf("Vecteur propre impossible à trouver\n");
			free_matrix(vpropretmp);
		}
		free_matrix(vpropres);
	}
	else
		printf("\033[31mImpossible de calculer les valeurs propres ! \033[00m \n");

	free_matrix(m);
	free_pmatrice(pm);
}
void print_menu()
{
	printf(	"\n	\033[31mMENU\033[00m\n"
			" 1 : déterminant - comatrice - transposée\n"
			" 2 : addition de 2 matrices\n"
			" 3 : multiplication de 2 matrices\n"
			" 4 : inversion - via comatrice puis par pivot\n"
			" 5 : résolution de système\n"
			" 6 : calcul de valeurs propres d'une matrice\n"
			" ---------------\033[34m-----DEV-------\033[00m-------------- \n"
			" 10 : tests divers sur les polynômes\n"
			" 11 : tests divers sur les pmatrices\n"
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
			case 3 : test_multiplication(); break;	
			case 4 : test_inversion(); break;
			case 5 : test_systeme_gauss(); break;
			case 6 : test_valeurs_propres(); break;
			case 10 : test_polynomes(); break;
			case 11 : test_pmatrices(); break;
			default : 
				printf("\033[32mERREUR CHOIX\033[00m\n");
				break;

		}
	}
}
int main(int argc, char * argv[])
{
	menu();
	return EXIT_SUCCESS;
}
