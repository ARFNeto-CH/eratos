#pragma once
#include "primos-lib.h"

int main(int argc, char** argv)
{
	unsigned int	i = 0;
	printf("Unica\n");
	for (int i = 0; i < 10; i += 1)
	{
		int v = proximo_primo_unica(i);
		printf("Unica retornou %d para %d\n", v, i);
	};
	return 0;
}	// end main()