#pragma once
#include "primos-lib.h"

int main(int argc, char** argv)
{
	unsigned int n;
	if (argc > 1)	n = strtoul(argv[1], 0, 0);
	else
		n = 200;
	unsigned int	i = 0; 
	unsigned int	lim = limita_memoria(n);

	printf("\n\nTestando com n=%u\n", lim);
	if (lim < n)
	{
		printf("Valor original %u truncado por falta de memoria para o crivo\n", n);
		printf("Memoria reservada = %uKB\n", LIMITE_A_ALOCAR_KB );
	}	// end if

	i = mostra_os_primos(lim);
	printf("\n\nEncontrados %u primos\n", i);

	// agora testa a funcao unica e compara com os valores obtidos do crivo de eratostenes
	i = compara_primos_com_crivo_unica(lim);
	if (i == 1)
		printf("Testando (nova) primos contra os marcados no crivo: sem surpresas. Todos os valores coincidem\n");
	else
		printf("Testando (nova) primos contra os marcados no crivo: Algo errado!\n");


	// agora testa a funcao e compara com os valores obtidos do crivo de eratostenes
	i = compara_primos_com_crivo(lim);
	if (i == 1)
		printf("Testando primos contra os marcados no crivo: sem surpresas. Todos os valores coincidem\n");
	else
		printf("Testando primos contra os marcados no crivo: Algo errado!\n");

	// agora testa o crivo e com a funcao verifica se todos sao primos
	i = testa_crivo_contra_funcao(lim);
	if (i == 1)	printf("Testando os valores do crivo com a funcao: sem surpresas. todos os valores confirmados\n");
	else
		printf("Testando os valores do crivo com a funcao: Algo errado\n");

	i = retorna_um_se_primo(UINT_MAX);
	printf("\n\n retorna_um_se_primo(UINT_MAX=%u) retornou %u\n", UINT_MAX, i);
	return 0;

}	// end main()