#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "math.h"

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


unsigned int	calcula_mmc(int a, int b, int c)
{
	char	produtos[256];					// para montar o resultado
	int		mmc = 1;						// o proprio MMC
	int		n;
	int		primo = proximo_primo(0);		// inicia o gerador
	sprintf(produtos, " mmc(%d;%d;%d) = 1", a, b, c);
	primo = proximo_primo(1);				// pega o 2
	printf("\n\n%5d; %5d; %5d |", a, b, c);	// comeca o esquema
	do
	{
		n = 0;
		if (a % primo == 0)	n += 1, a = a / primo;			// a = multiplo
		if (b % primo == 0)	n += 1, b = b / primo;			// b = multiplo
		if (c % primo == 0)	n += 1, c = c / primo;			// c = multiplo
		if (n == 0)
			primo = proximo_primo(1);		// nem a nem b nem c e multiplo desse
		else
		{
			sprintf(produtos, "%sx%u", produtos, primo);	// acrescenta fator ou vai perder
			printf(" %5d\n%5d; %5d; %5d |", primo, a, b, c);	// nova linha
			mmc = mmc * primo;				// atualiza MMC
		}	// end if
		if (a > 1 || b > 1 || c > 1) continue;	// ainda tem ao menos 1
		break;
	} while (1);								// vai sair apenas com 1;1;1
	printf("\n--------------------|-------\n                    |%s = %d\n", produtos, mmc);
	return mmc;
}	// end calcula_mmc()



int main()
{
	int a, b, c, mmc, i;
	
	i = 2;
	calcula_mmc(10, 5, 6);
	if (i == 2) return 0;

	scanf("%d %d %d", &a, &b, &c);

	mmc = 1;

	if (a == 0 || b == 0 || c == 0)
	{
		return 0;
	}

	while (a + b + c  != 2)
	{
		if (a % i == 0 || b % i == 0)
		{
			mmc += i;
			if (a % i  == 0)
			{
				a /= i;
			}
			if (b % i == 0)
			{
				b /= i;
			}
			if (c % i == 0)
			{
				c /= i;
			}
		}
		else
		{
			c += 1;
		}
	}	// while()
	printf("MMC= %d", mmc);
}