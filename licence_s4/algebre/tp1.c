#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct
{
	int nbl;
	int nbc;
	float **matrice;
} matrice_s;


void display_matrix(matrice_s * m) 
{
	int i, j;

	printf( "     " );
	for ( i = 0 ; i < m->nbc ; i++ ) 
		printf( " %4d", i ); 
	printf( "\n     " );
	for ( i = 0 ; i < m->nbc ; i++ ) 
		printf( "-----" ); 
	printf( "\n" );

	for ( i = 0 ; i < m->nbl ; i++ ) 
	{
		printf( " %2d |", i );	
		for ( j = 0 ; j < m->nbc ; j++ )
			printf( " %2.2f", m->matrice[i][j] );

		printf( "\n" );
	}
	printf( "\n" );
}
matrice_s * create_matrix(int nbl, int nbc)
{
	int i;
	float **t;
	t = (float **) malloc(nbl * sizeof(float*));
	for(i = 0 ; i < nbl ; i++)
		t[i] = (float*)malloc(nbc * sizeof(float));

	matrice_s * m = malloc(sizeof(matrice_s));
	m->matrice = t;
	m->nbl = nbl;
	m->nbc = nbc;
	return m;
}
void free_matrix(matrice_s * m)
{
	int i;
	for(i = 0 ; i < m->nbl ; i++)
		free(m->matrice[i]);
	free(m->matrice);
	free(m);
}

float calcul_determinant_nxn(matrice_s *m)
{
	if(m->nbl == 2 && m->nbc == 2)
		return (m->matrice[0][0] * m->matrice[1][1]) - (m->matrice[1][0] * m->matrice[0][1]);

	float somme = 0;
	int i, j,k,l;
	matrice_s * tmp;
	for(i = 0 ; i < m->nbl ; i++)
	{
		for(j = 0 ; j < m->nbc ; j++)
		{
			tmp = create_matrix(m->nbl -1, m->nbc -1);
			for(k = 0 ; k < m->nbl ; k++)
			{
				if(k == i)
					k++;
				for(l = 0 ; l < m->nbc ; l++)
				{
					if(l == j)
						l++;
					tmp->matrice[k][l] = m->matrice[k][l];
				}
			}
			if((i % 2) == 0)
				somme += (m->matrice[i][j] * calcul_determinant_nxn(tmp));
			else
				somme -= (m->matrice[i][j] * calcul_determinant_nxn(tmp));

			free_matrix(tmp);
		}
	}
	return somme;
}
matrice_s * read_matrix( int nbl, int nbc ) 
{
	int i,j;
	float **t;
	t = (float **) malloc(nbl * sizeof(float*));
	matrice_s * m = malloc(sizeof(matrice_s));
	m->nbc = nbc;
	m->nbl = nbl;
	for(i=0; i < nbl ;i++)
		t[i] = malloc(nbc * sizeof(float));
	for(i=0;i<nbl;i++)
	{
		for(j=0;j<nbc;j++)
		{
			printf("Ligne %2d Colonne %2d : ",i,j);
			scanf("%f", &t[i][j]);
		}
	}
	m->matrice = t;
	return m;
}
matrice_s * add_matrix(matrice_s * m1, matrice_s * m2)
{
	int i, j;
	matrice_s * somme = create_matrix(m1->nbl,m1->nbc);
	
	for(i = 0 ; i < m1->nbl ; i++)
		for(j = 0 ; j < m1->nbc ; j++)
			somme->matrice[i][j] = m1->matrice[i][j] + m2->matrice[i][j];
	return somme;
}
matrice_s * multiplication_matrices(matrice_s *m1, matrice_s *m2)
{
	int i, j, k;
	int somme;
	if(m1->nbc != m2->nbl)
		return NULL;
	matrice_s *m = create_matrix(m1->nbl, m2->nbc);

	for(i = 0 ; i < m1->nbl; i++)
	{
		for(j = 0 ; j < m2->nbc ; j++)
		{
			somme = 0;
			for(k = 0; k < m1->nbc ; k++)
				somme += (m1->matrice[i][k] * m2->matrice[k][j]);
			m->matrice[i][j] = somme;
		}
	}
	return m;
}
matrice_s * transposee_matrix(matrice_s *m)
{
	int i,j;
	matrice_s * t = create_matrix(m->nbc, m->nbl);
	for(i = 0 ; i < m->nbl ; i++)
		for(j = 0 ; j < m->nbc ; j++)
			t->matrice[j][i] = m->matrice[i][j];
	return t;
}
int main(int argc, char * argv[])
{
	matrice_s *m1, *m2,*m3,*multiplication, *transposee;

	printf("Création des matrices\n");
	m1 = read_matrix(2,2);
	m2 = read_matrix(2,2);
	printf("Affichage des matrices\n");
	display_matrix(m1);
	display_matrix(m2);
	printf("Addition des matrices précédentes : \n");
	m3 = add_matrix(m1,m2);
	// Affichage 
	display_matrix(m3);

	printf("Multiplication de m1 et m2\n");
	multiplication = multiplication_matrices(m1,m2);
	display_matrix(multiplication);
	printf("Transposée de m1 \n");
	transposee = transposee_matrix(m1);
	display_matrix(transposee);

	printf("Déterminant de la première matrice : %f\n",calcul_determinant_nxn(m1));

	free_matrix(m1);
	free_matrix(m2);
	free_matrix(m3);
	free_matrix(multiplication);
	free_matrix(transposee);

	return EXIT_SUCCESS;
}
