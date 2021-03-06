#include "include.h"

int main (int argc, char **argv)
{
	char *host ;
	int stat;
	entiers2 res ;
	entiers2 donnees = {13 , 5} ;

	if (argc != 2)
	{
		printf("Usage : %s <MachineName>\n", argv[0]) ;
		exit(-1) ;
	}
	host = argv[1] ;

	// Appel à la procédure rpc distance
	stat = callrpc(host, PROGNUM, VERSNUM, PROCNUM,
			(xdrproc_t) xdr_entiers2, // procédure pour encoder le paramètre
			(char *) &donnees, // pointeur vers la donnée (paramètre)
			(xdrproc_t) xdr_entiers2, // procédure pour décoder le résultat
			(char *)&res); // adresse d'un pointeur vers le résultat
	if (stat != RPC_SUCCESS)
	{
		fprintf(stderr, "Echec de l'appel distant\n") ;
		clnt_perrno(stat) ;
		fprintf(stderr, "\n") ;
		return 1 ;
	}

	printf("client res : %d/%d (q:%d r:%d)\n",donnees.x,donnees.y,res.x,res.y) ;

	return (0) ;
}
