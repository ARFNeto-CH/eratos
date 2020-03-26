#define _CRT_SECURE_NO_WARNINGS

#include "limits.h"
#include "math.h"
#include "stdio.h"

unsigned long   	proximo_primo(unsigned int);
int					retorna_um_se_primo(unsigned int);

int main()
{
	// lista os numeros N da forma N = A*A + B*B + C*C + D*D 
	// onde A B C e D sao primos  consecutivos

	unsigned long p1, p2, p3, p4; // os 4 primeiros
	unsigned long proximo = 0;

	proximo_primo(0);
	p1 = proximo_primo(1);
	p2 = proximo_primo(1);
	p3 = proximo_primo(1);
	p4 = proximo_primo(1);
	int seq = 1;
	long N = 0;
	N = (p1*p1) + (p2*p2) + (p3*p3) + (p4*p4);

	while (N < 10000000)
	{
		printf("%8ld    ", N);
		if (seq % 8 == 0) printf("\n");
		seq += 1;
		p1 = p2;
		p2 = p3;
		p3 = p4;
		p4 = proximo_primo(1);
		N = (p1 * p1 + p2 + p2 + p3 * p3 + p4 * p4);
	};	// while()
	printf("\n\nListados %d valores\n\n", seq);
};	// main()

int				retorna_um_se_primo(unsigned long n)
{
	if (n < 2)		return 0;
	if (n == 2)		return(1);
	if (n % 2 == 0) return(0);
	unsigned long maior = (unsigned int)sqrt((double)n);
	unsigned long fator = 3;
	while (fator <= maior)
	{
		if (n % fator == 0) return 0;
		fator += 2;
	}	// end while
	return 1;
}	// end retorna_zero_se_primo()

unsigned long	proximo_primo(unsigned long n)
{
	static long	 iniciado = 0;
	static long	 proximo = 0;

	if (n == 0)						// inicia a serie
	{
		iniciado = 1;
		proximo = 2;
		return 1;
	}	// end if

	if (iniciado == 0) return 0;		// erro: tem que chamar com 0 antes

	if (proximo == 2)
	{
		proximo = 1;
		return 2;
	}	// end if

	// normal: a a partir daqui retorna o proximo primo
	for (long i = proximo + 2;; i += 2)
		if (retorna_um_se_primo(i))
		{
			proximo = i;
			return proximo;
		}	// end if
}	// end proximo_primo()

// fim do texto