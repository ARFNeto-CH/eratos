#define _CRT_SECURE_NO_WARNINGS

#include "limits.h"
#include "math.h"
#include "stdio.h"

unsigned int   	proximo_primo(unsigned int);
int				retorna_um_se_primo(unsigned int);

int main()
{
	// lista os numeros N da forma N = A*A + B*B + C*C + D*D 
	// onde A B C e D sao primos  consecutivos
	unsigned int p1, p2, p3, p4; // os 4 primeiros
	unsigned int N;
	proximo_primo(0);
	p1 = proximo_primo(1); // 2
	p2 = proximo_primo(1); // 3
	p3 = proximo_primo(1); // 5
	p4 = proximo_primo(1); // 7
	int seq = 1;
	//if (seq == 0) return 0;
	while (1)
	{	
		N = (p1*p1) + (p2*p2) + (p3*p3) + (p4*p4);
		if (N > 10000000) break;
		printf(
			"%3d: %10d = %ld + %ld + %ld + %ld\
\t[%d,%d,%d,%d]\n",
			seq, N, (p1*p1), (p2*p2), (p3*p3), (p4*p4),
			p1, p2, p3, p4 );
		seq += 1;
		p1 = p2;
		p2 = p3;
		p3 = p4;
		p4 = proximo_primo(1);
	};	// while()
	// tinha passado: soma antes
	printf("\n\nListados %d valores\n\n", seq-1);

	proximo_primo(0);
	p1 = proximo_primo(1);
	p2 = proximo_primo(1);
	p3 = proximo_primo(1);
	p4 = proximo_primo(1);
	printf("Iniciando com [%d,%d,%d,%d]\n",
		p1, p2, p3, p4);
	seq = 0;
	N = 0;
	N = (p1*p1) + (p2*p2) + (p3*p3) + (p4*p4);
	while (N < 10000000)
	{	seq += 1;
		printf("%8ld    ", N);
		if (seq % 8 == 0) printf("\n");
		p1 = p2;
		p2 = p3;
		p3 = p4;
		p4 = proximo_primo(1);
		N = (p1*p1 + p2*p2 + p3*p3 + p4*p4);
	};	// while()
	printf("\n\nListados %d valores\n\n", seq);
};	// main()

int				retorna_um_se_primo(unsigned int n)
{
	if (n < 2)		return 0;
	if (n == 2)		return(1);
	if (n % 2 == 0) return(0);
	unsigned int maior = (unsigned int)sqrt((double)n);
	unsigned int fator = 3;
	while (fator <= maior)
	{
		if (n % fator == 0) return 0;
		fator += 2;
	}	// end while
	return 1;
}	// end retorna_zero_se_primo()

unsigned int	proximo_primo(unsigned int n)
{
	static int	 iniciado = 0;
	static int	 proximo = 0;

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
	for (int i = proximo + 2;; i += 2)
		if (retorna_um_se_primo(i))
		{
			proximo = i;
			return proximo;
		}	// end if
}	// end proximo_primo()

// fim do texto