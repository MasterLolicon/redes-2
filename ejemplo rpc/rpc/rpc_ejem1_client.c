/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "rpc_ejem1.h"


void
calculadora_1(char *host)
{
	CLIENT *clnt;
	int  *result_1;
	entrada  sumar_1_arg;
	int  *result_2;
	entrada  restar_1_arg;
	int  *result_3;
	entrada  multiplicar_1_arg;
	float  *result_4;
	entrada  dividir_1_arg;

#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORA, CALCULADORA_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	sumar_1_arg.arg1 = 5;
	sumar_1_arg.arg2 = 3;

	result_1 = sumar_1(&sumar_1_arg, clnt);
	if (result_1 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	printf("\nSumar %i + %i = %i\n", sumar_1_arg.arg1, sumar_1_arg.arg2,*result_1);

	result_2 = restar_1(&sumar_1_arg, clnt);
	if (result_2 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	printf("\nRestar: %i - %i = %i\n",sumar_1_arg.arg1,sumar_1_arg.arg2,*result_2 );
	
	result_3 = multiplicar_1(&sumar_1_arg, clnt);
	if (result_3 == (int *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	printf("\nMultiplicar: %i * %i = %i\n",sumar_1_arg.arg1,sumar_1_arg.arg2,*result_3 );

	result_4 = dividir_1(&sumar_1_arg, clnt);
	if (result_4 == (float *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	printf("\nDividir: %i / %i = %f\n",sumar_1_arg.arg1,sumar_1_arg.arg2,*result_4 );
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	calculadora_1 (host);
exit (0);
}