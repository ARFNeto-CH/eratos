#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "string.h"
#include "primos-lib.h"

int main(int argc, char** argv)
{
	int		total_de_primos = 8;
	printf("proximo_primo(0) retornou %d\n", proximo_primo(0));
	for (int i = 0; i < total_de_primos; i++)
	{
		printf("proximo_primo(1) retornou %d\n", proximo_primo(1));
	}
	printf("\n***************************\n");

	calcula_mmc(4, 6, 8);
	calcula_mmc(10, 5, 6);
	calcula_mmc(3, 5, 7);
	calcula_mmc(120, 64, 222);
	calcula_mmc(120, 64, 2);
	calcula_mmc(120, 120, 120);
	calcula_mmc(13, 17, 19);
	calcula_mmc(19, 13, 17);

	return 0;
}	// end main()